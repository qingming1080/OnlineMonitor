#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include "qmlenum.h"
#include "define.h"
// #include "model/device.h"
// #include "model/manual.h"
// #include "model/production.h"

#define CONFIGURATION_TABLENAME     QString("configuration")
#define NETWORK_TABLENAME           QString("connection_network")
#define RS232_TABLENAME             QString("connection_rs232")
#define IO_TABLENAME                QString("io_data")
#define MANUAL_TABLENAME            QString("manual")
#define MODEL_TABLENAME             QString("model")
#define PRODUCTION_TABLENAME        QString("production")
#define SYSTEM_TABLENAME            QString("system_conf")
#define USER_TABLENAME              QString("user")

class MANUAL_COLUMN
{
public:
    enum COLUMN
    {
        ID                  = 0,    // Manual_ ID
        WELDER_ID           = 1,    // 焊机ID
        CREATE_TIME         = 2,    // 创建时间
        CYCLE_COUNT         = 3,    // 循环总计
        ENERGY              = 4,    // 能量
        AMPLITUDE           = 5,
        TRIGGER_PRESSURE    = 6,
        WELD_PRESSURE       = 7,    // 压力
        WELD_TIME           = 8,    // 焊接时间
        PEAK_POWER          = 9,    // 功率
        PRE_HEIGHT          = 10,   // 焊前高度
        POST_HEIGHT         = 11,   // 焊后高度
        ACTUAL_FORCE        = 12,   // 撕拉力
        ACTUAL_RESIDUAL     = 13,   // 残留度
        IS_SELECTED         = 14
    };
};


class DataBaseManager : public QObject
{
    Q_OBJECT
public:
    enum CONFIGURATION_COLUMN
    {
        WELDER_ID               = 0,    // 焊机ID
        WELDER_NAME             = 1,    // 焊机名称
        WELDER_TYPE             = 2,    // 焊机型号
        PRODUCTION_BATCH        = 3,    // 最大生产批量
        MAX_MODEL_SAMPLES       = 4,    // 学习样本数
        YIELD_RATE_LOWER_LIMIT  = 5,    // 良率下限
        HEIGHT_ENCODER_OPTION   = 6,    // 高度模式
        SUSPICIOUS_OPTION       = 7,
        CONNECT_TYPE            = 8,    // 连接方式
        CONNECT_TYPE_ID,                 // 连接方式ID
        SINGLE_FACT_SETTING,
        GENERAL_FACT_SETTING,
        OTHER_FACT_SETTING,
        AUTO_LEARN_COUNT,
        FORCE_THRESHOLD,
        RESIDUAL_THRESHOLD,

    };

    enum PRODUCTION_COLUMN
    {
        PRODUCTION_ID           = 0,    // 生产ID
        PRODUCTION_WELDER_ID    = 1,    // 焊机ID
        MODEL_ID                = 2,    // 模型ID
        PRODUCTION_CREATE_TIME  = 3,    // 创建时间
        SERIAL_NUMBER           = 4,    // 序号Barcode
        CYCLE_COUNT             = 5,    // 循环值
        BATCH_COUNT             = 6,    // 生产值
        ENERGY                  = 7,    // 能量
        AMPLITUDE               = 8,    // 振幅
        TRIGGER_PRESSURE        = 9,
        WELD_PRESSURE           = 10,    // 压力
        WELD_TIME               = 11,   // 焊接时间
        PEAK_POWER              = 12,   // 功率
        PRE_HEIGHT              = 13,   // 焊前高度
        POST_HEIGHT             = 14,   // 焊后高度
        FORCE                   = 15,   // 撕拉力
        RESIDUAL                = 16,   // 残留度
        FINAL_RESULT            = 17,   // 产品状态 0_合格 1_次品 2_可疑

    };

