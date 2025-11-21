#ifndef DEFINE_H
#define DEFINE_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QDateTime>
#include <QPointF>

struct _IO_Data
{
    int id;         // io_id
    int welder_id;  // 焊接id
//    int type;       // 输入输出
    int pin;        // pin
    int available;  // 有效的  0:off  1:on
    int signal;     // 信号    0:alarm  1:reset 2:not_definite
};

// 良率趋势数据结构
struct _Yield_TrendData
{
    // 开始时间
    QString startTime;
    // 结束时间
    QString endTime;
    QList<QPointF> points;
    _Yield_TrendData& operator=(const _Yield_TrendData& other){
        this->points.clear();
        this->startTime = other.startTime;
        this->endTime   = other.endTime;
//        this->points    = other.points;
        for(int i = 0; i < other.points.count(); ++i)
            this->points.push_back(other.points.at(i));

        return *this;
    }
};

struct DateTimeData
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

struct IO_STATUS
{
    bool IOResetStatus;
};

#endif // DEFINE_H
