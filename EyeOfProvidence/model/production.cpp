#include "production.h"
#include "tools/utilityfunction.h"
#include "history.h"
#include "historyenum.h"
#include "provienceEE/providenceEE.h"
#include "DataBase/databasehelper.h"
#include "message.h"
#include "modbus/hbmodbusclient.h"

Production::Production(int welderID, QObject *parent)
    :QObject{parent}, m_WelderID(welderID)
{

    m_iGoodRate = 0.0;
    m_iGoodCycleCount = 0;
    m_iDefectiveCycleCount = 0;
    m_iSuspectCycleCount = 0;
    m_iTotalCycleCount = 0;
    m_DBModel.isAvailable = false;
    if(DataBaseManager::getInstance()->getModelRecord(m_WelderID, m_DBModel) == false)
    {
        setModelStatus(false);
        setEnergySetting(0);
        setAmpSetting(0);
        setTPSetting(0);
        setWPSetting(0);
        m_DBModel = DataBaseManager::DB_MODEL();
    }
    else
    {
        setModelStatus(m_DBModel.isAvailable);
        setEnergySetting(m_DBModel.Energy);
        setAmpSetting(m_DBModel.Amplitude);
        setTPSetting(m_DBModel.TriggerPressure);
        setWPSetting(m_DBModel.WeldPressure);
    }
    // Avoid using memset on structs that contain non-POD types (like QString).
    // Zeroing object memory with memset breaks QString/Qt internals and causes crashes.
    m_DBProduction = DataBaseManager::DB_PRODUCTION();
    m_DBProduction.SerialNumber = QString();
    m_DBProduction.BatchCount = m_DBModel.BatchCount;
    setGoodCycleCount("0");

#ifdef REMARK_FWC
    connect(this, &Production::signalAppendOperation, DataBaseManager::getInstance()->getDataBaseHelper(),
            &DataBaseHelper::appendOperation);
#endif
}

float Production::getGoodRate() const
{
    return m_iGoodRate;
}

void Production::setGoodRate(const float &rate)
{
    if (m_iGoodRate != rate)
    {
        m_iGoodRate = rate;
        emit notifyGoodRateChanged();
    }
}

QString Production::getGoodCycleCount() const
{
    return QString::number(m_iGoodCycleCount);
}

int Production::GetGoodCycleCount() const
{
    return m_iGoodCycleCount;
}

void Production::setGoodCycleCount(const QString &count)
{
    bool isOk = false;
    int iCount = count.toInt(&isOk);
    if (isOk && m_iGoodCycleCount != iCount)
    {
        m_iGoodCycleCount = iCount;
        emit notifyGoodCycleCountChanged();
    }
}

QString Production::getSuspectCycleCount() const
{
    return QString::number(m_iSuspectCycleCount);
}

int Production::GetSuspectCycleCount() const
{
    return m_iSuspectCycleCount;
}

void Production::setSuspectCycleCount(const QString &count)
{
    bool isOk = false;
    int iCount = count.toInt(&isOk);
    if (isOk && m_iSuspectCycleCount != iCount)
    {
        m_iSuspectCycleCount = iCount;
        emit notifySuspectCycleCountChanged();
    }
}

QString Production::getDefectiveCycleCount() const
{
    return QString::number(m_iDefectiveCycleCount);
}

int Production::GetDefectiveCycleCount() const
{
    return m_iDefectiveCycleCount;
}

void Production::setDefectiveCycleCount(const QString &count)
{
    bool isOk = false;
    int iCount = count.toInt(&isOk);
    if (isOk && m_iDefectiveCycleCount != iCount)
    {
        m_iDefectiveCycleCount = iCount;
        emit notifyDefectiveCycleCountChanged();
    }
}

QString Production::getTotalCycleCount() const
{
    return QString::number(m_iTotalCycleCount);
}

