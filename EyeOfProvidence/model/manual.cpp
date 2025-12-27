#include "manual.h"
#include "tools/utilityfunction.h"
#include <QDebug>
#include <algorithm>

Manual::Manual(int welderID, QObject *parent)
    : QAbstractListModel{parent}, m_WelderID(welderID)
{
    loadData();

    if(DataBaseManager::getInstance()->getModelRecord(m_WelderID, m_DBModel) == false)
    {
        m_DBModel.id = -1;
        m_DBModel.isAvailable = false;
        setEnergySetting("0");
        setAmplitudeSetting("0");
        setTriggerPressureSetting("0");
        setWeldPressureSetting("0");
    }
    else
    {
        m_DBModel.isAvailable = true;
        setEnergySetting(QString::number(m_DBModel.Energy));
        setAmplitudeSetting(QString::number(m_DBModel.Amplitude));
        QString strTP = UtilityFunction::getInstance()->RawValueToString(m_DBModel.TriggerPressure, 10, 1);
        QString strWP = UtilityFunction::getInstance()->RawValueToString(m_DBModel.WeldPressure, 10, 1);
        setTriggerPressureSetting(strTP);
        setWeldPressureSetting(strWP);
    }
    setCurrentSamples(0);
}

Manual::~Manual()
{
    m_listManualRecords.clear();
}

int Manual::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listManualRecords.size();
}

QVariant Manual::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    int row = index.row();
    DataBaseManager::DB_MANUAL data = m_listManualRecords.at(row);
    switch(role)
    {
    case MANUAL_TABLE::ID:
        return data.Id;
    case MANUAL_TABLE::WELDER_ID:
        return data.WelderId;
    case MANUAL_TABLE::CREATE_TIME:
        return data.CreateTime.toString("hh:mm:ss");
    case MANUAL_TABLE::CYCLE_COUNT:
        return data.CycleCount;
    case MANUAL_TABLE::ENERGY:
        return data.Energy;
    case MANUAL_TABLE::AMPLITUDE:
        return data.Amplitude;
    case MANUAL_TABLE::TRIGGER_PRESSURE:
        return data.TriggerPressure;
    case MANUAL_TABLE::WELD_PRESSURE:
        return data.WeldPressure;
    case MANUAL_TABLE::WELD_TIME:
        return UtilityFunction::getInstance()->RawValueToString(data.WeldTime, 100, 2);
    case MANUAL_TABLE::PEAK_POWER:
        return data.PeakPower;
    case MANUAL_TABLE::PRE_HEIGHT:
        return UtilityFunction::getInstance()->RawValueToString(data.Preheight, 100, 2);
    case MANUAL_TABLE::POST_HEIGHT:
        return UtilityFunction::getInstance()->RawValueToString(data.PostHeight, 100, 2);
    case MANUAL_TABLE::ACTUAL_FORCE:
        return data.ActualForce;
    case MANUAL_TABLE::ACTUAL_RESIDUAL:
        return data.ActualResidual;
    case MANUAL_TABLE::IS_SELECTED:
        return data.IsSelected;
    case MANUAL_TABLE::IS_BY_MANUAL:
        return data.IsAddByManual;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> Manual::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[MANUAL_TABLE::ID]               = "id";
    roles[MANUAL_TABLE::WELDER_ID]        = "welder_id";
    roles[MANUAL_TABLE::CREATE_TIME]      = "create_time";
    roles[MANUAL_TABLE::CYCLE_COUNT]      = "cycle_count";
    roles[MANUAL_TABLE::ENERGY]           = "energy";
    roles[MANUAL_TABLE::AMPLITUDE]        = "amplitude";
    roles[MANUAL_TABLE::TRIGGER_PRESSURE] = "trigger_pressure";
    roles[MANUAL_TABLE::WELD_PRESSURE]    = "weld_pressure";
    roles[MANUAL_TABLE::WELD_TIME]        = "weld_time";
    roles[MANUAL_TABLE::PEAK_POWER]       = "peak_power";
    roles[MANUAL_TABLE::PRE_HEIGHT]       = "preheight";
    roles[MANUAL_TABLE::POST_HEIGHT]      = "postheight";
    roles[MANUAL_TABLE::ACTUAL_FORCE]     = "actual_force";
    roles[MANUAL_TABLE::ACTUAL_RESIDUAL]  = "actual_residual";
    roles[MANUAL_TABLE::IS_SELECTED]      = "is_selected";
    roles[MANUAL_TABLE::IS_BY_MANUAL]     = "is_by_manual";
    return roles;
}

