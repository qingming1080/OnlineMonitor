#include "databitsmodel.h"
#include <QSerialPort>

DataBitsModel* DataBitsModel::m_ptrInstance = nullptr;
DataBitsModel *DataBitsModel::getInstance()
{
    if(m_ptrInstance == nullptr)
        m_ptrInstance = new DataBitsModel();
    return m_ptrInstance;
}

int DataBitsModel::getDataBitsIndex() const
{
    return m_iCurrentDataBitsIndex;
}

void DataBitsModel::setDataBitsIndex(const int &index)
{
    if(m_iCurrentDataBitsIndex != index)
    {
        m_iCurrentDataBitsIndex = index;
        emit notifyDataBitsIndexChanged();
    }
}

int DataBitsModel::indexOfValueRole(const int value) const
{
    for (int i = 0; i < m_listDataBits.size(); ++i) {
        if (m_listDataBits.at(i)["value"].toInt() == value) {
            return i;
        }
    }
    return -1;
}

DataBitsModel::DataBitsModel(QObject *parent)
    : QAbstractListModel{parent}
{
    // ["7bit", "8bit"]
    m_listDataBits.append({{"key", "7bits"}, {"value", QSerialPort::Data7}});
    m_listDataBits.append({{"key", "8bits"}, {"value", QSerialPort::Data8}});
}

int DataBitsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listDataBits.size();
}

QVariant DataBitsModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if (!index.isValid() || index.row() >= m_listDataBits.count())
        return QVariant();

    const auto &item = m_listDataBits.at(index.row());
    if (role == KeyRole)
        return item["key"];
    else if (role == ValueRole)
        return item["value"];

    return QVariant();
}

QHash<int, QByteArray> DataBitsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[KeyRole] = "key";
    roles[ValueRole] = "value";
    return roles;
}

QVariant DataBitsModel::get(int index) const
{
    if (index < 0 || index >= m_listDataBits.count())
        return QVariant();
    
    // Return a QVariantMap that QML can access with .key and .value
    QVariantMap result;
    result["key"] = m_listDataBits.at(index)["key"];
    result["value"] = m_listDataBits.at(index)["value"];
    return result;
}
