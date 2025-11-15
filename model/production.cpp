#include "production.h"
#include "tools/utilityfunction.h"
Production::Production(int welderID, ProvidenceEE *_providenceEE, QObject *parent)
    :QObject{parent}, m_WelderID(welderID), m_ptrProvidenceEE(_providenceEE)
{

    m_iGoodRate = 90;
    m_iGoodCycleCount = 333;
    m_iDefectiveCycleCount = 1;
    m_iSuspectCycleCount = 2;
    if(DataBaseManager::getInstance()->getModelRecord(m_WelderID, m_DBModel) == false)
    {
        setModelStatus(false);
        setEnergySetting(0);
        setAmpSetting(0);
        setTPSetting(0);
        setWPSetting(0);
    }
    else
    {
        setModelStatus(m_DBModel.isAvailable);
        setEnergySetting(m_DBModel.Energy);
        setAmpSetting(m_DBModel.Amplitude);
        setTPSetting(m_DBModel.TriggerPressure);
        setWPSetting(m_DBModel.WeldPressure);
    }
    memset(&m_DBProduction, 0, sizeof(DataBaseManager::DB_PRODUCTION));
}

QString Production::getGoodRate() const
{
    return QString::number(m_iGoodRate);
}

void Production::setGoodRate(const QString &rate)
{
    bool isOk;
    int iRate = rate.toInt(&isOk);
    if (isOk && m_iGoodRate != iRate)
    {
        m_iGoodRate = iRate;
        emit notifyGoodRateChanged();
    }
}

QString Production::getGoodCycleCount() const
{
    return QString::number(m_iGoodCycleCount);
}

void Production::setGoodCycleCount(const QString &count)
{
    bool isOk = false;
    int iCount = count.toInt(&isOk);
    if (isOk && m_iGoodCycleCount != iCount)
    {
        m_iGoodCycleCount = iCount;
        m_iTotalCycleCount = m_iGoodCycleCount + m_iDefectiveCycleCount + m_iSuspectCycleCount;
        setTotalCycleCount(QString::number(m_iTotalCycleCount));
        m_iGoodCycleCount = static_cast<int>(m_iGoodCycleCount / m_iTotalCycleCount * 100);
        setGoodRate(QString::number(m_iGoodCycleCount));
        emit notifyGoodCycleCountChanged();
    }
}

QString Production::getSuspectCycleCount() const
{
    return QString::number(m_iSuspectCycleCount);
}

void Production::setSuspectCycleCount(const QString &count)
{
    bool isOk = false;
    int iCount = count.toInt(&isOk);
    if (isOk && m_iSuspectCycleCount != iCount)
    {
        m_iSuspectCycleCount = iCount;
        m_iTotalCycleCount = m_iGoodCycleCount + m_iDefectiveCycleCount + m_iSuspectCycleCount;
        setTotalCycleCount(QString::number(m_iTotalCycleCount));
        emit notifySuspectCycleCountChanged();
    }
}

QString Production::getDefectiveCycleCount() const
{
    return QString::number(m_iDefectiveCycleCount);
}

void Production::setDefectiveCycleCount(const QString &count)
{
    bool isOk = false;
    int iCount = count.toInt(&isOk);
    if (isOk && m_iDefectiveCycleCount != iCount)
    {
        m_iDefectiveCycleCount = iCount;
        m_iTotalCycleCount = m_iGoodCycleCount + m_iDefectiveCycleCount + m_iSuspectCycleCount;
        setTotalCycleCount(QString::number(m_iTotalCycleCount));
        emit notifyDefectiveCycleCountChanged();
    }
}

QString Production::getTotalCycleCount() const
{
    return QString::number(m_iTotalCycleCount);
}

void Production::setTotalCycleCount(const QString &count)
{
    bool isOk = false;
    int iCount = count.toInt(&isOk);
    if (isOk && m_iTotalCycleCount != iCount)
    {
        m_iTotalCycleCount = iCount;
        emit notifyTotalCycleCountChanged();
    }
}

QString Production::getPeakPower() const
{
    return QString::number(m_DBProduction.PeakPower);
}

void Production::setPeakPower(const QString &power)
{
    bool isOk = false;
    int iPower = power.toInt(&isOk);
    if (isOk && m_DBProduction.PeakPower != iPower)
    {
        m_DBProduction.PeakPower = iPower;
        emit notifyPeakPowerChanged();
    }
}

QString Production::getWeldTime() const
{
    return UtilityFunction::getInstance()->RawValueToString(m_DBProduction.WeldTime, 100, 2);
}

