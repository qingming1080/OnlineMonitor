#ifndef COMMODEL_H
#define COMMODEL_H

#include <QAbstractListModel>

class ComModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        KeyRole = Qt::UserRole + 1,
        ValueRole
    };
public:
    static ComModel* getInstance();

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int,QByteArray> roleNames() const override;

    Q_INVOKABLE QVariant get(int index) const;

private:
    explicit ComModel(QObject *parent = nullptr);

private:
    static constexpr int COM1 = 0;
    static constexpr int COM2 = 1;
    static ComModel* m_ptrInstance;
    QList<QVariantMap> m_listComPort; // List of key-value pairs m_listComPort;
};
#endif // COMMODEL_H
