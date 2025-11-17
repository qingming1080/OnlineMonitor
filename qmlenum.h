#ifndef QMLENUM_H
#define QMLENUM_H

#include <QObject>

class QmlEnum : public QObject
{
    Q_OBJECT
public:
    enum NETWORK_COLUMN
    {
        NETWORK_id          = 0,   // 网口号
        NETWORK_type        = 1,   // 类型
        NETWORK_protocol    = 2,   // 协议
        NETWORK_local_ip    = 3,   // 本地IP
        NETWORK_local_port  = 4,   // 本地端口
        NETWORK_remote_ip   = 5,   // 远程IP
        NETWORK_server_port = 6,   // 服务器端口
        NETWORK_user        = 7,   // 用户
    };
    Q_ENUM(NETWORK_COLUMN)



    enum SYSTEM_COLUMN
    {
        WELD_ID,
        SINGLE_FACTOR_SETTING,
        GENERAL_FACTOR_SETTING,
        FORCE_THRESHOLD,
        RESIDUAL_THRESHOLD,
        AUTO_LEARNING_COUNT,
    };
    Q_ENUM(SYSTEM_COLUMN)

    enum RS232_COLUMN
    {
        RS232_id           = 0,    // 串口id
        RS232_port         = 1,    // 串口号
        RS232_baud_rate    = 2,    // 波特率
        RS232_data_bit     = 3,    // 数据位
        RS232_parity_bit   = 4,    // 奇偶校验位
        RS232_stop_bit     = 5,    // 停止位
    };
    Q_ENUM(RS232_COLUMN)

    enum IO_COLUMN

    {
        IO_id          = 0,    // io_id
        IO_welder_id   = 1,    // 焊接id
        //    IO_type        = 2,    // 输入输出
        IO_pin         = 3,    // pin
        IO_available   = 4,    // 有效的
        IO_signal      = 5,    // 信号
    };
    Q_ENUM(IO_COLUMN)

    enum SIGNAL_IO
    {
        SIGNAL_alarm = 0,
        SIGNAL_reset = 1,
        SIGNAL_noDefinite = 2,
    };
    Q_ENUM(SIGNAL_IO)

    enum MESSAGE{
        MESSAGE_suspicious = 0,         // 出现可疑品
        MESSAGE_defective  = 1,         // 出现次品
        MESSAGE_noConnect  = 2,         // 未连接
        MESSAGE_lowerValue = 3,         // 良率下降至下限值
        MESSAGE_defectiveOften = 4,     // 频繁出现次品
        MESSAGE_suspiciousOften = 5,    // 频繁出现可疑品
        MESSAGE_upperValue = 6,         // 自动学习次数超过上限值
        MESSAGE_studyOver   = 7,        // 自动学习已完成
        MESSAGE_touchSuccess = 8,       // 创建模型已完成
        MESSAGE_setupComplete = 9,      //设备已连接
    };
    Q_ENUM(MESSAGE)

    enum SCREEN_INDEX
    {
        AUTO_LEARNING_SCREEEN = 0,
        SINGLE_PRODUCTION_SCREEN,
        MULTI_PRODUCTION_SCREEN
    };
    Q_ENUM(SCREEN_INDEX)

public:
    explicit QmlEnum(QObject *parent = nullptr){Q_UNUSED(parent)}

signals:

};

#endif // QMLENUM_H
