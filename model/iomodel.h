#ifndef IOMODEL_H
#define IOMODEL_H

#include <QAbstractListModel>
#include "define.h"

///
/// \brief The IOModel class : IO
///
class IOModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit IOModel(int welderID, QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    Q_INVOKABLE int rowCount(const QModelIndex &parent) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE QVariant getDataByWelderID(int welderID, int role) const;
    Q_INVOKABLE void setIOData(int id, _IO_COLUMN column, QVariant data);

private:


private:
    const int m_welderID;
    QList<_IO_Data> m_data;
};

#endif // IOMODEL_H
