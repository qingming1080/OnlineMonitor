#include "hbmodbusclient.h"
#include <QModbusDataUnit>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QModbusTcpClient>
#include <QModbusReply>
#include <QDebug>
#include <QtConcurrent/QtConcurrent>
#include "tools/datavalidator.h"
#include "tools/utilityfunction.h"
#include "define.h"


constexpr char HBModbusClient::LOCAL_IP[13];
constexpr int HBModbusClient::SERVER_PORT;
unsigned char HBModbusClient::m_Coils[SYS_COILS_REGISTERS_COUNT + DEV_COILS_REGISTERS_COUNT * DEV_COUNT] = {0};
unsigned char HBModbusClient::m_Discreteds[DEV_DISCRETE_REGISTERS_COUNT * DEV_COUNT] = {0};
unsigned char  HBModbusClient::m_LastDiscreteds[DEV_DISCRETE_REGISTERS_COUNT * DEV_COUNT];
unsigned short HBModbusClient::m_Holdings[SYS_HOLDING_REGISTERS_COUNT + DEV_HOLDING_REGISTERS_COUNT * DEV_COUNT] = {0};
unsigned short HBModbusClient::m_Inputs[DEV_INPUT_REGISTERS_COUNT * DEV_COUNT] = {0};
unsigned int HBModbusClient::m_iPreviousCycleCount[DEV_COUNT] = {0, 0, 0, 0};
QVector<WELD_PRESET> HBModbusClient::m_lastPresets(DEV_COUNT);
HBModbusClient* HBModbusClient::m_instance = nullptr;

HBModbusClient::HBModbusClient( QObject *parent)
    : QObject(parent){

    modbusClient = new QModbusTcpClient(this);
    connectToServer(QString(LOCAL_IP), SERVER_PORT);

    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, this, &HBModbusClient::onPollingTimeoutEvent);
    m_timer->start();
    m_WelderDeviceMap.clear();
}

HBModbusClient *HBModbusClient::getInstance()
{
    if (!m_instance)
        m_instance = new HBModbusClient();
    return m_instance;
}

HBModbusClient::~HBModbusClient()
{

    if (modbusClient) {
        modbusClient->disconnectDevice();
        delete modbusClient;
    }
}

bool HBModbusClient::connectToServer(const QString &host, int port)
{
    modbusClient->setConnectionParameter(QModbusTcpClient::NetworkAddressParameter, host);
    modbusClient->setConnectionParameter(QModbusTcpClient::NetworkPortParameter, port);
    return modbusClient->connectDevice();
}

void HBModbusClient::reconnectToServer()
{
    if(modbusClient->state() == QModbusDevice::ConnectedState)
        return;

    modbusClient->disconnectDevice();
    QThread::msleep(1000);
    modbusClient->connectDevice();
    qDebug() << "尝试重新连接Modbus服务器...";
}

void HBModbusClient::onPollingTimeoutEvent()
{
    if(modbusClient->state() == QModbusDevice::ConnectedState)
    {
        readRegisters(QModbusDataUnit::HoldingRegisters, SYS_RTC_YY, SYS_HOLDING_REGISTERS_COUNT, "Modbus系统保持寄存器读取失败:");

        readRegisters(QModbusDataUnit::HoldingRegisters, HOLDING_REGISTERS_ADDRESS_BASE, DEV_HOLDING_REGISTERS_COUNT * DEV_COUNT, "Modbus设备保持寄存器读取失败:");

        readRegisters(QModbusDataUnit::InputRegisters, DEV_CYCLE_COUNT_H, DEV_INPUT_REGISTERS_COUNT * DEV_COUNT, "Modbus输入寄存器读取失败:");

        readRegisters(QModbusDataUnit::Coils, SYS_LED_L_BIT0, SYS_COILS_REGISTERS_COUNT + DEV_COILS_REGISTERS_COUNT * DEV_COUNT, "Modbus线圈读取失败:");

        readRegisters(QModbusDataUnit::DiscreteInputs, DEV_STATUE, DEV_DISCRETE_REGISTERS_COUNT * DEV_COUNT, "Modbus离散输入读取失败:");
    }
    else
    {
        modbusClient->connectDevice();
    }
}

