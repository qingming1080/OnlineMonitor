#include "weldresults.h"

WeldResults::WeldResults(QObject *parent)
    : QObject{parent}
{

}

double WeldResults::power() const
{
    return m_power;
}

void WeldResults::setPower(double newPower)
{
    if (m_power == newPower)
        return;
    m_power = newPower;
    emit powerChanged();
}

double WeldResults::time() const
{
    return m_time;
}

void WeldResults::setTime(double newTime)
{
    if (m_time == newTime)
        return;
    m_time = newTime;
    emit timeChanged();
}

double WeldResults::energy() const
{
    return m_energy;
}

void WeldResults::setEnergy(double newEnergy)
{
    if (m_energy == newEnergy)
        return;
    m_energy = newEnergy;
    emit energyChanged();
}

double WeldResults::heightPre() const
{
    return m_heightPre;
}

void WeldResults::setHeightPre(double newHeightPre)
{
    if (m_heightPre == newHeightPre)
        return;
    m_heightPre = newHeightPre;
    emit heightPreChanged();
}

double WeldResults::heightPost() const
{
    return m_heightPost;
}

void WeldResults::setHeightPost(double newHeightPost)
{
    if (m_heightPost == newHeightPost)
        return;
    m_heightPost = newHeightPost;
    emit heightPostChanged();
}
