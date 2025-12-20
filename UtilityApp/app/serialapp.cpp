#include "serialapp.h"
#include <QDebug>
#include "../definition.h"
#include "../protocol/touchscreen.h"
Serial* SerialApp::_objComPort[PORTS] = {nullptr, nullptr};
QThread* SerialApp::_objThread[PORTS] = {nullptr, nullptr};
SerialApp* SerialApp::_SerialApp = nullptr;
constexpr const char SerialApp::Port[PORTS][13];
QMap<int, SerialApp::SERIAL_DEV> SerialApp::m_mapSerialDev;
SerialApp::SerialApp(QObject *parent)
    : InterfaceApp{parent}
{
    for(int i = 0; i < PORTS; i++)
    {
        _objComPort[i] = new Serial();
        connect(_objComPort[i], SIGNAL(signalResultReady(int,QString)), this, SLOT(slotParseWeldResult(int,QString)), Qt::QueuedConnection);

        _objThread[i] = new QThread();
        _objComPort[i]->moveToThread(_objThread[i]);
        connect(_objThread[i], &QThread::started, _objComPort[i], &Serial::Open_Serial_Port);
        connect(_objThread[i], &QThread::finished, _objComPort[i], &Serial::Close_Serial_Port);
    }
    m_mapSerialDev.clear();
    this->startTimer(1000);
}

void SerialApp::slotParseWeldResult(int iDev, QString strResult)
{
    m_mutexWeldResult.lock();
    if(m_mapSerialDev.contains(iDev) == true)
    {
        if(m_mapSerialDev[iDev]._ptrProtocol != nullptr)
        {
            m_mapSerialDev[iDev]._ptrProtocol->ParseWeldResult(strResult);
            emit signalWeldResultReady(iDev, m_mapSerialDev[iDev]._ptrProtocol);
        }
    }
    m_mutexWeldResult.unlock();
}

SerialApp::~SerialApp()
{
    for(int i = 0; i < PORTS; i++)
    {
        _objComPort[i]->Close_Serial_Port();
        delete _objComPort[i];
        if(_objThread[i]->isRunning() == true)
            _objThread[i]->quit();
        _objThread[i]->deleteLater();
    }
}

int SerialApp::Init(const void *_dev)
{
    if(_dev == nullptr)
        return ERROR;
    m_mutexDev.lock();
    for(int i = 0; i < PORTS; i++)
    {
        if(_objThread[i]->isRunning() == true)
            _objThread[i]->quit();
    }
    QMap<int, SERIAL_DEV>::iterator iter = m_mapSerialDev.begin();
    while(iter != m_mapSerialDev.end())
    {
        if(iter->_ptrProtocol != nullptr)
        {
            delete iter->_ptrProtocol;
            iter->_ptrProtocol = nullptr;
        }
        iter++;
    }
    m_mapSerialDev.clear();
    m_mutexDev.unlock();
    return OK;
}

int SerialApp::Update(const int iDev, const Common::WELD_SETTING *_setting)
{
    int iResult = ERROR;
    if(_setting == nullptr)
        return iResult;
    if(m_mapSerialDev.contains(iDev) == true)
    {
        if(m_mapSerialDev[iDev]._ptrProtocol != nullptr)
        {
            m_mapSerialDev[iDev]._ptrProtocol->SetWeldSetting(_setting);
            iResult = OK;
        }
    }
    return iResult;
}

void SerialApp::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    if(m_mapSerialDev.isEmpty() == true)
        return;
    else
    {
        QMap<int, SERIAL_DEV>::iterator iter = m_mapSerialDev.begin();
        while(iter != m_mapSerialDev.end())
        {
            if(_objThread[iter->ComIndex]->isRunning() == OK)
                emit signalDeviceStatus(iter->DevNum, true);
            else
                emit signalDeviceStatus(iter->DevNum, false);
            iter++;
        }
    }
}

int SerialApp::getPortIndex()
{
    int iResult = -1;
    if(m_mapSerialDev.isEmpty() == true)
        return 0;
    for(int index = 0; index < PORTS; index++)
    {
        QMap<int, SERIAL_DEV>::iterator iter = m_mapSerialDev.begin();
        while(iter != m_mapSerialDev.end())
        {
            if(iter->ComIndex == index)
            {
                iResult = -1;
                break;
            }
            else
            {
                iResult = index;
            }
            iter++;
        }
        if(iResult != -1)
            break;
    }
    return iResult;
}

