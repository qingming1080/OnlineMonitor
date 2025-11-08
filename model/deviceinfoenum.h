#ifndef DEVICEINFOENUM_H
#define DEVICEINFOENUM_H
#include <QObject>
class DeviceInfoEnum : public QObject
{
    Q_OBJECT
public:
    enum CONNECT_STATE
    {
        DISCONNECTED    = 0,    // 未连接
        CONNECTED       = 1,     // 已连接
    };
    Q_ENUM(CONNECT_STATE)

    // 设备连接方式
    enum CONNECT_TYPE
    {
        TCP_IP = 0,    // TCP_CP
        RS232  = 1,    // RS232
        ANALOG = 2     //Analog
    };
    Q_ENUM(CONNECT_TYPE)

    enum WLEDER_TYPE
    {
        L20_VG  = 0,
        L20_TS  = 1,
        BRANSON_2000XC  = 2
    };Q_ENUM(WLEDER_TYPE)

    enum NETWORK_TYPE
    {
        SERVER = 0,
        CLIENT = 1
    };

public:
    explicit DeviceInfoEnum(QObject *parent = nullptr){Q_UNUSED(parent);}
};
#endif // DEVICEINFOENUM_H
