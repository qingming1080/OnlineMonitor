#ifndef QMLENUM_H
#define QMLENUM_H

#include <QObject>

class QmlEnum : public QObject
{
    Q_OBJECT
public:
    // 产品优良状态
    enum _PRODUCTSTATE
    {
        PRODUCTSTATE_Excelleng = 0,    // 良品
        PRODUCTSTATE_Difference,       // 次品
    };
    Q_ENUM(_PRODUCTSTATE)

    // 设备连接方式
    enum _CONNECTTYPE
    {
        _CONNECTTYPE_Network    = 0,    // 网络连接
        _CONNECTTYPE_RS232      = 1,    // RS232
    };
    Q_ENUM(_CONNECTTYPE)

    enum _SIGNAL
    {
        _SIGNAL_alarm = 0,
        _SIGNAL_reset = 1,
        _SIGNAL_noDefinite = 2,
    };
    Q_ENUM(_SIGNAL)

public:
    explicit QmlEnum(QObject *parent = nullptr){}

signals:

};

#endif // QMLENUM_H
