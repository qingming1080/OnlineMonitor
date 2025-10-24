#include "hbmodbusclient.h"
#include <QModbusDataUnit>
#include <QDateTime>
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
HBModbusClient* HBModbusClient::m_instance = nullptr;

HBModbusClient::HBModbusClient( QObject *parent)
    : QObject(parent){

    modbusClient = new QModbusTcpClient(this);

    connectToServer(QString(LOCAL_IP), SERVER_PORT);

    Init();
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

void HBModbusClient::Init()
{
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, this, [this]() {
        if (modbusClient->state() == QModbusDevice::ConnectedState) {
            onPollTimeout();
        } else {
            modbusClient->connectDevice();
        }
    });

    m_timer->start();
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

void HBModbusClient::onPollTimeout()
{
    if(modbusClient->state() != QModbusDevice::ConnectedState)
        return;

    // 读取各类寄存器数据
    pollHoldings(0, SYS_HOLDING_REGISTERS_COUNT, "Modbus系统保持寄存器读取失败:");
    pollHoldings(HOLDING_REGISTERS_ADDRESS_BASE, END_OF_DEV_HOLDING_REGISTER - HOLDING_REGISTERS_ADDRESS_BASE, "Modbus设备保持寄存器读取失败:");
    pollAllRegisters(QModbusDataUnit::InputRegisters, DEV_INPUT_REGISTERS_COUNT * DEV_COUNT, "Modbus输入寄存器读取失败:");
    pollAllRegisters(QModbusDataUnit::Coils, SYS_COILS_REGISTERS_COUNT + DEV_COILS_REGISTERS_COUNT * DEV_COUNT, "Modbus线圈读取失败:");
    pollAllRegisters(QModbusDataUnit::DiscreteInputs, DEV_DISCRETE_REGISTERS_COUNT * DEV_COUNT, "Modbus离散输入读取失败:");
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
                    dispatchInputsOnCycleCountChanged();
                    break;
                case QModbusDataUnit::HoldingRegisters:
                    dispatchDevicePresetData();
                    break;
                case QModbusDataUnit::DiscreteInputs:
                    dispatchDeviceStatus();
                    break;
                case QModbusDataUnit::Coils:
                    dispatchResetButton();
                    dispatchDeviceIOResetStatus();
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

void HBModbusClient::writeHoldingRegisters(int start, const QVector<quint16>& values)
{
    // QMutexLocker locker(&m_mutex);
    for (int i = 0; i < values.size(); ++i)
    {
        m_Holdings[start + i] = values[i];
    }

    if (modbusClient->state() == QModbusDevice::ConnectedState)
    {
        QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, start, values.size());
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

void HBModbusClient::writeCoils(int start, const QVector<quint8>& values)
{
    for (int i = 0; i < values.size(); ++i)
    {
        m_Coils[start + i] = values[i];
    }
    if (modbusClient->state() == QModbusDevice::ConnectedState)
    {
        QModbusDataUnit writeUnit(QModbusDataUnit::Coils, start, values.size());
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

void HBModbusClient::dispatchInputsOnCycleCountChanged()
{
    static QVector<quint32> lastCycleCount;

    if (lastCycleCount.size() != DEV_COUNT)
        lastCycleCount.fill(0, DEV_COUNT);
    for (int i = 0; i < DEV_COUNT ; ++i)
    {
        int base = i * DEV_INPUT_REGISTERS_COUNT;

        quint16 high = m_Inputs[base + DEV_CYCLE_COUNT_H];
        quint16 low  = m_Inputs[base + DEV_CYCLE_COUNT_L];
        quint32 cycleCount = (quint32(high) << 16) | quint32(low);
        if (lastCycleCount[i] != cycleCount && cycleCount > 0)
        {

            lastCycleCount[i] = cycleCount;
            WELD_RESULTDATA data;
            data.CycleCount      = cycleCount;
            data.Energy          = m_Inputs[base + DEV_ENERGY];
            data.Amplitude       = m_Inputs[base + DEV_AMPLITUDE];
            data.TriggerPressure = m_Inputs[base + DEV_TP];
            data.WeldingPressure = m_Inputs[base + DEV_WP];
            data.WeldTime        = m_Inputs[base + DEV_TIME];
            data.PeakPower       = m_Inputs[base + DEV_POWER];
            data.PreHeight       = m_Inputs[base + DEV_PRE_HEIGHT];
            data.PostHeight      = m_Inputs[base + DEV_POST_HEIGHT];
            data.WeldAlarm       = m_Inputs[base + DEV_WELD_ALARM];

            int year   = m_Inputs[base + DEV_YY];
            int month  = m_Inputs[base + DEV_YY_MM];
            int day    = m_Inputs[base + DEV_DD];
            int hour   = m_Inputs[base + DEV_HH];
            int minute = m_Inputs[base + DEV_MM];
            int second = m_Inputs[base + DEV_SS];

            data.DateData = UtilityFunction::getInstance()->toTimestamp(year, month, day, hour, minute, second);

            emit weldResultDataChanged(i + 1, data);
        }
    }
}

void HBModbusClient::dispatchDevicePresetData()
{
    for (int i = 0; i < DEV_COUNT; ++i)
    {
        int base = SYS_HOLDING_REGISTERS_COUNT + i * DEV_HOLDING_REGISTERS_COUNT;

        WELD_PRESETDATA weldPreset;
        weldPreset.EnergyPreset          = m_Holdings[base + (DEV_ENERGY_SET - SYS_HOLDING_REGISTERS_COUNT)];
        weldPreset.AmplitudePreset       = m_Holdings[base + (DEV_AMPLITUDE_SET - SYS_HOLDING_REGISTERS_COUNT)];
        weldPreset.TriggerPressurePreset = m_Holdings[base + (DEV_TP_SET - SYS_HOLDING_REGISTERS_COUNT)];
        weldPreset.WeldingPressurePreset = m_Holdings[base + (DEV_WP_SET - SYS_HOLDING_REGISTERS_COUNT)];
        emit presetDataChanged(i + 1, weldPreset);
    }
}

void HBModbusClient::dispatchDeviceStatus()
{
    for (int i = 0; i < DEV_COUNT; ++i)
    {
        int base = i * DEV_DISCRETE_REGISTERS_COUNT;
        WELD_STATUS weldStatus;
        weldStatus.isDeviceStatue        = m_Discreteds[base + DEV_STATUE];
        weldStatus.isDeviceDataStaue     = m_Discreteds[base + DEV_DATA_STATUE];
        emit deviceStatusChanged(i + 1, weldStatus);
    }
}

void HBModbusClient::dispatchResetButton()
{
    WELD_IORESTSTATUS resetButtonStatus;
    resetButtonStatus.isIOReset = m_Coils[SYS_BTN_R_BIT4];
    emit resetButtonChanged(resetButtonStatus);
}

void HBModbusClient::dispatchDeviceIOResetStatus()
{
    for (int i = 0; i < DEV_COUNT; ++i)
    {
        int base = SYS_COILS_REGISTERS_COUNT + i * DEV_COILS_REGISTERS_COUNT;
        WELD_IORESTSTATUS weldIoResetStatus;
        weldIoResetStatus.isIOReset = m_Coils[base + DEV_RESET_BIT2 - SYS_COILS_REGISTERS_COUNT];
        emit deviceIOResetChanged(i + 1, weldIoResetStatus);
    }
}

void HBModbusClient::setSystemClock(int year, int month, int day, int hour, int minute, int second)
{
    QVector<quint16> rtcValues = {quint16(year), quint16(month), quint16(day), quint16(hour), quint16(minute), quint16(second)};

    writeHoldingRegisters(SYS_RTC_YY, rtcValues);
}

Q_INVOKABLE void HBModbusClient::setLearnLedStatus(bool condition)
{
    QVector<quint8> value(1, condition ? 1 : 0);

    writeCoils(SYS_LED_L_BIT0, value);

}

Q_INVOKABLE void HBModbusClient::setPilotLedStatus(bool condition)
{
    QVector<quint8> value(1, condition ? 1 : 0);
    writeCoils(SYS_LED_P_BIT1, value);

}
Q_INVOKABLE void HBModbusClient::setReadyLedStatus(bool condition)
{
    QVector<quint8> value(1, condition ? 1 : 0);
    writeCoils(SYS_LED_R_BIT2, value);

}
Q_INVOKABLE void HBModbusClient::setAlarmLedStatus(bool condition)
{
    QVector<quint8> value(1, condition ? 1 : 0);
    writeCoils(SYS_LED_A_BIT3, value);
}

Q_INVOKABLE void HBModbusClient::setDeviceIOStatusReject(int deviceId, bool condition) {

    if (deviceId < 1 || deviceId > DEV_COUNT) return;
    int base = SYS_COILS_REGISTERS_COUNT + (deviceId - 1) * DEV_COILS_REGISTERS_COUNT;;
    int rejectAddress = base + DEV_REJECT_BIT0 - SYS_COILS_REGISTERS_COUNT;

    QVector<quint8> value(1, condition ? 1 : 0);
    writeCoils(rejectAddress, value);
}

Q_INVOKABLE void HBModbusClient::setDeviceIOStatusSuspect(int deviceId, bool condition) {

    if (deviceId < 1 || deviceId > DEV_COUNT) return;
    int base = SYS_COILS_REGISTERS_COUNT + (deviceId - 1) * DEV_COILS_REGISTERS_COUNT;;
    int suspectAddress = base + DEV_SUSPECT_BIT1 - SYS_COILS_REGISTERS_COUNT;

    QVector<quint8> value(1, condition ? 1 : 0);
    writeCoils(suspectAddress, value);

}

void HBModbusClient::setMesConfig(const QVector<quint16> mesHostValues)
{
    writeHoldingRegisters(SYS_MES_IP1, mesHostValues);
}

void HBModbusClient::setDeviceConfigData(int deviceId, const QVector<quint16> deviceValues)
{
    if (deviceId < 1 || deviceId > DEV_COUNT) {
        qWarning() << "Device ID does not exist";
        return;
    }

    int base = SYS_HOLDING_REGISTERS_COUNT + (deviceId - 1) * DEV_HOLDING_REGISTERS_COUNT;
    writeHoldingRegisters(base + (DEV_TYPE - SYS_HOLDING_REGISTERS_COUNT), deviceValues);
}
