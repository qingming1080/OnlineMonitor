#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <QObject>
#include "DataBase/databasemanager.h"
#include "modbus/hbmodbusclient.h"

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
    Q_PROPERTY(QString TotalCycleCount      READ getTotalCycleCount     WRITE setTotalCycleCount        NOTIFY notifyTotalCycleCountChanged)

    /// 2024/04/07  焊接结果暴露
    // 焊接结果:功率
    Q_PROPERTY(QString PeakPower        READ getPeakPower           WRITE setPeakPower              NOTIFY notifyPeakPowerChanged)
    // 焊接结果:时间
    Q_PROPERTY(QString WeldTime         READ getWeldTime            WRITE setWeldTime               NOTIFY notifyWeldTimeChanged)
    // 焊接结果:能量
    Q_PROPERTY(QString Energy           READ getEnergy              WRITE setEnergy                 NOTIFY notifyEnergyChanged)
    // 焊接结果:焊前高度
    Q_PROPERTY(QString Preheight        READ getPreheight           WRITE setPreheight              NOTIFY notifyPreheightChanged)
    // 焊接结果:焊后高度
    Q_PROPERTY(QString PostHeight       READ getPostHeight          WRITE setPostHeight             NOTIFY notifyPostHeightChanged)

    Q_PROPERTY(QString Amplitude        READ getAmplitude           WRITE setAmplitude              NOTIFY notifyAmplitudeChanged)

    Q_PROPERTY(QString WeldPressure     READ getWeldPressure        WRITE setWeldPressure           NOTIFY notifyWeldPressureChanged)

    Q_PROPERTY(QString TriggertPressure READ getTriggertPressure    WRITE setTriggertPressure       NOTIFY notifyTriggertPressureChanged)

    Q_PROPERTY(int EnergySetting        READ getEnergySetting       WRITE setEnergySetting          NOTIFY notifyEnergySettingChanged FINAL)
    Q_PROPERTY(int AmpSetting           READ getAmpSetting          WRITE setAmpSetting             NOTIFY notifyAmpSettingChanged FINAL)
    Q_PROPERTY(int TPSetting            READ getTPSetting           WRITE setTPSetting              NOTIFY notifyTPSettingChanged FINAL)
    Q_PROPERTY(int WPSetting            READ getWPSetting           WRITE setWPSetting              NOTIFY notifyWPSettingChanged FINAL)

    Q_PROPERTY(bool ModelStatus         READ getModelStatus         WRITE setModelStatus            NOTIFY notifyModelStatusChanged FINAL)

    // 最大生产批量
    Q_PROPERTY(int ProductionMaxBacth   READ getProductionMaxBacth  WRITE setProductionMaxBacth     NOTIFY notifyProductionMaxBacthChanged)

    // 良率下限
    Q_PROPERTY(int YieldRateLowerLimit  READ getYieldRateLowerLimit WRITE setYieldRateLowerLimit    NOTIFY notifyYieldRateLowerLimitChanged)

    Q_PROPERTY(int ForceThreshold       READ getForceThreshold      WRITE setForceThreshold     NOTIFY notifyForceThresholdChanged FINAL)
    Q_PROPERTY(int ResidualThreshold    READ getResidualThreshold   WRITE setResidualThreshold  NOTIFY notifyResidualThresholdChanged FINAL)

public:
    explicit Production(int welderID = 0, QObject *parent = nullptr);

    QString getGoodRate() const;
    void setGoodRate(const QString &rate);

    QString getGoodCycleCount() const;
    int GetGoodCycleCount() const;
    void setGoodCycleCount(const QString &cycles);

    QString getSuspectCycleCount() const;
    int GetSuspectCycleCount() const;
    void setSuspectCycleCount(const QString &cycles);

    QString getDefectiveCycleCount() const;
    int GetDefectiveCycleCount() const;
    void setDefectiveCycleCount(const QString &cycles);

    QString getTotalCycleCount() const;
    int GetTotalCycleCount() const;
    void setTotalCycleCount(const QString &cycles);

    QString getPeakPower() const;
    void setPeakPower(const QString &power);

    QString  getWeldTime() const;
    void setWeldTime(const QString &time);

    QString getEnergy() const;
    void setEnergy(const QString &energy);

    QString getPreheight() const;
    void setPreheight(const QString &height);

    QString getPostHeight() const;
    void setPostHeight(const QString &height);
    
    QString getAmplitude() const;
    void setAmplitude(const QString &amplitude);

    QString getWeldPressure() const;
    void setWeldPressure(const QString& weldPressure);

    QString getTriggertPressure() const;
    void setTriggertPressure(const QString& triggertPressure);

    int getEnergySetting() const;
    void setEnergySetting(const int energy);

    int getAmpSetting() const;
    void setAmpSetting(const int amp);

    int getTPSetting() const;
    void setTPSetting(const int tp);
    
    int getWPSetting() const;
    void setWPSetting(const int wp);

    bool getModelStatus() const;
    void setModelStatus(const bool status);

    int getProductionMaxBacth() const;
    void setProductionMaxBacth(const int maxBatch);

    int getYieldRateLowerLimit() const;
    void setYieldRateLowerLimit(const int limit);

    int getForceThreshold() const;
    void setForceThreshold(const int threshold);

    int getResidualThreshold() const;
    void setResidualThreshold(const int threshold);
    
    void AppendNewRecordComming(const HBModbusClient::MODBUS_WELD_RESULT &data);

    virtual void SetModel(const DataBaseManager::DB_MODEL& model);

private:
    int m_WelderID;
    DataBaseManager::DB_PRODUCTION  m_DBProduction;
    DataBaseManager::DB_MODEL       m_DBModel;
    int m_iGoodRate;                       // 良率
    int m_iGoodCycleCount;                 // 合格
    int m_iDefectiveCycleCount;            // 次品
    int m_iSuspectCycleCount;              // 可疑
    int m_iTotalCycleCount;                // 总数
    int m_iProductionMaxBacth;
    int m_iYieldRateLowerLimit;
    int m_iForceThreshold;
    int m_iResidualThreshold;

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
    void notifyAmplitudeChanged();
    void notifyWeldPressureChanged();
    void notifyTriggertPressureChanged();

    void notifyEnergySettingChanged();
    void notifyAmpSettingChanged();
    void notifyTPSettingChanged();
    void notifyWPSettingChanged();

    void notifyModelStatusChanged();

    void notifyProductionMaxBacthChanged();
    void notifyYieldRateLowerLimitChanged();

    void notifyForceThresholdChanged();
    void notifyResidualThresholdChanged();

#ifdef REMARK_FWC
    void signalAppendOperation(const DataBaseManager::DB_PRODUCTION &insertOperation,
                               const DataBaseManager::DB_MODEL &updateOperation);
#endif
};

#endif // PRODUCTION_H
