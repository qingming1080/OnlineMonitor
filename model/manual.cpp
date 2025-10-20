#include "manual.h"
#include "DataBase/databasemanager.h"
#include  "tools/utilityfunction.h"
#include "signalmanager.h"
#include <QDebug>
#include <QElapsedTimer>
#include "log/localrecord.h"
#include "tools/GenericLearning.h"
#include "provienceEE/providenceEE.h"

Manual::Manual(int welderID,QObject *parent)
    : QAbstractListModel{parent}, m_welderID(welderID)
{

    m_modbusClient = HBModbusClient::getInstance();

    m_listRawData = DataBaseManager::getInstance()->getManualData(m_welderID);

    for(int i = 0; i < m_listRawData.size(); ++i) {
        m_listRawData[i].serial_number = m_nextSerial++;
    }

}

Manual::~Manual()
{

}

int Manual::welderID() const
{
 return m_welderID;
}

void Manual::setWelderID(int id) {
    if (m_welderID != id) {
        m_welderID = id;

         loadData();  // 重新加载数据
        emit welderIDChanged();

    }
}

int Manual::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listRawData.size();
}

QVariant Manual::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    int row = index.row();
    MANUAL_DATA data = m_listRawData.at(row);
    switch(role)
    {
    // case QmlEnum::MANUAL_COLUMN::MANUAL_id:
    //     return data.id;
    case QmlEnum::MANUAL_COLUMN::MANUAL_welder_id:
        return data.WelderId;
    case QmlEnum::MANUAL_COLUMN::MANUAL_create_time:
        return data.CreateTime;
    case QmlEnum::MANUAL_COLUMN::MANUAL_serial_number:
        return data.serial_number;
        // return row + 1;
    case QmlEnum::MANUAL_COLUMN::MANUAL_cycle_count:
        return data.CycleCount;
    case QmlEnum::MANUAL_COLUMN::MANUAL_energy:
        return data.Energy;
    case QmlEnum::MANUAL_COLUMN::MANUAL_amplitude:
        return data.Amplitude;
    case QmlEnum::MANUAL_COLUMN::MANUAL_pressure:
        return data.WeldPressure;
    case QmlEnum::MANUAL_COLUMN::MANUAL_time:
        return data.WeldTime;
    case QmlEnum::MANUAL_COLUMN::MANUAL_power:
        return data.PeakPower;
    case QmlEnum::MANUAL_COLUMN::MANUAL_pre_height:
        return data.Preheight;
    case QmlEnum::MANUAL_COLUMN::MANUAL_post_height:
        return data.PostHeight;
    case QmlEnum::MANUAL_COLUMN::MANUAL_actual_force:
        return data.ActualForce;
    case QmlEnum::MANUAL_COLUMN::MANUAL_actual_degree:
        return data.ActualResidual;
    case QmlEnum::MANUAL_COLUMN::MANUAL_isSelected:
        return data.IsSelected;
    case QmlEnum::MANUAL_COLUMN::MANUAL_preEnergy:
        return data.PreEnergy;
    case QmlEnum::MANUAL_COLUMN::MANUAL_preAmplitude:
        return data.PreAmplitude;
    case QmlEnum::MANUAL_COLUMN::MANUAL_preTP:
        return data.PreTP;
    case QmlEnum::MANUAL_COLUMN::MANUAL_preWP:
        return data.PreWP;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> Manual::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[QmlEnum::MANUAL_COLUMN::MANUAL_id]               = "id";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_welder_id]        = "welder_id";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_create_time]      = "create_time";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_serial_number]    = "serial_number";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_cycle_count]      = "cycle_count";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_energy]           = "energy";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_amplitude]        = "amplitude";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_pressure]         = "pressure";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_time]             = "time";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_power]            = "power";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_pre_height]       = "pre_height";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_post_height]      = "post_height";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_actual_force]     = "actual_force";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_actual_degree]    = "actual_degree";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_isSelected]       = "selected";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_isNewComming]     = "isNewComming";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_preEnergy]        = "preEnergy";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_preAmplitude]     = "preAmplitude";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_preTP]            = "preTP";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_preWP]            = "preWP";

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
    // case QmlEnum::MANUAL_COLUMN::MANUAL_id:
    // {
    //     m_data[row].id = value.toInt();
    //     return true;
    // }
    case QmlEnum::MANUAL_welder_id:
        m_listRawData[row].WelderId = value.toInt();
        break;
    case QmlEnum::MANUAL_COLUMN::MANUAL_create_time:
        m_listRawData[row].CreateTime = value.toInt();
        break;
    // case QmlEnum::MANUAL_COLUMN::MANUAL_serial_number:
    // {
    //     // m_data[row].serial_number = value.toInt();
    //     m_rowSerialMap.value(index.row());
    //     return true;
    // }
    case QmlEnum::MANUAL_COLUMN::MANUAL_cycle_count:
        m_listRawData[row].CycleCount = value.toInt();
        break;
    case QmlEnum::MANUAL_COLUMN::MANUAL_energy:
        m_listRawData[row].Energy = value.toInt();
        break;
    case QmlEnum::MANUAL_COLUMN::MANUAL_amplitude:
        m_listRawData[row].Amplitude = value.toInt();
        break;
    case QmlEnum::MANUAL_COLUMN::MANUAL_pressure:
        m_listRawData[row].WeldPressure = value.toInt();
        break;
    case QmlEnum::MANUAL_COLUMN::MANUAL_time:
        m_listRawData[row].WeldTime = value.toInt();
        break;
    case QmlEnum::MANUAL_COLUMN::MANUAL_power:
        m_listRawData[row].PeakPower = value.toInt();
        break;
    case QmlEnum::MANUAL_COLUMN::MANUAL_pre_height:
        m_listRawData[row].Preheight = value.toInt();
        break;
    case QmlEnum::MANUAL_COLUMN::MANUAL_post_height:
        m_listRawData[row].PostHeight = value.toInt();
        break;
    case QmlEnum::MANUAL_COLUMN::MANUAL_actual_force:
        m_listRawData[row].ActualForce = value.toInt();
        break;
    case QmlEnum::MANUAL_COLUMN::MANUAL_actual_degree:
        m_listRawData[row].ActualResidual = value.toInt();
        break;
    case QmlEnum::MANUAL_COLUMN::MANUAL_preEnergy:
        m_listRawData[row].PreEnergy =  value.toInt();
    case QmlEnum::MANUAL_COLUMN::MANUAL_preAmplitude:
        m_listRawData[row].PreAmplitude =  value.toInt();
    case QmlEnum::MANUAL_COLUMN::MANUAL_preTP:
        m_listRawData[row].PreTP =  value.toInt();
    case QmlEnum::MANUAL_COLUMN::MANUAL_preWP:
        m_listRawData[row].PreWP =  value.toInt();
    case QmlEnum::MANUAL_COLUMN::MANUAL_isSelected:
        m_listRawData[row].IsSelected = value.toBool();
        emit dataChanged(index, index, {role});
        break;
    default:
        bResult =  false;
    }
    return bResult;
}

