#include "networkmodel.h"
#include "DataBase/databasemanager.h"

NetworkModel* NetworkModel::s_pNetworkModel = nullptr;

NetworkModel *NetworkModel::getInstance()
{
    if(s_pNetworkModel == nullptr)
        s_pNetworkModel = new NetworkModel();

    return s_pNetworkModel;
}

NetworkModel::NetworkModel(QObject *parent)
    : QAbstractListModel{parent}
{
    m_data = DataBaseManager::getInstance()->getNetworkData();
}

int NetworkModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

QVariant NetworkModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    int row = index.row();
    _Network_Data data = m_data.at(row);
    switch(role)
    {
    case _NETWORK_COLUMN::_NETWORK_id:
        return data.id;
    case _NETWORK_COLUMN::_NETWORK_type:
        return data.type;
    case _NETWORK_COLUMN::_NETWORK_protocol:
        return data.protocol;
    case _NETWORK_COLUMN::_NETWORK_local_ip:
        return data.local_ip;
    case _NETWORK_COLUMN::_NETWORK_local_port:
        return data.local_port;
    case _NETWORK_COLUMN::_NETWORK_remote_ip:
        return data.remote_ip;
    case _NETWORK_COLUMN::_NETWORK_server_port:
        return data.server_port;
    case _NETWORK_COLUMN::_NETWORK_user:
        return data.user;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> NetworkModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[_NETWORK_COLUMN::_NETWORK_id]          = "id";
    roles[_NETWORK_COLUMN::_NETWORK_type]        = "type";
    roles[_NETWORK_COLUMN::_NETWORK_protocol]    = "protocol";
    roles[_NETWORK_COLUMN::_NETWORK_local_ip]    = "local_ip";
    roles[_NETWORK_COLUMN::_NETWORK_local_port]  = "local_port";
    roles[_NETWORK_COLUMN::_NETWORK_remote_ip]   = "remote_ip";
    roles[_NETWORK_COLUMN::_NETWORK_server_port] = "server_port";
    roles[_NETWORK_COLUMN::_NETWORK_user]        = "user";

    return roles;
}

QVariant NetworkModel::getDataByWelderID(int welderID, int role) const
{
    for(int i = 0; i < m_data.size(); ++i)
    {
        if(m_data.at(i).id != welderID)
            continue;

        switch(role)
        {
        case _NETWORK_COLUMN::_NETWORK_id:
        {
            return m_data.at(i).id;
        }
        case _NETWORK_COLUMN::_NETWORK_type:
        {
            return m_data.at(i).type;
        }
        case _NETWORK_COLUMN::_NETWORK_protocol:
        {
            return m_data.at(i).protocol;
        }
        case _NETWORK_COLUMN::_NETWORK_local_ip:
        {
            return m_data.at(i).local_ip;
        }
        case _NETWORK_COLUMN::_NETWORK_local_port:
        {
            return m_data.at(i).local_port;
        }
        case _NETWORK_COLUMN::_NETWORK_remote_ip:
        {
            return m_data.at(i).remote_ip;
        }
        case _NETWORK_COLUMN::_NETWORK_server_port:
        {
            return m_data.at(i).server_port;
        }
        case _NETWORK_COLUMN::_NETWORK_user:
        {
            return m_data.at(i).user;
        }
        default:
            return QVariant();
        }
    }

    return QVariant();
}

void NetworkModel::setNetworkData(int id, _NETWORK_COLUMN column, QVariant data)
{
    for(int i = 0; i < m_data.size(); ++i)
    {
        if(m_data.at(i).id != id)
            continue;

        switch(column)
        {
        case _NETWORK_COLUMN::_NETWORK_id:
        {
            m_data[i].id = data.toInt();
            DataBaseManager::getInstance()->setNetworkData(id, column, data);
            return;
        }
        case _NETWORK_COLUMN::_NETWORK_type:
        {
            m_data[i].type = data.toInt();
            DataBaseManager::getInstance()->setNetworkData(id, column, data);
            return;
        }
        case _NETWORK_COLUMN::_NETWORK_protocol:
        {
            m_data[i].protocol = data.toInt();
            DataBaseManager::getInstance()->setNetworkData(id, column, data);
            return;
        }
        case _NETWORK_COLUMN::_NETWORK_local_ip:
        {
            m_data[i].local_ip = data.toString();
            DataBaseManager::getInstance()->setNetworkData(id, column, data);
            return;
        }
        case _NETWORK_COLUMN::_NETWORK_local_port:
        {
            m_data[i].local_port = data.toInt();
            DataBaseManager::getInstance()->setNetworkData(id, column, data);
            return;
        }
        case _NETWORK_COLUMN::_NETWORK_remote_ip:
        {
            m_data[i].remote_ip = data.toString();
            DataBaseManager::getInstance()->setNetworkData(id, column, data);
            return;
        }
        case _NETWORK_COLUMN::_NETWORK_server_port:
        {
            m_data[i].server_port = data.toInt();
            DataBaseManager::getInstance()->setNetworkData(id, column, data);
            return;
        }
        case _NETWORK_COLUMN::_NETWORK_user:
        {
            m_data[i].user = data.toString();
            DataBaseManager::getInstance()->setNetworkData(id, column, data);
            return;
        }
        default:
            return;
        }
    }
}
