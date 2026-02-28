#include <QDebug>
#include "modbus/servers.h"
#include "modbus/hbclient.h"
#include "app/ethernetapp.h"
#include "app/serialapp.h"
#include "app/interfaceapp.h"
#include "app/systemclock.h"
#include "hardware/serial.h"
#include "hardware/rtc_ds3231.h"
#include "decryption/decryption.h"
#include <QCoreApplication>
#include <QObject>
#include <QTimer>
#include <QThread>
#include <QDateTime>
int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    Decryption* _decryption = new Decryption(nullptr);
    if(_decryption->DecryptLicenseFile() == false)
    {
        QTimer::singleShot(600000, &app, &QCoreApplication::quit); //it will be running 10min
    }

    SystemClock::GetInstance()->SyncSystemClock();

    ModbusServers* _servers = new ModbusServers(nullptr);
    _servers->Init();
    qDebug()<< "Modbus Server Application Running ";
    return app.exec();

    delete _servers;
    delete _decryption;
}
