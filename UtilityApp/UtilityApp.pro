QT += core serialbus network core serialport

CONFIG += c++11

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
        app/ethernetapp.cpp \
        app/gpioapp.cpp \
        app/interfaceapp.cpp \
        app/serialapp.cpp \
        app/systemclock.cpp \
        hardware/board_cm3.cpp \
        hardware/ethernet.cpp \
        hardware/gpio.cpp \
        hardware/rtc_ds3231.cpp \
        hardware/serial.cpp \
        main.cpp \
        hardware/w5500.cpp \
        modbus/hbclient.cpp \
        modbus/hbserver.cpp \
        modbus/servers.cpp \
        protocol/common.cpp \
        protocol/touchscreen.cpp \
        protocol/versagraphic.cpp \
        proxy.cpp \
        subject.cpp \
        utility/utility.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
 contains(DEFINES, RASPBERRY){
    LIBS += -L$$PWD/BCM/ -lbcm2835

    INCLUDEPATH += $$PWD/BCM
    DEPENDPATH += $$PWD/BCM

    PRE_TARGETDEPS += $$PWD/BCM/libbcm2835.a
}
HEADERS += \
    app/ethernetapp.h \
    app/gpioapp.h \
    app/interfaceapp.h \
    app/serialapp.h \
    app/systemclock.h \
    hardware/board_cm3.h \
    definition.h \
    hardware/ethernet.h \
    hardware/gpio.h \
    hardware/rtc_ds3231.h \
    hardware/serial.h \
    hardware/w5500.h \
    modbus/hbclient.h \
    modbus/hbserver.h \
    modbus/servers.h \
    protocol/common.h \
    protocol/touchscreen.h \
    protocol/versagraphic.h \
    proxy.h \
    subject.h \
    utility/utility.h
