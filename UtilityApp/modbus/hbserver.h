#ifndef HBSERVER_H
#define HBSERVER_H
#include <QModbusTcpServer>
#include <QModbusDataUnit>
#include <QHostAddress>
class hbServer : public QModbusTcpServer
{
public:
    explicit hbServer(QObject *parent = nullptr);
    ~hbServer();
    bool Listen(const int &iPort, const QString &strAddress);
    // QModbusResponse processRequest(const QModbusPdu &request) override;
private:
    bool m_isConnected;
private slots:
    void slotStateChange(QModbusDevice::State state);
    void slotErrorChange(QModbusDevice::Error error);
};

#endif // HBSERVER_H
