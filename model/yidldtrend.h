#ifndef YIDLDTREND_H
#define YIDLDTREND_H

#include <QAbstractListModel>

///
/// \brief The YidldTrend class : 良率趋势_折现(暂不实现)
///
class YidldTrend : public QAbstractListModel
{
    Q_OBJECT
public:
    static YidldTrend* getInstance();


protected:
    // QML获取列表数量
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    // QML获取列表数据
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // QML获取列名
    virtual QHash<int, QByteArray> roleNames() const override;

private:
    explicit YidldTrend();

private:
    static YidldTrend* s_pYidldTrend;
};

#endif // YIDLDTREND_H