bool Manual::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool bResult = true;
    if(!index.isValid())
        return false;

    int row = index.row();
    switch(role)
    {
    case MANUAL_TABLE::CYCLE_COUNT:
        m_listManualRecords[row].CycleCount = value.toInt();
        qDebug() << "Cycle Count: " << m_listManualRecords[row].CycleCount;
        break;
    case MANUAL_TABLE::ENERGY:
        m_listManualRecords[row].Energy = value.toInt();
        break;
    case MANUAL_TABLE::AMPLITUDE:
        m_listManualRecords[row].Amplitude = value.toInt();
        break;
    case MANUAL_TABLE::TRIGGER_PRESSURE:
        m_listManualRecords[row].TriggerPressure = value.toInt();
        break;
    case MANUAL_TABLE::WELD_PRESSURE:
        m_listManualRecords[row].WeldPressure = value.toInt();
        break;
    case MANUAL_TABLE::WELD_TIME:
        m_listManualRecords[row].WeldTime = value.toInt();
        qDebug() << "Weld Time: " << m_listManualRecords[row].WeldTime;
        break;
    case MANUAL_TABLE::PEAK_POWER:
        m_listManualRecords[row].PeakPower = value.toInt();
        qDebug() << "Peak Power: " << m_listManualRecords[row].PeakPower;
        break;
    case MANUAL_TABLE::PRE_HEIGHT:
        m_listManualRecords[row].Preheight = value.toInt();
        qDebug() << "Preheightr: " << m_listManualRecords[row].Preheight;
        break;
    case MANUAL_TABLE::POST_HEIGHT:
        m_listManualRecords[row].PostHeight = value.toInt();
        qDebug() << "Post Heightr: " << m_listManualRecords[row].PostHeight;
        break;
    case MANUAL_TABLE::ACTUAL_FORCE:
        m_listManualRecords[row].ActualForce = value.toInt();
        break;
    case MANUAL_TABLE::ACTUAL_RESIDUAL:
        m_listManualRecords[row].ActualResidual = value.toInt();
        break;
    case MANUAL_TABLE::IS_SELECTED:
        m_listManualRecords[row].IsSelected = value.toBool();
        emit dataChanged(index, index, {role});
        break;
    case MANUAL_TABLE::IS_BY_MANUAL:
        m_listManualRecords[row].IsAddByManual = value.toBool();
        emit dataChanged(index, index, {role});
        break;
    default:
        bResult =  false;
        break;
    }
    return bResult;
}

void Manual::saveData()
{
    CalibrateModel();
    for(int i = 0; i < m_listManualRecords.size(); ++i)
    {
        if (m_listManualRecords[i].IsSelected)
        {
            if(m_listManualRecords[i].IsNewComming)
                DataBaseManager::getInstance()->insertManualRecord(m_listManualRecords.at(i));
            else
                DataBaseManager::getInstance()->updateManualRecord(m_listManualRecords.at(i).Id, m_listManualRecords.at(i));
        }
        else
            DataBaseManager::getInstance()->removeManualRecord(m_listManualRecords.at(i).Id);
        QModelIndex idx = index(i);
        emit dataChanged(idx, idx, {MANUAL_TABLE::IS_SELECTED});
    }
    if(m_DBModel.id == -1)
    {
        DataBaseManager::getInstance()->insertModelRecord(m_DBModel);
    }
    else
    {
        DataBaseManager::getInstance()->updateModelRecord(m_DBModel.id, m_DBModel);
    }
    emit notifyTrainingProcessFinished(m_DBModel);
}

void Manual::clearData()
{
    beginResetModel();
    m_listManualRecords.clear();
    DataBaseManager::getInstance()->removeManualRecords(m_WelderID);
    endResetModel();
    setCurrentSamples(0);
}

void Manual::loadData()
{
    beginResetModel();  // 通知 QML 模型发生变化
    m_listManualRecords.clear();
    DataBaseManager::getInstance()->getManualRecords(m_WelderID, m_listManualRecords); // 重新加载数据

    // Reverse the list so the newest records appear first in the model
    if (!m_listManualRecords.isEmpty()) {
        std::reverse(m_listManualRecords.begin(), m_listManualRecords.end());
    }

    endResetModel();
}

