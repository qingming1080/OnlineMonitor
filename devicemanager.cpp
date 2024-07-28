#include "devicemanager.h"
#include "DataBase/databasemanager.h"
#include "model/deviceinformation.h"
#include "define.h"
#include <qdebug.h>
#include "model/deviceinformation.h"

#include <QElapsedTimer>
#include "log/localrecord.h"

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
    QElapsedTimer timer;
    timer.start();

    init();

    LocalRecord::getInstance()->addRecord(QDateTime::currentDateTime(), QString("DeviceManager初始化耗时:%1ms").arg(timer.elapsed()));
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

QString DeviceManager::getHistoryName(int welderID)
{
    for(int i = 0; i < m_deviceList.size(); ++i)
    {
        if(m_deviceList.at(i)->pDeviceInformation()->id() == welderID)
            return m_deviceList.at(i)->pDeviceInformation()->name();
    }

    return "";
}

QList<Device *> DeviceManager::deviceList() const
{
    return m_deviceList;
}


void DeviceManager::addDevice()
{
    if(m_deviceList.size() == 4)
        return;

    _Configuration_Data data;
    for(int i = 0; i < 4; ++i)
    {
        if(i == m_deviceList.size())
        {
            m_deviceList.push_back(new Device(i+1));
            data.welder_id = i + 1;
            break;
        }
        if(m_deviceList.at(i) != nullptr){
            if(m_deviceList.at(i)->pDeviceInformation()->id() != i+1)
            {
                m_deviceList.insert(i, new Device(i+1));
                data.welder_id = i + 1;
                break;
            }
        }
    }


    DataBaseManager::getInstance()->insertConfigurationDevice(data);
    m_deviceNum++;
    emit deviceNumChanged();
    emit deviceListChanged();
}

void DeviceManager::removeDevice(int welderID)
{
    if(welderID < 1 || welderID > 4)
        return;

    for(int i = 0; i < m_deviceList.size(); ++i)
    {
        Device* pDevice = m_deviceList.at(i);
        if(pDevice->pDeviceInformation()->id() == welderID)
        {

            m_deviceList.removeOne(pDevice);
            delete pDevice;
            m_deviceNum--;
            DataBaseManager::getInstance()->removeConfigurationDevice(welderID);
            emit deviceNumChanged();
            emit deviceListChanged();
            return;
        }
    }
}

