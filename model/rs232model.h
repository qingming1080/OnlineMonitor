#ifndef RS232MODEL_H
#define RS232MODEL_H

#include <QAbstractListModel>

class RS232Model : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        KeyRole = Qt::UserRole + 1,
        ValueRole
    };
public:
    static RS232Model* getInstance();

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int,QByteArray> roleNames() const override;

    Q_INVOKABLE QVariant get(int index) const;

private:
    explicit RS232Model(QObject *parent = nullptr);

private:
    static constexpr int COM1 = 0;
    static constexpr int COM2 = 1;
    static RS232Model* m_ptrInstance;
    QList<QVariantMap> m_listComPort; // List of key-value pairs m_listComPort;
};
#endif // RS232MODEL_H
