#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <QObject>
#include "DataBase/databasemanager.h"

class Production : public QObject
{
    Q_OBJECT
    /// 2024/04/07  实时良率暴露
    // 实时良率
    Q_PROPERTY(QString GoodRate             READ getGoodRate            WRITE setGoodRate               NOTIFY notifyGoodRateChanged)
    // 合格
    Q_PROPERTY(QString GoodCycleCount       READ getGoodCycleCount      WRITE setGoodCycleCount         NOTIFY notifyGoodCycleCountChanged)
    // 可疑
    Q_PROPERTY(QString SuspectCycleCount    READ getSuspectCycleCount   WRITE setSuspectCycleCount      NOTIFY notifySuspectCycleCountChanged)
    // 次品
    Q_PROPERTY(QString DefectiveCycleCount  READ getDefectiveCycleCount WRITE setDefectiveCycleCount    NOTIFY notifyDefectiveCycleCountChanged)
    // Total Count = Good + Suspect + Defective
    Q_PROPERTY(QString TotalCycleCount       READ getTotalCycleCount    WRITE setTotalCycleCount       NOTIFY notifyTotalCycleCountChanged)

    /// 2024/04/07  焊接结果暴露
    // 焊接结果:功率
    Q_PROPERTY(int PeakPower    READ getPeakPower   WRITE setPeakPower  NOTIFY notifyPeakPowerChanged)
    // 焊接结果:时间
    Q_PROPERTY(int WeldTime     READ getWeldTime    WRITE setWeldTime   NOTIFY notifyWeldTimeChanged)
    // 焊接结果:能量
    Q_PROPERTY(int Energy       READ getEnergy      WRITE setEnergy     NOTIFY notifyEnergyChanged)
    // 焊接结果:焊前高度
    Q_PROPERTY(int Preheight    READ getPreheight   WRITE setPreheight  NOTIFY notifyPreheightChanged)
    // 焊接结果:焊后高度
    Q_PROPERTY(int PostHeight   READ getPostHeight  WRITE setPostHeight NOTIFY notifyPostHeightChanged)

    //Need Add Amplitude /  WeldPressure / TriggerPressure
public:
    explicit Production(int welderID = 0, QObject *parent = nullptr);

    QString getGoodRate() const;
    void setGoodRate(const QString &rate);

    QString getGoodCycleCount() const;
    void setGoodCycleCount(const QString &cycles);

    QString getSuspectCycleCount() const;
    void setSuspectCycleCount(const QString &cycles);

    QString getDefectiveCycleCount() const;
    void setDefectiveCycleCount(const QString &cycles);

    QString getTotalCycleCount() const;
    void setTotalCycleCount(const QString &cycles);

    int getPeakPower() const;
    void setPeakPower(const int power);

    int  getWeldTime() const;
    void setWeldTime(const int time);

    int getEnergy() const;
    void setEnergy(const int energy);

    int getPreheight() const;
    void setPreheight(const int height);

    int getPostHeight() const;
    void setPostHeight(const int height);

private:
    int m_WelderID;
    DataBaseManager::DB_PRODUCTION m_DBProduction;
    int m_iGoodRate;                       // 良率
    int m_iGoodCycleCount;                 // 合格
    int m_iDefectiveCycleCount;            // 次品
    int m_iSuspectCycleCount;              // 可疑
    int m_iTotalCycleCount;                // 总数

signals:
    void notifyGoodRateChanged();
    void notifyGoodCycleCountChanged();
    void notifySuspectCycleCountChanged();
    void notifyDefectiveCycleCountChanged();
    void notifyTotalCycleCountChanged();
    void notifyPeakPowerChanged();
    void notifyWeldTimeChanged();
    void notifyEnergyChanged();
    void notifyPreheightChanged();
    void notifyPostHeightChanged();
};

#endif // PRODUCTION_H