void Manual::addNewRecordByManual()
{
    beginInsertRows(QModelIndex(), 0, 0);
    DataBaseManager::DB_MANUAL record;
    record.WelderId       = m_WelderID;
    record.CycleCount     = -1;
    record.Energy         = m_DBModel.Energy;
    record.Amplitude      = m_DBModel.Amplitude;
    record.WeldPressure   = m_DBModel.WeldPressure;
    record.ActualForce    = 0;
    record.ActualResidual = 0;
    record.CreateTime     = QDateTime::currentDateTime();
    record.IsSelected     = false;
    record.IsNewComming   = true;
    record.IsAddByManual  = true;
    if(m_listManualRecords.size() == 0)
    {
        record.WeldTime       = 0;
        record.PeakPower      = 0;
        record.Preheight      = 0;
        record.PostHeight     = 0;
    }
    else
    {
        if(m_listManualRecords[0].IsNewComming == true)
        {
            record.WeldTime       = m_listManualRecords[0].WeldTime;
            record.PeakPower      = m_listManualRecords[0].PeakPower;
            record.Preheight      = m_listManualRecords[0].Preheight;
            record.PostHeight     = m_listManualRecords[0].PostHeight;
        }
        else
        {
            record.WeldTime       = 0;
            record.PeakPower      = 0;
            record.Preheight      = 0;
            record.PostHeight     = 0;
        }
    }

    m_listManualRecords.prepend(record);
    endInsertRows();
}

bool Manual::isSettingsValid() const
{
    bool ok;

    double energySetting = getEnergySetting().toDouble(&ok);
    if (!ok || energySetting <= 0.0)
        return false;

    double amplitudeSetting = getAmplitudeSetting().toDouble(&ok);
    if (!ok || amplitudeSetting <= 0.0)
        return false;

    double triggerPressureSetting = getTriggerPressureSetting().toDouble(&ok);
    if (!ok || triggerPressureSetting <= 0.0)
        return false;

    double pressureSetting = getWeldPressureSetting().toDouble(&ok);
    if (!ok || pressureSetting <= 0.0)
        return false;

    return true;
}

bool Manual::CalibrateModel()
{
    if(m_listManualRecords.size() == 0)
        return false;
    GenericLearning::PROCESS_PARAM param[GenericLearning::TOTALPARA];
    GenericLearning::AI_POLYNOMIAL_COEFFICIENT coefficient[GenericLearning::STRENGTH_MAX];
    GenericLearning::CENTRALIZED_PROPERTY centralized;
#if RASPBERRY
    ProvidenceEE::getInstance()->ResetProcess();
    ProvidenceEE::getInstance()->CalibrateSPCProcess(m_listManualRecords);
    ProvidenceEE::getInstance()->CalibrateAIProcess(m_listManualRecords);
    ProvidenceEE::getInstance()->GetSPCProcess(param);
    ProvidenceEE::getInstance()->GetAIProcess(&centralized, coefficient);
#endif
    InitDBModel(param, coefficient, centralized);
    return true;
}

