#ifndef DEVICEINFORMATION_H
#define DEVICEINFORMATION_H

#include <QObject>
#include <QSerialPort>
#include "DataBase/databasemanager.h"
///
/// \brief The DeviceInformation class : 设备信息:对应表格Configuration
///

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

class DeviceInformation : public QObject
{
    Q_OBJECT
    // 焊机名称
    Q_PROPERTY(QString  WelderName           READ getWelderName          WRITE setWelderName             NOTIFY notifyWelderNameChanged FINAL)
    // 焊机型号
    Q_PROPERTY(int      WelderType           READ getWelderType          WRITE setWelderType             NOTIFY notifyWelderTypeChanged FINAL)
    // 最大生产批量
    Q_PROPERTY(QString  ProductionMaxBacth   READ getProductionMaxBacth  WRITE setProductionMaxBacth     NOTIFY notifyProductionMaxBacthChanged)
    // 学习样本数
    Q_PROPERTY(QString  MaxModelSamples      READ getMaxModelSamples     WRITE setMaxModelSamples        NOTIFY notifyMaxModelSamplesChanged)
    // 良率下限
    Q_PROPERTY(QString  YieldRateLowerLimit  READ getYieldRateLowerLimit WRITE setYieldRateLowerLimit    NOTIFY notifyYieldRateLowerLimitChanged)
    // 高度模式
    Q_PROPERTY(bool     HeightEncoderOption  READ getHeightEncoderOption WRITE setHeightEncoderOption    NOTIFY notifyHeightEncoderOptionChanged)
    // 可疑模式
    Q_PROPERTY(bool     SuspiciousOption     READ getSuspiciousOption    WRITE setSuspiciousOption       NOTIFY notifySuspiciousOptionChanged)
    // 连接方式
    Q_PROPERTY(int      ConnectType          READ getConnectType         WRITE setConnectType            NOTIFY notifyConnectTypeChanged)
    /// 2024/04/07 设备状态 暴露
    // 设备状态(生产中，待机等)
    Q_PROPERTY(int      ConnectState         READ getConnectState        WRITE setConnectState           NOTIFY notifyConnectStateChanged)

    /// 2024/08/01 IP与端口 暴露
    // 远程端口
    // Q_PROPERTY(QString          mesIP                       READ mesIP               WRITE setMesIP               NOTIFY mesIPChanged)
    // // 远程IP
    // Q_PROPERTY(QString          deviceIP                    READ deviceIP            WRITE setDeviceIP            NOTIFY deviceIPChanged)
    // // 客户端IP
    // Q_PROPERTY(int              mesPort                     READ mesPort             WRITE setMesPort             NOTIFY mesPortChanged)


public:
    struct NETWORK_PROPERTIES
    {
        QString LocalIP;
        QString RemoteIP;
        int     PortNumber;
    };

    struct SERIAL_PROPERTIES
    {
        int ComNumber;
        QSerialPort::BaudRate BaudRate;
        QSerialPort::DataBits DataBits;
        QSerialPort::Parity   ParityBits;
        QSerialPort::StopBits StopBits;
    };

    struct MODBUS_CONFIGURE
    {
        DeviceInfoEnum::CONNECT_TYPE ConnectType;    // 连接方式     0_RS232  1_Network
        DeviceInfoEnum::WLEDER_TYPE  ProtocolType;   // 焊机型号
        DeviceInfoEnum::CONNECT_STATE ConnectState;  // 连接state
        DeviceInfoEnum::NETWORK_TYPE NetworkType;
        NETWORK_PROPERTIES NewworkProperties;
        SERIAL_PROPERTIES SerialProperties;
    };

    explicit DeviceInformation(int welderID = 0, QObject *parent = nullptr);

    QString getWelderName() const;
    void setWelderName(const QString &name);

    int getWelderType() const;
    void setWelderType(const int &type);

    QString getProductionMaxBacth() const;
    void setProductionMaxBacth(const QString &maxBacth);

    QString getMaxModelSamples() const;
    void setMaxModelSamples(const QString &samples);

    QString getYieldRateLowerLimit() const;
    void setYieldRateLowerLimit(const QString &yieldRate);

    bool getHeightEncoderOption() const;
    void setHeightEncoderOption(const bool &option);

    bool getSuspiciousOption() const;
    void setSuspiciousOption(const bool &option);

    int getConnectType() const;
    void setConnectType(const int &type);

    int getConnectTypeID() const;
    void setConnectTypeID(const int &typeID);

    int getConnectState() const;
    void setConnectState(const int &state);

    // QString mesIP() const;
    // void setMesIP(const QString &newMesIP);

    // QString deviceIP() const;
    // void setDeviceIP(const QString &newDeviceIP);

    // int mesPort() const;
    // void setMesPort(int newMesPort);

signals:
    void notifyWelderNameChanged();
    void notifyWelderTypeChanged();
    void notifyProductionMaxBacthChanged();
    void notifyMaxModelSamplesChanged();
    void notifyYieldRateLowerLimitChanged();
    void notifyHeightEncoderOptionChanged();
    void notifySuspiciousOptionChanged();
    void notifyConnectTypeChanged();
    void notifyConnectStateChanged();

    // void mesIPChanged();

    // void deviceIPChanged();

    // void mesPortChanged();

private:
    int m_WelderID;
    DataBaseManager::DB_CONFIGURE   m_DBConfigure;
    DeviceInfoEnum::CONNECT_TYPE    m_iConnectType;
    DeviceInfoEnum::CONNECT_STATE   m_iConnectState;

    // int m_mesPort{0};
    // QString m_mesIP;
    // QString m_deviceIP;

};

#endif // DEVICEINFORMATION_H
