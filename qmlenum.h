#ifndef QMLENUM_H
#define QMLENUM_H

#include <QObject>

class QmlEnum : public QObject
{
    Q_OBJECT
public:
    // 产品优良状态
    enum _PRODUCTSTATE{
        PRODUCTSTATE_Excelleng = 0,    // 良品
        PRODUCTSTATE_Difference,       // 次品
    };
    Q_ENUM(_PRODUCTSTATE)

public:
    explicit QmlEnum(QObject *parent = nullptr){}

signals:

};

#endif // QMLENUM_H