void HBModbusClient::readRegisters(QModbusDataUnit::RegisterType type,int startAddress, int count, const char* errMsg)
{
    QModbusDataUnit unit(type, startAddress, count);

    if (auto* reply = modbusClient->sendReadRequest(unit, 1))
    {
        connect(reply, &QModbusReply::finished, this,[this, reply, errMsg, type, startAddress]()
                {

                    if (reply->error() == QModbusDevice::NoError)
                    {
                        const QModbusDataUnit modbusDataUnit = reply->result();


                        for (int i = 0; i < modbusDataUnit.valueCount(); ++i)
                        {
                            const quint16 value = modbusDataUnit.value(i);
                            const int index = startAddress + i;

                            switch (type)
                            {
                            case QModbusDataUnit::HoldingRegisters:
                                m_Holdings[index] = value;
                                break;
                            case QModbusDataUnit::InputRegisters:
                                m_Inputs[index] = value;
                                break;
                            case QModbusDataUnit::Coils:
                                m_Coils[index] = value;
                                break;
                            case QModbusDataUnit::DiscreteInputs:
                                m_Discreteds[index] = value;
                                break;
                            default: break;
                            }
                        }

                        switch (type)
                        {
                        case QModbusDataUnit::HoldingRegisters:
                            if (startAddress >= HOLDING_REGISTERS_ADDRESS_BASE)
                                ParsePresetSetting();
                            break;
                        case QModbusDataUnit::InputRegisters:
                            ParseWeldResult();
                            break;
                        case QModbusDataUnit::DiscreteInputs:
                            ParseDeviceStatus();
                            break;
                        case QModbusDataUnit::Coils:
                            ParseResetButton();
                            ParseDeviceIOResetStatus();
                            break;
                        default:
                            break;
                        }

                    } else
                    {
                        qWarning() << errMsg << reply->errorString();
                    }

                    reply->deleteLater();
                });
    }
}

void HBModbusClient::WriteHoldingRegisters(int startAddress, const QVector<quint16>& values)
{

    // QMutexLocker locker(&m_mutex);
    for (int i = 0; i < values.size(); ++i)
    {
        m_Holdings[startAddress + i] = values[i];
    }

    if (modbusClient->state() == QModbusDevice::ConnectedState)
    {
        QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, startAddress, values.size());
        for (int i = 0; i < values.size(); ++i)
        {
            writeUnit.setValue(i, values[i]);
        }

        if (auto *reply = modbusClient->sendWriteRequest(writeUnit, 1))
        {
            connect(reply, &QModbusReply::finished, this, [reply]()
            {
                reply->deleteLater();
            });
        }
    } else {
        qWarning() << "Modbus未连接，写保持寄存器失败";
    }
}

void HBModbusClient::WriteCoils(int startAddress, const QVector<quint8>& values)
{
    for (int i = 0; i < values.size(); ++i)
    {
        m_Coils[startAddress + i] = values[i];
    }
    if (modbusClient->state() == QModbusDevice::ConnectedState)
    {
        QModbusDataUnit writeUnit(QModbusDataUnit::Coils, startAddress, values.size());
        for (int i = 0; i < values.size(); ++i)
        {
            writeUnit.setValue(i, values[i]);
            qDebug() << "WriteCoils success, addr:" << startAddress << "values:" << values;
        }
        if (auto *reply = modbusClient->sendWriteRequest(writeUnit, 1))
        {
            connect(reply, &QModbusReply::finished, this, [reply]()
            {
                if (reply->error() != QModbusDevice::NoError)
                {
                    qWarning() << "写入线圈失败:" << reply->errorString();
                }
                reply->deleteLater();
            });
        }
    } else {
        qWarning() << "Modbus未连接，写线圈失败";
    }
}

