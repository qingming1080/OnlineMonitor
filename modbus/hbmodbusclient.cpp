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
HBModbusClient* HBModbusClient::m_instance = nullptr;

HBModbusClient::HBModbusClient( QObject *parent)
    : QObject(parent){

    modbusClient = new QModbusTcpClient(this);
    connectToServer(QString(LOCAL_IP), SERVER_PORT);

    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, this, &HBModbusClient::onPollingTimeoutEvent);
    m_timer->start();
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
        // 读取各类寄存器数据
        pollHoldings(0, SYS_HOLDING_REGISTERS_COUNT, "Modbus系统保持寄存器读取失败:");
        pollHoldings(HOLDING_REGISTERS_ADDRESS_BASE, END_OF_DEV_HOLDING_REGISTER - HOLDING_REGISTERS_ADDRESS_BASE, "Modbus设备保持寄存器读取失败:");
        pollAllRegisters(QModbusDataUnit::InputRegisters, DEV_INPUT_REGISTERS_COUNT * DEV_COUNT, "Modbus输入寄存器读取失败:");
        pollAllRegisters(QModbusDataUnit::Coils, SYS_COILS_REGISTERS_COUNT + DEV_COILS_REGISTERS_COUNT * DEV_COUNT, "Modbus线圈读取失败:");
        pollAllRegisters(QModbusDataUnit::DiscreteInputs, DEV_DISCRETE_REGISTERS_COUNT * DEV_COUNT, "Modbus离散输入读取失败:");
    }
    else
    {
        modbusClient->connectDevice();
    }
}

void HBModbusClient::pollAllRegisters(QModbusDataUnit::RegisterType type, int count, const char* errMsg)
{
    pollRegisters(type, count,
                  [this, type](int i, quint16 value) {
                      switch(type)
                    {
                      case QModbusDataUnit::HoldingRegisters: m_Holdings[i] = value; break;
                      case QModbusDataUnit::InputRegisters: m_Inputs[i] = value; break;
                      case QModbusDataUnit::Coils: m_Coils[i] = value; break;
                      case QModbusDataUnit::DiscreteInputs: m_Discreteds[i] = value; break;
                      default: break;
                    }
                  },errMsg);
}

template<typename Setter>
void HBModbusClient::pollRegisters(QModbusDataUnit::RegisterType type, int count, Setter setter, const char* errMsg)
{
    QModbusDataUnit unit(type, 0, count);
    if (auto *reply = modbusClient->sendReadRequest(unit, 1))
    {
        connect(reply, &QModbusReply::finished, this, [this, reply, setter, errMsg,type]() {
            if (reply->error() == QModbusDevice::NoError) {
                const QModbusDataUnit u = reply->result();
                for (unsigned int i = 0; i < u.valueCount(); ++i) {
                    setter(i, u.value(i));
                }
                switch(type)
                {
                case QModbusDataUnit::InputRegisters:
                    ParseWeldResult();
                    break;
                case QModbusDataUnit::HoldingRegisters:
                    ParsePresetSetting();
                    break;
                case QModbusDataUnit::DiscreteInputs:
                    ParseDeviceStatus();
                    break;
                case QModbusDataUnit::Coils:
                    ParseResetButton();
                    ParseDeviceIOResetStatus();
                    break;
                default: break;
                }
            } else {
                qWarning() << errMsg << reply->errorString();
            }
            reply->deleteLater();
        });
    }

}

void HBModbusClient::pollHoldings(int start, int count, const char* errMsg)
{
    pollRegisters(QModbusDataUnit::HoldingRegisters, count,
                  [this, start](int i, quint16 v)
                  {
                      // QMutexLocker locker(&m_mutex);
                      m_Holdings[start + i] = v;
                  },
                  errMsg);
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
            writeUnit.setValue(i, values[i]);
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
            writeUnit.setValue(i, values[i]);

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
            WELD_RESULT data;
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
            emit notifyWeldResultComing(i, data);
        }
    }
}

