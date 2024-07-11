#ifndef HISTORY_H
#define HISTORY_H

#include <QAbstractListModel>
#include "define.h"

class History : public QAbstractListModel
{
    Q_OBJECT
public:
    static History* getInstance();

    // QAbstractItemModel interface
public:
    Q_INVOKABLE int rowCount(const QModelIndex &parent) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void setWelderID(int welderID = 0);

private:
    explicit History(QObject *parent = nullptr);

private:
    static History* s_pHistory;

    QList<_Production_Data> m_data;
};

#endif // HISTORY_H
