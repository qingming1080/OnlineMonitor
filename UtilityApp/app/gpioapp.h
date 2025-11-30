#ifndef GPIOAPP_H
#define GPIOAPP_H

#include <QObject>
#include <QMutex>
class GpioApp : public QObject
{
    Q_OBJECT
public:

public:
    union LED
    {
        unsigned char LED_Byte;
        struct LED_BITS
        {
            unsigned char LED_Learning: 1;
            unsigned char LED_PilotRun: 1;
            unsigned char LED_Ready:    1;
            unsigned char LED_Alarm:    1;
        }LED_Bits;
    };

    union IO
    {
        unsigned char IO_Byte;
        struct IO_BITS
        {
            unsigned char IO_Reject: 1;
            unsigned char IO_Suspect: 1;
        }IO_Bits;
    };

    enum BEEPER_TYPE
    {
        NONE = 0,
        ONE_TIME,
        ALWAYS
    };

    static GpioApp*   GetInstance ();
    int SetLEDs(const void* _LED);
    int SetDevIOs(const int iDev, const void* _IO);
    int GetResetButton() const;
    int GetResetIO(const int iDev) const;
protected:
    void timerEvent(QTimerEvent *event) override;
private:
    static constexpr int DEV_NUM = 4;
    explicit GpioApp(QObject *parent = nullptr);
    static GpioApp* _objGpioApp;
    int m_iResetButton;
    int m_iResetSignal[DEV_NUM];
    int m_iRejectSignal[DEV_NUM];
    int m_iSuspectSignal[DEV_NUM];
    bool m_isBeeperSound;
    BEEPER_TYPE m_BeeperType;
    static QMutex  m_mutexGpio;
signals:
    void signalButtonReset(bool status); //emit signal to modbus
    void signalIOReset(int iDev, bool status); //emit signal to modbus
};

#endif // GPIOAPP_H
