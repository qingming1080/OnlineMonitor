#ifndef DEVICEINFORMATION_H
#define DEVICEINFORMATION_H

#include <QObject>
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
        TCP_IP  = 0,    // 网络连接
        RS232   = 1,    // RS232
    };
    Q_ENUM(CONNECT_TYPE)

    enum WLED_TYPE
    {
        L20_VG  = 0,
        L20_TS  = 1,
    };Q_ENUM(WLED_TYPE)

public:
    explicit DeviceInfoEnum(QObject *parent = nullptr){Q_UNUSED(parent);}
};

class DeviceInformation : public QObject
{
    Q_OBJECT
    // 焊机ID
    Q_PROPERTY(int              id                          READ id                  /*WRITE setId */             NOTIFY idChanged)
    // 焊机名称
    Q_PROPERTY(QString          name                        READ name                WRITE setName                NOTIFY nameChanged)
    // 焊机型号
    Q_PROPERTY(QString          model                       READ model               WRITE setModel               NOTIFY modelChanged)
    // 最大生产批量
    Q_PROPERTY(int              maxBacth                    READ maxBacth            WRITE setMaxBacth            NOTIFY maxBacthChanged)
    // 学习样本数
    Q_PROPERTY(int              sample                      READ sample              WRITE setSample              NOTIFY sampleChanged)
    // 良率下限
    Q_PROPERTY(int              lowerLimit                  READ lowerLimit          WRITE setLowerLimit          NOTIFY lowerLimitChanged)
    // 高度模式
    Q_PROPERTY(int              heightOption                READ heightOption        WRITE setHeightOption        NOTIFY heightOptionChanged)

    // 连接方式
    Q_PROPERTY(int              ConnectType                 READ getConnectType      WRITE setConnectType         NOTIFY notifyConnectTypeChanged)
    // 连接方式ID
    Q_PROPERTY(int              connectID                   READ connectID           WRITE setConnectID           NOTIFY connectIDChanged)

    /// 2024/04/07  实时良率暴露
    // 实时良率
    Q_PROPERTY(int              goodRate                    READ goodRate            WRITE setGoodRate            NOTIFY goodRateChanged)
    // 合格
    Q_PROPERTY(int              goodCycles                  READ goodCycles          WRITE setGoodCycles          NOTIFY goodCyclesChanged)
    // 可疑
    Q_PROPERTY(int              suspectCycles               READ suspectCycles       WRITE setSuspectCycles       NOTIFY suspectCyclesChanged)
    // 次品
    Q_PROPERTY(int              notDefinite                 READ notDefinite         WRITE setNotDefinite         NOTIFY notDefiniteChanged)

    /// 2024/04/07  焊接结果暴露
    // 焊接结果:功率
    Q_PROPERTY(int              power                       READ power               WRITE setPower               NOTIFY powerChanged)
    // 焊接结果:时间
    Q_PROPERTY(int              time                        READ time                WRITE setTime                NOTIFY timeChanged)
    // 焊接结果:能量
    Q_PROPERTY(int              energy                      READ energy              WRITE setEnergy              NOTIFY energyChanged)
    // 焊接结果:焊前高度
    Q_PROPERTY(int              heightPre                   READ heightPre           WRITE setHeightPre           NOTIFY heightPreChanged)
    // 焊接结果:焊后高度
    Q_PROPERTY(int              heightPost                  READ heightPost          WRITE setHeightPost          NOTIFY heightPostChanged)

    /// preset
    Q_PROPERTY(QString          preEnegy                    READ getPreEnegy         WRITE setPreEnegy            NOTIFY preEnegyChanged)

    Q_PROPERTY(QString          preAmplitude                READ getPreAmplitude     WRITE setPreAmplitude        NOTIFY preAmplitudeChanged)

    Q_PROPERTY(QString          preTP                       READ getPreTP            WRITE setPreTP               NOTIFY preTPChanged)

    Q_PROPERTY(QString          preWP                       READ getPreWP            WRITE setPreWP               NOTIFY preWPChanged)

    Q_PROPERTY(QString          preTimeMin                  READ getPreTimeMin       WRITE setPreTimeMin          NOTIFY preTimeMinChanged)

