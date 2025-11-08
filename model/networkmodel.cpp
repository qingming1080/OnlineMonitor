#include "networkmodel.h"
#include "devicemanager.h"
#include "deviceinformation.h"
#include <QDebug>
NetworkModel* NetworkModel::m_ptrInstance = nullptr;

NetworkModel *NetworkModel::getInstance()
{
    if(m_ptrInstance == nullptr)
        m_ptrInstance = new NetworkModel();
    return m_ptrInstance;
}

int NetworkModel::getEthIndex() const
{
    return m_iCurrentEthIndex;
}

void NetworkModel::setEthIndex(const int &index)
{
    if(m_iCurrentEthIndex != index)
    {
        m_iCurrentEthIndex = index;
        emit notifyEthIndexChanged();
        qDebug() << "setEthIndex: " << index;
    }
}

int NetworkModel::getConnectTypeId() const
{
    return m_iConnectTypeId;
}

void NetworkModel::setConnectTypeId(const int &typeId)
{
    if(m_iConnectTypeId != typeId)
    {
        m_iConnectTypeId = typeId;

        emit notifyConnectTypeIdChanged();
    }
}

QString NetworkModel::getPortNumber() const
{
    return QString::number(m_iServerPort);
}


void NetworkModel::setPortNumber(const QString &port)
{
    bool isOk = false;
    int iServerPort = port.toInt(&isOk);
    if(isOk == true && iServerPort != m_iServerPort)
    {
        m_iServerPort = iServerPort;
        emit notifyPortNumberChanged();
    }
}

QString NetworkModel::getLocalIP() const
{
    return m_strLocalIP;
}

void NetworkModel::setLocalIP(const QString &ip)
{
    if(ip != m_strLocalIP)
    {
        m_strLocalIP = ip;
        emit notifyLocalIPChanged();
    }
}

QString NetworkModel::getRemoteIP() const
{
    return m_strRemoteIP;
}

void NetworkModel::setRemoteIP(const QString &ip)
{
    if(ip != m_strRemoteIP)
    {
        m_strRemoteIP = ip;
        emit notifyRemoteIPChanged();
    }
}

NetworkModel::NetworkModel(QObject *parent)
    : QAbstractListModel{parent}
{
    m_iCurrentWelderId = -1;
    InitListManager();
    UpdateWelderID();

    // NotifySelectedDeviceIndexChanged(m_iCurrentWelderId);

    connect(DeviceManager::getInstance(), &DeviceManager::notifySelectedDeviceIndexChanged,
            this, &NetworkModel::NotifySelectedDeviceIndexChanged);
}

void NetworkModel::NotifySelectedDeviceIndexChanged(int welderID)
{
    qDebug() << "CurrentWelderId: " << welderID;
    m_iCurrentWelderId = welderID;
    for(auto iter = m_listManager.begin(); iter != m_listManager.end(); iter++)
    {
		if(iter.value().WelderId == m_iCurrentWelderId)
        {
            if(m_iCurrentWelderId != -1)
            {
                setPortNumber(QString::number(iter.value().ServerPort));
                setLocalIP(iter.value().LocalIP);
                setRemoteIP(iter.value().RemoteIP);
                setConnectTypeId(iter.key());
            }
            else
            {
                setPortNumber("4000");
                setLocalIP("xxx.xxx.xxx.xxx");
                setRemoteIP("xxx.xxx.xxx.xxx");
                setConnectTypeId(iter.key());
            }
            break;
        }
	}
    modelReset();
    int index = indexOfEthRole(m_iConnectTypeId);
    qDebug() << "index: " << index;
    if(index != -1)
        setEthIndex(index);
    else
        setEthIndex(0);
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
    else if (role == IdRole)
        return item["Id"];
    return QVariant();
}

QHash<int, QByteArray> NetworkModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[KeyRole] = "key";
    roles[IdRole] = "Id";
    return roles;
}

void NetworkModel::modelReset()
{
    beginResetModel();
    m_listETHPort.clear();

    // Build m_listETHPort from m_listManager. Use a sequential index for display (ETH1..)
    int index = 0;
    for (auto iter = m_listManager.constBegin(); iter != m_listManager.constEnd(); iter++)
    {
        index++;
        QString strTitle = QString("ETH%1").arg(index);
        QVariantMap map;
        if((iter.value().WelderId == -1) || iter.value().WelderId == m_iCurrentWelderId)
        {
            map["key"] = strTitle;
            map["Id"] = iter.key();
            m_listETHPort.append(map);
        }
    }

    endResetModel();
}

