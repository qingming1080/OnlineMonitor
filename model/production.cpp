#include "production.h"
#include "DataBase/databasemanager.h"

Production* Production::s_pProduction = nullptr;

Production *Production::getInstance()
{
    if(s_pProduction == nullptr)
        s_pProduction = new Production();

    return s_pProduction;
}

int Production::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

QVariant Production::data(const QModelIndex &index, int role) const
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
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> Production::roleNames() const
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

    return roles;
}

QVariant Production::getProductionByWelderID(int welderID, int role) const
{
    for(int i = 0; i < m_data.size(); ++i)
    {
        if(m_data.at(i).welder_id != welderID)
            continue;

        switch(role)
        {
        case _PRODUCTION_COLUMN::_PRODUCTION_id:
            return m_data.at(i).id;
        case _PRODUCTION_COLUMN::_PRODUCTION_welder_id:
            return m_data.at(i).welder_id;
        case _PRODUCTION_COLUMN::_PRODUCTION_model_id:
            return m_data.at(i).model_id;
        case _PRODUCTION_COLUMN::_PRODUCTION_create_time:
            return m_data.at(i).create_time;
        case _PRODUCTION_COLUMN::_PRODUCTION_serial_number:
            return m_data.at(i).serial_number;
        case _PRODUCTION_COLUMN::_PRODUCTION_cycle_count:
            return m_data.at(i).cycle_count;
        case _PRODUCTION_COLUMN::_PRODUCTION_batch_count:
            return m_data.at(i).batch_count;
        case _PRODUCTION_COLUMN::_PRODUCTION_energy:
            return m_data.at(i).energy;
        case _PRODUCTION_COLUMN::_PRODUCTION_amplitude:
            return m_data.at(i).amplitude;
        case _PRODUCTION_COLUMN::_PRODUCTION_pressure:
            return m_data.at(i).pressure;
        case _PRODUCTION_COLUMN::_PRODUCTION_time:
            return m_data.at(i).time;
        case _PRODUCTION_COLUMN::_PRODUCTION_power:
            return m_data.at(i).power;
        case _PRODUCTION_COLUMN::_PRODUCTION_pre_height:
            return m_data.at(i).pre_height;
        case _PRODUCTION_COLUMN::_PRODUCTION_post_height:
            return m_data.at(i).post_height;
        case _PRODUCTION_COLUMN::_PRODUCTION_force:
            return m_data.at(i).force;
        case _PRODUCTION_COLUMN::_PRODUCTION_residual:
            return m_data.at(i).residual;
        case _PRODUCTION_COLUMN::_PRODUCTION_good_rate:
            return m_data.at(i).good_rate;
        case _PRODUCTION_COLUMN::_PRODUCTION_good_subtotal_cycles:
            return m_data.at(i).good_subtotal_cycles;
        case _PRODUCTION_COLUMN::_PRODUCTION_suspect_subtotal_cycles:
            return m_data.at(i).suspect_subtotal_cycles;
        case _PRODUCTION_COLUMN::_PRODUCTION_not_definite_cycles:
            return m_data.at(i).not_definite_cycles;
        default:
            return QVariant();
        }
    }

    return QVariant();
}

void Production::setProductionData(int id, _PRODUCTION_COLUMN column, QVariant data)
{
    for(int i = 0; i < m_data.size(); ++i)
    {
        if(m_data.at(i).welder_id != id)
            continue;

        switch(column)
        {
        case _PRODUCTION_COLUMN::_PRODUCTION_id:
        {
            m_data[i].id = data.toInt();
            return;
        }
        case _PRODUCTION_COLUMN::_PRODUCTION_welder_id:
        {
            m_data[i].welder_id = data.toInt();
            return;
        }
        case _PRODUCTION_COLUMN::_PRODUCTION_model_id:
        {
            m_data[i].model_id = data.toInt();
            return;
        }
        case _PRODUCTION_COLUMN::_PRODUCTION_create_time:
        {
            m_data[i].create_time = data.toInt();
            return;
        }
        case _PRODUCTION_COLUMN::_PRODUCTION_serial_number:
        {
            m_data[i].serial_number = data.toInt();
            return;
        }
        case _PRODUCTION_COLUMN::_PRODUCTION_cycle_count:
        {
            m_data[i].cycle_count = data.toInt();
            return;
        }
        case _PRODUCTION_COLUMN::_PRODUCTION_batch_count:
        {
            m_data[i].batch_count = data.toInt();
            return;
        }
        case _PRODUCTION_COLUMN::_PRODUCTION_energy:
        {
            m_data[i].energy = data.toInt();
            return;
        }
        case _PRODUCTION_COLUMN::_PRODUCTION_amplitude:
        {
            m_data[i].amplitude = data.toInt();
            return;
        }
        case _PRODUCTION_COLUMN::_PRODUCTION_pressure:
        {
            m_data[i].pressure = data.toInt();
            return;
        }
        case _PRODUCTION_COLUMN::_PRODUCTION_time:
        {
            m_data[i].time = data.toInt();
            return;
        }
        case _PRODUCTION_COLUMN::_PRODUCTION_power:
        {
            m_data[i].power = data.toInt();
            return;
        }
        case _PRODUCTION_COLUMN::_PRODUCTION_pre_height:
        {
            m_data[i].pre_height = data.toInt();
            return;
        }
        case _PRODUCTION_COLUMN::_PRODUCTION_post_height:
        {
            m_data[i].post_height = data.toInt();
            return;
        }
        case _PRODUCTION_COLUMN::_PRODUCTION_force:
        {
            m_data[i].force = data.toInt();
            return;
        }
        case _PRODUCTION_COLUMN::_PRODUCTION_residual:
        {
            m_data[i].residual = data.toInt();
            return;
        }
        case _PRODUCTION_COLUMN::_PRODUCTION_good_rate:
        {
            m_data[i].good_rate = data.toInt();
            return;
        }
        case _PRODUCTION_COLUMN::_PRODUCTION_good_subtotal_cycles:
        {
            m_data[i].good_subtotal_cycles = data.toInt();
            return;
        }
        case _PRODUCTION_COLUMN::_PRODUCTION_suspect_subtotal_cycles:
        {
            m_data[i].suspect_subtotal_cycles = data.toInt();
            return;
        }
        case _PRODUCTION_COLUMN::_PRODUCTION_not_definite_cycles:
        {
            m_data[i].not_definite_cycles = data.toInt();
            return;
        }
        default:
            return;
        }
    }
}

void Production::save()
{
    DataBaseManager::getInstance()->clearProduction();
    DataBaseManager::getInstance()->openTransaction();

    for(int i = 0; i < m_data.size(); ++i)
        DataBaseManager::getInstance()->insertProductionRow(m_data.at(i));

    DataBaseManager::getInstance()->closeTransaction();
}

Production::Production(QObject *parent)
    : QAbstractListModel{parent}
{
    m_data = DataBaseManager::getInstance()->getProductionData();
}
