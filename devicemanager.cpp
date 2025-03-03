#include "devicemanager.h"
#include "DataBase/databasemanager.h"
#include "model/deviceinformation.h"
#include "define.h"
#include <qdebug.h>
#include "model/deviceinformation.h"

#include "signalmanager.h"
#include <QElapsedTimer>
#include "log/localrecord.h"
#include "model/networkmodel.h"
#include "model/rs232model.h"
#include "model/devicenames.h"

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

    emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), QString("DeviceManager初始化耗时:%1ms").arg(timer.elapsed()));
}

Device *DeviceManager::getDeviceByNetworkID(int networkID)
{
    for(int i = 0; i < m_deviceList.size(); ++i)
    {
        if(m_deviceList.at(i)->pDeviceInformation()->connectType() == QmlEnum::CONNECTTYPE_Network
            && m_deviceList.at(i)->pDeviceInformation()->connectID() == networkID)
            return m_deviceList.at(i);
    }

    return nullptr;
}

Device *DeviceManager::getDeviceByRs232ID(int rs232ID)
{
    for(int i = 0; i < m_deviceList.size(); ++i)
    {
        if(m_deviceList.at(i)->pDeviceInformation()->connectType() == QmlEnum::CONNECTTYPE_RS232
            && m_deviceList.at(i)->pDeviceInformation()->connectID() == rs232ID)
            return m_deviceList.at(i);
    }

    return nullptr;
}

void DeviceManager::init()
{
    QList<int> list = DataBaseManager::getInstance()->getDeviceNums();
    QList<QString> names;
    m_deviceNum = list.size();



    for(int i = 0; i < list.size(); ++i)
    {
        m_deviceList.push_back(new Device(list.at(i)));
        names.push_back(m_deviceList.last()->pDeviceInformation()->name());
    }

    DeviceNames::getInstance()->setNames(names);
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


void DeviceManager::addDevice(const int &maxBacth, const int &sample, const int &lowerLimit, const int &port, const QString &targetIp, const QString &localIp, const int &heightOption, const QString &name, const QString &model, const int &connectType, const int &id)
{
    if(m_deviceList.size() == 4)
        return;

    _Configuration_Data data;

     m_deviceNum++;
    emit deviceNumChanged();

    // bool added = false;

    for(int i = 0; i < 4; ++i)
    {
        if(i == m_deviceList.size())
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
            m_deviceList.insert(i, d);
            break;
        }
        if(m_deviceList.at(i) != nullptr){
            if(m_deviceList.at(i)->pDeviceInformation()->id() != i+1)
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
                m_deviceList.insert(i, d);

                break;
            }
        }
    }



    emit deviceListChanged();

    QList<QString> names;
    for(int i = 0; i < m_deviceList.size(); ++i)
    {
        names.push_back(m_deviceList.at(i)->pDeviceInformation()->name());
    }

    DeviceNames::getInstance()->setNames(names);
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

    QList<QString> names;
    for(int i = 0; i < m_deviceList.size(); ++i)
    {
        names.push_back(m_deviceList.at(i)->pDeviceInformation()->name());
    }

    DeviceNames::getInstance()->setNames(names);
}


