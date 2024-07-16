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
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_id:
        return data.id;
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_welder_id:
        return data.welder_id;
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_create_time:
        return data.create_time;
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_serial_number:
        return data.serial_number;
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_cycle_count:
        return data.cycle_count;
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_energy:
        return data.energy;
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_amplitude:
        return data.amplitude;
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_pressure:
        return data.pressure;
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_time:
        return data.time;
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_power:
        return data.power;
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_pre_height:
        return data.pre_height;
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_post_height:
        return data.post_height;
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_actual_force:
        return data.actual_force;
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_actual_degree:
        return data.actual_degree;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> Manual::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[QmlEnum::_MANUAL_COLUMN::_MANUAL_id]               = "id";
    roles[QmlEnum::_MANUAL_COLUMN::_MANUAL_welder_id]        = "welder_id";
    roles[QmlEnum::_MANUAL_COLUMN::_MANUAL_create_time]      = "create_time";
    roles[QmlEnum::_MANUAL_COLUMN::_MANUAL_serial_number]    = "serial_number";
    roles[QmlEnum::_MANUAL_COLUMN::_MANUAL_cycle_count]      = "cycle_count";
    roles[QmlEnum::_MANUAL_COLUMN::_MANUAL_energy]           = "energy";
    roles[QmlEnum::_MANUAL_COLUMN::_MANUAL_amplitude]        = "amplitude";
    roles[QmlEnum::_MANUAL_COLUMN::_MANUAL_pressure]         = "pressure";
    roles[QmlEnum::_MANUAL_COLUMN::_MANUAL_time]             = "time";
    roles[QmlEnum::_MANUAL_COLUMN::_MANUAL_power]            = "power";
    roles[QmlEnum::_MANUAL_COLUMN::_MANUAL_pre_height]       = "pre_height";
    roles[QmlEnum::_MANUAL_COLUMN::_MANUAL_post_height]      = "post_height";
    roles[QmlEnum::_MANUAL_COLUMN::_MANUAL_actual_force]     = "actual_force";
    roles[QmlEnum::_MANUAL_COLUMN::_MANUAL_actual_degree]    = "actual_degree";

    return roles;
}

bool Manual::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
        return false;

    int row = index.row();
    switch(role)
    {
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_id:
    {
        m_data[row].id = value.toInt();
        return true;
    }
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_welder_id:
    {
        m_data[row].welder_id = value.toInt();
        return true;
    }
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_create_time:
    {
        m_data[row].create_time = value.toInt();
        return true;
    }
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_serial_number:
    {
        m_data[row].serial_number = value.toInt();
        return true;
    }
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_cycle_count:
    {
        m_data[row].cycle_count = value.toInt();
        return true;
    }
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_energy:
    {
        m_data[row].energy = value.toInt();
        return true;
    }
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_amplitude:
    {
        m_data[row].amplitude = value.toInt();
        return true;
    }
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_pressure:
    {
        m_data[row].pressure = value.toInt();
        return true;
    }
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_time:
    {
        m_data[row].time = value.toInt();
        return true;
    }
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_power:
    {
        m_data[row].power = value.toInt();
        return true;
    }
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_pre_height:
    {
        m_data[row].pre_height = value.toInt();
        return true;
    }
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_post_height:
    {
        m_data[row].post_height = value.toInt();
        return true;
    }
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_actual_force:
    {
        m_data[row].actual_force = value.toInt();
        return true;
    }
    case QmlEnum::_MANUAL_COLUMN::_MANUAL_actual_degree:
    {
        m_data[row].actual_degree = value.toInt();
        return true;
    }
    default:
        return false;
    }
}

void Manual::save()
{
    DataBaseManager::getInstance()->removeManualDevice(m_welderID);

    for(int i = 0; i < m_data.size(); ++i)
    {
        DataBaseManager::getInstance()->insertManualRow(m_data.at(i));
    }
}


