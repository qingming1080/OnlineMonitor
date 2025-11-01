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
    if(DataBaseManager::getInstance()->getConfigurationDevice(welderID, m_DBConfigure) == true)
    {
        setWelderName(m_DBConfigure.WelderName);
        setWelderType(m_DBConfigure.WelderType);
        setProductionMaxBacth(QString::number(m_DBConfigure.ProductionBatch));
        setMaxModelSamples(QString::number(m_DBConfigure.MaxModelSamples));
        setYieldRateLowerLimit(QString::number(m_DBConfigure.YieldRateLowerLimit));
        setHeightEncoderOption(m_DBConfigure.HeightEncoderOption);
        setSuspiciousOption(m_DBConfigure.SuspiciousOption);
        setConnectType(m_DBConfigure.ConnectType);
		setSingleFactor(QString::number(m_DBConfigure.SingleFactSetting));
        setGeneralFactor(QString::number(m_DBConfigure.GeneralFactSetting));
        setAutoLearningCount(QString::number(m_DBConfigure.AutoLearnCount));
        setForceThreshold(QString::number(m_DBConfigure.ForceThreshold));
        setResidualThreshold(QString::number(m_DBConfigure.ResidualThreshold));
    }
    else
    {
        setWelderName("NAN");
        setWelderType(DeviceInfoEnum::L20_VG);
        setProductionMaxBacth("200000");
        setMaxModelSamples("20");
        setYieldRateLowerLimit("90");
        setHeightEncoderOption(true);
        setSuspiciousOption(true);
        setConnectType(DeviceInfoEnum::TCP_IP);
        setSingleFactor("20");
        setGeneralFactor("80");
        setAutoLearningCount("5");
        setForceThreshold("1300");
        setResidualThreshold("90");
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
    return static_cast<int>(m_ModbusConfigure.ConnectState);
}

void DeviceInformation::setConnectState(const int &state)
{
    if (m_ModbusConfigure.ConnectState != state)
    {
        m_ModbusConfigure.ConnectState = static_cast<DeviceInfoEnum::CONNECT_STATE>(state);
        emit notifyConnectStateChanged();
    }
}

QString DeviceInformation::getSingleFactor() const
{
    return QString::number(m_DBConfigure.SingleFactSetting);
}

int DeviceInformation::GetSingleFactor() const
{
    return m_DBConfigure.SingleFactSetting;
}

void DeviceInformation::setSingleFactor(const QString &factor)
{
    bool isOk;
    int iFactor = factor.toInt(&isOk);
    if (!isOk || m_DBConfigure.SingleFactSetting == iFactor)
        return;
    m_DBConfigure.SingleFactSetting = iFactor;
    emit notifySingleFactorChanged();
}

QString DeviceInformation::getGeneralFactor() const
{
    return QString::number(m_DBConfigure.GeneralFactSetting);
}

int DeviceInformation::GetGeneralFactor() const
{
    return m_DBConfigure.GeneralFactSetting;
}

void DeviceInformation::setGeneralFactor(const QString &factor)
{
    bool isOk = false;
    int iFactor = factor.toInt(&isOk);
    if (!isOk || m_DBConfigure.GeneralFactSetting == iFactor)
        return;
    m_DBConfigure.GeneralFactSetting = iFactor;
    emit notifyGeneralFactorChanged();
}

QString DeviceInformation::getForceThreshold() const
{
    return QString::number(m_DBConfigure.ForceThreshold);
}

int DeviceInformation::GetForceThreshold() const
{
    return m_DBConfigure.ForceThreshold;
}

void DeviceInformation::setForceThreshold(const QString &threshold)
{
    bool isOk = false;
    int iThreshold = threshold.toInt(&isOk);
    if (!isOk || m_DBConfigure.ForceThreshold == iThreshold)
        return;
    m_DBConfigure.ForceThreshold = iThreshold;
    emit notifyForceThresholdChanged();
}

QString DeviceInformation::getResidualThreshold() const
{
    return QString::number(m_DBConfigure.ResidualThreshold);
}

int DeviceInformation::GetResidualThreshold() const
{
    return m_DBConfigure.ResidualThreshold;
}

