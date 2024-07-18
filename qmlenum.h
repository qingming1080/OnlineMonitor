#ifndef QMLENUM_H
#define QMLENUM_H

#include <QObject>

class QmlEnum : public QObject
{
    Q_OBJECT
public:
    enum CONFIGURATION_COLUMN
    {
        CONFIGURATION_welder_id        = 0,    // 焊机ID
        CONFIGURATION_welder_name      = 1,    // 焊机名称
        CONFIGURATION_welder_type      = 2,    // 焊机型号
        CONFIGURATION_production_bacth = 3,    // 最大生产批量
        CONFIGURATION_model_sample     = 4,    // 学习样本数
        CONFIGURATION_lower_limit      = 5,    // 良率下限
        CONFIGURATION_height_option    = 6,    // 高度模式
        CONFIGURATION_connect_type     = 7,    // 连接方式
        CONFIGURATION_connect_id       = 8,    // 连接方式ID
    };
    Q_ENUM(CONFIGURATION_COLUMN)

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

    enum MANUAL_COLUMN
    {
        MANUAL_id              = 0,    // Manual_ ID
        MANUAL_welder_id       = 1,    // 焊机ID
        MANUAL_create_time     = 2,    // 创建时间
        MANUAL_serial_number   = 3,    // 序号
        MANUAL_cycle_count     = 4,    // 循环总计
        MANUAL_energy          = 5,    // 能量
        MANUAL_amplitude       = 6,    // 振幅
        MANUAL_pressure        = 7,    // 压力
        MANUAL_time            = 8,    // 焊接时间
        MANUAL_power           = 9,    // 功率
        MANUAL_pre_height      = 10,   // 焊前高度
        MANUAL_post_height     = 11,   // 焊后高度
        MANUAL_actual_force    = 12,   // 撕拉力
        MANUAL_actual_degree   = 13,   // 残留度
    };
    Q_ENUM(MANUAL_COLUMN)

    enum PRODUCTION_COLUMN
    {
        PRODUCTION_id                      = 0,    // 生产ID
        PRODUCTION_welder_id               = 1,    // 焊机ID
        PRODUCTION_model_id                = 2,    // 模型ID
        PRODUCTION_create_time             = 3,    // 创建时间
        PRODUCTION_serial_number           = 4,    // 序号Barcode
        PRODUCTION_cycle_count             = 5,    // 循环值
        PRODUCTION_batch_count             = 6,    // 生产值
        PRODUCTION_energy                  = 7,    // 能量
        PRODUCTION_amplitude               = 8,    // 振幅
        PRODUCTION_pressure                = 9,    // 压力
        PRODUCTION_time                    = 10,   // 焊接时间
        PRODUCTION_power                   = 11,   // 功率
        PRODUCTION_pre_height              = 12,   // 焊前高度
        PRODUCTION_post_height             = 13,   // 焊后高度
        PRODUCTION_force                   = 14,   // 撕拉力
        PRODUCTION_residual                = 15,   // 残留度
        PRODUCTION_good_rate               = 16,   // 良率
        PRODUCTION_good_subtotal_cycles    = 17,   // 合格
        PRODUCTION_suspect_subtotal_cycles = 18,   // 次品
        PRODUCTION_not_definite_cycles     = 19,   // 可疑
        PRODUCTION_final_result            = 20,   // 产品状态 0_合格 1_次品 2_可疑
    };
    Q_ENUM(PRODUCTION_COLUMN)

    enum SYSTEM_COLUMN
    {
        SYSTEM_id                   = 0,   // id
        SYSTEM_welder_id            = 1,   // 设备id
        SYSTEM_single_fact_setting  = 2,   // 单因素设置
        SYSTEM_general_fact_setting = 3,   // 通用系数设置
        SYSTEM_other_fact_setting   = 4,   // 通用系数设置
        SYSTEM_auto_model_limit     = 5,   // 自动学习上限
    };
    Q_ENUM(SYSTEM_COLUMN)

    enum MODEL_COLUMN
    {
        MODEL_id                   = 0,       // 模型id
        MODEL_welder_id            = 1,       // 焊机id
        MODEL_create_time          = 2,       // 创建时间
        MODEL_energy               = 3,       // 能量
        MODEL_amplitude            = 4,       // 振幅
        MODEL_pressure             = 5,       // 压力
        MODEL_time_alpha           = 6,       // 焊机时间Alpha
        MODEL_time_beta            = 7,       // 焊机时间Beta
        MODEL_power_alpha          = 8,       // 功率Alpha
        MODEL_power_beta           = 9,       // 功率Beta
        MODEL_pre_height_alpha     = 10,      // 焊前高度Alpha
        MODEL_pre_height_beta      = 11,      // 焊前高度Beta
        MODEL_post_height_alpha    = 12,      // 焊后高度Alpha
        MODEL_post_height_beta     = 13,      // 焊后高度Beta
        MODEL_force_alpha          = 14,      // 撕拉力Alpha
        MODEL_force_beta           = 15,      // 撕拉力Beta
        MODEL_residual_alpha       = 16,      // 残留度Alpha
        MODEL_residual_beta        = 17,      // 残留度Beta
        MODEL_current_sample_count = 18,      // 当前样本数
    };
    Q_ENUM(MODEL_COLUMN)

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

    // 产品优良状态
    enum PRODUCTSTATE
    {
        PRODUCTSTATE_Excelleng = 0,    // 良品
        PRODUCTSTATE_Difference,       // 次品
        PRODUCTSTATE_Suspicious,       // 未知
    };
    Q_ENUM(PRODUCTSTATE)

    // 设备连接方式
    enum CONNECTTYPE
    {
        CONNECTTYPE_Network    = 0,    // 网络连接
        CONNECTTYPE_RS232      = 1,    // RS232
    };
    Q_ENUM(CONNECTTYPE)

    enum SIGNAL
    {
        SIGNAL_alarm = 0,
        SIGNAL_reset = 1,
        SIGNAL_noDefinite = 2,
    };
    Q_ENUM(SIGNAL)

public:
    explicit QmlEnum(QObject *parent = nullptr){}

signals:

};

#endif // QMLENUM_H
