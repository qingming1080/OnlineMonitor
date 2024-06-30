#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>


class DeviceInformation;

class WeldTrend;
class YieldTrend;

///
/// \brief The Device class : 单个设备
///
class Device : public QObject
{
    Q_OBJECT

    Q_PROPERTY(DeviceInformation *pDeviceInformation READ pDeviceInformation)   // 设备信息

    Q_PROPERTY(WeldTrend *pWeldTrend                 READ pWeldTrend)           // 焊接趋势_折线
    Q_PROPERTY(YieldTrend *pYieldTrend               READ pYieldTrend)          // 良率趋势_折线

public:
    explicit Device(QObject *parent = nullptr);

    Q_INVOKABLE DeviceInformation *pDeviceInformation() const;
    Q_INVOKABLE WeldTrend *pWeldTrend() const;
    Q_INVOKABLE YieldTrend *pYieldTrend() const;

signals:


private:
    DeviceInformation* m_pDeviceInformation{nullptr};   // 设备信息


    WeldTrend*         m_pWeldTrend{nullptr};           // 焊接趋势_折线
    YieldTrend*        m_pYieldTrend{nullptr};          // 良率趋势_折线
};

#endif // DEVICE_H
