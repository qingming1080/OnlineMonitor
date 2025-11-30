#include "w5500.h"
#include "../definition.h"
#include <QDebug>
#ifdef RASPBERRY
#include <bcm2835.h>
#endif
W5500* W5500::_w5500 = nullptr;
QMutex  W5500::m_Mutex;
W5500 *W5500::GetInstance()
{
    m_Mutex.lock();
    if(_w5500 == nullptr)
        _w5500 = new W5500();
    m_Mutex.unlock();
    return _w5500;
}

W5500::~W5500()
{
#ifdef RASPBERRY
    m_Mutex.lock();
    bcm2835_aux_spi_end();
    m_Mutex.unlock();
#endif
}

bool W5500::GetW5500Status() const
{
    return true;
}

W5500::W5500(QObject *parent)
    : QObject{parent}
{
#ifdef RASPBERRY
    if(bcm2835_aux_spi_begin() == 0)
    {
        qDebug()<<"W5500 initilization is failure";
        return;
    }
    else
    {
        bcm2835_aux_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_8);
        bcm2835_gpio_fsel(CS_GPIO, BCM2835_GPIO_FSEL_OUTP);
        bcm2835_gpio_write(CS_GPIO, HIGH);
        qDebug()<<"W5500 initialization is successful";
    }
#endif
}

int W5500::GetVersionNumber() const
{
    m_Mutex.lock();
    FRAME_VERSION tmpFrame;
    tmpFrame.AddressPhaseH = (VERSIONR>>8);
    tmpFrame.AddressPhaseL = VERSIONR & 0x00FF;
    tmpFrame.ControlPhase.Bits.BSB  = COMMON_REGISTER;
    tmpFrame.ControlPhase.Bits.RWB  = READ_MODE;
    tmpFrame.ControlPhase.Bits.OM   = ONE_BYTE_DATA_LENGTH_MODE;
    tmpFrame.Version = 0;

    int length = sizeof(FRAME_VERSION);
#ifdef RASPBERRY
    bcm2835_gpio_write(CS_GPIO, LOW);
    bcm2835_aux_spi_transfern((char*)(&tmpFrame), length);
    bcm2835_gpio_write(CS_GPIO, HIGH);
#else
    unsigned char _recv[4] = {0};
    memcpy(_recv, &tmpFrame, length);
#endif
    m_Mutex.unlock();
    return tmpFrame.Version;
}

int W5500::GetRegister(const unsigned char reg, const unsigned short add) const
{
    m_Mutex.lock();
    FRAME_ONE_BYTE tmpFrame;
    tmpFrame.AddressPhaseH = (add>>8);
    tmpFrame.AddressPhaseL = add & 0x00FF;
    tmpFrame.ControlPhase.Bits.BSB  = reg;
    tmpFrame.ControlPhase.Bits.RWB  = READ_MODE;
    tmpFrame.ControlPhase.Bits.OM   = ONE_BYTE_DATA_LENGTH_MODE;
    tmpFrame.Data = 0;

    int length = sizeof(FRAME_ONE_BYTE);
#ifdef RASPBERRY
    bcm2835_gpio_write(CS_GPIO, LOW);
    bcm2835_aux_spi_transfern((char*)(&tmpFrame), length);
    bcm2835_gpio_write(CS_GPIO, HIGH);
#else
    unsigned char _recv[4] = {0};
    memcpy(_recv, &tmpFrame, length);
#endif
    m_Mutex.unlock();
    return tmpFrame.Data;
}

