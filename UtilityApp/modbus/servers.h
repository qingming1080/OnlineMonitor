#ifndef SERVERS_H
#define SERVERS_H

#include <QObject>
#include <QList>
#include <QMutex>
#include "hbserver.h"
#include "protocol/common.h"
class ModbusServers : public QObject
{
    Q_OBJECT
public:
    static constexpr int DEV_HOLDING_REGISTERS_COUNT = 30;
    static constexpr int DEV_COILS_REGISTERS_COUNT   = 5;
    static constexpr int DEV_DISCRETE_REGISTERS_COUNT = 5;
    static constexpr int DEV_INPUT_REGISTERS_COUNT = 30;
    static constexpr int DEV_COUNT = 4;

    static constexpr int SYS_HOLDING_REGISTERS_COUNT = 20;
    static constexpr int SYS_INPUT_REGISTERS_COUNT = 10;
    static constexpr int SYS_COILS_REGISTERS_COUNT = 10;

    static constexpr int HOLDING_REGISTERS_ADDRESS_BASE =  SYS_HOLDING_REGISTERS_COUNT;
    static constexpr int COILS_REGISTERS_ADDRESS_BASE = SYS_COILS_REGISTERS_COUNT;

    static constexpr int SERVER_PORT = 502;
#ifdef RASPBERRY
    static constexpr char LOCAL_IP[13] = "127.0.0.1";
#else
    static constexpr char LOCAL_IP[13] = "192.168.1.5";
#endif
    enum HOLDING_REGISTERS
    {
        SYS_RTC_YY = 0,
        SYS_RTC_YY_MM,
        SYS_RTC_DD,
        SYS_RTC_HH,
        SYS_RTC_MM,
        SYS_RTC_SS,

        SYS_MES_IP1,
        SYS_MES_IP2,
        SYS_MES_IP3,
        SYS_MES_IP4,
        SYS_MES_Port,
        SYS_HOST_IP1,
        SYS_HOST_IP2,
        SYS_HOST_IP3,
        SYS_HOST_IP4,
        END_OF_SYS_HOLDING_REGISTER = SYS_HOLDING_REGISTERS_COUNT,

        DEV_TYPE, // 0 Ethernet, 1 Serial, 2 analog
        DEV_PROTOCOL_TYPE, // 0 VG, 1, TC, 2 2000X
        DEV_AVAILABLE, // 0 Close, 1 Open

        DEV_SERVER_IP1,
        DEV_SERVER_IP2,
        DEV_SERVER_IP3,
        DEV_SERVER_IP4,

        DEV_LOCAL_IP1,
        DEV_LOCAL_IP2,
        DEV_LOCAL_IP3,
        DEV_LOCAL_IP4,
        DEV_SERVER_PORT,

        DEV_COM_NUM,
        DEV_BAUD_RATE,
        DEV_DATA_BIT,
        DEV_PARITY_BIT,
        DEV_STOP_BIT,

        DEV_ENERGY_SET,
        DEV_AMPLITUDE_SET,
        DEV_TP_SET,
        DEV_WP_SET,

        DEV_TIME_MIN,
        DEV_TIME_MAX,
        DEV_POWER_MIN,
        DEV_POWER_MAX,
        DEV_PRE_HEIGHT_MIN,
        DEV_PRE_HEIGHT_MAX,
        DEV_POST_HEIGHT_MIN,
        DEV_POST_HEIGHT_MAX,


        END_OF_DEV_HOLDING_REGISTER = (SYS_HOLDING_REGISTERS_COUNT + DEV_HOLDING_REGISTERS_COUNT * DEV_COUNT)

    };

    enum DISCRETE_REGISTERS
    {
        DEV_STATUE = 0,
        DEV_DATA_STATUE,

        END_OF_DEV_DISCRETE_REGISTERS = DEV_DISCRETE_REGISTERS_COUNT,

    };

    enum COILS_REGISTERS
    {
        SYS_LED_L_BIT0 = 0, //Learning
        SYS_LED_P_BIT1,     //Pilot Run
        SYS_LED_R_BIT2,     //Ready
        SYS_LED_A_BIT3,     //Alarm
        SYS_BTN_R_BIT4,     //Reset Button

        END_OF_SYS_COILS_REGISTERS = SYS_COILS_REGISTERS_COUNT,

        DEV_REJECT_BIT0,
        DEV_SUSPECT_BIT1,
        DEV_RESET_BIT2,

        END_OF_DEV_COILS_REGISTERS = (SYS_COILS_REGISTERS_COUNT + DEV_COILS_REGISTERS_COUNT * DEV_COUNT),

    };

    enum INPUT_REGISTERS
    {
        DEV_CYCLE_COUNT_H,
        DEV_CYCLE_COUNT_L,
        DEV_ENERGY,
        DEV_AMPLITUDE,
        DEV_TP,
        DEV_WP,

        DEV_TIME,
        DEV_POWER,
        DEV_PRE_HEIGHT,
        DEV_POST_HEIGHT,

        DEV_WELD_ALARM,



        DEV_YY,
        DEV_YY_MM,
        DEV_DD,
        DEV_HH,
        DEV_MM,
        DEV_SS,

        END_OF_DEV_INPUT_REGISTERS = DEV_INPUT_REGISTERS_COUNT
    };

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
