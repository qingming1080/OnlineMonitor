#include "weldtrend.h"

WeldTrend::WeldTrend()
{
    init();
}


QStandardItemModel *WeldTrend::pBeforeModel() const
{
    return m_pBeforeModel;
}

QStandardItemModel *WeldTrend::pAfterModel() const
{
    return m_pAfterModel;
}

QStandardItemModel *WeldTrend::pTimeModel() const
{
    return m_pTimeModel;
}

QStandardItemModel *WeldTrend::pPowerModel() const
{
    return m_pPowerModel;
}

void WeldTrend::init()
{
    m_pBeforeModel  = new QStandardItemModel();
    m_pAfterModel   = new QStandardItemModel();
    m_pTimeModel    = new QStandardItemModel();
    m_pPowerModel   = new QStandardItemModel();

    m_pBeforeModel->setColumnCount(3);
    m_pAfterModel->setColumnCount(3);
    m_pTimeModel->setColumnCount(3);
    m_pPowerModel->setColumnCount(3);
}

