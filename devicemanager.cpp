#include "devicemanager.h"
#include "DataBase/databasemanager.h"

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

    for(int i = 0; i < list.size(); ++i)
    {
        m_deviceMap.insert(list.at(i), new Device(list.at(i)));
    }
}

int DeviceManager::deviceNum() const
{
    return m_deviceNum;
}

bool DeviceManager::hasDevice(int index) const
{
    return m_deviceMap.count(index)!=0?true:false;
}

Device *DeviceManager::device(int index) const
{
    if(m_deviceMap.count(index) != 0)
        return m_deviceMap.value(index);

    return nullptr;
}

void DeviceManager::addDevice()
{
    for(int i = 1; i <= 4; ++i)
    {
        if(m_deviceMap.count(i)==0)
        {
            m_deviceMap[i] = new Device(i);

            _Configuration_Data data;
            data.welder_id = i;
            DataBaseManager::getInstance()->insertConfigurationDevice(data);
        }
    }

    emit deviceNumChanged();
}

void DeviceManager::removeDevice(int welderID)
{
    m_deviceMap.remove(welderID);

    DataBaseManager::getInstance()->removeConfigurationDevice(welderID);

    emit deviceNumChanged();
}

