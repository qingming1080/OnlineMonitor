#ifndef SERVERS_H
#define SERVERS_H

#include <QObject>
#include <QList>
#include <QMutex>
#include "hbserver.h"
#include "protocol/common.h"
#include "ModbusDefine.h"
class ModbusServers : public QObject
{
    Q_OBJECT
public:
    explicit ModbusServers(QObject *parent = nullptr);
    ~ModbusServers();
    void Init();
    void Close();
    void GetState();
private:
    enum QIODevice{
        ETH_0 = 1,
        ETH_1,
        ETH_2,
        ETH_3,
        COM_0,
        COM_1,
        ANALOG_0,
        ANALOG_1,
        END_DEVICE
    };
    static QList<hbServer*>* _ServerList;
    static unsigned char    m_Coils[SYS_COILS_REGISTERS_COUNT + DEV_COILS_REGISTERS_COUNT * DEV_COUNT];
    static unsigned char    m_Discreteds[DEV_DISCRETE_REGISTERS_COUNT * DEV_COUNT];
    static unsigned short   m_Holdings[SYS_HOLDING_REGISTERS_COUNT + DEV_HOLDING_REGISTERS_COUNT * DEV_COUNT];
    static unsigned short   m_Inputs[DEV_INPUT_REGISTERS_COUNT * DEV_COUNT];

    static QMutex m_mutexWeldResult;
    static QMutex m_mutexDeviceStatus;
    static QMutex m_mutexIOStatus;

    int setSystemRegisters  (int address);
    int setDeviceRegisters  (int address);
    int setPresetRegisters  (int address);
    int setRTCRegisters     (int address);
    int setLEDRegisters     (int address);
    int setIORegisters      (int address);
signals:

private slots:
    void slotDataWritten(QModbusDataUnit::RegisterType table, int address, int size);
    void slotWeldResultRead(int iDev, Common* _protocol);
    void slotDeviceStatus(int iDev, bool status);
    void slotButtonReset(bool status);
    void slotIOReset(int iDev, bool status);

};

#endif // SERVERS_H
