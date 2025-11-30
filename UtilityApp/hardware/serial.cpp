#include "serial.h"
#include "definition.h"
#include <QDebug>
// #include <QSerialPort>
Serial::Serial(QSerialPort *parent)
    : QSerialPort{parent}
{
    //Register QSerialPort::SerialPortError type
    qRegisterMetaType<QSerialPort::SerialPortError>("QSerialPort::SerialPortError");
    m_iDevNum = -1;
#ifdef RASPBERRY
    m_strDevName = "/dev/ttyS0";
#else
    m_strDevName = "/dev/ttyUSB0";
#endif
    m_iBandrate = 9600;
    m_DataBits = QSerialPort::Data8;
    m_Parity = QSerialPort::NoParity;
    m_StopBits = QSerialPort::OneStop;
    if(this->isOpen() == true)
        this->close();

}

Serial::~Serial()
{
    if(this->isOpen() == true)
        this->close();
}

int Serial::Open_Serial_Port()
{
    int iResult = ERROR;
    if(this->isOpen() == true)
        return iResult;
    this->setPortName(m_strDevName);
    qDebug() << "name: " << this->portName();
    this->setBaudRate(m_iBandrate);
    qDebug() << "Baudrate: " << this->baudRate();
    this->setDataBits(m_DataBits);
    qDebug() << "Databits: " << this->dataBits();
    this->setParity(m_Parity);
    qDebug() << "Parity: " << this->parity();
    this->setStopBits(m_StopBits);
    qDebug() << "Stop: " << this->stopBits();
    this->setFlowControl(QSerialPort::NoFlowControl);
    connect(this, SIGNAL(readyRead()),      this, SLOT(slotReadyToRead()), Qt::QueuedConnection);
    connect(this, &QSerialPort::errorOccurred,  this, &Serial::slotErrorOccurred, Qt::QueuedConnection);
    if(this->open(QIODevice::ReadWrite) == false)
    {
        this->close();
    }
    else
    {
        this->clearError();
        this->clear();
        iResult = OK;
        qDebug() << this->portName() << " is Open!!!";
    }
    return iResult;
}

int Serial::SetDevName(const QString name)
{
    m_strDevName = name;
    return OK;
}

int Serial::SetBandrate(const int bandrate)
{
    m_iBandrate = bandrate;
    return OK;
}

int Serial::SetDataBits(const QSerialPort::DataBits dataBits)
{
    m_DataBits = dataBits;
    return OK;
}

int Serial::SetParity(const QSerialPort::Parity parity)
{
    m_Parity = parity;
    return OK;
}

int Serial::SetStopBits(const QSerialPort::StopBits stopBits)
{
    m_StopBits = stopBits;
    return OK;
}

int Serial::Close_Serial_Port()
{
    if(this->isOpen() == true)
    {
        this->close();
        disconnect(this, &QSerialPort::readyRead,       this, &Serial::slotReadyToRead);
        disconnect(this, &QSerialPort::errorOccurred,   this, &Serial::slotErrorOccurred);
    }
    return OK;
}

int Serial::Write_Serial_Port()
{
    char data[10] = {0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55};
    if(this->isOpen() == true)
    {
        this->write(data, 10);
    }
    return OK;
}

void Serial::SetDevNum(const int devNum)
{
    m_iDevNum = devNum;
}

int Serial::GetDevNum() const
{
    return m_iDevNum;
}

unsigned char Serial::GetStatus() const
{
    if(this->isOpen() == true)
        return OK;
    else
        return ERROR;
}

void Serial::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    Write_Serial_Port();
}

void Serial::slotReadyToRead()
{
    while(this->waitForReadyRead(1000) == true);
    QByteArray DataBuffer;
    QString strBuffer;
    DataBuffer.clear();
    DataBuffer = this->readAll();
    strBuffer = DataBuffer.data();
    if(strBuffer.size() == 0)
        return;
    try
    {
        qDebug() << "Receive: " << strBuffer;
        emit signalResultReady(m_iDevNum, strBuffer); //Send the signal to Serial APP
        strBuffer.clear();
    }
    catch(...)
    {
        qDebug() << this->portName() << ":" << this->errorString();
    }
}

void Serial::slotErrorOccurred(QSerialPort::SerialPortError error)
{
    switch(error)
    {
    case QSerialPort::WriteError:
        qDebug()<< QString("An I/O error occurred while writing the data to port 1%, error: %2")
                    .arg(this->portName()).arg(this->errorString());
        break;
    case QSerialPort::ReadError:
        qDebug()<< QString("An I/O error occurred while reading the data to port 1%, error: %2")
                    .arg(this->portName()).arg(this->errorString());
        break;
    default:
        break;
    }
}
