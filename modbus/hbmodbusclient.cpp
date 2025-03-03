#include "hbmodbusclient.h"
#include <QModbusDataUnit>
#include <QDateTime>
#include <QModbusTcpClient>
#include <QModbusReply>
#include <QDebug>
#include <deque>
#include "model/deviceinformation.h"
#include "model/trend.h"
#include "DataBase/databasemanager.h"
#include "define.h"
#include "model/message.h"
#include "qmlenum.h"

constexpr char HBModbusClient::LOCAL_IP[13];
constexpr int HBModbusClient::SERVER_PORT;
unsigned char HBModbusClient::m_Coils[SYS_COILS_REGISTERS_COUNT + DEV_COILS_REGISTERS_COUNT * DEV_COUNT] = {0};
unsigned char HBModbusClient::m_Discreteds[DEV_DISCRETE_REGISTERS_COUNT * DEV_COUNT] = {0};
unsigned short HBModbusClient::m_Holdings[SYS_HOLDING_REGISTERS_COUNT + DEV_HOLDING_REGISTERS_COUNT * DEV_COUNT] = {0};
unsigned short HBModbusClient::m_Inputs[DEV_INPUT_REGISTERS_COUNT * DEV_COUNT] = {0};


HBModbusClient::HBModbusClient(DeviceManager *deviceManager, QObject *parent)
    : QObject(parent),
    modbusClient(new QModbusTcpClient(this)),
    readTimer(new QTimer(this)),
    writeTimer(new QTimer(this)),
    reconnectTimer(new QTimer(this)),
    m_deviceManager(deviceManager)
{

    connect(readTimer, &QTimer::timeout, this, &HBModbusClient::readModbusData);

    //connect(writeTimer, &QTimer::timeout, this, &HBModbusClient::writeModbusData);


    // connect(readTimer, &QTimer::timeout, this, &HBModbusClient::updateTrendData);


    connect(reconnectTimer, &QTimer::timeout, this, &HBModbusClient::attemptReconnect);

    connect(modbusClient, &QModbusTcpClient::errorOccurred, this, &HBModbusClient::onModbusError);

    connect(m_deviceManager, &DeviceManager::deviceListChanged, this, &HBModbusClient::onDeviceNumChanged);

    // 连接到服务器
    connectToServer(QString(LOCAL_IP), SERVER_PORT);


     // 启动定时器
    startReading(1000);
    writeTimer->start(2000);
}

void HBModbusClient::startReading(int interval)
{
    readTimer->start(interval);
}


HBModbusClient::~HBModbusClient()
{
    if (modbusClient->state() == QModbusDevice::ConnectedState) {
        modbusClient->disconnectDevice();
    }

    delete modbusClient;
    delete readTimer;
    delete writeTimer;
    delete reconnectTimer;
    delete m_deviceManager;

}


bool HBModbusClient::connectToServer(const QString &host, int port)
{
    modbusClient->setConnectionParameter(QModbusTcpClient::NetworkAddressParameter, host);
    modbusClient->setConnectionParameter(QModbusTcpClient::NetworkPortParameter, port);

    return modbusClient->connectDevice();
}

void HBModbusClient::onModbusError(QModbusTcpClient::Error error)
{
    qDebug() << "Modbus error occurred:" << error;

    // 如果连接错误，则启动重连定时器
    if (error == QModbusDevice::ConnectionError) {
        qDebug() << "Modbus connection lost. Trying to reconnect...";
        reconnectTimer->start();  // 启动重连定时器
    }
}

void HBModbusClient::attemptReconnect()
{
    // 如果已经连接，则不需要重连
    if (modbusClient->state() == QModbusDevice::ConnectedState) {
        reconnectTimer->stop();
        qDebug() << "Reconnected to Modbus server!";
        return;
    }

    // 尝试重新连接
    qDebug() << "Attempting to reconnect to Modbus server...";
    if (connectToServer(QString(LOCAL_IP), SERVER_PORT)) {
        reconnectTimer->stop();
        qDebug() << "Reconnected to Modbus server!";
    } else {
        qDebug() << "Reconnect failed, will try again.";
    }
}