void HBModbusClient::ParseWeldResult()
{
    for (int i = 0; i < DEV_COUNT ; ++i)
    {
        int base = i * DEV_INPUT_REGISTERS_COUNT;
        quint16 high = m_Inputs[base + DEV_CYCLE_COUNT_H];
        quint16 low  = m_Inputs[base + DEV_CYCLE_COUNT_L];
        quint32 cycleCount = (quint32(high) << 16) | quint32(low);
        if((m_iPreviousCycleCount[i] != cycleCount) && (cycleCount > 0))
        {
            m_iPreviousCycleCount[i] = cycleCount;
            MODBUS_WELD_RESULT data;
            data.CycleCount      = cycleCount;
            data.Energy          = m_Inputs[base + DEV_ENERGY];
            data.Amplitude       = m_Inputs[base + DEV_AMPLITUDE];
            data.TriggerPressure = m_Inputs[base + DEV_TP];
            data.WeldingPressure = m_Inputs[base + DEV_WP];
            data.WeldTime        = m_Inputs[base + DEV_TIME];
            data.PeakPower       = m_Inputs[base + DEV_POWER];
            data.Preheight       = m_Inputs[base + DEV_PRE_HEIGHT];
            data.PostHeight      = m_Inputs[base + DEV_POST_HEIGHT];
            data.WeldAlarm       = m_Inputs[base + DEV_WELD_ALARM];
            int year   = m_Inputs[base + DEV_YY];
            int month  = m_Inputs[base + DEV_YY_MM];
            int day    = m_Inputs[base + DEV_DD];
            int hour   = m_Inputs[base + DEV_HH];
            int minute = m_Inputs[base + DEV_MM];
            int second = m_Inputs[base + DEV_SS];
            QDate date = QDate(year, month, day);
            QTime time = QTime(hour, minute, second);
            data.DateTime = QDateTime(date, time);

            qDebug() << "[ParseWeldResult] Device:" << i
                     << "CycleCount:" << data.CycleCount
                     << "Energy:" << data.Energy
                     << "Amplitude:" << data.Amplitude
                     << "TriggerPressure:" << data.TriggerPressure
                     << "WeldingPressure:" << data.WeldingPressure
                     << "WeldTime:" << data.WeldTime
                     << "PeakPower:" << data.PeakPower
                     << "Preheight:" << data.Preheight
                     << "PostHeight:" << data.PostHeight
                     << "WeldAlarm:" << data.WeldAlarm
                     << "DateTime:" << data.DateTime.toString("yyyy-MM-dd HH:mm:ss");

            for(auto iter = m_WelderDeviceMap.begin(); iter != m_WelderDeviceMap.end(); iter++)
            {
                if(iter.value() == i)
                {
                    emit notifyWeldResultComing(iter.key(), data);
                    break;
                }
            }
        }
    }
}

void HBModbusClient::ParsePresetSetting()
{
    WELD_PRESET weldPreset;
    for (int i = 0; i < DEV_COUNT; ++i)
    {
        int base = SYS_HOLDING_REGISTERS_COUNT + i * DEV_HOLDING_REGISTERS_COUNT;;
        weldPreset.Energy          = m_Holdings[base + (DEV_ENERGY_SET - SYS_HOLDING_REGISTERS_COUNT)];
        weldPreset.Amplitude       = m_Holdings[base + (DEV_AMPLITUDE_SET - SYS_HOLDING_REGISTERS_COUNT)];
        weldPreset.TriggerPressure = m_Holdings[base + (DEV_TP_SET - SYS_HOLDING_REGISTERS_COUNT)];
        weldPreset.WeldingPressure = m_Holdings[base + (DEV_WP_SET - SYS_HOLDING_REGISTERS_COUNT)];


        bool changed = m_isFirstPresetParse ||
            weldPreset.Energy          != m_lastPresets[i].Energy ||
            weldPreset.Amplitude       != m_lastPresets[i].Amplitude ||
            weldPreset.TriggerPressure != m_lastPresets[i].TriggerPressure ||
            weldPreset.WeldingPressure != m_lastPresets[i].WeldingPressure;

        if (changed)
        {
            qDebug() << "[ParsePresetSetting] Device:" << i
                     << "Energy:" << weldPreset.Energy
                     << "Amplitude:" << weldPreset.Amplitude
                     << "TriggerPressure:" << weldPreset.TriggerPressure
                     << "WeldingPressure:" << weldPreset.WeldingPressure;
            for(auto iter = m_WelderDeviceMap.begin(); iter != m_WelderDeviceMap.end(); iter++)
            {
                if(iter.value() == i)
                {
                    emit notifyPresetSettingChanged(iter.key(), weldPreset);
                    break;
                }
            }
            m_lastPresets[i] = weldPreset;
        }
    }
    m_isFirstPresetParse = false;
}

