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

    Q_INVOKABLE static QString displayValue(int rawValue, double scale = 1.0, int decimals = 0);

private:
    explicit UtilityFunction(QObject *parent = nullptr);

    UtilityFunction(const UtilityFunction&) = delete;
    UtilityFunction& operator=(const UtilityFunction&) = delete;

signals:
};

#endif // UTILITYFUNCTION_H