void Manual::save()
{
    CalibrateModel();
    // for(int i = 0; i < m_data.size(); ++i)
    // {
    //     if (m_data[i].selected)
    //     DataBaseManager::getInstance()->insertManualRow(m_data.at(i));
    //     QModelIndex idx = index(i);
    //     emit dataChanged(idx, idx, {QmlEnum::MANUAL_COLUMN::MANUAL_selected});
    // }
}


void Manual::clearData()
{
    beginResetModel();
    m_listRawData.clear();
    DataBaseManager::getInstance()->removeManualDevice(m_welderID);
    endResetModel();
    m_nextSerial = 1;
}

void Manual::loadData()
{
    beginResetModel();  // 通知 QML 模型发生变化
    m_listRawData = DataBaseManager::getInstance()->getManualData(m_welderID); // 重新加载数据
    m_nextSerial = 1;
    for(int i = 0; i < m_listRawData.size(); ++i) {
        m_listRawData[i].serial_number = m_nextSerial++;
    }
    endResetModel();
}


void Manual::startReading()
{
    connect(m_modbusClient, &HBModbusClient::newInputData, this, &Manual::onNewManualData);

    qDebug() << "Manual 开始接收 Modbus 数据";
}

void Manual::stopReading()
{
    disconnect(m_modbusClient, &HBModbusClient::newInputData, this, &Manual::onNewManualData);
    qDebug() << "Manual 停止接收 Modbus 数据";
}

