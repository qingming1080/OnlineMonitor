#include "history.h"
#include "DataBase/databasemanager.h"
#include <QtMath>

#include "signalmanager.h"
#include <QDebug>
#include <QElapsedTimer>
#include "log/localrecord.h"

History* History::s_pHistory = nullptr;

History *History::getInstance()
{
    if(s_pHistory == nullptr)
        s_pHistory = new History();

    return s_pHistory;
}

History::History(QObject *parent)
    : QAbstractListModel{parent}
{
    QElapsedTimer timer;
    timer.start();

    m_data = DataBaseManager::getInstance()->getProductionData();
   // std::reverse(m_data.begin(), m_data.end());


    QString text = QString("History_初始化共耗时:%1ms 加载%2条数据").arg(timer.elapsed()).arg(m_data.size());
    emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), text);
}

int History::finalResult() const
{
    return m_finalResult;
}

void History::setFinalResult(int newFinalResult)
{
    QElapsedTimer timer;
    timer.start();

    if (m_finalResult == newFinalResult)
        return;

    m_finalResult = newFinalResult;
    emit beginResetModel();
    m_data = DataBaseManager::getInstance()->getProductionData(m_deviceID, m_finalResult);
    emit endResetModel();
    emit finalResultChanged();

    QString text = QString("History_修改筛选结果耗时:%1ms").arg(timer.elapsed());
    emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), text);
}

int History::deviceID() const
{
    return m_deviceID;
}

// void History::setDeviceID(int newDeviceID)
// {
//     QElapsedTimer timer;
//     timer.start();

//     if (m_deviceID == newDeviceID)
//         return;

//     m_deviceID = newDeviceID;
//     emit beginResetModel();
//     m_data = DataBaseManager::getInstance()->getProductionData(m_deviceID, m_finalResult);
//     emit endResetModel();
//     emit deviceIDChanged();

//     QString text = QString("History_修改筛选设备耗时:%1ms").arg(timer.elapsed());
//     emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), text);
// }

void History::setDeviceID(int newDeviceID)
{
    QElapsedTimer timer;
    timer.start();

    if (m_deviceID == newDeviceID)
        return;

    m_deviceID = newDeviceID;
    emit beginResetModel();

    // 根据新的设备ID加载数据
    if (newDeviceID == 0) {
        m_data = DataBaseManager::getInstance()->getProductionData();  // 获取所有设备的数据
    } else {
        m_data = DataBaseManager::getInstance()->getProductionData(newDeviceID);  // 获取特定设备的数据
    }

    // 按照记录时间排序，确保最新的记录排在前面
    std::sort(m_data.begin(), m_data.end(), [](const _Production_Data &a, const _Production_Data &b) {
        return a.create_time > b.create_time;  // 降序排序，最新记录在前
    });

    emit endResetModel();
    emit deviceIDChanged();

    QString text = QString("History_修改筛选设备耗时:%1ms").arg(timer.elapsed());
    emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), text);
}


int History::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