    struct DB_CONFIGURE
    {
        int                             WelderID;
        QString                         WelderName;             // 焊机名称
        int                             WelderType;             // 焊机型号
        int                             ProductionBatch;        // 最大生产批量
        int                             MaxModelSamples;        // 学习样本数
        int                             YieldRateLowerLimit;    // 良率下限
        bool                            HeightEncoderOption;    // 高度模式
        bool                            SuspiciousOption;       // 可疑
        int                             ConnectType;            // 连接方式     0_RS232  1_Network
        int                             ConnectTypeId;          // 连接方式ID
        int                             SingleFactSetting;
        int                             GeneralFactSetting;
        int                             OtherFactSetting;
        int                             AutoLearnCount;
        int                             ForceThreshold;
        int                             ResidualThreshold;
    };

    struct DB_SYSTEM
    {
        // int Id;                     // id
        int SingleFactorSetting;    // 单因素设置
        int GeneralFactorSetting;   // 通用系数设置
        int ForceThreshold;         // 撕拉力阈值设置
        int ResidualThreshold;      // 残留阈值设置
        int AutoLearningCount;      // 自动学习上限
    };

    struct DB_NETWORK
    {
        int Id;             // 网口号
        int Type;           // 类型  0_Server  1_Client
        int Protocol;       // 协议  0_TCP/IP  1_OPCUA
        QString LocalIP;    // 本地IP
        int LocalPort;      // 本地端口
        QString RemoteIP;   // 远程IP
        int ServerPort;     // 服务器端口
        QString User;       // 用户
    };

    struct DB_RS232
    {
        int Id;         // 串口id
        QString Port;   // 串口号
        int BaudRate;   // 波特率
        int DataBit;    // 数据位
        int ParityBit;  // 奇偶校验位
        int StopBit;    // 停止位
    };

    struct DB_MANUAL
    {
        int Id;             // ID
        int WelderId;       // 焊机ID
        QDateTime CreateTime;     // 创建时间
        int CycleCount;     // 循环总计
        int Energy;         // 能量
        int Amplitude;      // 振幅
        int TriggerPressure;//
        int WeldPressure;   // 压力
        int WeldTime;       // 焊接时间
        int PeakPower;      // 功率
        int Preheight;      // 焊前高度
        int PostHeight;     // 焊后高度
        int ActualForce;    // 撕拉力
        int ActualResidual; // 残留度
        bool IsSelected;
        bool IsNewComming;
        //preset
        // int EnergySetting;
        // int AmplitudeSetting;
        // int WPressureSetting;
        // int TPressureSetting;
    };

    struct ALPHA_BETA
    {
        double Alpha;
        double Beta;
    };

    struct POLYNOMIAL_COEFFICIENT
    {
        double P00;
        double P10;
        double P01;
        double P20;
        double P11;
        double P02;
    };

    struct CENTRALIZED_PROPERTY
    {
        double TimeMean;
        double TimeStd;
        double PowerMean;
        double PowrStd;
        double ForceMean;
        double ResidualMean;
    };

    struct DB_MODEL
    {
        int id;                             // 模型id
        int WelderId;                       // 焊机id
        QDateTime CreateTime;               // 创建时间
        int Energy;                         // 能量
        int Amplitude;                      // 振幅
        // int pressure;                    // 压力
        int TriggerPressure;                // 焊接压力
        int WeldPressure;                   // 触发压力
        ALPHA_BETA WeldTime;                // 焊机时间Alpha&Beta
        ALPHA_BETA PeakPower;               // 功率Alpha&Beta
        ALPHA_BETA Preheight;               // 焊前高度Alpha&Beta
        ALPHA_BETA PostHeight;              // 焊后高度Alpha&Beta
        POLYNOMIAL_COEFFICIENT PeelForce;   // 撕拉力
        POLYNOMIAL_COEFFICIENT Residual;    // 残留度
        CENTRALIZED_PROPERTY Centralized;
        int SampleCount;                    // 当前样本数
        bool isAvailable;                   // Need to consider if the current model is available or not.
    };