int SerialApp::Open(int iDev, const void *_dev)
{
    if(_dev == nullptr)
        return ERROR;
    int baudrate = 9600;
    QSerialPort::DataBits data = QSerialPort::Data8;
    QSerialPort::Parity parity = QSerialPort::NoParity;
    QSerialPort::StopBits stop = QSerialPort::OneStop;
    if(m_mapSerialDev.contains(iDev) == true)
    {
        int index = m_mapSerialDev[iDev].ComIndex;
        const SERIAL_PROPERTIES* _serial = &static_cast<const SERIAL_DEV*>(_dev)->Properties;
        switch (_serial->m_Bandrate)
        {
        case SerialApp::BAUD2400:
            baudrate = 2400;
            break;
        case SerialApp::BAUD4800:
            baudrate = 4800;
            break;
        case SerialApp::BAUD9600:
            baudrate = 9600;
            break;
        case SerialApp::BAUD19200:
            baudrate = 19200;
            break;
        case SerialApp::BAUD115200:
            baudrate = 115200;
            break;
        default:
            baudrate = 9600;
            break;
        }
        _objComPort[index]->SetBandrate(baudrate);

        switch(_serial->m_DataBits)
        {
        case SerialApp::BIT7:
            data = QSerialPort::Data7;
            break;
        case SerialApp::BIT8:
            data = QSerialPort::Data8;
            break;
        default:
            data = QSerialPort::Data8;
            break;
        }
        _objComPort[index]->SetDataBits(data);

        switch(_serial->m_Parity)
        {
        case SerialApp::NONE:
            parity = QSerialPort::NoParity;
            break;
        case SerialApp::ODD:
            parity = QSerialPort::OddParity;
            break;
        case SerialApp::EVEN:
            parity = QSerialPort::EvenParity;
            break;
        default:
            parity = QSerialPort::NoParity;
            break;
        }
        _objComPort[index]->SetParity(parity);

        switch(_serial->m_StopBits)
        {
        case SerialApp::BIT1:
            stop = QSerialPort::OneStop;
            break;
        case SerialApp::BIT1_5:
            stop = QSerialPort::OneAndHalfStop;
            break;
        case SerialApp::BIT2:
            stop = QSerialPort::TwoStop;
            break;
        default:
            stop = QSerialPort::OneStop;
            break;
        }
        _objComPort[index]->SetStopBits(stop);
        _objComPort[index]->SetDevName(QString(Port[index]));
        _objComPort[index]->SetDevNum(iDev);
        _objThread[index]->start();
    }
    return OK;
}

int SerialApp::Close(int iDev)
{
    if(m_mapSerialDev.contains(iDev) == true)
    {
        int index = m_mapSerialDev[iDev].ComIndex;
        if(_objThread[index]->isRunning() == true)
        {
            _objThread[index]->quit();
            _objComPort[index]->SetDevNum(-1);
        }
        return OK;
    }
    else
        return ERROR;
}

int SerialApp::Attach(const int iDev, const int ProtocolType, const void *_dev)
{
    m_mutexDev.lock();
    SERIAL_DEV dev;
    dev.DevNum = iDev;
    dev.ComIndex = reinterpret_cast<const SERIAL_DEV*>(_dev)->ComIndex;
    switch(ProtocolType)
    {
    case Common::TC:
        dev._ptrProtocol = new TouchScreen();
        break;
    default:
        dev._ptrProtocol = new TouchScreen();
        break;
    }
    memcpy(&dev.Properties, &reinterpret_cast<const SERIAL_DEV*>(_dev)->Properties, sizeof(SERIAL_PROPERTIES));
    if(m_mapSerialDev.contains(iDev) == false)
    {
        m_mapSerialDev.insert(iDev, dev);
    }
    else
    {
        m_mapSerialDev[iDev].DevNum = dev.DevNum;
        if(m_mapSerialDev[iDev]._ptrProtocol != nullptr)
        {
            delete m_mapSerialDev[iDev]._ptrProtocol;
            m_mapSerialDev[iDev]._ptrProtocol = dev._ptrProtocol;
        }
        memcpy(&m_mapSerialDev[iDev].Properties, &dev.Properties, sizeof(SERIAL_PROPERTIES));
    }
    m_mutexDev.unlock();
    return OK;
}

int SerialApp::Detach(const int iDev)
{
    int iResult = ERROR;
    m_mutexDev.lock();
    if(m_mapSerialDev.contains(iDev) == false)
        iResult = ERROR;
    else
    {
        Close(iDev);
        if(m_mapSerialDev[iDev]._ptrProtocol != nullptr)
        {
            delete m_mapSerialDev[iDev]._ptrProtocol;
            m_mapSerialDev[iDev]._ptrProtocol = nullptr;
        }
        m_mapSerialDev.remove(iDev);
    }
    m_mutexDev.unlock();
    return iResult;
}

SerialApp *SerialApp::GetInstance()
{
    return (_SerialApp != nullptr) ? _SerialApp : (_SerialApp = new SerialApp());
}
