 #include "servers.h"
#include <QHostAddress>
#include <QDateTime>
#include "proxy.h"
#include "definition.h"
#include "app/interfaceapp.h"
#include "app/ethernetapp.h"
#include "app/serialapp.h"
#include "app/systemclock.h"
#include "protocol/common.h"
#include "app/gpioapp.h"
#define MODBUS_DEBUG 1
QList<hbServer*>* ModbusServers::_ServerList = nullptr;
// constexpr char ModbusServers::LOCAL_IP[13];
// constexpr int ModbusServers::SERVER_PORT;
unsigned char ModbusServers::m_Coils[SYS_COILS_REGISTERS_COUNT + DEV_COILS_REGISTERS_COUNT * DEV_COUNT] = {0};
unsigned char ModbusServers::m_Discreteds[DEV_DISCRETE_REGISTERS_COUNT * DEV_COUNT] = {0};
unsigned short ModbusServers::m_Holdings[SYS_HOLDING_REGISTERS_COUNT + DEV_HOLDING_REGISTERS_COUNT * DEV_COUNT] = {0};
unsigned short ModbusServers::m_Inputs[DEV_INPUT_REGISTERS_COUNT * DEV_COUNT] = {0};
QMutex ModbusServers::m_mutexWeldResult;
QMutex ModbusServers::m_mutexDeviceStatus;
QMutex ModbusServers::m_mutexIOStatus;
ModbusServers::ModbusServers(QObject *parent)
    : QObject{parent}
{
    _ServerList = new QList<hbServer*>();


    hbServer* tmpServer = new hbServer();
    tmpServer->setServerAddress(ETH_0);
    _ServerList->append(tmpServer);
    connect(_ServerList->at(0), &QModbusTcpServer::dataWritten, this, &ModbusServers::slotDataWritten);
    connect(EthernetApp::GetInstance(), &EthernetApp::signalWeldResultReady, this, &ModbusServers::slotWeldResultRead);
    connect(SerialApp::GetInstance(), &SerialApp::signalWeldResultReady, this, &ModbusServers::slotWeldResultRead);

    connect(EthernetApp::GetInstance(), &EthernetApp::signalDeviceStatus, this, &ModbusServers::slotDeviceStatus);
    connect(SerialApp::GetInstance(), &SerialApp::signalDeviceStatus, this, &ModbusServers::slotDeviceStatus);

    connect(GpioApp::GetInstance(), &GpioApp::signalButtonReset, this, &ModbusServers::slotButtonReset);
    connect(GpioApp::GetInstance(), &GpioApp::signalIOReset,     this, &ModbusServers::slotIOReset);

}

ModbusServers::~ModbusServers()
{
    for(int i = 0; i < _ServerList->size(); i++)
    {
        _ServerList->at(i)->deleteLater();
    }
    _ServerList->clear();
    delete _ServerList;
}

void ModbusServers::Init()
{
    QModbusDataUnitMap reg;
    reg.insert(QModbusDataUnit::Coils, {QModbusDataUnit::Coils, 0, SYS_COILS_REGISTERS_COUNT + DEV_COILS_REGISTERS_COUNT * DEV_COUNT});
    reg.insert(QModbusDataUnit::DiscreteInputs, {QModbusDataUnit::DiscreteInputs, 0, DEV_DISCRETE_REGISTERS_COUNT * DEV_COUNT});
    reg.insert(QModbusDataUnit::HoldingRegisters, { QModbusDataUnit::HoldingRegisters, 0, SYS_HOLDING_REGISTERS_COUNT + DEV_HOLDING_REGISTERS_COUNT *  DEV_COUNT});
    reg.insert(QModbusDataUnit::InputRegisters, { QModbusDataUnit::InputRegisters, 0, DEV_INPUT_REGISTERS_COUNT * DEV_COUNT });
    _ServerList->at(0)->setMap(reg);
    _ServerList->at(0)->Listen(SERVER_PORT, QString(LOCAL_IP));

}

