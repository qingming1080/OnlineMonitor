#ifndef YIELDSTRENDENUM_H
#define YIELDSTRENDENUM_H
#include <QObject>
class YieldsTrendEnum : public QObject
{
    Q_OBJECT
public:
    enum YIELDS_MODE
    {
        ONE_HOUR            = 0,
        TWENTY_FOUR_HOURS   = 1,
        SEVEN_DAYS          = 2,
        THIRTY_DAYS         = 3,
    };
    Q_ENUM(YIELDS_MODE)

public:
    explicit YieldsTrendEnum(QObject *parent = nullptr){Q_UNUSED(parent);}
};
#endif // YIELDSTRENDENUM_H
