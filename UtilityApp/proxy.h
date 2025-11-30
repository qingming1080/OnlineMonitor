#ifndef PROXY_H
#define PROXY_H

#include <QObject>
#include <QList>
#include <QThread>
#include <QModbusDataUnit>
#include <QMutex>
#include <QMap>
#include "protocol/common.h"
#include "app/ethernetapp.h"
#include "app/serialapp.h"
#include "app/systemclock.h"
class Proxy : public QObject //Proxy is to start Thread and handle with the result from thread.
{
    Q_OBJECT
    QThread WorkerThread;
public:
    struct MACHINE_DEVICE
    {
        bool                    IsOpen;
        int                     Type;
        int                     Protocol;
    };
public:
    ~Proxy();
    static Proxy*   GetInstance();
    int UpdateMachineList(const int devNum, const MACHINE_DEVICE* _dev);
    int UpdateEthernetList(const int devNum, const void *_dev);
    int UpdateSerialList(const int devNum, const void *_dev);
    int UpdateWeldSettings(const int devNum, const Common::WELD_SETTING* _setting);
    int UpdateSystemClock(const void *_datetime);
    int UpdateLedStatus(const void *_objLED);
    int UpdateIOStatus(const int devNum, const void *_objIO);
    int GetMachineDev(QList<MACHINE_DEVICE>*        _dev);
    int ImplementSettings(int index);
public slots:
    void Handle(int result); // Handle with the result of thread

private:
    static constexpr int DEV_NUM = 4;
    static constexpr int ETH_DEVS = 4;
    static constexpr int SER_DEVS = 2;

    static QList<MACHINE_DEVICE>        m_listDevice;

    static Proxy* _Proxy;

    static bool m_isRunning;
    static QMutex m_mutexMachine;

protected:
    explicit Proxy(QObject *parent = nullptr);
signals:
    void Invoke(int); //Send the signal to trigger thread
};

#endif // PROXY_H
