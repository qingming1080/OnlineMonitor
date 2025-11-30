#ifndef W5500_H
#define W5500_H

#include <QObject>
#include <QMutex>
#define CS_GPIO     16
#define ROUTE_RESET 41
#define W5500_RESET 34
class W5500 : public QObject
{
    Q_OBJECT
public:
    //BSB[4:0]
    enum BLOCK_SELECT_BITS
    {
        COMMON_REGISTER     = 0x00,
        SOCKET_0_REGISTER   = 0x01, SOCKET_0_TX_BUFFER  = 0x02, SOCKET_0_RX_BUFFER  = 0x03,

        SOCKET_1_REGISTER   = 0x05, SOCKET_1_TX_BUFFER  = 0x06, SOCKET_1_RX_BUFFER  = 0x07,

        SOCKET_2_REGISTER   = 0x09, SOCKET_2_TX_BUFFER  = 0x0A, SOCKET_2_RX_BUFFER  = 0x0B,

        SOCKET_3_REGISTER   = 0x0D, SOCKET_3_TX_BUFFER  = 0x0E, SOCKET_3_RX_BUFFER  = 0x0F,

        SOCKET_4_REGISTER   = 0x11, SOCKET_4_TX_BUFFER  = 0x12, SOCKET_4_RX_BUFFER  = 0x13,

        SOCKET_5_REGISTER   = 0x15, SOCKET_5_TX_BUFFER  = 0x16, SOCKET_5_RX_BUFFER  = 0x17,

        SOCKET_6_REGISTER   = 0x19, SOCKET_6_TX_BUFFER  = 0x1A, SOCKET_6_RX_BUFFER  = 0x1B,

        SOCKET_7_REGISTER   = 0x1D, SOCKET_7_TX_BUFFER  = 0x1E, SOCKET_7_RX_BUFFER  = 0x1F,
    };

    enum COMMON_REGISTER_BLOCK
    {
        //Mode
        MR          = 0x0000,
        //Gateway Address
        GAR0        = 0x0001, GAR1        = 0x0002, GAR2        = 0x0003, GAR3        = 0x0004,
        //Subnet Mask Address
        SUBR0       = 0x0005, SUBR1       = 0x0006, SUBR2       = 0x0007, SUBR3       = 0x0008,
        //Source Hardware Address
        SHAR0       = 0x0009, SHAR1       = 0x000A, SHAR2       = 0x000B, SHAR3       = 0x000C, SHAR4       = 0x000D, SHAR5       = 0x000E,
        //Source IP Address
        SIPR0       = 0x000F, SIPR1       = 0x0010, SIPR2       = 0x0011, SIPR3       = 0x0012,
        //Interrupt Low Level Timer
        INTLEVEL0   = 0x0013,
        INTLEVEL1   = 0x0014,
        //Interrupt
        IR          = 0x0015,
        //Interrupt Mask
        IMR         = 0x0016,
        //Socket Interrupt
        SIR         = 0x0017,
        //Socket Interrupt Mask
        SIMR        = 0x0018,
        //Retry Time
        RTR0        = 0x0019,
        RTR1        = 0x001A,
        //Retry Count
        RCR         = 0x001B,
        //PPP LCP Request Timer
        PTIMER      = 0x001C,
        //PPP LCP Magic number
        PMAGIC      = 0x001D,
        //PPP Destination MAC Address
        PHAR0       = 0x001E,
        PHAR1       = 0x001F,
        PHAR2       = 0x0020,
        PHAR3       = 0x0021,
        PHAR4       = 0x0022,
        PHAR5       = 0x0023,
        //PPP Session Identification
        PSID0       = 0x0024,
        PSID1       = 0x0025,
        //PPP Maximum Segment Size
        PMRU0       = 0x0026,
        PMRU1       = 0x0027,
        //Unreachable IP address
        UIPR0       = 0x0028,
        UIPR1       = 0x0029,
        UIPR2       = 0x002A,
        UIPR3       = 0x002B,
        //Unreachable Port
        UPORTR0     = 0x002C,
        UPORTR1     = 0x002D,
        //PHY Configuration
        PHYCFGR     = 0x002E,
        //Chip version
        VERSIONR    = 0x0039

    };

