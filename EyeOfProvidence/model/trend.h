#ifndef TREND_H
#define TREND_H

#include <QObject>
#include <QStandardItemModel>
#include <QtCharts>
#include <QXYSeries>
#include "DataBase/databasemanager.h"

class Trend : public QObject
{
    Q_OBJECT
    // 折线图范围
    Q_PROPERTY(int CountMinX        READ getCountMinX       WRITE setCountMinX      NOTIFY notifyCountMinXChanged       FINAL)
    Q_PROPERTY(int CountMaxX        READ getCountMaxX       WRITE setCountMaxX      NOTIFY notifyCountMaxXChanged       FINAL)
    Q_PROPERTY(float PreheightMaxY  READ getPreheightMaxY   WRITE setPreheightMaxY  NOTIFY notifyPreheightMaxYChanged   FINAL)
    Q_PROPERTY(float PreheightMinY  READ getPreheightMinY   WRITE setPreheightMinY  NOTIFY notifyPreheightMinYChanged   FINAL)
    Q_PROPERTY(float PostHeightMaxY READ getPostHeightMaxY  WRITE setPostHeightMaxY NOTIFY notifyPostHeightMaxYChanged  FINAL)
    Q_PROPERTY(float PostHeightMinY READ getPostHeightMinY  WRITE setPostHeightMinY NOTIFY notifyPostHeightMinYChanged  FINAL)
    Q_PROPERTY(float WeldTimeMaxY   READ getWeldTimeMaxY    WRITE setWeldTimeMaxY   NOTIFY notifyWeldTimeMaxYChanged    FINAL)
    Q_PROPERTY(float WeldTimeMinY   READ getWeldTimeMinY    WRITE setWeldTimeMinY   NOTIFY notifyWeldTimeMinYChanged    FINAL)
    Q_PROPERTY(int PeakPowerMaxY    READ getPeakPowerMaxY   WRITE setPeakPowerMaxY  NOTIFY notifyPeakPowerMaxYChanged   FINAL)
    Q_PROPERTY(int PeakPowerMinY    READ getPeakPowerMinY   WRITE setPeakPowerMinY  NOTIFY notifyPeakPowerMinYChanged   FINAL)
    Q_PROPERTY(int YieldType        READ getYieldType       WRITE setYieldType      NOTIFY notifyYieldTypeChanged       FINAL)
    Q_PROPERTY(QString StartTime    READ getStartTime       WRITE setStartTime      NOTIFY notifyStartTimeChanged       FINAL)
    Q_PROPERTY(QString EndTime      READ getEndTime         WRITE setEndTime        NOTIFY notifyEndTimeChanged         FINAL)

public:
    // 焊接趋势数据结构
    struct WELD_TREND
    {
        // X轴
        int Count_X_Max{0};
        int Count_X_Min{0};
        // 焊前高度 Y轴
        int Preheight_Y_Max{0};
        int Preheight_Y_Min{0};
        // 焊后高度 Y轴
        int PostHeight_Y_Max{0};
        int PostHeight_Y_Min{0};
        // 时间 Y轴
        int WeldTime_Y_Max;
        int WeldTime_Y_Min;
        // 功率
        int PeakPower_Y_Max{0};
        int PeakPower_Y_Min{0};
    };

    // 良率趋势数据结构
    struct YIELD_TREND
    {
        // 开始时间
        QString startTime;
        // 结束时间
        QString endTime;
        QList<QPointF> points;
        YIELD_TREND& operator= (const YIELD_TREND& other)
        {
            this->points.clear();
            this->startTime = other.startTime;
            this->endTime   = other.endTime;
            for(int i = 0; i < other.points.count(); ++i)
                this->points.push_back(other.points.at(i));
            return *this;
        }
    };

    struct SLOT_DATA
    {
        int TotalNumber;
        int GoodNumber;
        quint64 TimeStamp;
    };
public:
    explicit Trend(int welderID = 0, QObject *parent = nullptr);

    void AppendWeldPoint(const int cycleCount, const int power, const int time, const int preHeight, const int postHeight);
    void AppendProduction(const DataBaseManager::DB_PRODUCTION data);
    virtual void SetModel(const DataBaseManager::DB_MODEL& model);

    // 更新良率趋势
    void upYieldData(const int duration);
    // 更新焊接趋势
    void upWeldData();

    Q_INVOKABLE int getCountMinX() const;
    Q_INVOKABLE void setCountMinX(const int count);

    Q_INVOKABLE int getCountMaxX() const;
    Q_INVOKABLE void setCountMaxX(const int count);

    Q_INVOKABLE float getPreheightMaxY() const;
    Q_INVOKABLE void setPreheightMaxY(const float height);

