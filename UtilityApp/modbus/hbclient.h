#ifndef HBCLIENT_H
#define HBCLIENT_H
#include <QModbusDevice>
#include <QModbusTcpClient>
#include <QModbusTcpServer>

class hbclient : public QModbusTcpClient
{
public:
    explicit hbclient(QObject *parent = nullptr);
    ~hbclient();
    bool Connect(const int &iPort, const QString &strAddress);
private:
    bool m_isConnected;


};

#endif // HBCLIENT_H
