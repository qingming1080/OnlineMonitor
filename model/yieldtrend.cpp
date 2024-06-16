#include "yieldtrend.h"

YieldTrend::YieldTrend()
{
    m_pItemModel = new QStandardItemModel();
    /// 设置模型三列 0_行数  1_x轴  2_y轴
    m_pItemModel->setColumnCount(3);
}

QStandardItemModel *YieldTrend::getModel()
{
    return m_pItemModel;
}

void YieldTrend::addRow(int x, int y)
{
    int row = m_pItemModel->rowCount();

    QStandardItem* rowItem = new QStandardItem(QString::number(row));
    QStandardItem* xItem   = new QStandardItem(QString::number(x));
    QStandardItem* yItem   = new QStandardItem(QString::number(y));

    m_pItemModel->QStandardItemModel::setItem(row, 0, rowItem);
    m_pItemModel->QStandardItemModel::setItem(row, 1, xItem);
    m_pItemModel->QStandardItemModel::setItem(row, 2, yItem);
}

void YieldTrend::clear()
{
    m_pItemModel->clear();
}

