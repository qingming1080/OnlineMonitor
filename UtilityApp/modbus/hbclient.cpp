#include "hbclient.h"
hbclient::hbclient(QObject *parent)
{
    Q_UNUSED(parent);
    m_isConnected = false;
    setConnectionParameter(QModbusDevice::NetworkPortParameter, 1234);
}

hbclient::~hbclient()
{

}

bool hbclient::Connect(const int& iPort, const QString& strAddress)
{
    this->setConnectionParameter(QModbusDevice::NetworkPortParameter,       iPort);
    this->setConnectionParameter(QModbusDevice::NetworkAddressParameter,    strAddress);
    m_isConnected = this->connectDevice();
    return m_isConnected;
}
