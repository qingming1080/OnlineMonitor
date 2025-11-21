#include "device.h"

#include "model/deviceinformation.h"
#include "model/manual.h"
#include "model/trend.h"
#include "model/production.h"
#include "tools/utilityfunction.h"

#include <QDebug>
#include <QPointF>
#
/// TEST 2024_08_18

Device::Device(int welderID, QObject *parent)
    : QObject{parent}, m_WelderID(welderID),plotIndex(0)
{
    // QElapsedTimer timer;
    // timer.start();
    // TODO Need to use smart pointer to manage these pointers?
#ifndef REMARK_FWC
    m_ptrDevice         = new DeviceInformation(m_WelderID);
    m_ptrManual         = new Manual(m_WelderID);
    m_ptrProduction     = new Production(m_WelderID);
    m_ptrTrend          = new Trend(m_WelderID);
#else
    m_ptrDevice = std::make_shared<DeviceInformation>(m_WelderID);
    m_ptrManual = std::make_shared<Manual>(m_WelderID);
    m_ptrProduction = std::make_shared<Production>(m_WelderID);
    m_ptrTrend = std::make_shared<Trend>(m_WelderID);
#endif
    connect(m_ptrManual.get(), &Manual::notifyTrainingProcessFinished, this, &Device::slotNotifyTrainingProcessFinished);

    // QString text = QString("%1号设备_Device_初始化共耗时:%2ms").arg(welderID).arg(timer.elapsed());
    //                    emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), text);
}

Device::~Device()
{
    disconnect(m_ptrManual.get(), &Manual::notifyTrainingProcessFinished, this, &Device::slotNotifyTrainingProcessFinished);
#ifndef REMARK_FWC
    if(m_ptrManual != nullptr)
    {
        delete m_ptrManual;
        m_ptrManual = nullptr;
    }
    if(m_ptrProduction != nullptr)
    {
        delete m_ptrProduction;
        m_ptrProduction = nullptr;
    }
    if(m_ptrTrend != nullptr)
    {
        delete m_ptrTrend;
        m_ptrTrend = nullptr;
    }
    if(m_ptrDevice != nullptr)
    {
        delete m_ptrDevice;
        m_ptrDevice = nullptr;
    }
#endif
}

Trend *Device::getTrend() const
{
#ifdef REMARK_FWC
    return m_ptrTrend.get();
#else
    return m_ptrTrend;
#endif
}

int Device::getPlotIndex() const {
    return plotIndex;
}

void Device::incrementPlotIndex() {
    plotIndex++;
}

bool Device::IsProductionPresetChanged(const HBModbusClient::MODBUS_WELD_RESULT &data)
{
    bool bResult = false;
    int energy = m_ptrProduction->getEnergySetting();
    int amplitude = m_ptrProduction->getAmpSetting();
    int triggerPressure = m_ptrProduction->getTPSetting();
    int weldPressure = m_ptrProduction->getWPSetting();
    float energy_lower = static_cast<float>(0.95 * energy);
    float energy_upper = static_cast<float>(1.05 * energy);
    if(amplitude != data.Amplitude)
    {
        m_ptrProduction->setModelStatus(false);
        bResult = true;
    }
    else if(triggerPressure != data.TriggerPressure)
    {
        m_ptrProduction->setModelStatus(false);
        bResult = true;
    }
    else if(weldPressure != data.WeldingPressure)
    {
        m_ptrProduction->setModelStatus(false);
        bResult = true;
    }
    else if((energy != data.Energy) && (data.WeldAlarm == 0))
    {
        if((data.Energy < energy_lower) || (data.Energy > energy_upper))
        {
            m_ptrProduction->setModelStatus(false);
            bResult = true;
        }
    }
    else
    {
        bResult = false;
    }
    return bResult;
}

bool Device::IsProductionPresetChanged(const HBModbusClient::WELD_PRESET &data)
{
    bool bResult = false;
    int energy = m_ptrProduction->getEnergySetting();
    int amplitude = m_ptrProduction->getAmpSetting();
    int triggerPressure = m_ptrProduction->getTPSetting();
    int weldPressure = m_ptrProduction->getWPSetting();
    float energy_lower = static_cast<float>(0.95 * energy);
    float energy_upper = static_cast<float>(1.05 * energy);
    if(amplitude != data.Amplitude)
    {
        m_ptrProduction->setModelStatus(false);
        bResult = true;
    }
    else if(triggerPressure != data.TriggerPressure)
    {
        m_ptrProduction->setModelStatus(false);
        bResult = true;
    }
    else if(weldPressure != data.WeldingPressure)
    {
        m_ptrProduction->setModelStatus(false);
        bResult = true;
    }
    else if((data.Energy < energy_lower) || (data.Energy > energy_upper))
    {
        m_ptrProduction->setModelStatus(false);
        bResult = true;
    }
    else
    {
        bResult = false;
    }
    return bResult;
}

void Device::slotNotifyTrainingProcessFinished(DataBaseManager::DB_MODEL &model)
{
    m_ptrProduction->SetModel(model);
}

DeviceInformation* Device::getDeviceObj() const
{
#ifndef REMARK_FWC
    return m_ptrDevice;
#else
    return m_ptrDevice.get();
#endif
}

void Device::setDeviceObj(const DeviceInformation *object)
{
#ifndef REMARK_FWC
    if (m_ptrDevice != object) {
        m_ptrDevice = const_cast<DeviceInformation*>(object);
        emit notifyDeviceObjChanged();
    }
#else

#endif
}

Manual *Device::getManualObj() const
{
#ifndef REMARK_FWC
    return m_ptrManual;
#else
    return m_ptrManual.get();
#endif
}

