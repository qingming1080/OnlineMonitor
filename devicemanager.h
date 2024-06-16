#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
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

    /// 通过设备号获取设备
    Q_INVOKABLE Device *device(int index) const;

    ///
    /// \brief addDevice : 新增一台设备
    ///
    Q_INVOKABLE void addDevice();

signals:

    void deviceChanged();

    void deviceNumChanged();

private:
    explicit DeviceManager(QObject *parent = nullptr);

private:
    static DeviceManager* s_pInstance;

    Device *m_device[4];

    int m_deviceNum{0};


};

#endif // DEVICEMANAGER_H
