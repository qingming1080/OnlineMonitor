# UtilityApp Class Diagram

## Overview
This document contains the class diagram for the UtilityApp project, showing the architecture with its layers and relationships.

## Class Diagram

```mermaid
classDiagram
    %% Core Pattern Classes
    class Proxy {
        -QThread WorkerThread
        -QList~MACHINE_DEVICE~ m_listDevice
        -QMutex m_mutexMachine
        +GetInstance()* Proxy
        +UpdateMachineList(int, MACHINE_DEVICE*) int
        +UpdateEthernetList(int, void*) int
        +UpdateSerialList(int, void*) int
        +UpdateWeldSettings(int, WELD_SETTING*) int
        +UpdateSystemClock(void*) int
        +Handle(int) void
    }

    class Subject {
        -QList~MACHINE_DEVICE~ m_listDevice
        -QMap~int, ETHERNET_DEV~ m_mapEthernet
        -QMap~int, SERIAL_DEV~ m_mapSerial
        +Implement(int) void
        +signalReady(int) void
    }

    %% Application Layer
    class InterfaceApp {
        <<abstract>>
        #QMutex m_mutexDev
        #QMutex m_mutexWeldResult
        +Attach(int, int, void*)* int
        +Detach(int)* int
        +Init(void*)* int
        +Open(int, void*)* int
        +Close(int)* int
        +Update(int, WELD_SETTING*)* int
    }

    class EthernetApp {
        -W5500* _W5500
        -Ethernet* _Socket[4]
        -QMap~int, ETHERNET_DEV~ m_mapEthernetDev
        +GetInstance()* EthernetApp
        +Init(void*) int
        +Open(int, void*) int
        +Close(int) int
        +Attach(int, int, void*) int
        +Detach(int) int
        +Update(int, WELD_SETTING*) int
    }

    class SerialApp {
        -QMap~int, SERIAL_DEV~ m_mapSerialDev
        -Serial* _Serial[2]
        +GetInstance()* SerialApp
        +Init(void*) int
        +Open(int, void*) int
        +Close(int) int
        +Attach(int, int, void*) int
        +Detach(int) int
        +Update(int, WELD_SETTING*) int
    }

    class GpioApp {
        -GPIO* _GPIO
        +GetInstance()* GpioApp
        +SetLEDs(void*) int
        +SetDevIOs(int, void*) int
        +GetResetButton() int
        +GetResetIO(int) int
    }

    class SystemClock {
        -RTC_DS3231* _rtc
        +GetInstance()* SystemClock
        +SetSystemClock(void*) int
        +SyncSystemClock() int
    }

    %% Hardware Layer
    class W5500 {
        -QMutex m_mutexWrite
        -QMutex m_mutexRead
        +GetInstance()* W5500
        +Write_Register(int, int, unsigned char*, int) int
        +Read_Register(int, int, unsigned char*, int) int
        +Reset() int
    }

    class Ethernet {
        -SOCKET_DEVICE m_SocketNum
        -int m_iDevNum
        +Open_TCP_Socket(unsigned char*, unsigned short) int
        +Close_TCP_Socket() int
        +SetDevNum(int) void
        +GetDevNum() int
        +GetStatus() unsigned char
    }

    class Serial {
        -int m_iDevNum
        -QString m_strDevName
        -int m_iBandrate
        +Open_Serial_Port() int
        +Close_Serial_Port() int
        +SetDevNum(int) void
        +GetDevNum() int
        +GetStatus() unsigned char
        +slotReadyToRead() void
        +slotErrorOccurred(error) void
    }

    class GPIO {
        -QMutex m_Mutex
        +GetInstance()* GPIO
        +Init() int
        +Write_Output(int, int) int
        +Read_Input(int) int
        +Set_Buzzer(int) int
    }

    class RTC_DS3231 {
        -QMutex m_Mutex
        -bool m_IsBoardAvaiable
        +GetInstance()* RTC_DS3231
        +SetTime(QDateTime) int
        +GetTime(QDateTime) int
    }

    %% Protocol Layer
    class Common {
        <<abstract>>
        #WELD_RESULT m_resultData
        #WELD_SETTING m_settingData
        +ParseWeldResult(QString)* int
        +GetWeldResult() WELD_RESULT
        +SetWeldSetting(WELD_SETTING*) int
        +GetWeldSetting() WELD_SETTING
    }

    class Versagraphic {
        -ParseResultString2Data(QString) void
        +ParseWeldResult(QString) int
    }

    class TouchScreen {
        -ParseResultString2Data(QString) void
        -Parse1stString2Data(QString) void
        -Parse2ndString2Data(QString) void
        +ParseWeldResult(QString) int
    }

    %% Modbus Layer
    class hbclient {
        -bool m_isConnected
        +Connect(int, QString) bool
    }

    class hbServer {
        -bool m_isConnected
        +Listen(int, QString) bool
        -slotStateChange(State) void
        -slotErrorChange(Error) void
    }

    %% Qt Base Classes
    class QObject {
        <<Qt>>
    }
    class QSerialPort {
        <<Qt>>
    }
    class QModbusTcpClient {
        <<Qt>>
    }
    class QModbusTcpServer {
        <<Qt>>
    }

    %% Inheritance Relationships
    QObject <|-- Proxy
    QObject <|-- Subject
    QObject <|-- InterfaceApp
    QObject <|-- GpioApp
    QObject <|-- SystemClock
    QObject <|-- W5500
    QObject <|-- Ethernet
    QObject <|-- GPIO
    QObject <|-- RTC_DS3231
    InterfaceApp <|-- EthernetApp
    InterfaceApp <|-- SerialApp
    QSerialPort <|-- Serial
    Common <|-- Versagraphic
    Common <|-- TouchScreen
    QModbusTcpClient <|-- hbclient
    QModbusTcpServer <|-- hbServer

    %% Composition and Aggregation Relationships
    Proxy o-- Subject : uses
    Proxy *-- EthernetApp : manages
    Proxy *-- SerialApp : manages
    Proxy *-- SystemClock : manages
    Subject o-- EthernetApp : uses
    Subject o-- SerialApp : uses
    EthernetApp *-- W5500 : contains
    EthernetApp *-- Ethernet : contains
    EthernetApp o-- Common : uses
    SerialApp *-- Serial : contains
    SerialApp o-- Common : uses
    GpioApp *-- GPIO : contains
    SystemClock *-- RTC_DS3231 : contains
    Ethernet o-- W5500 : uses

    %% Notes
    note for Proxy "Singleton pattern\nManages worker threads\nCoordinates app layer"
    note for InterfaceApp "Abstract interface for\ndevice communication"
    note for Common "Abstract protocol parser\nfor weld data"
```

