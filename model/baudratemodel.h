#ifndef BAUDRATEMODEL_H
#define BAUDRATEMODEL_H

#include <QAbstractListModel>

class BaudRateModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int BaudRateIndex    READ getBaudRateIndex   WRITE setBaudRateIndex  NOTIFY notifyBaudRateIndexChanged FINAL)
public:
    enum Roles {
        KeyRole = Qt::UserRole + 1,
        ValueRole
    };
public:
    static BaudRateModel* getInstance();

    int getBaudRateIndex() const;
    void setBaudRateIndex(const int &index);
    int indexOfValueRole(const int value) const;

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int,QByteArray> roleNames() const override;

    Q_INVOKABLE QVariant get(int index) const;
signals:
    void notifyBaudRateIndexChanged();

private:
    explicit BaudRateModel(QObject *parent = nullptr);

private:
    static BaudRateModel* m_ptrInstance;
    QList<QVariantMap> m_listBaudRate; // List of key-value pairs m_listComPort;
    int m_iCurrentBaudRateIndex;
};

#endif // BAUDRATEMODEL_H
