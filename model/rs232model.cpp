#include "rs232model.h"

RS232Model* RS232Model::m_ptrInstance = nullptr;
RS232Model *RS232Model::getInstance()
{
    if(m_ptrInstance == nullptr)
        m_ptrInstance = new RS232Model();
    return m_ptrInstance;
}

RS232Model::RS232Model(QObject *parent)
    : QAbstractListModel{parent}
{
    m_listComPort.append({{"key", "COM1"}, {"value", 0}});
    m_listComPort.append({{"key", "COM2"}, {"value", 1}});

}

int RS232Model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listComPort.size();
}

QVariant RS232Model::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if (!index.isValid() || index.row() >= m_listComPort.count())
        return QVariant();

    const auto &item = m_listComPort.at(index.row());
    if (role == KeyRole)
        return item["key"];
    else if (role == ValueRole)
        return item["value"];

    return QVariant();
}

QHash<int, QByteArray> RS232Model::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[KeyRole] = "key";
    roles[ValueRole] = "value";
    return roles;
}

QVariant RS232Model::get(int index) const
{
    if (index < 0 || index >= m_listComPort.count())
        return QVariant();
    
    // Return a QVariantMap that QML can access with .key and .value
    QVariantMap result;
    result["key"] = m_listComPort.at(index)["key"];
    result["value"] = m_listComPort.at(index)["value"];
    return result;
}

