#ifndef SUBJECT_H
#define SUBJECT_H

#include <QObject>
#include "proxy.h"
#include "app/ethernetapp.h"
#include "app/serialapp.h"

class Subject : public QObject // Need to run something that need to be run in the thread
{
    Q_OBJECT
public:
    explicit Subject(QObject *parent = nullptr);
    virtual ~Subject();
public slots:
    void Implement(int arg);      // define the implement run by thread
private:
    static QList<Proxy::MACHINE_DEVICE>        m_listDevice;
    static QMap<int, EthernetApp::ETHERNET_DEV>   m_mapEthernet;
    static QMap<int, SerialApp::SERIAL_DEV>     m_mapSerial;
signals:
    void signalReady(int result); // The Thread has been finished.
};

#endif // SUBJECT_H
