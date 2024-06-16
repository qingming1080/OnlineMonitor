#ifndef WELDTREND_H
#define WELDTREND_H

#include <QStandardItemModel>

///
/// \brief The WeldTrend class : 焊接趋势_折线
///
class WeldTrend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStandardItemModel *pBeforeModel READ pBeforeModel)
    Q_PROPERTY(QStandardItemModel *pAfterModel  READ pAfterModel)
    Q_PROPERTY(QStandardItemModel *pTimeModel   READ pTimeModel)
    Q_PROPERTY(QStandardItemModel *pPowerModel  READ pPowerModel)
public:
    explicit WeldTrend();


    Q_INVOKABLE QStandardItemModel *pBeforeModel() const;
    Q_INVOKABLE QStandardItemModel *pAfterModel() const;
    Q_INVOKABLE QStandardItemModel *pTimeModel() const;
    Q_INVOKABLE QStandardItemModel *pPowerModel() const;

private:
    void init();

private:
    QStandardItemModel* m_pBeforeModel;     // 焊前高度
    QStandardItemModel* m_pAfterModel;      // 焊后高度
    QStandardItemModel* m_pTimeModel;       // 时间
    QStandardItemModel* m_pPowerModel;      // 功率

};

#endif // WELDTREND_H