bool Manual::CalibrateModel()
{
    qDebug()<< "111111111";
    m_listManualData.clear();
    for(int i = 0; i < m_listRawData.size(); i++)
    { qDebug()<< "222222";
        // if(m_listRawData[i].IsSelected == true)
        // {
            qDebug()<< "333333";
            // if(m_listRawData[i].ActualForce != 0 && m_listRawData[i].ActualResidual != 0)
            // {
                m_listManualData.append(m_listRawData[i]);
            // }
        // }
    }
    if(m_listManualData.size() == 0)
        return false;
#if RASPBERRY
    ProvidenceEE::GetInstance()->ResetProcess();
    ProvidenceEE::GetInstance()->CalibrateSPCProcess(m_listManualData);
    ProvidenceEE::GetInstance()->CalibrateAIProcess(m_listManualData);

    GenericLearning::PROCESS_PARAM param[GenericLearning::TOTALPARA];
    GenericLearning::AI_POLYNOMIAL_COEFFICIENT coefficient[GenericLearning::STRENGTH_MAX];
    GenericLearning::CENTRALIZED_PROPERTY centralized;

    ProvidenceEE::GetInstance()->GetSPCProcess(param);
    ProvidenceEE::GetInstance()->GetAIProcess(&centralized, coefficient);

    qDebug() << "Time.Alpha: " << param[GenericLearning::TIME].Alpha;
    qDebug() << "Time.Beta: " << param[GenericLearning::TIME].Beta;
    qDebug() << "Time.SampleCount: " << param[GenericLearning::TIME].SampleCount;
    qDebug() << "Power.Alpha: " << param[GenericLearning::POWER].Alpha;
    qDebug() << "Power.Beta: " << param[GenericLearning::POWER].Beta;
    qDebug() << "Power.SampleCount: " << param[GenericLearning::POWER].SampleCount;
    qDebug() << "Preheight.Alpha: " << param[GenericLearning::PREHEIGHT].Alpha;
    qDebug() << "Preheight.Beta: " << param[GenericLearning::PREHEIGHT].Beta;
    qDebug() << "Preheight.SampleCount: " << param[GenericLearning::PREHEIGHT].SampleCount;
    qDebug() << "Postheight.Alpha: " << param[GenericLearning::POSTHEIGHT].Alpha;
    qDebug() << "Postheight.Beta: " << param[GenericLearning::POSTHEIGHT].Beta;
    qDebug() << "Postheight.SampleCount: " << param[GenericLearning::POSTHEIGHT].SampleCount;

    qDebug() << "Centralized.ForceMean: " << centralized.ForceMean;
    qDebug() << "Centralized.ResidualMean: " << centralized.ResidualMean;
    qDebug() << "Centralized.PowerMean: " << centralized.PowerMean;
    qDebug() << "Centralized.PowrStd: " << centralized.PowrStd;
    qDebug() << "Centralized.TimeMean: " << centralized.TimeMean;
    qDebug() << "Centralized.TimeStd: " << centralized.TimeStd;

    qDebug() << "Strength0.P00: " << coefficient[GenericLearning::STRENGTH0].P00;
    qDebug() << "Strength0.P01: " << coefficient[GenericLearning::STRENGTH0].P01;
    qDebug() << "Strength0.P02: " << coefficient[GenericLearning::STRENGTH0].P02;
    qDebug() << "Strength0.P10: " << coefficient[GenericLearning::STRENGTH0].P10;
    qDebug() << "Strength0.P11: " << coefficient[GenericLearning::STRENGTH0].P11;
    qDebug() << "Strength0.P20: " << coefficient[GenericLearning::STRENGTH0].P20;

    qDebug() << "Strength1.P00: " << coefficient[GenericLearning::STRENGTH1].P00;
    qDebug() << "Strength1.P01: " << coefficient[GenericLearning::STRENGTH1].P01;
    qDebug() << "Strength1.P02: " << coefficient[GenericLearning::STRENGTH1].P02;
    qDebug() << "Strength1.P10: " << coefficient[GenericLearning::STRENGTH1].P10;
    qDebug() << "Strength1.P11: " << coefficient[GenericLearning::STRENGTH1].P11;
    qDebug() << "Strength1.P20: " << coefficient[GenericLearning::STRENGTH1].P20;
    qDebug()<< "444444444444444444";
#endif
    //TODO handle with Database
    return true;
}

void Manual::onNewManualData(int welderId, const QVector<quint16> &inputs, quint32 cycleCount, DateTimeData date, QVector<quint16> holdings)
{
    beginInsertRows(QModelIndex(), 0, 0);
    MANUAL_DATA data;
    data.WelderId       = welderId;
    data.CycleCount     = cycleCount;
    data.Energy         = inputs[HBModbusClient::DEV_ENERGY];
    data.Amplitude      = inputs[HBModbusClient::DEV_AMPLITUDE];
    data.WeldPressure   = inputs[HBModbusClient::DEV_WP];
    data.WeldTime       = inputs[HBModbusClient::DEV_TIME];
    data.PeakPower      = inputs[HBModbusClient::DEV_POWER];
    data.Preheight      = inputs[HBModbusClient::DEV_PRE_HEIGHT];
    data.PostHeight     = inputs[HBModbusClient::DEV_POST_HEIGHT];
    data.ActualForce    = 10;
    data.ActualResidual = 10;
    data.CreateTime     = UtilityFunction::buildDateTimeString(date).left(10);;
    data.serial_number  = m_nextSerial++;
    data.IsSelected     = false;
    data.IsNewComming   = true;
    data.PreEnergy      = holdings[PREENERGY];
    data.PreAmplitude   = holdings[PREAMPLITUDE];
    data.PreTP          = holdings[PRETP];
    data.PreWP          = holdings[PREWP];
    m_listRawData.prepend(data);
    endInsertRows();
}

