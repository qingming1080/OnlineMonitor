#ifndef HBMODBUSCLIENT_H
#define HBMODBUSCLIENT_H

#include <QObject>
#include <QModbusTcpClient>
#include <QModbusDataUnit>
#include <QModbusReply>
#include <QTimer>
#include <QVector>
#include "devicemanager.h"

class HBModbusClient : public QObject
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
     static constexpr char LOCAL_IP[13] = "127.0.0.1";
    // static constexpr char LOCAL_IP[13] = "192.168.1.38";

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

        END_OF_DEV_DISCRETE_REGISTERS = DEV_DISCRETE_REGISTERS_COUNT,

    };

    enum COILS_REGISTERS
    {
        SYS_LED_L_BIT0 = 0,
        SYS_LED_P_BIT1,//
        SYS_LED_R_BIT2,//准备生产,一电就亮,已报警就灭
        SYS_LED_A_BIT3,//
        SYS_BTN_R_BIT4,//王总发

        END_OF_SYS_COILS_REGISTERS = SYS_COILS_REGISTERS_COUNT,
        DEV_REJECT_BIT0, //我来控
        DEV_SUSPECT_BIT1,//我来
        DEV_RESET_BIT2,//王总发

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

        END_OF_DEV_INPUT_REGISTERS = DEV_INPUT_REGISTERS_COUNT
    };

public:
    explicit HBModbusClient(DeviceManager *deviceManager,QObject *parent = nullptr);
    ~HBModbusClient();

    bool connectToServer(const QString &host, int port);                                      // 连接到 Modbus 服务器
    void startReading(int interval);                                                          // 开始定时读取数据

    void readModbusRegisters(QModbusDataUnit::RegisterType registerType, int startAddress, int registerCount, void (HBModbusClient::*finishedSignal)());
    void readDiscreteInputs(int startAddress, int inputCount, void (HBModbusClient::*finishedSignal)());

    //input
    void processDeviceData(Device *device, const QVector<int> &result, int offset);           // 处理设备数据的函数
    void updateTrendData(Device *device, int preHeight, int postHeight, int time, int power);

    //device connetion
    void handleDeviceRemoval(int deviceID, const QMap<int, int>& deviceOffsets);
    QVector<int> prepareDeviceData(Device *device);
    int getBaudRateIndex(int baudRate);
    int getStopBitIndex(double stopBit);
    void writeModbusData(int offset, const QVector<int>& data);



    void resetCoilsToZero();
    void checkAndResetCoils();

    //I.O
    Q_INVOKABLE void setIO(int deviceID,int DEV_WELD_ALARM);
    bool getCoilAddressesAndValues(int deviceID, int DEV_WELD_ALARM, int &coilAddress1, int &coilAddress2, int &coilValue1, int &coilValue2);

    void resetButton();

    void resetCoilsAtAddresses(const QList<int>& addresses);
    void checkAlarmIsAllZero();
    void checkAlarmIsAllZeroRead();


    Q_INVOKABLE void writeSetTime(int year, int month, int day, int hour, int minute, int second);
    Q_INVOKABLE void setLED(bool state);


    static unsigned char    m_Coils[SYS_COILS_REGISTERS_COUNT + DEV_COILS_REGISTERS_COUNT * DEV_COUNT];
    static unsigned char    m_Discreteds[DEV_DISCRETE_REGISTERS_COUNT * DEV_COUNT];
    static unsigned short   m_Holdings[SYS_HOLDING_REGISTERS_COUNT + DEV_HOLDING_REGISTERS_COUNT * DEV_COUNT];
    static unsigned short   m_Inputs[DEV_INPUT_REGISTERS_COUNT * DEV_COUNT];

signals:
    void dataReceived(const QVector<int>& result);
    void reconnected();


public slots:

    void onModbusError(QModbusDevice::Error error);
    void onModbusStateChanged(QModbusDevice::State state);

    void attemptReconnect();                            // 尝试重连
    void readModbusData();                              // 读取 Modbus 数据


    void CoilsReadyRead();                              // read colis
    void HoldingsReadyRead();                           // read holdings
    void InputsReadyRead();                             // read input
    void DiscretedsReadyRead();                         // read discreteds
    void coilWriteFinished();
    void onDeviceNumChanged();


private:

    //IO/地址
    QList<int> alarmIoAddress = {11, 12, 16, 17, 21, 22, 26, 27};
    QMap<int, bool> coilStatus;
    int readCounter = 0;


private:
    QModbusTcpClient *modbusClient;               // Modbus TCP 客户端

    QTimer *readTimer;                            // 定时器，用于定时读取数据
    QTimer *writeTimer;                           // 定时器，用于定时读取数据
    QTimer *reconnectTimer;                       // 重连定时器
    DeviceManager *m_deviceManager;               // 设备管理器，处理设备数据
    QMap<int, int> m_lastCycleCounts;             //存储每个设备  lastCycleCounts


};

#endif // HBMODBUSCLIENT_H