void HBModbusClient::ParseDeviceStatus()
{
    int base = 0;
    DEVICE_STATUS DeviceStatus;
    for (int i = 0; i < DEV_COUNT; ++i)
    {
        base = i * DEV_DISCRETE_REGISTERS_COUNT;
        DeviceStatus.IsDeviceStatus     = m_Discreteds[base + DEV_STATUE];
        DeviceStatus.IsDeviceDataStatus = m_Discreteds[base + DEV_DATA_STATUE];
        for(auto iter = m_WelderDeviceMap.begin(); iter != m_WelderDeviceMap.end(); iter++)
        {
            if(iter.value() == i)
            {
                emit notifyDeviceStatusChanged(iter.key(), DeviceStatus);
            }
        }
    }
}

void HBModbusClient::ParseResetButton()
{
    bool bResetButtonStatus = m_Coils[SYS_BTN_R_BIT4];
    setResetButtonStatus(bResetButtonStatus);
}

void HBModbusClient::ParseDeviceIOResetStatus()
{
    int base = 0;
    IO_STATUS IOStatus;
    for (int i = 0; i < DEV_COUNT; ++i)
    {
        base = SYS_COILS_REGISTERS_COUNT + i * DEV_COILS_REGISTERS_COUNT;
        IOStatus.IOResetStatus = m_Coils[base + DEV_RESET_BIT2 - SYS_COILS_REGISTERS_COUNT];
        for(auto iter = m_WelderDeviceMap.begin(); iter != m_WelderDeviceMap.end(); iter++)
        {
            if(iter.value() == i)
            {
                emit notifyDeviceIOStatusChanged(iter.key(), IOStatus);
                break;
            }
        }
    }
}

void HBModbusClient::setSystemClock(const QDateTime &datetime)
{
    QVector<quint16> rtcValues;
    QDate date = datetime.date();
    QTime time = datetime.time();
    qDebug() << "设置系统时间:"
             << date.toString("yyyy-MM-dd")
             << time.toString("HH:mm:ss");

    rtcValues.append(date.year());
    rtcValues.append(date.month());
    rtcValues.append(date.day());
    rtcValues.append(time.hour());
    rtcValues.append(time.minute());
    rtcValues.append(time.second());

        qDebug() << "写入RTC寄存器值:" << rtcValues;
    WriteHoldingRegisters(SYS_RTC_YY, rtcValues);
}

Q_INVOKABLE void HBModbusClient::setLearnLedStatus(bool condition)
{
    updateLedStatus(SYS_LED_L_BIT0, condition);
}

Q_INVOKABLE void HBModbusClient::setPilotLedStatus(bool condition)
{
    updateLedStatus(SYS_LED_P_BIT1, condition);
}

Q_INVOKABLE void HBModbusClient::setReadyLedStatus(bool condition)
{
    updateLedStatus(SYS_LED_R_BIT2, condition);
}

Q_INVOKABLE void HBModbusClient::setAlarmLedStatus(bool condition)
{
    updateLedStatus(SYS_LED_A_BIT3, condition);
}

void HBModbusClient::updateLedStatus(int ledIndex, bool condition)
{
    QVector<quint8> values(4, 0);
    values[0] = m_Coils[SYS_LED_L_BIT0];
    values[1] = m_Coils[SYS_LED_P_BIT1];
    values[2] = m_Coils[SYS_LED_R_BIT2];
    values[3] = m_Coils[SYS_LED_A_BIT3];

    values[ledIndex] = condition ? 1 : 0;
    WriteCoils(SYS_LED_L_BIT0, values);
    m_Coils[SYS_LED_L_BIT0 + ledIndex] = values[ledIndex];
}

