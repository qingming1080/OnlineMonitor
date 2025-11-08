#include "rs232model.h"
#include "devicemanager.h"
#include "DataBase/databasemanager.h"
#include "deviceinformation.h"
#include "baudratemodel.h"
#include "databitsmodel.h"
#include "paritymodel.h"
#include "stopbitsmodel.h"
#include <QDebug>
RS232Model* RS232Model::m_ptrInstance = nullptr;
RS232Model *RS232Model::getInstance()
{
    if(m_ptrInstance == nullptr)
        m_ptrInstance = new RS232Model();
    return m_ptrInstance;
}

int RS232Model::getComIndex() const
{
    return m_iCurrentComIndex;
}

void RS232Model::setComIndex(const int &index)
{
    if(m_iCurrentComIndex != index)
    {
        m_iCurrentComIndex = index;
        emit notifyComIndexChanged();

    }
}

int RS232Model::getConnectTypeId() const
{
    return m_iConnectTypeId;
}

void RS232Model::setConnectTypeId(const int &typeId)
{
    if(m_iConnectTypeId != typeId)
    {
        m_iConnectTypeId = typeId;

        emit notifyConnectTypeIdChanged();
    }
}

int RS232Model::getBaudRate() const
{
    return m_iCurrentBaudRate;
}

void RS232Model::setBaudRate(const int &baudRate)
{
    int index = 0;
    if(m_iCurrentBaudRate != baudRate)
    {
        m_iCurrentBaudRate = baudRate;
        index = BaudRateModel::getInstance()->indexOfValueRole(m_iCurrentBaudRate);
        BaudRateModel::getInstance()->setBaudRateIndex(index);
        emit notifyBaudRateChanged();
    }
}
int RS232Model::getDataBits() const
{
    return m_iCurrentDataBits;
}

void RS232Model::setDataBits(const int &dataBits)
{
    int index = 0;
    if(m_iCurrentDataBits != dataBits)
    {
        m_iCurrentDataBits = dataBits;
        index = DataBitsModel::getInstance()->indexOfValueRole(m_iCurrentDataBits);
        DataBitsModel::getInstance()->setDataBitsIndex(index);
        emit notifyDataBitsChanged();
    }
}

int RS232Model::getParityBits() const
{
    return m_iCurrentParityBits;
}

void RS232Model::setParityBits(const int &parityBits)
{
    int index = 0;
    if(m_iCurrentParityBits != parityBits)
    {
        m_iCurrentParityBits = parityBits;
        index = ParityModel::getInstance()->indexOfValueRole(m_iCurrentParityBits);
        ParityModel::getInstance()->setParityBitsIndex(index);
        emit notifyParityBitsChanged();
    }
}

int RS232Model::getStopBits() const
{
    return m_iCurrentStopBits;
}

void RS232Model::setStopBits(const int &stopBits)
{
    int index = 0;
    if(m_iCurrentStopBits != stopBits)
    {
        m_iCurrentStopBits = stopBits;
        index = StopBitsModel::getInstance()->indexOfValueRole(m_iCurrentStopBits);
        StopBitsModel::getInstance()->setStopBitsIndex(index);
        emit notifyStopBitsChanged();
    }
}

RS232Model::RS232Model(QObject *parent)
    : QAbstractListModel{parent}
{
    m_iCurrentWelderId = 1;
    InitListManager();
    UpdateWelderID();
    // NotifySelectedDeviceIndexChanged(m_iCurrentWelderId);

    connect(DeviceManager::getInstance(), &DeviceManager::notifySelectedDeviceIndexChanged,
            this, &RS232Model::NotifySelectedDeviceIndexChanged);
}

void RS232Model::NotifySelectedDeviceIndexChanged(int welderID)
{
    qDebug() << "CurrentWelderId: " << welderID;
    int index = 0;
    m_iCurrentWelderId = welderID;
    for(auto iter = m_listManager.begin(); iter != m_listManager.end(); iter++)
    {
		if(iter.value().WelderId == m_iCurrentWelderId)
        {
            if(m_iCurrentWelderId != -1)
            {
                setBaudRate(iter.value().BaudRate);
                setDataBits(iter.value().DataBit);
                setParityBits(iter.value().ParityBit);
                setStopBits(iter.value().StopBit);
			}
            else
            {
                setBaudRate(QSerialPort::Baud9600);
                setDataBits(QSerialPort::Data8);
                setParityBits(QSerialPort::NoParity);
                setStopBits(QSerialPort::OneStop);
            }
            setConnectTypeId(iter.key());
            break;
        }
	}
    modelReset();
    index = indexOfComRole(m_iConnectTypeId);
    qDebug() << "index: " << index;
    if(index != -1)
        setComIndex(index);
    else
        setComIndex(0);
}

