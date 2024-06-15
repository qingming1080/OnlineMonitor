#include "weldtrend.h"

WeldTrend::WeldTrend(QObject *parent)
    : QAbstractListModel{parent}
{

}

int WeldTrend::rowCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant WeldTrend::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

QHash<int, QByteArray> WeldTrend::roleNames() const
{
    return QHash<int, QByteArray>();
}