int W5500::SetRegister(const unsigned char reg, const unsigned short add, unsigned char data)
{
    m_Mutex.lock();
    FRAME_ONE_BYTE tmpFrame;
    tmpFrame.AddressPhaseH = (add>>8);
    tmpFrame.AddressPhaseL = add & 0x00FF;
    tmpFrame.ControlPhase.Bits.BSB  = reg;
    tmpFrame.ControlPhase.Bits.RWB  = WRITE_MODE;
    tmpFrame.ControlPhase.Bits.OM   = ONE_BYTE_DATA_LENGTH_MODE;
    tmpFrame.Data = data;

    int length = sizeof(FRAME_ONE_BYTE);
#ifdef RASPBERRY
    bcm2835_gpio_write(CS_GPIO, LOW);
    bcm2835_aux_spi_writenb((const char*)(&tmpFrame), length);
    bcm2835_gpio_write(CS_GPIO, HIGH);
#else
    unsigned char _recv[4] = {0};
    memcpy(_recv, &tmpFrame, length);
#endif
    m_Mutex.unlock();
    return tmpFrame.Data;
}

int W5500::GetGatewayIPAddress(unsigned char *add) const
{
    m_Mutex.lock();
    int iResult = ERROR;
    if(add != nullptr)
    {
        FRAME_IP_ADDRESS tmpFrame;
        tmpFrame.AddressPhaseH = (GAR0 >> 8);
        tmpFrame.AddressPhaseL = GAR0 & 0x00FF;
        tmpFrame.ControlPhase.Bits.BSB = COMMON_REGISTER;
        tmpFrame.ControlPhase.Bits.RWB = READ_MODE;
        tmpFrame.ControlPhase.Bits.OM = FOUR_BYTES_DATA_LENGTH_MODE;
        memset(tmpFrame.IP, 0, 4);

        int length = sizeof(FRAME_IP_ADDRESS);
#ifdef RASPBERRY
        bcm2835_gpio_write(CS_GPIO, LOW);
        bcm2835_aux_spi_transfern((char*)(&tmpFrame), length);
        bcm2835_gpio_write(CS_GPIO, HIGH);
#else
        unsigned char _recv[7] = {0};
        memcpy(_recv, &tmpFrame, length);
#endif
        memcpy(add, tmpFrame.IP, 4);
        iResult = OK;
    }
    m_Mutex.unlock();
    return iResult;
}

int W5500::SetGatewayIPAddress(const unsigned char *add)
{
    m_Mutex.lock();
    int iResult = ERROR;
    if(add != nullptr)
    {
        FRAME_IP_ADDRESS tmpFrame;
        tmpFrame.AddressPhaseH = (GAR0 >> 8);
        tmpFrame.AddressPhaseL = GAR0 & 0x00FF;
        tmpFrame.ControlPhase.Bits.BSB = COMMON_REGISTER;
        tmpFrame.ControlPhase.Bits.RWB = WRITE_MODE;
        tmpFrame.ControlPhase.Bits.OM = FOUR_BYTES_DATA_LENGTH_MODE;
        memset(tmpFrame.IP, 0, 4);
        memcpy(tmpFrame.IP, add, 4);

        int length = sizeof(FRAME_IP_ADDRESS);
#ifdef RASPBERRY
        bcm2835_gpio_write(CS_GPIO, LOW);
        bcm2835_aux_spi_writenb((const char*)(&tmpFrame), length);
        bcm2835_gpio_write(CS_GPIO, HIGH);
#else
        unsigned char _recv[7] = {0};
        memcpy(_recv, &tmpFrame, length);

#endif
        iResult = OK;
    }
    m_Mutex.unlock();
    return iResult;
}

int W5500::GetSubnetMask(unsigned char *add) const
{
    m_Mutex.lock();
    int iResult = ERROR;
    if(add != nullptr)
    {
        FRAME_IP_ADDRESS tmpFrame;
        tmpFrame.AddressPhaseH = (SUBR0 >> 8);
        tmpFrame.AddressPhaseL = SUBR0 & 0x00FF;
        tmpFrame.ControlPhase.Bits.BSB = COMMON_REGISTER;
        tmpFrame.ControlPhase.Bits.RWB = READ_MODE;
        tmpFrame.ControlPhase.Bits.OM = FOUR_BYTES_DATA_LENGTH_MODE;
        memset(tmpFrame.IP, 0, 4);

        int length = sizeof(FRAME_IP_ADDRESS);
#ifdef RASPBERRY
        bcm2835_gpio_write(CS_GPIO, LOW);
        bcm2835_aux_spi_transfern((char*)(&tmpFrame), length);
        bcm2835_gpio_write(CS_GPIO, HIGH);
#else
        unsigned char _recv[7] = {0};
        memcpy(_recv, &tmpFrame, length);
#endif
        memcpy(add, tmpFrame.IP, 4);
        iResult = OK;
    }
    m_Mutex.unlock();
    return iResult;
}

