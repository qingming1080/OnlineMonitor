#include "gpio.h"
#include "board_cm3.h"
#ifdef RASPBERRY
#include <bcm2835.h>
#endif
#include "definition.h"
#include <QDebug>
unsigned int GPIO::m_arrayInput[GPIO::TOTAL_INPUT] = {GPIO::RESET_IO_0, GPIO::RESET_IO_1, GPIO::RESET_IO_2, GPIO::RESET_IO_3, GPIO::RESET_BUTTON};
unsigned int GPIO::m_arrayOutput[GPIO::TOTAL_OUTPUT] = {GPIO::BUZZER, GPIO::SUSPECT_IO_0, GPIO::REJECT_IO_0, GPIO::SUSPECT_IO_1, GPIO::REJECT_IO_1,
                                                        GPIO::SUSPECT_IO_2, GPIO::REJECT_IO_2, GPIO::SUSPECT_IO_3, GPIO::REJECT_IO_3,
                                                        GPIO::PILOT_RUN,    GPIO::LEARNING,  GPIO::READY, GPIO::ALARM};
GPIO* GPIO::_gpio = nullptr;
QMutex  GPIO::m_Mutex;
GPIO *GPIO::GetInstance()
{
    m_Mutex.lock();
    if(_gpio == nullptr)
        _gpio = new GPIO();
    m_Mutex.unlock();
    return _gpio;
}

int GPIO::SetSuspect(const int iDev, const int iLevel)
{
    int iResult = ERROR;
    if(m_IsBoardAvaiable == false)
        return iResult;
    m_Mutex.lock();
    switch(iDev)
    {
    case DEV_0:
#ifdef RASPBERRY
        bcm2835_gpio_write(SUSPECT_IO_0, iLevel);
#endif
        iResult = OK;
        break;
    case DEV_1:
#ifdef RASPBERRY
        bcm2835_gpio_write(SUSPECT_IO_1, iLevel);
#endif
        iResult = OK;
        break;
    case DEV_2:
#ifdef RASPBERRY
        bcm2835_gpio_write(SUSPECT_IO_2, iLevel);
#endif
        iResult = OK;
        break;
    case DEV_3:
#ifdef RASPBERRY
        bcm2835_gpio_write(SUSPECT_IO_3, iLevel);
#endif
        iResult = OK;
        break;
    default:
        iResult = ERROR;
        break;
    }
    m_Mutex.unlock();
    return iResult;
}

int GPIO::SetReject(const int iDev, const int iLevel)
{
    int iResult = ERROR;
    if(m_IsBoardAvaiable == false)
        return iResult;
    m_Mutex.lock();
    switch(iDev)
    {
    case DEV_0:
#ifdef RASPBERRY
        bcm2835_gpio_write(REJECT_IO_0, iLevel);
#endif
        iResult = OK;
        break;
    case DEV_1:
#ifdef RASPBERRY
        bcm2835_gpio_write(REJECT_IO_1, iLevel);
#endif
        iResult = OK;
        break;
    case DEV_2:
#ifdef RASPBERRY
        bcm2835_gpio_write(REJECT_IO_2, iLevel);
#endif
        iResult = OK;
        break;
    case DEV_3:
#ifdef RASPBERRY
        bcm2835_gpio_write(REJECT_IO_3, iLevel);
#endif
        iResult = OK;
        break;
    default:
        iResult = ERROR;
        break;
    }
    m_Mutex.unlock();
    return iResult;
}

int GPIO::SetPilotRun(const int iLevel)
{
    int iResult = ERROR;
    m_Mutex.lock();
    if(_gpio == nullptr)
        return iResult;
    if(_gpio->m_IsBoardAvaiable == false)
        return iResult;
#ifdef RASPBERRY
    bcm2835_gpio_write(PILOT_RUN, iLevel);
    iResult = OK;
#endif
    m_Mutex.unlock();
    return iResult;
}

