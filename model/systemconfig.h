#ifndef SYSTEMCONFIG_H
#define SYSTEMCONFIG_H

#include <QObject>
#include <QSerialPort>

///
/// \brief The SystemConfig class : 系统配置
///
class SystemConfig : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int maxBatch READ maxBatch WRITE setMaxBatch NOTIFY maxBatchChanged)
    Q_PROPERTY(int sampleNum READ sampleNum WRITE setSampleNum NOTIFY sampleNumChanged)
    Q_PROPERTY(int minYield READ minYield WRITE setMinYield NOTIFY minYieldChanged)
    Q_PROPERTY(bool heightMode READ heightMode WRITE setHeightMode NOTIFY heightModeChanged)
    Q_PROPERTY(bool undetermined READ undetermined WRITE setUndetermined NOTIFY undeterminedChanged)
    Q_PROPERTY(QString port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(QSerialPort::BaudRate baudRate READ baudRate WRITE setBaudRate NOTIFY baudRateChanged)
    Q_PROPERTY(QSerialPort::DataBits dataBits READ dataBits WRITE setDataBits NOTIFY dataBitsChanged)
    Q_PROPERTY(QSerialPort::Parity parity READ parity WRITE setParity NOTIFY parityChanged)
    Q_PROPERTY(QSerialPort::StopBits stopBits READ stopBits WRITE setStopBits NOTIFY stopBitsChanged)
public:
    explicit SystemConfig(QObject *parent = nullptr);

    Q_INVOKABLE int maxBatch() const;
    Q_INVOKABLE void setMaxBatch(int newMaxBatch);
    Q_INVOKABLE int sampleNum() const;
    Q_INVOKABLE void setSampleNum(int newSampleNum);
    Q_INVOKABLE int minYield() const;
    Q_INVOKABLE void setMinYield(int newMinYield);
    Q_INVOKABLE bool heightMode() const;
    Q_INVOKABLE void setHeightMode(bool newHeightMode);
    Q_INVOKABLE bool undetermined() const;
    Q_INVOKABLE void setUndetermined(bool newUndetermined);
    Q_INVOKABLE QString port() const;
    Q_INVOKABLE void setPort(const QString &newPort);
    Q_INVOKABLE QSerialPort::BaudRate baudRate() const;
    Q_INVOKABLE void setBaudRate(const QSerialPort::BaudRate &newBaudRate);
    Q_INVOKABLE QSerialPort::DataBits dataBits() const;
    Q_INVOKABLE void setDataBits(const QSerialPort::DataBits &newDataBits);
    Q_INVOKABLE QSerialPort::Parity parity() const;
    Q_INVOKABLE void setParity(const QSerialPort::Parity &newParity);
    Q_INVOKABLE QSerialPort::StopBits stopBits() const;
    Q_INVOKABLE void setStopBits(const QSerialPort::StopBits &newStopBits);

signals:

    void maxBatchChanged();

    void sampleNumChanged();

    void minYieldChanged();

    void heightModeChanged();

    void undeterminedChanged();

    void portChanged();

    void baudRateChanged();

    void dataBitsChanged();

    void parityChanged();

    void stopBitsChanged();

private:
    int m_maxBatch{0};  // 最大生产批量
    int m_sampleNum{0}; // 学习样本数
    int m_minYield{0};  // 良率下限
    bool m_heightMode{false};   // 高度模式启动
    bool m_undetermined{false}; // 待定
    QString m_port;             // 端口
    QSerialPort::BaudRate m_baudRate;   // 波特率
    QSerialPort::DataBits m_dataBits;   // 数据位
    QSerialPort::Parity   m_parity;     // 奇偶校验位
    QSerialPort::StopBits m_stopBits;   // 停止位

};

#endif // SYSTEMCONFIG_H
