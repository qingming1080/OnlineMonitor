#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include "define.h"

#define CONFIGURATION_TABLENAME     QString("configuration")
#define NETWORK_TABLENAME           QString("connection_network")
#define RS232_TABLENAME             QString("connection_rs232")

class DataBaseManager : public QObject
{
    Q_OBJECT
public:


public:
    static DataBaseManager* getInstance();

    ~DataBaseManager();

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
    /// \param data : 串口id
    /// \return : 插入结果
    ///
    bool insertRS232Row(_RS232_Data data);
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

private:
    static DataBaseManager* s_pDataBaseManager;

    QSqlDatabase m_database;

    bool b_hasFeature{false};      // 支持读取表格行列数量
};

#endif // DATABASEMANAGER_H