void Device::setManualObj(const Manual *object)
{
#ifndef REMARK_FWC
    if (m_ptrManual != object) {
        m_ptrManual = const_cast<Manual*>(object);
        emit notifyManualObjChanged();
    }
#else

#endif
}

Production *Device::getProductionObj() const
{
#ifndef REMARK_FWC
    return m_ptrProduction;
#else
    return m_ptrProduction.get();
#endif
}

void Device::setProductionObj(const Production *object)
{
#ifndef REMARK_FWC
    if (m_ptrProduction != object) {
        m_ptrProduction = const_cast<Production*>(object);
        emit notifyProductionObjChanged();
    }

#else

#endif
}

bool Device::SaveDevice()
{
    return  m_ptrDevice->SaveDevice();
}

bool Device::RemoveDevice()
{
    return m_ptrDevice->RemoveDevice();
}

int Device::getWelderID() const
{
    return m_WelderID;
}

void Device::NotifyDeviceStatusChanged(const HBModbusClient::DEVICE_STATUS &status)
{
    m_ptrDevice->setConnectState(status.IsDeviceStatus || status.IsDeviceDataStatus);
}

void Device::NotifyModbusStatusChanged(int targetWelderId)
{
    m_ptrDevice->setDeviceConfigure(targetWelderId);
}

bool Device::NotifyWeldResultComing(const HBModbusClient::MODBUS_WELD_RESULT &data)
{
    qDebug() << "New data coming";
    bool isPresetChanged = false;
    int MaxModelSamples = m_ptrDevice->GetMaxModelSamples();
    m_ptrManual->setMaxModelSamples(MaxModelSamples);
    int ProductionMaxBacth = m_ptrDevice->GetProductionMaxBacth();
    m_ptrProduction->setProductionMaxBacth(ProductionMaxBacth);
    int YieldRateLowerLimit = m_ptrDevice->GetYieldRateLowerLimit();
    m_ptrProduction->setYieldRateLowerLimit(YieldRateLowerLimit);
    int ForceThreshold = m_ptrDevice->GetForceThreshold();
    m_ptrProduction->setForceThreshold(ForceThreshold);
    int Residual = m_ptrDevice->GetResidualThreshold();
    m_ptrProduction->setResidualThreshold(Residual);

    if(m_ptrProduction->getModelStatus() == true)
    {
        isPresetChanged = IsProductionPresetChanged(data);
        if(isPresetChanged == false)
        {
            m_ptrProduction->AppendNewRecordComming(data);
            m_ptrTrend->AppendWeldPoint(data.CycleCount, data.PeakPower, data.WeldTime, data.Preheight, data.PostHeight);
            emit notifyWeldTrendChanged(m_WelderID);
            qDebug() << "Production data coming";
        }
        else
        {
            QString strEnergy = UtilityFunction::getInstance()->RawValueToString(data.Energy, 1, 0);
            m_ptrManual->setEnergySetting(strEnergy);
            QString strAmplitude = UtilityFunction::getInstance()->RawValueToString(data.Amplitude, 1, 0);
            m_ptrManual->setAmplitudeSetting(strAmplitude);
            QString strTriggerPressure = UtilityFunction::getInstance()->RawValueToString(data.TriggerPressure, 10, 1);
            m_ptrManual->setTriggerPressureSetting(strTriggerPressure);
            QString strWeldPressure = UtilityFunction::getInstance()->RawValueToString(data.WeldingPressure, 10, 1);
            m_ptrManual->setWeldPressureSetting(strWeldPressure);
            m_ptrManual->AppendNewRecordComming(data);
            // qDebug() << "Preset has been Changed";
        }
    }
    else
    {
        m_ptrManual->AppendNewRecordComming(data);
        // qDebug() << "Manual New data coming";
    }
    return isPresetChanged;
}

void Device::NotifyPresetSettingChanged(const HBModbusClient::WELD_PRESET &data)
{
    if(m_ptrProduction->getModelStatus() == true)
    {
        if(IsProductionPresetChanged(data) == true)
        {
            QString strEnergy = UtilityFunction::getInstance()->RawValueToString(data.Energy, 1, 0);
            m_ptrManual->setEnergySetting(strEnergy);
            QString strAmplitude = UtilityFunction::getInstance()->RawValueToString(data.Amplitude, 1, 0);
            m_ptrManual->setAmplitudeSetting(strAmplitude);
            QString strTriggerPressure = UtilityFunction::getInstance()->RawValueToString(data.TriggerPressure, 10, 1);
            m_ptrManual->setTriggerPressureSetting(strTriggerPressure);
            QString strWeldPressure = UtilityFunction::getInstance()->RawValueToString(data.WeldingPressure, 10, 1);
            m_ptrManual->setWeldPressureSetting(strWeldPressure);
        }
    }
    else
    {
        QString strEnergy = UtilityFunction::getInstance()->RawValueToString(data.Energy, 1, 0);
        m_ptrManual->setEnergySetting(strEnergy);
        QString strAmplitude = UtilityFunction::getInstance()->RawValueToString(data.Amplitude, 1, 0);
        m_ptrManual->setAmplitudeSetting(strAmplitude);
        QString strTriggerPressure = UtilityFunction::getInstance()->RawValueToString(data.TriggerPressure, 10, 1);
        m_ptrManual->setTriggerPressureSetting(strTriggerPressure);
        QString strWeldPressure = UtilityFunction::getInstance()->RawValueToString(data.WeldingPressure, 10, 1);
        m_ptrManual->setWeldPressureSetting(strWeldPressure);
    }
}
