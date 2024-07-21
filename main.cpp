#include <QApplication>
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
// 自定义消息处理程序
void myMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // 过滤掉你不想显示的消息
    switch (type) {
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
//    qInstallMessageHandler(myMessageHandler);
    QApplication app(argc, argv);
    DeviceManager::getInstance();

    QQmlApplicationEngine engine;
    QQmlContext* pQmlContext = engine.rootContext();
    pQmlContext->setContextProperty("DeviceManager", DeviceManager::getInstance());
    pQmlContext->setContextProperty("History", History::getInstance());
    pQmlContext->setContextProperty("Message", Message::getInstance());
    pQmlContext->setContextProperty("NetworkModel", NetworkModel::getInstance());
    pQmlContext->setContextProperty("RS232Model", RS232Model::getInstance());
    pQmlContext->setContextProperty("DataBaseManager", DataBaseManager::getInstance());
    pQmlContext->setContextProperty("Manual", new Manual(1));
    pQmlContext->setContextProperty("System1", new System(1));
    pQmlContext->setContextProperty("System2", new System(2));
    pQmlContext->setContextProperty("System3", new System(3));
    pQmlContext->setContextProperty("System4", new System(4));


    qmlRegisterType<Device>("Device",1,0,"Device");
    qmlRegisterType<IO>("IO",1,0,"IO");
//    qmlRegisterType<IOModel>("IOModel",1,0,"IOModel");
    qmlRegisterType<DeviceInformation>("DeviceInformation",1,0,"DeviceInformation");
    qmlRegisterType<Trend>("Trend",1,0,"Trend");
    qmlRegisterType<QmlEnum>("QmlEnum",1,0,"QmlEnum");


    const QUrl url(QStringLiteral("qrc:/qmlSource/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
