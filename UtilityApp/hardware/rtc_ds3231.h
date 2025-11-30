#ifndef RTC_DS3231_H
#define RTC_DS3231_H

#include <QObject>
#include <QMutex>
#include <QDateTime>
class RTC_DS3231 : public QObject
{
    Q_OBJECT
public:
    static RTC_DS3231*   GetInstance();
    int SetTime(const QDateTime &datetime);
    int GetTime(QDateTime &datetime) const;
    ~RTC_DS3231();
private:
    struct TIME_BUFFER
    {
        unsigned char RegAddr;
        unsigned char Second;
        unsigned char Minute;
        unsigned char Hour;
        unsigned char Weekdays;
        unsigned char Day;
        unsigned char Month;
        unsigned char Year;
    };
    static RTC_DS3231* _rtc;
    static QMutex  m_Mutex;
    bool m_IsBoardAvaiable;
    explicit RTC_DS3231(QObject *parent = nullptr);
signals:
};

#endif // RTC_DS3231_H
