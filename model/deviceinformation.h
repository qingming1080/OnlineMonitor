#ifndef DEVICEINFORMATION_H
#define DEVICEINFORMATION_H

#include <QObject>
#include "qmlenum.h"

///
/// \brief The DeviceInformation class : 设备信息_对应表格Configuration
///
class DeviceInformation : public QObject
{
    Q_OBJECT
    // 焊机ID
    Q_PROPERTY(int id                               READ id            /*WRITE setId */             NOTIFY idChanged)
    // 焊机名称
    Q_PROPERTY(QString name                         READ name          WRITE setName            NOTIFY nameChanged)
    // 焊机型号
    Q_PROPERTY(QString model                        READ model         WRITE setModel           NOTIFY modelChanged)
    // 最大生产批量
    Q_PROPERTY(int maxBacth                         READ maxBacth      WRITE setMaxBacth        NOTIFY maxBacthChanged)
    // 学习样本数
    Q_PROPERTY(int sample                           READ sample        WRITE setSample          NOTIFY sampleChanged)
    // 良率下限
    Q_PROPERTY(int lowerLimit                       READ lowerLimit    WRITE setLowerLimit      NOTIFY lowerLimitChanged)
    // 高度模式
    Q_PROPERTY(int heightOption                     READ heightOption  WRITE setHeightOption    NOTIFY heightOptionChanged)

    // 连接方式
    Q_PROPERTY(QmlEnum::_CONNECTTYPE connectType    READ connectType   WRITE setConnectType     NOTIFY connectTypeChanged)
    // 连接方式ID
    Q_PROPERTY(int connectID                        READ connectID     WRITE setConnectID       NOTIFY connectIDChanged)

    /// 2024/04/07  实时良率暴露
    // 实时良率
    Q_PROPERTY(int goodRate                         READ goodRate       WRITE setGoodRate       NOTIFY goodRateChanged)
    // 合格
    Q_PROPERTY(int goodCycles                       READ goodCycles     WRITE setGoodCycles     NOTIFY goodCyclesChanged)
    // 可疑
    Q_PROPERTY(int suspectCycles                    READ suspectCycles  WRITE setSuspectCycles  NOTIFY suspectCyclesChanged)
    // 次品
    Q_PROPERTY(int notDefinite                      READ notDefinite    WRITE setNotDefinite    NOTIFY notDefiniteChanged)

    /// 2024/04/07  焊接结果暴露
    // 焊接结果_功率
    Q_PROPERTY(int power                            READ power          WRITE setPower          NOTIFY powerChanged)
    // 焊接结果_时间
    Q_PROPERTY(int time                             READ time           WRITE setTime           NOTIFY timeChanged)
    // 焊接结果_能量
    Q_PROPERTY(int energy                           READ energy         WRITE setEnergy         NOTIFY energyChanged)
    // 焊接结果_焊前高度
    Q_PROPERTY(int heightPre                        READ heightPre      WRITE setHeightPre      NOTIFY heightPreChanged)
    // 焊接结果_焊后高度
    Q_PROPERTY(int heightPost                       READ heightPost     WRITE setHeightPost     NOTIFY heightPostChanged)

    /// 2024/04/07 设备状态 暴露
    // 设备状态(生产中，待机等)
    Q_PROPERTY(QString state                        READ state          WRITE setState          NOTIFY stateChanged)
public:
    explicit DeviceInformation(int welderID = 0, QObject *parent = nullptr);

    Q_INVOKABLE QString name() const;
    Q_INVOKABLE void setName(const QString &newName);

    Q_INVOKABLE QString model() const;
    Q_INVOKABLE void setModel(const QString &newModel);

    Q_INVOKABLE QmlEnum::_CONNECTTYPE connectType() const;
    Q_INVOKABLE void setConnectType(const QmlEnum::_CONNECTTYPE &newconnectType);

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

    Q_INVOKABLE QString state() const;
    Q_INVOKABLE void setState(const QString &newState);

    Q_INVOKABLE int goodRate() const;
    Q_INVOKABLE void setGoodRate(int newGoodRate);

    Q_INVOKABLE int goodCycles() const;
    Q_INVOKABLE void setGoodCycles(int newGoodCycles);

    Q_INVOKABLE int suspectCycles() const;
    Q_INVOKABLE void setSuspectCycles(int newSuspectCycles);

    Q_INVOKABLE int notDefinite() const;
    Q_INVOKABLE void setNotDefinite(int newNotDefinite);

    Q_INVOKABLE int power() const;
    Q_INVOKABLE void setPower(int newPower);

    Q_INVOKABLE int time() const;
    Q_INVOKABLE void setTime(int newTime);

    Q_INVOKABLE int energy() const;
    Q_INVOKABLE void setEnergy(int newEnergy);

    Q_INVOKABLE int heightPre() const;
    Q_INVOKABLE void setHeightPre(int newHeightPre);

    Q_INVOKABLE int heightPost() const;
    Q_INVOKABLE void setHeightPost(int newHeightPost);

signals:

    void nameChanged();
    void modelChanged();
    void connectTypeChanged();
    void stateChanged();

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

private:
    const int m_id;
    QString m_name{};
    QString m_model{};
    int m_maxBacth;
    int m_sample;
    int m_lowerLimit;
    int m_heightOption;
    QmlEnum::_CONNECTTYPE m_connectType;
    int m_connectID;

    int m_goodRate{95};
    int m_goodCycles{12};
    int m_suspectCycles{13};
    int m_notDefinite{14};

    int m_power{0};
    int m_time{0};
    int m_energy{0};
    int m_heightPre{0};
    int m_heightPost{0};

    QString m_state{"未连接"};
};

#endif // DEVICEINFORMATION_H
