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
    struct MANUAL_DATA
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
        int PreEnergy;
        int PreAmplitude;
        int PreWP;
        int PreTP;
    };

    enum PRESET
    {
        PREENERGY,
        PREAMPLITUDE,
        PRETP,
        PREWP,
    };

public:

    explicit Manual(int welderID = 0, QObject *parent = nullptr);
    ~Manual();

    Q_INVOKABLE int welderID() const;
    Q_INVOKABLE void setWelderID(int id);

    Q_INVOKABLE virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const;
    Q_INVOKABLE virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    Q_INVOKABLE void save();
    Q_INVOKABLE void clearData();
    Q_INVOKABLE void loadData();

    Q_INVOKABLE void startReading();
    Q_INVOKABLE void stopReading();

private slots:
    void onNewManualData(int welderId, const QVector<quint16> &inputs, quint32 cycleCount, DateTimeData date, QVector<quint16> holdings);

signals:
    void welderIDChanged();

private:
    int m_welderID;

    QList<MANUAL_DATA> m_listRawData;
    QList<MANUAL_DATA> m_listManualData;
    HBModbusClient *m_modbusClient = nullptr;

    //TODO need to be removed
    int m_nextSerial = 1;

    bool CalibrateModel();

};

#endif // MANUAL_H
