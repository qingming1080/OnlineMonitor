#include "networkmodel.h"
#include "DataBase/databasemanager.h"
#include "signalmanager.h"
#include <QElapsedTimer>
#include "log/localrecord.h"

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
    QElapsedTimer timer;
    timer.start();

    m_data = DataBaseManager::getInstance()->getNetworkData();

    QString text = QString("NetWork_初始化共耗时:%1ms").arg(timer.elapsed());
    emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), text);
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
    case QmlEnum::NETWORK_COLUMN::NETWORK_id:
        return data.id;
    case QmlEnum::NETWORK_COLUMN::NETWORK_type:
        return data.type;
    case QmlEnum::NETWORK_COLUMN::NETWORK_protocol:
        return data.protocol;
    case QmlEnum::NETWORK_COLUMN::NETWORK_local_ip:
        return data.local_ip;
    case QmlEnum::NETWORK_COLUMN::NETWORK_local_port:
        return data.local_port;
    case QmlEnum::NETWORK_COLUMN::NETWORK_remote_ip:
        return data.remote_ip;
    case QmlEnum::NETWORK_COLUMN::NETWORK_server_port:
        return data.server_port;
    case QmlEnum::NETWORK_COLUMN::NETWORK_user:
        return data.user;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> NetworkModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[QmlEnum::NETWORK_COLUMN::NETWORK_id]          = "id";
    roles[QmlEnum::NETWORK_COLUMN::NETWORK_type]        = "type";
    roles[QmlEnum::NETWORK_COLUMN::NETWORK_protocol]    = "protocol";
    roles[QmlEnum::NETWORK_COLUMN::NETWORK_local_ip]    = "local_ip";
    roles[QmlEnum::NETWORK_COLUMN::NETWORK_local_port]  = "local_port";
    roles[QmlEnum::NETWORK_COLUMN::NETWORK_remote_ip]   = "remote_ip";
    roles[QmlEnum::NETWORK_COLUMN::NETWORK_server_port] = "server_port";
    roles[QmlEnum::NETWORK_COLUMN::NETWORK_user]        = "user";

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
        case QmlEnum::NETWORK_COLUMN::NETWORK_id:
        {
            return m_data.at(i).id;
        }
        case QmlEnum::NETWORK_COLUMN::NETWORK_type:
        {
            return m_data.at(i).type;
        }
        case QmlEnum::NETWORK_COLUMN::NETWORK_protocol:
        {
            return m_data.at(i).protocol;
        }
        case QmlEnum::NETWORK_COLUMN::NETWORK_local_ip:
        {
            return m_data.at(i).local_ip;
        }
        case QmlEnum::NETWORK_COLUMN::NETWORK_local_port:
        {
            return m_data.at(i).local_port;
        }
        case QmlEnum::NETWORK_COLUMN::NETWORK_remote_ip:
        {
            return m_data.at(i).remote_ip;
        }
        case QmlEnum::NETWORK_COLUMN::NETWORK_server_port:
        {
            return m_data.at(i).server_port;
        }
        case QmlEnum::NETWORK_COLUMN::NETWORK_user:
        {
            return m_data.at(i).user;
        }
        default:
            return QVariant();
        }
    }

    return QVariant();
}

void NetworkModel::setNetworkData(int id, int column, QVariant data)
{
    for(int i = 0; i < m_data.size(); ++i)
    {
        beginResetModel();
        if(m_data.at(i).id != id)
            continue;
        QmlEnum::NETWORK_COLUMN index = (QmlEnum::NETWORK_COLUMN)column;
        switch(index)
        {
        case QmlEnum::NETWORK_COLUMN::NETWORK_id:
        {
            m_data[i].id = data.toInt();
            DataBaseManager::getInstance()->setNetworkData(id, index, data);
            endResetModel();
            return;
        }
        case QmlEnum::NETWORK_COLUMN::NETWORK_type:
        {
            m_data[i].type = data.toInt();
            DataBaseManager::getInstance()->setNetworkData(id, index, data);
            endResetModel();
            return;
        }
        case QmlEnum::NETWORK_COLUMN::NETWORK_protocol:
        {
            m_data[i].protocol = data.toInt();
            DataBaseManager::getInstance()->setNetworkData(id, index, data);
            endResetModel();
            return;
        }
        case QmlEnum::NETWORK_COLUMN::NETWORK_local_ip:
        {
            m_data[i].local_ip = data.toString();
            DataBaseManager::getInstance()->setNetworkData(id, index, data);
            endResetModel();
            return;
        }
        case QmlEnum::NETWORK_COLUMN::NETWORK_local_port:
        {
            m_data[i].local_port = data.toInt();
            DataBaseManager::getInstance()->setNetworkData(id, index, data);
            endResetModel();
            return;
        }
        case QmlEnum::NETWORK_COLUMN::NETWORK_remote_ip:
        {
            m_data[i].remote_ip = data.toString();
            DataBaseManager::getInstance()->setNetworkData(id, index, data);
            endResetModel();
            return;
        }
        case QmlEnum::NETWORK_COLUMN::NETWORK_server_port:
        {
            m_data[i].server_port = data.toInt();
            DataBaseManager::getInstance()->setNetworkData(id, index, data);
            endResetModel();
            return;
        }
        case QmlEnum::NETWORK_COLUMN::NETWORK_user:
        {
            m_data[i].user = data.toString();
            DataBaseManager::getInstance()->setNetworkData(id, index, data);
            endResetModel();
            return;
        }
        default:
            return;
        }
    }
}