int GPIO::SetLearning(const int iLevel)
{
    int iResult = ERROR;
    m_Mutex.lock();
    if(_gpio == nullptr)
        return iResult;
    if(_gpio->m_IsBoardAvaiable == false)
        return iResult;
#ifdef RASPBERRY
    bcm2835_gpio_write(LEARNING, iLevel);
    iResult = OK;
#endif
    m_Mutex.unlock();
    return iResult;
}

int GPIO::SetReady(const int iLevel)
{
    int iResult = ERROR;
    m_Mutex.lock();
    if(_gpio == nullptr)
        return iResult;
    if(_gpio->m_IsBoardAvaiable == false)
        return iResult;
#ifdef RASPBERRY
    bcm2835_gpio_write(READY, iLevel);
    iResult = OK;
#endif
    m_Mutex.unlock();
    return iResult;
}

int GPIO::SetAlarm(const int iLevel)
{
    int iResult = ERROR;
    m_Mutex.lock();
    if(_gpio == nullptr)
        return iResult;
    if(_gpio->m_IsBoardAvaiable == false)
        return iResult;
#ifdef RASPBERRY
    bcm2835_gpio_write(ALARM, iLevel);
    iResult = OK;
#endif
    m_Mutex.unlock();
    return iResult;
}

int GPIO::SetBuzzer(const int iLevel)
{
    int iResult = ERROR;
    m_Mutex.lock();
    if(_gpio == nullptr)
        return iResult;
    if(_gpio->m_IsBoardAvaiable == false)
        return iResult;
#ifdef RASPBERRY
    bcm2835_gpio_write(BUZZER, iLevel);
    iResult = OK;
#endif
    m_Mutex.unlock();
    return iResult;
}

int GPIO::GetReset(const int iDev) const
{
    int iResult = ERROR;
    if(m_IsBoardAvaiable == false)
        return iResult;
    m_Mutex.lock();
    switch(iDev)
    {
    case DEV_0:
#ifdef RASPBERRY
        iResult = bcm2835_gpio_lev(RESET_IO_0);
#else
        iResult = OK;
#endif
        break;
    case DEV_1:
#ifdef RASPBERRY
        iResult = bcm2835_gpio_lev(RESET_IO_1);
#else
        iResult = OK;
#endif
        break;
    case DEV_2:
#ifdef RASPBERRY
        iResult = bcm2835_gpio_lev(RESET_IO_2);
#else
        iResult = OK;
#endif
        break;
    case DEV_3:
#ifdef RASPBERRY
        iResult = bcm2835_gpio_lev(RESET_IO_3);
#else
        iResult = OK;
#endif
        break;
    default:
        break;
    }
    m_Mutex.unlock();
    return iResult;
}

int GPIO::GetResetButton()
{
    int iResult = ERROR;
    m_Mutex.lock();
    if(_gpio == nullptr)
        return ERROR;
    if(_gpio->m_IsBoardAvaiable == false)
        return iResult;
#ifdef RASPBERRY
    iResult = bcm2835_gpio_lev(RESET_BUTTON);
#endif
    m_Mutex.unlock();
    return iResult;
}

GPIO::GPIO(QObject *parent)
    : QObject{parent}
{
    m_IsBoardAvaiable = Board_CM3::GetInstance()->GetBoardStatus();
    if(m_IsBoardAvaiable == false)
    {
        return;
    }
#ifdef RASPBERRY
    for(int i = 0; i < TOTAL_OUTPUT; i++)
    {
        bcm2835_gpio_fsel(m_arrayOutput[i], BCM2835_GPIO_FSEL_OUTP);
        bcm2835_gpio_write(m_arrayOutput[i], LOW);
    }

    for(int i = 0; i < TOTAL_INPUT; i++)
    {
        bcm2835_gpio_fsel(m_arrayInput[i], BCM2835_GPIO_FSEL_INPT);
        // bcm2835_gpio_set_pud(m_arrayInput[i], BCM2835_GPIO_PUD_DOWN);
    }
#endif
}
