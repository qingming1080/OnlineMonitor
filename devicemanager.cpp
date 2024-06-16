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

Device *DeviceManager::device(int index) const
{
    if(index < 1 || index > 4)
        return nullptr;

    return m_device[index-1];
}

void DeviceManager::addDevice()
{
    if(deviceNum() >= 4)
        return;

    m_device[deviceNum()] = new Device();
    setDeviceNum(deviceNum()+1);
}
