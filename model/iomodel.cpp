#include "iomodel.h"
#include "DataBase/databasemanager.h"


IOModel::IOModel(int welderID, QObject *parent)
    : QAbstractListModel{parent}, m_welderID(welderID)
{
    m_data = DataBaseManager::getInstance()->getIOData(m_welderID);
}

int IOModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

QVariant IOModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    int row = index.row();
    _IO_Data data = m_data.at(row);
    switch(role)
    {
    case _IO_COLUMN::_IO_id:
        return data.id;
    case _IO_COLUMN::_IO_welder_id:
        return data.welder_id;
    case _IO_COLUMN::_IO_pin:
        return data.pin;
    case _IO_COLUMN::_IO_available:
        return data.available;
    case _IO_COLUMN::_IO_signal:
        return data.signal;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> IOModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[_IO_COLUMN::_IO_id]           = "id";
    roles[_IO_COLUMN::_IO_welder_id]    = "welder_id";
    roles[_IO_COLUMN::_IO_pin]          = "pin";
    roles[_IO_COLUMN::_IO_available]    = "available";
    roles[_IO_COLUMN::_IO_signal]       = "signal";

    return roles;
}

QVariant IOModel::getDataByWelderID(int welderID, int role) const
{
    for(int i = 0; i < m_data.size(); ++i)
    {
        if(m_data.at(i).welder_id != welderID)
            continue;

        switch(role)
        {
        case _IO_COLUMN::_IO_id:
            return m_data.at(i).id;
        case _IO_COLUMN::_IO_welder_id:
            return m_data.at(i).welder_id;
        case _IO_COLUMN::_IO_pin:
            return m_data.at(i).pin;
        case _IO_COLUMN::_IO_available:
            return m_data.at(i).available;
        case _IO_COLUMN::_IO_signal:
            return m_data.at(i).signal;
        default:
            return QVariant();
        }
    }

    return QVariant();
}

void IOModel::setIOData(int id, _IO_COLUMN column, QVariant data)
{
    for(int i = 0; i < m_data.size(); ++i)
    {
        if(m_data.at(i).id != id)
            continue;

        switch(column)
        {
        case _IO_COLUMN::_IO_id:
        {
            m_data[i].id = data.toInt();
            DataBaseManager::getInstance()->setIOData(id, column, data);
            return;
        }
        case _IO_COLUMN::_IO_welder_id:
        {
            m_data[i].welder_id = data.toInt();
            DataBaseManager::getInstance()->setIOData(id, column, data);
            return;
        }
        case _IO_COLUMN::_IO_pin:
        {
            m_data[i].pin = data.toInt();
            DataBaseManager::getInstance()->setIOData(id, column, data);
            return;
        }
        case _IO_COLUMN::_IO_available:
        {
            m_data[i].available = data.toInt();
            DataBaseManager::getInstance()->setIOData(id, column, data);
            return;
        }
        case _IO_COLUMN::_IO_signal:
        {
            m_data[i].signal = data.toInt();
            DataBaseManager::getInstance()->setIOData(id, column, data);
            return;
        }
        default:
            return;
        }
    }
}

