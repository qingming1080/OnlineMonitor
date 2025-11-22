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
    Q_PROPERTY(int CountMinX READ getCountMinX WRITE setCountMinX NOTIFY notifyCountMinXChanged)
    Q_PROPERTY(int CountMaxX READ getCountMaxX WRITE setCountMaxX NOTIFY notifyCountMaxXChanged)
    Q_PROPERTY(float PreheightMaxY READ getPreheightMaxY WRITE setPreheightMaxY NOTIFY notifyPreheightMaxYChanged)
    Q_PROPERTY(float PreheightMinY READ getPreheightMinY WRITE setPreheightMinY NOTIFY notifyPreheightMinYChanged)
    Q_PROPERTY(float PostHeightMaxY READ getPostHeightMaxY WRITE setPostHeightMaxY NOTIFY notifyPostHeightMaxYChanged)
    Q_PROPERTY(float PostHeightMinY READ getPostHeightMinY WRITE setPostHeightMinY NOTIFY notifyPostHeightMinYChanged)
    Q_PROPERTY(float WeldTimeMaxY READ getWeldTimeMaxY WRITE setWeldTimeMaxY NOTIFY notifyWeldTimeMaxYChanged)
    Q_PROPERTY(float WeldTimeMinY READ getWeldTimeMinY WRITE setWeldTimeMinY NOTIFY notifyWeldTimeMinYChanged)
    Q_PROPERTY(int PeakPowerMaxY READ getPeakPowerMaxY WRITE setPeakPowerMaxY NOTIFY notifyPeakPowerMaxYChanged)
    Q_PROPERTY(int PeakPowerMinY READ getPeakPowerMinY WRITE setPeakPowerMinY NOTIFY notifyPeakPowerMinYChanged)
    Q_PROPERTY(int yieldType READ yieldType WRITE setYieldType NOTIFY yieldTypeChanged)
    Q_PROPERTY(QString startTime READ startTime WRITE setStartTime NOTIFY startTimeChanged FINAL)
    Q_PROPERTY(QString endTime READ endTime WRITE setEndTime NOTIFY endTimeChanged FINAL)

    /// TEST 2024_08_18
    friend class Device;
    /// TEST 2024_08_18
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
public:
    explicit Trend(int welderID = 0, QObject *parent = nullptr);

    void AppendWeldPoint(const int cycleCount, const int power, const int time, const int preHeight, const int postHeight);
    virtual void SetModel(const DataBaseManager::DB_MODEL& model);

    // 更新良率趋势
    void upYieldData();
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

    Q_INVOKABLE int yieldType() const;
    Q_INVOKABLE void setYieldType(int newYieldType);

    Q_INVOKABLE QString startTime() const;
    Q_INVOKABLE void setStartTime(const QString &newStartTime);

    Q_INVOKABLE QString endTime() const;
    Q_INVOKABLE void setEndTime(const QString &newEndTime = nullptr);


    Q_INVOKABLE void setYieldSeries(QAbstractSeries *series);
    Q_INVOKABLE void setPreheightSeries(QAbstractSeries *series);
    Q_INVOKABLE void setPostHeightSeries(QAbstractSeries *series);
    Q_INVOKABLE void setWeldTimeSeries(QAbstractSeries *series);
    Q_INVOKABLE void setPeakPowerSeries(QAbstractSeries *series);
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

    void yieldTypeChanged();

    void startTimeChanged();

    void endTimeChanged();

    void signalYieldTrendChanged();

private:
    void init();

    void setWeldTrendData(WELD_TREND data);

    void setYieldTrendData();
    void updateYAxisRanges();

private:
    static constexpr int X_AXIS_MAX = 256;
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
    // 良率趋势 X轴范围
    QString m_startTime;
    QString m_endTime;

    // 良率趋势时间类型 0_小时 1_1天 2_7天 3_30天
    int m_yieldType{0};

    QTimer* m_weldTimer;
    QTimer* m_yieldTimer;

    DataBaseManager::DB_YIELD_TREND m_yieldData;
    QVector<QPointF> m_PreheightData;
    QVector<QPointF> m_PostHeightData;
    QVector<QPointF> m_WeldTimeData;
    QVector<QPointF> m_PeakPowerData;

    QXYSeries* m_pYieldSeries = nullptr;
    QXYSeries* m_pPreheightSeries = nullptr;
    QXYSeries* m_pPostHeightSeries = nullptr;
    QXYSeries* m_pWeldTimeSeries = nullptr;
    QXYSeries* m_pPeakPowerSeries = nullptr;

    DataBaseManager::DB_MODEL       m_DBModel;
};

#endif // TREND_H
