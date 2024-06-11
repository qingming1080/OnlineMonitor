#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>


class SystemInformation;
class DeviceInformation;
class RealTimeYield;
class WeldResults;

///
/// \brief The Device class : 单个设备
///
class Device : public QObject
{
    Q_OBJECT

    Q_PROPERTY(DeviceInformation *pDeviceInformation READ pDeviceInformation)   // 设备信息
    Q_PROPERTY(SystemInformation *pSystemInformation READ pSystemInformation)   // 系统消息
    Q_PROPERTY(RealTimeYield *pRealTimeYield         READ pRealTimeYield )      // 实时良率
    Q_PROPERTY(WeldResults *pWeldResults             READ pWeldResults)         // 焊接结果
public:
    explicit Device(QObject *parent = nullptr);

    /// 已暴露属性
    Q_INVOKABLE SystemInformation *pSystemInformation() const;
    Q_INVOKABLE DeviceInformation *pDeviceInformation() const;
    Q_INVOKABLE RealTimeYield *pRealTimeYield() const;
    Q_INVOKABLE WeldResults *pWeldResults() const;

signals:


    void pDeviceInformationChanged();

    void pRealTimeYieldChanged();

    void pWeldResultsChanged();

private:
    SystemInformation* m_pSystemInformation{nullptr};   // 系统消息
    DeviceInformation* m_pDeviceInformation{nullptr};   // 设备信息
    RealTimeYield*     m_pRealTimeYield{nullptr};       // 实时良率
    WeldResults*       m_pWeldResults{nullptr};         // 焊接结果

};

#endif // DEVICE_H
