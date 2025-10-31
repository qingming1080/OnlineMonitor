#ifndef BAUDRATEMODEL_H
#define BAUDRATEMODEL_H

#include <QAbstractListModel>

class BaudRateModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        KeyRole = Qt::UserRole + 1,
        ValueRole
    };
public:
    static BaudRateModel* getInstance();

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int,QByteArray> roleNames() const override;

    Q_INVOKABLE QVariant get(int index) const;

private:
    explicit BaudRateModel(QObject *parent = nullptr);

private:
    static BaudRateModel* m_ptrInstance;
    QList<QVariantMap> m_listBaudRate; // List of key-value pairs m_listComPort;
};

#endif // BAUDRATEMODEL_H
