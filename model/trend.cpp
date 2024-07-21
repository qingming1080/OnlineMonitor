#include "trend.h"
#include <QTimer>
#include "DataBase/databasemanager.h"
#include <QDateTime>
Trend::Trend(int welderID, QObject *parent)
    : QObject{parent}, m_welderID(welderID)
{
    init();
}

QStandardItemModel *Trend::pBeforeModel() const
{
    return m_pBeforeModel;
}

QStandardItemModel *Trend::pAfterModel() const
{
    return m_pAfterModel;
}

QStandardItemModel *Trend::pTimeModel() const
{
    return m_pTimeModel;
}

QStandardItemModel *Trend::pPowerModel() const
{
    return m_pPowerModel;
}

QStandardItemModel *Trend::pYieldTrend() const
{
    return m_pYieldTrend;
}

void Trend::upYieldData()
{
    if(m_yieldType == 0)
        setYieldTrendData(DataBaseManager::getInstance()->getYieldTrendData(0-60*60, m_welderID));  // 一个小时 60s*60m
    else if(m_yieldType == 1)
        setYieldTrendData(DataBaseManager::getInstance()->getYieldTrendData(0-60*60*24, m_welderID));   // 一天  60s*60m*24h
    else if(m_yieldType == 2)
        setYieldTrendData(DataBaseManager::getInstance()->getYieldTrendData(0-60*60*24*7, m_welderID)); // 七天
    else if(m_yieldType == 3)
        setYieldTrendData(DataBaseManager::getInstance()->getYieldTrendData(0-60*60*24*30, m_welderID)); // 三十天
}



void Trend::setWeldTrendData(_Weld_TrendData result)
{
    // 清除当前折线数据
    m_pBeforeModel->clear();
    m_pAfterModel->clear();
    m_pTimeModel->clear();
    m_pPowerModel->clear();

    for(int row = 0; row < result.data.size(); ++row)
    {
        // 焊前高度
        // 点下标
        QStandardItem* before_Row_Item = new QStandardItem(QString::number(row));
        // X坐标
        QStandardItem* before_X_Item = new QStandardItem(QString::number(result.data.at(row).serial_number));
        // Y坐标
        QStandardItem* before_Y_Item = new QStandardItem(QString::number(result.data.at(row).pre_height));
        m_pBeforeModel->setItem(row, 0, before_Row_Item);
        m_pBeforeModel->setItem(row, 1, before_X_Item);
        m_pBeforeModel->setItem(row, 2, before_Y_Item);

        // 焊后高度
        QStandardItem* after_Row_Item = new QStandardItem(QString::number(row));
        QStandardItem* after_X_Item = new QStandardItem(QString::number(result.data.at(row).serial_number));
        QStandardItem* after_Y_Item = new QStandardItem(QString::number(result.data.at(row).post_height));
        m_pAfterModel->setItem(row, 0, after_Row_Item);
        m_pAfterModel->setItem(row, 1, after_X_Item);
        m_pAfterModel->setItem(row, 2, after_Y_Item);

        // 时间
        QStandardItem* time_Row_Item = new QStandardItem(QString::number(row));
        QStandardItem* time_X_Item = new QStandardItem(QString::number(result.data.at(row).serial_number));
        // 去掉数据库的s时间单位
        QString time = result.data.at(row).time.left(result.data.at(row).time.length()-1);
        QStandardItem* time_Y_Item = new QStandardItem(time);
        m_pTimeModel->setItem(row, 0, time_Row_Item);
        m_pTimeModel->setItem(row, 1, time_X_Item);
        m_pTimeModel->setItem(row, 2, time_Y_Item);

        // 功率
        QStandardItem* power_Row_Item = new QStandardItem(QString::number(row));
        QStandardItem* power_X_Item = new QStandardItem(QString::number(result.data.at(row).serial_number));
        QStandardItem* power_Y_Item = new QStandardItem(QString::number(result.data.at(row).power));
        m_pPowerModel->setItem(row, 0, power_Row_Item);
        m_pPowerModel->setItem(row, 1, power_X_Item);
        m_pPowerModel->setItem(row, 2, power_Y_Item);
    }

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

void Trend::setYieldTrendData(_Yield_TrendData data)
{
    // 清除当前折线数据
    m_pYieldTrend->clear();

    for(int row = 0; row < data.points.size(); ++row)
    {
        // 良率折线
        QStandardItem* yieldItem      = new QStandardItem(QString::number(row));
        QDateTime time = QDateTime::fromString(data.points.at(row).second, "yyyy-MM-dd hh:mm:ss");
        QStandardItem* yield_X_Item   = new QStandardItem(QString::number(time.toMSecsSinceEpoch()));
        QStandardItem* yield_Y_Item   = new QStandardItem(QString::number(data.points.at(row).first));
        m_pYieldTrend->setItem(row, 0, yieldItem);
        m_pYieldTrend->setItem(row, 1, yield_X_Item);
        m_pYieldTrend->setItem(row, 2, yield_Y_Item);
    }

    m_startTime = data.startTime;
    m_endTime   = data.endTime;
    emit startTimeChanged();
    emit endTimeChanged();
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
    m_pBeforeModel  = new QStandardItemModel();
    m_pBeforeModel->setColumnCount(3);

    m_pAfterModel   = new QStandardItemModel();
    m_pAfterModel->setColumnCount(3);

    m_pTimeModel    = new QStandardItemModel();
    m_pTimeModel->setColumnCount(3);

    m_pPowerModel   = new QStandardItemModel();
    m_pPowerModel->setColumnCount(3);

    m_pYieldTrend   = new QStandardItemModel();
    m_pYieldTrend->setColumnCount(3);


    // 良率趋势刷新
    m_yieldTimer = new QTimer;
    connect(m_yieldTimer, &QTimer::timeout, [=](){
        upYieldData();
    });
    m_yieldTimer->start(1000*60*1);

    upYieldData();
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
    emit yieldTypeChanged();
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
