#ifndef SYSTEMCLOCK_H
#define SYSTEMCLOCK_H

#include <QObject>

class SystemClock : public QObject
{
    Q_OBJECT
public:
    struct DATE_TIME
    {
        unsigned short Year;
        unsigned short Month;
        unsigned short Day;
        unsigned short Hour;
        unsigned short Minute;
        unsigned short Second;
    };
    static SystemClock*   GetInstance ();
    int SetSystemClock(const void *_datetime);
    int SyncSystemClock();
private:
    explicit SystemClock(QObject *parent = nullptr);
    static SystemClock* _objClock;


signals:
};

#endif // SYSTEMCLOCK_H
