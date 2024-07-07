#include "trend.h"

Trend::Trend(QObject *parent)
    : QObject{parent}
{
    init();
}

QStandardItemModel *Trend::pBeforeModel() const
{
    return m_pBeforeModel;
}

QStandardItemModel *Trend::pAfterModel() const
{
    return m_pAfterModel;
}

QStandardItemModel *Trend::pTimeModel() const
{
    return m_pTimeModel;
}

QStandardItemModel *Trend::pPowerModel() const
{
    return m_pPowerModel;
}

QStandardItemModel *Trend::pYieldTrend() const
{
    return m_pYieldTrend;
}

void Trend::setTrendData(QList<_Production_Data> data)
{
    // 清除当前折线数据
    m_pBeforeModel->clear();
    m_pAfterModel->clear();
    m_pTimeModel->clear();
    m_pPowerModel->clear();
    m_pYieldTrend->clear();

    for(int row = 0; row < data.size(); ++row)
    {
        // 焊前高度
        QStandardItem* before_Row_Item = new QStandardItem(QString::number(row));
        QStandardItem* before_X_Item = new QStandardItem(QString::number(data.at(row).serial_number));
        QStandardItem* before_Y_Item = new QStandardItem(QString::number(data.at(row).pre_height));
        m_pBeforeModel->setItem(row, 0, before_Row_Item);
        m_pBeforeModel->setItem(row, 1, before_X_Item);
        m_pBeforeModel->setItem(row, 2, before_Y_Item);

        // 焊后高度
        QStandardItem* after_Row_Item = new QStandardItem(QString::number(row));
        QStandardItem* after_X_Item = new QStandardItem(QString::number(data.at(row).serial_number));
        QStandardItem* after_Y_Item = new QStandardItem(QString::number(data.at(row).post_height));
        m_pAfterModel->setItem(row, 0, after_Row_Item);
        m_pAfterModel->setItem(row, 1, after_X_Item);
        m_pAfterModel->setItem(row, 2, after_Y_Item);

        // 时间
        QStandardItem* time_Row_Item = new QStandardItem(QString::number(row));
        QStandardItem* time_X_Item = new QStandardItem(QString::number(data.at(row).serial_number));
        // 去掉数据库的s时间单位
        QString time = data.at(row).time.left(data.at(row).time.length()-1);
        QStandardItem* time_Y_Item = new QStandardItem(time);
        m_pTimeModel->setItem(row, 0, time_Row_Item);
        m_pTimeModel->setItem(row, 1, time_X_Item);
        m_pTimeModel->setItem(row, 2, time_Y_Item);

        // 功率
        QStandardItem* power_Row_Item = new QStandardItem(QString::number(row));
        QStandardItem* power_X_Item = new QStandardItem(QString::number(data.at(row).serial_number));
        QStandardItem* power_Y_Item = new QStandardItem(QString::number(data.at(row).power));
        m_pPowerModel->setItem(row, 0, power_Row_Item);
        m_pPowerModel->setItem(row, 1, power_X_Item);
        m_pPowerModel->setItem(row, 2, power_Y_Item);

        // 良率折线
        QStandardItem* yieldItem = new QStandardItem(QString::number(row));
        QDateTime creatTime = QDateTime::fromString(data.at(row).create_time, "yyyy-MM-dd hh:mm:ss");
        QStandardItem* yield_X_Item   = new QStandardItem(QString::number(creatTime.toMSecsSinceEpoch()));
        QStandardItem* yield_Y_Item   = new QStandardItem(QString::number(data.at(row).good_rate));
        m_pYieldTrend->setItem(row, 0, yieldItem);
        m_pYieldTrend->setItem(row, 1, yield_X_Item);
        m_pYieldTrend->setItem(row, 2, yield_Y_Item);
    }
}

void Trend::init()
{
    m_pBeforeModel  = new QStandardItemModel();
    m_pBeforeModel->setColumnCount(3);

    m_pAfterModel   = new QStandardItemModel();
    m_pAfterModel->setColumnCount(3);

    m_pTimeModel    = new QStandardItemModel();
    m_pTimeModel->setColumnCount(3);

    m_pPowerModel   = new QStandardItemModel();
    m_pPowerModel->setColumnCount(3);

    m_pYieldTrend   = new QStandardItemModel();
    m_pYieldTrend->setColumnCount(3);
}
