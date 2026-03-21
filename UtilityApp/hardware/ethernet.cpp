#include "ethernet.h"
#include "board_cm3.h"
#include "definition.h"
#include <QDebug>
Ethernet::Ethernet(const SOCKET_DEVICE socketNumber)
{
    m_SocketNum = socketNumber;
    m_iDevNum = -1;
    m_iStatus = W5500::SOCKET_CLOSED;
    m_timeID = -1;
    m_objThreadHandler = new QThread();
}

Ethernet::Ethernet()
{
    if(m_objThreadHandler->isRunning() == true)
    {
        m_objThreadHandler->quit();
        m_objThreadHandler->deleteLater();
    }
}

int Ethernet::Reset_W5500()
{
    if(Board_CM3::GetInstance()->GetBoardStatus() == false)
        return ERROR;
    else
    {
#ifdef RASPBERRY
        bcm2835_gpio_fsel(W5500_RESET, BCM2835_GPIO_FSEL_OUTP);
        bcm2835_gpio_write(W5500_RESET, LOW);
        QThread::sleep(1);
        bcm2835_gpio_write(W5500_RESET, HIGH);
#endif
    }
    return OK;
}

int Ethernet::Reset_Route()
{
    if(Board_CM3::GetInstance()->GetBoardStatus() == false)
        return ERROR;
    else
    {
#ifdef RASPBERRY
        bcm2835_gpio_fsel(ROUTE_RESET, BCM2835_GPIO_FSEL_OUTP);
        bcm2835_gpio_write(ROUTE_RESET, LOW);
        QThread::sleep(1);
        bcm2835_gpio_write(ROUTE_RESET, HIGH);
#endif
    }
    return OK;
}

int Ethernet::Set_Local_Eth0( const unsigned char* localIP, const unsigned char* gateway, const unsigned char* subnetMask)
{
    W5500* _w5500 = W5500::GetInstance();
    qDebug() << "Version1: " << _w5500->GetRegister(W5500::COMMON_REGISTER, W5500::VERSIONR);
//    qDebug() << "Set Mode: " << _w5500->SetRegister(W5500::COMMON_REGISTER, W5500::MR, 0x10);
    QThread::sleep(1);
    qDebug() << "Mode: " << _w5500->GetRegister(W5500::COMMON_REGISTER, W5500::MR);

    _w5500->SetGatewayIPAddress(gateway);
    unsigned char tmpGateway[4];
    memset(tmpGateway, 0, 4);
    _w5500->GetGatewayIPAddress(tmpGateway);
    for(int i = 0; i < 4; i++)
    {
        qDebug() << "Gateway Add[" << i << "] = " << tmpGateway[i];
    }

    _w5500->SetSubnetMask(subnetMask);
    unsigned char tmpSubnetMask[4];
    memset(tmpSubnetMask, 0, 4);
    _w5500->GetSubnetMask(tmpSubnetMask);
    for(int i = 0; i < 4; i++)
    {
        qDebug() << "Subnet Mask[" << i << "] = " << tmpSubnetMask[i];
    }

    qDebug() << "MAC0: " << _w5500->GetRegister(W5500::COMMON_REGISTER, W5500::SHAR0);
    qDebug() << "MAC1: " << _w5500->GetRegister(W5500::COMMON_REGISTER, W5500::SHAR1);
    qDebug() << "MAC2: " << _w5500->GetRegister(W5500::COMMON_REGISTER, W5500::SHAR2);
    qDebug() << "MAC3: " << _w5500->GetRegister(W5500::COMMON_REGISTER, W5500::SHAR3);
    qDebug() << "MAC4: " << _w5500->GetRegister(W5500::COMMON_REGISTER, W5500::SHAR4);
    qDebug() << "MAC5: " << _w5500->GetRegister(W5500::COMMON_REGISTER, W5500::SHAR5);
    unsigned char MAC[6] = {0x00, 0x08, 0xDC, 0x01, 0x02, 0x03};
    _w5500->SetMacAddress(MAC);
    memset(MAC, 0, 6);
    _w5500->GetMacAddress(MAC);
    for(int i = 0; i < 6; i++)
    {
        qDebug() << "MAC Address[" << i << "] = " << MAC[i];
    }


    _w5500->SetLocalIPAddress(localIP);
    unsigned char tmpLocalIP[4];
    memset(tmpLocalIP, 0, 4);
    _w5500->GetLocalIPAddress(tmpLocalIP);
    for(int i = 0; i < 4; i++)
    {
        qDebug() << "Local IP[" << i << "] = " << tmpLocalIP[i];
    }

    return OK;
}