void HBModbusClient::readModbusData()
{

    // readModbusRegisters(QModbusDataUnit::Coils, 0, SYS_COILS_REGISTERS_COUNT + DEV_COILS_REGISTERS_COUNT * DEV_COUNT, &HBModbusClient::CoilsReadyRead);


    //readDiscreteInputs(DEV_STATUE, DEV_DISCRETE_REGISTERS_COUNT * DEV_COUNT, &HBModbusClient::DiscretedsReadyRead);


    // readModbusRegisters(QModbusDataUnit::HoldingRegisters, 0, SYS_HOLDING_REGISTERS_COUNT + DEV_HOLDING_REGISTERS_COUNT * DEV_COUNT, &HBModbusClient::HoldingsReadyRead);
    checkAlarmIsAllZero();

    resetButton();

    checkAndResetCoils();

    readDiscreteInputs(DEV_STATUE,DEV_DISCRETE_REGISTERS_COUNT * DEV_COUNT,&HBModbusClient::DiscretedsReadyRead);

    readModbusRegisters(QModbusDataUnit::InputRegisters, 0, DEV_INPUT_REGISTERS_COUNT * DEV_COUNT, &HBModbusClient::InputsReadyRead);
}

void HBModbusClient::readModbusRegisters(QModbusDataUnit::RegisterType registerType, int startAddress, int registerCount, void (HBModbusClient::*finishedSignal)())
{
    QModbusDataUnit dataUnit(registerType, startAddress, registerCount);

    QModbusReply *reply = modbusClient->sendReadRequest(dataUnit, 1);

    if (reply) {
        connect(reply, &QModbusReply::finished, this, finishedSignal);
    } else {
        qDebug() << "Failed to read data from Modbus server.";
    }
}

void HBModbusClient::readDiscreteInputs(int startAddress, int inputCount, void (HBModbusClient::*finishedSignal)())
{

      qDebug("11111111111111111");
    QModbusDataUnit dataUnit(QModbusDataUnit::DiscreteInputs, startAddress, inputCount);

    QModbusReply *reply = modbusClient->sendReadRequest(dataUnit, 1);

    if (reply) {
        connect(reply, &QModbusReply::finished, this, finishedSignal);
    } else {
        qDebug() << "Failed to read data from Modbus server.";
    }
}



void HBModbusClient::DiscretedsReadyRead() {
    QModbusReply *reply = qobject_cast<QModbusReply *>(sender());

    if (reply) {
        if (reply->error() != QModbusDevice::NoError) {
            // 如果出现错误（如断开连接），将所有设备的状态设置为 "未连接"
            qDebug() << "Modbus 错误:" << reply->errorString();

            // 遍历所有设备，设置状态为 "未连接"
            for (Device *device : m_deviceManager->deviceList()) {
                device->pDeviceInformation()->setState("未连接");
                qDebug() << "设备 ID:" << device->pDeviceInformation()->id() << "状态: 未连接";
            }
        } else {
            // 没有错误，正常处理结果
            QModbusDataUnit unit = reply->result();
            QVector<int> result;
            for (int i = 0; i < unit.valueCount(); ++i) {
                result.append(unit.value(i));
                qDebug() << "i:" << i << " result.append(unit.value(i)):" << result[i];
            }

            emit dataReceived(result);

            // 根据读取到的结果更新设备状态
            for (Device *device : m_deviceManager->deviceList()) {
                int deviceId = device->pDeviceInformation()->id();
                int stateIndex = (deviceId - 1) * 5;

                if (stateIndex >= 0 && stateIndex + 4 < result.size()) {
                    QString deviceState = (result[stateIndex] == 1) ? "已连接" : "未连接";
                    qDebug() << "设备 ID:" << deviceId << "状态索引:" << stateIndex << "状态:" << deviceState;

                    device->pDeviceInformation()->setState(deviceState);
                }
            }
        }

        reply->deleteLater();
    }
}