    struct DB_PRODUCTION
    {
        int ProductionID;
        int WelderID;                       //deviceID
        int ModelID;                        // 模型ID
        int CreateTime;                     // 创建时间
        int SerialNumber;                   // 序号Barcode
        int CycleCount;                     // 循环值
        int BatchCount;                     // 生产值
        int Energy;                         // 能量
        int Amplitude;                      // 振幅
        int WeldPressure;                   // 压力
        int TriggertPressure;
        int WeldTime;                       // 焊接时间
        int PeakPower;                      // 功率
        int Preheight;                      // 焊前高度
        int PostHeight;                     // 焊后高度
        int Force;                          // 撕拉力
        int Residual;                       // 残留度
        int FinalResult;                    // 产品状态 0_合格 1_次品 2_可疑
    };

public:
    static DataBaseManager* getInstance();

    ~DataBaseManager();

    void openTransaction();

    void closeTransaction();

/////////////////////////configuration////////////////////////////////
    bool getWelderID(QList<int> &IdList);
    bool getAllConfigureationDevice(QList<DataBaseManager::DB_CONFIGURE>& list);
    bool getConfigurationDevice(const int welderID, DB_CONFIGURE& configure);
    bool removeConfigurationDevice(const int welderID);
    bool insertConfigurationDevice(const DB_CONFIGURE configure);
    bool updateConfigurationDevice(const int welderID, const DB_CONFIGURE configure);

    bool getAllNetworkConfigure(QList<DataBaseManager::DB_NETWORK>& list);
    bool updateNetworkConfigure(const int id, const DB_NETWORK network);
    bool getNetworkConfigure(const int id, DB_NETWORK& network);

    bool getAllRS232Configure(QList<DataBaseManager::DB_RS232>& list);
    bool updateRS232Configure(const int id, const DB_RS232 rs232);
    bool getRS232Configure(const int id, DB_RS232& rs232);

    bool getManualRecords(const int welderID, QList<DB_MANUAL>& list);
    bool removeManualRecords(const int welderID);
    bool insertManualRecord(DB_MANUAL data);
    bool updateManualRecord(const int id, const DB_MANUAL data);

    QList<DB_MODEL> getModelData();
    bool insertModelRecord(DB_MODEL model);
    bool removeModelRow(int id);
    bool clearModel();

/////////////////////////io_data////////////////////////////////
/// 只处理待定
    ///
    /// \brief getIOData : 获取io_data表格数据
    /// \return : 数据
    ///
    QList<_IO_Data> getIOData(int welderID);

    _IO_Data getIOAvailabel(int welderID);

    ///
    /// \brief setIOData : 设置io_data表格数据
    /// \param id : io_id
    /// \param column : 列号
    /// \param data : 新数据
    /// \return : 设置结果
    ///
    bool setIOData(int id, QmlEnum::IO_COLUMN column, QVariant data);

    ///
    /// \brief removeIOData : 删除io_data表格一行数据
    /// \param id : io_id
    /// \return : 删除结果
    ///
    bool removeIOData(int id);

    ///
    /// \brief insertIORow : 插入io_data表格一行数据
    /// \param data : 数据
    /// \return : 插入结果
    ///
    bool insertIORow(_IO_Data data);

/////////////////////////production////////////////////////////////
    ///
    /// \brief getWeldTrendData : 获取历史记录，取最新五百个
    /// \param welderID : 焊机ID，为零则不区分焊机
    /// \param finalResult : 生产状态 0_全部 1_合格 2_次品 3_可疑
    /// \return
    ///
    QList<DB_PRODUCTION> getProductionData(int welderID = 0, int finalResult = 0, bool exportAll = false);

    ///
    /// \brief getWeldTrendData : 获取焊接趋势折线图，取最新五百个
    /// \param welderID : 焊机ID，为零则不区分焊机
    /// \return
    ///
//    _Weld_TrendData getWeldTrendData(int welderID = 0);

    ///
    /// \brief getYieldTrendData : 获取良率趋势折线图,取最新五百个
    /// \param interVal : 时间间隔 前推多少秒
    /// \param welderID : 焊机ID，为零则不区分焊机
    /// \return
    ///
    _Yield_TrendData getYieldTrendData(int interVal, int welderID = 0);