bool NetworkModel::InitListManager()
{
    bool bResult = false;
    QList<DataBaseManager::DB_NETWORK> networkList;
    DataBaseManager::getInstance()->getAllNetworkConfigure(networkList);
    m_listManager.clear();
    for(int i = 0; i< networkList.count(); i++)
    {
        NETWORK_MANAGER manager;
        manager.ModbusDeviceId = i;
        manager.WelderId = -1;
        manager.LocalIP = networkList.at(i).LocalIP;
        manager.RemoteIP = networkList.at(i).RemoteIP;
        manager.LocalPort = networkList.at(i).LocalPort;
        manager.Protocol = networkList.at(i).Protocol;
        manager.ServerPort = networkList.at(i).ServerPort;
        manager.Type = networkList.at(i).Type;
        manager.User = networkList.at(i).User;
        m_listManager.insert(networkList.at(i).Id, manager);
        qDebug() << "  Id:" << manager.ModbusDeviceId
                 << " LocalIP:" << manager.LocalIP
                 << " RemoteIP:" << manager.RemoteIP
                 << " LocalPort:" << manager.LocalPort
                 << " ServerPort:" << manager.ServerPort;
        qDebug() << "  Protocol:" << manager.Protocol
                 << " Type:" << manager.Type
                 << " WelderId:" << manager.WelderId;
    }
    bResult = !m_listManager.empty();
    qDebug() << "m_listManger.cout: " << m_listManager.size();
    return bResult;
}

bool NetworkModel::UpdateWelderID()
{
    QList<DataBaseManager::DB_CONFIGURE> configureList;
    DataBaseManager::getInstance()->getAllConfigureationDevice(configureList);
    for(int i = 0; i < configureList.count(); i++)
    {
        qDebug() << "m_listManger[" << i <<"].ConnectType: " << configureList[i].ConnectType;
        qDebug() << "m_listManger[" << i <<"].ConnectTypeId: " << configureList[i].ConnectTypeId;
        if(configureList[i].ConnectType == DeviceInfoEnum::TCP_IP)
        {
            auto iter = m_listManager.find(configureList[i].ConnectTypeId);
            if(iter != m_listManager.end())
            {
                iter.value().WelderId = configureList[i].WelderID;
                qDebug() << "WelderID: " << iter.value().WelderId;
            }
        }
	}
    return !configureList.empty();
}

int NetworkModel::GetModbusDeviceID()
{
    int iModbusDeviceId = -1;
    for (auto iter = m_listManager.constBegin(); iter != m_listManager.constEnd(); iter++)
    {
        if(iter.value().WelderId == m_iCurrentWelderId)
        {
            iModbusDeviceId = iter.value().ModbusDeviceId;
            break;
        }
    }
    return iModbusDeviceId;
}

QVariant NetworkModel::get(int index) const
{
    qDebug() << "c++ index：" << index;
    if (index < 0 || index >= m_listETHPort.count())
        return QVariant();
    
    // Return a QVariantMap that QML can access with .key and .value
    QVariantMap result;
    result["key"] = m_listETHPort.at(index)["key"];
    result["Id"] = m_listETHPort.at(index)["Id"];
    return result;
}

bool NetworkModel::UpdateDatabase()
{
    bool bResult = false;
    DataBaseManager::DB_NETWORK network;
    auto iter = m_listManager.find(m_iConnectTypeId);
    if(iter != m_listManager.end())
    {
        network.LocalIP = m_strLocalIP;
        network.RemoteIP = m_strRemoteIP;
        network.LocalPort = iter.value().LocalPort;
        network.ServerPort = m_iServerPort;
        network.Protocol = iter.value().Protocol;
        network.Type = iter.value().Type;
        network.User = iter.value().User;
        bResult = DataBaseManager::getInstance()->updateNetworkConfigure(m_iConnectTypeId, network);
    }
    return bResult;
}

int NetworkModel::indexOfEthRole(const int id) const
{
    for (int i = 0; i < m_listETHPort.size(); ++i) 
    {
        bool ok = false;
        int tmp = m_listETHPort.at(i).value("Id").toInt(&ok);
        if (ok && tmp == id) 
            return i;
    }
    return -1;
}
