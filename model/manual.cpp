#include "manual.h"
#include "DataBase/databasemanager.h"

#include "signalmanager.h"
#include <QDebug>
#include <QElapsedTimer>
#include "log/localrecord.h"
#include "modbus/hbmodbusclient.h"



Manual::Manual(int welderID,HBModbusClient* modbusClient, QObject *parent)
    : QAbstractListModel{parent}, m_welderID(welderID),m_modbusClient(modbusClient)
{
    // m_modbusClient = HBModbusClient::getInstance();

    // QElapsedTimer timer;
    // timer.start();

    m_data = DataBaseManager::getInstance()->getManualData(m_welderID);
    // QString text = QString("%1号设备_Manual_初始化耗时:%2ms").arg(welderID).arg(timer.elapsed());
    // emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), text);

    connect(&m_flushTimer, &QTimer::timeout, this, &Manual::flushPendingData);
    m_flushTimer.start(1000);

}

Manual::~Manual()
{
    if (m_modbusClient) {
        disconnect(m_modbusClient, &HBModbusClient::signalNewManualData,
                   this, &Manual::onNewManualData);
    }
    qDebug() << "Manual 析构，断开 Modbus 信号";

}

int Manual::welderID() const
{
 return m_welderID;
}

void Manual::setWelderID(int id) {
    if (m_welderID != id) {
        m_welderID = id;

         loadData();  // 重新加载数据
        emit welderIDChanged();

    }
}

int Manual::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

QVariant Manual::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    int row = index.row();
    _Manual_Data data = m_data.at(row);
    switch(role)
    {
    case QmlEnum::MANUAL_COLUMN::MANUAL_id:
        return data.id;
    case QmlEnum::MANUAL_COLUMN::MANUAL_welder_id:
        return data.welder_id;
    case QmlEnum::MANUAL_COLUMN::MANUAL_create_time:
        return data.create_time;
    case QmlEnum::MANUAL_COLUMN::MANUAL_serial_number:
        return data.serial_number;
    case QmlEnum::MANUAL_COLUMN::MANUAL_cycle_count:
        return data.cycle_count;
    case QmlEnum::MANUAL_COLUMN::MANUAL_energy:
        return data.energy;
    case QmlEnum::MANUAL_COLUMN::MANUAL_amplitude:
        return data.amplitude;
    case QmlEnum::MANUAL_COLUMN::MANUAL_pressure:
        return data.pressure;
    case QmlEnum::MANUAL_COLUMN::MANUAL_time:
        return data.time;
    case QmlEnum::MANUAL_COLUMN::MANUAL_power:
        return data.power;
    case QmlEnum::MANUAL_COLUMN::MANUAL_pre_height:
        return data.pre_height;
    case QmlEnum::MANUAL_COLUMN::MANUAL_post_height:
        return data.post_height;
    case QmlEnum::MANUAL_COLUMN::MANUAL_actual_force:
        return data.actual_force;
    case QmlEnum::MANUAL_COLUMN::MANUAL_actual_degree:
        return data.actual_degree;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> Manual::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[QmlEnum::MANUAL_COLUMN::MANUAL_id]               = "id";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_welder_id]        = "welder_id";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_create_time]      = "create_time";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_serial_number]    = "serial_number";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_cycle_count]      = "cycle_count";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_energy]           = "energy";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_amplitude]        = "amplitude";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_pressure]         = "pressure";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_time]             = "time";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_power]            = "power";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_pre_height]       = "pre_height";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_post_height]      = "post_height";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_actual_force]     = "actual_force";
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_actual_degree]    = "actual_degree";

    return roles;
}

bool Manual::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
        return false;

    int row = index.row();
    switch(role)
    {
    case QmlEnum::MANUAL_COLUMN::MANUAL_id:
    {
        m_data[row].id = value.toInt();
        return true;
    }
    case QmlEnum::MANUAL_COLUMN::MANUAL_welder_id:
    {
        m_data[row].welder_id = value.toInt();
        return true;
    }
    case QmlEnum::MANUAL_COLUMN::MANUAL_create_time:
    {
        m_data[row].create_time = value.toInt();
        return true;
    }
    case QmlEnum::MANUAL_COLUMN::MANUAL_serial_number:
    {
        m_data[row].serial_number = value.toInt();
        return true;
    }
    case QmlEnum::MANUAL_COLUMN::MANUAL_cycle_count:
    {
        m_data[row].cycle_count = value.toInt();
        return true;
    }
    case QmlEnum::MANUAL_COLUMN::MANUAL_energy:
    {
        m_data[row].energy = value.toInt();
        return true;
    }
    case QmlEnum::MANUAL_COLUMN::MANUAL_amplitude:
    {
        m_data[row].amplitude = value.toInt();
        return true;
    }
    case QmlEnum::MANUAL_COLUMN::MANUAL_pressure:
    {
        m_data[row].pressure = value.toInt();
        return true;
    }
    case QmlEnum::MANUAL_COLUMN::MANUAL_time:
    {
        m_data[row].time = value.toInt();
        return true;
    }
    case QmlEnum::MANUAL_COLUMN::MANUAL_power:
    {
        m_data[row].power = value.toInt();
        return true;
    }
    case QmlEnum::MANUAL_COLUMN::MANUAL_pre_height:
    {
        m_data[row].pre_height = value.toInt();
        return true;
    }
    case QmlEnum::MANUAL_COLUMN::MANUAL_post_height:
    {
        m_data[row].post_height = value.toInt();
        return true;
    }
    case QmlEnum::MANUAL_COLUMN::MANUAL_actual_force:
    {
        m_data[row].actual_force = value.toInt();
        return true;
    }
    case QmlEnum::MANUAL_COLUMN::MANUAL_actual_degree:
    {
        m_data[row].actual_degree = value.toInt();
        return true;
    }
    default:
        return false;
    }
}

void Manual::save()
{

    QSqlDatabase db = QSqlDatabase::database();
    db.transaction();  // 开启事务

    DataBaseManager::getInstance()->removeManualDevice(m_welderID);

    for(int i = 0; i < m_data.size(); ++i)
    {
        DataBaseManager::getInstance()->insertManualRow(m_data.at(i));
    }

     db.commit();  // 提交事务
}


void Manual::clearData()
{
    beginResetModel();
    m_data.clear();
    endResetModel();
}

void Manual::loadData()
{
    beginResetModel();  // 通知 QML 模型发生变化
    m_data = DataBaseManager::getInstance()->getManualData(m_welderID); // 重新加载数据

    endResetModel();
}


void Manual::startReading()
{
    connect(m_modbusClient, &HBModbusClient::signalNewManualData,
            this, &Manual::onNewManualData);
    qDebug() << "Manual 开始接收 Modbus 数据";
}

void Manual::stopReading()
{
    disconnect(m_modbusClient, &HBModbusClient::signalNewManualData,
               this, &Manual::onNewManualData);
    qDebug() << "Manual 停止接收 Modbus 数据";
}


void Manual::onNewManualData(const _Manual_Data& data)
{
    if (data.welder_id != m_welderID)
        return;

    auto it = std::find_if(m_data.begin(), m_data.end(), [&](const _Manual_Data& d) {
        return d.serial_number == data.serial_number;
    });

    if (it != m_data.end())
        return;

    m_pendingData.append(data);
}



void Manual::flushPendingData()
{
    if (m_pendingData.isEmpty())
        return;

    int newRows = m_pendingData.size();

    beginInsertRows(QModelIndex(), m_data.size(), m_data.size() + newRows - 1);
    m_data.append(m_pendingData);
    endInsertRows();

    m_pendingData.clear();

}

