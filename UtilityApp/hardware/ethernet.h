#ifndef ETHERNET_H
#define ETHERNET_H

#include "w5500.h"
#include <QThread>
class Ethernet : public QObject
{
    Q_OBJECT // 必须包含宏 Q_OBJECT
public:
    enum SOCKET_DEVICE
    {
        SOCKET0 = 0,
        SOCKET1,
        SOCKET2,
        SOCKET3,
        SOCKET4,
        SOCKET5,
        SOCKET6,
        SOCKET7
    };
    Ethernet(const SOCKET_DEVICE socketNumber);
    Ethernet();
    static int Reset_W5500();
    static int Reset_Route();
    static int Set_Local_Eth0(const unsigned char *localIP, const unsigned char *gateway, const unsigned char *subnetMask);

public:
    int Open_TCP_Socket(const unsigned char *targeetIP, const unsigned short targetPort);
    int Close_TCP_Socket();
    void SetDevNum(const int devNum);
    int GetDevNum() const;
    unsigned char GetStatus() const;

protected:
    void timerEvent(QTimerEvent *event) override;
private:
    int open_TCP_Socket(const W5500::PROTOCOL_MODE mode);
    int close_TCP_Socket();
    int set_Socket_Server(const unsigned char *targetIP, const unsigned short targetPort);
    int get_Socket_Server(unsigned char *targetIP, unsigned short* targetPort) const;
    int set_Local_Port(const unsigned short localPort);

    int connect_TCP_Socket();
    int receive_TCP_Socket(unsigned char* _buffer);
    int get_TCP_Status();
private:
    static constexpr int RETRIED = 5;
    static constexpr int TX_REG_OFFSET = 1;
    static constexpr int RX_REG_OFFSET = 2;
    SOCKET_DEVICE m_SocketNum;
    QString m_strBuffer;
    unsigned char _Recv_buffer[2048];
    int m_timeID;
    int m_iDevNum;
    unsigned char m_iStatus;
    QThread* m_objThreadHandler;
signals:
    void signalResultReady(int iDev, QString strResult); //Send the signal to Ethernet APP
};

#endif // ETHERNET_H
