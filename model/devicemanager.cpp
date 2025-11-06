#include "devicemanager.h"
#include "DataBase/databasemanager.h"
#include "model/deviceinformation.h"
#include "define.h"
#include <qdebug.h>
#include "model/deviceinformation.h"
#include "modbus/hbmodbusclient.h"
#include "signalmanager.h"
#include <QElapsedTimer>
#include "model/devicenames.h"

DeviceManager* DeviceManager::m_ptrInstance = nullptr;
DeviceManager *DeviceManager::getInstance()
{
    if(m_ptrInstance == nullptr)
        m_ptrInstance = new DeviceManager();
    return m_ptrInstance;
}

DeviceManager::DeviceManager(QObject *parent)
    : QObject{parent}
{
    // QElapsedTimer timer;
    // timer.start();
    m_iDeviceCounter = 0;
    setSelectedDeviceIndex(-1);
    QList<int> welderIdlist;
    if(DataBaseManager::getInstance()->getWelderID(welderIdlist) == true)
    {
        QList<Device *> tmpDeviceList;
        for(int i = 0; i < welderIdlist.size(); ++i)
            tmpDeviceList.push_back(new Device(welderIdlist.at(i)));
        setDeviceList(tmpDeviceList);
        setDeviceCounter(m_listDevices.size());
        setSelectedDeviceIndex(0);
    }
    else
    {
        qDebug() << "Failed to query device list from database! ";
    }


    // emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), QString("DeviceManager初始化耗时:%1ms").arg(timer.elapsed()));
}

// Device *DeviceManager::getDeviceByNetworkID(int networkID)
// {
//     for(int i = 0; i < m_listDevices.size(); ++i)
//     {
//         if(m_listDevices.at(i)->getDeviceObj()->getConnectType() == DeviceInfoEnum::TCP_IP
//             && m_listDevices.at(i)->getDeviceObj()->getConnectTypeID() == networkID)
//             return m_listDevices.at(i);
//     }

//     return nullptr;
// }

// Device *DeviceManager::getDeviceByRs232ID(int rs232ID)
// {
//     for(int i = 0; i < m_listDevices.size(); ++i)
//     {
//         if(m_listDevices.at(i)->getDeviceObj()->getConnectType() == DeviceInfoEnum::RS232
//             && m_listDevices.at(i)->getDeviceObj()->getConnectTypeID() == rs232ID)
//             return m_listDevices.at(i);
//     }

//     return nullptr;
// }

int DeviceManager::getSelectedDeviceIndex() const
{
    return m_iSelectedDeviceIndex;
}
int DeviceManager::getDeviceCounter() const
{
    return m_iDeviceCounter;
}
QList<Device *> DeviceManager::getDeviceList() const
{
    return m_listDevices;
}

void DeviceManager::setDeviceCounter(int counter)
{
    if(m_iDeviceCounter != counter)
    {
        m_iDeviceCounter = counter;
        emit notifyDeviceCounterChanged();
    }
}
void DeviceManager::setSelectedDeviceIndex(const int &index)
{
    int weldID = -1;
    if(m_iSelectedDeviceIndex != index)
    {
        m_iSelectedDeviceIndex = index;
        if(index != -1)
            weldID = m_listDevices[index]->GetWelderID();
        emit notifySelectedDeviceIndexChanged(weldID);
    }
}
void DeviceManager::setDeviceList(const QList<Device *> &list)
{
    if(m_listDevices.size() != list.size())
    {
        m_listDevices.clear();
        for(int i = 0; i < list.size(); i++)
            m_listDevices.append(list[i]);
        emit notifyDeviceListChanged();
    }
}

int DeviceManager::getPasswordLevel(QString password)
{
    return DataBaseManager::getInstance()->getLevelByPassword(password);
}

void DeviceManager::setUserPassword(QString newPassword)
{
    DataBaseManager::getInstance()->setUserPassword(newPassword);
}

QString DeviceManager::getHistoryName(int welderID)
{
    // for(int i = 0; i < m_listDevices.size(); ++i)
    // {
    //     if(m_listDevices.at(i)->getDevInfoObject()->id() == welderID)
    //         return m_listDevices.at(i)->getDevInfoObject()->name();
    // }
    return "";
}

bool DeviceManager::addDevice()
{
    if(m_listDevices.size() == 4)
        return false;
    Device* _ptrDev = new Device(-1);
    QList<Device*> tmpDeviceList;
    for(int i = 0; i < m_listDevices.size(); i++)
        tmpDeviceList.append(m_listDevices[i]);
    tmpDeviceList.append(_ptrDev);
    setDeviceList(m_listDevices);
    setDeviceCounter(m_listDevices.size());
    setSelectedDeviceIndex(m_listDevices.size() - 1);
    qDebug() << "add Device";
    return true;
}

bool DeviceManager::removeDevice()
{
    if(m_iSelectedDeviceIndex < 0)
        return false;
    else if(m_iSelectedDeviceIndex >= m_listDevices.size())
        return false;

    QList<Device*> tmpDeviceList;
    for(int i = 0; i < m_listDevices.size(); i++)
        tmpDeviceList.append(m_listDevices[i]);

    Device* _ptrDev = m_listDevices.at(m_iSelectedDeviceIndex);
    tmpDeviceList.removeAt(m_iSelectedDeviceIndex);
    //TODO need to delete database when the object is detoried.
    delete _ptrDev;
    _ptrDev = nullptr;
    setDeviceList(tmpDeviceList);
    setDeviceCounter(m_listDevices.size());
    setSelectedDeviceIndex(-1);
    return true;
}

bool DeviceManager::saveDevice()
{
    if(m_iSelectedDeviceIndex < 0)
        return false;
    else if(m_iSelectedDeviceIndex >= m_listDevices.size())
        return false;
    return m_listDevices[m_iSelectedDeviceIndex]->SaveDevice();
}

bool DeviceManager::editDevice()
{
    if(m_iSelectedDeviceIndex < 0)
        return false;
    else if(m_iSelectedDeviceIndex >= m_listDevices.size())
        return false;
    return m_listDevices[m_iSelectedDeviceIndex]->UpdateDevice();
}
