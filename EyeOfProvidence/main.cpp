#include <QApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include <QQmlEngine>

#include "model/devicemanager.h"
#include "model/device.h"
#include "model/deviceinformation.h"
#include "model/manual.h"
#include "model/production.h"
#include "model/message.h"
#include "model/trend.h"
#include "model/history.h"
#include "model/networkmodel.h"
#include "model/rs232model.h"
#include "model/baudratemodel.h"
#include "model/databitsmodel.h"
#include "model/stopbitsmodel.h"
#include "model/paritymodel.h"
#include "model/weldertypemodel.h"
#include "model/historyenum.h"
#include "model/yieldstrendenum.h"
#include "DataBase/databasemanager.h"
#include "log/localrecord.h"
#include "LanguageManager/languageManager.h"
#include "tools/utilityapplauncher.h"
#include "tools/utilityfunction.h"
#include "KeyBoard/pinyindict.h"


//modbus
#include "modbus/hbmodbusclient.h"

// 自定义消息处理程序
void myMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(type)
    Q_UNUSED(context)
    Q_UNUSED(msg)
    // 过滤掉你不想显示的消息
    switch (type)
    {
   // case QtDebugMsg:
   // {
   //     if(msg.contains("I_WANT_"))
   //         std::cerr << msg.toLocal8Bit().toStdString() << std::endl;
   // }
    /// TEST 2024_08_18
    // case QtDebugMsg:
    //     break;
    case QtInfoMsg:
        break;
    case QtWarningMsg:
        break;
    case QtCriticalMsg:
        break;
    case QtFatalMsg:
        abort();
    case QtDebugMsg:
        break;
    }
}

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("none"));
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    // 安装自定义消息处理程序
    // qInstallMessageHandler(myMessageHandler);
    QApplication app(argc, argv);
    qRegisterMetaType<HBModbusClient::MODBUS_WELD_RESULT>("HBModbusClient::MODBUS_WELD_RESULT");
    qRegisterMetaType<HBModbusClient::WELD_PRESET>("HBModbusClient::WELD_PRESET");
    qRegisterMetaType<HBModbusClient::IO_STATUS>("HBModbusClient::IO_STATUS");
    qRegisterMetaType<HBModbusClient::DEVICE_STATUS>("HBModbusClient::DEVICE_STATUS");
    LocalRecord::getInstance()->start();

    LanguageManager LanguageManager;

    QQmlApplicationEngine engine;
    QQmlContext* pQmlContext = engine.rootContext();

    bool isRaspberry = false;

#if RASPBERRY
    isRaspberry = true;
#else
    isRaspberry = false;
#endif


    pQmlContext->setContextProperty("LanguageManager", &LanguageManager);
    pQmlContext->setContextProperty("DeviceManager", DeviceManager::getInstance());
    pQmlContext->setContextProperty("History", History::getInstance());
    pQmlContext->setContextProperty("Message", Message::getInstance());

    pQmlContext->setContextProperty("DataBaseManager", DataBaseManager::getInstance());

    pQmlContext->setContextProperty("NetworkModel",     NetworkModel::getInstance());
    pQmlContext->setContextProperty("RS232Model",       RS232Model::getInstance());
    pQmlContext->setContextProperty("BaudRateModel",    BaudRateModel::getInstance());
    pQmlContext->setContextProperty("DataBitsModel",    DataBitsModel::getInstance());
    pQmlContext->setContextProperty("StopBitsModel",    StopBitsModel::getInstance());
    pQmlContext->setContextProperty("ParityModel",      ParityModel::getInstance());
    pQmlContext->setContextProperty("WelderTypeModel",  WelderTypeModel::getInstance());

    pQmlContext->setContextProperty("ModbusClient",     HBModbusClient::getInstance());
    pQmlContext->setContextProperty("UtilityFunction",  UtilityFunction::getInstance());
    pQmlContext->setContextProperty("IsRaspberry",      isRaspberry);
    PinyinDict pinyinDict;
    pQmlContext->setContextProperty("PinyinDict", &pinyinDict);

    qmlRegisterType<Device>("Device", 1, 0, "Device");
    // qmlRegisterType<IO>("IO", 1, 0, "IO");
    qmlRegisterType<DeviceInformation>("DeviceObj",     1, 0, "DeviceObj");//
    qmlRegisterType<Production>("ProductionObj",        1, 0, "ProductionObj");//
    qmlRegisterType<Manual>("ManualObj",                1, 0, "ManualObj"); //
    qmlRegisterType<Trend>("TrendObj",                  1, 0,"TrendObj");
    qmlRegisterType<MESSAGE_ENUM>("MessageEnum",        1, 0, "MessageEnum");
    qmlRegisterType<QmlEnum>("QmlEnum",                 1, 0,"QmlEnum");
    qmlRegisterType<LanguageEnum>("LanguageEnum",       1, 0, "LanguageEnum");
    qmlRegisterType<DeviceInfoEnum>("DeviceInfoEnum",   1, 0, "DeviceInfoEnum");
    qmlRegisterType<MANUAL_TABLE>("ManualTable",        1, 0, "ManualTable");
    qmlRegisterType<HistoryEnum>("HistoryEnum",         1, 0, "HistoryEnum");
    qmlRegisterType<YieldsTrendEnum>("YieldsTrendEnum", 1, 0, "YieldsTrendEnum");

    qmlRegisterSingletonType(QUrl("qrc:/qmlSource/GlobalLanguageDefine.qml"),   "GlobalLanguageDefine", 1,  0,  "GlobalLanguageDefine");
    qmlRegisterSingletonType(QUrl("qrc:/qmlSource/BransonStyle.qml"),           "GlobalStyle",          1,  0,  "GlobalStyle");
    qmlRegisterSingletonType(QUrl("qrc:/qmlSource/GlobalSystemDefine.qml"),     "GlobalSystemDefine",   1,  0,  "GlobalSystemDefine");
    qmlRegisterSingletonType(QUrl("qrc:/qmlSource/GlobalMessageDefine.qml"),    "GlobalMessageDefine",  1,  0,  "GlobalMessageDefine");

    //Launch modbus server after the client ready
    UtilityAppLauncher::getInstance()->startUtilityApp();

    const QUrl url(QStringLiteral("qrc:/qmlSource/main.qml"));

    QObject::connect(&LanguageManager, &LanguageManager::notifyLanguageIndexChanged,[&]()
    {
        engine.retranslate();
    });

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, [url](QObject *obj, const QUrl &objUrl)
    {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