void HBModbusClient::CoilsReadyRead()
{
    QModbusReply *reply = qobject_cast<QModbusReply *>(sender());
    if (reply) {
        if (reply->error() != QModbusDevice::NoError) {
            qDebug() << "Modbus error:" << reply->errorString()
                     << "Error code:" << reply->error();
        } else {
            QModbusDataUnit unit = reply->result();


            int coilValue = unit.value(0);

            int address = reply->property("address").toInt();

            if (coilValue == 1) {
                if (address == 13) {
                    resetCoilsAtAddresses({11, 12});
                } else if (address == 18) {
                    resetCoilsAtAddresses({16, 17});
                } else if (address == 23) {
                    resetCoilsAtAddresses({21, 22});
                } else if (address == 28) {
                    resetCoilsAtAddresses({26, 27});
                }else if (address == 4) {
                    setLED(true);
                    resetCoilsToZero();
                }
            }
        }

        reply->deleteLater();
    }
}


void HBModbusClient::HoldingsReadyRead()
{
    QModbusReply *reply = qobject_cast<QModbusReply *>(sender());
    if (reply) {
        if (reply->error() != QModbusDevice::NoError) {
            qDebug() << "Modbus error:" << reply->errorString();
        } else {
            // 读取结果
            QModbusDataUnit unit = reply->result();
            QVector<int> result;
            for (int i = 0; i < unit.valueCount(); ++i) {
                result.append(unit.value(i));
            }

            // 发射信号，通知设备管理器更新设备数据
            emit dataReceived(result);

            // 遍历设备列表，根据设备 ID 更新数据

            for (Device *device : m_deviceManager->deviceList()) {

                int deviceId = device->pDeviceInformation()->id();

                // 根据设备 ID 更新对应设备的能量值
                if (deviceId == 1 && result.size() > 0) {
                   device->pDeviceInformation()->setEnergy(result[0]);
                } else if (deviceId == 2 && result.size() > 1) {
                   device->pDeviceInformation()->setEnergy(result[1]);
                } else if (deviceId == 3 && result.size() > 2) {
                   device->pDeviceInformation()->setEnergy(result[2]);
                } else if (deviceId == 4 && result.size() > 3) {
                   device->pDeviceInformation()->setEnergy(result[3]);
                }
            }
        }

        reply->deleteLater();
    }

}


