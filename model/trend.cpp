#include "trend.h"
#include <QTimer>
#include "DataBase/databasemanager.h"
#include <QDateTime>

#include "signalmanager.h"
#include <QDebug>
#include <QElapsedTimer>
#include "log/localrecord.h"
#include "devicemanager.h"
Trend::Trend(int welderID, QObject *parent)
    : QObject{parent}, m_welderID(welderID)
{
    QElapsedTimer timer;
    timer.start();

    init();

    QString text = QString("%1号设备_Trend_初始化耗时:%2ms").arg(welderID).arg(timer.elapsed());
    emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), text);
}

void Trend::upYieldData()
{
    QElapsedTimer timer;
    timer.start();

    if(m_yieldType == 0)
        m_yieldData = DataBaseManager::getInstance()->getYieldTrendData(0-60*60, m_welderID);  // 一个小时 60s*60m
    else if(m_yieldType == 1)
        m_yieldData = DataBaseManager::getInstance()->getYieldTrendData(0-60*60*24, m_welderID);   // 一天  60s*60m*24h
    else if(m_yieldType == 2)
        m_yieldData = DataBaseManager::getInstance()->getYieldTrendData(0-60*60*24*7, m_welderID); // 七天
    else if(m_yieldType == 3)
        m_yieldData = DataBaseManager::getInstance()->getYieldTrendData(0-60*60*24*30, m_welderID); // 三十天

    setYieldTrendData();

    QString text = QString("%1号设备_Trend_良率趋势图刷新耗时:%2ms").arg(m_welderID).arg(timer.elapsed());
    emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), text);
}

void Trend::upWeldData()
{
    if(m_pFrontSeries){
        m_pFrontSeries->replace(m_frontData);
    }
    if(m_pBackSeries){
        m_pBackSeries->replace(m_backData);
    }
    if(m_pTimeSeries){
        m_pTimeSeries->replace(m_timeData);
    }
    if(m_pPowerSeries){
        m_pPowerSeries->replace(m_powerData);
    }
}


void Trend::setWeldTrendData(_Weld_TrendData result)
{
    m_idMaxX = result.id_X_Max;
    m_idMinX = result.id_X_Min;
    emit idMaxXChanged();
    emit idMinXChanged();

    m_beforeMaxY = result.before_Y_Max;
    m_beforeMinY = result.before_Y_Min;
    emit beforeMaxYChanged();
    emit beforeMinYChanged();

    m_afterMaxY = result.after_Y_Max;
    m_afterMinY = result.after_Y_Min;
    emit afterMaxYChanged();
    emit afterMinYChanged();

    m_timeMaxY = result.time_Y_Max.toDouble();
    m_timeMinY = result.time_Y_Min.toDouble();
    emit timeMaxYChanged();
    emit timeMinYChanged();

    m_powerMaxY = result.power_Y_Max;
    m_powerMinY = result.power_Y_Min;
    emit powerMaxYChanged();
    emit powerMinYChanged();
}

void Trend::setYieldTrendData()
{
    m_startTime = m_yieldData.startTime;
    m_endTime   = m_yieldData.endTime;
    emit startTimeChanged();
    emit endTimeChanged();
    emit SignalManager::getInstance()->changeYieldTrendData();
    emit signalYieldTrendChanged();

    if(m_pYieldSeries)
    {
        m_pYieldSeries->replace(m_yieldData.points);
        qDebug() << "I_WANT_TEST 刷新折线" << m_pYieldSeries << m_yieldData.points.count() << m_startTime << m_endTime;
    }
}

QString Trend::endTime() const
{
    return m_endTime;
}

void Trend::setEndTime(const QString &newEndTime)
{
    if (m_endTime == newEndTime)
        return;
    m_endTime = newEndTime;
    emit endTimeChanged();
}

void Trend::setYieldSeries(QAbstractSeries *series)
{
    m_pYieldSeries = static_cast<QXYSeries*>(series);
    setYieldTrendData();

    qDebug() << QString("I_WANT_TEST 设备%1 设置折线").arg(m_welderID) << m_pYieldSeries;
}

void Trend::setFrontSeries(QAbstractSeries *series)
{
    m_pFrontSeries = static_cast<QXYSeries*>(series);
    if(m_pFrontSeries)
        m_pFrontSeries->replace(m_frontData);
    qDebug() << QString("I_WANT_TEST 设备%1 焊前高度").arg(m_welderID) << m_pFrontSeries;
}

void Trend::setBackSeries(QAbstractSeries *series)
{
    m_pBackSeries = static_cast<QXYSeries*>(series);
    if(m_pBackSeries)
        m_pBackSeries->replace(m_backData);
}

void Trend::setTimeSeries(QAbstractSeries *series)
{
    m_pTimeSeries = static_cast<QXYSeries*>(series);
    if(m_pTimeSeries)
        m_pTimeSeries->replace(m_timeData);
}

void Trend::setPowerSeries(QAbstractSeries *series)
{
    m_pPowerSeries = static_cast<QXYSeries*>(series);
    if(m_pPowerSeries)
        m_pPowerSeries->replace(m_powerData);
}

