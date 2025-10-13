#include "devicemodbusmapper.h"
#include "DataBase/databasemanager.h"
#include "model/deviceinformation.h"
#include <QDebug>
#include "model/message.h"

DeviceModbusMapper::ComPort DeviceModbusMapper::mapComPort(int comNum)
{
    return (comNum == 2) ? ComPort::COM2 : ComPort::COM1;
}

DeviceModbusMapper::EthPort DeviceModbusMapper::mapEthPort(int ethPort)
{
    switch (ethPort) {
    case 1: return EthPort::ETH0;
    case 2: return EthPort::ETH1;
    case 3: return EthPort::ETH2;
    case 4: return EthPort::ETH3;
    case 5: return EthPort::ETH4;
    default: return EthPort::ETH0;
    }
}

DeviceModbusMapper::BaudRate DeviceModbusMapper::mapBaudRate(int baud)
{
    switch (baud)
    {
        case 2400:
                return BaudRate::Baud_2400;
        case 4800:
                return BaudRate::Baud_4800;
        case 9600:
                return BaudRate::Baud_9600;
        case 19200:
                return BaudRate::Baud_19200;
        case 38400:
                return BaudRate::Baud_38400;
        case 115200:
                return BaudRate::Baud_115200;

        default: return BaudRate::Baud_9600;
    }
}

DeviceModbusMapper::DataBit DeviceModbusMapper::mapDataBit(int bit)
{
    return (bit == 8) ? DataBit::Bit8 : DataBit::Bit7;
}

DeviceModbusMapper::ParityBit DeviceModbusMapper::mapParity(const QString &parity)
{
    if (parity.compare("Odd") == 0) return ParityBit::Odd;
    if (parity.compare("Even") == 0) return ParityBit::Even;
    return ParityBit::None;
}

DeviceModbusMapper::StopBit DeviceModbusMapper::mapStopBit(float stopBit) {
    if (qFuzzyCompare(stopBit, 1.5f)) return StopBit::Bit1_5;
    if (qFuzzyCompare(stopBit, 2.0f)) return StopBit::Bit2;
    return StopBit::Bit1;
}

