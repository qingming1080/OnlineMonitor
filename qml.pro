QT += widgets quick virtualkeyboard charts serialport sql qml

CONFIG += c++11
msvc {
    QMAKE_CFLAGS *= /utf-8
    QMAKE_CXXFLAGS *= /utf-8
}
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        DataBase/databasemanager.cpp \
        devicemanager.cpp \
        fileobject.cpp \
        main.cpp \
        model/device.cpp \
        model/deviceinformation.cpp \
        model/io.cpp \
        model/iomodel.cpp \
        model/manual.cpp \
        model/message.cpp \
        model/model.cpp \
        model/networkmodel.cpp \
        model/production.cpp \
        model/rs232model.cpp \
        model/system.cpp \
        model/weldtrend.cpp \
        model/yieldtrend.cpp \
        qmlcache.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    DataBase/databasemanager.h \
    define.h \
    devicemanager.h \
    fileobject.h \
    model/device.h \
    model/deviceinformation.h \
    model/io.h \
    model/iomodel.h \
    model/manual.h \
    model/message.h \
    model/model.h \
    model/networkmodel.h \
    model/production.h \
    model/rs232model.h \
    model/system.h \
    model/weldtrend.h \
    model/yieldtrend.h \
    qmlcache.h \
    qmlenum.h