    //Offset Address in Socket n Register Block (0 <= n <= 7)
    enum SOCKET_REGISTER_BLOCK
    {
        //Socket n Mode
        Sn_MR       = 0x0000,
        //Socket n Command
        Sn_CR       = 0x0001,
        //Socket n Interrupt
        Sn_IR       = 0x0002,
        //Socket n Status
        Sn_SR       = 0x0003,
        //Socket n Source Port
        Sn_PORT0    = 0x0004,
        Sn_PORT1    = 0x0005,
        //Socket n Destination Hardware Address
        Sn_DHAR0    = 0x0006,
        Sn_DHAR1    = 0x0007,
        Sn_DHAR2    = 0x0008,
        Sn_DHAR3    = 0x0009,
        Sn_DHAR4    = 0x000A,
        Sn_DHAR5    = 0x000B,
        //Socket n Destination IP Address
        Sn_DIPR0    = 0x000C,
        Sn_DIPR1    = 0x000D,
        Sn_DIPR2    = 0x000E,
        Sn_DIPR3    = 0x000F,
        //Socket n Destination Port
        Sn_DPORT0   = 0x0010,
        Sn_DPORT1   = 0x0011,
        //Socket n Maximum Segment Size
        Sn_MSSR0    = 0x0012,
        Sn_MSSR1    = 0x0013,
        //Reserved
        Reserved    = 0x0014,
        //Socket n IP TOS
        Sn_TOS      = 0x0015,
        //Socket n IP TTL
        Sn_TTL      = 0x0016,
        //Socket n Receive Buffer Size
        Sn_RXBUF_SIZE   = 0x001E,
        //Socket n Transmit Buffer Size
        Sn_TXBUF_SIZE   = 0x001F,
        //Socket n TX Free Size
        Sn_TX_FSR0  = 0x0020,
        Sn_TX_FSR1  = 0x0021,
        //Socket n TX Read Pointer
        Sn_TX_RD0   = 0x0022,
        Sn_TX_RD1   = 0x0023,
        //Socket n TX Write Pointer
        Sn_TX_WR0   = 0x0024,
        Sn_TX_WR1   = 0x0025,
        //Socket n RX Received Size
        Sn_RX_RSR0  = 0x0026,
        Sn_RX_RSR1  = 0x0027,
        //Socket n RX Read Pointer
        Sn_RX_RD0   = 0x0028,
        Sn_RX_RD1   = 0x0029,
        //Socket n RX Writer Pointer
        Sn_RX_WR0   = 0x002A,
        Sn_RX_WR1   = 0x002B,
        //Socket n Interrupt Mask
        Sn_IMR      = 0x002C,
        //Socket n Fragment Offset in IP header
        Sn_FRAG0    = 0x002D,
        Sn_FRAG1    = 0x002E,
        //Keep alive time
        Sn_KPALVTR  = 0x002F,
    };

    enum PROTOCOL_MODE
    {
        CLOSED  = 0x00,
        TCP     = 0x01,
        UDP     = 0x02,
        MACRAW  = 0x04
    };

    enum CONTROL_COMMAND
    {
        OPEN        = 0x01,
        LISTEN      = 0x02,
        CONNECT     = 0x04,
        DISCON      = 0x08,
        CLOSE       = 0x10,
        SEND        = 0x20,
        SEND_MAC    = 0x21,
        SEND_KEEP   = 0x22,
        RECV        = 0x40
    };

