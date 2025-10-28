#include "system.h"
#include "signalmanager.h"
#include <QDebug>
#include <QElapsedTimer>
#include "log/localrecord.h"

System::System(int welderID, QObject *parent)
    : QObject{parent}, m_WelderID(welderID)
{
    // QElapsedTimer timer;
    // timer.start();

    bool bResult = DataBaseManager::getInstance()->getSystemData(m_WelderID, m_DBSystem);
    if(bResult == false)
    {
        setSingleFactor("20");
        setGeneralFactor("80");
        setAutoUpperLimit("90");
        setForceThreshold("1300");
        setResidualThreshold("90");
    }

    // QString text = QString("%1号设备_System_初始化耗时:%2ms").arg(welderID).arg(timer.elapsed());
    // emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), text);
}

// int System::id() const
// {
//     return m_id;
// }

// void System::setId(int newId)
// {
//     if (m_id == newId)
//         return;
//     m_id = newId;
//     emit idChanged();
// }

QString System::getSingleFactor() const
{
    return QString::number(m_DBSystem.SingleFactorSetting);
}

int System::GetSingleFactor() const
{
    return m_DBSystem.SingleFactorSetting;
}

void System::setSingleFactor(const QString &factor)
{
    bool isOk;
    int iFactor = factor.toInt(&isOk);
    if (!isOk || m_DBSystem.SingleFactorSetting == iFactor)
        return;
    m_DBSystem.SingleFactorSetting = iFactor;
    emit notifySingleFactorChanged();
}

QString System::getGeneralFactor() const
{
    return QString::number(m_DBSystem.GeneralFactorSetting);
}

int System::GetGeneralFactor() const
{
    return m_DBSystem.GeneralFactorSetting;
}

void System::setGeneralFactor(const QString &factor)
{
    bool isOk = false;
    int iFactor = factor.toInt(&isOk);
    if (!isOk || m_DBSystem.GeneralFactorSetting == iFactor)
        return;
    m_DBSystem.GeneralFactorSetting = iFactor;
    emit notifyGeneralFactorChanged();
}

QString System::getForceThreshold() const
{
    return QString::number(m_DBSystem.ForceThreshold);
}

int System::GetForceThreshold() const
{
    return m_DBSystem.ForceThreshold;
}

void System::setForceThreshold(const QString &threshold)
{
    bool isOk = false;
    int iThreshold = threshold.toInt(&isOk);
    if (!isOk || m_DBSystem.ForceThreshold == iThreshold)
        return;
    m_DBSystem.ForceThreshold = iThreshold;
    emit notifyForceThresholdChanged();
}

QString System::getAutoUpperLimit() const
{
    return QString::number(m_DBSystem.AutoUpperLimit);
}

int System::GetAutoUpperLimit() const
{
    return m_DBSystem.AutoUpperLimit;
}

void System::setAutoUpperLimit(const QString &limit)
{
    bool isOk = false;
    int iLimit = limit.toInt(&isOk);
    if (!isOk || m_DBSystem.AutoUpperLimit == iLimit)
        return;
    m_DBSystem.AutoUpperLimit = iLimit;
    emit notifyAutoUpperLimitChanged();
}

QString System::getResidualThreshold() const
{
    return QString::number(m_DBSystem.ResidualThreshold);
}

int System::GetResidualThreshold() const
{
    return m_DBSystem.ResidualThreshold;
}

void System::setResidualThreshold(const QString &threshold)
{
    bool isOk = false;
    int iThreshold = threshold.toInt(&isOk);
    if (!isOk || m_DBSystem.ResidualThreshold == iThreshold)
        return;
    m_DBSystem.ResidualThreshold = iThreshold;
    emit notifyResidualThresholdChanged();
}