Q_INVOKABLE void HBModbusClient::setDeviceIOStatusReject(int welderId, bool condition)
{
    int deviceId = -1;
    auto iter = m_WelderDeviceMap.find(welderId);
    if(iter != m_WelderDeviceMap.end())
        deviceId = iter.value();
    else
        return;
    if (deviceId < 0 || deviceId > (DEV_COUNT - 1))
        return;
    int base = SYS_COILS_REGISTERS_COUNT + deviceId * DEV_COILS_REGISTERS_COUNT;;
    int rejectAddress = base + DEV_REJECT_BIT0 - SYS_COILS_REGISTERS_COUNT;

    QVector<quint8> value(1, condition ? 1 : 0);
    WriteCoils(rejectAddress, value);
}

Q_INVOKABLE void HBModbusClient::setDeviceIOStatusSuspect(int welderId, bool condition)
{
    int deviceId = -1;
    auto iter = m_WelderDeviceMap.find(welderId);
    if(iter != m_WelderDeviceMap.end())
        deviceId = iter.value();
    else
        return;
    if (deviceId < 0 || deviceId > (DEV_COUNT - 1))
        return;
    int base = SYS_COILS_REGISTERS_COUNT + (deviceId - 1) * DEV_COILS_REGISTERS_COUNT;;
    int suspectAddress = base + DEV_SUSPECT_BIT1 - SYS_COILS_REGISTERS_COUNT;

    QVector<quint8> value(1, condition ? 1 : 0);
    WriteCoils(suspectAddress, value);

}

void HBModbusClient::setMesConfig(const QVector<quint16> mesHostValues)
{
    WriteHoldingRegisters(SYS_MES_IP1, mesHostValues);
}

void HBModbusClient::setResetButtonStatus(const bool status)
{
    if(status != m_bFrontPanelResetButton)
    {
        m_bFrontPanelResetButton = status;
        emit notifyResetButtonStatus(status);
    }
}

bool HBModbusClient::getResetButtonStatus() const
{
    return m_bFrontPanelResetButton;
}

void HBModbusClient::setDeviceConfigure(const int welderId, const MODBUS_CONFIGURE deviceConfig)
{
    auto iter = m_WelderDeviceMap.find(welderId);
    int base = 0;
    if(iter != m_WelderDeviceMap.end())
    {
        base = DEV_TYPE + iter.value() * DEV_HOLDING_REGISTERS_COUNT;
    }
    else
    {
        if(m_WelderDeviceMap.size() < DEV_COUNT)
        {
            int deviceId = m_WelderDeviceMap.size();
            m_WelderDeviceMap.insert(welderId, deviceId);
            base = DEV_TYPE + deviceId * DEV_HOLDING_REGISTERS_COUNT;
        }
    }

    qDebug() << "Modbus Device Map";
    for(auto iter = m_WelderDeviceMap.begin(); iter != m_WelderDeviceMap.end(); iter++)
    {
        qDebug() << " welderId: " << iter.key()
                 << " deviceId: " << iter.value();
    }

    QVector<quint16> deviceConfiginfo;
    deviceConfiginfo.append(deviceConfig.ConnectType);
    deviceConfiginfo.append(deviceConfig.ProtocolType);
    deviceConfiginfo.append(DeviceInfoEnum::CONNECTED);

    if (deviceConfig.ConnectType == DeviceInfoEnum::TCP_IP)
    {
        QStringList remote = deviceConfig.NetworkProperties.RemoteIP.split(".");
        QStringList local  = deviceConfig.NetworkProperties.LocalIP.split(".");

        deviceConfiginfo.append(remote.value(0).toUShort());
        deviceConfiginfo.append(remote.value(1).toUShort());
        deviceConfiginfo.append(remote.value(2).toUShort());
        deviceConfiginfo.append(remote.value(3).toUShort());

        deviceConfiginfo.append(local.value(0).toUShort());
        deviceConfiginfo.append(local.value(1).toUShort());
        deviceConfiginfo.append(local.value(2).toUShort());
        deviceConfiginfo.append(local.value(3).toUShort());
        deviceConfiginfo.append(deviceConfig.NetworkProperties.PortNumber);

        deviceConfiginfo.append(0);
        deviceConfiginfo.append(0);
        deviceConfiginfo.append(0);
        deviceConfiginfo.append(0);
        deviceConfiginfo.append(0);
    }
    else
    {
        for (int i = 0; i < 9; ++i)
            deviceConfiginfo.append(0);
        deviceConfiginfo.append(deviceConfig.SerialProperties.ComNumber);
        deviceConfiginfo.append(fromQtBaudRate(deviceConfig.SerialProperties.BaudRate));
        deviceConfiginfo.append(fromQtDataBits(deviceConfig.SerialProperties.DataBits));
        deviceConfiginfo.append(fromQtParity(deviceConfig.SerialProperties.ParityBits));
        deviceConfiginfo.append(fromQtStopBits(deviceConfig.SerialProperties.StopBits));
    }
    WriteHoldingRegisters(base, deviceConfiginfo);
}

