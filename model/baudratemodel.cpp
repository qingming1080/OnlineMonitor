#include "baudratemodel.h"
#include <QSerialPort>

BaudRateModel* BaudRateModel::m_ptrInstance = nullptr;
BaudRateModel *BaudRateModel::getInstance()
{
    if(m_ptrInstance == nullptr)
        m_ptrInstance = new BaudRateModel();
    return m_ptrInstance;
}

BaudRateModel::BaudRateModel(QObject *parent)
    : QAbstractListModel{parent}
{
    // ["2400", "4800", "9600", "19200", "38400", "115200"]
    m_listBaudRate.append({{"key", "2400"}, {"value", QSerialPort::Baud2400}});
    m_listBaudRate.append({{"key", "4800"}, {"value", QSerialPort::Baud4800}});
    m_listBaudRate.append({{"key", "9600"}, {"value", QSerialPort::Baud9600}});
    m_listBaudRate.append({{"key", "19200"}, {"value", QSerialPort::Baud19200}});
    m_listBaudRate.append({{"key", "38400"}, {"value", QSerialPort::Baud38400}});
    m_listBaudRate.append({{"key", "115200"}, {"value", QSerialPort::Baud115200}});
}

int BaudRateModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listBaudRate.size();
}

QVariant BaudRateModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if (!index.isValid() || index.row() >= m_listBaudRate.count())
        return QVariant();

    const auto &item = m_listBaudRate.at(index.row());
    if (role == KeyRole)
        return item["key"];
    else if (role == ValueRole)
        return item["value"];

    return QVariant();
}

QHash<int, QByteArray> BaudRateModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[KeyRole] = "key";
    roles[ValueRole] = "value";
    return roles;
}

QVariant BaudRateModel::get(int index) const
{
    if (index < 0 || index >= m_listBaudRate.count())
        return QVariant();
    
    // Return a QVariantMap that QML can access with .key and .value
    QVariantMap result;
    result["key"] = m_listBaudRate.at(index)["key"];
    result["value"] = m_listBaudRate.at(index)["value"];
    return result;
}
