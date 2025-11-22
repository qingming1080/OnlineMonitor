#include "trend.h"
#include <QTimer>
#include "DataBase/databasemanager.h"
#include <QDateTime>

#include "signalmanager.h"
#include <QDebug>
#include <QElapsedTimer>
// #include "log/localrecord.h"
// #include "devicemanager.h"
#include <QPointF>
Trend::Trend(int welderID, QObject *parent)
    : QObject{parent}, m_WelderID(welderID)
{
    if(DataBaseManager::getInstance()->getModelRecord(m_WelderID, m_DBModel) == false)
    {
        m_DBModel = DataBaseManager::DB_MODEL();
    }
    init();
}

void Trend::upYieldData()
{
    // QElapsedTimer timer;
    // timer.start();

    if(m_yieldType == 0)
        m_yieldData = DataBaseManager::getInstance()->getYieldTrendData(0-60*60, m_WelderID);  // 一个小时 60s*60m
    else if(m_yieldType == 1)
        m_yieldData = DataBaseManager::getInstance()->getYieldTrendData(0-60*60*24, m_WelderID);   // 一天  60s*60m*24h
    else if(m_yieldType == 2)
        m_yieldData = DataBaseManager::getInstance()->getYieldTrendData(0-60*60*24*7, m_WelderID); // 七天
    else if(m_yieldType == 3)
        m_yieldData = DataBaseManager::getInstance()->getYieldTrendData(0-60*60*24*30, m_WelderID); // 三十天

    setYieldTrendData();

    // QString text = QString("%1号设备_Trend_良率趋势图刷新耗时:%2ms").arg(m_welderID).arg(timer.elapsed());
    // emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), text);
}

void Trend::upWeldData()
{
    if(m_pPreheightSeries){
        m_pPreheightSeries->replace(m_PreheightData);
    }
    if(m_pPostHeightSeries){
        m_pPostHeightSeries->replace(m_PostHeightData);
    }
    if(m_pWeldTimeSeries){
        m_pWeldTimeSeries->replace(m_WeldTimeData);
    }
    if(m_pPeakPowerSeries){
        m_pPeakPowerSeries->replace(m_PeakPowerData);
    }
}

void Trend::setWeldTrendData(WELD_TREND result)
{
    setCountMaxX(result.Count_X_Max);
    setCountMinX(result.Count_X_Min);

    setPreheightMaxY(result.Preheight_Y_Max);
    setPreheightMinY(result.Preheight_Y_Min);

    setPostHeightMaxY(result.PostHeight_Y_Max);
    setPostHeightMinY(result.PostHeight_Y_Min);

    setWeldTimeMaxY(result.WeldTime_Y_Max);
    setWeldTimeMinY(result.WeldTime_Y_Min);

    setPeakPowerMaxY(result.PeakPower_Y_Max);
    setPeakPowerMinY(result.PeakPower_Y_Min);
}

void Trend::AppendWeldPoint(const int cycleCount, const int power, const int time, const int preHeight, const int postHeight)
{
    double preheightDouble  = preHeight / 100.0;
    double postHeightDouble = postHeight / 100.0;
    double timeDouble       = time / 100.0;
    double powerDouble      = static_cast<double>(power);

    auto appendWithLimit = [&](QVector<QPointF>& vec, int xCount, double yValue)
    {
        vec.append(QPointF(xCount, yValue));
        if (vec.size() > X_AXIS_MAX)
            vec.removeFirst();
    };

    appendWithLimit(m_PreheightData,    cycleCount, preheightDouble);
    appendWithLimit(m_PostHeightData,   cycleCount, postHeightDouble);
    appendWithLimit(m_WeldTimeData,     cycleCount, timeDouble);
    appendWithLimit(m_PeakPowerData,    cycleCount, powerDouble);

    int xMin = m_WeldTimeData.at(0).x();
    int size = m_WeldTimeData.size();
    int xMax = m_WeldTimeData.at(size - 1).x();
    setCountMinX(xMin);
    setCountMaxX(xMax);

    auto updateSeries = [&](QXYSeries* series, int xCount, double yValue)
    {
        if (series)
        {
            series->append(xCount, yValue);
            if (series->count() > X_AXIS_MAX)
                series->remove(0);
        }
    };

    updateSeries(m_pPreheightSeries,    cycleCount, preheightDouble);
    updateSeries(m_pPostHeightSeries,   cycleCount, postHeightDouble);
    updateSeries(m_pWeldTimeSeries,     cycleCount, timeDouble);
    updateSeries(m_pPeakPowerSeries,    cycleCount, powerDouble);

    updateYAxisRanges();
}

