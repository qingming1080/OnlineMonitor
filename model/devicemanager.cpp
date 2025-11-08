#include "devicemanager.h"
#include "DataBase/databasemanager.h"
#include <qdebug.h>
#include "networkmodel.h"
#include "rs232model.h"

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
    m_iDeviceCounter = 0;
    setSelectedDeviceIndex(-1);

    if(InitDeviceList() == true)
    {
        setSelectedDeviceIndex(0);
    }
    else
    {
        qDebug() << "Failed to query device list from database! ";
    }
}

bool DeviceManager::InitDeviceList()
{
    bool bResult = false;
    QList<int> welderIdlist;
    if(DataBaseManager::getInstance()->getWelderID(welderIdlist) == true)
    {
        QList<Device *> tmpDeviceList;
        for(int i = 0; i < welderIdlist.size(); i++)
            tmpDeviceList.push_back(new Device(welderIdlist.at(i)));
        setDeviceList(tmpDeviceList);
        setDeviceCounter(m_listDevices.size());
        bResult = true;
    }
    return bResult;
}



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
    m_iSelectedDeviceIndex = index;
    if(index != -1)
    {
        weldID = m_listDevices[index]->GetWelderID();
        NetworkModel::getInstance()->NotifySelectedDeviceIndexChanged(weldID);
        RS232Model::getInstance()->NotifySelectedDeviceIndexChanged(weldID);
    }
    emit notifySelectedDeviceIndexChanged();
}
void DeviceManager::setDeviceList(const QList<Device *> &list)
{
    Device* _obj = nullptr;
    for(int i = 0; i < m_listDevices.size(); i++)
    {
        _obj = m_listDevices[i];
        delete _obj;
        _obj = nullptr;
    }
    m_listDevices.clear();
    for(int i = 0; i < list.size(); i++)
    {
        _obj = list[i];
        m_listDevices.append(_obj);
    }
    emit notifyDeviceListChanged();
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
    setDeviceList(tmpDeviceList);
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
    _ptrDev->RemoveDevice();
    tmpDeviceList.removeAt(m_iSelectedDeviceIndex);
    //TODO need to delete database when the object is detoried.
    delete _ptrDev;
    _ptrDev = nullptr;
    setDeviceList(tmpDeviceList);
    setDeviceCounter(m_listDevices.size());
    setSelectedDeviceIndex(0);
    return true;
}

bool DeviceManager::saveDevice()
{
    if(m_iSelectedDeviceIndex < 0)
        return false;
    else if(m_iSelectedDeviceIndex >= m_listDevices.size())
        return false;
    m_listDevices[m_iSelectedDeviceIndex]->SaveDevice();
    return InitDeviceList();
}
