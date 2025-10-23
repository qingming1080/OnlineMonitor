#include "hbmodbusclient.h"
#include <QModbusDataUnit>
#include <QDateTime>
#include <QModbusTcpClient>
#include <QModbusReply>
#include <QDebug>
#include "model/deviceinformation.h"
#include "model/trend.h"
#include "DataBase/databasemanager.h"
#include "model/message.h"
#include "devicemanager.h"
#include "qmlenum.h"
#include <QtConcurrent/QtConcurrent>
#include "tools/datavalidator.h"
#include "tools/utilityfunction.h"

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

    // if (m_timer) {
    //     m_timer->stop();
    //     delete m_timer;
    // }
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

    connect(modbusClient, &QModbusTcpClient::stateChanged, this, [this](QModbusDevice::State state){
        emit connectedChanged(state == QModbusDevice::ConnectedState);
        if(state == QModbusDevice::ConnectedState) {
            updateSysLedStatus();
            // DeviceManager::getInstance()->syncDevicesToModbus();
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

void HBModbusClient::disconnect()
{
    if(modbusClient->state() == QModbusDevice::ConnectedState)
        modbusClient->disconnectDevice();
    qDebug() << "断开Modbus服务器";
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
                      processRegister(type, i, value);
                  },
                  errMsg);
}

template<typename Setter>
void HBModbusClient::pollRegisters(QModbusDataUnit::RegisterType type, int count, Setter setter, const char* errMsg)
{
    QModbusDataUnit unit(type, 0, count);
    if (auto *reply = modbusClient->sendReadRequest(unit, 1))
    {
        connect(reply, &QModbusReply::finished, this, [this, reply, setter, errMsg]() {
            if (reply->error() == QModbusDevice::NoError) {
                const QModbusDataUnit u = reply->result();
                for (unsigned int i = 0; i < u.valueCount(); ++i) {
                    setter(i, u.value(i));
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
                  [this, start](int i, quint16 v){
                      // QMutexLocker locker(&m_mutex);
                      m_Holdings[start + i] = v;
                      processRegister(QModbusDataUnit::HoldingRegisters, start + i, v);
                  },
                  errMsg);
}


template<typename T>
QVector<T> HBModbusClient::readRegisters(QModbusDataUnit::RegisterType type, int start, int count)
{
    QVector<T> result;
    switch(type)
    {
    case QModbusDataUnit::HoldingRegisters:
        for (int i = 0; i < count; ++i)
        {
            result.append(static_cast<T>(m_Holdings[start + i]));
        }
        break;
    case QModbusDataUnit::InputRegisters:
        for (int i = 0; i < count; ++i)
        {
            result.append(static_cast<T>(m_Inputs[start + i]));
        }
        break;
    case QModbusDataUnit::Coils:
        for (int i = 0; i < count; ++i)
        {
            result.append(static_cast<T>(m_Coils[start + i]));
        }
        break;
    case QModbusDataUnit::DiscreteInputs:
        for (int i = 0; i < count; ++i)
        {
            result.append(static_cast<T>(m_Discreteds[start + i]));
        }
        break;
    default:
        break;
    }
    return result;
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
    // 更新本地缓存
    for (int i = 0; i < values.size(); ++i)
    {
        m_Coils[start + i] = values[i];
        processRegister(QModbusDataUnit::Coils, start + i, values[i]);
    }

    // 检查Modbus连接状态
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

void HBModbusClient::processRegister(QModbusDataUnit::RegisterType type, int address, quint16 value)
{
    QMutexLocker locker(&m_mutex);
    switch(type) {
    case QModbusDataUnit::HoldingRegisters:
        m_Holdings[address] = value;
        break;
    case QModbusDataUnit::InputRegisters:
        if (address % DEV_INPUT_REGISTERS_COUNT == DEV_CYCLE_COUNT_H || address % DEV_INPUT_REGISTERS_COUNT == DEV_CYCLE_COUNT_L)
        { qDebug() << "11111111111";
            dispatchInputsOnCycleCountChanged();
            qDebug() << "";
        }
        break;

    case QModbusDataUnit::Coils:

        switch(address)
        {
        case SYS_BTN_R_BIT4:
            m_Coils[SYS_BTN_R_BIT4] = static_cast<unsigned char>(value);
            if (value == 1)  processSysBtnRBit4();
            qDebug() << "Coils" << "SYS_LED_L_BIT4" << value;
            break;

        }
        break;
    case QModbusDataUnit::DiscreteInputs: {
        int idx = address;
        if (idx >= 0 && idx < DEV_DISCRETE_REGISTERS_COUNT * DEV_COUNT) {
            unsigned char newVal = static_cast<unsigned char>(value);
            unsigned char prev = m_LastDiscreteds[idx];
            m_Discreteds[idx] = newVal;
            if (prev != newVal) {
                qDebug() << "DiscreteInputs index" << idx << "changed from" << prev << "to" << newVal;
                m_LastDiscreteds[idx] = newVal;
            }
        }
        break;
    }
    default:
        break;
    }

}


void HBModbusClient::dispatchInputsOnCycleCountChanged()
{
    static QVector<quint32> lastCycleCount;
    if (lastCycleCount.isEmpty())
        lastCycleCount.fill(0xFFFFFFFF, DEV_COUNT);
    const QList<Device*>& devList = DeviceManager::getInstance()->getDeviceList();
    for (int i = 0; i < DEV_COUNT && i < devList.size(); ++i)
    {
        int base = i * DEV_INPUT_REGISTERS_COUNT;

        quint16 high = m_Inputs[base + DEV_CYCLE_COUNT_H];
        quint16 low  = m_Inputs[base + DEV_CYCLE_COUNT_L];
        quint32 cycleCount = (quint32(high) << 16) | quint32(low);
        if (lastCycleCount[i] != cycleCount && cycleCount > 0)
        {
            lastCycleCount[i] = cycleCount;
            QVector<quint16> inputs = getDeviceInputs(i+1);
            QVector<quint16> holdings = getDeviceHoldings(i+1);
            if (!DataValidator::isValidForDatabase(inputs))
            {
                qDebug() << "设备" << i+1 << "输入数据异常，丢弃该条数据";
                continue;
            }
            DateTimeData data;
            data.year                   = inputs[DEV_YY];
            data.month                  = inputs[DEV_YY_MM];
            data.day                    = inputs[DEV_DD];
            data.hour                   = inputs[DEV_HH];
            data.minute                 = inputs[DEV_MM];
            data.second                 = inputs[DEV_SS];

            RECEIVE_INPUTDATA inputData;
            inputData.CycleCount       = cycleCount;
            inputData.Energy           = inputs[DEV_ENERGY];
            inputData.Amplitude        = inputs[DEV_AMPLITUDE];
            inputData.TriggerPressure  = inputs[DEV_TP];
            inputData.WeldingPressure  = inputs[DEV_WP];
            inputData.WeldTime         = inputs[DEV_TIME];
            inputData.PeakPower        = inputs[DEV_POWER];
            inputData.PreHeight        = inputs[DEV_PRE_HEIGHT];
            inputData.PostHeight       = inputs[DEV_POST_HEIGHT];
            inputData.WeldAlarm        = inputs[DEV_WELD_ALARM];
            inputData.DateData         = UtilityFunction::getInstance()->toTimestamp(data.year,data.month,data.day,data.hour,data.minute,data.second);
            // inputData.DateData         = UtilityFunction::getInstance()->toTimestamp(0,0,0,0,0,0);

            RECEIVE_HOLDINGDATA holdData;
            int holdindex = 0;
            holdData.PreEnergy           = holdings[holdindex++];
            holdData.PreAmplitude        = holdings[holdindex++];
            holdData.PreTriggerPressure  = holdings[holdindex++];
            holdData.PreWeldingPressure  = holdings[holdindex++];


            RECEIVE_COILSDATA coilData;
            coilData.Reset = m_Coils[DEV_RESET_BIT2 + i * DEV_COILS_REGISTERS_COUNT];


            RECEIVE_DISCRETE discrete;
            int discreteBase = i * DEV_DISCRETE_REGISTERS_COUNT;
            discrete.DeviceStatue      = m_Discreteds[discreteBase + DEV_STATUE];
            discrete.DeviceDataStaue   = m_Discreteds[discreteBase + DEV_DATA_STATUE];

            emit newData(i + 1, inputData, holdData, coilData, discrete);

            // bool Resetbutton = m_Coils[SYS_BTN_R_BIT4];
            // if(Resetbutton){
            //     emit resetButton(Resetbutton);
            // }


        }
    }
}

// 获取指定设备的某个输入寄存器值
quint16 HBModbusClient::getInputRegister(int devId, int regEnum) const
{   int i = 0;
    qDebug()<<"收到数据" << i;
    int index = (devId - 1) * DEV_INPUT_REGISTERS_COUNT + regEnum;
    if (index >= 0 && index < DEV_INPUT_REGISTERS_COUNT * DEV_COUNT)
        return m_Inputs[index];
    return 0;
}

// 获取指定设备的全部输入寄存器
QVector<quint16> HBModbusClient::getDeviceInputs(int devId) const
{
    int base = (devId - 1) * DEV_INPUT_REGISTERS_COUNT;
    if (base < 0 || base + DEV_INPUT_REGISTERS_COUNT > DEV_INPUT_REGISTERS_COUNT * DEV_COUNT)
        return {};
    return QVector<quint16>(m_Inputs + base, m_Inputs + base + DEV_INPUT_REGISTERS_COUNT);
}

void HBModbusClient::setRTC(int year, int month, int day, int hour, int minute, int second)
{
    // QMutexLocker locker(&m_mutex);
    QVector<quint16> rtcValues = {quint16(year), quint16(month), quint16(day), quint16(hour), quint16(minute), quint16(second)};

    writeHoldingRegisters(SYS_RTC_YY, rtcValues);
}

Q_INVOKABLE void HBModbusClient::setSysLedStatus(int ledIndex, bool condition)
{
    // ledIndex: 灯编号（0=L, 1=P, 2=R, 3=A）
    // condition: true=开, false=关


    if (ledIndex < 0 || ledIndex > 3)
    {
        qWarning() << "Invalid LED index:" << ledIndex;
        return;
    }

    int coilAddress = SYS_LED_L_BIT0 + ledIndex;

    QVector<quint8> value(1, condition ? 1 : 0);

    writeCoils(coilAddress, value);

    qDebug() << "Set LED" << ledIndex << "to" << (condition ? "ON" : "OFF");
}

Q_INVOKABLE void HBModbusClient::setDeviceCoilStatus(int devId, int value) {
    if (devId < 1 || devId > DEV_COUNT) return; // Ensure device ID is valid

    int base = calculateBaseAddress(devId);
    int rejectIdx = base + DEV_REJECT_BIT0 - SYS_COILS_REGISTERS_COUNT;
    int suspectIdx = base + DEV_SUSPECT_BIT1 - SYS_COILS_REGISTERS_COUNT;
    int resetIdx = base + DEV_RESET_BIT2 - SYS_COILS_REGISTERS_COUNT;

    QMutexLocker locker(&m_mutex);

    if (m_Coils[resetIdx] == 1)
    {
        m_Coils[rejectIdx] = 0;
        m_Coils[suspectIdx] = 0;
        writeCoils(rejectIdx, {0});
        writeCoils(suspectIdx, {0});
        qDebug() << "Device" << devId << "reset: cleared reject and suspect.";
    } else {

        if (value == 1) {
            m_Coils[rejectIdx] = 1;
            writeCoils(rejectIdx, {1});
            Message::getInstance()->addMessage(devId,QmlEnum::MESSAGE_defective);
        } else if (value == 2) {
            m_Coils[suspectIdx] = 1;
            writeCoils(suspectIdx, {1});
            Message::getInstance()->addMessage(devId,QmlEnum::MESSAGE_suspicious);
        }
    }
}

void HBModbusClient::processSysBtnRBit4() {

    qDebug() << "Processing SYS_BTN_R_BIT4...";

    // 清除所有设备的rejectIdx和suspectIdx
    for (int devId = 1; devId <= DEV_COUNT; ++devId)
    {
        clearRejectAndSuspectForDevice(devId);
    }

    for (int devId = 1; devId <= DEV_COUNT; ++devId)
    {
        int base = calculateBaseAddress(devId);
        qDebug() << "Device" << devId
                 << "Reject:" << m_Coils[base + (DEV_REJECT_BIT0 - SYS_COILS_REGISTERS_COUNT)]
                 << "Suspect:" << m_Coils[base + (DEV_SUSPECT_BIT1 - SYS_COILS_REGISTERS_COUNT)];
    }
}


int HBModbusClient::calculateBaseAddress(int devId) const {
    return SYS_COILS_REGISTERS_COUNT + (devId - 1) * DEV_COILS_REGISTERS_COUNT;
}

void HBModbusClient::clearRejectAndSuspectForDevice(int devId) {
    int base = calculateBaseAddress(devId);
    int rejectIdx = base + (DEV_REJECT_BIT0 - SYS_COILS_REGISTERS_COUNT);
    int suspectIdx = base + (DEV_SUSPECT_BIT1 - SYS_COILS_REGISTERS_COUNT);


    if (rejectIdx >= 0 && rejectIdx < sizeof(m_Coils) && suspectIdx >= 0 && suspectIdx < sizeof(m_Coils))
    {
        m_Coils[rejectIdx] = 0;
        m_Coils[suspectIdx] = 0;

        writeCoils(rejectIdx, {0});
        writeCoils(suspectIdx, {0});

        qDebug() << "Cleared reject and suspect for device" << devId
                 << "RejectIdx:" << rejectIdx
                 << "SuspectIdx:" << suspectIdx;
    } else {
        qWarning() << "Invalid coil indices for device" << devId
                   << "RejectIdx:" << rejectIdx
                   << "SuspectIdx:" << suspectIdx;
    }
}

void HBModbusClient::updateDeviceConnectionStates()
{
    const QList<Device*>& devList = DeviceManager::getInstance()->getDeviceList();
    // 每个设备占用 DEV_DISCRETE_REGISTERS_COUNT 个离散输入
    for (int i = 0; i < DEV_COUNT && i < devList.size(); ++i) {
        int base = i * DEV_DISCRETE_REGISTERS_COUNT;
        // 设备连接状态通常在 DEV_STATUE 偏移位置
        int idx = base + DEV_STATUE;
        int state = DeviceInfoEnum::DISCONNECTED;
        if (idx >= 0 && idx < DEV_DISCRETE_REGISTERS_COUNT * DEV_COUNT)
        {
            if(m_Discreteds[idx] == 1)
                state = DeviceInfoEnum::CONNECTED;
        }
        Device* dev = devList.at(i);
        if (dev && dev->getDevInfoObject())
        {
            dev->getDevInfoObject()->setConnectState(state);
            qDebug() << "Device ID:" << dev->getDevInfoObject()->id() << "state:" << state;
        }
    }
}

// 使用读取到的离散输入向量来更新缓存并更新设备状态（更通用）
void HBModbusClient::updateDeviceConnectionStates(const QVector<int>& result)
{
    // 更新本地缓存
    int max = qMin(result.size(), DEV_DISCRETE_REGISTERS_COUNT * DEV_COUNT);
    for (int i = 0; i < max; ++i)
        m_Discreteds[i] = static_cast<unsigned char>(result.at(i));

    // 调用不带参数的版本来更新设备对象
    updateDeviceConnectionStates();
}

void HBModbusClient::setDeviceConfig(int deviceId, const DeviceModbusMapper::DeviceRegisterData &data)
{
    if (deviceId <= 0) {
        qWarning() << "writeDeviceConfig: invalid deviceId" << deviceId;
        return;
    }

    int index = deviceId - 1;
    if (index < 0 || index >= DEV_COUNT) {

        qWarning() << "writeDeviceConfig: deviceId out of range" << deviceId;
        return;
    }

    int start = DEV_TYPE + index * DEV_HOLDING_REGISTERS_COUNT;

    QVector<quint16> devcieRegs = DeviceModbusMapper::toRegisterVector(data);

    writeHoldingRegisters(start, devcieRegs);
}

QVector<quint16> HBModbusClient::getDeviceHoldings(int devId) const
{
    if (devId < 1 || devId > DEV_COUNT)
        return {};

    QVector<quint16> holdings;
    holdings.reserve(12);
    int baseIndex = SYS_HOLDING_REGISTERS_COUNT + (devId - 1) * DEV_HOLDING_REGISTERS_COUNT;

    holdings.append(m_Holdings[baseIndex + (DEV_ENERGY_SET - SYS_HOLDING_REGISTERS_COUNT)]);
    holdings.append(m_Holdings[baseIndex + (DEV_AMPLITUDE_SET - SYS_HOLDING_REGISTERS_COUNT)]);
    holdings.append(m_Holdings[baseIndex + (DEV_TP_SET - SYS_HOLDING_REGISTERS_COUNT)]);
    holdings.append(m_Holdings[baseIndex + (DEV_WP_SET - SYS_HOLDING_REGISTERS_COUNT)]);
    holdings.append(m_Holdings[baseIndex + (DEV_TIME_MIN - SYS_HOLDING_REGISTERS_COUNT)]);
    holdings.append(m_Holdings[baseIndex + (DEV_TIME_MAX - SYS_HOLDING_REGISTERS_COUNT)]);
    holdings.append(m_Holdings[baseIndex + (DEV_POWER_MIN - SYS_HOLDING_REGISTERS_COUNT)]);
    holdings.append(m_Holdings[baseIndex + (DEV_POWER_MAX - SYS_HOLDING_REGISTERS_COUNT)]);
    holdings.append(m_Holdings[baseIndex + (DEV_PRE_HEIGHT_MIN - SYS_HOLDING_REGISTERS_COUNT)]);
    holdings.append(m_Holdings[baseIndex + (DEV_PRE_HEIGHT_MAX - SYS_HOLDING_REGISTERS_COUNT)]);
    holdings.append(m_Holdings[baseIndex + (DEV_POST_HEIGHT_MIN - SYS_HOLDING_REGISTERS_COUNT)]);
    holdings.append(m_Holdings[baseIndex + (DEV_POST_HEIGHT_MAX - SYS_HOLDING_REGISTERS_COUNT)]);

    return holdings;
}
