#ifndef YIELDTREND_H
#define YIELDTREND_H

#include <QStandardItemModel>

///
/// \brief The YidldTrend class : 良率趋势_折线
///
class YieldTrend : public QObject
{
    Q_OBJECT
public:
    explicit YieldTrend();

    Q_INVOKABLE QStandardItemModel* getModel();

    ///
    /// \brief addRow : 添加一行数据
    ///
    void addRow(int x, int y);

    void clear();

private:
    QStandardItemModel* m_pItemModel{nullptr};   // 良品折线模型
};

#endif // YIELDTREND_H