    enum STATUS_COMMAND
    {
        SOCKET_CLOSED       = 0x00,
        SOCK_INIT           = 0x13,
        SOCK_LISTEN         = 0x14,
        SOCK_ESTABLISHED    = 0x17,
        SOCK_CLOSE_WAIT     = 0x1C,
        SOCK_UDP            = 0x22,
        SOCK_MACRAW         = 0x42
    };


private:
    enum READ_WRITE_ACCESS_MODE_BIT
    {
        READ_MODE    = 0,
        WRITE_MODE   = 1,
    };

    enum SPI_OPERATION_MODE_BITS
    {
        VARIABLE_DATA_LENGTH_MODE   = 0,
        ONE_BYTE_DATA_LENGTH_MODE   = 1,
        TWO_BYTES_DATA_LENGTH_MODE  = 2,
        FOUR_BYTES_DATA_LENGTH_MODE = 3
    };

    union CONTROL_PHASE
    {
        unsigned char Phase;
        struct CONTROL_PHASE_BITS
        {
            unsigned char OM  : 2;
            unsigned char RWB : 1;
            unsigned char BSB : 5;
        }Bits;
    };

    struct FRAME_HEADER
    {
        unsigned char  AddressPhaseH;
        unsigned char  AddressPhaseL;
        CONTROL_PHASE  ControlPhase;
    };

    struct FRAME_VERSION
    {
        unsigned char  AddressPhaseH;
        unsigned char  AddressPhaseL;
        CONTROL_PHASE  ControlPhase;
        unsigned char  Version;

    };

    struct FRAME_ONE_BYTE
    {
        unsigned char AddressPhaseH;
        unsigned char AddressPhaseL;
        CONTROL_PHASE ControlPhase;
        unsigned char Data;
    };

    struct FRAME_ONE_SHORT
    {
        unsigned char AddressPhaseH;
        unsigned char AddressPhaseL;
        CONTROL_PHASE ControlPhase;
        unsigned char DataH;
        unsigned char DataL;
    };

    struct FRAME_IP_ADDRESS
    {
        unsigned char AddressPhaseH;
        unsigned char AddressPhaseL;
        CONTROL_PHASE ControlPhase;
        unsigned char IP[4];
    };

    struct FRAME_MAC_ADDRESS
    {
        unsigned char AddressPhaseH;
        unsigned char AddressPhaseL;
        CONTROL_PHASE ControlPhase;
        unsigned char MAC[6];
    };

public:
    static W5500*   GetInstance();
    virtual         ~W5500();
    bool            GetW5500Status() const;
    int             GetVersionNumber    () const;
    int             GetRegister(const unsigned char reg, const unsigned short add) const;
    int             SetRegister(const unsigned char reg, const unsigned short add, unsigned char data);

    int             GetGatewayIPAddress(unsigned char* add) const;
    int             SetGatewayIPAddress(const unsigned char* add);

    int             GetSubnetMask(unsigned char* add) const;
    int             SetSubnetMask(const unsigned char* add);

    int             GetMacAddress(unsigned char* add) const;
    int             SetMacAddress(const unsigned char* add);

    int             GetLocalIPAddress(unsigned char* add) const;
    int             SetLocalIPAddress(const unsigned char* add);

    int             GetTargetIPAddress(const unsigned char reg, unsigned char* add) const;
    int             SetTargetIPAddress(const unsigned char reg, const unsigned char* add);

    int             GetTargetPort(const unsigned char reg, unsigned short* port) const;
    int             SetTargetPort(const unsigned char reg, const unsigned short port);

    int             GetLocalPort(const unsigned char reg, unsigned short* port) const;
    int             SetLocalPort(const unsigned char reg, const unsigned short port);

    int             GetShortRegister(const unsigned char reg, const unsigned short add, unsigned short* data) const;
    int             SetShortRegister(const unsigned char reg, const unsigned short add, const unsigned short data);
private:
    static  W5500* _w5500;
    static QMutex  m_Mutex;
    bool    m_IsW5500Avaiable;
    explicit    W5500               (QObject *parent = nullptr);

signals:

};

#endif // W5500_H