QString Trend::startTime() const
{
    return m_startTime;
}

void Trend::setStartTime(const QString &newStartTime)
{
    if (m_startTime == newStartTime)
        return;
    m_startTime = newStartTime;
    emit startTimeChanged();
}

void Trend::init()
{
    QElapsedTimer tm;
    tm.start();


    // 良率趋势刷新
    m_yieldTimer = new QTimer;
    connect(m_yieldTimer, &QTimer::timeout, this, &Trend::upYieldData);
    m_yieldTimer->start(1000*60);
    upYieldData();

    // m_weldTimer = new QTimer(this);
    // connect(m_weldTimer, &QTimer::timeout, this, &Trend::upWeldData);
    // m_weldTimer->start(1000 * 1);  // 每2秒刷新一次焊接数据
}

int Trend::yieldType() const
{
    return m_yieldType;
}

void Trend::setYieldType(int newYieldType)
{
    if (m_yieldType == newYieldType)
        return;
    m_yieldType = newYieldType;
    emit yieldTypeChanged();
    emit DeviceManager::getInstance()->upDateBtns();

    m_endTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    if(m_yieldType == 0){
        QDateTime time = QDateTime::currentDateTime().addSecs(-3600);
        m_startTime = time.toString("yyyy-MM-dd hh:mm:ss");
    }
    else if(m_yieldType == 1){
        QDateTime time = QDateTime::currentDateTime().addDays(-1);
        m_startTime = time.toString("yyyy-MM-dd hh:mm:ss");
    }
    else if(m_yieldType == 2){
        QDateTime time = QDateTime::currentDateTime().addDays(-7);
        m_startTime = time.toString("yyyy-MM-dd hh:mm:ss");
    }
    else if(m_yieldType == 3){
        QDateTime time = QDateTime::currentDateTime().addDays(-30);
        m_startTime = time.toString("yyyy-MM-dd hh:mm:ss");
    }

    emit startTimeChanged();
    emit endTimeChanged();
    upYieldData();
}

int Trend::powerMinY() const
{
    return m_powerMinY;
}

void Trend::setPowerMinY(int newPowerMinY)
{
    if (m_powerMinY == newPowerMinY)
        return;
    m_powerMinY = newPowerMinY;
    emit powerMinYChanged();
}

int Trend::powerMaxY() const
{
    return m_powerMaxY;
}

void Trend::setPowerMaxY(int newPowerMaxY)
{
    if (m_powerMaxY == newPowerMaxY)
        return;
    m_powerMaxY = newPowerMaxY;
    emit powerMaxYChanged();
}

double Trend::timeMinY() const
{
    return m_timeMinY;
}

void Trend::setTimeMinY(double newTimeMinY)
{
    if (qFuzzyCompare(m_timeMinY, newTimeMinY))
        return;
    m_timeMinY = newTimeMinY;
    emit timeMinYChanged();
}

double Trend::timeMaxY() const
{
    return m_timeMaxY;
}

void Trend::setTimeMaxY(double newTimeMaxY)
{
    if (qFuzzyCompare(m_timeMaxY, newTimeMaxY))
        return;
    m_timeMaxY = newTimeMaxY;
    emit timeMaxYChanged();
}

int Trend::afterMinY() const
{
    return m_afterMinY;
}

void Trend::setAfterMinY(int newAfterMinY)
{
    if (m_afterMinY == newAfterMinY)
        return;
    m_afterMinY = newAfterMinY;
    emit afterMinYChanged();
}

int Trend::afterMaxY() const
{
    return m_afterMaxY;
}

void Trend::setAfterMaxY(int newAfterMaxY)
{
    if (m_afterMaxY == newAfterMaxY)
        return;
    m_afterMaxY = newAfterMaxY;
    emit afterMaxYChanged();
}

int Trend::beforeMinY() const
{
    return m_beforeMinY;
}

void Trend::setBeforeMinY(int newBeforeMinY)
{
    if (m_beforeMinY == newBeforeMinY)
        return;
    m_beforeMinY = newBeforeMinY;
    emit beforeMinYChanged();
}

int Trend::beforeMaxY() const
{
    return m_beforeMaxY;
}

void Trend::setBeforeMaxY(int newBeforeMaxY)
{
    if (m_beforeMaxY == newBeforeMaxY)
        return;
    m_beforeMaxY = newBeforeMaxY;
    emit beforeMaxYChanged();
}

int Trend::idMaxX() const
{
    return m_idMaxX;
}

void Trend::setIdMaxX(int newIdMaxX)
{
    if (m_idMaxX == newIdMaxX)
        return;
    m_idMaxX = newIdMaxX;
    emit idMaxXChanged();
}

int Trend::idMinX() const
{
    return m_idMinX;
}

void Trend::setIdMinX(int newIdMinX)
{
    if (m_idMinX == newIdMinX)
        return;
    m_idMinX = newIdMinX;
    emit idMinXChanged();
}
