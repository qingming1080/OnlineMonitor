#include "proxy.h"
#include "subject.h"
#include "definition.h"
#include "../app/gpioapp.h"
#include <QDebug>
QList<Proxy::MACHINE_DEVICE>        Proxy::m_listDevice;
Proxy* Proxy::_Proxy = nullptr;
bool Proxy::m_isRunning = false;
QMutex Proxy::m_mutexMachine;

Proxy::Proxy(QObject *parent) : QObject{parent}
{
    //Initialize Machine Device
    m_listDevice.clear();

}

Proxy::~Proxy()
{
    WorkerThread.quit();
    WorkerThread.wait();
}

Proxy *Proxy::GetInstance()
{
    return (_Proxy != nullptr) ? _Proxy : (_Proxy = new Proxy());
}

int Proxy::UpdateMachineList(const int devNum, const MACHINE_DEVICE *_dev)
{
    m_mutexMachine.lock();
    MACHINE_DEVICE machine;
    machine.IsOpen = _dev->IsOpen;
    machine.Protocol = _dev->Protocol;
    machine.Type = _dev->Type;
    if(devNum < m_listDevice.size())
    {
        m_listDevice[devNum].IsOpen = machine.IsOpen;
        m_listDevice[devNum].Protocol = machine.Protocol;
        m_listDevice[devNum].Type = machine.Type;
    }
    else
        m_listDevice.push_back(machine);
    m_mutexMachine.unlock();
    return OK;
}

int Proxy::UpdateEthernetList(const int devNum, const void *_dev)
{
    int iResult = ERROR;
    if(devNum < m_listDevice.size())
    {
        if(m_listDevice[devNum].IsOpen == false)
            EthernetApp::GetInstance()->Close(devNum);
        else
        {
            EthernetApp::GetInstance()->Init(_dev);
            EthernetApp::GetInstance()->Attach(devNum, m_listDevice[devNum].Protocol, _dev);
            EthernetApp::GetInstance()->Open(devNum, _dev);
            SerialApp::GetInstance()->Detach(devNum);
        }
        iResult = OK;
    }
    else
        iResult = ERROR;
    return iResult;
}

int Proxy::UpdateSerialList(const int devNum, const void *_dev)
{
    int iResult = ERROR;
    if(devNum < m_listDevice.size())
    {
        if(m_listDevice[devNum].IsOpen == false)
            SerialApp::GetInstance()->Close(devNum);
        else
        {
            // SerialApp::GetInstance()->Init(_dev);
            SerialApp::GetInstance()->Attach(devNum, m_listDevice[devNum].Protocol, _dev);
            SerialApp::GetInstance()->Open(devNum, _dev);
            // EthernetApp::GetInstance()->Detach(devNum);
        }
        iResult = OK;
    }
    else
        iResult = ERROR;
    return iResult;
}

int Proxy::UpdateWeldSettings(const int devNum, const Common::WELD_SETTING* _setting)
{
    if(devNum < m_listDevice.size())
    {
        switch(m_listDevice[devNum].Type)
        {
        case InterfaceApp::ETHERNET:
            EthernetApp::GetInstance()->Update(devNum, _setting);
            break;
        case InterfaceApp::SERIAL:
            SerialApp::GetInstance()->Update(devNum, _setting);
            break;
        default:
            break;
        }
    }
    return OK;
}

int Proxy::UpdateSystemClock(const void *_datetime)
{
    int iResult = ERROR;
    if(SystemClock::GetInstance()->SetSystemClock(_datetime) == OK)
    {
        SystemClock::GetInstance()->SyncSystemClock();
        iResult = OK;
    }
    return iResult;
}

int Proxy::UpdateLedStatus(const void *_objLED)
{
    GpioApp::GetInstance()->SetLEDs(_objLED);
    return OK;
}

int Proxy::UpdateIOStatus(const int devNum, const void *_objIO)
{
    GpioApp::GetInstance()->SetDevIOs(devNum, _objIO);
    return OK;
}

int Proxy::GetMachineDev(QList<MACHINE_DEVICE> *_dev)
{
    if(_dev == nullptr)
        return ERROR;
    m_mutexMachine.lock();
    MACHINE_DEVICE device;
    for(int i = 0; i < m_listDevice.size(); i++)
    {
        device.IsOpen = m_listDevice[i].IsOpen;
        device.Protocol = m_listDevice[i].Protocol;
        device.Type = m_listDevice[i].Type;
        _dev->push_back(device);
    }
    m_mutexMachine.unlock();
    return OK;
}

int Proxy::ImplementSettings(int index)
{
    if(WorkerThread.isRunning() == false)
    {
        Subject *_ptrSubject = new Subject();
        _ptrSubject->moveToThread(&WorkerThread); //call moveToThread to move the task to WorkerThread

        connect(this, SIGNAL(Invoke(int)), _ptrSubject, SLOT(Implement(int))); //Invoke signal emitted to launch the pthread
        connect(&WorkerThread, &QThread::finished, _ptrSubject, &QObject::deleteLater); // The thread is delete when it is finished
        connect(_ptrSubject, SIGNAL(signalReady(int)), this, SLOT(Handle(int))); // The thread is completed and emit the signal, to handle with result.

        WorkerThread.start(); //launch the thread
        emit Invoke(index);
    }
    return OK;
}

void Proxy::Handle(int result)
{
    Q_UNUSED(result);
    WorkerThread.quit();
    WorkerThread.wait();
}
