#include "devicemanager.h"

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

}

int DeviceManager::deviceNum() const
{
    return m_deviceNum;
}

void DeviceManager::setDeviceNum(int newDeviceNum)
{
    if (m_deviceNum == newDeviceNum)
        return;
    m_deviceNum = newDeviceNum;
    emit deviceNumChanged();
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

void DeviceManager::addDevice(int index)
{
    if(m_deviceMap.count(index) != 0)
        return;

    m_deviceMap[index] = new Device(index);
    setDeviceNum(deviceNum()+1);
}
