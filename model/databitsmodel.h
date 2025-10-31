#ifndef DATABITSMODEL_H
#define DATABITSMODEL_H

#include <QAbstractListModel>

class DataBitsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        KeyRole = Qt::UserRole + 1,
        ValueRole
    };
public:
    static DataBitsModel* getInstance();

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int,QByteArray> roleNames() const override;

    Q_INVOKABLE QVariant get(int index) const;

private:
    explicit DataBitsModel(QObject *parent = nullptr);

private:
    static DataBitsModel* m_ptrInstance;
    QList<QVariantMap> m_listDataBits; // List of key-value pairs m_listDataBits;
};

#endif // DATABITSMODEL_H
