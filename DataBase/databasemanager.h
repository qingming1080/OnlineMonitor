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
        CONNECT_TYPE            = 7,    // 连接方式
        CONNECT_TYPE_ID         = 8,    // 连接方式ID
        DELECT_TYPE             = 9,    // 是否删除(已无用)
        MES_PORT                = 10,   // 远程端口
        MES_IP                  = 11,   // 远程IP
        DEVICE_IP               = 12,   // 客户端IP
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
        WELD_PRESSURE           = 9,    // 压力
        WELD_TIME               = 10,   // 焊接时间
        PEAK_POWER              = 11,   // 功率
        PRE_HEIGHT              = 12,   // 焊前高度
        POST_HEIGHT             = 13,   // 焊后高度
        FORCE                   = 14,   // 撕拉力
        RESIDUAL                = 15,   // 残留度
        GOOD_RATE               = 16,   // 良率
        GOOD_CYCLE_COUNT        = 17,   // 合格
        SUSPECT_CYCLE_COUNT     = 18,   // 次品
        DEFECTIVE_CYCLE_COUNT   = 19,   // 可疑
        FINAL_RESULT            = 20,   // 产品状态 0_合格 1_次品 2_可疑
    };

    struct DB_CONFIGURE
    {
        QString                         WelderName;             // 焊机名称
        int                             WelderType;             // 焊机型号
        int                             ProductionBatch;        // 最大生产批量
        int                             MaxModelSamples;        // 学习样本数
        int                             YieldRateLowerLimit;    // 良率下限
        bool                            HeightEncoderOption;    // 高度模式
        bool                            SuspiciousOption;       // 可疑
        int                             ConnectType;            // 连接方式     0_RS232  1_Network
        int                             ConnectTypeId;          // 连接方式ID
        int                             MES_Port;               // 远程端口
        QString                         MES_IP;                 // 远程IP
        QString                         Device_IP;              // 客户端IP
    };

    struct DB_MANUAL
    {
        int WelderId;       // 焊机ID
        QString CreateTime; // 创建时间
        int serial_number;  // 序号
        int CycleCount;     // 循环总计
        int Energy;         // 能量
        int Amplitude;      // 振幅
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
        int EnergySetting;
        int AmplitudeSetting;
        int WPressureSetting;
        int TPressureSetting;
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
        QDateTime CreateTime;                 // 创建时间
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
    };

    struct DB_PRODUCTION
    {
        int ProductionID;
        int WelderID;                       //deviceID
        int ModelID;                        // 模型ID
        QDateTime CreateTime;               // 创建时间
        int SerialNumber;                   // 序号Barcode
        int CycleCount;                     // 循环值
        int BatchCount;                     // 生产值
        int Energy;                         // 能量
        int Amplitude;                      // 振幅
        int WeldPressure;                   // 压力
        int WeldTime;                       // 焊接时间
        int PeakPower;                      // 功率
        int Preheight;                      // 焊前高度
        int PostHeight;                     // 焊后高度
        int Force;                          // 撕拉力
        int Residual;                       // 残留度
        int GoodRate;                       // 良率
        int GoodCycleCount;                 // 合格
        int DefectiveCycleCount;            // 次品
        int SuspectCycleCount;              // 可疑
        int FinalResult;                    // 产品状态 0_合格 1_次品 2_可疑
    };

public:
    static DataBaseManager* getInstance();

    ~DataBaseManager();

    void openTransaction();

    void closeTransaction();

/////////////////////////configuration////////////////////////////////

    QList<int> getDeviceCount();

    ///
    /// \brief getConfigurationData : 获取Configuration表格数据
    /// \return : 数据
    ///
    bool getConfigurationData(int welderID, DataBaseManager::DB_CONFIGURE& configure);

    ///
    /// \brief setConfigurationData : 设置Configuration表格数据
    /// \param deviceID : 设备号
    /// \param column : 列号
    /// \param data : 新数据
    /// \return : 设置结果
    ///
    bool setConfigurationData(int deviceID, CONFIGURATION_COLUMN column, QVariant data);

    ///
    /// \brief removeConfigurationDevice : 删除Configuration表格一行数据
    /// \param deviceID : 设备号
    /// \return : 删除结果
    ///
    bool removeConfigurationDevice(int deviceID);

    ///
    /// \brief insertConfigurationDevice : 插入Configuration表格一行数据
    /// \param data : 数据
    /// \return : 插入结果
    ///
    bool insertConfigurationDevice(DB_CONFIGURE data);

    ///
    /// \brief insertConfigurationDevice : 插入Configuration表格一行数据
    /// \param data : 数据
    /// \return : 更新结果

    bool updateConfigurationDevice(const int WelderID, DB_CONFIGURE &data);


