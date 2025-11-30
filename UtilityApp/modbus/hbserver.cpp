#include "hbserver.h"
#include <QDebug>
hbServer::hbServer(QObject *parent)
{
    Q_UNUSED(parent);
    m_isConnected = false;
}

hbServer::~hbServer()
{

}

bool hbServer::Listen(const int& iPort, const QString& strAddress)
{
    connect(this, &QModbusTcpServer::stateChanged, this, &hbServer::slotStateChange);
    connect(this, &QModbusTcpServer::errorOccurred, this, &hbServer::slotErrorChange);
    //    connect(this, &QModbusTcpServer::modbusClientDisconnected, this, )

    this->setValue(QModbusServer::ListenOnlyMode,   false);
    this->setValue(QModbusServer::DeviceBusy,       false);

    this->setConnectionParameter(QModbusDevice::NetworkPortParameter, iPort);
    this->setConnectionParameter(QModbusDevice::NetworkAddressParameter, strAddress);
    m_isConnected = this->connectDevice();
    if(m_isConnected == false)
        qDebug() << this->errorString();
    return m_isConnected;
}

// QModbusResponse hbServer::processRequest(const QModbusPdu &request)
// {
//     // Get function code
//     const auto functionCode = request.functionCode();

//     // process function code
//     switch (functionCode) {
//     case QModbusPdu::ReadCoils:
//         // 处理读取线圈的请求
//         qDebug() << "Read Coils request";
//         // 假设我们总是返回一个成功的响应，这里可以根据实际情况返回数据
//         return QModbusResponse(QModbusPdu::ReadCoils, QByteArray::fromHex("0101"));

//     case QModbusPdu::WriteSingleCoil:
//         // 处理写单个线圈的请求
//         qDebug() << "Write Single Coil request";
//         // 返回响应，通常是回显请求数据
//         return QModbusResponse(request);

//     default:
//         // 返回一个异常响应，表示不支持的功能码
//         return QModbusExceptionResponse(functionCode, QModbusExceptionResponse::IllegalFunction);
//     }
// }

void hbServer::slotStateChange(State state)
{
    switch(state)
    {
    case UnconnectedState:
        qDebug() << "State: Unconnected";
        break;
    case ConnectingState:
        qDebug() << "State: Connecting";
        break;
    case ConnectedState:
        // this->setData(QModbusDataUnit::Coils, quint16(0), 1);
        // this->setData(QModbusDataUnit::Coils, quint16(1), 1);
        // this->setData(QModbusDataUnit::Coils, quint16(2), 1);
        // this->setData(QModbusDataUnit::Coils, quint16(3), 1);
        // this->setData(QModbusDataUnit::Coils, quint16(4), 1);
        // this->setData(QModbusDataUnit::Coils, quint16(5), 1);
        qDebug() << "State: Connected";
        break;
    case ClosingState:
        m_isConnected = false;
        qDebug() << "State: Closing";
        break;
    default:
        qDebug() << "State: Unknown";
        break;
    }
}

void hbServer::slotErrorChange(Error error)
{
    switch(error)
    {
    case NoError:
        qDebug() << "Error: NoError";
        break;
    case ReadError:
        qDebug() << "Error: ReadError";
        break;
    case WriteError:
        qDebug() << "Error: WriteError";
        break;
    case ConnectionError:
        qDebug() << "Error: ConnectionError";
        break;
    case ConfigurationError:
        qDebug() << "Error: ConfigureationError";
        break;
    case TimeoutError:
        qDebug() << "Error: TimeoutError";
        break;
    case ProtocolError:
        qDebug() << "Error: ProtocolError";
        break;
    case ReplyAbortedError:
        qDebug() << "Error: ReplyAbortedError";
        break;
    default:
        break;
    }
}
