#include "weldparam.h"

WeldParam::WeldParam(QObject *parent)
    : QObject{parent}
{

}

double WeldParam::energy() const
{
    return m_energy;
}

void WeldParam::setEnergy(double newEnergy)
{
    if (qFuzzyCompare(m_energy, newEnergy))
        return;
    m_energy = newEnergy;
    emit energyChanged();
}

double WeldParam::amplitude() const
{
    return m_amplitude;
}

void WeldParam::setAmplitude(double newAmplitude)
{
    if (qFuzzyCompare(m_amplitude, newAmplitude))
        return;
    m_amplitude = newAmplitude;
    emit amplitudeChanged();
}

double WeldParam::pressure() const
{
    return m_pressure;
}

void WeldParam::setPressure(double newPressure)
{
    if (qFuzzyCompare(m_pressure, newPressure))
        return;
    m_pressure = newPressure;
    emit pressureChanged();
}
