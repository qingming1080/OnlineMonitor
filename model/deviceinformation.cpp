#include "deviceinformation.h"
#include "DataBase/databasemanager.h"
#include <QVariant>

DeviceInformation::DeviceInformation(int welderID, QObject *parent)
    : QObject{parent}, m_id(welderID)
{
    _Configuration_Data data = DataBaseManager::getInstance()->getConfigurationData(welderID);

    m_name  = data.welder_name;
    m_model = data.welder_type;
    m_maxBacth = data.production_bacth;
    m_sample    = data.model_sample;
    m_lowerLimit = data.lower_limit;
    m_heightOption = data.height_option;
    m_connectType = static_cast<QmlEnum::_CONNECTTYPE>(data.connect_type);
    m_connectID = data.connect_id;
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

    DataBaseManager::getInstance()->setConfigurationData(m_id, _CONFIGURATION_welder_name, m_name);
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

    DataBaseManager::getInstance()->setConfigurationData(m_id, _CONFIGURATION_welder_type, m_model);
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

    DataBaseManager::getInstance()->setConfigurationData(m_id, _CONFIGURATION_connect_type, m_connectType);
}

int DeviceInformation::id() const
{
    return m_id;
}

//void DeviceInformation::setId(int newId)
//{
//    if (m_id == newId)
//        return;
//    m_id = newId;
//    emit idChanged();
//}

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

    DataBaseManager::getInstance()->setConfigurationData(m_id, _CONFIGURATION_production_bacth, m_maxBacth);
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

    DataBaseManager::getInstance()->setConfigurationData(m_id, _CONFIGURATION_model_sample, m_sample);
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

    DataBaseManager::getInstance()->setConfigurationData(m_id, _CONFIGURATION_height_option, m_heightOption);
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

    DataBaseManager::getInstance()->setConfigurationData(m_id, _CONFIGURATION_lower_limit, m_lowerLimit);
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

    DataBaseManager::getInstance()->setConfigurationData(m_id, _CONFIGURATION_connect_id, m_connectID);
}

QString DeviceInformation::state() const
{
    return m_state;
}

void DeviceInformation::setState(const QString &newState)
{
    if (m_state == newState)
        return;
    m_state = newState;
    emit stateChanged();
}
