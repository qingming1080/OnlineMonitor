#include "production.h"
Production::Production(int welderID, QObject *parent)
    :QObject{parent}, m_WelderID(welderID)
{

}

QString Production::getGoodRate() const
{
    return QString::number(m_iGoodRate);
}

void Production::setGoodRate(const QString &rate)
{
    bool isOk;
    int iRate = rate.toInt(&isOk);
    if (isOk && m_iGoodRate != iRate)
    {
        m_iGoodRate = iRate;
        emit notifyGoodRateChanged();
    }
}

QString Production::getGoodCycleCount() const
{
    return QString::number(m_iGoodCycleCount);
}

void Production::setGoodCycleCount(const QString &count)
{
    bool isOk = false;
    int iCount = count.toInt(&isOk);
    if (isOk && m_iGoodCycleCount != iCount)
    {
        m_iGoodCycleCount = iCount;
        m_iTotalCycleCount = m_iGoodCycleCount + m_iDefectiveCycleCount + m_iSuspectCycleCount;
        setTotalCycleCount(QString::number(m_iTotalCycleCount));
        m_iGoodCycleCount = static_cast<int>(m_iGoodCycleCount / m_iTotalCycleCount * 100);
        setGoodRate(QString::number(m_iGoodCycleCount));
        emit notifyGoodCycleCountChanged();
    }
}

QString Production::getSuspectCycleCount() const
{
    return QString::number(m_iSuspectCycleCount);
}

void Production::setSuspectCycleCount(const QString &count)
{
    bool isOk = false;
    int iCount = count.toInt(&isOk);
    if (isOk && m_iSuspectCycleCount != iCount)
    {
        m_iSuspectCycleCount = iCount;
        m_iTotalCycleCount = m_iGoodCycleCount + m_iDefectiveCycleCount + m_iSuspectCycleCount;
        setTotalCycleCount(QString::number(m_iTotalCycleCount));
        emit notifySuspectCycleCountChanged();
    }
}

QString Production::getDefectiveCycleCount() const
{
    return QString::number(m_iDefectiveCycleCount);
}

void Production::setDefectiveCycleCount(const QString &count)
{
    bool isOk = false;
    int iCount = count.toInt(&isOk);
    if (isOk && m_iDefectiveCycleCount != iCount)
    {
        m_iDefectiveCycleCount = iCount;
        m_iTotalCycleCount = m_iGoodCycleCount + m_iDefectiveCycleCount + m_iSuspectCycleCount;
        setTotalCycleCount(QString::number(m_iTotalCycleCount));
        emit notifyDefectiveCycleCountChanged();
    }
}

QString Production::getTotalCycleCount() const
{
    return QString::number(m_iTotalCycleCount);
}

void Production::setTotalCycleCount(const QString &count)
{
    bool isOk = false;
    int iCount = count.toInt(&isOk);
    if (isOk && m_iTotalCycleCount != iCount)
    {
        m_iTotalCycleCount = iCount;
        emit notifyTotalCycleCountChanged();
    }
}

int Production::getPeakPower() const
{
    return m_DBProduction.PeakPower;
}

void Production::setPeakPower(const int power)
{
    if (m_DBProduction.PeakPower != power)
    {
        m_DBProduction.PeakPower = power;
        emit notifyPeakPowerChanged();
    }
}

int Production::getWeldTime() const
{
    return m_DBProduction.WeldTime;
}

void Production::setWeldTime(const int time)
{
    if (m_DBProduction.WeldTime != time)
    {
        m_DBProduction.WeldTime = time;
        emit notifyWeldTimeChanged();
    }   
}

int Production::getEnergy() const
{
    return m_DBProduction.Energy;
}

void Production::setEnergy(const int energy)
{
    if (m_DBProduction.Energy != energy)
    {
        m_DBProduction.Energy = energy;
        emit notifyEnergyChanged();
    }
}

int Production::getPreheight() const
{
    return m_DBProduction.Preheight;
}

void Production::setPreheight(const int height)
{
    if (m_DBProduction.Preheight != height)
    {
        m_DBProduction.Preheight = height;
        emit notifyPreheightChanged();
    }
}

int Production::getPostHeight() const
{
    return m_DBProduction.PostHeight;
}

void Production::setPostHeight(const int height)
{
    if (m_DBProduction.PostHeight != height)
    {
        m_DBProduction.PostHeight = height;
        emit notifyPostHeightChanged();
    }
}