void ModbusServers::GetState()
{
    qDebug() << _ServerList->at(0)->state();
}

void ModbusServers::slotDataWritten(QModbusDataUnit::RegisterType table, int address, int size)
{
    qDebug() << "address: " << address;
    qDebug() << "size: " << size;
    qDebug() << "table: " << table;
    for (int i = 0; i < size; ++i)
    {
        quint16 value;
        switch (table)
        {
        case QModbusDataUnit::Coils:
            _ServerList->at(0)->data(QModbusDataUnit::Coils,            quint16(address + i), &value);
            m_Coils[address + i] = value;
            break;
        case QModbusDataUnit::HoldingRegisters:
            _ServerList->at(0)->data(QModbusDataUnit::HoldingRegisters, quint16(address + i), &value);
            m_Holdings[address + i] = value;
            qDebug() << "Address: " << address + i << " " << "Value: " << value;
            break;
        case QModbusDataUnit::InputRegisters:
            _ServerList->at(0)->data(QModbusDataUnit::InputRegisters,   quint16(address + i), &value);
            break;
        case QModbusDataUnit::DiscreteInputs:
            _ServerList->at(0)->data(QModbusDataUnit::DiscreteInputs,   quint16(address + i), &value);
            m_Discreteds[address + i] = value;
            break;
        default:
            break;
        }
    }

    if(table == QModbusDataUnit::HoldingRegisters)
    {
        // int devIndex = setDeviceRegisters(address);
        // if(devIndex != ERROR)
        //     Proxy::GetInstance()->ImplementSettings(devIndex);

        setRTCRegisters(address);
        setDeviceRegisters(address);
        setPresetRegisters(address);
    }
    else if(table == QModbusDataUnit::Coils)
    {
        setLEDRegisters(address);
        setIORegisters(address);
    }
}