    Q_INVOKABLE float getPreheightMinY() const;
    Q_INVOKABLE void setPreheightMinY(const float height);

    Q_INVOKABLE float getPostHeightMaxY() const;
    Q_INVOKABLE void setPostHeightMaxY(const float height);

    Q_INVOKABLE float getPostHeightMinY() const;
    Q_INVOKABLE void setPostHeightMinY(const float height);

    Q_INVOKABLE float getWeldTimeMaxY() const;
    Q_INVOKABLE void setWeldTimeMaxY(const float time);

    Q_INVOKABLE float getWeldTimeMinY() const;
    Q_INVOKABLE void setWeldTimeMinY(const float time);

    Q_INVOKABLE int getPeakPowerMaxY() const;
    Q_INVOKABLE void setPeakPowerMaxY(int power);

    Q_INVOKABLE int getPeakPowerMinY() const;
    Q_INVOKABLE void setPeakPowerMinY(int power);

    Q_INVOKABLE int getYieldType() const;
    Q_INVOKABLE void setYieldType(int type);

    Q_INVOKABLE QString getStartTime() const;
    Q_INVOKABLE void setStartTime(const QString& time);

    Q_INVOKABLE QString getEndTime() const;
    Q_INVOKABLE void setEndTime(const QString& time);


    Q_INVOKABLE void setYieldSeries(QAbstractSeries *series);
    Q_INVOKABLE void setPreheightSeries(QAbstractSeries *series);
    Q_INVOKABLE void setPostHeightSeries(QAbstractSeries *series);
    Q_INVOKABLE void setWeldTimeSeries(QAbstractSeries *series);
    Q_INVOKABLE void setPeakPowerSeries(QAbstractSeries *series);

    Q_INVOKABLE void updateXYAxisRanges();
    Q_INVOKABLE void updateSeries();
signals:

    void notifyCountMinXChanged();

    void notifyCountMaxXChanged();

    void notifyPreheightMaxYChanged();

    void notifyPreheightMinYChanged();

    void notifyPostHeightMaxYChanged();
    
    void notifyPostHeightMinYChanged();

    void notifyWeldTimeMaxYChanged();

    void notifyWeldTimeMinYChanged();

    void notifyPeakPowerMaxYChanged();

    void notifyPeakPowerMinYChanged();

    void notifyYieldTypeChanged(int welderID);

    void notifyStartTimeChanged();

    void notifyEndTimeChanged();

    void notifyYieldTrendChanged(int welderID);

private:
    void init();

    void setWeldTrendData(WELD_TREND data);

    void setYieldTrendData();

private:
    static constexpr int X_AXIS_MAX = 128;
    static constexpr int ONE_HOUR = 60 * 60;
    static constexpr int ONE_DAY = 60 * 60 * 24;
    static constexpr int SEVEN_DAYS = 60 * 60 * 24 * 7;
    static constexpr int ONE_MONTH = 60 * 60 * 24 * 30;
    int m_WelderID;

    // 焊接趋势 X轴范围
    int m_CountMinX;
    int m_CountMaxX;
    // 焊前高度 Y轴范围
    float m_PreheightMaxY;
    float m_PreheightMinY;
    // 焊后高度 Y轴范围
    float m_PostHeightMaxY;
    float m_PostHeightMinY;
    // 焊接时间 Y轴范围
    float m_WeldTimeMaxY;
    float m_WeldTimeMinY;
    // 焊接功率 Y轴范围
    int m_PeakPowerMaxY;
    int m_PeakPowerMinY;

    QXYSeries* m_pYieldSeries = nullptr;
    QXYSeries* m_pPreheightSeries = nullptr;
    QXYSeries* m_pPostHeightSeries = nullptr;
    QXYSeries* m_pWeldTimeSeries = nullptr;
    QXYSeries* m_pPeakPowerSeries = nullptr;

    QVector<QPointF> m_PreheightData;
    QVector<QPointF> m_PostHeightData;
    QVector<QPointF> m_WeldTimeData;
    QVector<QPointF> m_PeakPowerData;

    QList<DataBaseManager::DB_PRODUCTION> m_OneHourWeldResultData;

    // 良率趋势 X轴范围
    QString m_StartTime;
    QString m_EndTime;
    // 良率趋势时间类型 0_小时 1_1天 2_7天 3_30天
    int m_YieldType{0};
    QTimer* m_weldTimer;
    QTimer* m_yieldTimer;

    int lastCycleCount = -1;

    YIELD_TREND                     m_YieldData;
    DataBaseManager::DB_MODEL       m_DBModel;
};

#endif // TREND_H
