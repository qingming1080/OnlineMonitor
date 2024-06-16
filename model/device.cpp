#include "device.h"
#include "model/systeminformation.h"
#include "model/deviceinformation.h"
#include "model/realtimeyield.h"
#include "model/weldresults.h"
#include "model/weldtrend.h"
#include "model/yieldtrend.h"
#include "model/yieldmodel.h"

Device::Device(QObject *parent)
    : QObject{parent}
{
    m_pSystemInformation  = new SystemInformation();
    m_pDeviceInformation  = new DeviceInformation();
    m_pRealTimeYield      = new RealTimeYield();
    m_pWeldResults        = new WeldResults();
    m_pWeldTrend          = new WeldTrend();
    m_pYieldTrend         = new YieldTrend();
    m_pYieldModel         = new YieldModel();
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

WeldTrend *Device::pWeldTrend() const
{
    return m_pWeldTrend;
}

YieldTrend *Device::pYieldTrend() const
{
    return m_pYieldTrend;
}

YieldModel *Device::pYieldModel() const
{
    return m_pYieldModel;
}