/////////////////////////connection_network////////////////////////////////
    ///
    /// \brief getNetworkData : 获取connection_network表格数据
    /// \return : 数据
    ///
    QList<_Network_Data> getNetworkData();

    ///
    /// \brief setNetworkData : 设置connection_network表格数据(注:1网口不允许界面配置!!!)
    /// \param networkID: 网口号
    /// \param column : 列号
    /// \param data : 新数据
    /// \return : 设置结果
    ///
    bool setNetworkData(int networkID, QmlEnum::NETWORK_COLUMN column, QVariant data);

    ///
    /// \brief removeNetworkRow : 删除connection_network表格一行数据(注:1网口不允许界面配置!!!)
    /// \param networkID : 网口号
    /// \return : 删除结果
    ///
    bool removeNetworkRow(int networkID);

    ///
    /// \brief insertNetworkRow : 插入connection_network表格一行数据(注:1网口不允许界面配置!!!)
    /// \param data : 数据
    /// \return : 插入结果
    ///
    bool insertNetworkRow(_Network_Data data);

    QStringList getNetworkInfoById(int id);

/////////////////////////connection_rs232////////////////////////////////
    ///
    /// \brief getRS232Data : 获取connection_rs232表格数据
    /// \return : 数据
    ///
    QList<_RS232_Data> getRS232Data();

    ///
    /// \brief setRS232Data : 设置RS232表格数据
    /// \param id : 串口id
    /// \param column : 列号
    /// \param data : 新数据
    /// \return : 设置结果
    ///
    bool setRS232Data(int id, QmlEnum::RS232_COLUMN column, QVariant data);

    ///
    /// \brief removeRS232Row : 删除RS232表格一行数据
    /// \param id : 串口id
    /// \return : 删除结果
    ///
    bool removeRS232Row(int id);

    ///
    /// \brief insertRS232Row : 插入RS232表格一行数据
    /// \param data : 数据
    /// \return : 插入结果
    ///
    bool insertRS232Row(_RS232_Data data);

    _RS232_Data getRS232DataById(int id);

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

/////////////////////////manual////////////////////////////////
/// 模型_只写 不清楚其他设备的模型
    ///
    /// \brief getManualData : 获取manual表格数据
    /// \return : 数据
    ///
    QList<DB_MANUAL> getManualData(int welderID);

    bool removeManualDevice(int deviceID);

    bool insertManualRow(DB_MANUAL data);

/////////////////////////model////////////////////////////////
    ///
    /// \brief getModelData : 获取model表格数据
    /// \return : 数据
    ///
    QList<DB_MODEL> getModelData();

    ///
    /// \brief removeModelRow : 删除model表格一行数据
    /// \param id : model_id
    /// \return : 删除结果
    ///
    bool removeModelRow(int id);

    bool clearModel();

    ///
    /// \brief insertModelRow : 插入model表格一行数据
    /// \param data : 数据
    /// \return : 插入结果
    ///
    bool insertModelRow(DB_MODEL model);

    bool existsManualRowByCycle(int cycleCount);

/////////////////////////production////////////////////////////////
    ///
    /// \brief getWeldTrendData : 获取历史记录，取最新五百个
    /// \param welderID : 焊机ID，为零则不区分焊机
    /// \param finalResult : 生产状态 0_全部 1_合格 2_次品 3_可疑
    /// \return
    ///
    QList<DB_PRODUCTION> getProductionData(int welderID = 0, int finalResult = 0);

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
    QList<_System_Data> getSystemData(int welderID);

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
    QString getManual_ColumnName(QmlEnum::MANUAL_COLUMN column);

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
