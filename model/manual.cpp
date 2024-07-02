#include "manual.h"
#include "DataBase/databasemanager.h"

Manual::Manual(int welderID, QObject *parent)
    : QAbstractListModel{parent}, m_welderID(welderID)
{
    m_data = DataBaseManager::getInstance()->getManualData(m_welderID);
}

int Manual::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

QVariant Manual::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    int row = index.row();
    _Manual_Data data = m_data.at(row);
    switch(role)
    {
    case _MANUAL_COLUMN::_MANUAL_id:
        return data.id;
    case _MANUAL_COLUMN::_MANUAL_welder_id:
        return data.welder_id;
    case _MANUAL_COLUMN::_MANUAL_create_time:
        return data.create_time;
    case _MANUAL_COLUMN::_MANUAL_serial_number:
        return data.serial_number;
    case _MANUAL_COLUMN::_MANUAL_cycle_count:
        return data.cycle_count;
    case _MANUAL_COLUMN::_MANUAL_energy:
        return data.energy;
    case _MANUAL_COLUMN::_MANUAL_amplitude:
        return data.amplitude;
    case _MANUAL_COLUMN::_MANUAL_pressure:
        return data.pressure;
    case _MANUAL_COLUMN::_MANUAL_time:
        return data.time;
    case _MANUAL_COLUMN::_MANUAL_power:
        return data.power;
    case _MANUAL_COLUMN::_MANUAL_pre_height:
        return data.pre_height;
    case _MANUAL_COLUMN::_MANUAL_post_height:
        return data.post_height;
    case _MANUAL_COLUMN::_MANUAL_actual_force:
        return data.actual_force;
    case _MANUAL_COLUMN::_MANUAL_actual_degree:
        return data.actual_degree;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> Manual::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[_MANUAL_COLUMN::_MANUAL_id]               = "id";
    roles[_MANUAL_COLUMN::_MANUAL_welder_id]        = "welder_id";
    roles[_MANUAL_COLUMN::_MANUAL_create_time]      = "create_time";
    roles[_MANUAL_COLUMN::_MANUAL_serial_number]    = "serial_number";
    roles[_MANUAL_COLUMN::_MANUAL_cycle_count]      = "cycle_count";
    roles[_MANUAL_COLUMN::_MANUAL_energy]           = "energy";
    roles[_MANUAL_COLUMN::_MANUAL_amplitude]        = "amplitude";
    roles[_MANUAL_COLUMN::_MANUAL_pressure]         = "pressure";
    roles[_MANUAL_COLUMN::_MANUAL_time]             = "time";
    roles[_MANUAL_COLUMN::_MANUAL_power]            = "power";
    roles[_MANUAL_COLUMN::_MANUAL_pre_height]       = "pre_height";
    roles[_MANUAL_COLUMN::_MANUAL_post_height]      = "post_height";
    roles[_MANUAL_COLUMN::_MANUAL_actual_force]     = "actual_force";
    roles[_MANUAL_COLUMN::_MANUAL_actual_degree]    = "actual_degree";

    return roles;
}

QVariant Manual::getManualDataByWelderID(int welderID, int role) const
{
    for(int i = 0; i < m_data.size(); ++i)
    {
        if(m_data.at(i).welder_id != welderID)
            continue;

        switch(role)
        {
        case _MANUAL_COLUMN::_MANUAL_id:
            return m_data.at(i).id;
        case _MANUAL_COLUMN::_MANUAL_welder_id:
            return m_data.at(i).welder_id;
        case _MANUAL_COLUMN::_MANUAL_create_time:
            return m_data.at(i).create_time;
        case _MANUAL_COLUMN::_MANUAL_serial_number:
            return m_data.at(i).serial_number;
        case _MANUAL_COLUMN::_MANUAL_cycle_count:
            return m_data.at(i).cycle_count;
        case _MANUAL_COLUMN::_MANUAL_energy:
            return m_data.at(i).energy;
        case _MANUAL_COLUMN::_MANUAL_amplitude:
            return m_data.at(i).amplitude;
        case _MANUAL_COLUMN::_MANUAL_pressure:
            return m_data.at(i).pressure;
        case _MANUAL_COLUMN::_MANUAL_time:
            return m_data.at(i).time;
        case _MANUAL_COLUMN::_MANUAL_power:
            return m_data.at(i).power;
        case _MANUAL_COLUMN::_MANUAL_pre_height:
            return m_data.at(i).pre_height;
        case _MANUAL_COLUMN::_MANUAL_post_height:
            return m_data.at(i).post_height;
        case _MANUAL_COLUMN::_MANUAL_actual_force:
            return m_data.at(i).actual_force;
        case _MANUAL_COLUMN::_MANUAL_actual_degree:
            return m_data.at(i).actual_degree;
        default:
            return QVariant();
        }
    }

    return QVariant();
}

