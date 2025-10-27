#ifndef HBMODBUSCLIENT_H
#define HBMODBUSCLIENT_H

#include <QObject>
#include <QModbusTcpClient>
#include <QModbusReply>
#include <QTimer>
#include <QVector>
#include <QMutex>
#include "define.h"
#include "model/deviceinformation.h"
#include <QSerialPort>

class HBModbusClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool ResetButtonStatus READ getResetButtonStatus WRITE setResetButtonStatus NOTIFY notifyResetButtonStatus FINAL)
public:

    static HBModbusClient* getInstance();
    ~HBModbusClient();

    //LED
    Q_INVOKABLE void setLearnLedStatus(const bool condition);
    Q_INVOKABLE void setPilotLedStatus(const bool condition);
    Q_INVOKABLE void setReadyLedStatus(const bool condition);
    Q_INVOKABLE void setAlarmLedStatus(const bool condition);

    //IO
    Q_INVOKABLE void setDeviceIOStatusReject(const int deviceId, const bool condition);
    Q_INVOKABLE void setDeviceIOStatusSuspect(const int deviceId, const bool condition);

    //RTC
    Q_INVOKABLE void setSystemClock(const QDateTime &datetime);

    Q_INVOKABLE void setDeviceConfigure(const int deviceId, const DeviceInformation::MODBUS_CONFIGURE deviceConfig);

    //TODO Need to move others.
    Q_INVOKABLE void setMesConfig(const QVector<quint16> mesHostValues);

    void setResetButtonStatus(const bool status);
    bool getResetButtonStatus() const;

    Q_INVOKABLE void testAllFunctions();

private:
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

    static unsigned int m_iPreviousCycleCount[DEV_COUNT];

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


     enum  BaudRate
     {
       Baud_2400 = 0,
       Baud_4800 = 1,
       Baud_9600 = 2,
       Baud_19200 = 3,
       Baud_38400 = 4,
       Baud_115200 = 5
     };

     enum  DataBit
     {
        Bit7 = 0,
        Bit8 = 1
     };
     enum  ParityBit
     {
       None = 0,
       Odd = 1,
       Even = 2
     };
     enum  StopBit
     {
         Bit1 = 0,
         Bit1_5 = 1,
         Bit2 = 2
     };

protected:
    explicit HBModbusClient(QObject *parent = nullptr);

private:
    bool connectToServer(const QString &host, int port);
    void reconnectToServer();

    void WriteHoldingRegisters(int startAddress, const QVector<quint16>& values);
    void WriteCoils(int startAddress, const QVector<quint8>& values);

    void ParseWeldResult();

    void ParsePresetSetting();

    void ParseDeviceStatus();

    void ParseResetButton();

    void ParseDeviceIOResetStatus();

    template<typename Setter>
    void pollRegisters(QModbusDataUnit::RegisterType type, int count, Setter setter, const char* errMsg);

    void pollAllRegisters(QModbusDataUnit::RegisterType type, int count, const char* errMsg);

    void pollHoldings(int start, int count, const char* errMsg);

    //Serial
    BaudRate fromQtBaudRate(QSerialPort::BaudRate baud);
    DataBit  fromQtDataBits(QSerialPort::DataBits bit);
    ParityBit fromQtParity(QSerialPort::Parity parity);
    StopBit   fromQtStopBits(QSerialPort::StopBits stop);


signals:

    void notifyWeldResultComing(int deviceId, const WELD_RESULT& data);

    void notifyPresetSettingChanged(int deviceId, const WELD_PRESET& data);

    void notifyDeviceIOStatusChanged(int deviceId, const IO_STATUS &status);

    void notifyDeviceStatusChanged(int deviceId, const DEVICE_STATUS &status);

    void notifyResetButtonStatus(const bool& status);

public slots:
    void onPollingTimeoutEvent();

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

    bool m_bFrontPanelResetButton;
};

#endif // HBMODBUSCLIENT_H
