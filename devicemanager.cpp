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

void DeviceManager::addDevice()
{
    if(deviceNum() >= 4)
        return;

    m_device[deviceNum()] = new Device();
    setDeviceNum(deviceNum()+1);
}

Device *DeviceManager::device_1() const
{
    return m_device[0];
}

Device *DeviceManager::device_2() const
{
    return m_device[1];
}

Device *DeviceManager::device_3() const
{
    return m_device[2];
}

Device *DeviceManager::device_4() const
{
    return m_device[3];
}