void HBModbusClient::InputsReadyRead()
{
    QModbusReply *reply = qobject_cast<QModbusReply *>(sender());
    if (!reply) {
        return;
    }

    if (reply->error() != QModbusDevice::NoError) {
        qDebug() << "Modbus error:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QModbusDataUnit unit = reply->result();
    QVector<int> result;
    for (int i = 0; i < unit.valueCount(); ++i) {
        result.append(unit.value(i));
    }

    emit dataReceived(result);

    // 遍历所有设备，根据设备ID选择相应的偏移量
    for (Device *device : m_deviceManager->deviceList()) {
        int deviceId = device->pDeviceInformation()->id();
        if (result.isEmpty()) continue;  // 如果数据为空，跳过该设备

        int offset = 0;
        switch (deviceId) {
        case 1: offset = 0; break;
        case 2: offset = 30; break;
        case 3: offset = 60; break;
        case 4: offset = 90; break;
        default:
            qDebug() << "Unknown device ID:" << deviceId;
            continue;
        }

        if (result.size() > offset + 15) {  // 检查数据是否足够
            processDeviceData(device, result, offset);
        }
    }

    reply->deleteLater();
}


void HBModbusClient::processDeviceData(Device *device, const QVector<int> &result, int offset)
{
    if (result.size() <= offset + 16) return;  // 数据长度检查

    int DEV_CYCLE_COUNT = (static_cast<int>(result[offset]) << 16) | result[offset + 1];
    int DEV_ENERGY = result[offset + 2];
    int DEV_AMPLITUDE = result[offset + 3];
    int DEV_TP = result[offset + 4];
    int DEV_WP = result[offset + 5];
    int DEV_TIME = result[offset + 6];
    int DEV_POWER = result[offset + 7];
    int DEV_PRE_HEIGHT = result[offset + 8];
    int DEV_POST_HEIGHT = result[offset + 9];
    int DEV_WELD_ALARM = result[offset + 10];
    int DEV_YY = result[offset + 11];
    int DEV_YY_MM = result[offset + 12];
    int DEV_DD = result[offset + 13];
    int DEV_HH = result[offset + 14];
    int DEV_MM = result[offset + 15];
    int DEV_SS = result[offset + 16];

    // 获取设备 ID
    int deviceId = device->pDeviceInformation()->id();

    setIO(deviceId,DEV_WELD_ALARM);

    // 初始化设备的 LAST_CYCLE_COUNT，如果不存在
    if (!m_lastCycleCounts.contains(deviceId)) {
        m_lastCycleCounts[deviceId] = -1;  // 初始化为 -1，表示没有记录
    }

    // 检查当前设备的 DEV_CYCLE_COUNT 是否发生变化
    if (DEV_CYCLE_COUNT == m_lastCycleCounts[deviceId]) {
        return;
    }

    // 更新 LAST_CYCLE_COUNT
    m_lastCycleCounts[deviceId] = DEV_CYCLE_COUNT;

    device->pDeviceInformation()->setEnergy(DEV_ENERGY);
    device->pDeviceInformation()->setTime(DEV_TIME);
    device->pDeviceInformation()->setPower(DEV_POWER);
    device->pDeviceInformation()->setHeightPre(DEV_PRE_HEIGHT);
    device->pDeviceInformation()->setHeightPost(DEV_POST_HEIGHT);


    updateTrendData(device, DEV_PRE_HEIGHT, DEV_POST_HEIGHT, DEV_TIME, DEV_POWER);

    QDateTime dateTime(QDate(DEV_YY, DEV_YY_MM, DEV_DD),QTime(DEV_HH, DEV_MM, DEV_SS));

    _Production_Data data;

    data.welder_id = deviceId;
    data.model_id = 1;
    data.create_time = dateTime.toString("yyyy-MM-dd HH:mm:ss");
    //data.serial_number = DEV_CYCLE_COUNT;
    data.cycle_count = DEV_CYCLE_COUNT;
    //data.batch_count = DEV_CYCLE_COUNT;
    data.energy = DEV_ENERGY;
    data.amplitude = DEV_AMPLITUDE;
    data.pressure = DEV_WP;
    data.time = QString::number(DEV_TIME / 100.0, 'f', 2); ;
    data.power = DEV_POWER;
    data.pre_height = static_cast<double>(DEV_PRE_HEIGHT) / 100.0;
    data.post_height = static_cast<double>(DEV_POST_HEIGHT) / 100.0;
    data.force = 200;
    data.residual = 0;
    data.good_rate = 100;
    data.good_subtotal_cycles = 80;
    data.suspect_subtotal_cycles = 10;
    data.not_definite_cycles = 10;
    data.final_result = DEV_WELD_ALARM;

    DataBaseManager::getInstance()->insertProductionRow(data);
}


void HBModbusClient::updateTrendData(Device *device, int preHeight, int postHeight, int time, int power)
{
    static const int AxisMAX = 150;
    static const int PowerBufferSize = 10;

    int plotIndex = device->getPlotIndex();

    double preHeightDouble = preHeight / 100.0;
    double postHeightDouble = postHeight / 100.0;
    double timeDouble = time / 100.0;

    // 获取当前功率的最大值和最小值（加缓冲区）
    static std::deque<int> powerBuffer;
    powerBuffer.push_back(power);

    // 保证缓冲区的大小不超过设置的最大值
    if (powerBuffer.size() > PowerBufferSize) {
        powerBuffer.pop_front();
    }

    // 计算功率的最大值和最小值，动态调整 Power Y 轴范围
    int maxPower = *std::max_element(powerBuffer.begin(), powerBuffer.end()) + 250;
    int minPower = *std::min_element(powerBuffer.begin(), powerBuffer.end()) - 200;

    int AxisMIN = (plotIndex >= AxisMAX) ? plotIndex - AxisMAX : 0;
    int AxisMaxActual = (plotIndex >= AxisMAX) ? plotIndex : AxisMAX;


    device->pTrend()->setIdMaxX(AxisMaxActual);
    device->pTrend()->setIdMinX(AxisMIN);

    device->pTrend()->setBeforeMaxY(2);
    device->pTrend()->setBeforeMinY(0);
    device->pTrend()->setAfterMaxY(2);
    device->pTrend()->setAfterMinY(0);
    device->pTrend()->setTimeMaxY(2);
    device->pTrend()->setTimeMinY(0);
    device->pTrend()->setPowerMaxY(maxPower);
    device->pTrend()->setPowerMinY(minPower);

    QPointF pos;
    pos.setX(plotIndex);
    pos.setY(preHeightDouble);
    device->pTrend()->m_frontData.push_back(pos);

    pos.setY(postHeightDouble);
    device->pTrend()->m_backData.push_back(pos);

    pos.setY(timeDouble);
    device->pTrend()->m_timeData.push_back(pos);

    pos.setY(power);
    device->pTrend()->m_powerData.push_back(pos);


    if (device->pTrend()->m_frontData.size() > AxisMAX) {
        device->pTrend()->m_frontData.pop_front();
        device->pTrend()->m_backData.pop_front();
        device->pTrend()->m_timeData.pop_front();
        device->pTrend()->m_powerData.pop_front();
    }

    device->pTrend()->upWeldData();
    device->incrementPlotIndex();
}




void HBModbusClient::onDeviceNumChanged() {
    QList<Device *> devices = m_deviceManager->deviceList();

    // 设备偏移量映射表
    QMap<int, int> deviceOffsets = {
        {1, 21}, {2, 51}, {3, 81}, {4, 111}
    };

    // 处理设备的删除和存在状态
    for (int deviceID = 1; deviceID <= 4; ++deviceID) {
        bool deviceExists = std::any_of(devices.begin(), devices.end(),
                                        [deviceID](Device *device) {
                                            return device->pDeviceInformation()->id() == deviceID;
                                        });

        if (!deviceExists) {
            handleDeviceRemoval(deviceID, deviceOffsets);
        }
    }

    // 处理设备的更新
    for (Device *device : devices) {
        int deviceID = device->pDeviceInformation()->id();
        if (!deviceOffsets.contains(deviceID)) {
            qDebug() << "Unknown device ID:" << deviceID;
            continue;
        }

        int offset = deviceOffsets[deviceID];
        QVector<int> deviceData = prepareDeviceData(device);

        writeModbusData(offset, deviceData);
    }
}

void HBModbusClient::handleDeviceRemoval(int deviceID, const QMap<int, int>& deviceOffsets) {
    int offset = deviceOffsets.value(deviceID, -1);
    if (offset == -1) {
        return;
    }

    qDebug() << "设备" << deviceID << "已被删除，修改 DEV_AVAILABLE 为 0";
    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, offset + 2, 1);
    writeUnit.setValue(0, 0);

    QModbusReply *reply = modbusClient->sendWriteRequest(writeUnit, 1);
    if (reply) {
        connect(reply, &QModbusReply::finished, this, [reply]() {
            if (reply->error() != QModbusDevice::NoError) {
                qDebug() << "Modbus 写入错误：" << reply->errorString();
            } else {
                qDebug() << "设备删除，Modbus 写入成功！";
            }
            reply->deleteLater();
        });
    } else {
        qDebug() << "发送写请求到 Modbus 服务器失败。";
    }
}