void ModbusServers::slotWeldResultRead(int iDev, Common *_protocol)
{
    m_mutexWeldResult.lock();
    Common::WELD_RESULT  weldResult;
    Common::WELD_SETTING weldSetting;

    _protocol->GetWeldResult(&weldResult);
    _protocol->GetWeldSetting(&weldSetting);
    int address = DEV_CYCLE_COUNT_H + iDev * DEV_INPUT_REGISTERS_COUNT;
    m_Inputs[address] = (weldResult.CycleCount>>16) & 0xFFFF;
    _ServerList->at(0)->setData(QModbusDataUnit::InputRegisters, address, m_Inputs[address]);

    address++;
    m_Inputs[address] = (weldResult.CycleCount & 0xFFFF);
    _ServerList->at(0)->setData(QModbusDataUnit::InputRegisters, address, m_Inputs[address]);

    address++;
    m_Inputs[address] = weldResult.Energy;
    _ServerList->at(0)->setData(QModbusDataUnit::InputRegisters, address, m_Inputs[address]);

    address++;
    m_Inputs[address] = weldResult.Amplitude;
    _ServerList->at(0)->setData(QModbusDataUnit::InputRegisters, address, m_Inputs[address]);

    address++;
    m_Inputs[address] = weldResult.TPressure;
    _ServerList->at(0)->setData(QModbusDataUnit::InputRegisters, address, m_Inputs[address]);

    address++;
    m_Inputs[address] = weldResult.WPressure;
    _ServerList->at(0)->setData(QModbusDataUnit::InputRegisters, address, m_Inputs[address]);

    address++;
    m_Inputs[address] = weldResult.Time;
    _ServerList->at(0)->setData(QModbusDataUnit::InputRegisters, address, m_Inputs[address]);

    address++;
    m_Inputs[address] = weldResult.Power;
    _ServerList->at(0)->setData(QModbusDataUnit::InputRegisters, address, m_Inputs[address]);

    address++;
    m_Inputs[address] = weldResult.Preheight;
    _ServerList->at(0)->setData(QModbusDataUnit::InputRegisters, address, m_Inputs[address]);

    address++;
    m_Inputs[address] = weldResult.PostHeight;
    _ServerList->at(0)->setData(QModbusDataUnit::InputRegisters, address, m_Inputs[address]);

    address++;
    m_Inputs[address] = weldResult.AlarmFlag;
    _ServerList->at(0)->setData(QModbusDataUnit::InputRegisters, address, m_Inputs[address]);

    QDateTime datetime = QDateTime::currentDateTime();
    QDate date = datetime.date();
    QTime time = datetime.time();
    address++;
    m_Inputs[address] = date.year();
    _ServerList->at(0)->setData(QModbusDataUnit::InputRegisters, address, m_Inputs[address]);
    address++;
    m_Inputs[address] = date.month();
    _ServerList->at(0)->setData(QModbusDataUnit::InputRegisters, address, m_Inputs[address]);
    address++;
    m_Inputs[address] = date.day();
    _ServerList->at(0)->setData(QModbusDataUnit::InputRegisters, address, m_Inputs[address]);
    address++;
    m_Inputs[address] = time.hour();
    _ServerList->at(0)->setData(QModbusDataUnit::InputRegisters, address, m_Inputs[address]);
    address++;
    m_Inputs[address] = time.minute();
    _ServerList->at(0)->setData(QModbusDataUnit::InputRegisters, address, m_Inputs[address]);
    address++;
    m_Inputs[address] = time.second();
    _ServerList->at(0)->setData(QModbusDataUnit::InputRegisters, address, m_Inputs[address]);

    address = DEV_ENERGY_SET + iDev * DEV_HOLDING_REGISTERS_COUNT;
    m_Holdings[address] = weldSetting.Energy;
    _ServerList->at(0)->setData(QModbusDataUnit::HoldingRegisters, address, m_Holdings[address]);

    address++;
    m_Holdings[address] = weldSetting.Amplitude;
    _ServerList->at(0)->setData(QModbusDataUnit::HoldingRegisters, address, m_Holdings[address]);

    address++;
    m_Holdings[address] = weldSetting.TPressure;
    _ServerList->at(0)->setData(QModbusDataUnit::HoldingRegisters, address, m_Holdings[address]);

    address++;
    m_Holdings[address] = weldSetting.WPressure;
    _ServerList->at(0)->setData(QModbusDataUnit::HoldingRegisters, address, m_Holdings[address]);

    address++;
    m_Holdings[address] = weldSetting.Time.Min;
    _ServerList->at(0)->setData(QModbusDataUnit::HoldingRegisters, address, m_Holdings[address]);

    address++;
    m_Holdings[address] = weldSetting.Time.Max;
    _ServerList->at(0)->setData(QModbusDataUnit::HoldingRegisters, address, m_Holdings[address]);

    address++;
    m_Holdings[address] = weldSetting.Power.Min;
    _ServerList->at(0)->setData(QModbusDataUnit::HoldingRegisters, address, m_Holdings[address]);

    address++;
    m_Holdings[address] = weldSetting.Power.Max;
    _ServerList->at(0)->setData(QModbusDataUnit::HoldingRegisters, address, m_Holdings[address]);

    address++;
    m_Holdings[address] = weldSetting.Preheight.Min;
    _ServerList->at(0)->setData(QModbusDataUnit::HoldingRegisters, address, m_Holdings[address]);

    address++;
    m_Holdings[address] = weldSetting.Preheight.Max;
    _ServerList->at(0)->setData(QModbusDataUnit::HoldingRegisters, address, m_Holdings[address]);

    address++;
    m_Holdings[address] = weldSetting.PostHeight.Min;
    _ServerList->at(0)->setData(QModbusDataUnit::HoldingRegisters, address, m_Holdings[address]);

    address++;
    m_Holdings[address] = weldSetting.PostHeight.Max;
    _ServerList->at(0)->setData(QModbusDataUnit::HoldingRegisters, address, m_Holdings[address]);


    m_mutexWeldResult.unlock();
}

