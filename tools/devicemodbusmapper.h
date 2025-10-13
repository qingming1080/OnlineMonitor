#ifndef DEVICEMODBUSMAPPER_H
#define DEVICEMODBUSMAPPER_H

#include <QString>
#include <QStringList>
#include <QVector>
#include "model/device.h"

class DeviceModbusMapper
{

public:

    enum class DeviceType : int
    {   Ethernet = 0,
        Serial = 1,
        Analog = 2
    };

    enum class ProtocolType : int
    {   L20_VG = 0,
        L20_TS = 1,
    };

    enum class ComPort : int
    {   COM1 = 0,
        COM2 = 1
    };

    enum class EthPort : int
    {
        ETH0 = 1,
        ETH1 = 2,
        ETH2 = 3,
        ETH3 = 4,
        ETH4 = 5
    };

    enum class BaudRate : int
    {   Baud_2400 = 0,
        Baud_4800 = 1,
        Baud_9600 = 2,
        Baud_19200 = 3,
        Baud_38400 = 4,
        Baud_115200 = 5
    };

    enum class DataBit : int
    {   Bit7 = 0,
        Bit8 = 1
    };
    enum class ParityBit : int
    {   None = 0,
        Odd = 1,
        Even = 2
    };
    enum class StopBit : int
    {
        Bit1 = 0,
        Bit1_5 = 1,
        Bit2 = 2
    };

  //Modbus -> Device Data
    struct DeviceRegisterData {
        int deviceID = 0;
        DeviceType DEV_TYPE = DeviceType::Ethernet;;
        ProtocolType DEV_PROTOCOL_TYPE = ProtocolType::L20_VG;
        int DEV_AVAILABLE = 0;

        QVector<quint8> DEV_SERVER_IP; // 4 bytes
        QVector<quint8> DEV_LOCAL_IP;  // 4 bytes
        quint16 DEV_SERVER_PORT;

        ComPort DEV_COM_NUM = ComPort::COM1;
        BaudRate DEV_BAUD_RATE = BaudRate::Baud_9600;
        DataBit DEV_DATA_BIT = DataBit::Bit8;
        ParityBit DEV_PARITY_BIT = ParityBit::None;
        StopBit DEV_STOP_BIT = StopBit::Bit1;

        DeviceRegisterData() {
            DEV_SERVER_IP.resize(4);
            DEV_LOCAL_IP.resize(4);
        }
    };

    static DeviceRegisterData generateRegisterData(Device* device);

    static QVector<quint16> toRegisterVector(const DeviceRegisterData &data);

private:
    static  ComPort      mapComPort(int comNum);
    static  EthPort      mapEthPort(int ethPort);
    static  BaudRate     mapBaudRate(int baud);
    static  DataBit      mapDataBit(int bit);
    static  ParityBit    mapParity(const QString &parity);
    static  StopBit      mapStopBit(float  stopBit);
};

#endif // DEVICEMODBUSMAPPER_H
