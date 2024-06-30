#include "deviceinformation.h"

DeviceInformation::DeviceInformation(QObject *parent)
    : QObject{parent}
{

}

QString DeviceInformation::name() const
{
    return m_name;
}

void DeviceInformation::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

QString DeviceInformation::model() const
{
    return m_model;
}

void DeviceInformation::setModel(const QString &newModel)
{
    if (m_model == newModel)
        return;
    m_model = newModel;
    emit modelChanged();
}

QmlEnum::_CONNECTTYPE DeviceInformation::connectType() const
{
    return m_connectType;
}

void DeviceInformation::setConnectType(const QmlEnum::_CONNECTTYPE &newconnectType)
{
    if (m_connectType == newconnectType)
        return;
    m_connectType = newconnectType;
    emit connectTypeChanged();
}

int DeviceInformation::id() const
{
    return m_id;
}

void DeviceInformation::setId(int newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

int DeviceInformation::maxBacth() const
{
    return m_maxBacth;
}

void DeviceInformation::setMaxBacth(int newMaxBacth)
{
    if (m_maxBacth == newMaxBacth)
        return;
    m_maxBacth = newMaxBacth;
    emit maxBacthChanged();
}

int DeviceInformation::sample() const
{
    return m_sample;
}

void DeviceInformation::setSample(int newSample)
{
    if (m_sample == newSample)
        return;
    m_sample = newSample;
    emit sampleChanged();
}

int DeviceInformation::heightOption() const
{
    return m_heightOption;
}

void DeviceInformation::setHeightOption(int newHeightOption)
{
    if (m_heightOption == newHeightOption)
        return;
    m_heightOption = newHeightOption;
    emit heightOptionChanged();
}

int DeviceInformation::lowerLimit() const
{
    return m_lowerLimit;
}

void DeviceInformation::setLowerLimit(int newLowerLimit)
{
    if (m_lowerLimit == newLowerLimit)
        return;
    m_lowerLimit = newLowerLimit;
    emit lowerLimitChanged();
}

int DeviceInformation::connectID() const
{
    return m_connectID;
}

void DeviceInformation::setConnectID(int newConnectID)
{
    if (m_connectID == newConnectID)
        return;
    m_connectID = newConnectID;
    emit connectIDChanged();
}
