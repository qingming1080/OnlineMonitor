#include "devicemanager.h"
#include "DataBase/databasemanager.h"
#include <qdebug.h>
#include "model/deviceinformation.h"
#include "production.h"
#include "manual.h"
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
    connect(HBModbusClient::getInstance(), &HBModbusClient::notifyDeviceStatusChanged, this, &DeviceManager::slotNotifyDeviceStatusChanged);
    connect(HBModbusClient::getInstance(), &HBModbusClient::notifyWeldResultComing, this, &DeviceManager::slotNotifyWeldResultComing);
}

bool DeviceManager::InitDeviceList()
{
    bool bResult = false;
    QList<int> welderIdlist;
    if(DataBaseManager::getInstance()->getWelderID(welderIdlist) == true)
    {
        Device* _obj = nullptr;
        for(int i = 0; i < m_listDevices.size(); i++)
        {
            _obj = m_listDevices[i];
            _obj->deleteLater();
            _obj = nullptr;
        }
        m_listDevices.clear();
        for(int i = 0; i < welderIdlist.size(); i++)
        {
            _obj = new Device(welderIdlist.at(i));
            m_listDevices.push_back(_obj);
        }
        if(m_listDevices.size() == 0)
            addDevice();
        else
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
    if (index < 0 || index >= m_listDevices.size()) {
        m_iSelectedDeviceIndex = -1;
        emit notifySelectedDeviceIndexChanged();
        return;
    }
    int weldID = -1;
    m_iSelectedDeviceIndex = index;
    weldID = m_listDevices[index]->getWelderID();
    NetworkModel::getInstance()->NotifySelectedDeviceIndexChanged(weldID);
    RS232Model::getInstance()->NotifySelectedDeviceIndexChanged(weldID);
    emit notifySelectedDeviceIndexChanged();
}

void DeviceManager::setDeviceList(const QList<Device *> &list)
{
    Device* _obj = nullptr;
    for(int i = 0; i < m_listDevices.size(); i++)
    {
        _obj = m_listDevices[i];
        _obj->deleteLater();
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

void DeviceManager::slotNotifyDeviceStatusChanged(int welderId, const DEVICE_STATUS &status)
{
    for(int i = 0; i < m_listDevices.size(); i++)
    {
        int id = m_listDevices[i]->getWelderID();
        if(id == welderId)
        {
            m_listDevices[i]->getDeviceObj()->setConnectState(status.IsDeviceStatus || status.IsDeviceDataStatus);
        }
    }
}

void DeviceManager::slotNotifyWeldResultComing(int welderId, const HBModbusClient::MODBUS_WELD_RESULT &data)
{
    qDebug() << "Modbus Weld Result & WeldID: " << welderId;
    qDebug() << " Cycle Count：" << data.CycleCount
             << " Energy:" << data.Energy
             << " Amplitude:" << data.Amplitude
             << " TP:" << data.TriggerPressure
             << " WP:" << data.WeldingPressure
             << " PeakPower:" << data.PeakPower
             << " Preheight:" << data.Preheight
             << " PostHeight:" << data.PostHeight
             << " WeldAlarm: " << data.WeldAlarm
             << " DateTime:" << data.DateTime.toString("yyyy-MM-dd hh:mm:ss");
    for(int i = 0; i < m_listDevices.size(); i++)
    {
        Device* _objDevice = m_listDevices[i];
        Production* _objProduction = _objDevice->getProductionObj();
        Manual* _objManual = _objDevice->getManualObj();
        if(welderId == _objDevice->getWelderID())
        {
            int energy = _objProduction->getEnergySetting();
            float energy_lower = static_cast<float>(0.95 * energy);
            float energy_upper = static_cast<float>(1.05 * energy);
            int amplitude = _objProduction->getAmpSetting();
            int triggerPressure = _objProduction->getTPSetting();
            int weldPressure = _objProduction->getWPSetting();
            if(amplitude != data.Amplitude)
            {
                _objProduction->SetModelStatus(false);
                _objManual->clearData();
            }
            else if(triggerPressure != data.TriggerPressure)
            {
                _objProduction->SetModelStatus(false);
                _objManual->clearData();
            }
            else if(weldPressure != data.WeldingPressure)
            {
                _objProduction->SetModelStatus(false);
                _objManual->clearData();
            }
            else if(energy != data.Energy)
            {
                if((data.WeldAlarm == 0) && ((data.Energy < energy_lower) || (data.Energy > energy_upper)))
                {
                    _objProduction->SetModelStatus(false);
                    _objManual->clearData();
                }
            }
            else
            {
            }

            if(_objProduction->GetModelStatus() == true)
            {


            }
            else
            {
                _objManual->AppendNewRecordComming(welderId, data);
            }
        }

    }
}

bool DeviceManager::addDevice()
{
    if(m_listDevices.size() == 4)
        return false;
    Device* _ptrDev = new Device(-1);
    m_listDevices.append(_ptrDev);
    setDeviceCounter(m_listDevices.size());
    setSelectedDeviceIndex(m_listDevices.size() - 1);
    qDebug() << "add Device" << m_iSelectedDeviceIndex;
    return true;
}

bool DeviceManager::removeDevice()
{
    if(m_iSelectedDeviceIndex < 0)
        return false;
    else if(m_iSelectedDeviceIndex >= m_listDevices.size())
        return false;

    Device* _ptrDev = m_listDevices.at(m_iSelectedDeviceIndex);
    _ptrDev->RemoveDevice();
    m_listDevices.removeAt(m_iSelectedDeviceIndex);
    setDeviceCounter(m_listDevices.size());

    if (m_listDevices.isEmpty())
        setSelectedDeviceIndex(-1);
    else
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
