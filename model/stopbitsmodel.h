#ifndef STOPBITSMODEL_H
#define STOPBITSMODEL_H

#include <QAbstractListModel>

class StopBitsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        KeyRole = Qt::UserRole + 1,
        ValueRole
    };
public:
    static StopBitsModel* getInstance();

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int,QByteArray> roleNames() const override;

    Q_INVOKABLE QVariant get(int index) const;

private:
    explicit StopBitsModel(QObject *parent = nullptr);

private:
    static StopBitsModel* m_ptrInstance;
    QList<QVariantMap> m_listStopBits; // List of key-value pairs m_listStopBits;
};

#endif // STOPBITSMODEL_H