QVector<int> HBModbusClient::prepareDeviceData(Device *device) {
    QVector<int> data(17, 0);

    const QString model = device->pDeviceInformation()->model();
    data[1] = (model == "L20-VG") ? 0 :
                  (model == "L20-TS") ? 1 :
                  (model == "20DP") ? 2 :
                  (model == "20MA") ? 3 :
                  (model == "自定义") ? 4 : -1;

    // 获取连接方式
    QmlEnum::CONNECTTYPE connectType = device->pDeviceInformation()->connectType();
    if (connectType == QmlEnum::CONNECTTYPE_Network) {
        QStringList networkInfo = DataBaseManager::getInstance()->getNetworkInfoById(device->pDeviceInformation()->connectID() + 1);
        if (!networkInfo.isEmpty()) {
            auto ipList = networkInfo.at(0).split(".");
            for (int i = 0; i < 4; ++i) {
                data[3 + i] = ipList.at(i).toInt();
            }
            data[11] = networkInfo.at(1).toInt();

            auto localIpList = networkInfo.at(2).split(".");
            for (int i = 0; i < 4; ++i) {
                data[7 + i] = localIpList.at(i).toInt();
            }
        }
    } else {
        // RS232 数据配置
        _RS232_Data rs232Data = DataBaseManager::getInstance()->getRS232DataById(device->pDeviceInformation()->connectID());
        data[0] = 1;  // 设置 DEV_TYPE 为 RS232
        data[12] = (rs232Data.port == "COM1") ? 0 : 1;
        data[13] = getBaudRateIndex(rs232Data.baud_rate);
        data[14] = (rs232Data.data_bit == 8) ? 1 : 0;
        data[15] = (rs232Data.parity_bit == "None") ? 0 : (rs232Data.parity_bit == "Odd" ? 1 : 2);
        data[16] = getStopBitIndex(rs232Data.stop_bit);
    }

    data[2] = 1;  // 设置 DEV_AVAILABLE 为 1（设备可用）

    return data;
}