void HBModbusClient::ParsePresetSetting()
{
    WELD_PRESET weldPreset;
    int base = 0;
    for (int i = 0; i < DEV_COUNT; ++i)
    {
        base = SYS_HOLDING_REGISTERS_COUNT + i * DEV_HOLDING_REGISTERS_COUNT;
        weldPreset.Energy          = m_Holdings[base + (DEV_ENERGY_SET - SYS_HOLDING_REGISTERS_COUNT)];
        weldPreset.Amplitude       = m_Holdings[base + (DEV_AMPLITUDE_SET - SYS_HOLDING_REGISTERS_COUNT)];
        weldPreset.TriggerPressure = m_Holdings[base + (DEV_TP_SET - SYS_HOLDING_REGISTERS_COUNT)];
        weldPreset.WeldingPressure = m_Holdings[base + (DEV_WP_SET - SYS_HOLDING_REGISTERS_COUNT)];
        emit notifyPresetSettingChanged(i, weldPreset);
    }
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
        emit notifyDeviceStatusChanged(i, DeviceStatus);
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
        emit notifyDeviceIOStatusChanged(i, IOStatus);
    }
}

void HBModbusClient::setSystemClock(const QDateTime &datetime)
{
    QVector<quint16> rtcValues;
    QDate date = datetime.date();
    QTime time = datetime.time();
    rtcValues.append(date.year());
    rtcValues.append(date.month());
    rtcValues.append(date.day());
    rtcValues.append(time.hour());
    rtcValues.append(time.minute());
    rtcValues.append(time.second());
    WriteHoldingRegisters(SYS_RTC_YY, rtcValues);
}

Q_INVOKABLE void HBModbusClient::setLearnLedStatus(bool condition)
{
    QVector<quint8> value(1, condition ? 1 : 0);

    WriteCoils(SYS_LED_L_BIT0, value);

}

Q_INVOKABLE void HBModbusClient::setPilotLedStatus(bool condition)
{
    QVector<quint8> value(1, condition ? 1 : 0);
    WriteCoils(SYS_LED_P_BIT1, value);

}
Q_INVOKABLE void HBModbusClient::setReadyLedStatus(bool condition)
{
    QVector<quint8> value(1, condition ? 1 : 0);
    WriteCoils(SYS_LED_R_BIT2, value);

}
Q_INVOKABLE void HBModbusClient::setAlarmLedStatus(bool condition)
{
    QVector<quint8> value(1, condition ? 1 : 0);
    WriteCoils(SYS_LED_A_BIT3, value);
}

Q_INVOKABLE void HBModbusClient::setDeviceIOStatusReject(int deviceId, bool condition) {

    if (deviceId < 1 || deviceId > DEV_COUNT) return;
    int base = SYS_COILS_REGISTERS_COUNT + (deviceId - 1) * DEV_COILS_REGISTERS_COUNT;;
    int rejectAddress = base + DEV_REJECT_BIT0 - SYS_COILS_REGISTERS_COUNT;

    QVector<quint8> value(1, condition ? 1 : 0);
    WriteCoils(rejectAddress, value);
}

Q_INVOKABLE void HBModbusClient::setDeviceIOStatusSuspect(int deviceId, bool condition) {

    if (deviceId < 1 || deviceId > DEV_COUNT) return;
    int base = SYS_COILS_REGISTERS_COUNT + (deviceId - 1) * DEV_COILS_REGISTERS_COUNT;;
    int suspectAddress = base + DEV_SUSPECT_BIT1 - SYS_COILS_REGISTERS_COUNT;

    QVector<quint8> value(1, condition ? 1 : 0);
    WriteCoils(suspectAddress, value);

}

void HBModbusClient::setMesConfig(const QVector<quint16> mesHostValues)
{
    WriteHoldingRegisters(SYS_MES_IP1, mesHostValues);
}

void HBModbusClient::setDeviceConfigure(const int deviceId, const DeviceInformation::MODBUS_CONFIGURE deviceConfig)
{
    if (deviceId < 1 || deviceId > DEV_COUNT) {
        qWarning() << "Device ID does not exist";
        return;
    }

    int base = SYS_HOLDING_REGISTERS_COUNT + (deviceId - 1) * DEV_HOLDING_REGISTERS_COUNT;
    // WriteHoldingRegisters(base + (DEV_TYPE - SYS_HOLDING_REGISTERS_COUNT), deviceValues);
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


