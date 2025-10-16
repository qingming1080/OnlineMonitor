#ifndef UTILITYFUNCTION_H
#define UTILITYFUNCTION_H

#include <QObject>
#include "define.h"

class UtilityFunction : public QObject
{
    Q_OBJECT
public:
    explicit UtilityFunction(QObject *parent = nullptr);

    static QDateTime buildDateTime(const DateTimeData &data);
    static QString buildDateTimeString(const DateTimeData &data);

signals:
};

#endif // UTILITYFUNCTION_H
