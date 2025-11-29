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
