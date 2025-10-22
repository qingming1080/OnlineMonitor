#ifndef DATAVALIDATOR_H
#define DATAVALIDATOR_H

#include <QObject>

class DataValidator : public QObject
{
    Q_OBJECT
public:
    static const int MIN_ENERGY             = 0;
    static const int MAX_ENERGY             = 0x2710;

    static const int MIN_AMPLITUDE          = 0;
    static const int MAX_AMPLITUDE          = 0x2710;

    static const int MIN_TP                 = 0;
    static const int MAX_TP                 = 0x2710;

    static const int MIN_WP                 = 0;
    static const int MAX_WP                 = 0x2710;

    static const int MIN_TIME               = 0;
    static const int MAX_TIME               = 0x2710;

    static const int MIN_POWER              = 0;
    static const int MAX_POWER              = 0x2710;

    static const int MIN_PRESSURE           = 0;
    static const int MAX_PRESSURE           = 0x2710;

    static const int MIN_PREHEIGHT          = 0;
    static const int MAX_PREHEIGHT          = 0x2710;

    static const int MIN_POSTHEIGHT         = 0;
    static const int MAX_POSTHEIGHT         = 0x2710;


public:
    explicit DataValidator(QObject *parent = nullptr);

    static bool isValidForDatabase(const QVector<quint16> &inputs);

signals:
};

#endif // DATAVALIDATOR_H
