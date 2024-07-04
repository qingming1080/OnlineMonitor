#include "weldtrend.h"

WeldTrend::WeldTrend()
{
    init();
    for(int i = 0; i < 100; ++i)
    {
        QStandardItem* rowItem = new QStandardItem(QString::number(i));
        QStandardItem* xItem   = new QStandardItem(QString::number(i));
        QStandardItem* yItem   = new QStandardItem(QString::number(i));

        m_pBeforeModel->setItem(i, 0, rowItem);
        m_pBeforeModel->setItem(i, 1, xItem);
        m_pBeforeModel->setItem(i, 2, yItem);
    }
    for(int i = 100; i > 0; i--)
    {
        QStandardItem* rowItem = new QStandardItem(QString::number(100-i));
        QStandardItem* xItem   = new QStandardItem(QString::number(i));
        QStandardItem* yItem   = new QStandardItem(QString::number(100-i));

        m_pAfterModel->setItem(i, 0, rowItem);
        m_pAfterModel->setItem(i, 1, xItem);
        m_pAfterModel->setItem(i, 2, yItem);
    }
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

