#ifndef YIELDTREND_H
#define YIELDTREND_H

#include <QStandardItemModel>
#include <QDateTime>

///
/// \brief The YidldTrend class : 良率趋势_折线
///
class YieldTrend : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit YieldTrend();

    ///
    /// \brief addRow : 添加一行数据
    ///
    void addRow(QDateTime x, int y);

};

#endif // YIELDTREND_H
