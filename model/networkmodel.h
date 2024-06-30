#ifndef NETWORKMODEL_H
#define NETWORKMODEL_H

#include <QAbstractListModel>
#include "define.h"

///
/// \brief The NetworkModel class : 网络连接
///
class NetworkModel : public QAbstractListModel
{
    Q_OBJECT
public:
    static NetworkModel* getInstance();

    // QAbstractItemModel interface
public:
    Q_INVOKABLE int rowCount(const QModelIndex &parent) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE QVariant getDataByWelderID(int welderID, int role) const;
    Q_INVOKABLE void setNetworkData(int id, _NETWORK_COLUMN column, QVariant data);

private:
    explicit NetworkModel(QObject *parent = nullptr);

private:
    static NetworkModel* s_pNetworkModel;

    QList<_Network_Data> m_data;
};

#endif // NETWORKMODEL_H
