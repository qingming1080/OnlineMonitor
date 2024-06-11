#include "systeminformation.h"
#include <QDateTime>

void SystemInformation::addRow(QDateTime time, QString information)
{
    emit beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data.push_back(_SystemInformation_Data(time.toString("yyyy-MM-dd hh:mm:ss"), information));
    emit endInsertRows();

    /// 向前端发信号
    emit sigAddRow(time.toString("yyyy-MM-dd hh:mm:ss"), information);
}

SystemInformation::SystemInformation()
{

}

int SystemInformation::rowCount(const QModelIndex &parent) const
{
    return m_data.count();
}

QVariant SystemInformation::data(const QModelIndex &index, int role) const
{
    // 避免内存泄露
    int row = index.row();
    if(row < 0 || row >= m_data.size()){
        return QVariant();
    }

    switch(role){
    case SYSTEMINFORMATION_ROLE::_Date:
        return m_data.at(row).dateTime;
    case SYSTEMINFORMATION_ROLE::_Information:
        return m_data.at(row).information;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> SystemInformation::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles.insert(SYSTEMINFORMATION_ROLE::_Date, "dateTime");
    roles.insert(SYSTEMINFORMATION_ROLE::_Information, "information");

    return roles;
}
