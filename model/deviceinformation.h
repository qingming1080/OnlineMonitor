#ifndef DEVICEINFORMATION_H
#define DEVICEINFORMATION_H

#include <QObject>

///
/// \brief The DeviceInformation class : 设备信息
///
class DeviceInformation : public QObject
{
    Q_OBJECT
    // 设备名称
    Q_PROPERTY(QString name             READ name          WRITE setName            NOTIFY nameChanged)
    // 设备型号
    Q_PROPERTY(QString model            READ model         WRITE setModel           NOTIFY modelChanged)
    // 设备连接方式
    Q_PROPERTY(QString connectMethod    READ connectMethod WRITE setConnectMethod   NOTIFY connectMethodChanged)
    // 设置状态
    Q_PROPERTY(QString state            READ state         WRITE setState           NOTIFY stateChanged)
public:
    explicit DeviceInformation(QObject *parent = nullptr);

    /// 已暴露属性
    Q_INVOKABLE QString name() const;
    Q_INVOKABLE QString model() const;
    Q_INVOKABLE QString connectMethod() const;
    Q_INVOKABLE QString state() const;
    Q_INVOKABLE void setName(const QString &newName);
    Q_INVOKABLE void setModel(const QString &newModel);
    Q_INVOKABLE void setConnectMethod(const QString &newConnectMethod);
    Q_INVOKABLE void setState(const QString &newState);

signals:

    void nameChanged();
    void modelChanged();
    void connectMethodChanged();
    void stateChanged();

private:
    // 设备名称
    QString m_name{};
    // 设备信号
    QString m_model{};
    // 连接方式
    QString m_connectMethod{};
    // 设备状态
    QString m_state{};

};

#endif // DEVICEINFORMATION_H
