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

    m_ptrDevice     = new DeviceInformation(m_WelderID);
    m_ptrManual     = new Manual(m_WelderID);
    m_ptrProduction = new Production(m_WelderID);
    m_ptrTrend      = new Trend(m_WelderID);

    // QString text = QString("%1号设备_Device_初始化共耗时:%2ms").arg(welderID).arg(timer.elapsed());
    //                    emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), text);
}

Device::~Device()
{
    delete m_ptrDevice;
    m_ptrDevice = nullptr;
    delete m_ptrManual;
    m_ptrManual = nullptr;
    delete m_ptrProduction;
    m_ptrProduction = nullptr;
    delete m_ptrTrend;
    m_ptrTrend = nullptr;
}

Trend *Device::pTrend() const
{
    return m_ptrTrend;
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

DeviceInformation* Device::getDeviceObj() const
{
    return m_ptrDevice;
}

void Device::setDeviceObj(const DeviceInformation *object)
{
    if (m_ptrDevice != object) {
        m_ptrDevice = const_cast<DeviceInformation*>(object);
        emit notifyDeviceObjChanged();
    }
}

Manual *Device::getManualObj() const
{
    return m_ptrManual;
}

void Device::setManualObj(const Manual *object)
{
    if (m_ptrManual != object) {
        m_ptrManual = const_cast<Manual*>(object);
        emit notifyManualObjChanged();
    }
}

Production *Device::getProductionObj() const
{
    return m_ptrProduction;
}

void Device::setProductionObj(const Production *object)
{
    if (m_ptrProduction != object) {
        m_ptrProduction = const_cast<Production*>(object);
        emit notifyProductionObjChanged();
    }
}

bool Device::SaveDevice()
{
    m_ptrDevice->SaveDevice();
    return true;
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

void Device::NotifyWeldResultComing(const HBModbusClient::MODBUS_WELD_RESULT &data)
{
    if(m_ptrProduction->getModelStatus() == true)
    {
        if(IsProductionPresetChanged(data) == false)
            m_ptrProduction->AppendNewRecordComming(data);
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
        }
    }
    else
    {
        m_ptrManual->AppendNewRecordComming(data);
    }
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
