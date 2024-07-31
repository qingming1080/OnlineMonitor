#include "device.h"

#include "model/deviceinformation.h"
#include "model/io.h"
#include "model/manual.h"
#include "model/system.h"
#include "model/trend.h"

#include "signalmanager.h"
#include <QDebug>
#include <QElapsedTimer>
#include "log/localrecord.h"

Device::Device(int welderID, QObject *parent)
    : QObject{parent}, m_welderID(welderID)
{
    QElapsedTimer timer;
    timer.start();

    m_pDeviceInformation  = new DeviceInformation(m_welderID);
    m_pIO                 = new IO(m_welderID);
    m_pManual             = new Manual(m_welderID);
    m_pSystem             = new System(m_welderID);
    m_pTrend              = new Trend(m_welderID);

    QString text = QString("%1号设备_Device_初始化共耗时:%2ms").arg(welderID).arg(timer.elapsed());
    emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), text);
}

DeviceInformation *Device::pDeviceInformation() const
{
    return m_pDeviceInformation;
}

System *Device::pSystem() const
{
    return m_pSystem;
}

IO *Device::pIO() const
{
    return m_pIO;
}

Trend *Device::pTrend() const
{
    return m_pTrend;
}


Manual *Device::pManual() const
{
    return m_pManual;
}
