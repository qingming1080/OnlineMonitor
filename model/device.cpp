#include "device.h"

#include "model/deviceinformation.h"
#include "model/io.h"
#include "model/manual.h"
#include "model/system.h"
#include "model/trend.h"

#include "signalmanager.h"
#include <QDebug>
#include <QElapsedTimer>
#include "log/localrecord.h"

/// TEST 2024_08_18
#include "message.h"
#include "define.h"
#include <QPointF>
/// TEST 2024_08_18

Device::Device(int welderID, QObject *parent)
    : QObject{parent}, m_WelderID(welderID),plotIndex(0)
{
    // QElapsedTimer timer;
    // timer.start();

    m_ptrDevInfo    = new DeviceInformation(m_WelderID);
    m_ptrManual     = new Manual(m_WelderID);
    m_ptrSystem     = new System(m_WelderID);
    m_ptrProduction = new Production(m_WelderID);
    m_ptrTrend      = new Trend(m_WelderID);

    // QString text = QString("%1号设备_Device_初始化共耗时:%2ms").arg(welderID).arg(timer.elapsed());
    //                    emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), text);
}

Device::~Device()
{
    delete m_ptrDevInfo;
    m_ptrDevInfo = nullptr;
    delete m_ptrManual;
    m_ptrManual = nullptr;
    delete m_ptrSystem;
    m_ptrSystem = nullptr;
    delete m_ptrProduction;
    m_ptrProduction = nullptr;
    delete m_ptrTrend;
    m_ptrTrend = nullptr;
}

Trend *Device::pTrend() const
{
    return m_ptrTrend;
}

int Device::getPlotIndex() const {
    return plotIndex;
}

void Device::incrementPlotIndex() {
    plotIndex++;
}

DeviceInformation* Device::getDevInfoObject() const
{
    return m_ptrDevInfo;
}

void Device::setDevInfoObject(const DeviceInformation *object)
{
    if (m_ptrDevInfo != object) {
        m_ptrDevInfo = const_cast<DeviceInformation*>(object);
        emit notifyDevInfoObjectChanged();
    }
}

Manual *Device::getManualObj() const
{
    return m_ptrManual;
}

void Device::setManualObj(const Manual *object)
{
    if (m_ptrManual != object) {
        m_ptrManual = const_cast<Manual*>(object);
        emit notifyManualObjChanged();
    }
}

Production *Device::getProductionObj() const
{
    return m_ptrProduction;
}

void Device::setProductionObj(const Production *object)
{
    if (m_ptrProduction != object) {
        m_ptrProduction = const_cast<Production*>(object);
        emit notifyProductionObjChanged();
    }
}

System *Device::getSystemObj() const
{
    return m_ptrSystem;
}

void Device::setSystemObj(const System *object)
{
    if (m_ptrSystem != object) {
        m_ptrSystem = const_cast<System*>(object);
        emit notifySystemObjChanged();
    }
}

bool Device::SaveDevice()
{
    return true;
}

bool Device::UpdateDevice()
{
    return true;
}
