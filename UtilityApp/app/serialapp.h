#ifndef SERIALAPP_H
#define SERIALAPP_H
#include "../hardware/serial.h"
#include "interfaceapp.h"
#include "../protocol/common.h"
#include <QObject>
#include <QMutex>
#include <QThread>
class SerialApp : public InterfaceApp
{
    Q_OBJECT
public:
    enum COM_NUM
    {
        COM1 = 0,
        COM2
    };
    enum BAUD_RATE
    {
        BAUD2400 = 0,
        BAUD4800,
        BAUD9600,
        BAUD19200,
        BAUD115200
    };

    enum DATA_BITS
    {
        BIT7 = 0,
        BIT8,
    };

    enum PARITY_BITS
    {
        NONE = 0,
        ODD,
        EVEN,
    };

    enum STOP_BITS
    {
        BIT1 = 0,
        BIT1_5,
        BIT2,
    };


    struct SERIAL_PROPERTIES
    {
        int m_Bandrate;
        int m_DataBits;
        int m_Parity;
        int m_StopBits;
    };

    struct SERIAL_DEV
    {
        int                 DevNum;
        int                 ComIndex;
        Common*             _ptrProtocol;
        SERIAL_PROPERTIES   Properties;
    };
    static constexpr int  PORTS = 2;
public:
    static SerialApp*   GetInstance ();
    virtual             ~SerialApp  ();
    virtual int         Open        (int iDev, const void* _dev) override;
    virtual int         Close       (int iDev) override;
    virtual int         Attach      (const int iDev, const int ProtocolType, const void* _dev) override;
    virtual int         Detach      (const int iDev) override;
    virtual int         Init        (const void* _dev) override;
    virtual int         Update      (const int iDev, const Common::WELD_SETTING* _setting) override;
protected:
    void timerEvent(QTimerEvent *event) override;
private:
#ifdef RASPBERRY
    static constexpr char Port[PORTS][13] = {"/dev/ttyAMA0", "/dev/ttyS0"};
#else
    static constexpr char Port[PORTS][13] = {"/dev/ttyUSB0", "/dev/ttyUSB1"};
#endif
    static Serial*   _objComPort[PORTS];
    static QThread*  _objThread[PORTS];
    static SerialApp* _SerialApp;
    static QMap<int, SERIAL_DEV> m_mapSerialDev;

    int getPortIndex();
private:
    explicit SerialApp(QObject *parent = nullptr);

private slots:
    void slotParseWeldResult(int iDev, QString strResult); // Handle with the result
signals:
    void signalWeldResultReady(int iDev, Common* _protocol); //emit signal to modbus
    void signalDeviceStatus(int iDev, bool status);          //emit signal to modbus
};

#endif // SERIALAPP_H
