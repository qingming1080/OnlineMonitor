#include "device.h"

#include "model/deviceinformation.h"
#include "model/iomodel.h"
#include "model/manual.h"
#include "model/production.h"
#include "model/system.h"

#include "model/weldtrend.h"
#include "model/yieldtrend.h"

Device::Device(int welderID, QObject *parent)
    : QObject{parent}, m_welderID(welderID)
{
    m_pDeviceInformation  = new DeviceInformation(m_welderID);
    m_pIOModel            = new IOModel(m_welderID);
    m_pManual             = new Manual(m_welderID);
    m_pProduction         = new Production(m_welderID);
    m_pSystem             = new System(m_welderID);

    m_pWeldTrend          = new WeldTrend();
    m_pYieldTrend         = new YieldTrend();
}

DeviceInformation *Device::pDeviceInformation() const
{
    return m_pDeviceInformation;
}

WeldTrend *Device::pWeldTrend() const
{
    return m_pWeldTrend;
}

YieldTrend *Device::pYieldTrend() const
{
    return m_pYieldTrend;
}

Production *Device::pProduction() const
{
    return m_pProduction;
}

System *Device::pSystem() const
{
    return m_pSystem;
}

Manual *Device::pManual() const
{
    return m_pManual;
}


IOModel *Device::pIOModel() const
{
    return m_pIOModel;
}
