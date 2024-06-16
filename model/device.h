#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>


class SystemInformation;
class DeviceInformation;
class RealTimeYield;
class WeldResults;
class WeldTrend;
class YieldTrend;
class YieldModel;

///
/// \brief The Device class : 单个设备
///
class Device : public QObject
{
    Q_OBJECT

    Q_PROPERTY(DeviceInformation *pDeviceInformation READ pDeviceInformation)   // 设备信息
    Q_PROPERTY(RealTimeYield *pRealTimeYield         READ pRealTimeYield )      // 实时良率
    Q_PROPERTY(WeldResults *pWeldResults             READ pWeldResults)         // 焊接结果
    Q_PROPERTY(WeldTrend *pWeldTrend                 READ pWeldTrend)           // 焊接趋势_折线
    Q_PROPERTY(YieldTrend *pYieldTrend               READ pYieldTrend)          // 良率趋势_折线
    Q_PROPERTY(YieldModel *pYieldModel               READ pYieldModel)          // 生产模型

public:
    explicit Device(QObject *parent = nullptr);

    /// 已暴露属性
    Q_INVOKABLE SystemInformation *pSystemInformation() const;
    Q_INVOKABLE DeviceInformation *pDeviceInformation() const;
    Q_INVOKABLE RealTimeYield *pRealTimeYield() const;
    Q_INVOKABLE WeldResults *pWeldResults() const;
    Q_INVOKABLE WeldTrend *pWeldTrend() const;
    Q_INVOKABLE YieldTrend *pYieldTrend() const;
    Q_INVOKABLE YieldModel *pYieldModel() const;

signals:


    void pDeviceInformationChanged();

    void pRealTimeYieldChanged();

    void pWeldResultsChanged();

    void pWeldTrendChanged();

    void pYieldTrendChanged();

    void pYieldModelChanged();

private:
    SystemInformation* m_pSystemInformation{nullptr};   // 系统消息
    DeviceInformation* m_pDeviceInformation{nullptr};   // 设备信息
    RealTimeYield*     m_pRealTimeYield{nullptr};       // 实时良率
    WeldResults*       m_pWeldResults{nullptr};         // 焊接结果
    WeldTrend*         m_pWeldTrend{nullptr};           // 焊接趋势_折线
    YieldTrend*        m_pYieldTrend{nullptr};          // 良率趋势_折线
    YieldModel*        m_pYieldModel{nullptr};          // 生产模型
};

#endif // DEVICE_H
