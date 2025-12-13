#ifndef HBMODBUSCLIENT_H
#define HBMODBUSCLIENT_H

#include <QObject>
#include <QModbusTcpClient>
#include <QModbusReply>
#include <QTimer>
#include <QVector>
#include <QMutex>
#include "define.h"
#include "model/deviceinfoenum.h"
#include "ModbusDefine.h"
#include <QSerialPort>
#include <QMap>

class HBModbusClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool ResetButtonStatus READ getResetButtonStatus WRITE setResetButtonStatus NOTIFY notifyResetButtonStatus FINAL)
    Q_PROPERTY(bool connected READ isConnected NOTIFY connectionStateChanged)
public:
    struct WELD_PRESET
    {
        int     Energy;
        int     Amplitude;
        int     TriggerPressure;
        int     WeldingPressure;
    };

    struct MODBUS_WELD_RESULT
    {
        int         CycleCount;
        int         Energy;
        int         Amplitude;
        int         TriggerPressure;
        int         WeldingPressure;
        int         WeldTime;
        int         PeakPower;
        int         Preheight;
        int         PostHeight;
        int         WeldAlarm;
        QDateTime   DateTime;
    };

    struct NETWORK_PROPERTIES
    {
        int     EthNumber;
        QString LocalIP;
        QString RemoteIP;
        int     PortNumber;
    };

    struct SERIAL_PROPERTIES
    {
        int ComNumber;
        QSerialPort::BaudRate BaudRate;
        QSerialPort::DataBits DataBits;
        QSerialPort::Parity   ParityBits;
        QSerialPort::StopBits StopBits;
    };

    struct MODBUS_CONFIGURE
    {
        DeviceInfoEnum::CONNECT_TYPE    ConnectType;    // 连接方式     0_RS232  1_Network
        DeviceInfoEnum::WLEDER_TYPE     ProtocolType;   // 焊机型号
        DeviceInfoEnum::CONNECT_STATE   ConnectState;   // 连接state
        DeviceInfoEnum::NETWORK_TYPE    NetworkType;
        NETWORK_PROPERTIES              NetworkProperties;
        SERIAL_PROPERTIES               SerialProperties;
    };

    struct DEVICE_STATUS
    {
        bool    IsDeviceStatus;
        bool    IsDeviceDataStatus;
    };

public:
    static HBModbusClient* getInstance();
    ~HBModbusClient();

    bool isConnected() const;

    //LED
    Q_INVOKABLE void setLearnLedStatus(const bool condition);
    Q_INVOKABLE void setPilotLedStatus(const bool condition);
    Q_INVOKABLE void setReadyLedStatus(const bool condition);
    Q_INVOKABLE void setAlarmLedStatus(const bool condition);

    //IO
    Q_INVOKABLE void setDeviceIOStatusReject(const int welderId, const bool condition);
    Q_INVOKABLE void setDeviceIOStatusSuspect(const int welderId, const bool condition);

    //RTC
    Q_INVOKABLE void setSystemClock(const QDateTime &datetime);

    void setDeviceConfigure(const int welderId, const MODBUS_CONFIGURE deviceConfig);
    void removeDeviceConfigure(const int welderId, const MODBUS_CONFIGURE deviceConfig);

    //TODO Need to move others.
    Q_INVOKABLE void setMesConfig(const QVector<quint16> mesHostValues);

    void setResetButtonStatus(const bool status);
    bool getResetButtonStatus() const;

    Q_INVOKABLE void testAllFunctions();

private:
    static unsigned int m_iPreviousCycleCount[DEV_COUNT];

    enum BaudRate
    {
        Baud_2400 = 0,
        Baud_4800 = 1,
        Baud_9600 = 2,
        Baud_19200 = 3,
        Baud_38400 = 4,
        Baud_115200 = 5
    };

    enum DataBit
    {
        Bit7 = 0,
        Bit8 = 1
    };

    enum ParityBit
    {
        None = 0,
        Odd = 1,
        Even = 2
    };

    enum StopBit
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

    void updateLedStatus(int ledIndex, bool condition);

    void readRegisters(QModbusDataUnit::RegisterType type,int startAddress, int count, const char* errMsg);

    //Serial
    BaudRate    fromQtBaudRate(QSerialPort::BaudRate baud);
    DataBit     fromQtDataBits(QSerialPort::DataBits bit);
    ParityBit   fromQtParity(QSerialPort::Parity parity);
    StopBit     fromQtStopBits(QSerialPort::StopBits stop);


signals:
    void notifyWeldResultComing(int welderId, const MODBUS_WELD_RESULT& data);

    void notifyPresetSettingChanged(int welderId, const WELD_PRESET& data);

    void notifyDeviceIOStatusChanged(int welderId, const IO_STATUS &status);

    void notifyDeviceStatusChanged(int welderId, DEVICE_STATUS status);

    void notifyResetButtonStatus(const bool& status);

    void connectionStateChanged(bool connected);

public slots:
    void onPollingTimeoutEvent();
    void onStateChanged(QModbusDevice::State state);

private:
    static unsigned char    m_Coils[SYS_COILS_REGISTERS_COUNT + DEV_COILS_REGISTERS_COUNT * DEV_COUNT];
    static unsigned char    m_LastDiscreteds[DEV_DISCRETE_REGISTERS_COUNT * DEV_COUNT];
    static unsigned char    m_Discreteds[DEV_DISCRETE_REGISTERS_COUNT * DEV_COUNT];
    static unsigned short   m_Holdings[SYS_HOLDING_REGISTERS_COUNT + DEV_HOLDING_REGISTERS_COUNT * DEV_COUNT];
    static unsigned short   m_Inputs[DEV_INPUT_REGISTERS_COUNT * DEV_COUNT];
    static QVector<WELD_PRESET> m_lastPresets;
    static HBModbusClient* m_instance;
    QModbusTcpClient *modbusClient;
    QTimer *m_timer;
    mutable QMutex m_mutex;
    bool m_bFrontPanelResetButton;
    bool m_isFirstPresetParse = true;
    QMap<int, int> m_WelderDeviceMap; //welderId, deviceId
    bool m_connected = false;
};

#endif // HBMODBUSCLIENT_H
