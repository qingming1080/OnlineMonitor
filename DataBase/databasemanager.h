#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
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

/////////////////////////configuration////////////////////////////////
    ///
    /// \brief getConfigurationData : 获取Configuration表格数据
    /// \return : 数据
    ///
    QList<_Configuration_Data> getConfigurationData();

    ///
    /// \brief setConfigurationData : 设置Configuration表格数据
    /// \param deviceID : 设备号
    /// \param column : 列号
    /// \param data : 新数据
    /// \return : 设置结果
    ///
    bool setConfigurationData(int deviceID, _CONFIGURATION_COLUMN column, QVariant data);

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
    bool setNetworkData(int networkID, _NETWORK_COLUMN column, QVariant data);

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
    bool setRS232Data(int id, _RS232_COLUMN column, QVariant data);

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

/////////////////////////io_data////////////////////////////////
    ///
    /// \brief getIOData : 获取io_data表格数据
    /// \return : 数据
    ///
    QList<_IO_Data> getIOData();

    ///
    /// \brief setIOData : 设置io_data表格数据
    /// \param id : io_id
    /// \param column : 列号
    /// \param data : 新数据
    /// \return : 设置结果
    ///
    bool setIOData(int id, _IO_COLUMN column, QVariant data);

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
    ///
    /// \brief getManualData : 获取manual表格数据
    /// \return : 数据
    ///
    QList<_Manual_Data> getManualData();

    bool setManualData(int id, _MANUAL_COLUMN column, QVariant data);

    bool removeManualRow(int id);

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

    ///
    /// \brief insertModelRow : 插入model表格一行数据
    /// \param data : 数据
    /// \return : 插入结果
    ///
    bool insertModelRow(_Model_Data data);

/////////////////////////production////////////////////////////////
    ///
    /// \brief getProductionData : 获取production表格数据
    /// \return : 数据
    ///
    QList<_Production_Data> getProductionData();

    ///
    /// \brief removeProductionRow : 删除production表格一行数据
    /// \param id : 生产id
    /// \return : 删除结果
    ///
    bool removeProductionRow(int id);

    ///
    /// \brief insertProductionRow : 插入production表格一行数据
    /// \param data : 数据
    /// \return : 插入结果
    ///
    bool insertProductionRow(_Production_Data data);

/////////////////////////production////////////////////////////////
    ///
    /// \brief getSystemData : 获取system_conf表格数据
    /// \return : 数据
    ///
    QList<_System_Data> getSystemData();

    ///
    /// \brief setIOData : 设置system_conf表格数据
    /// \param id : id
    /// \param column : 列号
    /// \param data : 新数据
    /// \return : 设置结果
    ///
    bool setSystemData(int id, _SYSTEM_COLUMN column, QVariant data);

/////////////////////////user////////////////////////////////

    ///
    /// \brief getLevelByPassword : 通过密码获取用户等级
    /// \param password : 密码
    /// \return : 用户等级，1最大，0无效
    ///
    int getLevelByPassword(QString password);
signals:

private:
    explicit DataBaseManager(QObject *parent = nullptr);

    void init();

    ///
    /// \brief getConfiguration_ColumnName : 通过Configuration列号获取列名
    /// \param column : 列号
    /// \return : 列名
    ///
    QString getConfiguration_ColumnName(_CONFIGURATION_COLUMN column);

    ///
    /// \brief getNetwork_ColumnName : 通过connection_network列号获取列名
    /// \param column : 列号
    /// \return : 列名
    ///
    QString getNetwork_ColumnName(_NETWORK_COLUMN column);

    ///
    /// \brief getRS232_ColumnName : 通过connection_rs232列号获取列名
    /// \param column : 列号
    /// \return : 列名
    ///
    QString getRS232_ColumnName(_RS232_COLUMN column);

    ///
    /// \brief getIO_ColumnName : 通过io_data列号获取列名
    /// \param column : 列号
    /// \return : 列名
    ///
    QString getIO_ColumnName(_IO_COLUMN column);

    ///
    /// \brief getManuaal_ColumnName : 通过manual列号获取列名
    /// \param column : 列号
    /// \return : 列名
    ///
    QString getManual_ColumnName(_MANUAL_COLUMN column);

    ///
    /// \brief getModel_ColumnName : 通过model列号获取列名
    /// \param column : 列号
    /// \return : 列名
    ///
    QString getModel_ColumnName(_MODEL_COLUMN column);

    ///
    /// \brief getProduction_ColumnName : 通过production列号获取列名
    /// \param column : 列号
    /// \return : 列名
    ///
    QString getProduction_ColumnName(_PRODUCTION_COLUMN column);

    ///
    /// \brief getSystem_ColumnName : 通过system_conf列号获取列名
    /// \param column : 列号
    /// \return : 列名
    ///
    QString getSystem_ColumnName(_SYSTEM_COLUMN column);

private:
    static DataBaseManager* s_pDataBaseManager;

    QSqlDatabase m_database;

    bool b_hasFeature{false};      // 支持读取表格行列数量
};

#endif // DATABASEMANAGER_H
