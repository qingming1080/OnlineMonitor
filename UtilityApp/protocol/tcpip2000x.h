#ifndef TCPIP2___X_H
#define TCPIP2___X_H

#include <QObject>
#include "common.h"

class TcpIp2000x : public Common
{
public:
    TcpIp2000x();
    virtual int ParseWeldResult(QString weldResult) override;
};

#endif // TCPIP2___X_H
