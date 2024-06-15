#include "history.h"

History::History(QObject *parent)
    : QAbstractListModel{parent}
{
    m_data.push_back(_History_Data{"Item 1", "1", 1, 1, QmlEnum::PRODUCTSTATE_Excelleng});
    m_data.push_back(_History_Data{"Item 2", "1", 1, 1, QmlEnum::PRODUCTSTATE_Excelleng});
    m_data.push_back(_History_Data{"Item 3", "1", 1, 1, QmlEnum::PRODUCTSTATE_Difference});
    m_data.push_back(_History_Data{"Item 4", "1", 1, 1, QmlEnum::PRODUCTSTATE_Excelleng});
    m_data.push_back(_History_Data{"Item 4", "1", 1, 1, QmlEnum::PRODUCTSTATE_Difference});
}

int History::rowCount(const QModelIndex &parent) const
{
    return m_data.count();
}

QVariant History::data(const QModelIndex &index, int role) const
{
    // 避免内存泄露
    int row = index.row();
    if(row < 0 || row >= m_data.count()){
        return QVariant();
    }

    switch(role){
    case History::_HISTORY_ROLE_name:
        return m_data.at(row).name;
    case History::_HISTORY_ROLE_date:
        return m_data.at(row).date;
    case History::_HISTORY_ROLE_energy:
        return m_data.at(row).energy;
    case History::_HISTORY_ROLE_power:
        return m_data.at(row).power;
    case History::_HISTORY_ROLE_result:
        return m_data.at(row).result;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> History::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles.insert(History::_HISTORY_ROLE_name, "name");
    roles.insert(History::_HISTORY_ROLE_date, "date");
    roles.insert(History::_HISTORY_ROLE_energy, "energy");
    roles.insert(History::_HISTORY_ROLE_power, "power");
    roles.insert(History::_HISTORY_ROLE_result, "result");

    return roles;
}
