#include "devicemanager.h"
#include "DataBase/databasemanager.h"
#include <qdebug.h>
#include "model/deviceinformation.h"
#include "production.h"
#include "manual.h"
#include "networkmodel.h"
#include "rs232model.h"
#include "tools/utilityfunction.h"
#include "message.h"
#include "../define.h"

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
    connect(HBModbusClient::getInstance(), &HBModbusClient::notifyDeviceStatusChanged,  this, &DeviceManager::slotNotifyDeviceStatusChanged);
    connect(HBModbusClient::getInstance(), &HBModbusClient::notifyWeldResultComing,     this, &DeviceManager::slotNotifyWeldResultComing);
    connect(HBModbusClient::getInstance(), &HBModbusClient::notifyPresetSettingChanged, this, &DeviceManager::slotNotifyPresetSettingChanged);
    connect(HBModbusClient::getInstance(), &HBModbusClient::connectionStateChanged, this, &DeviceManager::slotNotifyModbusStatusChanged);
    connect(HBModbusClient::getInstance(), &HBModbusClient::notifyResetButtonChanged, this,&DeviceManager::slotNotifyResetButtonChanged);
    connect(HBModbusClient::getInstance(), &HBModbusClient::notifyDeviceIOStatusChanged, this,&DeviceManager::slotNotifyDeviceIOStatusChanged);
#if DEBUG_MULTIDEVICE
    startTimer(3000);
#endif
}

bool DeviceManager::InitDeviceList()
{
    bool bResult = false;
    QList<int> welderIdlist;
    if(DataBaseManager::getInstance()->getWelderID(welderIdlist) == true)
    {
        Device* _obj = nullptr;
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

bool DeviceManager::IsManualPresetChanged()
{
    return true;
}

void DeviceManager::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)
    static int iCount = 0;
    HBModbusClient::MODBUS_WELD_RESULT tmpWeldResult;
    tmpWeldResult.WeldAlarm = 0;

    tmpWeldResult.DateTime = QDateTime::currentDateTime();
    if(iCount % 2 == 0)
    {
        tmpWeldResult.CycleCount = iCount;
        tmpWeldResult.Energy = 2000;
        tmpWeldResult.Amplitude = 22;
        tmpWeldResult.TriggerPressure = 200;
        tmpWeldResult.WeldingPressure = 200;
        tmpWeldResult.WeldTime = 200;
        tmpWeldResult.PeakPower = 2000;
        tmpWeldResult.Preheight = 600;
        tmpWeldResult.PostHeight = 400;
        slotNotifyWeldResultComing(1, tmpWeldResult);
    }
    else
    {
        tmpWeldResult.CycleCount = iCount;
        tmpWeldResult.Energy = 1000;
        tmpWeldResult.Amplitude = 11;
        tmpWeldResult.TriggerPressure = 300;
        tmpWeldResult.WeldingPressure = 300;
        tmpWeldResult.WeldTime = 100;
        tmpWeldResult.PeakPower = 1000;
        tmpWeldResult.Preheight = 500;
        tmpWeldResult.PostHeight = 300;
        slotNotifyWeldResultComing(2, tmpWeldResult);
    }
    iCount++;

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

void DeviceManager::slotNotifyDeviceStatusChanged(int welderId, HBModbusClient::DEVICE_STATUS status)
{
    for(int i = 0; i < m_listDevices.size(); i++)
    {
        if(m_listDevices[i]->getWelderID() == welderId)
        {
            if(m_listDevices[i]->getDeviceObj()->getWelderType() == DeviceInfoEnum::RS232)
            {
                status.IsDeviceStatus = true;
                status.IsDeviceDataStatus = true;
            }
            m_listDevices[i]->NotifyDeviceStatusChanged(status);
        }
    }
    bool bResult = true;
    for(int i = 0; i < m_listDevices.size(); i++)
    {
        if(m_listDevices[i]->getDeviceObj()->getConnectState() == false)
        {
            bResult = false;
            break;
        }
    }
    if(bResult)
    {
        if(HBModbusClient::getInstance()->getReadyLedStatus() == false)
        {
            HBModbusClient::getInstance()->setReadyLedStatus(true);
        }
    }
    else
    {
        if(HBModbusClient::getInstance()->getReadyLedStatus() == true)
        {
            HBModbusClient::getInstance()->setReadyLedStatus(false);
        }
    }
}

void DeviceManager::slotNotifyWeldResultComing(int welderId, const HBModbusClient::MODBUS_WELD_RESULT &data)
{
    // qDebug() << "Modbus Weld Result & WeldID: " << welderId;
    // qDebug() << " Cycle Count：" << data.CycleCount
    //          << " Energy:" << data.Energy
    //          << " Amplitude:" << data.Amplitude
    //          << " TP:" << data.TriggerPressure
    //          << " WP:" << data.WeldingPressure
    //          << " PeakPower:" << data.PeakPower
    //          << " Preheight:" << data.Preheight
    //          << " PostHeight:" << data.PostHeight
    //          << " WeldAlarm: " << data.WeldAlarm
    //          << " DateTime:" << data.DateTime.toString("yyyy-MM-dd hh:mm:ss");
    for(int i = 0; i < m_listDevices.size(); i++)
    {
        if(welderId == m_listDevices[i]->getWelderID())
        {
            m_listDevices[i]->NotifyWeldResultComing(data);
        }
    }
}

void DeviceManager::slotNotifyPresetSettingChanged(int welderId, const HBModbusClient::WELD_PRESET &data)
{
    for(int i = 0; i < m_listDevices.size(); i++)
    {
        if(welderId == m_listDevices[i]->getWelderID())
        {
            m_listDevices[i]->NotifyPresetSettingChanged(data);
        }
    }
}

void DeviceManager::slotNotifyModbusStatusChanged(const bool connected)
{
    if(connected == true)
    {
        for(int i = 0; i < m_listDevices.size(); i++)
        {
            int targetWelderId = m_listDevices[i]->getWelderID();
            m_listDevices[i]->NotifyModbusStatusChanged(targetWelderId);
        }
    }
    emit notifyConnectionStateChanged(connected);
}

void DeviceManager::slotNotifyResetButtonChanged(const bool ResetButtonStatus)
{
    if(ResetButtonStatus == true)
    {
        HBModbusClient::getInstance()->setAlarmLedStatus(false);
        Message::getInstance()->clearMessages();
    }
}

void DeviceManager::slotNotifyDeviceIOStatusChanged(int welderId, const HBModbusClient::IO_STATUS &status)
{
    for(auto device : m_listDevices)
    {
        if(device->getWelderID() == welderId)
        {
            device->setIORejectStatus(status.IsRejectStatus);
            device->setIOSuspectStatus(status.IsSuspectStatus);
            device->setIOResetStatus(status.IsResetStatus);
            break;
        }
    }

    if(status.IsResetStatus)
    {
        // resetDeviceIO(welderId);
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
    if (!m_listDevices[m_iSelectedDeviceIndex]->SaveDevice())
        return false;
    return true;
}
