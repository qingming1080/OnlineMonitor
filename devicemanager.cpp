#include "devicemanager.h"
#include "DataBase/databasemanager.h"
#include <qdebug.h>

DeviceManager* DeviceManager::s_pInstance = nullptr;


DeviceManager *DeviceManager::getInstance()
{
    if(s_pInstance == nullptr)
        s_pInstance = new DeviceManager();

    return s_pInstance;
}

DeviceManager::DeviceManager(QObject *parent)
    : QObject{parent}
{
    init();
}

void DeviceManager::init()
{
    QList<int> list = DataBaseManager::getInstance()->getDeviceNums();

    m_deviceNum = list.size();

    for(int i = 0; i < list.size(); ++i)
        m_deviceList.push_back(new Device(list.at(i)));
}

int DeviceManager::deviceNum() const
{
    return m_deviceNum;
}

int DeviceManager::getPasswordLevel(QString password)
{
    return DataBaseManager::getInstance()->getLevelByPassword(password);
}

void DeviceManager::setUserPassword(QString newPassword)
{
    DataBaseManager::getInstance()->setUserPassword(newPassword);
}

QList<Device *> DeviceManager::deviceList() const
{
    return m_deviceList;
}


void DeviceManager::addDevice()
{
    for(int i = 0; i < m_deviceList.size() || i < 4; ++i)
    {
        if(m_deviceList.at(i) == nullptr)
        {
            m_deviceList[i] = new Device(i+1);
            _Configuration_Data data;
            data.welder_id = i+1;
            m_deviceNum++;
            DataBaseManager::getInstance()->insertConfigurationDevice(data);
            emit deviceNumChanged();
            emit deviceListChanged();
        }
    }
}

void DeviceManager::removeDevice(int welderID)
{
    if(welderID < 1 || welderID > 4)
        return;
    if(m_deviceList.at(welderID-1)==nullptr)
        return;

    delete m_deviceList.at(welderID-1);
    m_deviceList[welderID-1] = nullptr;
    m_deviceNum--;
    DataBaseManager::getInstance()->removeConfigurationDevice(welderID);

    emit deviceNumChanged();
    emit deviceListChanged();
}

