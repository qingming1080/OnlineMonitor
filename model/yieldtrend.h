#ifndef YIELDTREND_H
#define YIELDTREND_H

#include <QAbstractListModel>

///
/// \brief The YidldTrend class : 良率趋势_折线(暂不实现)
///
class YieldTrend : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit YieldTrend();


protected:
    // QML获取列表数量
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    // QML获取列表数据
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // QML获取列名
    virtual QHash<int, QByteArray> roleNames() const override;

private:


};

#endif // YIELDTREND_H