void Manual::InitDBModel(const GenericLearning::PROCESS_PARAM *_param, const GenericLearning::AI_POLYNOMIAL_COEFFICIENT *_coefficient, const GenericLearning::CENTRALIZED_PROPERTY centralized)
{
    m_DBModel.WeldTime.Alpha = _param[GenericLearning::TIME].Alpha;
    m_DBModel.WeldTime.Beta = _param[GenericLearning::TIME].Beta;
    m_DBModel.PeakPower.Alpha = _param[GenericLearning::POWER].Alpha;
    m_DBModel.PeakPower.Beta = _param[GenericLearning::POWER].Beta;
    m_DBModel.Preheight.Alpha = _param[GenericLearning::PREHEIGHT].Alpha;
    m_DBModel.Preheight.Beta = _param[GenericLearning::PREHEIGHT].Beta;
    m_DBModel.PostHeight.Alpha = _param[GenericLearning::POSTHEIGHT].Alpha;
    m_DBModel.PostHeight.Beta = _param[GenericLearning::POSTHEIGHT].Beta;

    m_DBModel.PeelForce.P00 = _coefficient[GenericLearning::STRENGTH0].P00;
    m_DBModel.PeelForce.P01 = _coefficient[GenericLearning::STRENGTH0].P01;
    m_DBModel.PeelForce.P02 = _coefficient[GenericLearning::STRENGTH0].P02;
    m_DBModel.PeelForce.P10 = _coefficient[GenericLearning::STRENGTH0].P10;
    m_DBModel.PeelForce.P11 = _coefficient[GenericLearning::STRENGTH0].P11;
    m_DBModel.PeelForce.P20 = _coefficient[GenericLearning::STRENGTH0].P20;

    m_DBModel.Residual.P00 = _coefficient[GenericLearning::STRENGTH1].P00;
    m_DBModel.Residual.P01 = _coefficient[GenericLearning::STRENGTH1].P01;
    m_DBModel.Residual.P02 = _coefficient[GenericLearning::STRENGTH1].P02;
    m_DBModel.Residual.P10 = _coefficient[GenericLearning::STRENGTH1].P10;
    m_DBModel.Residual.P11 = _coefficient[GenericLearning::STRENGTH1].P11;
    m_DBModel.Residual.P20 = _coefficient[GenericLearning::STRENGTH1].P20;

    m_DBModel.Centralized.TimeMean = centralized.TimeMean;
    m_DBModel.Centralized.TimeStd = centralized.TimeStd;
    m_DBModel.Centralized.PowerMean = centralized.PowerMean;
    m_DBModel.Centralized.PowerStd = centralized.PowerStd;
    m_DBModel.Centralized.ForceMean = centralized.ForceMean;
    m_DBModel.Centralized.ResidualMean = centralized.ResidualMean;

    m_DBModel.SampleCount = _param[GenericLearning::TIME].SampleCount;
    m_DBModel.BatchCount = 0;

    m_DBModel.WelderId = m_WelderID;                       // 焊机id
    m_DBModel.CreateTime = QDateTime::currentDateTime();               // 创建时间
    m_DBModel.Energy = GetEnergySetting();                         // 能量
    m_DBModel.Amplitude = GetAmplitudeSetting();                      // 振幅
    m_DBModel.TriggerPressure = GetTriggerPressureSetting();                // 焊接压力
    m_DBModel.WeldPressure = GetWeldPressureSetting();                   // 触发压力
    m_DBModel.isAvailable = true;
    qDebug() << "Set PROCESS_PARAM: ";
    qDebug() << " Time.Alpha: " << m_DBModel.WeldTime.Alpha
             << " Time.Beta: " << m_DBModel.WeldTime.Beta
             << " Power.Alpha: " << m_DBModel.PeakPower.Alpha
             << " Power.Beta: " << m_DBModel.PeakPower.Beta
             << " Preheight.Alpha: " << m_DBModel.Preheight.Alpha
             << " Preheight.Beta: " << m_DBModel.Preheight.Beta
             << " Postheight.Alpha: " << m_DBModel.PostHeight.Alpha
             << " Postheight.Beta: " << m_DBModel.PostHeight.Beta;

    qDebug() << "CENTRALIZED_PROPERTY: ";
    qDebug() << " Centralized.ForceMean: " << m_DBModel.Centralized.ForceMean
             << " Centralized.ResidualMean: " << m_DBModel.Centralized.ResidualMean
             << " Centralized.PowerMean: " << m_DBModel.Centralized.PowerMean
             << " Centralized.PowrStd: " << m_DBModel.Centralized.PowerStd
             << " Centralized.TimeMean: " << m_DBModel.Centralized.TimeMean
             << " Centralized.TimeStd: " << m_DBModel.Centralized.TimeStd;

    qDebug() << "SAMPLE COUNT: " << m_DBModel.SampleCount;

    qDebug() << "FORCE_COEFFICIENT: ";
    qDebug() << " Strength0.P00: " << m_DBModel.PeelForce.P00
             << " Strength0.P01: " << m_DBModel.PeelForce.P01
             << " Strength0.P02: " << m_DBModel.PeelForce.P02
             << " Strength0.P10: " << m_DBModel.PeelForce.P10
             << " Strength0.P11: " << m_DBModel.PeelForce.P11
             << " Strength0.P20: " << m_DBModel.PeelForce.P20;

    qDebug() << "RESIDUAL_COEFFICIENT: ";
    qDebug() << " Strength1.P00: " << m_DBModel.Residual.P00
             << " Strength1.P01: " << m_DBModel.Residual.P01
             << " Strength1.P02: " << m_DBModel.Residual.P02
             << " Strength1.P10: " << m_DBModel.Residual.P10
             << " Strength1.P11: " << m_DBModel.Residual.P11
             << " Strength1.P20: " << m_DBModel.Residual.P20;
}

