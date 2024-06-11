#include "yidldtrend.h"

YidldTrend* YidldTrend::s_pYidldTrend = nullptr;

YidldTrend *YidldTrend::getInstance()
{
    if(s_pYidldTrend == nullptr)
        s_pYidldTrend = new YidldTrend();

    return s_pYidldTrend;
}

int YidldTrend::rowCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant YidldTrend::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

QHash<int, QByteArray> YidldTrend::roleNames() const
{
    return QHash<int, QByteArray>();
}

YidldTrend::YidldTrend()
{

}
