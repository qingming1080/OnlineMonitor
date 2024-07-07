#include <QApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include <QQmlEngine>

#include "devicemanager.h"
#include "model/device.h"
#include "model/deviceinformation.h"
#include "model/manual.h"
#include "model/message.h"
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
    pQmlContext->setContextProperty("Message", Message::getInstance());
    pQmlContext->setContextProperty("Manual", new Manual());

    qmlRegisterType<Device>("Device",1,0,"Device");
//    qmlRegisterType<IOModel>("IOModel",1,0,"IOModel");
    qmlRegisterType<DeviceInformation>("DeviceInformation",1,0,"DeviceInformation");


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
