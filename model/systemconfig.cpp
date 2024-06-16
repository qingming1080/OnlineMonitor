#include "systemconfig.h"

SystemConfig::SystemConfig(QObject *parent)
    : QObject{parent}
{

}

int SystemConfig::maxBatch() const
{
    return m_maxBatch;
}

void SystemConfig::setMaxBatch(int newMaxBatch)
{
    if (m_maxBatch == newMaxBatch)
        return;
    m_maxBatch = newMaxBatch;
    emit maxBatchChanged();
}

int SystemConfig::sampleNum() const
{
    return m_sampleNum;
}

void SystemConfig::setSampleNum(int newSampleNum)
{
    if (m_sampleNum == newSampleNum)
        return;
    m_sampleNum = newSampleNum;
    emit sampleNumChanged();
}

int SystemConfig::minYield() const
{
    return m_minYield;
}

void SystemConfig::setMinYield(int newMinYield)
{
    if (m_minYield == newMinYield)
        return;
    m_minYield = newMinYield;
    emit minYieldChanged();
}

bool SystemConfig::heightMode() const
{
    return m_heightMode;
}

void SystemConfig::setHeightMode(bool newHeightMode)
{
    if (m_heightMode == newHeightMode)
        return;
    m_heightMode = newHeightMode;
    emit heightModeChanged();
}

bool SystemConfig::undetermined() const
{
    return m_undetermined;
}

void SystemConfig::setUndetermined(bool newUndetermined)
{
    if (m_undetermined == newUndetermined)
        return;
    m_undetermined = newUndetermined;
    emit undeterminedChanged();
}

QString SystemConfig::port() const
{
    return m_port;
}

void SystemConfig::setPort(const QString &newPort)
{
    if (m_port == newPort)
        return;
    m_port = newPort;
    emit portChanged();
}

QSerialPort::BaudRate SystemConfig::baudRate() const
{
    return m_baudRate;
}

void SystemConfig::setBaudRate(const QSerialPort::BaudRate &newBaudRate)
{
    if (m_baudRate == newBaudRate)
        return;
    m_baudRate = newBaudRate;
    emit baudRateChanged();
}

QSerialPort::DataBits SystemConfig::dataBits() const
{
    return m_dataBits;
}

void SystemConfig::setDataBits(const QSerialPort::DataBits &newDataBits)
{
    if (m_dataBits == newDataBits)
        return;
    m_dataBits = newDataBits;
    emit dataBitsChanged();
}

QSerialPort::Parity SystemConfig::parity() const
{
    return m_parity;
}

void SystemConfig::setParity(const QSerialPort::Parity &newParity)
{
    if (m_parity == newParity)
        return;
    m_parity = newParity;
    emit parityChanged();
}

QSerialPort::StopBits SystemConfig::stopBits() const
{
    return m_stopBits;
}

void SystemConfig::setStopBits(const QSerialPort::StopBits &newStopBits)
{
    if (m_stopBits == newStopBits)
        return;
    m_stopBits = newStopBits;
    emit stopBitsChanged();
}
