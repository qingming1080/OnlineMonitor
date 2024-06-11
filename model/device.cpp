#include "device.h"
#include "model/systeminformation.h"
#include "model/deviceinformation.h"
#include "model/realtimeyield.h"
#include "model/weldresults.h"

Device::Device(QObject *parent)
    : QObject{parent}
{
    m_pSystemInformation  = new SystemInformation();
    m_pDeviceInformation  = new DeviceInformation();
    m_pRealTimeYield      = new RealTimeYield();
    m_pWeldResults        = new WeldResults();
}

SystemInformation *Device::pSystemInformation() const
{
    return m_pSystemInformation;
}

DeviceInformation *Device::pDeviceInformation() const
{
    return m_pDeviceInformation;
}

RealTimeYield *Device::pRealTimeYield() const
{
    return m_pRealTimeYield;
}

WeldResults *Device::pWeldResults() const
{
    return m_pWeldResults;
}