void Trend::updateYAxisRanges()
{
    // auto calcRange = [](const QVector<QPointF>& data, double& minVal, double& maxVal) {
    //     if (data.isEmpty()) return;
    //     minVal = maxVal = data.first().y();
    //     for (const QPointF& p : data)
    //     {
    //         minVal = qMin(minVal, p.y());
    //         maxVal = qMax(maxVal, p.y());
    //     }
    // };

    double PreheightMinY, PreheightMaxY;
    double PostHeightMinY,  PostHeightMaxY;
    double WeldTimeMinY,   WeldTimeMaxY;
    double PeakPowerMinY,  PeakPowerMaxY;

    // calcRange(m_PreheightData, PreheightMinY, PreheightMaxY);
    // calcRange(m_PostHeightData,  PostHeightMinY,  PostHeightMaxY);
    // calcRange(m_WeldTimeData,  WeldTimeMinY,   WeldTimeMaxY);
    // calcRange(m_PeakPowerData, PeakPowerMinY,  PeakPowerMaxY);

    PreheightMaxY = m_DBModel.Preheight.Alpha + 5 * m_DBModel.Preheight.Beta;
    PreheightMaxY /= 100;
    PreheightMinY = qMax(0.0, (m_DBModel.Preheight.Alpha - 5 * m_DBModel.Preheight.Beta));
    PreheightMinY /= 100;
    setPreheightMaxY(PreheightMaxY);
    setPreheightMinY(PreheightMinY);

    PostHeightMaxY = m_DBModel.PostHeight.Alpha + 5 * m_DBModel.PostHeight.Beta;
    PostHeightMaxY /= 100;
    PostHeightMinY = qMax(0.0, m_DBModel.PostHeight.Alpha - 5 * m_DBModel.PostHeight.Beta);
    PostHeightMinY /= 100;
    setPostHeightMaxY(PostHeightMaxY);
    setPostHeightMinY(PostHeightMinY);

    WeldTimeMaxY = m_DBModel.WeldTime.Alpha + 5 * m_DBModel.WeldTime.Beta;
    WeldTimeMaxY /= 100;
    WeldTimeMinY = qMax(0.0, m_DBModel.WeldTime.Alpha - 5 * m_DBModel.WeldTime.Beta);
    WeldTimeMinY /= 100;
    setWeldTimeMaxY(WeldTimeMaxY);
    setWeldTimeMinY(WeldTimeMinY);

    PeakPowerMaxY = m_DBModel.PeakPower.Alpha + 5 * m_DBModel.PeakPower.Beta;
    PeakPowerMinY = qMax(0.0, m_DBModel.PeakPower.Alpha - 5 * m_DBModel.PeakPower.Beta);
    setPeakPowerMaxY(PeakPowerMaxY);
    setPeakPowerMinY(PeakPowerMinY);
}

void Trend::SetModel(const DataBaseManager::DB_MODEL &model)
{
    m_DBModel.id = model.id;
    m_DBModel.WelderId = model.WelderId;
    m_DBModel.CreateTime = model.CreateTime;
    m_DBModel.Energy = model.Energy;
    m_DBModel.Amplitude = model.Amplitude;
    m_DBModel.TriggerPressure = model.TriggerPressure;
    m_DBModel.WeldPressure = model.WeldPressure;

    m_DBModel.WeldTime.Alpha = model.WeldTime.Alpha;
    m_DBModel.WeldTime.Beta = model.WeldTime.Beta;
    m_DBModel.PeakPower.Alpha = model.PeakPower.Alpha;
    m_DBModel.PeakPower.Beta = model.PeakPower.Beta;
    m_DBModel.Preheight.Alpha = model.Preheight.Alpha;
    m_DBModel.Preheight.Beta = model.Preheight.Beta;
    m_DBModel.PostHeight.Alpha = model.PostHeight.Alpha;
    m_DBModel.PostHeight.Beta = model.PostHeight.Beta;

    m_DBModel.PeelForce.P00 = model.PeelForce.P00;
    m_DBModel.PeelForce.P10 = model.PeelForce.P10;
    m_DBModel.PeelForce.P01 = model.PeelForce.P01;
    m_DBModel.PeelForce.P20 = model.PeelForce.P20;
    m_DBModel.PeelForce.P11 = model.PeelForce.P11;
    m_DBModel.PeelForce.P02 = model.PeelForce.P02;
    m_DBModel.Residual.P00 = model.Residual.P00;
    m_DBModel.Residual.P10 = model.Residual.P10;
    m_DBModel.Residual.P01 = model.Residual.P01;
    m_DBModel.Residual.P20 = model.Residual.P20;
    m_DBModel.Residual.P11 = model.Residual.P11;
    m_DBModel.Residual.P02 = model.Residual.P02;

    m_DBModel.Centralized.TimeMean = model.Centralized.TimeMean;
    m_DBModel.Centralized.TimeStd = model.Centralized.TimeStd;
    m_DBModel.Centralized.PowerMean = model.Centralized.PowerMean;
    m_DBModel.Centralized.PowerStd = model.Centralized.PowerStd;
    m_DBModel.Centralized.ForceMean = model.Centralized.ForceMean;
    m_DBModel.Centralized.ResidualMean = model.Centralized.ResidualMean;

    m_DBModel.SampleCount = model.SampleCount;
    m_DBModel.BatchCount = model.BatchCount;
    m_DBModel.isAvailable = model.isAvailable;
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
        // m_pYieldSeries->replace(m_yieldData.points);
        // qDebug() << "I_WANT_TEST 刷新折线" << m_pYieldSeries << m_yieldData.points.count() << m_startTime << m_endTime;
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

    // qDebug() << QString("I_WANT_TEST 设备%1 设置折线").arg(m_welderID) << m_pYieldSeries;
}