void ModbusServers::slotDeviceStatus(int iDev, bool status)
{
    m_mutexDeviceStatus.lock();
    int address = DEV_DATA_STATUE + iDev * DEV_DISCRETE_REGISTERS_COUNT;
    if(status == true)
        m_Discreteds[address] = ON;
    else
        m_Discreteds[address] = OFF;
    _ServerList->at(0)->setData(QModbusDataUnit::DiscreteInputs, address, m_Discreteds[address]);
    m_mutexDeviceStatus.unlock();
}

void ModbusServers::slotButtonReset(bool status)
{
    int address = SYS_BTN_R_BIT4;
    if(status == true)
        m_Coils[address] = ON;
    else
        m_Coils[address] = OFF;
    _ServerList->at(0)->setData(QModbusDataUnit::Coils, address, m_Coils[address]);
}

void ModbusServers::slotIOReset(int iDev, bool status)
{
    m_mutexIOStatus.lock();
    int address = DEV_RESET_BIT2 + iDev * DEV_COILS_REGISTERS_COUNT;
    if(status == true)
        m_Coils[address] = ON;
    else
        m_Coils[address] = OFF;
    _ServerList->at(0)->setData(QModbusDataUnit::Coils, address, m_Coils[address]);
    m_mutexIOStatus.unlock();
}

int ModbusServers::setSystemRegisters(int address)
{
    if(address == SYS_RTC_YY)
        return OK;
    else
        return ERROR;
}

int ModbusServers::setDeviceRegisters(int address)
{
    int iResult = -1;
    int index = address;
    Proxy* _proxy = Proxy::GetInstance();
    Proxy::MACHINE_DEVICE       machineDevice;
    EthernetApp::ETHERNET_DEV   ethernetDevice;
    SerialApp::SERIAL_DEV       serialDevice;
    for(int j = 0; j < DEV_COUNT; j++)
    {
        if(address == (DEV_TYPE + j * DEV_HOLDING_REGISTERS_COUNT))
        {
            machineDevice.Type = static_cast<InterfaceApp::DEVICE_TYPE>(m_Holdings[index]);
            index++;
            machineDevice.Protocol = static_cast<Common::DEVICE_PROTOCOL_TYPE>(m_Holdings[index]);
            index++;
            machineDevice.IsOpen = m_Holdings[index];
            _proxy->UpdateMachineList(j, &machineDevice);
#if MODBUS_DEBUG
            qDebug() << "Type: " << machineDevice.Type;
            qDebug() << "Protocol: " << machineDevice.Protocol;
            qDebug() << "IsOpen: " << machineDevice.IsOpen;
#endif

            index++;
            ethernetDevice.Properties.ServerAddr[0] = m_Holdings[index];
            index++;
            ethernetDevice.Properties.ServerAddr[1] = m_Holdings[index];
            index++;
            ethernetDevice.Properties.ServerAddr[2] = m_Holdings[index];
            index++;
            ethernetDevice.Properties.ServerAddr[3] = m_Holdings[index];
            index++;
            ethernetDevice.Properties.LocalAddr[0] = m_Holdings[index];
            index++;
            ethernetDevice.Properties.LocalAddr[1] = m_Holdings[index];
            index++;
            ethernetDevice.Properties.LocalAddr[2] = m_Holdings[index];
            index++;
            ethernetDevice.Properties.LocalAddr[3] = m_Holdings[index];
            index++;
            ethernetDevice.Properties.ServerPort = m_Holdings[index];

            if(machineDevice.Type == InterfaceApp::ETHERNET)
            {
                _proxy->UpdateEthernetList(j, &ethernetDevice); //TODO
            }

            index++;
            serialDevice.ComIndex = m_Holdings[index];
            index++;
            serialDevice.Properties.m_Bandrate = m_Holdings[index];
            index++;
            serialDevice.Properties.m_DataBits = m_Holdings[index];
            index++;
            serialDevice.Properties.m_Parity = m_Holdings[index];
            index++;
            serialDevice.Properties.m_StopBits = m_Holdings[index];
            if(machineDevice.Type == InterfaceApp::SERIAL)
            {
                _proxy->UpdateSerialList(j, &serialDevice);
            }
            iResult = j;
        }
    }
    return iResult;
}