void Manual::setManualData(int id, _MANUAL_COLUMN column, QVariant data)
{
    for(int i = 0; i < m_data.size(); ++i)
    {
        if(m_data.at(i).id != id)
            continue;

        switch(column)
        {
        case _MANUAL_COLUMN::_MANUAL_id:
        {
            m_data[i].id = data.toInt();
            DataBaseManager::getInstance()->setManualData(id, column, data);
            return;
        }
        case _MANUAL_COLUMN::_MANUAL_welder_id:
        {
            m_data[i].welder_id = data.toInt();
            DataBaseManager::getInstance()->setManualData(id, column, data);
            return;
        }
        case _MANUAL_COLUMN::_MANUAL_create_time:
        {
            m_data[i].create_time = data.toInt();
            DataBaseManager::getInstance()->setManualData(id, column, data);
            return;
        }
        case _MANUAL_COLUMN::_MANUAL_serial_number:
        {
            m_data[i].serial_number = data.toInt();
            DataBaseManager::getInstance()->setManualData(id, column, data);
            return;
        }
        case _MANUAL_COLUMN::_MANUAL_cycle_count:
        {
            m_data[i].cycle_count = data.toInt();
            DataBaseManager::getInstance()->setManualData(id, column, data);
            return;
        }
        case _MANUAL_COLUMN::_MANUAL_energy:
        {
            m_data[i].energy = data.toInt();
            DataBaseManager::getInstance()->setManualData(id, column, data);
            return;
        }
        case _MANUAL_COLUMN::_MANUAL_amplitude:
        {
            m_data[i].amplitude = data.toInt();
            DataBaseManager::getInstance()->setManualData(id, column, data);
            return;
        }
        case _MANUAL_COLUMN::_MANUAL_pressure:
        {
            m_data[i].pressure = data.toInt();
            DataBaseManager::getInstance()->setManualData(id, column, data);
            return;
        }
        case _MANUAL_COLUMN::_MANUAL_time:
        {
            m_data[i].time = data.toInt();
            DataBaseManager::getInstance()->setManualData(id, column, data);
            return;
        }
        case _MANUAL_COLUMN::_MANUAL_power:
        {
            m_data[i].power = data.toInt();
            DataBaseManager::getInstance()->setManualData(id, column, data);
            return;
        }
        case _MANUAL_COLUMN::_MANUAL_pre_height:
        {
            m_data[i].pre_height = data.toInt();
            DataBaseManager::getInstance()->setManualData(id, column, data);
            return;
        }
        case _MANUAL_COLUMN::_MANUAL_post_height:
        {
            m_data[i].post_height = data.toInt();
            DataBaseManager::getInstance()->setManualData(id, column, data);
            return;
        }
        case _MANUAL_COLUMN::_MANUAL_actual_force:
        {
            m_data[i].actual_force = data.toInt();
            DataBaseManager::getInstance()->setManualData(id, column, data);
            return;
        }
        case _MANUAL_COLUMN::_MANUAL_actual_degree:
        {
            m_data[i].actual_degree = data.toInt();
            DataBaseManager::getInstance()->setManualData(id, column, data);
            return;
        }
        default:
            return;
        }
    }
}


