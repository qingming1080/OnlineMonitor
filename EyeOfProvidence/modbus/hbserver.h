#ifndef HBSERVER_H
#define HBSERVER_H

#include <QObject>

class HBModbus2Server : public QObject
{
    Q_OBJECT
public:
    explicit HBModbus2Server(QObject *parent = nullptr);

signals:
    // HBModbusClient modbusClient;
};

#endif // HBSERVER_H
