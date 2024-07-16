#ifndef TREND_H
#define TREND_H

#include <QObject>
#include <QStandardItemModel>
#include "define.h"

class Trend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStandardItemModel *pBeforeModel READ pBeforeModel)  // 焊前高度
    Q_PROPERTY(QStandardItemModel *pAfterModel  READ pAfterModel)   // 焊后高度
    Q_PROPERTY(QStandardItemModel *pTimeModel   READ pTimeModel)    // 时间
    Q_PROPERTY(QStandardItemModel *pPowerModel  READ pPowerModel)   // 功率
    Q_PROPERTY(QStandardItemModel *pYieldTrend  READ pYieldTrend)   // 良率
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

public:
    explicit Trend(int welderID=0, QObject *parent = nullptr);

    Q_INVOKABLE QStandardItemModel *pBeforeModel() const;
    Q_INVOKABLE QStandardItemModel *pAfterModel() const;
    Q_INVOKABLE QStandardItemModel *pTimeModel() const;
    Q_INVOKABLE QStandardItemModel *pPowerModel() const;
    Q_INVOKABLE QStandardItemModel *pYieldTrend() const;

    void upWeldData();

    /// 0714 良率趋势五百个点
    void upYieldData();


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
    Q_INVOKABLE void setEndTime(const QString &newEndTime);

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

private:
    void init();

    void setWeldTrendData(_Weld_TrendData data);

    void setYieldTrendData(_Yield_TrendData data);

private:
    const int m_welderID;
    QStandardItemModel* m_pBeforeModel;     // 焊前高度
    QStandardItemModel* m_pAfterModel;      // 焊后高度
    QStandardItemModel* m_pTimeModel;       // 时间
    QStandardItemModel* m_pPowerModel;      // 功率
    QStandardItemModel* m_pYieldTrend;      // 良率

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
};

#endif // TREND_H
