#include "utilityfunction.h"
#include <QDateTime>
#include <QDate>
#include <QTime>

UtilityFunction::UtilityFunction(QObject *parent)
    : QObject{parent}
{

}

QDateTime UtilityFunction::buildDateTime(const DateTimeData &data)
{
    if (!QDate::isValid(data.year, data.month, data.day)) {
        return QDateTime::currentDateTime();
    }
    return QDateTime(
        QDate(data.year, data.month, data.day),
        QTime(data.hour, data.minute, data.second)
        );
}

QString UtilityFunction::buildDateTimeString(const DateTimeData &data)
{
    return buildDateTime(data).toString("yyyy-MM-dd HH:mm:ss");
}

QString UtilityFunction::displayValue(int rawValue, double scale, int decimals){
    return QString::number(rawValue / scale, 'f', decimals);
}


UtilityFunction* UtilityFunction::getInstance()
{
    static UtilityFunction singleton;
    return &singleton;
}

qint64 UtilityFunction::toTimestamp(int year, int month, int day, int hour, int minute, int second)
{
    QDateTime dt(QDate(year, month, day), QTime(hour, minute, second), Qt::UTC);
    return dt.toMSecsSinceEpoch();
}

QString UtilityFunction::timestampToString(int timestamp)
{
    QDateTime dt = QDateTime::fromSecsSinceEpoch(timestamp, Qt::UTC);
    return dt.toString("yyyy-MM-dd HH:mm:ss");
}

Q_INVOKABLE QDateTime UtilityFunction::makeDateTime(int year, int month, int day, int hour, int minute, int second) {
    QDate date(year, month, day);
    QTime time(hour, minute, second);
    return QDateTime(date, time);
}