void HBModbusClient::removeDeviceConfigure(const int welderId, const MODBUS_CONFIGURE deviceConfig)
{
    auto iter = m_WelderDeviceMap.find(welderId);
    int base = 0;
    if(iter != m_WelderDeviceMap.end())
    {
        base = DEV_TYPE + iter.value() * DEV_HOLDING_REGISTERS_COUNT;
        m_WelderDeviceMap.remove(iter.key());
    }
    else
    {
        return;
    }

    QVector<quint16> deviceConfiginfo;
    deviceConfiginfo.append(deviceConfig.ConnectType);
    deviceConfiginfo.append(deviceConfig.ProtocolType);
    deviceConfiginfo.append(DeviceInfoEnum::DISCONNECTED);

    if (deviceConfig.ConnectType == DeviceInfoEnum::TCP_IP)
    {
        QStringList remote = deviceConfig.NetworkProperties.RemoteIP.split(".");
        QStringList local  = deviceConfig.NetworkProperties.LocalIP.split(".");

        deviceConfiginfo.append(remote.value(0).toUShort());
        deviceConfiginfo.append(remote.value(1).toUShort());
        deviceConfiginfo.append(remote.value(2).toUShort());
        deviceConfiginfo.append(remote.value(3).toUShort());

        deviceConfiginfo.append(local.value(0).toUShort());
        deviceConfiginfo.append(local.value(1).toUShort());
        deviceConfiginfo.append(local.value(2).toUShort());
        deviceConfiginfo.append(local.value(3).toUShort());
        deviceConfiginfo.append(deviceConfig.NetworkProperties.PortNumber);

        deviceConfiginfo.append(0);
        deviceConfiginfo.append(0);
        deviceConfiginfo.append(0);
        deviceConfiginfo.append(0);
        deviceConfiginfo.append(0);
    }
    else
    {
        for (int i = 0; i < 9; ++i)
            deviceConfiginfo.append(0);
        deviceConfiginfo.append(deviceConfig.SerialProperties.ComNumber);
        deviceConfiginfo.append(fromQtBaudRate(deviceConfig.SerialProperties.BaudRate));
        deviceConfiginfo.append(fromQtDataBits(deviceConfig.SerialProperties.DataBits));
        deviceConfiginfo.append(fromQtParity(deviceConfig.SerialProperties.ParityBits));
        deviceConfiginfo.append(fromQtStopBits(deviceConfig.SerialProperties.StopBits));
    }
    WriteHoldingRegisters(base, deviceConfiginfo);
}

HBModbusClient::BaudRate HBModbusClient:: fromQtBaudRate(QSerialPort::BaudRate baud)
{
    switch (baud)
    {
    case QSerialPort::Baud2400:
        return Baud_2400;
    case QSerialPort::Baud4800:
        return Baud_4800;
    case QSerialPort::Baud9600:
        return Baud_9600;
    case QSerialPort::Baud19200:
        return Baud_19200;
    case QSerialPort::Baud38400:
        return Baud_38400;
    case QSerialPort::Baud115200:
        return Baud_115200;
    default:
        return Baud_9600;
    }
}