void DeviceInformation::setResidualThreshold(const QString &threshold)
{
    bool isOk = false;
    int iThreshold = threshold.toInt(&isOk);
    if (!isOk || m_DBConfigure.ResidualThreshold == iThreshold)
        return;
    m_DBConfigure.ResidualThreshold = iThreshold;
    emit notifyResidualThresholdChanged();
}

QString DeviceInformation::getAutoLearningCount() const
{
    return QString::number(m_DBConfigure.AutoLearnCount);
}

int DeviceInformation::GetAutoLearningCount() const
{
    return m_DBConfigure.AutoLearnCount;
}

void DeviceInformation::setAutoLearningCount(const QString &limit)
{
    bool isOk = false;
    int iLimit = limit.toInt(&isOk);
    if (!isOk || m_DBConfigure.AutoLearnCount == iLimit)
        return;
    m_DBConfigure.AutoLearnCount = iLimit;
    emit notifyAutoLearningCountChanged();
}

int DeviceInformation::getPortNumber() const
{
    return m_ModbusConfigure.NetworkProperties.PortNumber;
}

void DeviceInformation::setPortNumber(const int &port)
{
    if (m_ModbusConfigure.NetworkProperties.PortNumber != port)
    {
        m_ModbusConfigure.NetworkProperties.PortNumber = port;
        emit notifyPortNumberChanged();
    }
}

QString DeviceInformation::getLocalIP() const
{
    return m_ModbusConfigure.NetworkProperties.LocalIP;
}

void DeviceInformation::setLocalIP(const QString &ip)
{
    if (m_ModbusConfigure.NetworkProperties.LocalIP != ip)
    {
        m_ModbusConfigure.NetworkProperties.LocalIP = ip;
        emit notifyLocalIPChanged();
    }
}

QString DeviceInformation::getRemoteIP() const
{
    return m_ModbusConfigure.NetworkProperties.RemoteIP;
}

void DeviceInformation::setRemoteIP(const QString &ip)
{
    if (m_ModbusConfigure.NetworkProperties.RemoteIP != ip)
    {
        m_ModbusConfigure.NetworkProperties.RemoteIP = ip;
        emit notifyRemoteIPChanged();
    }
}
int DeviceInformation::getComNumber() const
{
    return m_ModbusConfigure.SerialProperties.ComNumber;
}

void DeviceInformation::setComNumber(const int &com)
{
    if (m_ModbusConfigure.SerialProperties.ComNumber != com)
    {
        m_ModbusConfigure.SerialProperties.ComNumber = com;
        emit notifyComNumberChanged();
    }
}

int DeviceInformation::getBaudRate() const
{
    return m_ModbusConfigure.SerialProperties.BaudRate;
}

void DeviceInformation::setBaudRate(const int &baudrate)
{
    if (m_ModbusConfigure.SerialProperties.BaudRate != baudrate)
    {
        m_ModbusConfigure.SerialProperties.BaudRate = static_cast<QSerialPort::BaudRate>(baudrate);
        emit notifyBaudRateChanged();
    }
}

int DeviceInformation::getDataBits() const
{
    return m_ModbusConfigure.SerialProperties.DataBits;
}

void DeviceInformation::setDataBits(const int &databits)
{
    if (m_ModbusConfigure.SerialProperties.DataBits != databits)
    {
        m_ModbusConfigure.SerialProperties.DataBits = static_cast<QSerialPort::DataBits>(databits);
        emit notifyDataBitsChanged();
    }
}

int DeviceInformation::getParityBits() const
{
    return m_ModbusConfigure.SerialProperties.ParityBits;
}

void DeviceInformation::setParityBits(const int &paritybits)
{
    if (m_ModbusConfigure.SerialProperties.ParityBits != paritybits)
    {
        m_ModbusConfigure.SerialProperties.ParityBits = static_cast<QSerialPort::Parity>(paritybits);
        emit notifyParityBitsChanged();
    }
}

int DeviceInformation::getStopBits() const
{
    return m_ModbusConfigure.SerialProperties.StopBits;
}

void DeviceInformation::setStopBits(const int &stopbits)
{
    if (m_ModbusConfigure.SerialProperties.StopBits != stopbits)
    {
        m_ModbusConfigure.SerialProperties.StopBits = static_cast<QSerialPort::StopBits>(stopbits);
        emit notifyStopBitsChanged();
    }
}