## Architecture Layers

### 1. **Core Pattern Layer**
- **Proxy**: Singleton managing worker threads and coordinating between GUI and business logic
- **Subject**: Observer pattern implementation for thread-safe operations

### 2. **Application Layer**
- **InterfaceApp**: Abstract base class for device interfaces
- **EthernetApp**: Manages Ethernet-based device communication
- **SerialApp**: Manages serial port communication
- **GpioApp**: Handles GPIO operations (LEDs, buttons, I/O)
- **SystemClock**: Manages system time synchronization

### 3. **Hardware Layer**
- **W5500**: Ethernet controller driver
- **Ethernet**: TCP socket management
- **Serial**: Serial port wrapper
- **GPIO**: GPIO pin control
- **RTC_DS3231**: Real-time clock interface

### 4. **Protocol Layer**
- **Common**: Abstract base for protocol parsing
- **Versagraphic**: Versagraphic protocol implementation
- **TouchScreen**: Touch screen protocol implementation

### 5. **Modbus Layer**
- **hbclient**: Modbus TCP client
- **hbServer**: Modbus TCP server

## Design Patterns Used

1. **Singleton Pattern**: Proxy, EthernetApp, SerialApp, GpioApp, SystemClock, W5500, GPIO, RTC_DS3231
2. **Observer Pattern**: Subject/Proxy with signal-slot mechanism
3. **Strategy Pattern**: Protocol classes (Common, Versagraphic, TouchScreen)
4. **Abstract Factory**: InterfaceApp hierarchy

## Key Relationships

- Proxy acts as the central coordinator
- InterfaceApp provides a unified interface for different device types
- Hardware layer is abstracted from application logic
- Protocol parsing is delegated to specialized classes
- Qt's signal-slot mechanism for inter-object communication
```
