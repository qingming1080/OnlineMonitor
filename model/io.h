#ifndef IO_H
#define IO_H

#include <QObject>

class IO : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool availabel READ availabel WRITE setAvailabel NOTIFY availabelChanged)
public:
    explicit IO(int welderID = 0, QObject *parent = nullptr);

    bool availabel() const;
    Q_INVOKABLE void setAvailabel(bool newAvailabel);

signals:


    void availabelChanged();

private:
    const int m_welderID;
    int m_ioID;

    bool m_availabel;

};

#endif // IO_H
