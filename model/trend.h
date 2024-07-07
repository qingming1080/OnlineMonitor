#ifndef TREND_H
#define TREND_H

#include <QObject>
#include <QStandardItemModel>
#include "define.h"

class Trend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStandardItemModel *pBeforeModel READ pBeforeModel)  // 焊前高度
    Q_PROPERTY(QStandardItemModel *pAfterModel  READ pAfterModel)   // 焊后高度
    Q_PROPERTY(QStandardItemModel *pTimeModel   READ pTimeModel)    // 时间
    Q_PROPERTY(QStandardItemModel *pPowerModel  READ pPowerModel)   // 功率
    Q_PROPERTY(QStandardItemModel *pYieldTrend  READ pYieldTrend)   // 良率
public:
    explicit Trend(QObject *parent = nullptr);

    Q_INVOKABLE QStandardItemModel *pBeforeModel() const;
    Q_INVOKABLE QStandardItemModel *pAfterModel() const;
    Q_INVOKABLE QStandardItemModel *pTimeModel() const;
    Q_INVOKABLE QStandardItemModel *pPowerModel() const;
    Q_INVOKABLE QStandardItemModel *pYieldTrend() const;

    void setTrendData(QList<_Production_Data> data);

signals:

private:
    void init();

private:
    QStandardItemModel* m_pBeforeModel;     // 焊前高度
    QStandardItemModel* m_pAfterModel;      // 焊后高度
    QStandardItemModel* m_pTimeModel;       // 时间
    QStandardItemModel* m_pPowerModel;      // 功率
    QStandardItemModel* m_pYieldTrend;      // 良率

};

#endif // TREND_H