int W5500::SetSubnetMask(const unsigned char *add)
{
    m_Mutex.lock();
    int iResult = ERROR;
    if(add != nullptr)
    {
        FRAME_IP_ADDRESS tmpFrame;
        tmpFrame.AddressPhaseH = (SUBR0 >> 8);
        tmpFrame.AddressPhaseL = SUBR0 & 0x00FF;
        tmpFrame.ControlPhase.Bits.BSB = COMMON_REGISTER;
        tmpFrame.ControlPhase.Bits.RWB = WRITE_MODE;
        tmpFrame.ControlPhase.Bits.OM = FOUR_BYTES_DATA_LENGTH_MODE;
        memset(tmpFrame.IP, 0, 4);
        memcpy(tmpFrame.IP, add, 4);

        int length = sizeof(FRAME_IP_ADDRESS);
#ifdef RASPBERRY
        bcm2835_gpio_write(CS_GPIO, LOW);
        bcm2835_aux_spi_writenb((const char*)(&tmpFrame), length);
        bcm2835_gpio_write(CS_GPIO, HIGH);
#else
        unsigned char _recv[7] = {0};
        memcpy(_recv, &tmpFrame, length);
#endif
        iResult = OK;
    }
    m_Mutex.unlock();
    return iResult;
}

int W5500::GetMacAddress(unsigned char *add) const
{
    m_Mutex.lock();
    int iResult = ERROR;
    if(add != nullptr)
    {
        FRAME_MAC_ADDRESS tmpFrame;
        tmpFrame.AddressPhaseH = (SHAR0 >> 8);
        tmpFrame.AddressPhaseL = SHAR0 & 0x00FF;
        tmpFrame.ControlPhase.Bits.BSB = COMMON_REGISTER;
        tmpFrame.ControlPhase.Bits.RWB = READ_MODE;
        tmpFrame.ControlPhase.Bits.OM = VARIABLE_DATA_LENGTH_MODE;
        memset(tmpFrame.MAC, 0, 6);

        int length = sizeof(FRAME_MAC_ADDRESS);
#ifdef RASPBERRY
        bcm2835_gpio_write(CS_GPIO, LOW);
        bcm2835_aux_spi_transfern((char*)(&tmpFrame), length);
        bcm2835_gpio_write(CS_GPIO, HIGH);
#else
        unsigned char _recv[9] = {0};
        memcpy(_recv, &tmpFrame, length);
#endif
        memcpy(add, tmpFrame.MAC, 6);
        iResult = OK;
    }
    m_Mutex.unlock();
    return iResult;
}

int W5500::SetMacAddress(const unsigned char *add)
{
    m_Mutex.lock();
    int iResult = ERROR;
    if(add != nullptr)
    {
        FRAME_MAC_ADDRESS tmpFrame;
        tmpFrame.AddressPhaseH = (SHAR0 >> 8);
        tmpFrame.AddressPhaseL = SHAR0 & 0x00FF;
        tmpFrame.ControlPhase.Bits.BSB = COMMON_REGISTER;
        tmpFrame.ControlPhase.Bits.RWB = WRITE_MODE;
        tmpFrame.ControlPhase.Bits.OM = VARIABLE_DATA_LENGTH_MODE;
        memset(tmpFrame.MAC, 0, 6);
        memcpy(tmpFrame.MAC, add, 6);

        int length = sizeof(FRAME_IP_ADDRESS);
#ifdef RASPBERRY
        bcm2835_gpio_write(CS_GPIO, LOW);
        bcm2835_aux_spi_writenb((const char*)(&tmpFrame), length);
        bcm2835_gpio_write(CS_GPIO, HIGH);
#else
        unsigned char _recv[9] = {0};
        memcpy(_recv, &tmpFrame, length);
#endif
        iResult = OK;
    }
    m_Mutex.unlock();
    return iResult;
}

