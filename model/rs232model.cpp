#include "rs232model.h"
#include "DataBase/databasemanager.h"

RS232Model* RS232Model::s_pRS232Model = nullptr;

RS232Model *RS232Model::getInstance()
{
    if(s_pRS232Model == nullptr)
        s_pRS232Model = new RS232Model();

    return s_pRS232Model;
}

int RS232Model::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

QVariant RS232Model::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    int row = index.row();
    _RS232_Data data = m_data.at(row);
    switch(role)
    {
    case QmlEnum::RS232_COLUMN::RS232_id:
        return data.id;
    case QmlEnum::RS232_COLUMN::RS232_port:
        return data.port;
    case QmlEnum::RS232_COLUMN::RS232_baud_rate:
        return data.baud_rate;
    case QmlEnum::RS232_COLUMN::RS232_data_bit:
        return data.data_bit;
    case QmlEnum::RS232_COLUMN::RS232_parity_bit:
        return data.parity_bit;
    case QmlEnum::RS232_COLUMN::RS232_stop_bit:
        return data.stop_bit;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> RS232Model::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[QmlEnum::RS232_COLUMN::RS232_id]             = "id";
    roles[QmlEnum::RS232_COLUMN::RS232_port]           = "port";
    roles[QmlEnum::RS232_COLUMN::RS232_baud_rate]      = "baud_rate";
    roles[QmlEnum::RS232_COLUMN::RS232_data_bit]       = "data_bit";
    roles[QmlEnum::RS232_COLUMN::RS232_parity_bit]     = "parity_bit";
    roles[QmlEnum::RS232_COLUMN::RS232_stop_bit]       = "stop_bit";

    return roles;
}

QVariant RS232Model::getDataByWelderID(int welderID, int role) const
{
    for(int i = 0; i < m_data.size(); ++i)
    {
        if(m_data.at(i).id != welderID)
            continue;

        switch(role)
        {
        case QmlEnum::RS232_COLUMN::RS232_id:
        {
            return m_data.at(i).id;
        }
        case QmlEnum::RS232_COLUMN::RS232_port:
        {
            return m_data.at(i).port;
        }
        case QmlEnum::RS232_COLUMN::RS232_baud_rate:
        {
            return m_data.at(i).baud_rate;
        }
        case QmlEnum::RS232_COLUMN::RS232_data_bit:
        {
            return QString("%1%2").arg(m_data.at(i).data_bit).arg("bit");
        }
        case QmlEnum::RS232_COLUMN::RS232_parity_bit:
        {
            return m_data.at(i).parity_bit;
        }
        case QmlEnum::RS232_COLUMN::RS232_stop_bit:
        {
            return QString("%1%2").arg(m_data.at(i).stop_bit).arg("bit");
        }
        default:
            return QVariant();
        }
    }

    return QVariant();
}

void RS232Model::setRS232Data(int id, int column, QVariant data)
{
    for(int i = 0; i < m_data.size(); ++i)
    {
        beginResetModel();
        if(m_data.at(i).id != id)
            continue;

        QmlEnum::RS232_COLUMN index = (QmlEnum::RS232_COLUMN)column;
        switch(index)
        {
        case QmlEnum::RS232_COLUMN::RS232_id:
        {
            m_data[i].id = data.toInt();
            DataBaseManager::getInstance()->setRS232Data(id,index , data);
            endResetModel();
            return;
        }
        case QmlEnum::RS232_COLUMN::RS232_port:
        {
            m_data[i].port = data.toString();
            DataBaseManager::getInstance()->setRS232Data(id, index, data);
            endResetModel();
            return;
        }
        case QmlEnum::RS232_COLUMN::RS232_baud_rate:
        {
            m_data[i].baud_rate = data.toInt();
            DataBaseManager::getInstance()->setRS232Data(id, index, data);
            endResetModel();
            return;
        }
        case QmlEnum::RS232_COLUMN::RS232_data_bit:
        {
            m_data[i].data_bit = data.toInt();
            DataBaseManager::getInstance()->setRS232Data(id, index, data);
            endResetModel();
            return;
        }
        case QmlEnum::RS232_COLUMN::RS232_parity_bit:
        {
            m_data[i].parity_bit = data.toString();
            DataBaseManager::getInstance()->setRS232Data(id, index, data);
            endResetModel();
            return;
        }
        case QmlEnum::RS232_COLUMN::RS232_stop_bit:
        {
            m_data[i].stop_bit = data.toInt();
            DataBaseManager::getInstance()->setRS232Data(id, index, data);
            endResetModel();
            return;
        }
        default:
            return;
        }
    }
}

RS232Model::RS232Model(QObject *parent)
    : QAbstractListModel{parent}
{
    m_data = DataBaseManager::getInstance()->getRS232Data();
}
