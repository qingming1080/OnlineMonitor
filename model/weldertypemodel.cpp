#include "weldertypemodel.h"
#include "deviceinformation.h"
WelderTypeModel* WelderTypeModel::m_ptrInstance = nullptr;
WelderTypeModel *WelderTypeModel::getInstance()
{
    if(m_ptrInstance == nullptr)
        m_ptrInstance = new WelderTypeModel();
    return m_ptrInstance;
}

WelderTypeModel::WelderTypeModel(QObject *parent)
    : QAbstractListModel{parent}
{
	//"L20-VG", "L20-TS", "20DP", "20MA"
    m_listWelderTypes.append({{"key", "L20-VG"}, {"value", DeviceInfoEnum::L20_VG}});
    m_listWelderTypes.append({{"key", "L20-TS"}, {"value", DeviceInfoEnum::L20_TS}});
    m_listWelderTypes.append({{"key", "2000XC"}, {"value", DeviceInfoEnum::BRANSON_2000XC}});
}

int WelderTypeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listWelderTypes.size();
}

QVariant WelderTypeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if (!index.isValid() || index.row() >= m_listWelderTypes.count())
        return QVariant();

    const auto &item = m_listWelderTypes.at(index.row());
    if (role == KeyRole)
        return item["key"];
    else if (role == ValueRole)
        return item["value"];

    return QVariant();
}

QHash<int, QByteArray> WelderTypeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[KeyRole] = "key";
    roles[ValueRole] = "value";
    return roles;
}

QVariant WelderTypeModel::get(int index) const
{
    if (index < 0 || index >= m_listWelderTypes.count())
        return QVariant();
    
    // Return a QVariantMap that QML can access with .key and .value
    QVariantMap result;
    result["key"] = m_listWelderTypes.at(index)["key"];
    result["value"] = m_listWelderTypes.at(index)["value"];
    return result;
}
int WelderTypeModel::getWelderTypeIndex() const
{
    return m_iCurrentWelderTypeIndex;
}

void WelderTypeModel::setWelderTypeIndex(const int &index)
{
    if(m_iCurrentWelderTypeIndex != index)
    {
        m_iCurrentWelderTypeIndex = index;
        emit notifyWelderTypeIndexChanged();
    }
}

int WelderTypeModel::indexOfValueRole(const int value) const
{
    for (int i = 0; i < m_listWelderTypes.size(); ++i) {
        if (m_listWelderTypes.at(i)["value"].toInt() == value) {
            return i;
        }
    }
    return 0;

}

