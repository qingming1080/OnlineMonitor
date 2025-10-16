#ifndef DATAVALIDATOR_H
#define DATAVALIDATOR_H

#include <QObject>

class DataValidator : public QObject
{
    Q_OBJECT
public:
    static const int MIN_ENERGY             = 0;
    static const int MAX_ENERGY             = 1000;

    static const int MIN_AMPLITUDE          = 0;
    static const int MAX_AMPLITUDE          = 100;

    static const int MIN_TP                 = 0;
    static const int MAX_TP                 = 1000;

    static const int MIN_WP                 = 0;
    static const int MAX_WP                 = 1000;

    static const int MIN_TIME               = 0;
    static const int MAX_TIME               = 1000;

    static const int MIN_POWER              = 0;
    static const int MAX_POWER              = 6000;

    static const int MIN_PRESSURE           = 0;
    static const int MAX_PRESSURE           = 100;

    static const int MIN_PREHEIGHT          = 0;
    static const int MAX_PREHEIGHT          = 1000;

    static const int MIN_POSTHEIGHT          = 0;
    static const int MAX_POSTHEIGHT          = 1000;


public:
    explicit DataValidator(QObject *parent = nullptr);

    static bool isValidForDatabase(const QVector<quint16> &inputs);

signals:
};

#endif // DATAVALIDATOR_H
