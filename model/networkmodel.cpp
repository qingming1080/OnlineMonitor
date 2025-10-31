#include "networkmodel.h"
#include "DataBase/databasemanager.h"
#include "signalmanager.h"
#include <QElapsedTimer>
#include "log/localrecord.h"

NetworkModel* NetworkModel::m_ptrInstance = nullptr;

NetworkModel *NetworkModel::getInstance()
{
    if(m_ptrInstance == nullptr)
        m_ptrInstance = new NetworkModel();
    return m_ptrInstance;
}

NetworkModel::NetworkModel(QObject *parent)
    : QAbstractListModel{parent}
{
    // QElapsedTimer timer;
    // timer.start();
    m_listETHPort.append({{"key", "ETH1"}, {"value", 0}});
    m_listETHPort.append({{"key", "ETH2"}, {"value", 1}});
    m_listETHPort.append({{"key", "ETH3"}, {"value", 2}});
    m_listETHPort.append({{"key", "ETH4"}, {"value", 3}});

    // m_data = DataBaseManager::getInstance()->getNetworkData();

    // QString text = QString("NetWork_初始化共耗时:%1ms").arg(timer.elapsed());
    // emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), text);
}

int NetworkModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listETHPort.size();
}

QVariant NetworkModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if (!index.isValid() || index.row() >= m_listETHPort.count())
        return QVariant();

    const auto &item = m_listETHPort.at(index.row());
    if (role == KeyRole)
        return item["key"];
    else if (role == ValueRole)
        return item["value"];

    return QVariant();
}

QHash<int, QByteArray> NetworkModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[KeyRole] = "key";
    roles[ValueRole] = "value";
    return roles;
}

QVariant NetworkModel::get(int index) const
{
    if (index < 0 || index >= m_listETHPort.count())
        return QVariant();
    
    // Return a QVariantMap that QML can access with .key and .value
    QVariantMap result;
    result["key"] = m_listETHPort.at(index)["key"];
    result["value"] = m_listETHPort.at(index)["value"];
    return result;
}






