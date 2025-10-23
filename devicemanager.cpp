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
#include "tools/devicemodbusmapper.h"

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
    QElapsedTimer timer;
    timer.start();

    init();

    emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), QString("DeviceManager初始化耗时:%1ms").arg(timer.elapsed()));
}

Device *DeviceManager::getDeviceByNetworkID(int networkID)
{
    for(int i = 0; i < m_listDevices.size(); ++i)
    {
        if(m_listDevices.at(i)->getDevInfoObject()->getConnectType() == DeviceInfoEnum::TCP_IP
            && m_listDevices.at(i)->getDevInfoObject()->connectID() == networkID)
            return m_listDevices.at(i);
    }

    return nullptr;
}

Device *DeviceManager::getDeviceByRs232ID(int rs232ID)
{
    for(int i = 0; i < m_listDevices.size(); ++i)
    {
        if(m_listDevices.at(i)->getDevInfoObject()->getConnectType() == DeviceInfoEnum::RS232
            && m_listDevices.at(i)->getDevInfoObject()->connectID() == rs232ID)
            return m_listDevices.at(i);
    }

    return nullptr;
}

void DeviceManager::init()
{
    QList<int> list = DataBaseManager::getInstance()->getDeviceNums();
    QList<QString> names;
    setDeviceCounter(list.size());
    for(int i = 0; i < list.size(); ++i)
    {
        m_listDevices.push_back(new Device(list.at(i)));
        names.push_back(m_listDevices.last()->getDevInfoObject()->name());
    }
    DeviceNames::getInstance()->setNames(names);
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
    if(m_iSelectedDeviceIndex != index)
    {
        m_iSelectedDeviceIndex = index;
        emit notifySelectedDeviceIndexChanged();
    }
}
void DeviceManager::setDeviceList(const QList<Device *> &list)
{
    m_listDevices = list;
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
    for(int i = 0; i < m_listDevices.size(); ++i)
    {
        if(m_listDevices.at(i)->getDevInfoObject()->id() == welderID)
            return m_listDevices.at(i)->getDevInfoObject()->name();
    }

    return "";
}





void DeviceManager::addDevice(const int &maxBacth, const int &sample, const int &lowerLimit, const int &port, const QString &targetIp, const QString &localIp, const int &heightOption, const QString &name, const QString &model, const int &connectType, const int &id)
{
    if(m_listDevices.size() == 4)
        return;

    _Configuration_Data data;

    for(int i = 0; i < 4; ++i)
    {
        if(i == m_listDevices.size())
        {
            data.welder_id = i + 1;
            data.welder_name = name;
            data.welder_type = model;
            data.production_bacth = maxBacth;
            data.model_sample = sample;
            data.lower_limit = lowerLimit;
            data.height_option = heightOption;
            data.connect_type = connectType;
            data.connect_id = id;
            data.mes_port = port;
            data.mes_ip = targetIp;
            data.device_ip = localIp;

            DataBaseManager::getInstance()->insertConfigurationDevice(data);

            Device *d = new Device(i+1);
            m_listDevices.insert(i, d);
            break;
        }
        if(m_listDevices.at(i) != nullptr){
            if(m_listDevices.at(i)->getDevInfoObject()->id() != i+1)
            {
                data.welder_id = i + 1;
                data.welder_name = name;
                data.welder_type = model;
                data.production_bacth = maxBacth;
                data.model_sample = sample;
                data.lower_limit = lowerLimit;
                data.height_option = heightOption;
                data.connect_type = connectType;
                data.connect_id = id;
                data.mes_port = port;
                data.mes_ip = targetIp;
                data.device_ip = localIp;

                DataBaseManager::getInstance()->insertConfigurationDevice(data);

                Device *d = new Device(i+1);
                m_listDevices.insert(i, d);

                break;
            }
        }
    }

    setDeviceList(m_listDevices);
    // syncDevicesToModbus();

    QList<QString> names;
    for(int i = 0; i < m_listDevices.size(); ++i)
    {
        names.push_back(m_listDevices.at(i)->getDevInfoObject()->name());
    }

    DeviceNames::getInstance()->setNames(names);
}

void DeviceManager::removeDevice(int welderID)
{
    if(welderID < 1 || welderID > 4)
        return;

    for(int i = 0; i < m_listDevices.size(); ++i)
    {
        Device* pDevice = m_listDevices.at(i);
        if(pDevice->getDevInfoObject()->id() == welderID)
        {
            //TODO  delete device   DEV_AVAILABLE = 0
            // DeviceModbusMapper::DeviceRegisterData emptyData;
            // emptyData.deviceID = welderID;
            // emptyData.DEV_AVAILABLE = 0;
            // HBModbusClient::getInstance()->writeDeviceConfig(welderID, emptyData);

            m_listDevices.removeOne(pDevice);
            delete pDevice;
        }
    }
    setDeviceCounter(m_listDevices.size());
    DataBaseManager::getInstance()->removeConfigurationDevice(welderID);
    setDeviceList(m_listDevices);
    return;

    QList<QString> names;
    for(int i = 0; i < m_listDevices.size(); ++i)
    {
        names.push_back(m_listDevices.at(i)->getDevInfoObject()->name());
    }

    DeviceNames::getInstance()->setNames(names);
}


// void DeviceManager::syncDevicesToModbus()
// {
//     for (Device* device : m_listDevices)
//     {
//         auto deviceData = DeviceModbusMapper::generateRegisterData(device);
//         HBModbusClient::getInstance()->writeDeviceConfig(deviceData.deviceID, deviceData);
//     }

// }
