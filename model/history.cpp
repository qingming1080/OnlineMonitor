#include "history.h"
#include "DataBase/databasemanager.h"

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
    m_data = DataBaseManager::getInstance()->getProductionData();
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
    case _PRODUCTION_COLUMN::_PRODUCTION_id:
        return data.id;
    case _PRODUCTION_COLUMN::_PRODUCTION_welder_id:
        return data.welder_id;
    case _PRODUCTION_COLUMN::_PRODUCTION_model_id:
        return data.model_id;
    case _PRODUCTION_COLUMN::_PRODUCTION_create_time:
        return data.create_time;
    case _PRODUCTION_COLUMN::_PRODUCTION_serial_number:
        return data.serial_number;
    case _PRODUCTION_COLUMN::_PRODUCTION_cycle_count:
        return data.cycle_count;
    case _PRODUCTION_COLUMN::_PRODUCTION_batch_count:
        return data.batch_count;
    case _PRODUCTION_COLUMN::_PRODUCTION_energy:
        return data.energy;
    case _PRODUCTION_COLUMN::_PRODUCTION_amplitude:
        return data.amplitude;
    case _PRODUCTION_COLUMN::_PRODUCTION_pressure:
        return data.pressure;
    case _PRODUCTION_COLUMN::_PRODUCTION_time:
        return data.time;
    case _PRODUCTION_COLUMN::_PRODUCTION_power:
        return data.power;
    case _PRODUCTION_COLUMN::_PRODUCTION_pre_height:
        return data.pre_height;
    case _PRODUCTION_COLUMN::_PRODUCTION_post_height:
        return data.post_height;
    case _PRODUCTION_COLUMN::_PRODUCTION_force:
        return data.force;
    case _PRODUCTION_COLUMN::_PRODUCTION_residual:
        return data.residual;
    case _PRODUCTION_COLUMN::_PRODUCTION_good_rate:
        return data.good_rate;
    case _PRODUCTION_COLUMN::_PRODUCTION_good_subtotal_cycles:
        return data.good_subtotal_cycles;
    case _PRODUCTION_COLUMN::_PRODUCTION_suspect_subtotal_cycles:
        return data.suspect_subtotal_cycles;
    case _PRODUCTION_COLUMN::_PRODUCTION_not_definite_cycles:
        return data.not_definite_cycles;
    case _PRODUCTION_COLUMN::_PRODUCTION_final_result:
        return data.final_result;
    }
}

QHash<int, QByteArray> History::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[_PRODUCTION_COLUMN::_PRODUCTION_id]                       = "id";
    roles[_PRODUCTION_COLUMN::_PRODUCTION_welder_id]                = "welder_id";
    roles[_PRODUCTION_COLUMN::_PRODUCTION_model_id]                 = "model_id";
    roles[_PRODUCTION_COLUMN::_PRODUCTION_create_time]              = "create_time";
    roles[_PRODUCTION_COLUMN::_PRODUCTION_serial_number]            = "serial_number";
    roles[_PRODUCTION_COLUMN::_PRODUCTION_cycle_count]              = "cycle_count";
    roles[_PRODUCTION_COLUMN::_PRODUCTION_batch_count]              = "batch_count";
    roles[_PRODUCTION_COLUMN::_PRODUCTION_energy]                   = "energy";
    roles[_PRODUCTION_COLUMN::_PRODUCTION_amplitude]                = "amplitude";
    roles[_PRODUCTION_COLUMN::_PRODUCTION_pressure]                 = "pressure";
    roles[_PRODUCTION_COLUMN::_PRODUCTION_time]                     = "time";
    roles[_PRODUCTION_COLUMN::_PRODUCTION_power]                    = "power";
    roles[_PRODUCTION_COLUMN::_PRODUCTION_pre_height]               = "pre_height";
    roles[_PRODUCTION_COLUMN::_PRODUCTION_post_height]              = "post_height";
    roles[_PRODUCTION_COLUMN::_PRODUCTION_force]                    = "force";
    roles[_PRODUCTION_COLUMN::_PRODUCTION_residual]                 = "residual";
    roles[_PRODUCTION_COLUMN::_PRODUCTION_good_rate]                = "good_rate";
    roles[_PRODUCTION_COLUMN::_PRODUCTION_good_subtotal_cycles]     = "good_subtotal_cycles";
    roles[_PRODUCTION_COLUMN::_PRODUCTION_suspect_subtotal_cycles]  = "suspect_subtotal_cycles";
    roles[_PRODUCTION_COLUMN::_PRODUCTION_not_definite_cycles]      = "not_definite_cycles";
    roles[_PRODUCTION_COLUMN::_PRODUCTION_final_result]             = "final_result";

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