int HBModbusClient::getBaudRateIndex(int baudRate) {
    switch (baudRate) {
    case 2400: return 0;
    case 4800: return 1;
    case 9600: return 2;
    case 19200: return 3;
    case 38400: return 4;
    case 115200: return 5;
    default: return -1;
    }
}

int HBModbusClient::getStopBitIndex(double stopBit) {
    if (stopBit == 1) return 0;
    if (stopBit == 1.5) return 1;
    if (stopBit == 2) return 2;
    return -1;
}

void HBModbusClient::writeModbusData(int offset, const QVector<int>& data) {
    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, offset, data.size());
    for (int i = 0; i < data.size(); ++i) {
        writeUnit.setValue(i, data[i]);
    }

    QModbusReply *reply = modbusClient->sendWriteRequest(writeUnit, 1);
    if (reply) {
        connect(reply, &QModbusReply::finished, this, [reply]() {
            if (reply->error() != QModbusDevice::NoError) {
                qDebug() << "Modbus 写入错误：" << reply->errorString();
            } else {
                qDebug() << "Modbus 写入成功！";
            }
            reply->deleteLater();
        });
    } else {
        qDebug() << "发送写请求到 Modbus 服务器失败。";
    }
}




void HBModbusClient::writeSetTime(int year,int month, int day, int hour, int minute, int second)
{

    QVector<int> timeData = {year, month, day, hour, minute, second};

    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, SYS_RTC_YY, 6);

        for (int i = 0; i < 6; i++) {
            writeUnit.setValue(i, timeData[i]);
        }
        QModbusReply *reply = modbusClient->sendWriteRequest(writeUnit, 1);

        if (reply) {

            connect(reply, &QModbusReply::finished, this, [reply]() {

                if (reply->error() != QModbusDevice::NoError) {
                    qDebug() << "Modbus write error:" << reply->errorString();
                } else {
                    qDebug() << "Modbus write successful!";
                }
                reply->deleteLater();
            });
    } else {
        qDebug() << "No changes to write.";
    }
}