void Production::setWeldTime(const QString &time)
{
    int iTime = UtilityFunction::getInstance()->StringToRawValue(time, 100);
    if (m_DBProduction.WeldTime != iTime)
    {
        m_DBProduction.WeldTime = iTime;
        emit notifyWeldTimeChanged();
    }   
}

QString Production::getEnergy() const
{
    return QString::number(m_DBProduction.Energy);
}

void Production::setEnergy(const QString &energy)
{
    bool isOk = false;
    int iEnergy = energy.toInt(&isOk);
    if (isOk && m_DBProduction.Energy != iEnergy)
    {
        m_DBProduction.Energy = iEnergy;
        emit notifyEnergyChanged();
    }
}

QString Production::getPreheight() const
{
    return UtilityFunction::getInstance()->RawValueToString(m_DBProduction.Preheight, 100, 2);
}

void Production::setPreheight(const QString &height)
{
    int iPreheight = UtilityFunction::getInstance()->StringToRawValue(height, 100);
    if (m_DBProduction.Preheight != iPreheight)
    {
        m_DBProduction.Preheight = iPreheight;
        emit notifyPreheightChanged();
    }
}

QString Production::getPostHeight() const
{
    return UtilityFunction::getInstance()->RawValueToString(m_DBProduction.PostHeight, 100, 2);
}

void Production::setPostHeight(const QString& height)
{
    int iPostHeight = UtilityFunction::getInstance()->StringToRawValue(height, 100);
    if (m_DBProduction.PostHeight != iPostHeight)
    {
        m_DBProduction.PostHeight = iPostHeight;
        emit notifyPostHeightChanged();
    }
}

QString Production::getAmplitude() const
{
    return QString::number(m_DBProduction.Amplitude);
}

void Production::setAmplitude(const QString &amplitude)
{
    bool isOk = false;
    int iAmplitude = amplitude.toInt(&isOk);
    if (isOk && m_DBProduction.Amplitude != iAmplitude)
    {
        m_DBProduction.Amplitude = iAmplitude;
        emit notifyAmplitudeChanged();
    }
}

QString Production::getWeldPressure() const
{
    return UtilityFunction::getInstance()->RawValueToString(m_DBProduction.WeldPressure, 10.0, 1);
}

void Production::setWeldPressure(const QString& weldPressure)
{
    int iWeldPressure = UtilityFunction::getInstance()->StringToRawValue(weldPressure, 10.0);
    if (m_DBProduction.WeldPressure != iWeldPressure)
    {
        m_DBProduction.WeldPressure = iWeldPressure;
        emit notifyWeldPressureChanged();
    }
}

QString Production::getTriggertPressure() const
{
     return UtilityFunction::getInstance()->RawValueToString(m_DBProduction.TriggertPressure, 10.0, 1);
}

void Production::setTriggertPressure(const QString& triggertPressure)
{
    int iTriggertPressure = UtilityFunction::getInstance()->StringToRawValue(triggertPressure, 10.0);
    if (m_DBProduction.TriggertPressure != iTriggertPressure)
    {
        m_DBProduction.TriggertPressure = iTriggertPressure;
        emit notifyTriggertPressureChanged();
    }
}

int Production::getEnergySetting() const
{
    return m_DBModel.Energy;
}

void Production::setEnergySetting(const int energy)
{
    if(m_DBModel.Energy != energy)
    {
        m_DBModel.Energy = energy;
        emit notifyEnergySettingChanged();
    }
}

int Production::getAmpSetting() const
{
    return m_DBModel.Amplitude;
}

void Production::setAmpSetting(const int amp)
{
    if(m_DBModel.Amplitude != amp)
    {
        m_DBModel.Amplitude = amp;
        emit notifyAmpSettingChanged();
    }
}

int Production::getTPSetting() const
{
    return m_DBModel.TriggerPressure;
}

void Production::setTPSetting(const int tp)
{
    if(m_DBModel.TriggerPressure != tp)
    {
        m_DBModel.TriggerPressure = tp;
        emit notifyTPSettingChanged();
    }
}

int Production::getWPSetting() const
{
    return m_DBModel.WeldPressure;
}

void Production::setWPSetting(const int wp)
{
    if(m_DBModel.WeldPressure != wp)
    {
        m_DBModel.WeldPressure = wp;
        emit notifyWPSettingChanged();
    }
}

bool Production::getModelStatus() const
{
    return m_DBModel.isAvailable;
}

void Production::setModelStatus(const bool status)
{
    if(m_DBModel.isAvailable != status)
    {
        m_DBModel.isAvailable = status;
        emit notifyModelStatusChanged();
    }
}

void Production::AppendNewRecordComming(const HBModbusClient::MODBUS_WELD_RESULT &data)
{

}