int W5500::GetLocalIPAddress(unsigned char *add) const
{
    m_Mutex.lock();
    int iResult = ERROR;
    if(add != nullptr)
    {
        FRAME_IP_ADDRESS tmpFrame;
        tmpFrame.AddressPhaseH = (SIPR0 >> 8);
        tmpFrame.AddressPhaseL = SIPR0 & 0x00FF;
        tmpFrame.ControlPhase.Bits.BSB = COMMON_REGISTER;
        tmpFrame.ControlPhase.Bits.RWB = READ_MODE;
        tmpFrame.ControlPhase.Bits.OM = FOUR_BYTES_DATA_LENGTH_MODE;
        memset(tmpFrame.IP, 0, 4);

        int length = sizeof(FRAME_IP_ADDRESS);
#ifdef RASPBERRY
        bcm2835_gpio_write(CS_GPIO, LOW);
        bcm2835_aux_spi_transfern((char*)(&tmpFrame), length);
        bcm2835_gpio_write(CS_GPIO, HIGH);
#else
        unsigned char _recv[7] = {0};
        memcpy(_recv, &tmpFrame, length);
#endif
        memcpy(add, tmpFrame.IP, 4);
        iResult = OK;
    }
    m_Mutex.unlock();
    return iResult;
}

int W5500::SetLocalIPAddress(const unsigned char *add)
{
    m_Mutex.lock();
    int iResult = ERROR;
    if(add != nullptr)
    {
        FRAME_IP_ADDRESS tmpFrame;
        tmpFrame.AddressPhaseH = (SIPR0 >> 8);
        tmpFrame.AddressPhaseL = SIPR0 & 0x00FF;
        tmpFrame.ControlPhase.Bits.BSB = COMMON_REGISTER;
        tmpFrame.ControlPhase.Bits.RWB = WRITE_MODE;
        tmpFrame.ControlPhase.Bits.OM = FOUR_BYTES_DATA_LENGTH_MODE;
        memset(tmpFrame.IP, 0, 4);
        memcpy(tmpFrame.IP, add, 4);

        int length = sizeof(FRAME_IP_ADDRESS);
    #ifdef RASPBERRY
        bcm2835_gpio_write(CS_GPIO, LOW);
        bcm2835_aux_spi_writenb((const char*)(&tmpFrame), length);
        bcm2835_gpio_write(CS_GPIO, HIGH);
    #else
        unsigned char _recv[7] = {0};
        memcpy(_recv, &tmpFrame, length);
    #endif
        iResult = OK;
    }
    m_Mutex.unlock();
    return iResult;
}