void HBModbusClient::setLED(bool state)
{
    int coilState = state ? 0b1110 : 0b0001;

    QModbusDataUnit dataUnit(QModbusDataUnit::Coils, 0, 4);

    for (int i = 0; i < 4; ++i) {
        dataUnit.setValue(i, (coilState >> (3 - i)) & 0x01);
    }

    QModbusReply *reply = modbusClient->sendWriteRequest(dataUnit, 1);


    if (reply) {
        connect(reply, &QModbusReply::finished, this, &HBModbusClient::coilWriteFinished);
    } else {
        qDebug() << "Failed to write coil to Modbus server.";
    }
}

void HBModbusClient::coilWriteFinished()
{
    qDebug() << "coilWriteFinished11111111111111111111";
    QModbusReply *reply = qobject_cast<QModbusReply *>(sender());
    if (reply) {
        if (reply->error() != QModbusDevice::NoError) {
             qDebug() << "coilWriteFinished222222222222222222222";
            qDebug() << "Modbus error during coil write:" << reply->errorString();
        } else {
            qDebug() << "Coil write successful.";
        }

        reply->deleteLater();
    }
}


void HBModbusClient::setIO(int deviceID, int DEV_WELD_ALARM)
{
    if (DEV_WELD_ALARM != 1 && DEV_WELD_ALARM != 2) {
        return;
    }

    qDebug() << "Setting IO for device" << deviceID << "with alarm state" << DEV_WELD_ALARM;


    Message::getInstance()->addMessage(deviceID, QmlEnum::MESSAGE_defective);


    setLED(false);

    int coilAddress1 = 0, coilAddress2 = 0, coilValue1 = 0, coilValue2 = 0;


    if (!getCoilAddressesAndValues(deviceID, DEV_WELD_ALARM, coilAddress1, coilAddress2, coilValue1, coilValue2)) {
        return;
    }


    QModbusDataUnit dataUnit(QModbusDataUnit::Coils, coilAddress1, 2);
    dataUnit.setValue(0, coilValue1);
    dataUnit.setValue(1, coilValue2);


    QModbusReply *reply = modbusClient->sendWriteRequest(dataUnit, 1);
    if (reply) {
        connect(reply, &QModbusReply::finished, this, &HBModbusClient::coilWriteFinished);
    } else {
        qDebug() << "Failed to write coil to Modbus server.";
    }
}

bool HBModbusClient::getCoilAddressesAndValues(int deviceId, int DEV_WELD_ALARM, int &coilAddress1, int &coilAddress2, int &coilValue1, int &coilValue2)
{
    if (DEV_WELD_ALARM == 1) {

        switch (deviceId) {
        case 1:
            coilAddress1 = 11; coilAddress2 = 12; coilValue1 = 1; coilValue2 = 0;
            break;
        case 2:
            coilAddress1 = 16; coilAddress2 = 17; coilValue1 = 1; coilValue2 = 0;
            break;
        case 3:
            coilAddress1 = 21; coilAddress2 = 22; coilValue1 = 1; coilValue2 = 0;
            break;
        case 4:
            coilAddress1 = 26; coilAddress2 = 27; coilValue1 = 1; coilValue2 = 0;
            break;
        default:
            return false;
        }
    } else if (DEV_WELD_ALARM == 2) {

        switch (deviceId) {
        case 1:
            coilAddress1 = 11; coilAddress2 = 12; coilValue1 = 0; coilValue2 = 1;
            break;
        case 2:
            coilAddress1 = 16; coilAddress2 = 17; coilValue1 = 0; coilValue2 = 1;
            break;
        case 3:
            coilAddress1 = 21; coilAddress2 = 22; coilValue1 = 0; coilValue2 = 1;
            break;
        case 4:
            coilAddress1 = 26; coilAddress2 = 27; coilValue1 = 0; coilValue2 = 1;
            break;
        default:
            return false;
        }
    } else {

        return false;
    }

    return true;
}


