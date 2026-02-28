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
static ModbusServers* _servers = nullptr;
static bool bResult = false;
static QTimer *timer = nullptr;
int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    SystemClock::GetInstance()->SyncSystemClock();

    _servers = new ModbusServers(nullptr);
    _servers->Init();

    Decryption* _decryption = new Decryption(nullptr);

    // if(_decryption->DecryptLicenseFile() == false)
    // {
    //     QTimer::singleShot(600000, &app, &QCoreApplication::quit); //it will be running 10min
    // }
    if(_decryption->DecryptLicenseFile() == false)
    {
        timer = new QTimer(&app);
        QObject::connect(timer, &QTimer::timeout, [&app]() {
            qDebug() << "Timer triggered at" << QDateTime::currentDateTime().toString();
            if(bResult == false)
            {
                delete _servers;
                timer->stop();
            }
            // 你的定时任务在这里
        });
        timer->start(60000);  // 每5秒触发一次
    }

    qDebug()<< "Modbus Server Application Running ";
    return app.exec();

    delete _servers;
    delete _decryption;
}
