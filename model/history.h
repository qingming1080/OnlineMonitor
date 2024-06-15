#ifndef HISTORY_H
#define HISTORY_H

#include <QAbstractListModel>
#include "qmlenum.h"

///
/// \brief The History class : 历史记录(不属于如何设备)
///
class History : public QAbstractListModel
{
    Q_OBJECT
public:
    enum _HISTORY_ROLE{
        _HISTORY_ROLE_name = 0,   // 名称
        _HISTORY_ROLE_date,       // 日期
        _HISTORY_ROLE_energy,     // 能量
        _HISTORY_ROLE_power,      // 功率
        _HISTORY_ROLE_result,     // 结果
    };

    struct _History_Data{
        QString name;
        QString date;
        int energy;
        int power;
        QmlEnum::_PRODUCTSTATE result;
    };

public:
    explicit History(QObject *parent = nullptr);

protected:
    // QML获取列表数量
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    // QML获取列表数据
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // QML获取列名
    virtual QHash<int, QByteArray> roleNames() const override;

private:
    QList<_History_Data> m_data;
};

#endif // HISTORY_H
