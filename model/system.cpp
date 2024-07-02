#include "system.h"
#include "DataBase/databasemanager.h"

System::System(int welderID, QObject *parent)
    : QAbstractListModel{parent}, m_welderID(welderID)
{
    m_data = DataBaseManager::getInstance()->getSystemData(m_welderID);
}


int System::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

QVariant System::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    int row = index.row();
    _System_Data data = m_data.at(row);
    switch(role)
    {
    case _SYSTEM_COLUMN::_SYSTEM_id:
        return data.id;
    case _SYSTEM_COLUMN::_SYSTEM_welder_id:
        return data.welder_id;
    case _SYSTEM_COLUMN::_SYSTEM_single_fact_setting:
        return data.single_fact_setting;
    case _SYSTEM_COLUMN::_SYSTEM_general_fact_setting:
        return data.general_fact_setting;
    case _SYSTEM_COLUMN::_SYSTEM_other_fact_setting:
        return data.other_fact_setting;
    case _SYSTEM_COLUMN::_SYSTEM_auto_model_limit:
        return data.auto_model_limit;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> System::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[_SYSTEM_COLUMN::_SYSTEM_id]                     = "id";
    roles[_SYSTEM_COLUMN::_SYSTEM_welder_id]              = "welder_id";
    roles[_SYSTEM_COLUMN::_SYSTEM_single_fact_setting]    = "single_fact_setting";
    roles[_SYSTEM_COLUMN::_SYSTEM_general_fact_setting]   = "general_fact_setting";
    roles[_SYSTEM_COLUMN::_SYSTEM_other_fact_setting]     = "other_fact_setting";
    roles[_SYSTEM_COLUMN::_SYSTEM_auto_model_limit]       = "auto_model_limit";


    return roles;
}

QVariant System::getSystemByWelderID(int welderID, int role) const
{
    for(int i = 0; i < m_data.size(); ++i)
    {
        if(m_data.at(i).id != welderID)
            continue;

        switch(role)
        {
        case _SYSTEM_COLUMN::_SYSTEM_id:
            return m_data.at(i).id;
        case _SYSTEM_COLUMN::_SYSTEM_welder_id:
            return m_data.at(i).welder_id;
        case _SYSTEM_COLUMN::_SYSTEM_single_fact_setting:
            return m_data.at(i).single_fact_setting;
        case _SYSTEM_COLUMN::_SYSTEM_general_fact_setting:
            return m_data.at(i).general_fact_setting;
        case _SYSTEM_COLUMN::_SYSTEM_other_fact_setting:
            return m_data.at(i).other_fact_setting;
        case _SYSTEM_COLUMN::_SYSTEM_auto_model_limit:
            return m_data.at(i).auto_model_limit;
        default:
            return QVariant();
        }
    }

    return QVariant();
}

void System::setSystemData(int id, _SYSTEM_COLUMN column, QVariant data)
{
    for(int i = 0; i < m_data.size(); ++i)
    {
        if(m_data.at(i).id != id)
            continue;

        switch(column)
        {
        case _SYSTEM_COLUMN::_SYSTEM_id:
        {
            m_data[i].id = data.toInt();
            DataBaseManager::getInstance()->setSystemData(id, column, data);
            return;
        }
        case _SYSTEM_COLUMN::_SYSTEM_welder_id:
        {
            m_data[i].welder_id = data.toInt();
            DataBaseManager::getInstance()->setSystemData(id, column, data);
            return;
        }
        case _SYSTEM_COLUMN::_SYSTEM_single_fact_setting:
        {
            m_data[i].single_fact_setting = data.toInt();
            DataBaseManager::getInstance()->setSystemData(id, column, data);
            return;
        }
        case _SYSTEM_COLUMN::_SYSTEM_general_fact_setting:
        {
            m_data[i].general_fact_setting = data.toInt();
            DataBaseManager::getInstance()->setSystemData(id, column, data);
            return;
        }
        case _SYSTEM_COLUMN::_SYSTEM_other_fact_setting:
        {
            m_data[i].other_fact_setting = data.toInt();
            DataBaseManager::getInstance()->setSystemData(id, column, data);
            return;
        }
        case _SYSTEM_COLUMN::_SYSTEM_auto_model_limit:
        {
            m_data[i].auto_model_limit = data.toInt();
            DataBaseManager::getInstance()->setSystemData(id, column, data);
            return;
        }
        default:
            return;
        }
    }
}

