#include "stopbitsmodel.h"
#include <QSerialPort>

StopBitsModel* StopBitsModel::m_ptrInstance = nullptr;
StopBitsModel *StopBitsModel::getInstance()
{
    if(m_ptrInstance == nullptr)
        m_ptrInstance = new StopBitsModel();
    return m_ptrInstance;
}

StopBitsModel::StopBitsModel(QObject *parent)
    : QAbstractListModel{parent}
{
    // ["1bit", "1.5bit", "2bit"]
    m_listStopBits.append({{"key", "1bit"}, {"value", QSerialPort::OneStop}});
    m_listStopBits.append({{"key", "1.5bits"}, {"value", QSerialPort::OneAndHalfStop}});
    m_listStopBits.append({{"key", "2bits"}, {"value", QSerialPort::TwoStop}});
}

int StopBitsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listStopBits.size();
}

QVariant StopBitsModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if (!index.isValid() || index.row() >= m_listStopBits.count())
        return QVariant();

    const auto &item = m_listStopBits.at(index.row());
    if (role == KeyRole)
        return item["key"];
    else if (role == ValueRole)
        return item["value"];

    return QVariant();
}

QHash<int, QByteArray> StopBitsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[KeyRole] = "key";
    roles[ValueRole] = "value";
    return roles;
}

QVariant StopBitsModel::get(int index) const
{
    if (index < 0 || index >= m_listStopBits.count())
        return QVariant();
    
    // Return a QVariantMap that QML can access with .key and .value
    QVariantMap result;
    result["key"] = m_listStopBits.at(index)["key"];
    result["value"] = m_listStopBits.at(index)["value"];
    return result;
}
