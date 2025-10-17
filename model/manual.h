#ifndef MANUAL_H
#define MANUAL_H

#include <QAbstractListModel>
#include "define.h"
#include "modbus/hbmodbusclient.h"
///
/// \brief The Manual class : manual
/// 暴露添加一行接口，暴露数据库保存接口
class Manual : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int welderID READ welderID WRITE setWelderID NOTIFY welderIDChanged)
public:
    enum INPUT_REGISTERS
    {
        DEV_CYCLE_COUNT_H = 0,
        DEV_CYCLE_COUNT_L,
        DEV_ENERGY,
        DEV_AMPLITUDE,
        DEV_TP,
        DEV_WP,

        DEV_TIME,
        DEV_POWER,
        DEV_PRE_HEIGHT,
        DEV_POST_HEIGHT,

        DEV_WELD_ALARM,

        DEV_YY,
        DEV_YY_MM,
        DEV_DD,
        DEV_HH,
        DEV_MM,
        DEV_SS,

        END_OF_DEV_INPUT_REGISTERS = 120,
    };
public:

    explicit Manual(int welderID = 0, QObject *parent = nullptr);
    ~Manual();

    Q_INVOKABLE int welderID() const;
    Q_INVOKABLE void setWelderID(int id);

    Q_INVOKABLE int rowCount(const QModelIndex &parent) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const;
    Q_INVOKABLE virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    Q_INVOKABLE void save();
    Q_INVOKABLE void clearData();
    Q_INVOKABLE void loadData();

    Q_INVOKABLE void startReading();
    Q_INVOKABLE void stopReading();

private slots:
    void onNewManualData(int welderID, const QVector<quint16> &inputs, quint32 cycleCount, DateTimeData date);
    void flushPendingData();


signals:
    void welderIDChanged();

private:
    int m_welderID;

    QList<_Manual_Data> m_data;


    QList<_Manual_Data> m_pendingData;

    QTimer m_flushTimer;

    HBModbusClient *m_modbusClient = nullptr;

    int m_nextSerial = 1;
    QMap<int, int> m_rowSerialMap;

};

#endif // MANUAL_H
