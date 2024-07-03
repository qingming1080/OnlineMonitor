#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>


class DeviceInformation;
class IOModel;
class Manual;
class Production;
class System;

class WeldTrend;
class YieldTrend;

///
/// \brief The Device class : 单个设备
///
class Device : public QObject
{
    Q_OBJECT

    Q_PROPERTY(DeviceInformation *pDeviceInformation READ pDeviceInformation)   // 设备信息
    Q_PROPERTY(IOModel *pIOModel                     READ pIOModel)             // IO表格
    Q_PROPERTY(Manual *pManual                       READ pManual)              // Manual表格
    Q_PROPERTY(Production *pProduction               READ pProduction)          // Production表格
    Q_PROPERTY(System *pSystem                       READ pSystem)              // System表格

    Q_PROPERTY(WeldTrend *pWeldTrend                 READ pWeldTrend)           // 焊接趋势_折线
    Q_PROPERTY(YieldTrend *pYieldTrend               READ pYieldTrend)          // 良率趋势_折线

public:
    explicit Device(int welderID = 0, QObject *parent = nullptr);

    Q_INVOKABLE DeviceInformation *pDeviceInformation() const;
    Q_INVOKABLE IOModel *pIOModel() const;
    Q_INVOKABLE Manual *pManual() const;

    Q_INVOKABLE WeldTrend *pWeldTrend() const;
    Q_INVOKABLE YieldTrend *pYieldTrend() const;


    Production *pProduction() const;

    System *pSystem() const;
    void setPSystem(System *newPSystem);

signals:


    void pProductionChanged();

    void pSystemChanged();

private:
    const int m_welderID;

    DeviceInformation* m_pDeviceInformation{nullptr};   // 设备信息
    IOModel* m_pIOModel;
    Manual* m_pManual;
    Production* m_pProduction;
    System* m_pSystem;

    WeldTrend*         m_pWeldTrend{nullptr};           // 焊接趋势_折线
    YieldTrend*        m_pYieldTrend{nullptr};          // 良率趋势_折线



};

#endif // DEVICE_H
