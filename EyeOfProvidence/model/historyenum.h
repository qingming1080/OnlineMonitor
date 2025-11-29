#ifndef HISTORYENUM_H
#define HISTORYENUM_H
#include <QObject>
class HistoryEnum : public QObject
{
    Q_OBJECT
public:
    enum WELDER_NUMBER
    {
        ALL_WELDERS     = 0,
        FIRST_WELDER    = 1,
        SECOND_WELDER   = 2,
        THIRD_WEDLER    = 3,
        FOURTH_WELDER   = 4
    };
    Q_ENUM(WELDER_NUMBER)

    enum FINAL_RESULT
    {
        ALL     = 0,
        GOOD    = 1,
        DEFECT  = 2,
        SUSPECT = 3
    };
    Q_ENUM(FINAL_RESULT)

public:
    explicit HistoryEnum(QObject *parent = nullptr){Q_UNUSED(parent);}
};
#endif // HISTORYENUM_H
