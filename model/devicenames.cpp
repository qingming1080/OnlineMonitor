#include "devicenames.h"

DeviceNames* DeviceNames::s_pDeviceNames = nullptr;

DeviceNames *DeviceNames::getInstance()
{
    if(s_pDeviceNames == nullptr)
        s_pDeviceNames = new DeviceNames();

    return s_pDeviceNames;
}

int DeviceNames::rowCount(const QModelIndex &parent) const
{
    return m_names.size();
}

QVariant DeviceNames::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    return m_names.at(index.row());
}

QHash<int, QByteArray> DeviceNames::roleNames() const
{
    QHash<int, QByteArray> hash;

    hash[1] = "name";

    return hash;
}

void DeviceNames::setNames(QList<QString> names)
{
    beginResetModel();

    m_names = names;

    endResetModel();
}


DeviceNames::DeviceNames(QObject *parent)
    : QAbstractListModel{parent}
{

}
