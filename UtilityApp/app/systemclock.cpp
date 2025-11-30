#include "systemclock.h"
#include "../hardware/rtc_ds3231.h"
#include "../definition.h"
#include <QProcess>
#include <QDebug>
#include <QStringList>
#include <QDateTime>
SystemClock* SystemClock::_objClock = nullptr;
SystemClock *SystemClock::GetInstance()
{
    return (_objClock != nullptr) ? _objClock : (_objClock = new SystemClock());
}

int SystemClock::SetSystemClock(const void *_datetime)
{
    if(_datetime == nullptr)
        return ERROR;
    RTC_DS3231* _objRtc = RTC_DS3231::GetInstance();
    const SystemClock::DATE_TIME* _DateTime = reinterpret_cast<const SystemClock::DATE_TIME*>(_datetime);
    QDate date(_DateTime->Year, _DateTime->Month, _DateTime->Day);
    QTime time(_DateTime->Hour, _DateTime->Minute, _DateTime->Second);
    QDateTime DateTime(date, time);
    qDebug() << "Set Time: " << DateTime.toString("yyyy-MM-dd hh:mm:ss");
    _objRtc->SetTime(DateTime);
    return OK;
}

int SystemClock::SyncSystemClock()
{
    RTC_DS3231* _objRtc = RTC_DS3231::GetInstance();
    QDateTime currentTime;
    int iResult = ERROR;
    if(_objRtc->GetTime(currentTime) != ERROR)
    {
        QString strTimeStamp = currentTime.toString("yyyy-MM-dd hh:mm:ss");
        qDebug() << "current Time: " << strTimeStamp;
#ifdef RASPBERRY
        QString cmd = QString("sudo date -s %1%2%3").arg('"').arg(strTimeStamp).arg('"');
        cmd += "\n";
        QProcess process;
        process.setProcessChannelMode(QProcess::MergedChannels);
        QStringList cmdList;
        process.start("bash", cmdList);
        if(!process.waitForStarted())
        {
            qDebug() << "Failed to start process!";
        }

        process.write(cmd.toUtf8());
        process.waitForBytesWritten();

        process.closeWriteChannel();
        process.waitForFinished();

        QString output = process.readAll();
        qDebug() << "system time: " << output;
#endif
        iResult = OK;
    }
    return iResult;
}

SystemClock::SystemClock(QObject *parent)
    : QObject{parent}
{}
