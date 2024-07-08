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
    Q_PROPERTY(int max READ max  NOTIFY maxChanged)
    Q_PROPERTY(int min READ min  NOTIFY minChanged)
public:
    explicit Trend(int welderID=0, QObject *parent = nullptr);

    Q_INVOKABLE QStandardItemModel *pBeforeModel() const;
    Q_INVOKABLE QStandardItemModel *pAfterModel() const;
    Q_INVOKABLE QStandardItemModel *pTimeModel() const;
    Q_INVOKABLE QStandardItemModel *pPowerModel() const;
    Q_INVOKABLE QStandardItemModel *pYieldTrend() const;

    void setTrendData(QList<_Production_Data> data);

    int max() const;

    int min() const;

signals:

    void maxChanged();

    void minChanged();

private:
    void init();

private:
    const int m_welderID;
    QStandardItemModel* m_pBeforeModel;     // 焊前高度
    QStandardItemModel* m_pAfterModel;      // 焊后高度
    QStandardItemModel* m_pTimeModel;       // 时间
    QStandardItemModel* m_pPowerModel;      // 功率
    QStandardItemModel* m_pYieldTrend;      // 良率

    QTimer* m_timer;

    int m_max = 0;
    int m_min = 0;

};

#endif // TREND_H
