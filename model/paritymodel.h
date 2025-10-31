#ifndef PARITYMODEL_H
#define PARITYMODEL_H

#include <QAbstractListModel>

class ParityModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        KeyRole = Qt::UserRole + 1,
        ValueRole
    };
public:
    static ParityModel* getInstance();

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int,QByteArray> roleNames() const override;

    Q_INVOKABLE QVariant get(int index) const;

private:
    explicit ParityModel(QObject *parent = nullptr);

private:
    static ParityModel* m_ptrInstance;
    QList<QVariantMap> m_listParityBits; // List of key-value pairs m_listParityBits;
};

#endif // PARITYMODEL_H