int W5500::GetTargetIPAddress(const unsigned char reg, unsigned char *add) const
{
    m_Mutex.lock();
    int iResult = ERROR;
    if(add != nullptr)
    {
        switch(reg)
        {
        case SOCKET_1_REGISTER:
        case SOCKET_2_REGISTER:
        case SOCKET_3_REGISTER:
        case SOCKET_4_REGISTER:
        case SOCKET_5_REGISTER:
        case SOCKET_6_REGISTER:
        case SOCKET_7_REGISTER:
            break;
        default:
            return -1;
        }

        FRAME_IP_ADDRESS tmpFrame;
        tmpFrame.AddressPhaseH = (Sn_DIPR0 >> 8);
        tmpFrame.AddressPhaseL = Sn_DIPR0 & 0x00FF;
        tmpFrame.ControlPhase.Bits.BSB = reg;
        tmpFrame.ControlPhase.Bits.RWB = READ_MODE;
        tmpFrame.ControlPhase.Bits.OM = FOUR_BYTES_DATA_LENGTH_MODE;
        memset(tmpFrame.IP, 0, 4);

        int length = sizeof(FRAME_IP_ADDRESS);
#ifdef RASPBERRY
        bcm2835_gpio_write(CS_GPIO, LOW);
        bcm2835_aux_spi_transfern((char*)(&tmpFrame), length);
        bcm2835_gpio_write(CS_GPIO, HIGH);
#else
        unsigned char _recv[7] = {0};
        memcpy(_recv, &tmpFrame, length);
#endif
        memcpy(add, tmpFrame.IP, 4);
        iResult = OK;
    }
    m_Mutex.unlock();
    return iResult;
}

int W5500::SetTargetIPAddress(const unsigned char reg, const unsigned char *add)
{
    m_Mutex.lock();
    int iResult = ERROR;
    if(add != nullptr)
    {
        switch(reg)
        {
        case SOCKET_1_REGISTER:
        case SOCKET_2_REGISTER:
        case SOCKET_3_REGISTER:
        case SOCKET_4_REGISTER:
        case SOCKET_5_REGISTER:
        case SOCKET_6_REGISTER:
        case SOCKET_7_REGISTER:
            break;
        default:
            return -1;
        }
        FRAME_IP_ADDRESS tmpFrame;
        tmpFrame.AddressPhaseH = (Sn_DIPR0 >> 8);
        tmpFrame.AddressPhaseL = Sn_DIPR0 & 0x00FF;
        tmpFrame.ControlPhase.Bits.BSB = reg;
        tmpFrame.ControlPhase.Bits.RWB = WRITE_MODE;
        tmpFrame.ControlPhase.Bits.OM = FOUR_BYTES_DATA_LENGTH_MODE;
        memset(tmpFrame.IP, 0, 4);
        memcpy(tmpFrame.IP, add, 4);

        int length = sizeof(FRAME_IP_ADDRESS);
#ifdef RASPBERRY
        bcm2835_gpio_write(CS_GPIO, LOW);
        bcm2835_aux_spi_writenb((const char*)(&tmpFrame), length);
        bcm2835_gpio_write(CS_GPIO, HIGH);
#else
        unsigned char _recv[7] = {0};
        memcpy(_recv, &tmpFrame, length);
#endif
        iResult = OK;
    }
    m_Mutex.unlock();
    return iResult;
}

int W5500::GetTargetPort(const unsigned char reg, unsigned short *port) const
{
    m_Mutex.lock();
    int iResult = ERROR;
    if(port != nullptr)
    {
        switch(reg)
        {
        case SOCKET_1_REGISTER:
        case SOCKET_2_REGISTER:
        case SOCKET_3_REGISTER:
        case SOCKET_4_REGISTER:
        case SOCKET_5_REGISTER:
        case SOCKET_6_REGISTER:
        case SOCKET_7_REGISTER:
            iResult = OK;
            break;
        default:
            iResult = ERROR;
            break;
        }

        if(iResult == OK)
        {
            FRAME_ONE_SHORT tmpFrame;
            tmpFrame.AddressPhaseH = (Sn_DPORT0 >> 8);
            tmpFrame.AddressPhaseL = Sn_DPORT0 & 0x00FF;
            tmpFrame.ControlPhase.Bits.BSB = reg;
            tmpFrame.ControlPhase.Bits.RWB = READ_MODE;
            tmpFrame.ControlPhase.Bits.OM = TWO_BYTES_DATA_LENGTH_MODE;
            tmpFrame.DataH = 0;
            tmpFrame.DataL = 0;

            int length = sizeof(FRAME_ONE_SHORT);
    #ifdef RASPBERRY
            bcm2835_gpio_write(CS_GPIO, LOW);
            bcm2835_aux_spi_transfern((char*)(&tmpFrame), length);
            bcm2835_gpio_write(CS_GPIO, HIGH);
    #else
            unsigned char _recv[5] = {0};
            memcpy(_recv, &tmpFrame, length);
    #endif
            *port = tmpFrame.DataH;
            *port <<= 8;
            *port &= 0xff00;
            *port |= tmpFrame.DataL;
        }
    }
    m_Mutex.unlock();
    return iResult;
}