int Ethernet::set_Socket_Server(const unsigned char *targetIP, const unsigned short targetPort)
{
    int iResult = ERROR;
    unsigned char reg = W5500::SOCKET_0_REGISTER;
    if(m_SocketNum == Ethernet::SOCKET0)
        return iResult;
    switch(m_SocketNum)
    {
    case SOCKET1:
        reg = W5500::SOCKET_1_REGISTER;
        iResult = OK;
        break;
    case SOCKET2:
        reg = W5500::SOCKET_2_REGISTER;
        iResult = OK;
        break;
    case SOCKET3:
        reg = W5500::SOCKET_3_REGISTER;
        iResult = OK;
        break;
    case SOCKET4:
        reg = W5500::SOCKET_4_REGISTER;
        iResult = OK;
        break;
    case SOCKET5:
        reg = W5500::SOCKET_5_REGISTER;
        iResult = OK;
        break;
    case SOCKET6:
        reg = W5500::SOCKET_6_REGISTER;
        iResult = OK;
        break;
    case SOCKET7:
        reg = W5500::SOCKET_7_REGISTER;
        iResult = OK;
        break;
    default:
        iResult = ERROR;
    }
    if(iResult == ERROR)
        return iResult;

    W5500* _w5500 = W5500::GetInstance();
    _w5500->SetTargetIPAddress(reg, targetIP);
    _w5500->SetTargetPort(reg, targetPort);
    return iResult;
}

int Ethernet::get_Socket_Server(unsigned char *targetIP, unsigned short *targetPort) const
{
    int iResult = ERROR;
    if(targetIP == nullptr)
        return iResult;
    if(targetPort == nullptr)
        return iResult;
    unsigned char reg = W5500::SOCKET_0_REGISTER;
    if(m_SocketNum == Ethernet::SOCKET0)
        return iResult;
    switch(m_SocketNum)
    {
    case SOCKET1:
        reg = W5500::SOCKET_1_REGISTER;
        iResult = OK;
        break;
    case SOCKET2:
        reg = W5500::SOCKET_2_REGISTER;
        iResult = OK;
        break;
    case SOCKET3:
        reg = W5500::SOCKET_3_REGISTER;
        iResult = OK;
        break;
    case SOCKET4:
        reg = W5500::SOCKET_4_REGISTER;
        iResult = OK;
        break;
    case SOCKET5:
        reg = W5500::SOCKET_5_REGISTER;
        iResult = OK;
        break;
    case SOCKET6:
        reg = W5500::SOCKET_6_REGISTER;
        iResult = OK;
        break;
    case SOCKET7:
        reg = W5500::SOCKET_7_REGISTER;
        iResult = OK;
        break;
    default:
        iResult = ERROR;
    }
    if(iResult == ERROR)
        return iResult;

    W5500* _w5500 = W5500::GetInstance();
    if(_w5500->GetTargetIPAddress(reg, targetIP) == OK)
    {
        for(int i = 0; i < 4; i++)
        {
            qDebug() << "Target IP[" << i << "] = " << targetIP[i];
        }
    }
    if(_w5500->GetTargetPort(reg, targetPort) == 0)
        qDebug() << "Target Port = " << *targetPort;
    return iResult;
}

int Ethernet::set_Local_Port(const unsigned short localPort)
{
    int iResult = ERROR;
    unsigned char reg = W5500::SOCKET_0_REGISTER;
    if(m_SocketNum == Ethernet::SOCKET0)
        return iResult;
    switch(m_SocketNum)
    {
    case SOCKET1:
        reg = W5500::SOCKET_1_REGISTER;
        iResult = OK;
        break;
    case SOCKET2:
        reg = W5500::SOCKET_2_REGISTER;
        iResult = OK;
        break;
    case SOCKET3:
        reg = W5500::SOCKET_3_REGISTER;
        iResult = OK;
        break;
    case SOCKET4:
        reg = W5500::SOCKET_4_REGISTER;
        iResult = OK;
        break;
    case SOCKET5:
        reg = W5500::SOCKET_5_REGISTER;
        iResult = OK;
        break;
    case SOCKET6:
        reg = W5500::SOCKET_6_REGISTER;
        iResult = OK;
        break;
    case SOCKET7:
        reg = W5500::SOCKET_7_REGISTER;
        iResult = OK;
        break;
    default:
        iResult = ERROR;
    }
    if(iResult == ERROR)
        return iResult;

    W5500* _w5500 = W5500::GetInstance();
    _w5500->SetLocalPort(reg, localPort);
    unsigned short tmpLocalPort = 0;
    _w5500->GetLocalPort(reg, &tmpLocalPort);
    qDebug() << "Local Port = " << tmpLocalPort;
    return iResult;
}

