#ifndef UTILITYFUNCTION_H
#define UTILITYFUNCTION_H

#include <QObject>
#include "define.h"
#include <QString>

class UtilityFunction : public QObject
{
    Q_OBJECT
public:
    static UtilityFunction* getInstance();

    static QDateTime buildDateTime(const DateTimeData &data);
    static QString buildDateTimeString(const DateTimeData &data);

    qint64 toTimestamp(int year, int month, int day, int hour, int minute, int second);
    Q_INVOKABLE QString timestampToString(int timestamp);
    Q_INVOKABLE QDateTime makeDateTime(int year, int month, int day, int hour, int minute, int second);

    QString RawValueToString(const int rawValue, const double scale = 1.0, const int decimals = 0);
    int     StringToRawValue(const QString displayValue, const double scale = 1.0);

private:
    explicit UtilityFunction(QObject *parent = nullptr);

    UtilityFunction(const UtilityFunction&) = delete;
    UtilityFunction& operator=(const UtilityFunction&) = delete;

signals:
};

#endif // UTILITYFUNCTION_H
