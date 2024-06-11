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
    // 四个设备
    Q_PROPERTY(Device *device_1 READ device_1)
    Q_PROPERTY(Device *device_2 READ device_1)
    Q_PROPERTY(Device *device_3 READ device_1)
    Q_PROPERTY(Device *device_4 READ device_1)
    // 当前设备数量
    Q_PROPERTY(int deviceNum READ deviceNum WRITE setDeviceNum NOTIFY deviceNumChanged)
public:
    static DeviceManager* getInstance();

    /// 已暴露属性
    Q_INVOKABLE Device *device_1() const;
    Q_INVOKABLE Device *device_2() const;
    Q_INVOKABLE Device *device_3() const;
    Q_INVOKABLE Device *device_4() const;
    Q_INVOKABLE int deviceNum() const;
    Q_INVOKABLE void setDeviceNum(int newDeviceNum);    // 不建议前端直接使用

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
