#include "device.h"

#include "model/deviceinformation.h"

#include "model/weldtrend.h"
#include "model/yieldtrend.h"

Device::Device(QObject *parent)
    : QObject{parent}
{
    m_pDeviceInformation  = new DeviceInformation();
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
