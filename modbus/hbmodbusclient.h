#ifndef HBMODBUSCLIENT_H
#define HBMODBUSCLIENT_H

#include <QObject>
#include <QModbusTcpClient>
#include <QModbusReply>
#include <QTimer>
#include <QVector>
#include <QMutex>
#include "model/device.h"
#include "tools/devicemodbusmapper.h"

class HBModbusClient : public QObject
{
    Q_OBJECT

public:

    static HBModbusClient* getInstance();
    ~HBModbusClient();

    void Init();

    int calculateBaseAddress(int devId) const;

    template<typename T>
    QVector<T> readRegisters(QModbusDataUnit::RegisterType type, int start, int count);
    Q_INVOKABLE void writeHoldingRegisters(int start, const QVector<quint16>& values);
    Q_INVOKABLE void writeCoils(int start, const QVector<quint8>& values);

    template<typename Setter>
    void pollRegisters(QModbusDataUnit::RegisterType type, int count, Setter setter, const char* errMsg);

    void pollAllRegisters(QModbusDataUnit::RegisterType type, int count, const char* errMsg);

    void pollHoldings(int start, int count, const char* errMsg);

    void processRegister(QModbusDataUnit::RegisterType type, int address, quint16 value);

    // 只在CycleCount变化时，批量分发所有输入寄存器到UI和数据库
    void dispatchInputsOnCycleCountChanged();
    // 获取指定设备的某个输入寄存器值（设备ID: 1~DEV_COUNT，regEnum为INPUT_REGISTERS枚举）
    quint16 getInputRegister(int devId, int regEnum) const;

    // 获取指定设备的全部输入寄存器（返回QVector，便于UI/DeviceManager批量处理）
    QVector<quint16> getDeviceInputs(int devId) const;

    // 刷新指定设备的曲线数据（Power/Time/PreHeight/PostHeight）
    void updateDeviceTrend(Device* dev, quint16 power, quint16 time, quint16 preHeight, quint16 postHeight);

    Q_INVOKABLE void setRTC(int year, int month, int day, int hour, int minute, int second);

    Q_INVOKABLE void setSysLedStatus(bool condition);

    Q_INVOKABLE void handleDeviceCoilStatus(int devId, int value); // Updated to handle resetIdx logic

    void updateDeviceConnectionStates();

    void updateDeviceConnectionStates(const QVector<int>& result);

    void writeDeviceConfig(int deviceId, const DeviceModbusMapper::DeviceRegisterData &data);



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

         END_OF_DEV_INPUT_REGISTERS = DEV_INPUT_REGISTERS_COUNT * DEV_COUNT,
     };



protected:
    explicit HBModbusClient(QObject *parent = nullptr);

private:
    bool connectToServer(const QString &host, int port);
    void disconnect();
    void reconnectToServer();

    void processSysBtnRBit4();
    void clearRejectAndSuspectForDevice(int devId);

    void updateSysLedStatus(); // Ensure LED status reflects device states

signals:

    void connectedChanged(bool connected);

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

    QTimer* m_reconnectTimer;

    QMutex m_mutex;

    bool m_updateLedStatus = false; // 标志位：是否需要更新LED状态
};

#endif // HBMODBUSCLIENT_H
