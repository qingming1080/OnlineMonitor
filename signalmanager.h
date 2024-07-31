#ifndef SIGNALMANAGER_H
#define SIGNALMANAGER_H

#include <QObject>

class SignalManager : public QObject
{
    Q_OBJECT
public:
    static SignalManager* getInstance();

signals:
    void signalAddRecord(const QDateTime& time, const QString& text);

private:
    explicit SignalManager(QObject *parent = nullptr);

private:
    static SignalManager* s_pSignalManager;
};

#endif // SIGNALMANAGER_H