    ///
    /// \brief removeProductionRow : 删除production表格一行数据
    /// \param id : 生产id
    /// \return : 删除结果
    ///
    bool removeProductionRow(int id);

    bool clearProduction();

    ///
    /// \brief insertProductionRow : 插入production表格一行数据
    /// \param data : 数据
    /// \return : 插入结果
    ///
    bool insertProductionRow(DB_PRODUCTION data);

    // bool saveProductionDataofModbus(Device* device, const QVector<quint16>& inputs, quint32 cycleCount, DateTimeData date);

/////////////////////////system////////////////////////////////
/// root界面
    ///
    /// \brief getSystemData : 获取system_conf表格数据
    /// \return : 数据
    ///
    bool getSystemData(const int welderID, DataBaseManager::DB_SYSTEM& system);

    ///
    /// \brief setIOData : 设置system_conf表格数据
    /// \param id : id
    /// \param column : 列号
    /// \param data : 新数据
    /// \return : 设置结果
    ///
    bool setSystemData(int id, QmlEnum::SYSTEM_COLUMN column, QVariant data);

/////////////////////////user////////////////////////////////

    ///
    /// \brief getLevelByPassword : 通过密码获取用户等级
    /// \param password : 密码
    /// \return : 用户等级，1最大，0无效
    ///
    int getLevelByPassword(QString password);

    ///
    /// \brief setUserPassword : 设置user密码
    /// \param password : 新密码
    /// \return : 设置结果
    ///
    bool setUserPassword(QString password);

signals:

private:
    explicit DataBaseManager(QObject *parent = nullptr);

    void init();

    ///
    /// \brief getConfiguration_ColumnName : 通过Configuration列号获取列名
    /// \param column : 列号
    /// \return : 列名
    ///
    QString getConfiguration_ColumnName(CONFIGURATION_COLUMN column);

    ///
    /// \brief getNetwork_ColumnName : 通过connection_network列号获取列名
    /// \param column : 列号
    /// \return : 列名
    ///
    QString getNetwork_ColumnName(QmlEnum::NETWORK_COLUMN column);

    ///
    /// \brief getRS232_ColumnName : 通过connection_rs232列号获取列名
    /// \param column : 列号
    /// \return : 列名
    ///
    QString getRS232_ColumnName(QmlEnum::RS232_COLUMN column);

    ///
    /// \brief getIO_ColumnName : 通过io_data列号获取列名
    /// \param column : 列号
    /// \return : 列名
    ///
    QString getIO_ColumnName(QmlEnum::IO_COLUMN column);

    ///
    /// \brief getManuaal_ColumnName : 通过manual列号获取列名
    /// \param column : 列号
    /// \return : 列名
    ///
    QString getManual_ColumnName(MANUAL_COLUMN::COLUMN column);

    ///
    /// \brief getModel_ColumnName : 通过model列号获取列名
    /// \param column : 列号
    /// \return : 列名
    ///
    QString getModel_ColumnName(QmlEnum::MODEL_COLUMN column);

    ///
    /// \brief getProduction_ColumnName : 通过production列号获取列名
    /// \param column : 列号
    /// \return : 列名
    ///
    QString getProduction_ColumnName(PRODUCTION_COLUMN column);

    ///
    /// \brief getSystem_ColumnName : 通过system_conf列号获取列名
    /// \param column : 列号
    /// \return : 列名
    ///
    QString getSystem_ColumnName(QmlEnum::SYSTEM_COLUMN column);

    QList<DB_PRODUCTION> getAllTrendData(int welderID, int interVal, QDateTime startTime, QDateTime endTime);

    QString getD2eviceInfo();

private:
    static DataBaseManager* s_pDataBaseManager;

    QSqlDatabase m_database;

    bool b_hasFeature{false};      // 支持读取表格行列数量全视觉之眼系统
};

#endif // DATABASEMANAGER_H
