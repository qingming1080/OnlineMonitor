#include "deviceinformation.h"
#include <QVariant>

#include "signalmanager.h"
#include <QDebug>
#include <QElapsedTimer>
#include "log/localrecord.h"
#include "tools/utilityfunction.h"

DeviceInformation::DeviceInformation(int welderID, QObject *parent)
    : QObject{parent}, m_WelderID(welderID)
{
    // QElapsedTimer timer;
    // timer.start();
    if(m_WelderID == -1)
    {

    }
    else if(DataBaseManager::getInstance()->getConfigurationData(welderID, m_DBConfigure) == true)
    {
        setWelderName(m_DBConfigure.WelderName);
        setWelderType(m_DBConfigure.WelderType);
        setProductionMaxBacth(QString::number(m_DBConfigure.ProductionBatch));
        setMaxModelSamples(QString::number(m_DBConfigure.MaxModelSamples));
        setYieldRateLowerLimit(QString::number(m_DBConfigure.YieldRateLowerLimit));
        setHeightEncoderOption(m_DBConfigure.HeightEncoderOption);
        setSuspiciousOption(m_DBConfigure.SuspiciousOption);
        setConnectType(m_DBConfigure.ConnectType);
    }
    else
    {

    }

    // QString text = QString("%1号设备_DeviceInformation_初始化耗时:%2ms").arg(welderID).arg(timer.elapsed());
    // emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), text);
}


QString DeviceInformation::getWelderName() const
{
    return m_DBConfigure.WelderName;
}

void DeviceInformation::setWelderName(const QString &name)
{
    if (m_DBConfigure.WelderName != name)
    {
        m_DBConfigure.WelderName = name;
        emit notifyWelderNameChanged();
    }
}

int DeviceInformation::getWelderType() const
{
    return m_DBConfigure.WelderType;
}

void DeviceInformation::setWelderType(const int &type)
{
    if (m_DBConfigure.WelderType != type)
    {
        m_DBConfigure.WelderType = type;
        emit notifyWelderTypeChanged();
    }
}

QString DeviceInformation::getProductionMaxBacth() const
{
    return QString::number(m_DBConfigure.ProductionBatch);
}

void DeviceInformation::setProductionMaxBacth(const QString &maxBacth)
{
    bool ok;
    int value = maxBacth.toInt(&ok);
    if (ok && m_DBConfigure.ProductionBatch != value)
    {
        m_DBConfigure.ProductionBatch = value;
        emit notifyProductionMaxBacthChanged();
    }
}

QString DeviceInformation::getMaxModelSamples() const
{
    return QString::number(m_DBConfigure.MaxModelSamples);
}

void DeviceInformation::setMaxModelSamples(const QString &samples)
{
    bool ok;
    int value = samples.toInt(&ok);
    if (ok && m_DBConfigure.MaxModelSamples != value)
    {
        m_DBConfigure.MaxModelSamples = value;
        emit notifyMaxModelSamplesChanged();
    }
}

QString DeviceInformation::getYieldRateLowerLimit() const
{
    return QString::number(m_DBConfigure.YieldRateLowerLimit);
}

void DeviceInformation::setYieldRateLowerLimit(const QString &yieldRate)
{
    bool ok;
    int value = yieldRate.toInt(&ok);
    if (ok && m_DBConfigure.YieldRateLowerLimit != value)
    {
        m_DBConfigure.YieldRateLowerLimit = value;
        emit notifyYieldRateLowerLimitChanged();
    }
}

bool DeviceInformation::getHeightEncoderOption() const
{
    return m_DBConfigure.HeightEncoderOption;
}

void DeviceInformation::setHeightEncoderOption(const bool &option)
{
    if (m_DBConfigure.HeightEncoderOption != option)
    {
        m_DBConfigure.HeightEncoderOption = option;
        emit notifyHeightEncoderOptionChanged();
    }
}

bool DeviceInformation::getSuspiciousOption() const
{
    return m_DBConfigure.SuspiciousOption;
}

void DeviceInformation::setSuspiciousOption(const bool &option)
{
    if (m_DBConfigure.SuspiciousOption != option)
    {
        m_DBConfigure.SuspiciousOption = option;
        emit notifySuspiciousOptionChanged();
    }
}

int DeviceInformation::getConnectType() const
{
    return m_DBConfigure.ConnectType;
}

void DeviceInformation::setConnectType(const int &type)
{
    if (m_DBConfigure.ConnectType != type)
    {
        m_DBConfigure.ConnectType = static_cast<DeviceInfoEnum::CONNECT_TYPE>(type);
        emit notifyConnectTypeChanged();
    }
}

int DeviceInformation::getConnectTypeID() const
{
    return m_DBConfigure.ConnectTypeId;
}

void DeviceInformation::setConnectTypeID(const int &typeID)
{
    if (m_DBConfigure.ConnectTypeId != typeID)
    {
        m_DBConfigure.ConnectTypeId = typeID;
    }
}

int DeviceInformation::getConnectState() const
{
    return static_cast<int>(m_iConnectState);
}

void DeviceInformation::setConnectState(const int &state)
{
    if (m_iConnectState != state)
    {
        m_iConnectState = static_cast<DeviceInfoEnum::CONNECT_STATE>(state);
        emit notifyConnectStateChanged();
    }
}

// QString DeviceInformation::mesIP() const
// {
//     return m_mesIP;
// }

// void DeviceInformation::setMesIP(const QString &newMesIP)
// {
//     if (m_mesIP == newMesIP)
//         return;
//     m_mesIP = newMesIP;
//     emit mesIPChanged();
// }

// QString DeviceInformation::deviceIP() const
// {
//     return m_deviceIP;
// }

// void DeviceInformation::setDeviceIP(const QString &newDeviceIP)
// {
//     if (m_deviceIP == newDeviceIP)
//         return;
//     m_deviceIP = newDeviceIP;
//     emit deviceIPChanged();
// }

// int DeviceInformation::mesPort() const
// {
//     return m_mesPort;
// }

// void DeviceInformation::setMesPort(int newMesPort)
// {
//     if (m_mesPort == newMesPort)
//         return;
//     m_mesPort = newMesPort;
//     emit mesPortChanged();
// }


