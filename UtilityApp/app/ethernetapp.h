#ifndef ETHERNETAPP_H
#define ETHERNETAPP_H

#include <QObject>
#include "hardware/w5500.h"
#include "hardware/board_cm3.h"
#include "definition.h"
#include "hardware/ethernet.h"
#include "interfaceapp.h"
#include "../protocol/common.h"
#include <QMap>
class EthernetApp : public InterfaceApp
{
    Q_OBJECT
public:
    struct TCP_PROPERTIES
    {
        unsigned char   ServerAddr[4];
        unsigned char   LocalAddr[4];
        unsigned short  ServerPort;
    };

    struct ETHERNET_DEV
    {
        int             DevNum;
        int             SocketIndex;
        Common*         _ptrProtocol;
        TCP_PROPERTIES  Properties;
    };
    static constexpr int  ETHS = 4;
public:
    static EthernetApp* GetInstance     ();
    virtual             ~EthernetApp    ();
    virtual int         Init            (const void* _dev) override;
    virtual int         Open            (int iDev, const void* _dev) override;
    virtual int         Close           (int iDev) override;
    virtual int         Attach          (const int iDev, const int ProtocolType, const void *_dev) override;
    virtual int         Detach          (const int iDev) override;
    virtual int         Update          (const int iDev, const Common::WELD_SETTING* _setting) override;

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    explicit EthernetApp(QObject *parent = nullptr);
    static  EthernetApp* _EthernetApp;
    static W5500* _W5500;
    static Ethernet*   _Socket[ETHS];
    static QMap<int, ETHERNET_DEV> m_mapEthernetDev;


    static unsigned char Gateway[4];
    static unsigned char LocalIP[4];
    static constexpr unsigned char SUBNET_MASK[4] = {255, 255, 255, 0};

    int getSocketIndex();

signals:
    void signalWeldResultReady(int iDev, Common* _protocol); //emit signal to modbus
    void signalDeviceStatus(int iDev, bool status);          //emit signal to modbus
private slots:
    void slotParseWeldResult(int iDev, QString strResult); // Handle with the result
};

#endif // ETHERNETAPP_H
