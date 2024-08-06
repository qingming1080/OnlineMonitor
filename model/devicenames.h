#ifndef DEVICENAMES_H
#define DEVICENAMES_H

#include <QAbstractListModel>

class DeviceNames : public QAbstractListModel
{
    Q_OBJECT
public:
    static DeviceNames* getInstance();

public:
    Q_INVOKABLE int rowCount(const QModelIndex &parent) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const;

    void setNames(QList<QString> names);

private:
    explicit DeviceNames(QObject *parent = nullptr);


private:
    static DeviceNames* s_pDeviceNames;

    QList<QString> m_names;
};

#endif // DEVICENAMES_H
