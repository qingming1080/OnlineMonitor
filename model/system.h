#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>
#include "DataBase/databasemanager.h"

class System : public QObject
{
    Q_OBJECT
    // Q_PROPERTY(int id           READ id             WRITE setId             NOTIFY idChanged)
    Q_PROPERTY(QString SingleFactor         READ getSingleFactor        WRITE setSingleFactor       NOTIFY notifySingleFactorChanged)
    Q_PROPERTY(QString GeneralFactor        READ getGeneralFactor       WRITE setGeneralFactor      NOTIFY notifyGeneralFactorChanged)
    Q_PROPERTY(QString ForceThreshold       READ getForceThreshold      WRITE setForceThreshold     NOTIFY notifyForceThresholdChanged)
    Q_PROPERTY(QString ResidualThreshold    READ getResidualThreshold   WRITE setResidualThreshold  NOTIFY notifyResidualThresholdChanged FINAL)
    Q_PROPERTY(QString AutoUpperLimit       READ getAutoUpperLimit      WRITE setAutoUpperLimit     NOTIFY notifyAutoUpperLimitChanged)
public:
    explicit System(int welderID = 0, QObject *parent = nullptr);

    // Q_INVOKABLE int id() const;
    // Q_INVOKABLE void setId(int newId);

    QString getSingleFactor() const;
        int GetSingleFactor() const;
    void setSingleFactor(const QString &factor);

    QString getGeneralFactor() const;
        int GetGeneralFactor() const;
    void setGeneralFactor(const QString &factor);

    QString getForceThreshold() const;
        int GetForceThreshold() const;
    void setForceThreshold(const QString &threshold);

    QString getResidualThreshold() const;
        int GetResidualThreshold() const;
    void setResidualThreshold(const QString &threshold);

    QString getAutoUpperLimit() const;
        int GetAutoUpperLimit() const;
    void setAutoUpperLimit(const QString &limit);

signals:
    // void idChanged();
    void notifySingleFactorChanged();
    void notifyGeneralFactorChanged();
    void notifyForceThresholdChanged();
    void notifyResidualThresholdChanged();
    void notifyAutoUpperLimitChanged();
private:
    int m_WelderID;
    DataBaseManager::DB_SYSTEM   m_DBSystem;
};

#endif // SYSTEM_H
