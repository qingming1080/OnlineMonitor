#include "paritymodel.h"
#include <QSerialPort>

ParityModel* ParityModel::m_ptrInstance = nullptr;
ParityModel *ParityModel::getInstance()
{
    if(m_ptrInstance == nullptr)
        m_ptrInstance = new ParityModel();
    return m_ptrInstance;
}

ParityModel::ParityModel(QObject *parent)
    : QAbstractListModel{parent}
{
    // ["None", "Odd", "Even"]
    m_listParityBits.append({{"key", "None"},   {"value", QSerialPort::NoParity}});
    m_listParityBits.append({{"key", "Odd"},    {"value", QSerialPort::OddParity}});
    m_listParityBits.append({{"key", "Even"},   {"value", QSerialPort::EvenParity}});
}

int ParityModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listParityBits.size();
}

QVariant ParityModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if (!index.isValid() || index.row() >= m_listParityBits.count())
        return QVariant();

    const auto &item = m_listParityBits.at(index.row());
    if (role == KeyRole)
        return item["key"];
    else if (role == ValueRole)
        return item["value"];

    return QVariant();
}

QHash<int, QByteArray> ParityModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[KeyRole] = "key";
    roles[ValueRole] = "value";
    return roles;
}

QVariant ParityModel::get(int index) const
{
    if (index < 0 || index >= m_listParityBits.count())
        return QVariant();
    
    // Return a QVariantMap that QML can access with .key and .value
    QVariantMap result;
    result["key"]   = m_listParityBits.at(index)["key"];
    result["value"] = m_listParityBits.at(index)["value"];
    return result;
}
