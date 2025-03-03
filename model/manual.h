#ifndef MANUAL_H
#define MANUAL_H

#include <QAbstractListModel>
#include "define.h"

///
/// \brief The Manual class : manual
/// 暴露添加一行接口，暴露数据库保存接口
class Manual : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit Manual(int welderID = 0, QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    Q_INVOKABLE int rowCount(const QModelIndex &parent) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const;
    Q_INVOKABLE virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    Q_INVOKABLE void save();
    Q_INVOKABLE void clearData();
private:


private:
    const int m_welderID;

    QList<_Manual_Data> m_data;
};

#endif // MANUAL_H