int W5500::SetTargetPort(const unsigned char reg, const unsigned short port)
{
    m_Mutex.lock();
    int iResult = ERROR;
    switch(reg)
    {
    case SOCKET_1_REGISTER:
    case SOCKET_2_REGISTER:
    case SOCKET_3_REGISTER:
    case SOCKET_4_REGISTER:
    case SOCKET_5_REGISTER:
    case SOCKET_6_REGISTER:
    case SOCKET_7_REGISTER:
        iResult = OK;
        break;
    default:
        iResult = ERROR;
        break;
    }
    if(iResult == OK)
    {
        FRAME_ONE_SHORT tmpFrame;
        tmpFrame.AddressPhaseH = (Sn_DPORT0 >> 8);
        tmpFrame.AddressPhaseL = Sn_DPORT0 & 0x00FF;
        tmpFrame.ControlPhase.Bits.BSB = reg;
        tmpFrame.ControlPhase.Bits.RWB = WRITE_MODE;
        tmpFrame.DataH = port >> 8;
        tmpFrame.DataL = port & 0x00ff;

        int length = sizeof(FRAME_ONE_SHORT);
#ifdef RASPBERRY
        bcm2835_gpio_write(CS_GPIO, LOW);
        bcm2835_aux_spi_writenb((const char*)(&tmpFrame), length);
        bcm2835_gpio_write(CS_GPIO, HIGH);
#else
        unsigned char _recv[5] = {0};
        memcpy(_recv, &tmpFrame, length);
#endif
    }
    m_Mutex.unlock();
    return iResult;
}

int W5500::GetLocalPort(const unsigned char reg, unsigned short *port) const
{
    m_Mutex.lock();
    int iResult = ERROR;
    if(port != nullptr)
    {
        switch(reg)
        {
        case SOCKET_1_REGISTER:
        case SOCKET_2_REGISTER:
        case SOCKET_3_REGISTER:
        case SOCKET_4_REGISTER:
        case SOCKET_5_REGISTER:
        case SOCKET_6_REGISTER:
        case SOCKET_7_REGISTER:
            iResult = OK;
            break;
        default:
            iResult = ERROR;
            break;
        }
        if(iResult == OK)
        {
            FRAME_ONE_SHORT tmpFrame;
            tmpFrame.AddressPhaseH = (Sn_PORT0 >> 8);
            tmpFrame.AddressPhaseL = Sn_PORT0 & 0x00FF;
            tmpFrame.ControlPhase.Bits.BSB = reg;
            tmpFrame.ControlPhase.Bits.RWB = READ_MODE;
            tmpFrame.ControlPhase.Bits.OM = TWO_BYTES_DATA_LENGTH_MODE;
            tmpFrame.DataH = 0;
            tmpFrame.DataL = 0;

            int length = sizeof(FRAME_ONE_SHORT);
#ifdef RASPBERRY
            bcm2835_gpio_write(CS_GPIO, LOW);
            bcm2835_aux_spi_transfern((char*)(&tmpFrame), length);
            bcm2835_gpio_write(CS_GPIO, HIGH);
#else
            unsigned char _recv[5] = {0};
            memcpy(_recv, &tmpFrame, length);
#endif
            *port = tmpFrame.DataH;
            *port <<= 8;
            *port &= 0xff00;
            *port |= tmpFrame.DataL;
        }
    }
    m_Mutex.unlock();
    return iResult;
}