QVariant History::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    int row = index.row();
    _Production_Data data = m_data.at(row);
    switch(role)
    {
    case QmlEnum::PRODUCTION_COLUMN::PRODUCTION_id:
        return data.id;
    case QmlEnum::PRODUCTION_COLUMN::PRODUCTION_welder_id:
        return data.welder_id;
    case QmlEnum::PRODUCTION_COLUMN::PRODUCTION_model_id:
        return data.model_id;
    case QmlEnum::PRODUCTION_COLUMN::PRODUCTION_create_time:
        return data.create_time;
    case QmlEnum::PRODUCTION_COLUMN::PRODUCTION_serial_number:
        return data.serial_number;
    case QmlEnum::PRODUCTION_COLUMN::PRODUCTION_cycle_count:
        return data.cycle_count;
    case QmlEnum::PRODUCTION_COLUMN::PRODUCTION_batch_count:
        return data.batch_count;
    case QmlEnum::PRODUCTION_COLUMN::PRODUCTION_energy:
        return data.energy;
    case QmlEnum::PRODUCTION_COLUMN::PRODUCTION_amplitude:
        return data.amplitude;
    case QmlEnum::PRODUCTION_COLUMN::PRODUCTION_pressure:
        return data.pressure;
    case QmlEnum::PRODUCTION_COLUMN::PRODUCTION_time:
        return data.time;
    case QmlEnum::PRODUCTION_COLUMN::PRODUCTION_power:
        return data.power;
    case QmlEnum::PRODUCTION_COLUMN::PRODUCTION_pre_height:
        return data.pre_height;
    case QmlEnum::PRODUCTION_COLUMN::PRODUCTION_post_height:
        return data.post_height;
    case QmlEnum::PRODUCTION_COLUMN::PRODUCTION_force:
        return data.force;
    case QmlEnum::PRODUCTION_COLUMN::PRODUCTION_residual:
        return data.residual;
    case QmlEnum::PRODUCTION_COLUMN::PRODUCTION_good_rate:
        return data.good_rate;
    case QmlEnum::PRODUCTION_COLUMN::PRODUCTION_good_subtotal_cycles:
        return data.good_subtotal_cycles;
    case QmlEnum::PRODUCTION_COLUMN::PRODUCTION_suspect_subtotal_cycles:
        return data.suspect_subtotal_cycles;
    case QmlEnum::PRODUCTION_COLUMN::PRODUCTION_not_definite_cycles:
        return data.not_definite_cycles;
    case QmlEnum::PRODUCTION_COLUMN::PRODUCTION_final_result:
        return data.final_result;
    default:
        return QVariant();
    }

}

QHash<int, QByteArray> History::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[QmlEnum::PRODUCTION_COLUMN::PRODUCTION_id]                       = "id";
    roles[QmlEnum::PRODUCTION_COLUMN::PRODUCTION_welder_id]                = "welder_id";
    roles[QmlEnum::PRODUCTION_COLUMN::PRODUCTION_model_id]                 = "model_id";
    roles[QmlEnum::PRODUCTION_COLUMN::PRODUCTION_create_time]              = "create_time";
    roles[QmlEnum::PRODUCTION_COLUMN::PRODUCTION_serial_number]            = "serial_number";
    roles[QmlEnum::PRODUCTION_COLUMN::PRODUCTION_cycle_count]              = "cycle_count";
    roles[QmlEnum::PRODUCTION_COLUMN::PRODUCTION_batch_count]              = "batch_count";
    roles[QmlEnum::PRODUCTION_COLUMN::PRODUCTION_energy]                   = "energy";
    roles[QmlEnum::PRODUCTION_COLUMN::PRODUCTION_amplitude]                = "amplitude";
    roles[QmlEnum::PRODUCTION_COLUMN::PRODUCTION_pressure]                 = "pressure";
    roles[QmlEnum::PRODUCTION_COLUMN::PRODUCTION_time]                     = "time";
    roles[QmlEnum::PRODUCTION_COLUMN::PRODUCTION_power]                    = "power";
    roles[QmlEnum::PRODUCTION_COLUMN::PRODUCTION_pre_height]               = "pre_height";
    roles[QmlEnum::PRODUCTION_COLUMN::PRODUCTION_post_height]              = "post_height";
    roles[QmlEnum::PRODUCTION_COLUMN::PRODUCTION_force]                    = "force";
    roles[QmlEnum::PRODUCTION_COLUMN::PRODUCTION_residual]                 = "residual";
    roles[QmlEnum::PRODUCTION_COLUMN::PRODUCTION_good_rate]                = "good_rate";
    roles[QmlEnum::PRODUCTION_COLUMN::PRODUCTION_good_subtotal_cycles]     = "good_subtotal_cycles";
    roles[QmlEnum::PRODUCTION_COLUMN::PRODUCTION_suspect_subtotal_cycles]  = "suspect_subtotal_cycles";
    roles[QmlEnum::PRODUCTION_COLUMN::PRODUCTION_not_definite_cycles]      = "not_definite_cycles";
    roles[QmlEnum::PRODUCTION_COLUMN::PRODUCTION_final_result]             = "final_result";

    return roles;
}

void History::setWelderID(int welderID)
{
    emit beginResetModel();

    if(welderID == 0)
        m_data = DataBaseManager::getInstance()->getProductionData();
    else
        m_data = DataBaseManager::getInstance()->getProductionData(welderID);

    emit endResetModel();
}
