#include "ethernetapp.h"
#include "../protocol/common.h"
#include "../protocol/versagraphic.h"
#include <QThread>
#include <QTimerEvent>
#include <QDebug>
EthernetApp*    EthernetApp::_EthernetApp       = nullptr;
W5500*          EthernetApp::_W5500             = nullptr;
Ethernet*       EthernetApp::_Socket[ETHS] = {nullptr, nullptr, nullptr, nullptr};
QMap<int,       EthernetApp::ETHERNET_DEV> EthernetApp::m_mapEthernetDev;
unsigned char EthernetApp::Gateway[4]    = {192, 168, 10, 1};
unsigned char EthernetApp::LocalIP[4]    = {192, 168, 10, 38};
constexpr unsigned char EthernetApp::SUBNET_MASK[4];
EthernetApp::EthernetApp(QObject *parent)
    : InterfaceApp{parent}
{
    Board_CM3* _board = Board_CM3::GetInstance();
    if(_board->GetBoardStatus() == false)
    {
        qDebug()<<"Board initialization falure";
        return;
    }

    Ethernet::Reset_W5500();
    Ethernet::Reset_Route();
    _W5500 = W5500::GetInstance();

    Ethernet::Set_Local_Eth0(LocalIP, Gateway, SUBNET_MASK);

    QThread::sleep(5);
    for(int i = 0; i < ETHS; i++)
    {
        _Socket[i] = new Ethernet(static_cast<Ethernet::SOCKET_DEVICE>(Ethernet::SOCKET1 + i));
        connect(_Socket[i], SIGNAL(signalResultReady(int,QString)), this, SLOT(slotParseWeldResult(int,QString)));
    }
    m_mapEthernetDev.clear();
    this->startTimer(1000);
}

