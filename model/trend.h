#ifndef TREND_H
#define TREND_H

#include <QObject>
#include <QStandardItemModel>
#include "define.h"

#include <QtCharts>
#include <QXYSeries>

class Trend : public QObject
{
    Q_OBJECT
    // 折线图范围
    Q_PROPERTY(int idMinX READ idMinX WRITE setIdMinX NOTIFY idMinXChanged)
    Q_PROPERTY(int idMaxX READ idMaxX WRITE setIdMaxX NOTIFY idMaxXChanged)
    Q_PROPERTY(int beforeMaxY READ beforeMaxY WRITE setBeforeMaxY NOTIFY beforeMaxYChanged)
    Q_PROPERTY(int beforeMinY READ beforeMinY WRITE setBeforeMinY NOTIFY beforeMinYChanged)
    Q_PROPERTY(int afterMaxY READ afterMaxY WRITE setAfterMaxY NOTIFY afterMaxYChanged)
    Q_PROPERTY(int afterMinY READ afterMinY WRITE setAfterMinY NOTIFY afterMinYChanged)
    Q_PROPERTY(double timeMaxY READ timeMaxY WRITE setTimeMaxY NOTIFY timeMaxYChanged)
    Q_PROPERTY(double timeMinY READ timeMinY WRITE setTimeMinY NOTIFY timeMinYChanged)
    Q_PROPERTY(int powerMaxY READ powerMaxY WRITE setPowerMaxY NOTIFY powerMaxYChanged)
    Q_PROPERTY(int powerMinY READ powerMinY WRITE setPowerMinY NOTIFY powerMinYChanged)
    Q_PROPERTY(int yieldType READ yieldType WRITE setYieldType NOTIFY yieldTypeChanged)
    Q_PROPERTY(QString startTime READ startTime WRITE setStartTime NOTIFY startTimeChanged FINAL)
    Q_PROPERTY(QString endTime READ endTime WRITE setEndTime NOTIFY endTimeChanged FINAL)

    /// TEST 2024_08_18
    friend class Device;
    /// TEST 2024_08_18

public:
    explicit Trend(int welderID=0, QObject *parent = nullptr);

    // 更新良率趋势
    void upYieldData();
    // 更新焊接趋势
    void upWeldData();

    Q_INVOKABLE int idMinX() const;
    Q_INVOKABLE void setIdMinX(int newIdMinX);

    Q_INVOKABLE int idMaxX() const;
    Q_INVOKABLE void setIdMaxX(int newIdMaxX);

    Q_INVOKABLE int beforeMaxY() const;
    Q_INVOKABLE void setBeforeMaxY(int newBeforeMaxY);

    Q_INVOKABLE int beforeMinY() const;
    Q_INVOKABLE void setBeforeMinY(int newBeforeMinY);

    Q_INVOKABLE int afterMaxY() const;
    Q_INVOKABLE void setAfterMaxY(int newAfterMaxY);

    Q_INVOKABLE int afterMinY() const;
    Q_INVOKABLE void setAfterMinY(int newAfterMinY);

    Q_INVOKABLE double timeMaxY() const;
    Q_INVOKABLE void setTimeMaxY(double newTimeMaxY);

    Q_INVOKABLE double timeMinY() const;
    Q_INVOKABLE void setTimeMinY(double newTimeMinY);

    Q_INVOKABLE int powerMaxY() const;
    Q_INVOKABLE void setPowerMaxY(int newPowerMaxY);

    Q_INVOKABLE int powerMinY() const;
    Q_INVOKABLE void setPowerMinY(int newPowerMinY);

    Q_INVOKABLE int yieldType() const;
    Q_INVOKABLE void setYieldType(int newYieldType);

    Q_INVOKABLE QString startTime() const;
    Q_INVOKABLE void setStartTime(const QString &newStartTime);

    Q_INVOKABLE QString endTime() const;
    Q_INVOKABLE void setEndTime(const QString &newEndTime = nullptr);


    Q_INVOKABLE void setYieldSeries(QAbstractSeries *series);
    Q_INVOKABLE void setFrontSeries(QAbstractSeries *series);
    Q_INVOKABLE void setBackSeries(QAbstractSeries *series);
    Q_INVOKABLE void setTimeSeries(QAbstractSeries *series);
    Q_INVOKABLE void setPowerSeries(QAbstractSeries *series);
signals:

    void idMinXChanged();

    void idMaxXChanged();

    void beforeMaxYChanged();

    void beforeMinYChanged();

    void afterMaxYChanged();

    void afterMinYChanged();

    void timeMaxYChanged();

    void timeMinYChanged();

    void powerMaxYChanged();

    void powerMinYChanged();

    void yieldTypeChanged();

    void startTimeChanged();

    void endTimeChanged();

    void signalYieldTrendChanged();

private:
    void init();

    void setWeldTrendData(_Weld_TrendData data);

    void setYieldTrendData();

private:
    const int m_welderID;

    // 焊接趋势 X轴范围
    int m_idMinX;
    int m_idMaxX;
    // 焊前高度 Y轴范围
    int m_beforeMaxY;
    int m_beforeMinY;
    // 焊后高度 Y轴范围
    int m_afterMaxY;
    int m_afterMinY;
    // 焊接时间 Y轴范围
    double m_timeMaxY;
    double m_timeMinY;
    // 焊接功率 Y轴范围
    int m_powerMaxY;
    int m_powerMinY;
    // 良率趋势 X轴范围
    QString m_startTime;
    QString m_endTime;

    // 良率趋势时间类型 0_小时 1_1天 2_7天 3_30天
    int m_yieldType{0};

    QTimer* m_weldTimer;
    QTimer* m_yieldTimer;

    // _Yield_TrendData m_yieldData;
    // QVector<QPointF> m_frontData;
    // QVector<QPointF> m_backData;
    // QVector<QPointF> m_timeData;
    // QVector<QPointF> m_powerData;

    // QXYSeries* m_pYieldSeries = nullptr;
    // QXYSeries* m_pFrontSeries = nullptr;
    // QXYSeries* m_pBackSeries = nullptr;
    // QXYSeries* m_pTimeSeries = nullptr;
    // QXYSeries* m_pPowerSeries = nullptr;
public:
    _Yield_TrendData m_yieldData;
    QVector<QPointF> m_frontData;
    QVector<QPointF> m_backData;
    QVector<QPointF> m_timeData;
    QVector<QPointF> m_powerData;

    QXYSeries* m_pYieldSeries = nullptr;
    QXYSeries* m_pFrontSeries = nullptr;
    QXYSeries* m_pBackSeries = nullptr;
    QXYSeries* m_pTimeSeries = nullptr;
    QXYSeries* m_pPowerSeries = nullptr;
};

#endif // TREND_H