int RS232Model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listComPort.size();
}

QVariant RS232Model::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if (!index.isValid() || index.row() >= m_listComPort.count())
        return QVariant();

    const auto &item = m_listComPort.at(index.row());
    if (role == KeyRole)
        return item["key"];
    else if (role == IdRole)
        return item["Id"];
    return QVariant();
}

QHash<int, QByteArray> RS232Model::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[KeyRole] = "key";
    roles[IdRole] = "Id";
    return roles;
}

void RS232Model::modelReset()
{
    beginResetModel();
    m_listComPort.clear();

    // Build m_listETHPort from m_listManager. Use a sequential index for display (ETH1..)
    int index = 0;
    for (auto iter = m_listManager.constBegin(); iter != m_listManager.constEnd(); iter++)
    {
        index++;
        QString strTitle = QString("Com%1").arg(index);
        QVariantMap map;
        if((iter.value().WelderId == -1) || iter.value().WelderId == m_iCurrentWelderId)
        {
            map["key"] = strTitle;
            map["Id"] = iter.key();
            m_listComPort.append(map);
        }
    }

    endResetModel();
}

bool RS232Model::InitListManager()
{
    bool bResult = false;
    QList<DataBaseManager::DB_RS232> rs232List;
    DataBaseManager::getInstance()->getAllRS232Configure(rs232List);
    m_listManager.clear();
    for(int i = 0; i< rs232List.count(); i++)
    {
		RS232_MANAGER manager;
        manager.ModbusDeviceId = i;
        manager.WelderId = -1;
        manager.BaudRate = rs232List[i].BaudRate;
        manager.DataBit = rs232List[i].DataBit;
        manager.ParityBit = rs232List[i].ParityBit;
        manager.Port = rs232List[i].Port;
        manager.StopBit = rs232List[i].StopBit;
        m_listManager.insert(rs232List.at(i).Id, manager);
    }
    bResult = !m_listManager.empty();
    qDebug() << "m_listManger.cout: " << m_listManager.size();
    return bResult;
}

bool RS232Model::UpdateWelderID()
{
    QList<DataBaseManager::DB_CONFIGURE> configureList;
    DataBaseManager::getInstance()->getAllConfigureationDevice(configureList);
    for(int i = 0; i < configureList.count(); i++)
    {
        qDebug() << "m_listManger[" << i <<"].ConnectType: " << configureList[i].ConnectType;
        qDebug() << "m_listManger[" << i <<"].ConnectTypeId: " << configureList[i].ConnectTypeId;
        if(configureList[i].ConnectType == DeviceInfoEnum::RS232)
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

int RS232Model::GetModbusDeviceID()
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

QVariant RS232Model::get(int index) const
{
	qDebug() << "c++ index: " << index;
    if (index < 0 || index >= m_listComPort.count())
        return QVariant();
    
    // Return a QVariantMap that QML can access with .key and .value
    QVariantMap result;
    result["key"] = m_listComPort.at(index)["key"];
    result["value"] = m_listComPort.at(index)["value"];
    return result;
}

bool RS232Model::UpdateDatabase()
{
    bool bResult = false;
    DataBaseManager::DB_RS232 rs232;
    auto iter = m_listManager.find(m_iConnectTypeId);
    if(iter != m_listManager.end())
    {
        rs232.BaudRate = m_iCurrentBaudRate;
        rs232.DataBit = m_iCurrentDataBits;
        rs232.ParityBit = m_iCurrentParityBits;
        rs232.StopBit = m_iCurrentStopBits;
        bResult = DataBaseManager::getInstance()->updateRS232Configure(m_iConnectTypeId, rs232);
    }
    return bResult;
}

int RS232Model::indexOfComRole(const int id) const
{
    for (int i = 0; i < m_listComPort.size(); ++i)
    {
        bool ok = false;
        int tmp = m_listComPort.at(i).value("Id").toInt(&ok);
        if (ok && tmp == id) 
            return i;
    }
    return -1;
}