int W5500::SetLocalPort(const unsigned char reg, const unsigned short port)
{
    m_Mutex.lock();
    int iResult = ERROR;
    switch(reg)
    {
    case SOCKET_1_REGISTER:
    case SOCKET_2_REGISTER:
    case SOCKET_3_REGISTER:
    case SOCKET_4_REGISTER:
    case SOCKET_5_REGISTER:
    case SOCKET_6_REGISTER:
    case SOCKET_7_REGISTER:
        iResult = OK;
        break;
    default:
        iResult = ERROR;
        break;
    }
    if(iResult == OK)
    {
        FRAME_ONE_SHORT tmpFrame;
        tmpFrame.AddressPhaseH = (Sn_PORT0 >> 8);
        tmpFrame.AddressPhaseL = Sn_PORT0 & 0x00FF;
        tmpFrame.ControlPhase.Bits.BSB = reg;
        tmpFrame.ControlPhase.Bits.RWB = WRITE_MODE;
        tmpFrame.DataH = port >> 8;
        tmpFrame.DataL = port & 0x00ff;

        int length = sizeof(FRAME_ONE_SHORT);
#ifdef RASPBERRY
        bcm2835_gpio_write(CS_GPIO, LOW);
        bcm2835_aux_spi_writenb((const char*)(&tmpFrame), length);
        bcm2835_gpio_write(CS_GPIO, HIGH);
#else
        unsigned char _recv[5] = {0};
        memcpy(_recv, &tmpFrame, length);
#endif
    }
    m_Mutex.unlock();
    return iResult;
}

int W5500::GetShortRegister(const unsigned char reg, const unsigned short add, unsigned short *data) const
{
    m_Mutex.lock();
    int iResult = ERROR;
    if(data != nullptr)
    {
        FRAME_ONE_SHORT tmpFrame;
        tmpFrame.AddressPhaseH = (add >> 8);
        tmpFrame.AddressPhaseL = add & 0x00FF;
        tmpFrame.ControlPhase.Bits.BSB = reg;
        tmpFrame.ControlPhase.Bits.RWB = READ_MODE;
        tmpFrame.ControlPhase.Bits.OM = TWO_BYTES_DATA_LENGTH_MODE;
        tmpFrame.DataH = 0;
        tmpFrame.DataL = 0;

        int length = sizeof(FRAME_ONE_SHORT);
#ifdef RASPBERRY
        bcm2835_gpio_write(CS_GPIO, LOW);
        bcm2835_aux_spi_transfern((char*)(&tmpFrame), length);
        bcm2835_gpio_write(CS_GPIO, HIGH);
#else
        unsigned char _recv[5] = {0};
        memcpy(_recv, &tmpFrame, length);
#endif
        *data = tmpFrame.DataH;
        *data <<= 8;
        *data &= 0xff00;
        *data |= tmpFrame.DataL;
        iResult = OK;
    }
    m_Mutex.unlock();
    return iResult;
}

int W5500::SetShortRegister(const unsigned char reg, const unsigned short add, const unsigned short data)
{
    m_Mutex.lock();
    FRAME_ONE_SHORT tmpFrame;
    tmpFrame.AddressPhaseH = (add >> 8);
    tmpFrame.AddressPhaseL = add & 0x00FF;
    tmpFrame.ControlPhase.Bits.BSB = reg;
    tmpFrame.ControlPhase.Bits.RWB = WRITE_MODE;
    tmpFrame.DataH = data >> 8;
    tmpFrame.DataL = data & 0x00ff;

    int length = sizeof(FRAME_ONE_SHORT);
#ifdef RASPBERRY
    bcm2835_gpio_write(CS_GPIO, LOW);
    bcm2835_aux_spi_writenb((const char*)(&tmpFrame), length);
    bcm2835_gpio_write(CS_GPIO, HIGH);
#else
    unsigned char _recv[5] = {0};
    memcpy(_recv, &tmpFrame, length);
#endif
    m_Mutex.unlock();
    return OK;
}
