#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <QMap>
#include "model/device.h"
#include "qmlenum.h"
///
/// \brief The DeviceManager class : 设备管理
///
class DeviceManager : public QObject
{
    Q_OBJECT
    // 设备指针列表
    Q_PROPERTY(QList<Device *> deviceList READ deviceList  NOTIFY deviceListChanged)
    // 设备数量
    Q_PROPERTY(int deviceNum READ deviceNum  NOTIFY deviceNumChanged)
public:
    static DeviceManager* getInstance();

    Q_INVOKABLE QList<Device *> deviceList() const;

    ///
    /// \brief addDevice : 新增一台设备
    ///
    Q_INVOKABLE void addDevice(const int &maxBacth, const int &sample, const int &lowerLimit, const int &port, const QString &targetIp, const QString &localIp, const int &heightOption, const QString &name, const QString &model, const int &connectType, const int &id);

    ///
    /// \brief removeDevice : 删除一台设备
    ///
    Q_INVOKABLE void removeDevice(int welderID);

    Q_INVOKABLE int deviceNum() const;

    ///
    /// \brief getPasswordLevel : 获取密码权能等级
    /// \param password : 密码
    /// \return : 等级 0_无效 1_ROOT 2_USER
    ///
    Q_INVOKABLE int getPasswordLevel(QString password);

    Q_INVOKABLE void setUserPassword(QString newPassword);

    Q_INVOKABLE QString getHistoryName(int welderID);

signals:
    void deviceNumChanged();


    void deviceListChanged();

private:
    explicit DeviceManager(QObject *parent = nullptr);

    void init();

private:
    static DeviceManager* s_pInstance;

    int m_deviceNum;

    QList<Device*> m_deviceList;


};

#endif // DEVICEMANAGER_H
