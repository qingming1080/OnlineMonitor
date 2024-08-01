#ifndef DEFINE_H
#define DEFINE_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QDateTime>

#define CONFIGURATION_TABLENAME     QString("configuration")
#define NETWORK_TABLENAME           QString("connection_network")
#define RS232_TABLENAME             QString("connection_rs232")
#define IO_TABLENAME                QString("io_data")
#define MODEL_TABLENAME             QString("model")
#define PRODUCTION_TABLENAME        QString("production")
#define SYSTEM_TABLENAME            QString("system_conf")
#define USER_TABLENAME              QString("user")



struct _Configuration_Data
{
    int welder_id{0};           // 焊机ID
    QString welder_name{""};    // 焊机名称
    QString welder_type{""};    // 焊机型号
    int production_bacth{0};    // 最大生产批量
    int model_sample{0};        // 学习样本数
    int lower_limit{0};         // 良率下限
    int height_option{0};       // 高度模式
    int connect_type{0};        // 连接方式     0_RS232  1_Network
    int connect_id{0};          // 连接方式ID
    int mes_port{0};            // 远程端口
    QString mes_ip{""};         // 远程IP
    QString device_ip{""};      // 客户端IP
};
Q_DECLARE_METATYPE(_Configuration_Data)



struct _Network_Data
{
    int id;                    // 网口号
    int type;                  // 类型  0_Server  1_User
    int protocol;              // 协议  0_TCP/IP  1_OPCUA
    QString local_ip;          // 本地IP
    int local_port;            // 本地端口
    QString remote_ip;         // 远程IP
    int server_port;           // 服务器端口
    QString user;              // 用户
};



struct _RS232_Data
{
    int id;                 // 串口id
    QString port;           // 串口号
    int baud_rate;          // 波特率
    int data_bit;           // 数据位
    QString parity_bit;     // 奇偶校验位
    int stop_bit;           // 停止位
};


struct _IO_Data
{
    int id;         // io_id
    int welder_id;  // 焊接id
//    int type;       // 输入输出
    int pin;        // pin
    int available;  // 有效的  0:off  1:on
    int signal;     // 信号    0:alarm  1:reset 2:not_definite
};



struct _Manual_Data
{
    int id;                   // Manual_ ID
    int welder_id;            // 焊机ID
    QString create_time;      // 创建时间
    int serial_number;        // 序号
    int cycle_count;          // 循环总计
    int energy;               // 能量
    int amplitude;            // 振幅
    int pressure;             // 压力
    QString time;             // 焊接时间
    int power;                // 功率
    int pre_height;           // 焊前高度
    int post_height;          // 焊后高度
    int actual_force;         // 撕拉力
    int actual_degree;        // 残留度
};


struct _Model_Data
{
    int id;                            // 模型id
    int welder_id;                     // 焊机id
    QString create_time;               // 创建时间
    int energy;                        // 能量
    int amplitude;                     // 振幅
    int pressure;                      // 压力
    QString time_alpha;                // 焊机时间Alpha
    QString time_beta;                 // 焊机时间Beta
    int power_alpha;                   // 功率Alpha
    int power_beta;                    // 功率Beta
    int pre_height_alpha;              // 焊前高度Alpha
    int pre_height_beta;               // 焊前高度Beta
    int post_height_alpha;             // 焊后高度Alpha
    int post_height_beta;              // 焊后高度Beta
    int force_alpha;                   // 撕拉力Alpha
    int force_beta;                    // 撕拉力Beta
    int residual_alpha;                // 残留度Alpha
    int residual_beta;                 // 残留度Beta
    int current_sample_count;          // 当前样本数
};


struct _Production_Data
{
    int id;                                // 生产ID
    int welder_id;                         // 焊机ID
    int model_id;                          // 模型ID
    QString create_time;                   // 创建时间
    int serial_number;                     // 序号Barcode
    int cycle_count;                       // 循环值
    int batch_count;                       // 生产值
    int energy;                            // 能量
    int amplitude;                         // 振幅
    int pressure;                          // 压力
    QString time;                          // 焊接时间
    int power;                             // 功率
    double pre_height;                        // 焊前高度
    double post_height;                       // 焊后高度
    int force;                             // 撕拉力
    int residual;                          // 残留度
    int good_rate;                         // 良率
    int good_subtotal_cycles;              // 合格
    int suspect_subtotal_cycles;           // 次品
    int not_definite_cycles;               // 可疑
    int final_result;                      // 产品状态 0_合格 1_次品 2_可疑
};



struct _System_Data
{
    int id;                     // id
    int welder_id;              // 设备id
    int single_fact_setting;    // 单因素设置
    int general_fact_setting;   // 通用系数设置
    int other_fact_setting;     // 通用系数设置
    int auto_model_limit;       // 自动学习上限
};



// 焊接趋势数据结构
struct _Weld_TrendData
{
    // X轴
    int id_X_Max{0};
    int id_X_Min{0};
    // 焊前高度 Y轴
    int before_Y_Max{0};
    int before_Y_Min{0};
    // 焊后高度 Y轴
    int after_Y_Max{0};
    int after_Y_Min{0};
    // 时间 Y轴
    QString time_Y_Max;
    QString time_Y_Min;
    // 功率
    int power_Y_Max{0};
    int power_Y_Min{0};

    // 数据
    QList<_Production_Data> data;
};

// 良率趋势数据结构
struct _Yield_TrendData
{
    // 开始时间
    QString startTime;
    // 结束时间
    QString endTime;
    QList<QPair<int, QString>> points;
};


#endif // DEFINE_H
