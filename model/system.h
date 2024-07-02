#ifndef SYSTEM_H
#define SYSTEM_H

#include <QAbstractListModel>
#include "define.h"

///
/// \brief The System class : system_conf
///
class System : public QAbstractListModel
{
    Q_OBJECT
public:
   explicit System(int welderID, QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    Q_INVOKABLE int rowCount(const QModelIndex &parent) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE QVariant getSystemByWelderID(int welderID, int role) const;
    Q_INVOKABLE void setSystemData(int id, _SYSTEM_COLUMN column, QVariant data);

private:


private:
    const int m_welderID;

    QList<_System_Data> m_data;
};

#endif // SYSTEM_H