void Trend::setPreheightSeries(QAbstractSeries *series)
{
    m_pPreheightSeries = static_cast<QXYSeries*>(series);
    if(m_pPreheightSeries)
        m_pPreheightSeries->replace(m_PreheightData);
}

void Trend::setPostHeightSeries(QAbstractSeries *series)
{
    m_pPostHeightSeries = static_cast<QXYSeries*>(series);
    if(m_pPostHeightSeries)
        m_pPostHeightSeries->replace(m_PostHeightData);
}

void Trend::setWeldTimeSeries(QAbstractSeries *series)
{
    m_pWeldTimeSeries = static_cast<QXYSeries*>(series);
    if(m_pWeldTimeSeries)
        m_pWeldTimeSeries->replace(m_WeldTimeData);
}

void Trend::setPeakPowerSeries(QAbstractSeries *series)
{
    m_pPeakPowerSeries = static_cast<QXYSeries*>(series);
    if(m_pPeakPowerSeries)
        m_pPeakPowerSeries->replace(m_PeakPowerData);
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
    // QElapsedTimer tm;
    // tm.start();


    // 良率趋势刷新
    // m_yieldTimer = new QTimer;
    // connect(m_yieldTimer, &QTimer::timeout, this, &Trend::upYieldData);
    // m_yieldTimer->start(1000*60);
    upYieldData();
    setWeldTimeMinY(0.00);
    setWeldTimeMaxY(5.00);
    setPeakPowerMinY(0);
    setPeakPowerMaxY(10000);
    setPreheightMinY(0.00);
    setPreheightMaxY(15.00);
    setPostHeightMinY(0.00);
    setPostHeightMaxY(15.00);
    setCountMinX(0);
    setCountMaxX(X_AXIS_MAX);

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
    // emit DeviceManager::getInstance()->upDateBtns();

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

int Trend::getPeakPowerMinY() const
{
    return m_PeakPowerMinY;
}

void Trend::setPeakPowerMinY(int power)
{
    if (m_PeakPowerMinY == power)
        return;
    m_PeakPowerMinY = power;
    emit notifyPeakPowerMinYChanged();
}

int Trend::getPeakPowerMaxY() const
{
    return m_PeakPowerMaxY;
}

void Trend::setPeakPowerMaxY(int power)
{
    if (m_PeakPowerMaxY == power)
        return;
    m_PeakPowerMaxY = power;
    emit notifyPeakPowerMaxYChanged();
}

float Trend::getWeldTimeMinY() const
{
    return m_WeldTimeMinY;
}

void Trend::setWeldTimeMinY(float time)
{
    if (qFuzzyCompare(m_WeldTimeMinY, time))
        return;
    m_WeldTimeMinY = time;
    emit notifyWeldTimeMinYChanged();
}

float Trend::getWeldTimeMaxY() const
{
    return m_WeldTimeMaxY;
}

void Trend::setWeldTimeMaxY(float time)
{
    if (qFuzzyCompare(m_WeldTimeMaxY, time))
        return;
    m_WeldTimeMaxY = time;
    emit notifyWeldTimeMaxYChanged();
}

float Trend::getPostHeightMinY() const
{
    return m_PostHeightMinY;
}

void Trend::setPostHeightMinY(const float height)
{
    if (m_PostHeightMinY == height)
        return;
    m_PostHeightMinY = height;
    emit notifyPostHeightMinYChanged();
}

float Trend::getPostHeightMaxY() const
{
    return m_PostHeightMaxY;
}

void Trend::setPostHeightMaxY(const float height)
{
    if (m_PostHeightMaxY == height)
        return;
    m_PostHeightMaxY = height;
    emit notifyPostHeightMaxYChanged();
}

float Trend::getPreheightMinY() const
{
    return m_PreheightMinY;
}

void Trend::setPreheightMinY(const float height)
{
    if (m_PreheightMinY == height)
        return;
    m_PreheightMinY = height;
    emit notifyPreheightMinYChanged();
}

float Trend::getPreheightMaxY() const
{
    return m_PreheightMaxY;
}

void Trend::setPreheightMaxY(const float height)
{
    if (m_PreheightMaxY == height)
        return;
    m_PreheightMaxY = height;
    emit notifyPreheightMaxYChanged();
}

int Trend::getCountMaxX() const
{
    return m_CountMaxX;
}

void Trend::setCountMaxX(const int count)
{
    if (m_CountMaxX == count)
        return;
    m_CountMaxX = count;
    emit notifyCountMaxXChanged();
}

int Trend::getCountMinX() const
{
    return m_CountMinX;
}

void Trend::setCountMinX(const int count)
{
    if (m_CountMinX == count)
        return;
    m_CountMinX = count;
    emit notifyCountMinXChanged();
}
