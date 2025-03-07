﻿#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include "qmlenum.h"
#include "define.h"

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


public:
    static DataBaseManager* getInstance();

    ~DataBaseManager();

    void openTransaction();

    void closeTransaction();

/////////////////////////configuration////////////////////////////////

    QList<int> getDeviceNums();

    ///
    /// \brief getConfigurationData : 获取Configuration表格数据
    /// \return : 数据
    ///
    _Configuration_Data getConfigurationData(int welderID);

    ///
    /// \brief setConfigurationData : 设置Configuration表格数据
    /// \param deviceID : 设备号
    /// \param column : 列号
    /// \param data : 新数据
    /// \return : 设置结果
    ///
    bool setConfigurationData(int deviceID, QmlEnum::CONFIGURATION_COLUMN column, QVariant data);

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
    bool insertConfigurationDevice(_Configuration_Data data);

    ///
    /// \brief insertConfigurationDevice : 插入Configuration表格一行数据
    /// \param data : 数据
    /// \return : 更新结果

    bool updateConfigurationDevice(_Configuration_Data data);


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
    QList<_Manual_Data> getManualData(int welderID);

    bool removeManualDevice(int deviceID);

    bool insertManualRow(_Manual_Data data);

/////////////////////////model////////////////////////////////
    ///
    /// \brief getModelData : 获取model表格数据
    /// \return : 数据
    ///
    QList<_Model_Data> getModelData();

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
    bool insertModelRow(_Model_Data data);

/////////////////////////production////////////////////////////////
    ///
    /// \brief getWeldTrendData : 获取历史记录，取最新五百个
    /// \param welderID : 焊机ID，为零则不区分焊机
    /// \param finalResult : 生产状态 0_全部 1_合格 2_次品 3_可疑
    /// \return
    ///
    QList<_Production_Data> getProductionData(int welderID = 0, int finalResult = 0);

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
    bool insertProductionRow(_Production_Data data);

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
    QString getConfiguration_ColumnName(QmlEnum::CONFIGURATION_COLUMN column);

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
    QString getProduction_ColumnName(QmlEnum::PRODUCTION_COLUMN column);

    ///
    /// \brief getSystem_ColumnName : 通过system_conf列号获取列名
    /// \param column : 列号
    /// \return : 列名
    ///
    QString getSystem_ColumnName(QmlEnum::SYSTEM_COLUMN column);

    QList<_Production_Data> getAllTrendData(int welderID, int interVal, QDateTime startTime, QDateTime endTime);

    QString getD2eviceInfo();

private:
    static DataBaseManager* s_pDataBaseManager;

    QSqlDatabase m_database;

    bool b_hasFeature{false};      // 支持读取表格行列数量全视觉之眼系统
};

#endif // DATABASEMANAGER_H
