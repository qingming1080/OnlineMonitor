#include "manual.h"
#include "DataBase/databasemanager.h"
#include  "tools/utilityfunction.h"
#include "signalmanager.h"
#include <QDebug>
#include <QElapsedTimer>
#include "log/localrecord.h"



Manual::Manual(int welderID,QObject *parent)
    : QAbstractListModel{parent}, m_welderID(welderID)
{

    m_modbusClient = HBModbusClient::getInstance();

    m_data = DataBaseManager::getInstance()->getManualData(m_welderID);

    for(int i = 0; i < m_data.size(); ++i) {
        m_data[i].serial_number = m_nextSerial++;
    }

    connect(&m_flushTimer, &QTimer::timeout, this, &Manual::flushPendingData);
    m_flushTimer.start(1000);

}

Manual::~Manual()
{

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
        // return row + 1;
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
    case QmlEnum::MANUAL_COLUMN::MANUAL_selected:
        return data.selected;
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
    roles[QmlEnum::MANUAL_COLUMN::MANUAL_selected]         = "selected";

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
    // case QmlEnum::MANUAL_COLUMN::MANUAL_serial_number:
    // {
    //     // m_data[row].serial_number = value.toInt();
    //     m_rowSerialMap.value(index.row());
    //     return true;
    // }
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
    case QmlEnum::MANUAL_COLUMN::MANUAL_selected:
    {
        m_data[row].selected = value.toBool();
        emit dataChanged(index, index, {role});
        return true;
    }
    default:
        return false;
    }
}

void Manual::save()
{
    for(int i = 0; i < m_data.size(); ++i)
    {
        if (m_data[i].selected)
        DataBaseManager::getInstance()->insertManualRow(m_data.at(i));
        QModelIndex idx = index(i);
        emit dataChanged(idx, idx, {QmlEnum::MANUAL_COLUMN::MANUAL_selected});
    }
}


void Manual::clearData()
{
    beginResetModel();
    m_data.clear();
    DataBaseManager::getInstance()->removeManualDevice(m_welderID);
    endResetModel();
    m_nextSerial = 1;
}

void Manual::loadData()
{
    beginResetModel();  // 通知 QML 模型发生变化
    m_data = DataBaseManager::getInstance()->getManualData(m_welderID); // 重新加载数据
    m_nextSerial = 1;
    for(int i = 0; i < m_data.size(); ++i) {
        m_data[i].serial_number = m_nextSerial++;
    }

    endResetModel();
}


void Manual::startReading()
{
    connect(m_modbusClient, &HBModbusClient::newInputData, this, &Manual::onNewManualData);

    qDebug() << "Manual 开始接收 Modbus 数据";
}

void Manual::stopReading()
{
    disconnect(m_modbusClient, &HBModbusClient::newInputData, this, &Manual::onNewManualData);

    qDebug() << "Manual 停止接收 Modbus 数据";
}

void Manual::onNewManualData(int welderID, const QVector<quint16> &inputs, quint32 cycleCount, DateTimeData date)
{
    beginInsertRows(QModelIndex(), 0, 0);
    _Manual_Data data;
    data.welder_id     = welderID;
    data.cycle_count   = cycleCount;
    data.energy        = inputs[DEV_ENERGY];
    data.amplitude     = inputs[DEV_AMPLITUDE];
    data.pressure      = inputs[DEV_WP];
    data.time          = QString::number(inputs[DEV_TIME]);
    data.power         = inputs[DEV_POWER];
    data.pre_height    = inputs[DEV_PRE_HEIGHT];
    data.post_height   = inputs[DEV_POST_HEIGHT];
    data.actual_force  = 0;
    data.actual_degree = 0;
    data.create_time   = UtilityFunction::buildDateTimeString(date).left(10);;
    data.serial_number = m_nextSerial++;
    data.selected      = false;
    m_data.prepend(data);
    endInsertRows();
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

