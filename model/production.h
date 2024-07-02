#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <QAbstractListModel>
#include "define.h"

///
/// \brief The Production class : Production
///
class Production : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit Production(int welderID, QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    Q_INVOKABLE int rowCount(const QModelIndex &parent) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE QVariant getProductionByWelderID(int welderID, int role) const;
    Q_INVOKABLE void setProductionData(int id, _PRODUCTION_COLUMN column, QVariant data);

    Q_INVOKABLE void save();
private:


private:
    const int m_welderID;

    QList<_Production_Data> m_data;
};

#endif // PRODUCTION_H
