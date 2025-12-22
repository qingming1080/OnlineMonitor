#include "gpioapp.h"
#include "../hardware/gpio.h"
#include "definition.h"
#include <QDebug>
GpioApp* GpioApp::_objGpioApp = nullptr;
QMutex  GpioApp::m_mutexGpio;
GpioApp* GpioApp::GetInstance()
{
    return (_objGpioApp != nullptr) ? _objGpioApp : (_objGpioApp = new GpioApp());
}

int GpioApp::SetLEDs(const void *_LED)
{
    if(_LED == nullptr)
        return ERROR;
    const LED* _obj = reinterpret_cast<const LED*>(_LED);
    qDebug() << "Learning LED: " << _obj->LED_Bits.LED_Learning;
    int status = _obj->LED_Bits.LED_Learning;
    if(status == ON)
        GPIO::GetInstance()->SetLearning(OFF);
    else
        GPIO::GetInstance()->SetLearning(ON);
    qDebug() << "Pilot Run LED: " << _obj->LED_Bits.LED_PilotRun;
    status = _obj->LED_Bits.LED_PilotRun;
    if(status == ON)
        GPIO::GetInstance()->SetPilotRun(OFF);
    else
        GPIO::GetInstance()->SetPilotRun(ON);
    qDebug() << "Ready LED: " << _obj->LED_Bits.LED_Ready;
    status = _obj->LED_Bits.LED_Ready;
    if(status == ON)
        GPIO::GetInstance()->SetReady(OFF);
    else
        GPIO::GetInstance()->SetReady(ON);
    qDebug() << "Alarm LED: " << _obj->LED_Bits.LED_Alarm;
    status = _obj->LED_Bits.LED_Alarm;
    if(status == ON)
        GPIO::GetInstance()->SetAlarm(OFF);
    else
        GPIO::GetInstance()->SetAlarm(ON);
    return OK;
}

int GpioApp::SetDevIOs(const int iDev, const void* _IO)
{
    if(_IO == nullptr)
        return ERROR;
    const IO* _obj = reinterpret_cast<const IO*>(_IO);
    qDebug() << "iDEV: " << iDev;
    qDebug() << "Reject: " << _obj->IO_Bits.IO_Reject;
    int status = _obj->IO_Bits.IO_Reject;
    GPIO::GetInstance()->SetReject(iDev, status);
    m_iRejectSignal[iDev] = _obj->IO_Bits.IO_Reject;

    qDebug() << "Suspect: " << _obj->IO_Bits.IO_Suspect;
    status = _obj->IO_Bits.IO_Suspect;
    GPIO::GetInstance()->SetSuspect(iDev, status);
    m_iSuspectSignal[iDev] = _obj->IO_Bits.IO_Suspect;
    m_mutexGpio.lock();
    m_BeeperType = NONE;
    for(int i = 0; i < DEV_NUM; i++)
    {
        if(m_iSuspectSignal[i] == ON)
        {
            m_BeeperType = ONE_TIME;
            break;
        }
    }
    for(int i = 0; i < DEV_NUM; i++)
    {
        if(m_iRejectSignal[i] == ON)
        {
            m_BeeperType = ALWAYS;
            break;
        }
    }
    m_mutexGpio.unlock();
    return OK;
}

int GpioApp::GetResetButton() const
{
    return GPIO::GetInstance()->GetResetButton();
}

int GpioApp::GetResetIO(const int iDev) const
{
    return GPIO::GetInstance()->GetReset(iDev);
}

void GpioApp::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    if(m_iResetButton != GetResetButton())
    {
        m_iResetButton = GetResetButton();
        emit signalButtonReset(static_cast<bool>(m_iResetButton));
    }
    for(int i = 0; i < DEV_NUM; i++)
    {
        if(m_iResetSignal[i] != GetResetIO(i))
        {
            m_iResetSignal[i] = GetResetIO(i);
            emit signalIOReset(i, static_cast<bool>(m_iResetSignal[i]));
        }
    }

    m_mutexGpio.lock();
    if(m_isBeeperSound == true)
    {
        GPIO::GetInstance()->SetBuzzer(OFF);
        m_isBeeperSound = false;
    }
    else
    {
        switch(m_BeeperType)
        {
        case NONE:
            GPIO::GetInstance()->SetBuzzer(OFF);
            break;
        case ONE_TIME:
            GPIO::GetInstance()->SetBuzzer(ON);
            m_BeeperType = NONE;
            m_isBeeperSound = true;
            break;
        case ALWAYS:
            GPIO::GetInstance()->SetBuzzer(ON);
            m_isBeeperSound = true;
            break;
        default:
            GPIO::GetInstance()->SetBuzzer(OFF);
            break;
        }
    }
    m_mutexGpio.unlock();
}

GpioApp::GpioApp(QObject *parent)
    : QObject{parent}
{
    GPIO::GetInstance();
    m_iResetButton = 0;
    m_isBeeperSound = false;
    m_BeeperType = NONE;
    for(int i = 0; i < DEV_NUM; i++)
    {
        m_iResetSignal[i] = 0;
        m_iRejectSignal[i] = 0;
        m_iSuspectSignal[i] = 0;
    }
    this->startTimer(1000);
}
