#include "yieldtrend.h"

YieldTrend::YieldTrend()
{
    /// 设置模型三列 0_行数  1_x轴  2_y轴
    setColumnCount(3);

    for(int i = 10; i < 20; ++i)
        addRow(QDateTime::fromString(QString("2001-01-01 01:%1:00").arg(i), "yyyy-MM-dd hh:mm:ss"),i);
}

void YieldTrend::addRow(QDateTime x, int y)
{
    int row = rowCount();

    QStandardItem* rowItem = new QStandardItem(QString::number(row));
    QStandardItem* xItem   = new QStandardItem(QString::number(x.toMSecsSinceEpoch()));
    QStandardItem* yItem   = new QStandardItem(QString::number(y));

    QStandardItemModel::setItem(row, 0, rowItem);
    QStandardItemModel::setItem(row, 1, xItem);
    QStandardItemModel::setItem(row, 2, yItem);
}

