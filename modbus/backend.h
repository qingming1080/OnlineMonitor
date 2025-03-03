#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <QDebug>

class backend : public QObject
{
    Q_OBJECT
public:
    explicit backend(QObject *parent = nullptr);

    Q_INVOKABLE void setTime(const QString &year, const QString &month, const QString &day,
                             const QString &hour, const QString &minute, const QString &second);

signals:
};

#endif // BACKEND_H