int ModbusServers::setPresetRegisters(int address)
{
    int iResult = ERROR;
    int index = address;
    Common::WELD_SETTING    weldSetting;
    Proxy* _proxy = Proxy::GetInstance();
    for(int j = 0; j < DEV_COUNT; j++)
    {
        if(address == (DEV_ENERGY_SET + j * DEV_HOLDING_REGISTERS_COUNT))
        {
            weldSetting.Energy = m_Holdings[index];
            index++;
            weldSetting.Amplitude = m_Holdings[index];
            index++;
            weldSetting.TPressure = m_Holdings[index];
            index++;
            weldSetting.WPressure = m_Holdings[index];
            index++;
            weldSetting.Time.Min = m_Holdings[index];
            index++;
            weldSetting.Time.Max = m_Holdings[index];
            index++;
            weldSetting.Power.Min = m_Holdings[index];
            index++;
            weldSetting.Power.Max = m_Holdings[index];
            index++;
            weldSetting.Preheight.Min = m_Holdings[index];
            index++;
            weldSetting.Preheight.Max = m_Holdings[index];
            index++;
            weldSetting.PostHeight.Min = m_Holdings[index];
            index++;
            weldSetting.PostHeight.Max = m_Holdings[index];
            weldSetting.MODE_FLAGS.ModeFlags.WeldMode = 0;
            _proxy->UpdateWeldSettings(j, &weldSetting);
            iResult = j;
        }
    }
    return iResult;
}

int ModbusServers::setRTCRegisters(int address)
{
    int iResult = ERROR;
    int index = address;
    SystemClock::DATE_TIME datetime;
    Proxy* _proxy = Proxy::GetInstance();
    if(address == SYS_RTC_YY)
    {
        datetime.Year = m_Holdings[index];
        index++;
        datetime.Month = m_Holdings[index];
        index++;
        datetime.Day = m_Holdings[index];
        index++;
        datetime.Hour = m_Holdings[index];
        index++;
        datetime.Minute = m_Holdings[index];
        index++;
        datetime.Second = m_Holdings[index];
        _proxy->UpdateSystemClock(&datetime);
        iResult = OK;
    }
    return iResult;
}

int ModbusServers::setLEDRegisters(int address)
{
    int iResult = ERROR;
    int index = address;
    GpioApp::LED led;
    Proxy* _proxy = Proxy::GetInstance();
    if(address == SYS_LED_L_BIT0)
    {
        led.LED_Bits.LED_Learning = m_Coils[index];
        index++;
        led.LED_Bits.LED_PilotRun = m_Coils[index];
        index++;
        led.LED_Bits.LED_Ready = m_Coils[index];
        index++;
        led.LED_Bits.LED_Alarm = m_Coils[index];
        _proxy->UpdateLedStatus(&led);
        iResult = OK;
    }
    return iResult;
}

int ModbusServers::setIORegisters(int address)
{
    int iResult = ERROR;
    int index = address;
    GpioApp::IO gpio;
    Proxy* _proxy = Proxy::GetInstance();
    for(int j = 0; j < DEV_COUNT; j++)
    {
        if(address == (DEV_REJECT_BIT0 + j * DEV_COILS_REGISTERS_COUNT))
        {
            gpio.IO_Bits.IO_Reject = m_Coils[index];
            index++;
            gpio.IO_Bits.IO_Suspect = m_Coils[index];
            _proxy->UpdateIOStatus(j, &gpio);
            iResult = j;
        }
    }
    return iResult;
}
