#ifndef HBMODBUSCLIENT_H
#define HBMODBUSCLIENT_H

#include <QObject>
#include <QModbusTcpClient>
#include <QModbusReply>
#include <QTimer>
#include <QVector>
#include <QMutex>
#include "define.h"

class HBModbusClient : public QObject
{
    Q_OBJECT

public:

    static HBModbusClient* getInstance();
    ~HBModbusClient();

    Q_INVOKABLE void writeHoldingRegisters(int start, const QVector<quint16>& values);
    Q_INVOKABLE void writeCoils(int start, const QVector<quint8>& values);

    //LED
    Q_INVOKABLE void setLearnLedStatus(bool condition);
    Q_INVOKABLE void setPilotLedStatus(bool condition);
    Q_INVOKABLE void setReadyLedStatus(bool condition);
    Q_INVOKABLE void setAlarmLedStatus(bool condition);

    //IO
    Q_INVOKABLE void setDeviceIOStatusReject(int deviceId, bool condition);
    Q_INVOKABLE void setDeviceIOStatusSuspect(int deviceId, bool condition);

    //RTC
    Q_INVOKABLE void setSystemClock(int year, int month, int day, int hour, int minute, int second);

    Q_INVOKABLE void setMesConfig(const QVector<quint16> mesHostValues);

    Q_INVOKABLE void setDeviceConfigData(int deviceId, const QVector<quint16> deviceValues);

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
    static constexpr char LOCAL_IP[13] = "192.168.1.38";
#else
    static constexpr char LOCAL_IP[13] = "127.0.0.1";
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

         //read or write
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

     enum DISCRETE_REGISTERS //only read
     {
         DEV_STATUE = 0,
         DEV_DATA_STATUE,

         END_OF_DEV_DISCRETE_REGISTERS = DEV_DISCRETE_REGISTERS_COUNT * DEV_COUNT,

     };

     enum COILS_REGISTERS
     {
         SYS_LED_L_BIT0 = 0,
         SYS_LED_P_BIT1,
         SYS_LED_R_BIT2,
         SYS_LED_A_BIT3,
         SYS_BTN_R_BIT4,

         END_OF_SYS_COILS_REGISTERS = SYS_COILS_REGISTERS_COUNT,
         DEV_REJECT_BIT0,
         DEV_SUSPECT_BIT1,
         DEV_RESET_BIT2,

         END_OF_DEV_COILS_REGISTERS = (SYS_COILS_REGISTERS_COUNT + DEV_COILS_REGISTERS_COUNT * DEV_COUNT),

     };

     enum INPUT_REGISTERS //only read
     {
         DEV_CYCLE_COUNT_H = 0,
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

         END_OF_DEV_INPUT_REGISTERS = DEV_INPUT_REGISTERS_COUNT * DEV_COUNT,
     };



protected:
    explicit HBModbusClient(QObject *parent = nullptr);

private:
    bool connectToServer(const QString &host, int port);
    void reconnectToServer();

    void dispatchInputsOnCycleCountChanged();

    void dispatchDevicePresetData();

    void dispatchDeviceStatus();

    void dispatchResetButton();

    void dispatchDeviceIOResetStatus();

    template<typename Setter>
    void pollRegisters(QModbusDataUnit::RegisterType type, int count, Setter setter, const char* errMsg);

    void pollAllRegisters(QModbusDataUnit::RegisterType type, int count, const char* errMsg);

    void pollHoldings(int start, int count, const char* errMsg);

    void Init();

signals:

    void weldResultDataChanged(int deviceId, const WELD_RESULTDATA &data);

    void presetDataChanged(int deviceId, const WELD_PRESETDATA &data);

    void deviceIOResetChanged(int deviceId, const WELD_IORESTSTATUS &data);

    void deviceStatusChanged(int deviceId, const WELD_STATUS &data);

    void resetButtonChanged(const WELD_IORESTSTATUS &data);

public slots:

    void onPollTimeout();

private:
    static unsigned char    m_Coils[SYS_COILS_REGISTERS_COUNT + DEV_COILS_REGISTERS_COUNT * DEV_COUNT];
    static unsigned char    m_LastDiscreteds[DEV_DISCRETE_REGISTERS_COUNT * DEV_COUNT];
    static unsigned char    m_Discreteds[DEV_DISCRETE_REGISTERS_COUNT * DEV_COUNT];
    static unsigned short   m_Holdings[SYS_HOLDING_REGISTERS_COUNT + DEV_HOLDING_REGISTERS_COUNT * DEV_COUNT];
    static unsigned short   m_Inputs[DEV_INPUT_REGISTERS_COUNT * DEV_COUNT];

    static HBModbusClient* m_instance;

    QModbusTcpClient *modbusClient;

    QTimer *m_timer;

    mutable QMutex m_mutex;
};

#endif // HBMODBUSCLIENT_H