HBModbusClient::StopBit HBModbusClient::fromQtStopBits(QSerialPort::StopBits stop)
{
    switch (stop)
    {
    case QSerialPort::OneStop:
        return Bit1;
    case QSerialPort::OneAndHalfStop:
        return Bit1_5;
    case QSerialPort::TwoStop:
        return Bit2;
    default:
        return Bit1;
    }

}

HBModbusClient::ParityBit HBModbusClient::fromQtParity(QSerialPort::Parity parity)
{
    switch (parity)
    {
    case QSerialPort::NoParity:
        return None;
    case QSerialPort::OddParity:
        return Odd;
    case QSerialPort::EvenParity:
        return Even;
    default:
        return None;
    }

}

HBModbusClient::DataBit HBModbusClient::fromQtDataBits(QSerialPort::DataBits bit)
{
    switch (bit)
    {
    case QSerialPort::Data7:
        return Bit7;
    case QSerialPort::Data8:
        return Bit8;
    default:
        return Bit8;
    }

}

void HBModbusClient::testAllFunctions()
{
    auto doTest = [this](){

        // setLearnLedStatus(true);
        // setPilotLedStatus(true);
        // setReadyLedStatus(true);
        // setAlarmLedStatus(true);
        // qDebug() << "[Test] LED状态已设置为 true";



        // 2. 测试 IO
        for(int deviceId = 1; deviceId <= DEV_COUNT; ++deviceId)
        {
            setDeviceIOStatusReject(deviceId, true);
            setDeviceIOStatusSuspect(deviceId, true);
        }
        qDebug() << "[Test] IO状态已设置为 true";

        // 3. 测试 RTC
        QDate date(2025, 10, 28);
        QTime time(14, 30, 0);
        QDateTime datetime(date, time);
        setSystemClock(datetime);
        qDebug() << "[Test] 系统时间已设置:" << datetime.toString("yyyy-MM-dd HH:mm:ss");

        // 4. 测试 DeviceConfigure
            MODBUS_CONFIGURE device1;
            // 填写示例配置
            device1.ConnectType = DeviceInfoEnum::TCP_IP;
            device1.ProtocolType = DeviceInfoEnum::WLEDER_TYPE::L20_VG;
            device1.ConnectState = DeviceInfoEnum::CONNECT_STATE::CONNECTED;
            device1.NetworkProperties.RemoteIP = "192.168.1.55";
            device1.NetworkProperties.LocalIP  = "192.168.1.100";
            device1.NetworkProperties.PortNumber = 4200;
            setDeviceConfigure(1, device1);

            MODBUS_CONFIGURE device2;
            // 填写示例配置
            device2.ConnectType = DeviceInfoEnum::RS232;
            device2.ProtocolType = DeviceInfoEnum::WLEDER_TYPE::L20_TS;
            device2.ConnectState = DeviceInfoEnum::CONNECT_STATE::CONNECTED;
            device2.SerialProperties.ComNumber = 0;
            device2.SerialProperties.ParityBits  = QSerialPort::Parity::NoParity;
            device2.SerialProperties.BaudRate = QSerialPort::Baud9600;
            device2.SerialProperties.DataBits = QSerialPort::Data8;
            device2.SerialProperties.StopBits = QSerialPort::OneStop;
            setDeviceConfigure(2, device2);

    };

    if(modbusClient->state() == QModbusDevice::ConnectedState)
    {
        doTest();
    }
    else
    {
        qDebug() << "[Test] Modbus未连接，等待连接成功再测试";
        connect(modbusClient, &QModbusDevice::stateChanged, this, [this, doTest](int state){
            if(state == QModbusDevice::ConnectedState)
            {
                qDebug() << "[Test] Modbus已连接，开始测试所有功能";
                doTest();

            }
        });
    }
}
