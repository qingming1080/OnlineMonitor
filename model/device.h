#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>


class DeviceInformation;
class IO;
class IOModel;
class Manual;
class System;

class Trend;

///
/// \brief The Device class : 单个设备
///
class Device : public QObject
{
    Q_OBJECT

    Q_PROPERTY(DeviceInformation *pDeviceInformation READ pDeviceInformation)   // 设备信息
    Q_PROPERTY(IO *pIO                               READ pIO)                  // IO
    Q_PROPERTY(Manual *pManual                       READ pManual)              // Manual表格
    Q_PROPERTY(System *pSystem                       READ pSystem)              // System表格
    Q_PROPERTY(Trend *pTrend                         READ pTrend)               // 折线

public:
    explicit Device(int welderID = 0, QObject *parent = nullptr);

    Q_INVOKABLE DeviceInformation *pDeviceInformation() const;
    Q_INVOKABLE Manual *pManual() const;
    Q_INVOKABLE System *pSystem() const;
    Q_INVOKABLE IO *pIO() const;
    Q_INVOKABLE Trend *pTrend() const;

    Q_INVOKABLE void test();
signals:


    void pProductionChanged();

    void pSystemChanged();

    void pYieldTrendChanged();
    void pIOChanged();

    void pTrendChanged();

private:
    const int m_welderID;

    DeviceInformation* m_pDeviceInformation{nullptr};   // 设备信息
    IO* m_pIO;
    Manual* m_pManual;
    System* m_pSystem;

    Trend* m_pTrend;

};

#endif // DEVICE_H
