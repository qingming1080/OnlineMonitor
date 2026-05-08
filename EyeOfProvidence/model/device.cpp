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
    : QObject{parent}, m_WelderID(welderID)
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

bool Device::isIORejectStatus() const
{
    return isIOReject;
}

void Device::setIORejectStatus(bool status)
{
    if(isIOReject != status)
    {
        isIOReject = status;
        void notifyIOResetChanged();
    }
}

bool Device::isIOSuspectStatus() const
{
    return isIOSuspect;
}

void Device::setIOSuspectStatus(bool status)
{
    if(isIOSuspect != status)
    {
        isIOSuspect = status;
        void notifyIOSuspectChanged();
    }
}

bool Device::isIOResetStatus() const
{
    return isIOReset;
}

void Device::setIOResetStatus(bool status)
{
    if(isIOReset != status)
    {
        isIOReset = status;
        void notifyIOResetChanged();
    }
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
    float amplitude_lower = static_cast<float>(0.95 * amplitude);
    float amplitude_upper = static_cast<float>(1.05 * amplitude);
    float triggerPressure_lower = static_cast<float>(0.95 * triggerPressure);
    float triggerPressure_upper = static_cast<float>(1.05 * triggerPressure);
    float weldPressure_lower = static_cast<float>(0.95 * weldPressure);
    float weldPressure_upper = static_cast<float>(1.05 * weldPressure);

    if(data.Amplitude == 0)
        return false;
    if(data.TriggerPressure == 0)
        return false;
    if(data.WeldingPressure == 0)
        return false;
    if(data.Energy == 0)
        return false;
    if(data.WeldAlarm != 0)
        return false;

    if(amplitude != data.Amplitude)
    {
        if((data.Amplitude < amplitude_lower) || (data.Amplitude > amplitude_upper))
        {
            m_ptrProduction->setModelStatus(false);
            bResult = true;
        }
    }
    else
        bResult = false;
    if(bResult == true)
        return bResult;

    if(triggerPressure != data.TriggerPressure)
    {
        if((data.TriggerPressure < triggerPressure_lower) || (data.TriggerPressure > triggerPressure_upper))
        {
            m_ptrProduction->setModelStatus(false);
            bResult = true;
        }
    }
    else
        bResult = false;
    if(bResult == true)
        return bResult;

    if(weldPressure != data.WeldingPressure)
    {
        if((data.WeldingPressure < weldPressure_lower) || (data.WeldingPressure > weldPressure_upper))
        {
            m_ptrProduction->setModelStatus(false);
            bResult = true;
        }
    }
    else
        bResult = false;
    if(bResult == true)
        return bResult;

    if(energy != data.Energy)
    {
        if((data.Energy < energy_lower) || (data.Energy > energy_upper))
        {
            m_ptrProduction->setModelStatus(false);
            bResult = true;
        }
    }
    else
        bResult = false;
        
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
    float amplitude_lower = static_cast<float>(1.05 * amplitude);
    float amplitude_upper = static_cast<float>(1.05 * amplitude);
    float triggerPressure_lower = static_cast<float>(0.95 * triggerPressure);
    float triggerPressure_upper = static_cast<float>(1.05 * triggerPressure);
    float weldPressure_lower = static_cast<float>(0.95 * weldPressure);
    float weldPressure_upper = static_cast<float>(1.05 * weldPressure);
    if(data.Amplitude == 0)
        return bResult;
    if(data.TriggerPressure == 0)
        return bResult;
    if(data.WeldingPressure == 0)
        return bResult;
    if(data.Energy == 0)
        return bResult;
    if((data.Amplitude < amplitude_lower) || (data.Amplitude > amplitude_upper))
    {
        m_ptrProduction->setModelStatus(false);
        bResult = true;
    }
    else if((data.TriggerPressure < triggerPressure_lower) || (data.TriggerPressure > triggerPressure_upper))
    {
        m_ptrProduction->setModelStatus(false);
        bResult = true;
    }
    else if((data.WeldingPressure < weldPressure_lower) || (data.WeldingPressure > weldPressure_upper))
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
    m_ptrTrend->SetModel(model);
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
    Q_UNUSED(object);
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
    Q_UNUSED(object)
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
    Q_UNUSED(object)
#endif
}

bool Device::SaveDevice()
{
    if(m_ptrDevice->SaveDevice() == true)
    {
        m_WelderID = m_ptrDevice->getWelderID();
        return true;
    }
    else
        return false;
}

bool Device::RemoveDevice()
{
    return m_ptrDevice->RemoveDevice();
}

bool Device::UpdateDevice()
{
    return m_ptrDevice->UpdateDevice();
}

int Device::getWelderID() const
{
    return m_WelderID;
}

void Device::NotifyDeviceStatusChanged(const HBModbusClient::DEVICE_STATUS &status)
{
    m_ptrDevice->setConnectState(status.IsDeviceDataStatus);
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
            DataBaseManager::DB_PRODUCTION production = m_ptrProduction->GetProductionResult();
            m_ptrTrend->AppendProduction(production);
            emit notifyWeldTrendChanged(m_WelderID);
            // qDebug() << "Production data coming";
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
            emit notifyPresetChanged(m_WelderID);
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
        emit notifyPresetChanged(m_WelderID);
    }
}
