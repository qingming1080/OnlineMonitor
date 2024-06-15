#include "yieldmodel.h"

YieldModel::YieldModel()
{

}

int YieldModel::rowCount(const QModelIndex &parent) const
{
    return m_data.count();
}

QVariant YieldModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= m_data.count())
        return QVariant();

    switch(role){
    case _YIELDMODEL_ROLE::isSelect:
        return m_data.at(row).isSelect;
    case _YIELDMODEL_ROLE::index:
        return m_data.at(row).index;
    case _YIELDMODEL_ROLE::time:
        return m_data.at(row).time;
    case _YIELDMODEL_ROLE::power:
        return m_data.at(row).power;
    case _YIELDMODEL_ROLE::energy:
        return m_data.at(row).energy;
    case _YIELDMODEL_ROLE::date:
        return m_data.at(row).date;
    case _YIELDMODEL_ROLE::pull:
        return m_data.at(row).pull;
    case _YIELDMODEL_ROLE::rest:
        return m_data.at(row).rest;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> YieldModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[_YIELDMODEL_ROLE::isSelect] = "isSelect";
    roles[_YIELDMODEL_ROLE::index]    = "index";
    roles[_YIELDMODEL_ROLE::time]     = "time";
    roles[_YIELDMODEL_ROLE::power]    = "power";
    roles[_YIELDMODEL_ROLE::energy]   = "energy";
    roles[_YIELDMODEL_ROLE::date]     = "date";
    roles[_YIELDMODEL_ROLE::pull]     = "pull";
    roles[_YIELDMODEL_ROLE::rest]     = "rest";

    return roles;
}

bool YieldModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    if(row < 0 || row >= m_data.count())
        return false;

    // 只允许设置 是否选中、拉力、残留度
    switch(role){
    case _YIELDMODEL_ROLE::isSelect:{
        m_data[row].isSelect = value.toBool();
        break;
    }
    case _YIELDMODEL_ROLE::pull:{
        m_data[row].pull = value.toDouble();
        break;
    }
    case _YIELDMODEL_ROLE::rest:{
        m_data[row].rest = value.toDouble();
        break;
    }
    default:
        return false;
    }

    emit dataChanged(index, index, {role});
    return true;
}

void YieldModel::addRow(int row)
{
    beginInsertRows(QModelIndex(), row, row);

    if(row < 0 || row > m_data.size()){
        return;
    }
    else if(row == m_data.size()){
        m_data.push_back(_YieldModel_Data());
    }
    else{
        m_data.insert(row, _YieldModel_Data());
    }

    endInsertRows();
}

void YieldModel::removeRow(int row)
{
    beginRemoveRows(QModelIndex(), row, row);

    if(row < 0 || row >= m_data.size()){
        return;
    }else{
        m_data.removeAt(row);
    }

    endRemoveRows();
}
