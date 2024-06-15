#ifndef WELDTREND_H
#define WELDTREND_H

#include <QAbstractListModel>

///
/// \brief The WeldTrend class : 焊接趋势_折线(暂不实现)
///
class WeldTrend : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit WeldTrend(QObject *parent = nullptr);

protected:
    // QML获取列表数量
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    // QML获取列表数据
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // QML获取列名
    virtual QHash<int, QByteArray> roleNames() const override;
};

#endif // WELDTREND_H