void Manual::AppendNewRecordComming(const HBModbusClient::MODBUS_WELD_RESULT &data)
{
    beginInsertRows(QModelIndex(), 0, 0);
    DataBaseManager::DB_MANUAL record;
    record.WelderId       = m_WelderID;
    record.CycleCount     = data.CycleCount;
    record.Energy         = data.Energy;
    record.Amplitude      = data.Amplitude;
    record.WeldPressure   = data.WeldingPressure;
    record.WeldTime       = data.WeldTime;
    record.PeakPower      = data.PeakPower;
    record.Preheight      = data.Preheight;
    record.PostHeight     = data.PostHeight;
    record.ActualForce    = 0;
    record.ActualResidual = 0;
    record.CreateTime     = data.DateTime;
    record.IsSelected     = true;
    record.IsNewComming   = true;

    m_listManualRecords.prepend(record);
    endInsertRows();

    int samples = getCurrentSamples();
    samples++;
    setCurrentSamples(samples);
}

QString Manual::getEnergySetting() const
{
    return QString::number(m_DBModel.Energy);
}

int Manual::GetEnergySetting() const
{
    return m_DBModel.Energy;
}

void Manual::setEnergySetting(const QString &value)
{
    bool isOK = false;
    int iEnergy = value.toInt(&isOK);
    if(isOK == false)
        return;
    if (m_DBModel.Energy != iEnergy)
    {
        m_DBModel.Energy = iEnergy;
        emit notifyEnergySettingChanged();
    }
}

QString Manual::getAmplitudeSetting() const
{
    return QString::number(m_DBModel.Amplitude);
}

int Manual::GetAmplitudeSetting() const
{
    return m_DBModel.Amplitude;
}

void Manual::setAmplitudeSetting(const QString &value)
{
    bool isOK = false;
    int iAmplitude = value.toInt(&isOK);
    if(isOK == false)
        return;
    if (m_DBModel.Amplitude != iAmplitude)
    {
        m_DBModel.Amplitude = iAmplitude;
        emit notifyAmplitudeSettingChanged();
    }
}

QString Manual::getTriggerPressureSetting() const
{
    return UtilityFunction::getInstance()->RawValueToString(m_DBModel.TriggerPressure, 10.0, 1);
}

int Manual::GetTriggerPressureSetting() const
{
    return m_DBModel.TriggerPressure;
}

void Manual::setTriggerPressureSetting(const QString &value)
{
    int iTriggerPressure = UtilityFunction::getInstance()->StringToRawValue(value, 10.0);
    if (m_DBModel.TriggerPressure != iTriggerPressure)
    {
        m_DBModel.TriggerPressure = iTriggerPressure;
        emit notifyTriggerPressureSettingChanged();
    }
}

QString Manual::getWeldPressureSetting() const
{
    return UtilityFunction::getInstance()->RawValueToString(m_DBModel.WeldPressure, 10.0, 1);
}

int Manual::GetWeldPressureSetting() const
{
    return m_DBModel.WeldPressure;
}

void Manual::setWeldPressureSetting(const QString &value)
{
    int iWeldPressure = UtilityFunction::getInstance()->StringToRawValue(value, 10.0);
    if (m_DBModel.WeldPressure != iWeldPressure)
    {
        m_DBModel.WeldPressure = iWeldPressure;
        emit notifyWeldPressureSettingChanged();
    }
}

bool Manual::getIsSelectedAll() const
{
    for (const auto &record : m_listManualRecords)
    {
        if (!record.IsSelected)
            return false;
    }
    return true;
}

void Manual::setIsSelectedAll(const bool &value)
{
    for (int i = 0; i < m_listManualRecords.size(); ++i)
    {
        if (m_listManualRecords[i].IsSelected != value)
        {
            m_listManualRecords[i].IsSelected = value;
            QModelIndex idx = index(i);
            emit dataChanged(idx, idx, {MANUAL_TABLE::IS_SELECTED});
        }
    }
    emit notifyIsSelectedAllChanged();
}

int Manual::getMaxModelSamples() const
{
    return m_iMaxModelSamples;
}

void Manual::setMaxModelSamples(const int &value)
{
    if (m_iMaxModelSamples != value)
    {
        m_iMaxModelSamples = value;
        emit notifyMaxModelSamplesChanged();
    }
}

int Manual::getCurrentSamples() const
{
    return m_iCurrentSamples;
}

void Manual::setCurrentSamples(const int &value)
{
    if(m_iCurrentSamples != value)
    {
        m_iCurrentSamples = value;
        emit notifyCurrentSamplesChanged();
    }
}
