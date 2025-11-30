#ifndef SERIAL_H
#define SERIAL_H
#include <QtSerialPort/QSerialPort>
#include <QObject>
class Serial : public QSerialPort
{
    Q_OBJECT
private:
    int m_iDevNum;
    QString                 m_strDevName;
    int                     m_iBandrate;
    QSerialPort::DataBits   m_DataBits;
    QSerialPort::Parity     m_Parity;
    QSerialPort::StopBits   m_StopBits;
public:
    explicit Serial(QSerialPort *parent = nullptr);
    ~Serial();
    int Open_Serial_Port();
    int SetDevName(const QString name);
    int SetBandrate(const int bandrate);
    int SetDataBits(const QSerialPort::DataBits dataBits);
    int SetParity(const QSerialPort::Parity parity);
    int SetStopBits(const QSerialPort::StopBits stopBits);
    int Close_Serial_Port();
    int Write_Serial_Port();
    void SetDevNum(const int devNum);
    int GetDevNum() const;
    unsigned char GetStatus() const;
protected:
    void timerEvent(QTimerEvent *event) override;
public slots:
    void slotReadyToRead();
    void slotErrorOccurred(QSerialPort::SerialPortError error);
signals:
    void signalResultReady(int iDev, QString strResult); //Send the signal to Serial APP
};

#endif // SERIAL_H
