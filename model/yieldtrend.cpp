#include "yieldtrend.h"

YieldTrend::YieldTrend()
{

}


int YieldTrend::rowCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant YieldTrend::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

QHash<int, QByteArray> YieldTrend::roleNames() const
{
    return QHash<int, QByteArray>();
}