void HBModbusClient::resetButton()
{
    QModbusDataUnit dataUnit(QModbusDataUnit::Coils, SYS_BTN_R_BIT4, 1);

    QModbusReply *reply = modbusClient->sendReadRequest(dataUnit, 1);
    if (reply) {
         reply->setProperty("address",SYS_BTN_R_BIT4);
        connect(reply, &QModbusReply::finished, this, &HBModbusClient::CoilsReadyRead);
    } else {
        qDebug() << "Failed to read coil at address" << SYS_BTN_R_BIT4;
    }

}

void HBModbusClient::checkAndResetCoils()
{
    QList<int> checkAddresses = {13, 18, 23, 28};

    for (int i = 0; i < checkAddresses.size(); ++i) {

        QModbusDataUnit dataUnit(QModbusDataUnit::Coils, checkAddresses[i], 1);

        // 发送读取请求
        QModbusReply *reply = modbusClient->sendReadRequest(dataUnit, 1);
        if (reply) {
            reply->setProperty("address", checkAddresses[i]);
            connect(reply, &QModbusReply::finished, this, &HBModbusClient::CoilsReadyRead);
        } else {
            qDebug() << "Failed to read coil at address" << checkAddresses[i];
        }
    }

}

// 重置线圈值为 0
void HBModbusClient::resetCoilsToZero()
{

    QList<int> resetAddresses = { 11, 12, 16, 17, 21, 22, 26, 27};

    for (int i = 0; i < resetAddresses.size(); ++i) {
        QModbusDataUnit dataUnit(QModbusDataUnit::Coils, resetAddresses[i], 1);

        dataUnit.setValue(i, 0);
        qDebug() << "FresetAddresses[i]" << resetAddresses[i] <<"resetAddresses.size():" << resetAddresses.size();
        QModbusReply *reply = modbusClient->sendWriteRequest(dataUnit, 1);
        if (reply) {
            connect(reply, &QModbusReply::finished, this, &HBModbusClient::coilWriteFinished);
        } else {
            qDebug() << "Failed to reset coils.";
        }
    }

}


void HBModbusClient::resetCoilsAtAddresses(const QList<int>& addresses)
{
    for (int address : addresses) {
        QModbusDataUnit dataUnit(QModbusDataUnit::Coils, address, 1);
        dataUnit.setValue(0, 0);

        QModbusReply *reply = modbusClient->sendWriteRequest(dataUnit, 1);
        if (!reply) {
            qDebug() << "Failed to write coil at address" << address;
        }
    }
}


void HBModbusClient::checkAlarmIsAllZero()
{

    coilStatus.clear();
    for (int i = 0; i < alarmIoAddress.size(); ++i) {
        coilStatus[alarmIoAddress[i]] = false;
    }

    for (int i = 0; i < alarmIoAddress.size(); ++i) {
        QModbusDataUnit dataUnit(QModbusDataUnit::Coils, alarmIoAddress[i], 1);
        QModbusReply *reply = modbusClient->sendReadRequest(dataUnit, 1);
        if (reply) {
            connect(reply, &QModbusReply::finished, this, &HBModbusClient::checkAlarmIsAllZeroRead);
        } else {
            qDebug() << "Failed to read coil at address" << alarmIoAddress[i];
        }
    }

}

void HBModbusClient::checkAlarmIsAllZeroRead()
{
    QModbusReply *reply = qobject_cast<QModbusReply *>(sender());
    if (!reply) {
        return;
    }

    const QModbusDataUnit unit = reply->result();
    int address = unit.startAddress();
    bool coilValue = unit.value(0);

    if (coilStatus.contains(address)) {
        coilStatus[address] = coilValue;
    }
    readCounter++;
    if (readCounter == alarmIoAddress.size()) {

        bool allZero = true;
        for (int i = 0; i < alarmIoAddress.size(); ++i) {
            if (coilStatus[alarmIoAddress[i]] != 0) {
                allZero = false;
                break;
            }
        }
        if (allZero) {
            setLED(true);
        }
        readCounter = 0;
    }

    reply->deleteLater();
}
