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


constexpr char HBModbusClient::LOCAL_IP[13];
constexpr int HBModbusClient::SERVER_PORT;
unsigned char HBModbusClient::m_Coils[SYS_COILS_REGISTERS_COUNT + DEV_COILS_REGISTERS_COUNT * DEV_COUNT] = {0};
unsigned char HBModbusClient::m_Discreteds[DEV_DISCRETE_REGISTERS_COUNT * DEV_COUNT] = {0};
unsigned short HBModbusClient::m_Holdings[SYS_HOLDING_REGISTERS_COUNT + DEV_HOLDING_REGISTERS_COUNT * DEV_COUNT] = {0};
unsigned short HBModbusClient::m_Inputs[DEV_INPUT_REGISTERS_COUNT * DEV_COUNT] = {0};
HBModbusClient* HBModbusClient::m_instance = nullptr;

HBModbusClient::HBModbusClient( QObject *parent)
    : QObject(parent)
{
    modbusClient = new QModbusTcpClient(this);

    connectToServer(QString(LOCAL_IP), SERVER_PORT);

    Init();

}

HBModbusClient *HBModbusClient::GetInstance()
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

    if (m_timer) {
        m_timer->stop();
        delete m_timer;
    }
}

void HBModbusClient::Init()
{
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, this, &HBModbusClient::onPollTimeout);

    m_reconnectTimer = new QTimer(this);
    m_reconnectTimer->setInterval(2000);
    m_reconnectTimer->setSingleShot(false);
    connect(m_reconnectTimer, &QTimer::timeout, this, [this]() {
        if (modbusClient->state() != QModbusDevice::ConnectedState) {
            qDebug() << "自动重连Modbus服务器...";
            modbusClient->connectDevice();
        } else {
            m_reconnectTimer->stop();
        }
    });
    connect(modbusClient, &QModbusTcpClient::stateChanged, this, [this](QModbusDevice::State state){
        if(state == QModbusDevice::ConnectedState) {
            qDebug() << "Modbus已连接";
            emit connectedChanged(true);
            m_timer->start();
            if (m_reconnectTimer->isActive()) m_reconnectTimer->stop();
        } else if(state == QModbusDevice::UnconnectedState) {
            qDebug() << "Modbus已断开";
            emit connectedChanged(false);
            m_timer->stop();
            if (!m_reconnectTimer->isActive()) m_reconnectTimer->start();
        }
    });
    connect(modbusClient, &QModbusTcpClient::errorOccurred, this, [this](QModbusDevice::Error err){
        if(err != QModbusDevice::NoError)
            qWarning() << "Modbus错误:" << modbusClient->errorString();
    });

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
    QThread::msleep(200);
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
                      switch(type) {
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
    if (auto *reply = modbusClient->sendReadRequest(unit, 1)) {
        connect(reply, &QModbusReply::finished, this, [this, reply, setter, errMsg]() {
            if (reply->error() == QModbusDevice::NoError) {
                const QModbusDataUnit u = reply->result();
                for (int i = 0; i < u.valueCount(); ++i) {
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
    switch(type) {
    case QModbusDataUnit::HoldingRegisters:
        for (int i = 0; i < count; ++i) {
            result.append(static_cast<T>(m_Holdings[start + i]));
        }
        break;
    case QModbusDataUnit::InputRegisters:
        for (int i = 0; i < count; ++i) {
            result.append(static_cast<T>(m_Inputs[start + i]));
        }
        break;
    case QModbusDataUnit::Coils:
        for (int i = 0; i < count; ++i) {
            result.append(static_cast<T>(m_Coils[start + i]));
        }
        break;
    case QModbusDataUnit::DiscreteInputs:
        for (int i = 0; i < count; ++i) {
            result.append(static_cast<T>(m_Discreteds[start + i]));
        }
        break;
    default:
        break;
    if (m_reconnectTimer) {
          m_reconnectTimer->stop();
          delete m_reconnectTimer;
        }
    }
    return result;
}


void HBModbusClient::writeHoldingRegisters(int start, const QVector<quint16>& values)
{
    // QMutexLocker locker(&m_mutex);
    for (int i = 0; i < values.size(); ++i) {
        m_Holdings[start + i] = values[i];
    }
    if (modbusClient->state() == QModbusDevice::ConnectedState) {
        QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, start, values.size());
        for (int i = 0; i < values.size(); ++i)
            writeUnit.setValue(i, values[i]);
        if (auto *reply = modbusClient->sendWriteRequest(writeUnit, 1)) {
            connect(reply, &QModbusReply::finished, this, [reply]() {
                reply->deleteLater();
            });
        }
    } else {
        qWarning() << "Modbus未连接，写保持寄存器失败";
    }
}

void HBModbusClient::writeCoils(int start, const QVector<quint8>& values)
{
    // QMutexLocker locker(&m_mutex);
    for (int i = 0; i < values.size(); ++i) {
        m_Coils[start + i] = values[i];
        processRegister(QModbusDataUnit::Coils, start + i, values[i]);
    }
    if (modbusClient->state() == QModbusDevice::ConnectedState) {
        QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, start, values.size());
        for (int i = 0; i < values.size(); ++i)
            writeUnit.setValue(i, values[i]);
        if (auto *reply = modbusClient->sendWriteRequest(writeUnit, 1)) {
            connect(reply, &QModbusReply::finished, this, [reply]() {
                reply->deleteLater();
            });
        }
    } else {
        qWarning() << "Modbus未连接，写保持寄存器失败";
    }
}

void HBModbusClient::processRegister(QModbusDataUnit::RegisterType type, int address, quint16 value)
{
    switch(type) {
    case QModbusDataUnit::HoldingRegisters:
        // 处理保持寄存器
        switch(address) {
        case SYS_RTC_YY:
            // 处理年
            qDebug()<< "SYS_RTC_YY" << value;
            break;
        case SYS_RTC_YY_MM:
            // 处理月
            qDebug()<< "SYS_RTC_YY_MM" << value;
            break;
        // ... 其他case ...
        default:
            break;
        }
        break;
    case QModbusDataUnit::InputRegisters:

        if (address % DEV_INPUT_REGISTERS_COUNT == DEV_CYCLE_COUNT_H || address % DEV_INPUT_REGISTERS_COUNT == DEV_CYCLE_COUNT_L) {
            dispatchInputsOnCycleCountChanged();
        }
        break;
    case QModbusDataUnit::Coils:
        // 处理线圈
        switch(address) {
        case SYS_LED_L_BIT0:
            // 处理LED
             qDebug()<< "Coils" <<"SYS_LED_L_BIT0" << value;
            break;
        // ... 其他case ...
        default:
            break;
        }
        break;
    case QModbusDataUnit::DiscreteInputs:
        // 处理离散输入
        switch(address) {
        case DEV_STATUE:
            // 处理状态
              qDebug()<< "DiscreteInputs" <<"DEV_STATUE" << value;
            break;
        // ... 其他case ...
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void HBModbusClient::dispatchInputsOnCycleCountChanged()
{
    static QVector<quint32> lastCycleCount(DEV_COUNT, 0xFFFFFFFF);
    const QList<Device*>& devList = DeviceManager::getInstance()->deviceList();
    for (int i = 0; i < DEV_COUNT && i < devList.size(); ++i) {
        int base = i * DEV_INPUT_REGISTERS_COUNT;
        quint16 high = m_Inputs[base + DEV_CYCLE_COUNT_H];
        quint16 low  = m_Inputs[base + DEV_CYCLE_COUNT_L];
        quint32 cycleCount = (quint32(high) << 16) | quint32(low);
        if (lastCycleCount[i] != cycleCount) {
            lastCycleCount[i] = cycleCount;
            QVector<quint16> inputs = getDeviceInputs(i+1);
            Device* dev = (i < devList.size()) ? devList.at(i) : nullptr;
            if (dev && dev->pDeviceInformation() && inputs.size() >= DEV_INPUT_REGISTERS_COUNT) {
                // dev->pDeviceInformation()->setCycleCount(cycleCount);
                dev->pDeviceInformation()->setPower(inputs[DEV_POWER]);
                dev->pDeviceInformation()->setTime(inputs[DEV_TIME]);
                dev->pDeviceInformation()->setEnergy(inputs[DEV_ENERGY]);
                dev->pDeviceInformation()->setHeightPre(inputs[DEV_PRE_HEIGHT]);
                dev->pDeviceInformation()->setHeightPost(inputs[DEV_POST_HEIGHT]);

                updateDeviceTrend(dev, inputs[DEV_POWER], inputs[DEV_TIME], inputs[DEV_PRE_HEIGHT], inputs[DEV_POST_HEIGHT]);

            }
            // 假设DataBaseManager有insertDeviceInputs接口
            // DataBaseManager::getInstance()->insertDeviceInputs(i+1, inputs);
             //TODO
            //DataBaseManager::getInstance()->insertProductionRow(data);
        }
    }
}

void HBModbusClient::updateDeviceTrend(Device* dev, quint16 power, quint16 time, quint16 preHeight, quint16 postHeight)
{
    if (!dev || !dev->pTrend())
        return;

    dev->pTrend()->appendWeldPoint(power, time, preHeight, postHeight);
}


// 获取指定设备的某个输入寄存器值
quint16 HBModbusClient::getInputRegister(int devId, int regEnum) const
{
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
