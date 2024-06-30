#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <QMap>
#include "model/device.h"

///
/// \brief The DeviceManager class : 设备管理
///
class DeviceManager : public QObject
{
    Q_OBJECT
    // 当前设备数量
    Q_PROPERTY(int deviceNum READ deviceNum WRITE setDeviceNum NOTIFY deviceNumChanged)
public:
    static DeviceManager* getInstance();

    /// 已暴露属性
    Q_INVOKABLE int deviceNum() const;
    Q_INVOKABLE void setDeviceNum(int newDeviceNum);    // 不建议前端直接使用

    /// 是否有设备
    Q_INVOKABLE bool hasDevice(int index) const;
    /// 通过设备号获取设备
    Q_INVOKABLE Device *device(int index) const;

    ///
    /// \brief addDevice : 新增一台设备
    ///
    Q_INVOKABLE void addDevice(int index);

signals:

    void deviceChanged();

    void deviceNumChanged();

private:
    explicit DeviceManager(QObject *parent = nullptr);

    void init();

private:
    static DeviceManager* s_pInstance;

    QMap<int, Device *> m_deviceMap;

    int m_deviceNum{0};
};

#endif // DEVICEMANAGER_H