int Production::GetTotalCycleCount() const
{
    return m_iTotalCycleCount;
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
    m_DBModel.BatchCount++;
    setEnergy(QString::number(data.Energy));
    setAmplitude(QString::number(data.Amplitude));
    QString strTriggerPressure = UtilityFunction::getInstance()->RawValueToString(data.TriggerPressure, 10, 1);
    setTriggertPressure(strTriggerPressure);
    QString strWeldPressure = UtilityFunction::getInstance()->RawValueToString(data.WeldingPressure, 10, 1);
    setWeldPressure(strWeldPressure);
    QString strWeldTime = UtilityFunction::getInstance()->RawValueToString(data.WeldTime, 100, 2);
    setWeldTime(strWeldTime);
    setPeakPower(QString::number(data.PeakPower));
    QString strPreheight = UtilityFunction::getInstance()->RawValueToString(data.Preheight, 100, 2);
    setPreheight(strPreheight);
    QString strPostHeight = UtilityFunction::getInstance()->RawValueToString(data.PostHeight, 100, 2);
    setPostHeight(strPostHeight);


    ProvidenceEE::getInstance()->SetRelevantParam();
    ProvidenceEE::getInstance()->SetProcessPara(m_DBModel, true);
    ProvidenceEE::getInstance()->SetPolynomialCoefficient(m_DBModel);
    ProvidenceEE::getInstance()->SetCentralized(m_DBModel);
    ProvidenceEE::getInstance()->SetProcess();

    ProvidenceEE::getInstance()->UpdateNewComingValue(GenericLearning::TIME, m_DBProduction.WeldTime);
    ProvidenceEE::getInstance()->UpdateNewComingValue(GenericLearning::POWER, m_DBProduction.PeakPower);
    ProvidenceEE::getInstance()->UpdateNewComingValue(GenericLearning::PREHEIGHT, m_DBProduction.Preheight);
    ProvidenceEE::getInstance()->UpdateNewComingValue(GenericLearning::POSTHEIGHT, m_DBProduction.PostHeight);

    double peelForce;
    double residule;
    ProvidenceEE::getInstance()->PredictFromAIModel(GenericLearning::PEEL_FORCE,
                                          m_DBProduction.WeldTime,
                                          m_DBProduction.PeakPower,
                                          peelForce);
    m_DBProduction.Force = static_cast<int>(peelForce);
    ProvidenceEE::getInstance()->PredictFromAIModel(GenericLearning::RESIDUAL,
                                          m_DBProduction.WeldTime,
                                          m_DBProduction.PeakPower,
                                          residule);
    m_DBProduction.Residual = static_cast<int>(residule);
    if(data.WeldAlarm == 0)
        m_DBProduction.FinalResult = HistoryEnum::GOOD;
    else
        m_DBProduction.FinalResult = HistoryEnum::DEFECT;

    if(m_DBProduction.FinalResult == HistoryEnum::GOOD)
    {
        if(ProvidenceEE::getInstance()->GetSPCGoodnessResult() == true)
        {
            if(m_DBProduction.WeldTime > (m_DBModel.WeldTime.Alpha + 3 * m_DBModel.WeldTime.Beta))
                m_DBProduction.FinalResult = HistoryEnum::SUSPECT;
            else if(m_DBProduction.PeakPower < (m_DBModel.PeakPower.Alpha - 3 * m_DBModel.PeakPower.Beta))
                m_DBProduction.FinalResult = HistoryEnum::SUSPECT;
            // if((m_DBProduction.Force < m_iForceThreshold) || (m_DBProduction.Residual < m_iResidualThreshold))
            //     m_DBProduction.FinalResult = HistoryEnum::DEFECT;
        }
        else
            m_DBProduction.FinalResult = HistoryEnum::DEFECT;
    }

    int goodCount = GetGoodCycleCount();
    int suspectCount = GetSuspectCycleCount();
    int defectCount = GetDefectiveCycleCount();
    int totalCount = GetTotalCycleCount();
    switch(m_DBProduction.FinalResult)
    {

    case HistoryEnum::GOOD:
        goodCount++;
        HBModbusClient::getInstance()->setDeviceIOStatus(m_WelderID, false, false);
        break;
    case HistoryEnum::SUSPECT:
        suspectCount++;
        HBModbusClient::getInstance()->setAlarmLedStatus(true);
        HBModbusClient::getInstance()->setDeviceIOStatus(m_WelderID, false, true);
        Message::getInstance()->addMessage(m_WelderID, MESSAGE_ENUM::SUSPICIOUS);
        break;
    case HistoryEnum::DEFECT:
        defectCount++;
        HBModbusClient::getInstance()->setAlarmLedStatus(true);
        HBModbusClient::getInstance()->setDeviceIOStatus(m_WelderID, true, false);
        Message::getInstance()->addMessage(m_WelderID, MESSAGE_ENUM::DEFECTIVE);
        break;
    default:
        break;
    }

    totalCount++;
    setGoodCycleCount(QString::number(goodCount));
    setSuspectCycleCount(QString::number(suspectCount));
    setDefectiveCycleCount(QString::number(defectCount));
    setTotalCycleCount(QString::number(totalCount));
    float goodRate = 0.0;
    if(totalCount != 0)
        goodRate = static_cast<float>(goodCount + suspectCount) / totalCount * 100;
    setGoodRate(goodRate);

    // TODO need to move these two line code into movetothread process.
    // need to emit signal to device manager the record insert into qlist
#ifdef REMARK_FWC
    emit signalAppendOperation(m_DBProduction, m_DBModel);
#else
    DataBaseManager::getInstance()->insertProductionRow(m_DBProduction);
    DataBaseManager::getInstance()->updateModelRecord(m_DBModel.id, m_DBModel);
#endif
    // *************************************************************************

    History::getInstance()->AppendNewRecordComming(m_DBProduction);
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

int Production::getProductionMaxBacth() const
{
    return m_DBModel.BatchCount;
}

int Production::getYieldRateLowerLimit() const
{
    return m_iGoodRate;
}

void Production::setProductionMaxBacth(const int maxBatch)
{
    if (m_DBModel.BatchCount != maxBatch)
    {
        m_DBModel.BatchCount = maxBatch;
        emit notifyProductionMaxBacthChanged();
    }
}

void Production::setYieldRateLowerLimit(const int limit)
{
    if (m_iGoodRate != limit)
    {
        m_iGoodRate = limit;
        emit notifyYieldRateLowerLimitChanged();
    }
}

int Production::getForceThreshold() const
{
    return m_iForceThreshold;
}

void Production::setForceThreshold(const int threshold)
{
    if (m_iForceThreshold != threshold)
    {
        m_iForceThreshold = threshold;
        emit notifyForceThresholdChanged();
    }
}

int Production::getResidualThreshold() const
{
    return m_iResidualThreshold;
}

void Production::setResidualThreshold(const int threshold)
{
    if (m_iResidualThreshold != threshold)
    {
        m_iResidualThreshold = threshold;
        emit notifyResidualThresholdChanged();
    }
}   
