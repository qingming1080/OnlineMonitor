#include <QApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>


#include "devicemanager.h"
#include "model/device.h"
#include "model/deviceinformation.h"

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



    QQmlApplicationEngine engine;
    QQmlContext* pQmlContext = engine.rootContext();
    pQmlContext->setContextProperty("DeviceManager", DeviceManager::getInstance());
<<<<<<< HEAD
    qmlRegisterUncreatableType<Device>("Device",1,0,"Device","can not instantiate Device in qml");
    qmlRegisterUncreatableType<DeviceInformation>("DeviceInformation",1,0,"DeviceInformation","can not instantiate DeviceInformation in qml");
=======
    pQmlContext->setContextProperty("YieldTrendModel", new YieldTrend);
>>>>>>> 0e792ce475351b12d2ad79d17594e31c1baa68ad


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