    Q_PROPERTY(QString          preTimeMax                  READ getPreTimeMax       WRITE setPreTimeMax          NOTIFY preTimeMaxChanged)

    Q_PROPERTY(QString          prePowerMin                 READ getPrePowerMin      WRITE setPrePowerMin         NOTIFY prePowerMinChanged)

    Q_PROPERTY(QString          prePowerMax                 READ getPrePowerMax      WRITE setPrePowerMax         NOTIFY prePowerMaxChanged)

    Q_PROPERTY(QString          preHeightMin                READ getPreHeightMin     WRITE setPreHeightMin        NOTIFY preHeightMinChanged)

    Q_PROPERTY(QString          preHeightMax                READ getPreHeightMax     WRITE setPreHeightMax        NOTIFY preHeightMaxChanged)

    Q_PROPERTY(QString          postHeightMin               READ getPostHeightMin    WRITE setPostHeightMin       NOTIFY postHeightMinChanged)

    Q_PROPERTY(QString          postHeightMax               READ getPostHeightMax    WRITE setPostHeightMax       NOTIFY postHeightMaxChanged)

    /// 2024/08/01 IP与端口 暴露
    // 远程端口
    Q_PROPERTY(QString          mesIP                       READ mesIP               WRITE setMesIP               NOTIFY mesIPChanged)
    // 远程IP
    Q_PROPERTY(QString          deviceIP                    READ deviceIP            WRITE setDeviceIP            NOTIFY deviceIPChanged)
    // 客户端IP
    Q_PROPERTY(int              mesPort                     READ mesPort             WRITE setMesPort             NOTIFY mesPortChanged)

    /// 2024/04/07 设备状态 暴露
    // 设备状态(生产中，待机等)
    Q_PROPERTY(int              ConnectState                READ getConnectState     WRITE setConnectState        NOTIFY notifyConnectStateChanged)
public:


    explicit DeviceInformation(int welderID = 0, QObject *parent = nullptr);

    Q_INVOKABLE QString name() const;
    Q_INVOKABLE void setName(const QString &newName);

    Q_INVOKABLE QString model() const;
    Q_INVOKABLE void setModel(const QString &newModel);

    int getConnectType() const;
    void setConnectType(const int &type);

    int getConnectState() const;
    void setConnectState(const int &state);

    Q_INVOKABLE int id() const;
//    Q_INVOKABLE void setId(int newId);

    Q_INVOKABLE int maxBacth() const;
    Q_INVOKABLE void setMaxBacth(int newMaxBacth);

    Q_INVOKABLE int sample() const;
    Q_INVOKABLE void setSample(int newSample);

    Q_INVOKABLE int heightOption() const;
    Q_INVOKABLE void setHeightOption(int newHeightOption);

    Q_INVOKABLE int lowerLimit() const;
    Q_INVOKABLE void setLowerLimit(int newLowerLimit);

    Q_INVOKABLE int connectID() const;
    Q_INVOKABLE void setConnectID(int newConnectID);

    Q_INVOKABLE int goodRate() const;
    Q_INVOKABLE void setGoodRate(int newGoodRate);

    Q_INVOKABLE int goodCycles() const;
    Q_INVOKABLE void setGoodCycles(int newGoodCycles);

    Q_INVOKABLE int suspectCycles() const;
    Q_INVOKABLE void setSuspectCycles(int newSuspectCycles);

    Q_INVOKABLE int notDefinite() const;
    Q_INVOKABLE void setNotDefinite(int newNotDefinite);

    Q_INVOKABLE int  power() const;
    Q_INVOKABLE void setPower(int  newPower);

    Q_INVOKABLE int  time() const;
    Q_INVOKABLE void setTime(int  newTime);

    Q_INVOKABLE int  energy() const;
    Q_INVOKABLE void setEnergy(int  newEnergy);

    Q_INVOKABLE int  heightPre() const;
    Q_INVOKABLE void setHeightPre(int  newHeightPre);

    Q_INVOKABLE int  heightPost() const;
    Q_INVOKABLE void setHeightPost(int  newHeightPost);

    QString mesIP() const;
    void setMesIP(const QString &newMesIP);

    QString deviceIP() const;
    void setDeviceIP(const QString &newDeviceIP);

