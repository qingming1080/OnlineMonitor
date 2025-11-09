#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <QMap>
#include "device.h"
#include "define.h"
#include "modbus/hbmodbusclient.h"

///
/// \brief The DeviceManager class : 设备管理
///
class DeviceManager : public QObject
{
    Q_OBJECT
    // 设备指针列表
    Q_PROPERTY(QList<Device*> DeviceList READ getDeviceList WRITE setDeviceList NOTIFY notifyDeviceListChanged)
    // 选中设备索引
    Q_PROPERTY(int SelectedDeviceIndex READ getSelectedDeviceIndex WRITE setSelectedDeviceIndex  NOTIFY notifySelectedDeviceIndexChanged)
    // 设备数量
    Q_PROPERTY(int DeviceCounter READ getDeviceCounter WRITE setDeviceCounter NOTIFY notifyDeviceCounterChanged)


public:
    static DeviceManager* getInstance();

    QList<Device *> getDeviceList() const;
    void setDeviceList(const QList<Device*> &list);

    void setSelectedDeviceIndex(const int &index);
    int getSelectedDeviceIndex() const;

    int getDeviceCounter() const;
    void setDeviceCounter(int counter);

    //获取指针
    // Device* getDeviceByNetworkID(int networkID);

    // Device* getDeviceByRs232ID(int rs232ID);

    Q_INVOKABLE bool addDevice();

    Q_INVOKABLE bool removeDevice();

    Q_INVOKABLE bool saveDevice();

    

    ///
    /// \brief getPasswordLevel : 获取密码权能等级
    /// \param password : 密码
    /// \return : 等级 0_无效 1_ROOT 2_USER
    ///
    Q_INVOKABLE int getPasswordLevel(QString password);

    Q_INVOKABLE void setUserPassword(QString newPassword);

    Q_INVOKABLE QString getHistoryName(int welderID);


    //manual
    // Q_INVOKABLE void startManualMode(int deviceID);  // 开启手动模式
    // Q_INVOKABLE void stopManualMode();              // 关闭手动模式
    // QList<QString> manualDataList() const;          // 获取手动模式数据

    // void syncDevicesToModbus();

signals:
    void notifyDeviceListChanged();
    void notifySelectedDeviceIndexChanged();
    void notifyDeviceCounterChanged();

public slots:
    void slotNotifyDeviceStatusChanged(int welderId, const DEVICE_STATUS &status);
    void slotNotifyWeldResultComing(int welderId, const HBModbusClient::MODBUS_WELD_RESULT& data);

private:
    explicit DeviceManager(QObject *parent = nullptr);
    bool InitDeviceList();
private:
    static DeviceManager* m_ptrInstance;
    int m_iSelectedDeviceIndex;
    QList<Device*> m_listDevices;
    int m_iDeviceCounter;

    // int m_manualModeDeviceID = -1;  // 当前处于手动模式的设备 ID（-1 表示未开启）
    // QList<QString> m_manualDataList;  // 存储手动模式下的数据
};

#endif // DEVICEMANAGER_H
