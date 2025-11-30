#include <QDebug>
#include "modbus/servers.h"
#include "modbus/hbclient.h"
#include "app/ethernetapp.h"
#include "app/serialapp.h"
#include "app/interfaceapp.h"
#include "app/systemclock.h"
#include "hardware/serial.h"
#include "hardware/rtc_ds3231.h"
#include <QCoreApplication>
#include <QObject>
#include <QTimer>
#include <QThread>
#include <QDateTime>
int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    SystemClock::GetInstance()->SyncSystemClock();

    ModbusServers* _servers = new ModbusServers(nullptr);
    _servers->Init();
    qDebug()<< "Modbus Server Application Running ";

    // QTimer::singleShot(5000 * 720, &app, &QCoreApplication::quit);
    return app.exec();

    // _EthernetApp->Close(0);
    // _SerialApp->Close(0);
    // delete _EthernetApp;
    // delete _SerialApp;
    // delete _servers;
}
