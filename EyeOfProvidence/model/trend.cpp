#include "trend.h"
#include <QTimer>
#include "DataBase/databasemanager.h"
#include <QDateTime>
#include "historyenum.h"
#include "yieldstrendenum.h"

#include <QDebug>
#include <QElapsedTimer>
#include <QPointF>
Trend::Trend(int welderID, QObject *parent)
    : QObject{parent}, m_WelderID(welderID)
{
    m_PreheightData.reserve(X_AXIS_MAX);
    m_PostHeightData.reserve(X_AXIS_MAX);
    m_WeldTimeData.reserve(X_AXIS_MAX);
    m_PeakPowerData.reserve(X_AXIS_MAX);
    lastCycleCount = -1;
    if(DataBaseManager::getInstance()->getModelRecord(m_WelderID, m_DBModel) == false)
    {
        m_DBModel = DataBaseManager::DB_MODEL();
    }
    init();
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
    if (lastCycleCount > cycleCount)
    {
        m_PreheightData.clear();
        m_PostHeightData.clear();
        m_WeldTimeData.clear();
        m_PeakPowerData.clear();

        // if (m_pPreheightSeries)    m_pPreheightSeries->clear();
        // if (m_pPostHeightSeries)   m_pPostHeightSeries->clear();
        // if (m_pWeldTimeSeries)     m_pWeldTimeSeries->clear();
        // if (m_pPeakPowerSeries)    m_pPeakPowerSeries->clear();
    }
    lastCycleCount = cycleCount;
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
}

void Trend::AppendProduction(const DataBaseManager::DB_PRODUCTION data)
{
    int duration = ONE_HOUR;
    m_OneHourWeldResultData.append(data);
    qint64 startTime = m_OneHourWeldResultData.first().CreateTime;
    qint64 endTime = m_OneHourWeldResultData.last().CreateTime;
    while(endTime - duration > startTime)
        m_OneHourWeldResultData.pop_front();
    if((QDateTime::currentSecsSinceEpoch() - m_CurrentTimeStamp) > 60)
    {
        setYieldType(YieldsTrendEnum::ONE_HOUR);
        m_CurrentTimeStamp = QDateTime::currentSecsSinceEpoch();
    }
}

void Trend::updateXYAxisRanges()
{

    if (m_WeldTimeData.isEmpty())
    {
        return;
    }

    int xMin = m_WeldTimeData.first().x();
    int xMax = m_WeldTimeData.last().x();
    setCountMinX(xMin);
    setCountMaxX(xMax);

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
    PreheightMaxY *= 1.25;
    PreheightMinY = qMax(0.0, (m_DBModel.Preheight.Alpha - 5 * m_DBModel.Preheight.Beta));
    PreheightMinY /= 100;
    PreheightMinY *= 0.75;
    setPreheightMaxY(PreheightMaxY);
    setPreheightMinY(PreheightMinY);

    PostHeightMaxY = m_DBModel.PostHeight.Alpha + 5 * m_DBModel.PostHeight.Beta;
    PostHeightMaxY /= 100;
    PostHeightMaxY *= 1.25;
    PostHeightMinY = qMax(0.0, m_DBModel.PostHeight.Alpha - 5 * m_DBModel.PostHeight.Beta);
    PostHeightMinY /= 100;
    PostHeightMinY *= 0.75;
    setPostHeightMaxY(PostHeightMaxY);
    setPostHeightMinY(PostHeightMinY);

    WeldTimeMaxY = m_DBModel.WeldTime.Alpha + 5 * m_DBModel.WeldTime.Beta;
    WeldTimeMaxY /= 100;
    WeldTimeMaxY *= 1.25;
    WeldTimeMinY = qMax(0.0, m_DBModel.WeldTime.Alpha - 5 * m_DBModel.WeldTime.Beta);
    WeldTimeMinY /= 100;
    WeldTimeMinY *= 0.75;
    setWeldTimeMaxY(WeldTimeMaxY);
    setWeldTimeMinY(WeldTimeMinY);

    PeakPowerMaxY = m_DBModel.PeakPower.Alpha + 5 * m_DBModel.PeakPower.Beta;
    PeakPowerMaxY *= 1.25;
    PeakPowerMinY = qMax(0.0, m_DBModel.PeakPower.Alpha - 5 * m_DBModel.PeakPower.Beta);
    PeakPowerMinY *= 0.75;
    setPeakPowerMaxY(PeakPowerMaxY);
    setPeakPowerMinY(PeakPowerMinY);
}

