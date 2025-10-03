#ifndef TIMEHANDLER_H
#define TIMEHANDLER_H

#include <QObject>
#include <QDateTime>


class TimeHandler : public QObject
{
    Q_OBJECT

public:

    explicit TimeHandler( QObject *parent = nullptr);


    Q_INVOKABLE void setTime(const int year, const int month, const int day, const int hour, const int minute, const int second);

signals:

     void timeChanged(const QVector<int>& timeData);


private:

    // 用于存储上一次的时间数据
     QVector<int> m_lastTimeData;

};

#endif // TIMEHANDLER_H