int Ethernet::open_TCP_Socket(const W5500::PROTOCOL_MODE mode)
{
    int iResult = OK;
    unsigned char reg = 0;
    W5500* _w5500 = W5500::GetInstance();
    switch(m_SocketNum)
    {
    case SOCKET0:
        reg = W5500::SOCKET_0_REGISTER;
        break;
    case SOCKET1:
        reg = W5500::SOCKET_1_REGISTER;
        break;
    case SOCKET2:
        reg = W5500::SOCKET_2_REGISTER;
        break;
    case SOCKET3:
        reg = W5500::SOCKET_3_REGISTER;
        break;
    case SOCKET4:
        reg = W5500::SOCKET_4_REGISTER;
        break;
    case SOCKET5:
        reg = W5500::SOCKET_5_REGISTER;
        break;
    case SOCKET6:
        reg = W5500::SOCKET_6_REGISTER;
        break;
    case SOCKET7:
        reg = W5500::SOCKET_7_REGISTER;
        break;
    default:
        iResult = ERROR;
        break;
    }
    if(iResult == ERROR)
        return iResult;

    if(mode == W5500::TCP)
    {
        // Only for Client Mode
        // Set the socket mode to TCP
        qDebug() << "Set TCP Mode: " << _w5500->SetRegister(reg, W5500::Sn_MR, mode);
        // Open the socket
        qDebug() << "Open Socket: " << _w5500->SetRegister(reg, W5500::Sn_CR, W5500::OPEN);
    }
    else
        iResult = ERROR;
    return iResult;
}

int Ethernet::connect_TCP_Socket()
{
    int iResult = OK;
    unsigned char reg = 0;
    W5500* _w5500 = W5500::GetInstance();
    switch(m_SocketNum)
    {
    case SOCKET0:
        reg = W5500::SOCKET_0_REGISTER;
        break;
    case SOCKET1:
        reg = W5500::SOCKET_1_REGISTER;
        break;
    case SOCKET2:
        reg = W5500::SOCKET_2_REGISTER;
        break;
    case SOCKET3:
        reg = W5500::SOCKET_3_REGISTER;
        break;
    case SOCKET4:
        reg = W5500::SOCKET_4_REGISTER;
        break;
    case SOCKET5:
        reg = W5500::SOCKET_5_REGISTER;
        break;
    case SOCKET6:
        reg = W5500::SOCKET_6_REGISTER;
        break;
    case SOCKET7:
        reg = W5500::SOCKET_7_REGISTER;
        break;
    default:
        iResult = ERROR;
        break;
    }
    if(iResult == ERROR)
        return iResult;

    if(_w5500->GetRegister(reg, W5500::Sn_MR) == W5500::TCP)
        qDebug() << "Connect Socket: " << _w5500->SetRegister(reg, W5500::Sn_CR, W5500::CONNECT);
    else
        iResult = ERROR;
    return iResult;
}

int Ethernet::receive_TCP_Socket(unsigned char *_buffer)
{
    if(_buffer == nullptr)
        return ERROR;
    int iResult = OK;
    unsigned char reg = 0;
    W5500* _w5500 = W5500::GetInstance();
    switch(m_SocketNum)
    {
    case SOCKET0:
        reg = W5500::SOCKET_0_REGISTER;
        break;
    case SOCKET1:
        reg = W5500::SOCKET_1_REGISTER;
        break;
    case SOCKET2:
        reg = W5500::SOCKET_2_REGISTER;
        break;
    case SOCKET3:
        reg = W5500::SOCKET_3_REGISTER;
        break;
    case SOCKET4:
        reg = W5500::SOCKET_4_REGISTER;
        break;
    case SOCKET5:
        reg = W5500::SOCKET_5_REGISTER;
        break;
    case SOCKET6:
        reg = W5500::SOCKET_6_REGISTER;
        break;
    case SOCKET7:
        reg = W5500::SOCKET_7_REGISTER;
        break;
    default:
        iResult = ERROR;
        break;
    }
    if(iResult == ERROR)
        return iResult;

    unsigned short rx_size = 0;
    unsigned short rx_read_pointer = 0;
    unsigned short rx_address = 0;
    // Check how many data in rx buffer
    _w5500->GetShortRegister(reg, W5500::Sn_RX_RSR0, &rx_size);
//    qDebug() << "Rx Size: " << rx_size;

    if(rx_size == 0)
        return 0;

    // Get current receive pointer
    _w5500->GetShortRegister(reg, W5500::Sn_RX_RD0, &rx_read_pointer);
    qDebug() << "Rx Read Pointer: " << rx_read_pointer;

    //
    rx_address = rx_read_pointer & 0xFFFF;

    // Get data from rx buffer
    for(int i = 0; i < rx_size; i++)
    {
        _buffer[i] = _w5500->GetRegister(reg + RX_REG_OFFSET, rx_address + i);
    }

    // Update rx pointer
    rx_read_pointer += rx_size;
    _w5500->SetShortRegister(reg, W5500::Sn_RX_RD0, rx_read_pointer);

    // Notify W5500 data has been read
    _w5500->SetRegister(reg, W5500::Sn_CR, W5500::RECV);
    return rx_size;
}

