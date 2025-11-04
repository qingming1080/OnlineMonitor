#ifndef NETWORKMODEL_H
#define NETWORKMODEL_H

#include <QAbstractListModel>
#include <QMap>

///
/// \brief The NetworkModel class : 网络连接
///
class NetworkModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        KeyRole = Qt::UserRole + 1,
        ValueRole
    };
public:
    static NetworkModel* getInstance();

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int,QByteArray> roleNames() const override;

    Q_INVOKABLE QVariant get(const int index) const;
    Q_INVOKABLE int getKeyRoleIndex(const int value) const;

private:
    explicit NetworkModel(QObject *parent = nullptr);

private:
    static constexpr int ETH1 = 0;
    static constexpr int ETH2 = 1;
    static constexpr int ETH3 = 2;
    static constexpr int ETH4 = 3;
    static constexpr int ETH5 = 4;
    static NetworkModel* m_ptrInstance;
    QList<QVariantMap> m_listETHPort; // List of key-value pairs m_listETHPort;
};
#endif // NETWORKMODEL_H
