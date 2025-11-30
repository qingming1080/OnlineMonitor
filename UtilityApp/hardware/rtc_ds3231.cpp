#include "rtc_ds3231.h"
#include "board_cm3.h"
#ifdef RASPBERRY
#include <bcm2835.h>
#endif
#include "definition.h"
#include <QDebug>
RTC_DS3231* RTC_DS3231::_rtc = nullptr;
QMutex  RTC_DS3231::m_Mutex;
RTC_DS3231 *RTC_DS3231::GetInstance()
{
    m_Mutex.lock();
    if(_rtc == nullptr)
        _rtc = new RTC_DS3231();
    m_Mutex.unlock();
    return _rtc;
}

int RTC_DS3231::SetTime(const QDateTime &datetime)
{
    if(m_IsBoardAvaiable == false)
        return ERROR;
    m_Mutex.lock();
    TIME_BUFFER timeBuff;
    timeBuff.RegAddr = 0x00;
    QDate date = datetime.date();
    QTime time = datetime.time();
    int tmp = date.day();
    timeBuff.Day = ((tmp / 10) * 16 + (tmp % 10)) & 0x3f;
    tmp = date.month();
    timeBuff.Month = ((tmp / 10) * 16 + (tmp % 10)) & 0x1F;
    tmp = (date.year() % 2000);
    timeBuff.Year = ((tmp / 10) * 16 + (tmp % 10));
    tmp = date.dayOfWeek();
    timeBuff.Weekdays = ((tmp / 10) * 16 + (tmp % 10)) & 0x07;
    tmp = time.second();
    timeBuff.Second = ((tmp / 10) * 16 + (tmp % 10)) & 0x7F;
    tmp = time.minute();
    timeBuff.Minute = ((tmp / 10) * 16 + (tmp % 10)) & 0x7F;
    tmp = time.hour();
    timeBuff.Hour = ((tmp / 10) * 16 + (tmp % 10)) & 0x3F;
#ifdef RASPBERRY
    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(0x68);
    bcm2835_i2c_set_baudrate(10000);
    bcm2835_i2c_write(reinterpret_cast<const char*>(&timeBuff), 8);
    bcm2835_i2c_end();
#endif
    m_Mutex.unlock();
    return OK;
}

int RTC_DS3231::GetTime(QDateTime &datetime) const
{
    if(m_IsBoardAvaiable == false)
        return ERROR;
    m_Mutex.lock();
    TIME_BUFFER timeBuff;
    timeBuff.RegAddr = 0x00;
#ifdef RASPBERRY
    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(0x68);
    bcm2835_i2c_set_baudrate(10000);
    bcm2835_i2c_write_read_rs(reinterpret_cast<char*>(&timeBuff.RegAddr), 1, reinterpret_cast<char*>(&timeBuff.Second), 7);
    bcm2835_i2c_end();
#else
    timeBuff.Year = 0x00;
    timeBuff.Month = 0x00;
    timeBuff.Day = 0x00;
    timeBuff.Hour = 0x00;
    timeBuff.Minute = 0x00;
    timeBuff.Second = 0x00;
    timeBuff.Weekdays = 0x00;
#endif
    int year, month, day;
    year = (timeBuff.Year >> 4) * 10 + (timeBuff.Year & 0x0F) + 2000;
    month = (timeBuff.Month >> 4) * 10 + (timeBuff.Month & 0x0F);
    day = (timeBuff.Day >> 4) * 10 + (timeBuff.Day & 0x0F);
    QDate date(year, month, day);

    int second, minute, hour;
    hour = (timeBuff.Hour >> 4) * 10 + (timeBuff.Hour & 0x0F);
    minute = (timeBuff.Minute >> 4) * 10 + (timeBuff.Minute & 0x0F);
    second = (timeBuff.Second >> 4) * 10 + (timeBuff.Second & 0x0F);
    QTime time(hour, minute, second);
    datetime.setDate(date);
    datetime.setTime(time);
    m_Mutex.unlock();
    return OK;
}

RTC_DS3231::~RTC_DS3231()
{

}

RTC_DS3231::RTC_DS3231(QObject *parent)
    : QObject{parent}
{
    m_IsBoardAvaiable = Board_CM3::GetInstance()->GetBoardStatus();
    if(m_IsBoardAvaiable == false)
    {
        return;
    }

    qDebug() << "DS3231 is ready...";
}