int Ethernet::get_TCP_Status()
{
    int iResult = OK;
    unsigned char reg = 0;
    W5500* _w5500 = W5500::GetInstance();
    switch(m_SocketNum)
    {
    case SOCKET0:
        reg = W5500::SOCKET_0_REGISTER;
        break;
    case SOCKET1:
        reg = W5500::SOCKET_1_REGISTER;
        break;
    case SOCKET2:
        reg = W5500::SOCKET_2_REGISTER;
        break;
    case SOCKET3:
        reg = W5500::SOCKET_3_REGISTER;
        break;
    case SOCKET4:
        reg = W5500::SOCKET_4_REGISTER;
        break;
    case SOCKET5:
        reg = W5500::SOCKET_5_REGISTER;
        break;
    case SOCKET6:
        reg = W5500::SOCKET_6_REGISTER;
        break;
    case SOCKET7:
        reg = W5500::SOCKET_7_REGISTER;
        break;
    default:
        iResult = ERROR;
        break;
    }
    if(iResult == ERROR)
        return iResult;
    return _w5500->GetRegister(reg, W5500::Sn_SR);
}

int Ethernet::Open_TCP_Socket(const unsigned char *targeetIP, const unsigned short targetPort)
{
    this->set_Local_Port(targetPort);
    this->set_Socket_Server(targeetIP, targetPort);
    this->open_TCP_Socket(W5500::TCP);
    this->connect_TCP_Socket();
    m_timeID = this->startTimer(1000);   // 1-second timer
    return 0;
}

int Ethernet::Close_TCP_Socket()
{
    if(m_timeID != -1)
    {
        this->killTimer(m_timeID);
        m_timeID = -1;
    }
    return this->close_TCP_Socket();
}

void Ethernet::SetDevNum(const int devNum)
{
    m_iDevNum = devNum;
}

int Ethernet::GetDevNum() const
{
    return m_iDevNum;
}

unsigned char Ethernet::GetStatus() const
{
    return m_iStatus;
}

void Ethernet::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    // qDebug() << "Timer ID:" << event->timerId();

    // qDebug() << "PHY: " << _W5500->GetRegister(W5500::COMMON_REGISTER, W5500::PHYCFGR);
    unsigned status = this->get_TCP_Status();
    int receivedSize = -1;
    m_iStatus = status;
    switch(status)
    {
    case W5500::SOCKET_CLOSED:
        this->open_TCP_Socket(W5500::TCP);
        break;
    case W5500::SOCK_INIT:
        this->connect_TCP_Socket();
        break;
    case W5500::SOCK_ESTABLISHED:
        // _Socket1->Get_Socket_Server(TargetIP_1, &TargetPort_1);
        memset(_Recv_buffer, 0, 2048);
        receivedSize = this->receive_TCP_Socket(_Recv_buffer);
        if(receivedSize > 0)
        {
            m_strBuffer.clear();
            m_strBuffer = QString::fromLatin1(reinterpret_cast<const char*>(_Recv_buffer), receivedSize);

            emit signalResultReady(m_iDevNum, m_strBuffer); //Send the signal to Serial APP
            qDebug() << m_strBuffer;
        }
        break;
    case W5500::SOCK_CLOSE_WAIT:
        this->close_TCP_Socket();
        break;
    default:
        qDebug() << "Status: " << status;
        break;
    }
}

int Ethernet::close_TCP_Socket()
{
    int iResult = OK;
    unsigned char reg = 0;
    W5500* _w5500 = W5500::GetInstance();
    switch(m_SocketNum)
    {
    case SOCKET0:
        reg = W5500::SOCKET_0_REGISTER;
        break;
    case SOCKET1:
        reg = W5500::SOCKET_1_REGISTER;
        break;
    case SOCKET2:
        reg = W5500::SOCKET_2_REGISTER;
        break;
    case SOCKET3:
        reg = W5500::SOCKET_3_REGISTER;
        break;
    case SOCKET4:
        reg = W5500::SOCKET_4_REGISTER;
        break;
    case SOCKET5:
        reg = W5500::SOCKET_5_REGISTER;
        break;
    case SOCKET6:
        reg = W5500::SOCKET_6_REGISTER;
        break;
    case SOCKET7:
        reg = W5500::SOCKET_7_REGISTER;
        break;
    default:
        iResult = ERROR;
        break;
    }
    if(iResult == ERROR)
        return iResult;

    return _w5500->SetRegister(reg, W5500::Sn_CR, W5500::CLOSE);
}
