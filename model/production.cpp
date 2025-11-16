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
    memset((void*)&m_DBProduction, 0, sizeof(DataBaseManager::DB_PRODUCTION));
    m_DBProduction.BatchCount = m_DBModel.BatchCount;
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
     return UtilityFunction::getInstance()->RawValueToString(m_DBProduction.TriggerPressure, 10.0, 1);
}

void Production::setTriggertPressure(const QString& triggertPressure)
{
    int iTriggertPressure = UtilityFunction::getInstance()->StringToRawValue(triggertPressure, 10.0);
    if (m_DBProduction.TriggerPressure != iTriggertPressure)
    {
        m_DBProduction.TriggerPressure = iTriggertPressure;
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

    // int FinalResult;                    // 产品状态 0_合格 1_次品 2_可疑

    m_DBProduction.WelderID = m_WelderID;
    m_DBProduction.CreateTime = data.DateTime.toSecsSinceEpoch();
    m_DBProduction.SerialNumber = "NAN";
    m_DBProduction.CycleCount = data.CycleCount;
    m_DBProduction.BatchCount++;
    m_DBProduction.Energy = data.Energy;
    m_DBProduction.Amplitude = data.Amplitude;
    m_DBProduction.TriggerPressure = data.TriggerPressure;
    m_DBProduction.WeldPressure = data.WeldingPressure;
    m_DBProduction.WeldTime = data.WeldTime;
    m_DBProduction.PeakPower = data.PeakPower;
    m_DBProduction.Preheight = data.Preheight;
    m_DBProduction.PostHeight = data.PostHeight;
    m_DBProduction.Force = 0;
    m_DBProduction.Residual = 0;
    if(data.WeldAlarm != 0)
        m_DBProduction.FinalResult = 1;
    else
        m_DBProduction.FinalResult = 0;

    DataBaseManager::getInstance()->insertProductionRow(m_DBProduction);
    DataBaseManager::getInstance()->updateModelRecord(m_DBModel.id, m_DBModel);
}

void Production::SetModel(const DataBaseManager::DB_MODEL &model)
{
    m_DBModel.id = model.id;
    m_DBModel.WelderId = model.WelderId;
    m_DBModel.CreateTime = model.CreateTime;
    m_DBModel.Energy = model.Energy;
    m_DBModel.Amplitude = model.Amplitude;
    m_DBModel.TriggerPressure = model.TriggerPressure;
    m_DBModel.WeldPressure = model.WeldPressure;

    m_DBModel.WeldTime.Alpha = model.WeldTime.Alpha;
    m_DBModel.WeldTime.Beta = model.WeldTime.Beta;
    m_DBModel.PeakPower.Alpha = model.PeakPower.Alpha;
    m_DBModel.PeakPower.Beta = model.PeakPower.Beta;
    m_DBModel.Preheight.Alpha = model.Preheight.Alpha;
    m_DBModel.Preheight.Beta = model.Preheight.Beta;
    m_DBModel.PostHeight.Alpha = model.PostHeight.Alpha;
    m_DBModel.PostHeight.Beta = model.PostHeight.Beta;

    m_DBModel.PeelForce.P00 = model.PeelForce.P00;
    m_DBModel.PeelForce.P10 = model.PeelForce.P10;
    m_DBModel.PeelForce.P01 = model.PeelForce.P01;
    m_DBModel.PeelForce.P20 = model.PeelForce.P20;
    m_DBModel.PeelForce.P11 = model.PeelForce.P11;
    m_DBModel.PeelForce.P02 = model.PeelForce.P02;
    m_DBModel.Residual.P00 = model.Residual.P00;
    m_DBModel.Residual.P10 = model.Residual.P10;
    m_DBModel.Residual.P01 = model.Residual.P01;
    m_DBModel.Residual.P20 = model.Residual.P20;
    m_DBModel.Residual.P11 = model.Residual.P11;
    m_DBModel.Residual.P02 = model.Residual.P02;

    m_DBModel.Centralized.TimeMean = model.Centralized.TimeMean;
    m_DBModel.Centralized.TimeStd = model.Centralized.TimeStd;
    m_DBModel.Centralized.PowerMean = model.Centralized.PowerMean;
    m_DBModel.Centralized.PowerStd = model.Centralized.PowerStd;
    m_DBModel.Centralized.ForceMean = model.Centralized.ForceMean;
    m_DBModel.Centralized.ResidualMean = model.Centralized.ResidualMean;
    
    m_DBModel.SampleCount = model.SampleCount;
    m_DBModel.BatchCount = model.BatchCount;
    m_DBModel.isAvailable = model.isAvailable;
}