    int mesPort() const;
    void setMesPort(int newMesPort);

    //qml
    Q_INVOKABLE void setPreEnegy(const QString &value);
    Q_INVOKABLE void setPreAmplitude(const QString &value);
    Q_INVOKABLE void setPreTP(const QString &value);
    Q_INVOKABLE void setPreWP(const QString &value);
    Q_INVOKABLE void setPreTimeMin(const QString &value);
    Q_INVOKABLE void setPreTimeMax(const QString &value);
    Q_INVOKABLE void setPrePowerMin(const QString &value);
    Q_INVOKABLE void setPrePowerMax(const QString &value);
    Q_INVOKABLE void setPreHeightMin(const QString &value);
    Q_INVOKABLE void setPreHeightMax(const QString &value);
    Q_INVOKABLE void setPostHeightMin(const QString &value);
    Q_INVOKABLE void setPostHeightMax(const QString &value);

    QString getPreEnegy() const;
    QString getPreAmplitude() const;
    QString getPreTP() const;
    QString getPreWP() const;
    QString getPreTimeMin() const;
    QString getPreTimeMax() const;
    QString getPrePowerMin() const;
    QString getPrePowerMax() const;
    QString getPreHeightMin() const;
    QString getPreHeightMax() const;
    QString getPostHeightMin() const;
    QString getPostHeightMax() const;

    //modbus
    void setPreEnegyRaw(int value);
    void setPreAmplitudeRaw(int value);
    void setPreTPRaw(int value);
    void setPreWPRaw(int value);
    void setPreTimeMinRaw(int value);
    void setPreTimeMaxRaw(int value);
    void setPrePowerMinRaw(int value);
    void setPrePowerMaxRaw(int value);
    void setPreHeightMinRaw(int value);
    void setPreHeightMaxRaw(int value);
    void setPostHeightMinRaw(int value);
    void setPostHeightMaxRaw(int value);

signals:

    void nameChanged();
    void modelChanged();
    void notifyConnectTypeChanged();
    void notifyConnectStateChanged();

    void idChanged();

    void maxBacthChanged();

    void sampleChanged();

    void heightOptionChanged();

    void lowerLimitChanged();

    void connectIDChanged();

    void goodRateChanged();

    void goodCyclesChanged();

    void suspectCyclesChanged();

    void notDefiniteChanged();

    void powerChanged();

    void timeChanged();

    void energyChanged();

    void heightPreChanged();

    void heightPostChanged();

    void mesIPChanged();

    void deviceIPChanged();

    void mesPortChanged();

    void preEnegyChanged();
    void preAmplitudeChanged();
    void preTPChanged();
    void preWPChanged();
    void preTimeMinChanged();
    void preTimeMaxChanged();
    void prePowerMinChanged();
    void prePowerMaxChanged();
    void preHeightMinChanged();
    void preHeightMaxChanged();
    void postHeightMinChanged();
    void postHeightMaxChanged();

private:
    const int m_id;
    QString m_name;
    QString m_model;
    int m_maxBacth;
    int m_sample;
    int m_lowerLimit;
    int m_heightOption;
    int m_connectID;

    int m_goodRate{0};
    int m_goodCycles{0};
    int m_suspectCycles{0};
    int m_notDefinite{0};

    int  m_power{0};
    int  m_time{0};
    int  m_energy{0};
    // int m_heightPre{0};
    // int m_heightPost{0};
    int  m_heightPre{0};
    int  m_heightPost{0};

    int m_mesPort{0};
    QString m_mesIP;
    QString m_deviceIP;

    DeviceInfoEnum::CONNECT_TYPE    m_iConnectType;
    DeviceInfoEnum::CONNECT_STATE   m_iConnectState;


    int m_preEnegy{0};
    int m_preAmplitude{0};
    int m_preTP{10};
    int m_preWP{150};
    int m_preTimeMin{110};
    int m_preTimeMax{120};
    int m_prePowerMin{0};
    int m_prePowerMax{0};
    int m_preHeightMin{120};
    int m_preHeightMax{340};
    int m_postHeightMin{0};
    int m_postHeightMax{0};
};

#endif // DEVICEINFORMATION_H
