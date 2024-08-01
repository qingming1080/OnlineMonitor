#include "deviceinformation.h"
#include "DataBase/databasemanager.h"
#include <QVariant>

#include "signalmanager.h"
#include <QDebug>
#include <QElapsedTimer>
#include "log/localrecord.h"

DeviceInformation::DeviceInformation(int welderID, QObject *parent)
    : QObject{parent}, m_id(welderID)
{
    QElapsedTimer timer;
    timer.start();

    _Configuration_Data data = DataBaseManager::getInstance()->getConfigurationData(welderID);

    m_name  = data.welder_name;
    m_model = data.welder_type;
    m_maxBacth = data.production_bacth;
    m_sample    = data.model_sample;
    m_lowerLimit = data.lower_limit;
    m_heightOption = data.height_option;
    m_connectType = static_cast<QmlEnum::CONNECTTYPE>(data.connect_type);
    m_connectID = data.connect_id;
    m_mesPort = data.mes_port;
    m_mesIP = data.mes_ip;
    m_deviceIP = data.device_ip;

    if(welderID == 1){
        m_goodRate = 22;
        m_power = 12;
    }
    if(welderID == 4){
        m_power = 16;
        m_goodRate = 30;
    }

    QString text = QString("%1号设备_DeviceInformation_初始化耗时:%2ms").arg(welderID).arg(timer.elapsed());
    emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), text);
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

    DataBaseManager::getInstance()->setConfigurationData(m_id, QmlEnum::CONFIGURATION_welder_name, m_name);
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

    DataBaseManager::getInstance()->setConfigurationData(m_id, QmlEnum::CONFIGURATION_welder_type, m_model);
}

QmlEnum::CONNECTTYPE DeviceInformation::connectType() const
{
    return m_connectType;
}

void DeviceInformation::setConnectType(const QmlEnum::CONNECTTYPE &newconnectType)
{
    if (m_connectType == newconnectType)
        return;
    m_connectType = newconnectType;
    emit connectTypeChanged();

    DataBaseManager::getInstance()->setConfigurationData(m_id, QmlEnum::CONFIGURATION_connect_type, m_connectType);
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

    DataBaseManager::getInstance()->setConfigurationData(m_id, QmlEnum::CONFIGURATION_production_bacth, m_maxBacth);
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

    DataBaseManager::getInstance()->setConfigurationData(m_id, QmlEnum::CONFIGURATION_model_sample, m_sample);
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

    DataBaseManager::getInstance()->setConfigurationData(m_id, QmlEnum::CONFIGURATION_height_option, m_heightOption);
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

    DataBaseManager::getInstance()->setConfigurationData(m_id, QmlEnum::CONFIGURATION_lower_limit, m_lowerLimit);
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

    DataBaseManager::getInstance()->setConfigurationData(m_id, QmlEnum::CONFIGURATION_connect_id, m_connectID);
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

int DeviceInformation::goodRate() const
{
    return m_goodRate;
}

void DeviceInformation::setGoodRate(int newGoodRate)
{
    if (m_goodRate == newGoodRate)
        return;
    m_goodRate = newGoodRate;
    emit goodRateChanged();
}

int DeviceInformation::goodCycles() const
{
    return m_goodCycles;
}

void DeviceInformation::setGoodCycles(int newGoodCycles)
{
    if (m_goodCycles == newGoodCycles)
        return;
    m_goodCycles = newGoodCycles;
    emit goodCyclesChanged();
}

int DeviceInformation::suspectCycles() const
{
    return m_suspectCycles;
}

void DeviceInformation::setSuspectCycles(int newSuspectCycles)
{
    if (m_suspectCycles == newSuspectCycles)
        return;
    m_suspectCycles = newSuspectCycles;
    emit suspectCyclesChanged();
}

int DeviceInformation::notDefinite() const
{
    return m_notDefinite;
}

void DeviceInformation::setNotDefinite(int newNotDefinite)
{
    if (m_notDefinite == newNotDefinite)
        return;
    m_notDefinite = newNotDefinite;
    emit notDefiniteChanged();
}

int DeviceInformation::power() const
{
    return m_power;
}

void DeviceInformation::setPower(int newPower)
{
    if (m_power == newPower)
        return;
    m_power = newPower;
    emit powerChanged();
}

int DeviceInformation::time() const
{
    return m_time;
}

void DeviceInformation::setTime(int newTime)
{
    if (m_time == newTime)
        return;
    m_time = newTime;
    emit timeChanged();
}

int DeviceInformation::energy() const
{
    return m_energy;
}

void DeviceInformation::setEnergy(int newEnergy)
{
    if (m_energy == newEnergy)
        return;
    m_energy = newEnergy;
    emit energyChanged();
}

int DeviceInformation::heightPre() const
{
    return m_heightPre;
}

void DeviceInformation::setHeightPre(int newHeightPre)
{
    if (m_heightPre == newHeightPre)
        return;
    m_heightPre = newHeightPre;
    emit heightPreChanged();
}

int DeviceInformation::heightPost() const
{
    return m_heightPost;
}

void DeviceInformation::setHeightPost(int newHeightPost)
{
    if (m_heightPost == newHeightPost)
        return;
    m_heightPost = newHeightPost;
    emit heightPostChanged();
}

QString DeviceInformation::mesIP() const
{
    return m_mesIP;
}

void DeviceInformation::setMesIP(const QString &newMesIP)
{
    if (m_mesIP == newMesIP)
        return;
    m_mesIP = newMesIP;
    emit mesIPChanged();
}

QString DeviceInformation::deviceIP() const
{
    return m_deviceIP;
}

void DeviceInformation::setDeviceIP(const QString &newDeviceIP)
{
    if (m_deviceIP == newDeviceIP)
        return;
    m_deviceIP = newDeviceIP;
    emit deviceIPChanged();
}

int DeviceInformation::mesPort() const
{
    return m_mesPort;
}

void DeviceInformation::setMesPort(int newMesPort)
{
    if (m_mesPort == newMesPort)
        return;
    m_mesPort = newMesPort;
    emit mesPortChanged();
}
