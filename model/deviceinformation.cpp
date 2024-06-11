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

QString DeviceInformation::connectMethod() const
{
    return m_connectMethod;
}

void DeviceInformation::setConnectMethod(const QString &newConnectMethod)
{
    if (m_connectMethod == newConnectMethod)
        return;
    m_connectMethod = newConnectMethod;
    emit connectMethodChanged();
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
