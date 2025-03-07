﻿#include <QApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include <QQmlEngine>

#include "devicemanager.h"
#include "model/device.h"
#include "model/deviceinformation.h"
#include "model/manual.h"
#include "model/message.h"
#include "model/io.h"
#include "model/trend.h"
#include "model/history.h"
#include "model/networkmodel.h"
#include "model/rs232model.h"
#include "DataBase/databasemanager.h"
#include "model/system.h"
#include "log/localrecord.h"
#include "model/devicenames.h"
#include "LanguageManger/languagemanger.h"

//modbus
#include "modbus/hbmodbusclient.h"
#include "DataHandler/timehandler.h"



#include <iostream>
// 自定义消息处理程序
void myMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    /// TEST 2024_08_18
    // 过滤掉你不想显示的消息
    switch (type) {
//    case QtDebugMsg:
//    {
//        if(msg.contains("I_WANT_"))
//            std::cerr << msg.toLocal8Bit().toStdString() << std::endl;
//    }
    /// TEST 2024_08_18
    case QtDebugMsg:
        break;
    case QtInfoMsg:
        break;
    case QtWarningMsg:
        break;
    case QtCriticalMsg:
        break;
    case QtFatalMsg:
        abort();
    }
}

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    // 安装自定义消息处理程序
    qInstallMessageHandler(myMessageHandler);
    QApplication app(argc, argv);
    LocalRecord::getInstance()->start();

    LanguageManger LanguageManger;
    QTranslator translator;
    // 默认加载英文
    translator.load(":/translations/en.ts");
    app.installTranslator(&translator);

    DeviceManager* deviceManager = DeviceManager::getInstance();

    //modbus
    HBModbusClient  *modbusClient = new HBModbusClient(deviceManager);


    QQmlApplicationEngine engine;
    QQmlContext* pQmlContext = engine.rootContext();
    pQmlContext->setContextProperty("QTranslator",&translator);
    pQmlContext->setContextProperty("LanguageManger",&LanguageManger);
    pQmlContext->setContextProperty("DeviceManager", DeviceManager::getInstance());
    pQmlContext->setContextProperty("History", History::getInstance());
    pQmlContext->setContextProperty("Message", Message::getInstance());
    pQmlContext->setContextProperty("NetworkModel", NetworkModel::getInstance());
    pQmlContext->setContextProperty("RS232Model", RS232Model::getInstance());
    pQmlContext->setContextProperty("DataBaseManager", DataBaseManager::getInstance());
    pQmlContext->setContextProperty("DeviceNames", DeviceNames::getInstance());
    pQmlContext->setContextProperty("Manual", new Manual(1));
    pQmlContext->setContextProperty("HBModbusClient", modbusClient);



    qmlRegisterType<Device>("Device",1,0,"Device");
    qmlRegisterType<IO>("IO",1,0,"IO");
    qmlRegisterType<DeviceInformation>("DeviceInformation",1,0,"DeviceInformation");
    qmlRegisterType<Trend>("Trend",1,0,"Trend");
    qmlRegisterType<System>("System",1,0,"System");
    qmlRegisterType<QmlEnum>("QmlEnum",1,0,"QmlEnum");
//    qmlRegisterType<LineChartItem>("CustomChart", 1, 0, "CustomChart");
//    qmlRegisterType<TimeChartItem>("CustomTimeChart", 1, 0, "CustomTimeChart");


    const QUrl url(QStringLiteral("qrc:/qmlSource/main.qml"));

    QObject::connect(&LanguageManger,&LanguageManger::updata,[&](){
        engine.retranslate();
    });

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
