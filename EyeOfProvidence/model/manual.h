#ifndef MANUAL_H
#define MANUAL_H

#include <QAbstractListModel>
#include "DataBase/databasemanager.h"
#include "modbus/hbmodbusclient.h"
#include "provienceEE/providenceEE.h"
#include "tools/GenericLearning.h"
///
/// \brief The Manual class : manual
/// 暴露添加一行接口，暴露数据库保存接口
class Manual : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString  EnergySetting            READ getEnergySetting           WRITE setEnergySetting          NOTIFY notifyEnergySettingChanged FINAL)
    Q_PROPERTY(QString  AmplitudeSetting         READ getAmplitudeSetting        WRITE setAmplitudeSetting       NOTIFY notifyAmplitudeSettingChanged FINAL)
    Q_PROPERTY(QString  TriggerPressureSetting   READ getTriggerPressureSetting  WRITE setTriggerPressureSetting NOTIFY notifyTriggerPressureSettingChanged FINAL)
    Q_PROPERTY(QString  WeldPressureSetting      READ getWeldPressureSetting     WRITE setWeldPressureSetting    NOTIFY notifyWeldPressureSettingChanged FINAL)
    Q_PROPERTY(bool     IsSelectedAll            READ getIsSelectedAll           WRITE setIsSelectedAll          NOTIFY notifyIsSelectedAllChanged FINAL)

    // 学习样本数
    Q_PROPERTY(int      MaxModelSamples          READ getMaxModelSamples         WRITE setMaxModelSamples        NOTIFY notifyMaxModelSamplesChanged)
    Q_PROPERTY(int      CurrentSamples           READ getCurrentSamples          WRITE setCurrentSamples         NOTIFY notifyCurrentSamplesChanged)
public:
    explicit Manual(int welderID = 0, QObject *parent = nullptr);
    ~Manual();

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole) override;

    Q_INVOKABLE void saveData();
    Q_INVOKABLE void clearData();
    Q_INVOKABLE void loadData();
    Q_INVOKABLE bool isSettingsValid() const;

    void AppendNewRecordComming(const HBModbusClient::MODBUS_WELD_RESULT &data);

    QString getEnergySetting() const;
    int GetEnergySetting() const;
    void setEnergySetting(const QString &value);
    QString getAmplitudeSetting() const;
    int GetAmplitudeSetting() const;
    void setAmplitudeSetting(const QString &value);
    QString getTriggerPressureSetting() const;
    int GetTriggerPressureSetting() const;
    void setTriggerPressureSetting(const QString &value);
    QString getWeldPressureSetting() const;
    int GetWeldPressureSetting() const;
    void setWeldPressureSetting(const QString &value);
    bool getIsSelectedAll() const;
    void setIsSelectedAll(const bool &value);
    int getMaxModelSamples() const;
    void setMaxModelSamples(const int &value);
    int getCurrentSamples() const;
    void setCurrentSamples(const int &value);
private:
    bool CalibrateModel();
    void InitDBModel(const GenericLearning::PROCESS_PARAM* _param,
                     const GenericLearning::AI_POLYNOMIAL_COEFFICIENT* _coefficient,
                     const GenericLearning::CENTRALIZED_PROPERTY centralized);
private slots:

signals:
    void notifyEnergySettingChanged();
    void notifyAmplitudeSettingChanged();
    void notifyTriggerPressureSettingChanged();
    void notifyWeldPressureSettingChanged();
    void notifyTrainingProcessFinished(DataBaseManager::DB_MODEL& model);
    void notifyIsSelectedAllChanged();
    void notifyMaxModelSamplesChanged();
    void notifyCurrentSamplesChanged();
private:
    int m_WelderID;
    QList<DataBaseManager::DB_MANUAL>   m_listManualRecords;
    DataBaseManager::DB_MODEL           m_DBModel;
    int m_iMaxModelSamples;
    int m_iCurrentSamples;
};

#endif // MANUAL_H
