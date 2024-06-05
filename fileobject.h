#ifndef FILEOBJECT_H
#define FILEOBJECT_H

#include <QObject>

class FileObject : public QObject
{
    Q_OBJECT
public:
    explicit FileObject(QObject *parent = nullptr);

signals:

public slots:
};

#endif // FILEOBJECT_H
