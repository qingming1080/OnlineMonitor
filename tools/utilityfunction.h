#ifndef UTILITYFUNCTION_H
#define UTILITYFUNCTION_H

#include <QObject>
#include "define.h"
#include <QString>

class UtilityFunction : public QObject
{
    Q_OBJECT
public:
    explicit UtilityFunction(QObject *parent = nullptr);

    static QDateTime buildDateTime(const DateTimeData &data);
    static QString buildDateTimeString(const DateTimeData &data);

    static QString displayValue(int rawValue, double scale = 1.0, int decimals = 0);

signals:
};

#endif // UTILITYFUNCTION_H