int EthernetApp::getSocketIndex()
{
    int iResult = -1;
    if(m_mapEthernetDev.isEmpty() == true)
        return 0;
    for(int index = 0; index < ETHS; index++)
    {
        QMap<int, ETHERNET_DEV>::iterator iter = m_mapEthernetDev.begin();
        while(iter != m_mapEthernetDev.end())
        {
            if(iter->SocketIndex == index)
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

void EthernetApp::slotParseWeldResult(int iDev, QString strResult)
{
    m_mutexWeldResult.lock();
    if(m_mapEthernetDev.contains(iDev) == true)
    {
        if(m_mapEthernetDev[iDev]._ptrProtocol != nullptr)
        {
            if(m_mapEthernetDev[iDev]._ptrProtocol->ParseWeldResult(strResult) == OK)
                emit signalWeldResultReady(iDev, m_mapEthernetDev[iDev]._ptrProtocol);
        }
    }
    m_mutexWeldResult.unlock();
}

EthernetApp *EthernetApp::GetInstance()
{
    return (_EthernetApp != nullptr) ? _EthernetApp : (_EthernetApp = new EthernetApp());
}

EthernetApp::~EthernetApp()
{
    for(int i = 0; i < ETHS; i++)
    {
        _Socket[i]->Close_TCP_Socket();
        delete _Socket[i];
        _Socket[i] = nullptr;
    }
    delete _W5500;
}

int EthernetApp::Init(const void *_dev)
{
    if(_dev == nullptr)
        return ERROR;
    m_mutexDev.lock();
    if(memcmp(static_cast<const ETHERNET_DEV*>(_dev)->Properties.LocalAddr, LocalIP, 4) != 0)
    {
        Board_CM3* _board = Board_CM3::GetInstance();
        if(_board->GetBoardStatus() == false)
            return ERROR;
        Ethernet::Reset_W5500();
        Ethernet::Reset_Route();
        memcpy(LocalIP, static_cast<const ETHERNET_DEV*>(_dev)->Properties.LocalAddr, 4);
        memcpy(Gateway, LocalIP, 4);
        Gateway[3] = 1;
        Ethernet::Set_Local_Eth0(LocalIP, Gateway, SUBNET_MASK);

        for(int i = 0; i < ETHS; i++)
            _Socket[i]->Close_TCP_Socket();
        static QMap<int, ETHERNET_DEV>::iterator iter = m_mapEthernetDev.begin();
        while(iter != m_mapEthernetDev.end())
        {
            if(iter->_ptrProtocol != nullptr)
            {
                delete iter->_ptrProtocol;
                iter->_ptrProtocol = nullptr;
            }
            iter++;
        }
        m_mapEthernetDev.clear();
    }
    m_mutexDev.unlock();
    return OK;
}

int EthernetApp::Open(int iDev, const void *_dev)
{
    if(_dev == nullptr)
        return ERROR;
    if(m_mapEthernetDev.contains(iDev) == true)
    {
        int index = m_mapEthernetDev[iDev].SocketIndex;
        const TCP_PROPERTIES* _tcp = reinterpret_cast<const TCP_PROPERTIES*>(&m_mapEthernetDev[iDev].Properties);
        _Socket[index]->Open_TCP_Socket(_tcp->ServerAddr, _tcp->ServerPort);
        _Socket[index]->SetDevNum(iDev);
    }
    return OK;
}

int EthernetApp::Close(int iDev)
{
    if(m_mapEthernetDev.contains(iDev) == true)
    {
        int index = m_mapEthernetDev[iDev].SocketIndex;
        _Socket[index]->Close_TCP_Socket();
        _Socket[index]->SetDevNum(-1);
        return OK;
    }
    else
        return ERROR;
}

int EthernetApp::Attach(const int iDev, const int ProtocolType, const void *_dev)
{
    m_mutexDev.lock();
    ETHERNET_DEV dev;
    dev.DevNum = iDev;
    dev.SocketIndex = getSocketIndex();
    switch(ProtocolType)
    {
    case Common::VG_TCP:
        dev._ptrProtocol = new Versagraphic();
        break;
    case Common::DP2000X_TCP:
        break;
    default:
        dev._ptrProtocol = new Versagraphic();
        break;
    }
    memcpy(&dev.Properties, &static_cast<const ETHERNET_DEV*>(_dev)->Properties, sizeof(TCP_PROPERTIES));

    if(m_mapEthernetDev.contains(iDev) == false)
    {
        m_mapEthernetDev.insert(iDev,dev);
    }
    else
    {
        m_mapEthernetDev[iDev].DevNum = dev.DevNum;
        if(m_mapEthernetDev[iDev]._ptrProtocol != nullptr)
        {
            delete m_mapEthernetDev[iDev]._ptrProtocol;
            m_mapEthernetDev[iDev]._ptrProtocol = dev._ptrProtocol;
        }
        memcpy(&m_mapEthernetDev[iDev].Properties, &dev.Properties, sizeof(TCP_PROPERTIES));
    }
    m_mutexDev.unlock();
    return OK;
}

int EthernetApp::Detach(const int iDev)
{
    int iResult = ERROR;
    m_mutexDev.lock();
    if(m_mapEthernetDev.contains(iDev) == false)
        iResult = ERROR;
    else
    {
        Close(iDev);
        if(m_mapEthernetDev[iDev]._ptrProtocol != nullptr)
        {
            delete m_mapEthernetDev[iDev]._ptrProtocol;
            m_mapEthernetDev[iDev]._ptrProtocol = nullptr;
        }
        m_mapEthernetDev.remove(iDev);
    }
    m_mutexDev.unlock();
    return iResult;
}

int EthernetApp::Update(const int iDev, const Common::WELD_SETTING *_setting)
{
    int iResult = ERROR;
    if(_setting == nullptr)
        return iResult;
    if(m_mapEthernetDev.contains(iDev) == true)
    {
        if(m_mapEthernetDev[iDev]._ptrProtocol != nullptr)
        {
            m_mapEthernetDev[iDev]._ptrProtocol->SetWeldSetting(_setting);
            iResult = OK;
        }
    }
    return iResult;
}

void EthernetApp::timerEvent(QTimerEvent *event)
{
    if(m_mapEthernetDev.isEmpty() == true)
        return;
    else
    {
        QMap<int, ETHERNET_DEV>::iterator iter = m_mapEthernetDev.begin();
        while(iter != m_mapEthernetDev.end())
        {
            bool status = false;
            if(_Socket[iter->SocketIndex]->GetStatus() == W5500::SOCK_ESTABLISHED)
                status = true;
            else
                status = false;
            emit signalDeviceStatus(iter->DevNum, status);
            iter++;
        }
    }
}
