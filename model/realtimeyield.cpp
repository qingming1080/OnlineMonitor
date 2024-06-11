#include "realtimeyield.h"

RealTimeYield::RealTimeYield(QObject *parent)
    : QObject{parent}
{

}

int RealTimeYield::passRate() const
{
    return m_passRate;
}

void RealTimeYield::setPassRate(int newPassRate)
{
    if (m_passRate == newPassRate)
        return;
    m_passRate = newPassRate;
    emit passRateChanged();
}

int RealTimeYield::passNum() const
{
    return m_passNum;
}

void RealTimeYield::setPassNum(int newPassNum)
{
    if (m_passNum == newPassNum)
        return;
    m_passNum = newPassNum;
    emit passNumChanged();
}

int RealTimeYield::dubiousNum() const
{
    return m_dubiousNum;
}

void RealTimeYield::setDubiousNum(int newDubiousNum)
{
    if (m_dubiousNum == newDubiousNum)
        return;
    m_dubiousNum = newDubiousNum;
    emit dubiousNumChanged();
}

int RealTimeYield::rejectNum() const
{
    return m_rejectNum;
}

void RealTimeYield::setRejectNum(int newRejectNum)
{
    if (m_rejectNum == newRejectNum)
        return;
    m_rejectNum = newRejectNum;
    emit rejectNumChanged();
}

int RealTimeYield::sumNum() const
{
    return m_sumNum;
}

void RealTimeYield::setSumNum(int newSumNum)
{
    if (m_sumNum == newSumNum)
        return;
    m_sumNum = newSumNum;
    emit sumNumChanged();
}
