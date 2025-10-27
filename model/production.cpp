#include "production.h"
Production::Production(int welderID, QObject *parent)
    :QObject{parent}, m_WelderID(welderID)
{

}

int Production::goodRate() const
{
    return m_goodRate;
}

void Production::setGoodRate(int newGoodRate)
{
    if (m_goodRate == newGoodRate)
        return;
    m_goodRate = newGoodRate;
    emit goodRateChanged();
}

int Production::goodCycles() const
{
    return m_goodCycles;
}

void Production::setGoodCycles(int newGoodCycles)
{
    if (m_goodCycles == newGoodCycles)
        return;
    m_goodCycles = newGoodCycles;
    emit goodCyclesChanged();
}

int Production::suspectCycles() const
{
    return m_suspectCycles;
}

void Production::setSuspectCycles(int newSuspectCycles)
{
    if (m_suspectCycles == newSuspectCycles)
        return;
    m_suspectCycles = newSuspectCycles;
    emit suspectCyclesChanged();
}

int  Production::power() const
{
    return m_power;
}

void Production::setPower(int  newPower)
{
    m_power = newPower;
    emit powerChanged();
}

int  Production::time() const
{
    return m_time;
}

void Production::setTime(int  newTime)
{
    m_time = newTime;
    emit timeChanged();
}

int  Production::energy() const
{
    return m_energy;
}

void Production::setEnergy(int  newEnergy)
{
    m_energy = newEnergy;
    emit energyChanged();

}

int  Production::heightPre() const
{
    return m_heightPre;
}

void Production::setHeightPre(int  newHeightPre)
{
    m_heightPre = newHeightPre;
    emit heightPreChanged();

}

int  Production::heightPost() const
{
    return m_heightPost;
}

void Production::setHeightPost(int  newHeightPost)
{
    if (m_heightPost == newHeightPost)
        return;
    m_heightPost = newHeightPost;
    emit heightPostChanged();
}
