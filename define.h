#ifndef DEFINE_H
#define DEFINE_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QDateTime>
#include <QPointF>
// #include <Database/databasemanager.h>

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
    // QList<DB_PRODUCTION> data;
};

// 良率趋势数据结构
struct _Yield_TrendData
{
    // 开始时间
    QString startTime;
    // 结束时间
    QString endTime;
    QList<QPointF> points;
    _Yield_TrendData& operator=(const _Yield_TrendData& other){
        this->points.clear();
        this->startTime = other.startTime;
        this->endTime   = other.endTime;
//        this->points    = other.points;
        for(int i = 0; i < other.points.count(); ++i)
            this->points.push_back(other.points.at(i));

        return *this;
    }
};


struct DateTimeData
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

struct WELD_PRESET
{
    int     Energy;
    int     Amplitude;
    int     TriggerPressure;
    int     WeldingPressure;
};

struct IO_STATUS
{
    bool IOResetStatus;
};

struct DEVICE_STATUS
{
    bool    IsDeviceStatus;
    bool    IsDeviceDataStatus;
};



#endif // DEFINE_H