DeviceModbusMapper::DeviceRegisterData DeviceModbusMapper::generateRegisterData(Device* device)
{
    DeviceRegisterData deviceInfodata;

    int deviceId = device->getDevInfoObject()->id();
    deviceInfodata.deviceID = deviceId;
    DeviceInformation* deviceInfo = device->getDevInfoObject();

    //protocol type
    const QString  weldType = deviceInfo->model();
    if(weldType == "L20-VG")
        deviceInfodata.DEV_PROTOCOL_TYPE = ProtocolType::L20_VG;
    else
        deviceInfodata.DEV_PROTOCOL_TYPE = ProtocolType::L20_TS;

    bool isTcp = (deviceInfo->getConnectType() == DeviceInfoEnum::TCP_IP);
    deviceInfodata.DEV_TYPE = isTcp ? DeviceType::Ethernet : DeviceType::Serial;

    if(isTcp)
    {
        QStringList network = DataBaseManager::getInstance()->getNetworkInfoById(deviceInfo->connectID() + 1);
        if(network.size() == 3)
        {
            QStringList serverIp = network.at(0).split(".");
            QStringList localIp = network.at(2).split(".");
            for(int i = 0; i < 4; ++i)
            {
                deviceInfodata.DEV_SERVER_IP[i] = serverIp.value(i).toUShort();
                deviceInfodata.DEV_LOCAL_IP[i] = localIp.value(i).toUShort();
            }
            deviceInfodata.DEV_SERVER_PORT = network.at(1).toShort();
        }

        deviceInfodata.DEV_COM_NUM    = ComPort::COM1;
        deviceInfodata.DEV_BAUD_RATE  = BaudRate::Baud_2400;
        deviceInfodata.DEV_DATA_BIT   = DataBit::Bit7;
        deviceInfodata.DEV_PARITY_BIT = ParityBit::None;
        deviceInfodata.DEV_STOP_BIT   = StopBit::Bit1;

    }
    else
    {
        _RS232_Data rs232 = DataBaseManager::getInstance()->getRS232DataById(deviceInfo->connectID());
        qDebug() << "RS232 DATA -> ID:" << rs232.id
                 << "PORT:" << rs232.port
                 << "BAUD:" << rs232.baud_rate
                 << "DATA_BIT:" << rs232.data_bit
                 << "PARITY:" << rs232.parity_bit
                 << "STOP_BIT:" << rs232.stop_bit;
        deviceInfodata.DEV_COM_NUM      = mapComPort(rs232.id);
        deviceInfodata.DEV_BAUD_RATE    = mapBaudRate(rs232.baud_rate);
        deviceInfodata.DEV_DATA_BIT     = mapDataBit(rs232.data_bit);
        deviceInfodata.DEV_PARITY_BIT   = mapParity(rs232.parity_bit);
        deviceInfodata.DEV_STOP_BIT     = mapStopBit(rs232.stop_bit);

        for (int i = 0; i < 4; ++i)
        {
            deviceInfodata.DEV_SERVER_IP[i] = 0;
            deviceInfodata.DEV_LOCAL_IP[i]  = 0;
        }
        deviceInfodata.DEV_SERVER_PORT = 0;
    }

    deviceInfodata.DEV_AVAILABLE = 1;
    int state = DeviceInfoEnum::CONNECTED;
    deviceInfo->setConnectState(state);
    Message::getInstance()->addMessage(deviceId,QmlEnum::MESSAGE_setupComplete);

    qDebug() << "DeviceID:" << deviceInfodata.deviceID
             << "DEV_TYPE:" << static_cast<int>(deviceInfodata.DEV_TYPE)
             << "DEV_PROTOCOL_TYPE:" << static_cast<int>(deviceInfodata.DEV_PROTOCOL_TYPE)
             << "DEV_AVAILABLE:" << deviceInfodata.DEV_AVAILABLE;

    qDebug() << "DEV_SERVER_IP:"
             << deviceInfodata.DEV_SERVER_IP[0] << deviceInfodata.DEV_SERVER_IP[1]
             << deviceInfodata.DEV_SERVER_IP[2] << deviceInfodata.DEV_SERVER_IP[3];

    qDebug() << "DEV_LOCAL_IP:"
             << deviceInfodata.DEV_LOCAL_IP[0] << deviceInfodata.DEV_LOCAL_IP[1]
             << deviceInfodata.DEV_LOCAL_IP[2] << deviceInfodata.DEV_LOCAL_IP[3];

    qDebug() << "DEV_SERVER_PORT:" << deviceInfodata.DEV_SERVER_PORT
             << "DEV_COM_NUM:" << static_cast<int>(deviceInfodata.DEV_COM_NUM)
             << "DEV_BAUD_RATE:" << static_cast<int>(deviceInfodata.DEV_BAUD_RATE)
             << "DEV_DATA_BIT:" << static_cast<int>(deviceInfodata.DEV_DATA_BIT)
             << "DEV_PARITY_BIT:" << static_cast<int>(deviceInfodata.DEV_PARITY_BIT)
             << "DEV_STOP_BIT:" << static_cast<int>(deviceInfodata.DEV_STOP_BIT);

    return deviceInfodata;
}

QVector<quint16> DeviceModbusMapper::toRegisterVector(const DeviceRegisterData &deviceInfodata)
{
    QVector<quint16> devVector;
    devVector.reserve(15);

    devVector << static_cast<quint16>(deviceInfodata.DEV_TYPE);
    devVector << static_cast<quint16>(deviceInfodata.DEV_PROTOCOL_TYPE);
    devVector << static_cast<quint16>(deviceInfodata.DEV_AVAILABLE);

    for (int i = 0; i < 4; ++i) devVector << static_cast<quint16>(deviceInfodata.DEV_SERVER_IP.value(i, 0));

    for (int i = 0; i < 4; ++i) devVector << static_cast<quint16>(deviceInfodata.DEV_LOCAL_IP.value(i, 0));

    devVector << static_cast<quint16>(deviceInfodata.DEV_SERVER_PORT);

    devVector << static_cast<quint16>(deviceInfodata.DEV_COM_NUM);
    devVector << static_cast<quint16>(deviceInfodata.DEV_BAUD_RATE);
    devVector << static_cast<quint16>(deviceInfodata.DEV_DATA_BIT);
    devVector << static_cast<quint16>(deviceInfodata.DEV_PARITY_BIT);
    devVector << static_cast<quint16>(deviceInfodata.DEV_STOP_BIT);

    return devVector;
}


