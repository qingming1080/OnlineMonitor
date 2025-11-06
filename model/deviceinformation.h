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
    Q_PROPERTY(QString ProductionMaxBacth   READ getProductionMaxBacth  WRITE setProductionMaxBacth     NOTIFY notifyProductionMaxBacthChanged)
    // 学习样本数
    Q_PROPERTY(QString MaxModelSamples      READ getMaxModelSamples     WRITE setMaxModelSamples        NOTIFY notifyMaxModelSamplesChanged)
    // 良率下限
    Q_PROPERTY(QString YieldRateLowerLimit  READ getYieldRateLowerLimit WRITE setYieldRateLowerLimit    NOTIFY notifyYieldRateLowerLimitChanged)
    // 高度模式
    Q_PROPERTY(bool    HeightEncoderOption  READ getHeightEncoderOption WRITE setHeightEncoderOption    NOTIFY notifyHeightEncoderOptionChanged)
    // 可疑模式
    Q_PROPERTY(bool    SuspiciousOption     READ getSuspiciousOption    WRITE setSuspiciousOption   NOTIFY notifySuspiciousOptionChanged)
    // 连接方式
    Q_PROPERTY(int     ConnectType          READ getConnectType         WRITE setConnectType        NOTIFY notifyConnectTypeChanged)
    /// 2024/04/07 设备状态 暴露
    // 设备状态(生产中，待机等)
    Q_PROPERTY(int     ConnectState         READ getConnectState        WRITE setConnectState       NOTIFY notifyConnectStateChanged)

    /// 2024/08/01 IP与端口 暴露
    Q_PROPERTY(QString SingleFactor         READ getSingleFactor        WRITE setSingleFactor       NOTIFY notifySingleFactorChanged FINAL)
    Q_PROPERTY(QString GeneralFactor        READ getGeneralFactor       WRITE setGeneralFactor      NOTIFY notifyGeneralFactorChanged FINAL)
    Q_PROPERTY(QString ForceThreshold       READ getForceThreshold      WRITE setForceThreshold     NOTIFY notifyForceThresholdChanged FINAL)
    Q_PROPERTY(QString ResidualThreshold    READ getResidualThreshold   WRITE setResidualThreshold  NOTIFY notifyResidualThresholdChanged FINAL)
    Q_PROPERTY(QString AutoLearningCount    READ getAutoLearningCount   WRITE setAutoLearningCount  NOTIFY notifyAutoLearningCountChanged FINAL)


    Q_PROPERTY(int     ComNumber            READ getComNumber           WRITE setComNumber          NOTIFY notifyComNumberChanged FINAL)
    Q_PROPERTY(int     BaudRate             READ getBaudRate            WRITE setBaudRate           NOTIFY notifyBaudRateChanged FINAL)
    Q_PROPERTY(int     DataBits             READ getDataBits            WRITE setDataBits           NOTIFY notifyDataBitsChanged FINAL)
    Q_PROPERTY(int     ParityBits           READ getParityBits          WRITE setParityBits         NOTIFY notifyParityBitsChanged FINAL)
    Q_PROPERTY(int     StopBits             READ getStopBits            WRITE setStopBits           NOTIFY notifyStopBitsChanged FINAL)
public:
    struct NETWORK_PROPERTIES
    {
        int     EthNumber;
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
        DeviceInfoEnum::CONNECT_TYPE    ConnectType;    // 连接方式     0_RS232  1_Network
        DeviceInfoEnum::WLEDER_TYPE     ProtocolType;   // 焊机型号
        DeviceInfoEnum::CONNECT_STATE   ConnectState;   // 连接state
        DeviceInfoEnum::NETWORK_TYPE    NetworkType;
        NETWORK_PROPERTIES              NetworkProperties;
        SERIAL_PROPERTIES               SerialProperties;
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

    QString getSingleFactor() const;
    int GetSingleFactor() const;
    void setSingleFactor(const QString &factor);

    QString getGeneralFactor() const;
    int GetGeneralFactor() const;
    void setGeneralFactor(const QString &factor);

    QString getForceThreshold() const;
    int GetForceThreshold() const;
    void setForceThreshold(const QString &threshold);

    QString getResidualThreshold() const;
    int GetResidualThreshold() const;
    void setResidualThreshold(const QString &threshold);

    QString getAutoLearningCount() const;
    int GetAutoLearningCount() const;
    void setAutoLearningCount(const QString &limit);

    int getComNumber() const;
    void setComNumber(const int &com);

    int getBaudRate() const;
    void setBaudRate(const int &baudrate);

    int getDataBits() const;
    void setDataBits(const int &databits);

    int getParityBits() const;
    void setParityBits(const int &paritybits);

    int getStopBits() const;
    void setStopBits(const int &stopbits);

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

    void notifySingleFactorChanged();
    void notifyGeneralFactorChanged();
    void notifyForceThresholdChanged();
    void notifyResidualThresholdChanged();
    void notifyAutoLearningCountChanged();

    void notifyComNumberChanged();
    void notifyBaudRateChanged();
    void notifyDataBitsChanged();
    void notifyParityBitsChanged();
    void notifyStopBitsChanged();

private:
    int m_WelderID;
    DataBaseManager::DB_CONFIGURE   m_DBConfigure;
    DataBaseManager::DB_NETWORK     m_DBNetwork;
    DataBaseManager::DB_RS232       m_DBRS232;
    // DeviceInfoEnum::CONNECT_TYPE    m_iConnectType;
    // DeviceInfoEnum::CONNECT_STATE   m_iConnectState;

    MODBUS_CONFIGURE                m_ModbusConfigure;
};

#endif // DEVICEINFORMATION_H
