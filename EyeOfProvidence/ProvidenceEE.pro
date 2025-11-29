QT += widgets quick virtualkeyboard charts serialport sql qml xml serialbus core
CONFIG += c++11
CONFIG += C++11UTF8
msvc {
    QMAKE_CFLAGS *= /utf-8
    QMAKE_CXXFLAGS *= /utf-8
}
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += REMARK_FWC
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        DataBase/databasehelper.cpp \
        DataBase/databasemanager.cpp \
        KeyBoard/pinyindict.cpp \
        LanguageManager/languageManager.cpp \
        fileobject.cpp \
        log/localrecord.cpp \
        main.cpp \
        modbus/hbmodbusclient.cpp \
        modbus/hbserver.cpp \
        model/baudratemodel.cpp \
        model/databitsmodel.cpp \
        model/csvexportworker.cpp \
        model/device.cpp \
        model/deviceinformation.cpp \
        model/devicemanager.cpp \
        model/exportworker.cpp \
        model/history.cpp \
        model/manual.cpp \
        model/message.cpp \
        model/networkmodel.cpp \
        model/paritymodel.cpp \
        model/production.cpp \
        model/rs232model.cpp \
        model/stopbitsmodel.cpp \
        model/trend.cpp \
        model/weldertypemodel.cpp \
        provienceEE/providenceEE.cpp \
        signalmanager.cpp \
        tools/datavalidator.cpp \
        tools/utilityapplauncher.cpp \
        tools/utilityfunction.cpp

RESOURCES += qml.qrc \
    databaseSource.qrc \
    fonts.qrc \
    hanzilib.qrc \
    images.qrc \
    languageTranslation.qrc \
    misc.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    DataBase/databasehelper.h \
    DataBase/databasemanager.h \
    KeyBoard/pinyindict.h \
    LanguageManager/languageManager.h \
    define.h \
    fileobject.h \
    log/localrecord.h \
    modbus/hbmodbusclient.h \
    modbus/hbserver.h \
    model/baudratemodel.h \
    model/databitsmodel.h \
    model/csvexportworker.h \
    model/device.h \
    model/deviceinfoenum.h \
    model/deviceinformation.h \
    model/devicemanager.h \
    model/exportworker.h \
    model/history.h \
    model/historyenum.h \
    model/manual.h \
    model/message.h \
    model/networkmodel.h \
    model/paritymodel.h \
    model/production.h \
    model/rs232model.h \
    model/stopbitsmodel.h \
    model/trend.h \
    model/weldertypemodel.h \
    provienceEE/providenceEE.h \
    qmlenum.h \
    signalmanager.h \
    tools/datavalidator.h \
    tools/utilityapplauncher.h \
    tools/utilityfunction.h \
    tools/GenericLearning.h

TRANSLATIONS += \
        languageTranslation/SimplifiedChinese.ts \
        languageTranslation/English.ts

DISTFILES +=

INCLUDEPATH += $$PWD/LIB
DEPENDPATH += $$PWD/LIB

contains(DEFINES, RASPBERRY){
   LIBS += -L$$PWD/./RASPBERRY_LIB/ -lalgorithm
   INCLUDEPATH += $$PWD/./RASPBERRY_LIB
   DEPENDPATH += $$PWD/./RASPBERRY_LIB
   PRE_TARGETDEPS += $$PWD/./RASPBERRY_LIB/libalgorithm.a
}
else
{
    contains(DEFINES, linux){
        LIBS += -L$$PWD/./PC_LIB/ -lalgorithm
        INCLUDEPATH += $$PWD/./PC_LIB
        DEPENDPATH += $$PWD/./PC_LIB
        PRE_TARGETDEPS += $$PWD/./PC_LIB/libalgorithm.a
    }
}
