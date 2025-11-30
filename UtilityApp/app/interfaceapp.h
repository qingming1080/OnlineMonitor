#ifndef INTERFACEAPP_H
#define INTERFACEAPP_H

#include <QObject>
#include <QMutex>
#include "../protocol/common.h"
class InterfaceApp : public QObject
{
    Q_OBJECT
public:
    enum DEVICE_TYPE
    {
        ETHERNET = 0,
        SERIAL,
        ANALOG
    };
    explicit InterfaceApp(QObject *parent = nullptr);
    virtual int Attach(const int iDev, const int ProtocolType, const void* _properties) = 0;
    virtual int Detach(const int iDev) = 0;
    virtual int Init(const void* _properties) = 0;
    virtual int Open(int index, const void* _properties) = 0;
    virtual int Close(int index) = 0;
    virtual int Update(const int iDev, const Common::WELD_SETTING* _setting) = 0;
protected:
    QMutex m_mutexDev;
    QMutex m_mutexWeldResult;
signals:
};

#endif // INTERFACEAPP_H
