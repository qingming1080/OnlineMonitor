#include "timehandler.h"
#include <QDebug>
#include <QProcess>


TimeHandler::TimeHandler(QObject *parent): QObject(parent){

    // 初始化时间数据
    m_lastTimeData = {0, 0, 0, 0, 0, 0};

}


void TimeHandler::setTime(int year, int month, int day, int hour, int minute, int second)
{

    QVector<int> timeData = {year, month, day, hour, minute, second};

    qDebug() << "TimeHandler::setTime triggered, timeData: " << timeData;

    // 验证时间数据是否合法
    if (month < 1 || month > 12 || hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59) {
        qWarning() << "Invalid time data, ignoring...";
        return;
    }

    // 如果时间未改变，不触发信号
    if (timeData == m_lastTimeData) {
        qDebug() << "Time data unchanged, signal not emitted.";
        return;
    }

    m_lastTimeData = timeData;

    // 发射信号
    emit timeChanged(timeData);

    qDebug() << "timeChanged signal 发射.";


}