void Trend::updateSeries()
{
    if (m_pPreheightSeries == nullptr)
        return;
    if (m_pPostHeightSeries == nullptr)
        return;
    if (m_pWeldTimeSeries == nullptr)
        return;
    if (m_pPeakPowerSeries == nullptr)
        return;

    m_pPreheightSeries->replace(m_PreheightData);
    m_pPostHeightSeries->replace(m_PostHeightData);
    m_pWeldTimeSeries->replace(m_WeldTimeData);
    m_pPeakPowerSeries->replace(m_PeakPowerData);
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
    if(m_pYieldSeries)
    {
        m_pYieldSeries->replace(m_YieldData.points);
        qDebug() << "I_WANT_TEST 刷新折线" << m_pYieldSeries << m_YieldData.points.count() << m_StartTime << m_EndTime;
    }
}

void Trend::setYieldSeries(QAbstractSeries *series)
{
    m_pYieldSeries = static_cast<QXYSeries*>(series);
    if(m_pYieldSeries)
        m_pYieldSeries->replace(m_YieldData.points);
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

void Trend::init()
{

    // 良率趋势刷新
    // m_yieldTimer = new QTimer;
    // connect(m_yieldTimer, &QTimer::timeout, this, &Trend::upYieldData);
    // m_yieldTimer->start(1000*60);
    // upYieldData(YieldsTrendEnum::ONE_HOUR);
    m_OneHourWeldResultData.clear();
    m_CurrentTimeStamp = QDateTime::currentSecsSinceEpoch();
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

void Trend::upYieldData(const int duration)
{
    DataBaseManager::DB_PRODUCTION production;
    QList<DataBaseManager::DB_PRODUCTION> productionList;
    qint64 startTime = -1;
    qint64 endTime = -1;
    if(DataBaseManager::getInstance()->getProductionLastRecord(m_WelderID, production) == false)
        return;
    switch(m_YieldType)
    {
    case YieldsTrendEnum::ONE_HOUR:
        productionList = m_OneHourWeldResultData;
        break;
    case YieldsTrendEnum::TWENTY_FOUR_HOURS:
    case YieldsTrendEnum::SEVEN_DAYS:
    case YieldsTrendEnum::THIRTY_DAYS:
        if(DataBaseManager::getInstance()->getProductionLastRecord(m_WelderID, production) == true)
        {
            startTime = production.CreateTime - duration;
            endTime = production.CreateTime;
            if(startTime > 0)
            {
                DataBaseManager::getInstance()->getProductionRecords(m_WelderID, startTime, endTime, productionList);
            }
        }
        break;
    default:
        // duration = ONE_HOUR; // 一个小时 60s*60m
        productionList = m_OneHourWeldResultData;
        break;
    }

    if (productionList.isEmpty())
        return;
    // qDebug() << "StartTime: " << QDateTime::fromSecsSinceEpoch(startTime).toString("yyyy-MM-dd hh:mm:ss");
    // qDebug() << "End Time: " << QDateTime::fromSecsSinceEpoch(endTime).toString("yyyy-MM-dd hh:mm:ss");
    int SecondStep = duration / 60; // seconds per timeslot

    QList<SLOT_DATA> resultList;     // 60个时间段每个时间段的生产总数列表

    // Ensure records are in ascending time order
    std::sort(productionList.begin(), productionList.end(), [](const DataBaseManager::DB_PRODUCTION &a, const DataBaseManager::DB_PRODUCTION &b){
        return a.CreateTime < b.CreateTime;
    });

    qint64 slotStart = static_cast<qint64>(productionList.at(0).CreateTime);
    qint64 slotEnd = slotStart + SecondStep;
    SLOT_DATA trendData;
    trendData.TimeStamp = slotStart;
    trendData.TotalNumber = 0;
    trendData.GoodNumber = 0;
    for (int i = 0; i < productionList.size(); ++i)
    {
        qint64 ts = static_cast<qint64>(productionList.at(i).CreateTime);
        int finalResult = productionList.at(i).FinalResult;

        if (ts >= slotStart && ts < slotEnd)
        {
            trendData.TotalNumber++;
            if (finalResult == HistoryEnum::GOOD)
                trendData.GoodNumber++;
        }
        else if (ts >= slotEnd && resultList.size() < 60)
        {
            resultList.append(trendData);
            slotStart = slotEnd;
            slotEnd += SecondStep;
            trendData.TimeStamp = slotStart;
        }
        else if (ts >= slotEnd && resultList.size() >= 60)
        {
            resultList.append(trendData);
            break;
        }
    }
    if(resultList.size() == 0)
        resultList.append(trendData);

    m_YieldData.startTime = QDateTime::fromSecsSinceEpoch(resultList.at(0).TimeStamp).toString("yyyy-MM-dd hh:mm:ss");
    m_YieldData.endTime = QDateTime::fromSecsSinceEpoch(resultList.at(resultList.size() - 1).TimeStamp).toString("yyyy-MM-dd hh:mm:ss");

    setStartTime(m_YieldData.startTime);
    setEndTime(m_YieldData.endTime);
    qDebug() << "Yield StartTime: " << m_YieldData.startTime;
    qDebug() << "Yield End Time: " <<  m_YieldData.endTime;

    m_YieldData.points.clear();
    // 开始计算每个时间段的良率
    for (int i = 0; i < resultList.size(); ++i)
    {
        int total = resultList.at(i).TotalNumber;
        int good_num = resultList.at(i).GoodNumber;
        QPointF pos;
        if (total == 0)
        {
            pos.ry() = 0;
        }
        else
        {
            pos.ry() = static_cast<float>(good_num * 100 / total);
            // qDebug() << "pos.ry: " << pos.ry() << good_num << total;
        }
        pos.rx() = QDateTime::fromSecsSinceEpoch(resultList.at(i).TimeStamp).toMSecsSinceEpoch();
        m_YieldData.points.push_back(pos);
    }
    emit notifyYieldTrendChanged(m_WelderID);
}

int Trend::getYieldType() const
{
    return m_YieldType;
}

void Trend::setYieldType(int type)
{
    int duration = 0;
    QDateTime time;
    // if (m_YieldType == type)
    //     return;
    m_YieldType = type;
    emit notifyYieldTypeChanged(m_WelderID);

    m_EndTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    switch(m_YieldType)
    {
    case YieldsTrendEnum::ONE_HOUR:
        time = QDateTime::currentDateTime().addSecs(-3600);
        m_StartTime = time.toString("yyyy-MM-dd hh:mm:ss");
        duration = ONE_HOUR; // 一个小时 60s*60m
        break;
    case YieldsTrendEnum::TWENTY_FOUR_HOURS:
        time = QDateTime::currentDateTime().addDays(-1);
        m_StartTime = time.toString("yyyy-MM-dd hh:mm:ss");
        duration = ONE_DAY;   // 一天  60s*60m*24h
        break;
    case YieldsTrendEnum::SEVEN_DAYS:
        time = QDateTime::currentDateTime().addDays(-7);
        m_StartTime = time.toString("yyyy-MM-dd hh:mm:ss");
        duration = SEVEN_DAYS; // 七天
        break;
    case YieldsTrendEnum::THIRTY_DAYS:
        time = QDateTime::currentDateTime().addDays(-30);
        m_StartTime = time.toString("yyyy-MM-dd hh:mm:ss");
        duration = ONE_MONTH; // 三十天
    }

    // emit notifyStartTimeChanged();
    // emit notifyEndTimeChanged();
    upYieldData(duration);
}

QString Trend::getStartTime() const
{
    return m_StartTime;
}

void Trend::setStartTime(const QString& time)
{
    if (m_StartTime == time)
        return;
    m_StartTime = time;
    emit notifyStartTimeChanged();
}

QString Trend::getEndTime() const
{
    return m_EndTime;
}

void Trend::setEndTime(const QString& time)
{
    if (m_EndTime == time)
        return;
    m_EndTime = time;
    emit notifyEndTimeChanged();
}
