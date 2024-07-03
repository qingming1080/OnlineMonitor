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

    // 设备状态(生产中，待机等)
    Q_PROPERTY(QString state                        READ state         WRITE setState           NOTIFY stateChanged)
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

    QString state() const;
    void setState(const QString &newState);

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

    QString m_state;
};

#endif // DEVICEINFORMATION_H
