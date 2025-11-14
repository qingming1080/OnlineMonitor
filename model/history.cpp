#include "history.h"
#include "DataBase/databasemanager.h"
#include <QtMath>
#include <QFile>
#include <QTextStream>
#include "signalmanager.h"
#include <QDebug>
#include <QElapsedTimer>
#include <QStorageInfo>
#include <QDebug>
#include <QStringList>
#include <qcoreapplication.h>
#include <QProcess>
#include <QThread>
#include <QObject>
#include "csvexportworker.h"
#include "tools/utilityfunction.h"

History* History::s_pHistory = nullptr;
QString  History::m_USBDirectory = "";
History *History::getInstance()
{
    if(s_pHistory == nullptr)
        s_pHistory = new History();

    return s_pHistory;
}

History::History(QObject *parent)
    : QAbstractListModel{parent}
{
    QElapsedTimer timer;
    timer.start();

    m_data = DataBaseManager::getInstance()->getProductionData();
   // std::reverse(m_data.begin(), m_data.end());


    QString text = QString("History_初始化共耗时:%1ms 加载%2条数据").arg(timer.elapsed()).arg(m_data.size());
    emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), text);

    QString ConvertCSVPath      = QCoreApplication::applicationDirPath() + "/ConvertCSV.py";

    if(!QFile::exists(ConvertCSVPath))
    {
        if(!QFile::copy(":/misc/ConvertCSV.py", ConvertCSVPath))
        {
            qWarning() << "Failed to copy ConvertCSV.py from resource to" << ConvertCSVPath;
        }
    }
}

int History::finalResult() const
{
    return m_finalResult;
}

void History::setFinalResult(int newFinalResult)
{
    QElapsedTimer timer;
    timer.start();

    if (m_finalResult == newFinalResult)
        return;

    m_finalResult = newFinalResult;
    emit beginResetModel();
    m_data = DataBaseManager::getInstance()->getProductionData(m_deviceID, m_finalResult);
    emit endResetModel();
    emit finalResultChanged();

    QString text = QString("History_修改筛选结果耗时:%1ms").arg(timer.elapsed());
    emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), text);
}

int History::deviceID() const
{
    return m_deviceID;
}

void History::setDeviceID(int newDeviceID)
{
    QElapsedTimer timer;
    timer.start();

    if (m_deviceID == newDeviceID)
        return;

    m_deviceID = newDeviceID;
    beginResetModel();

    // 根据新的设备ID加载数据
    if (newDeviceID == 0) {
        m_data = DataBaseManager::getInstance()->getProductionData();  // 获取所有设备的数据
    } else {
        m_data = DataBaseManager::getInstance()->getProductionData(newDeviceID);  // 获取特定设备的数据
    }

    // 按照记录时间排序，确保最新的记录排在前面
    std::sort(m_data.begin(), m_data.end(), [](const DataBaseManager::DB_PRODUCTION &a, const DataBaseManager::DB_PRODUCTION &b) {
        return a.CreateTime > b.CreateTime;  // 降序排序，最新记录在前
    });

    endResetModel();
    emit deviceIDChanged();

    QString text = QString("History_修改筛选设备耗时:%1ms").arg(timer.elapsed());
    emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), text);
}


int History::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.size();
}

QVariant History::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    int row = index.row();
    DataBaseManager::DB_PRODUCTION data = m_data.at(row);
    switch(role)
    {
    case DataBaseManager::PRODUCTION_ID:
        return data.ProductionID;
    case DataBaseManager::PRODUCTION_WELDER_ID:
        return data.WelderID;
    case DataBaseManager::MODEL_ID:
        return data.ModelID;
    case DataBaseManager::PRODUCTION_CREATE_TIME:
        return data.CreateTime;
    case DataBaseManager::SERIAL_NUMBER:
        return data.SerialNumber;
    case DataBaseManager::CYCLE_COUNT:
        return data.CycleCount;
    case DataBaseManager::BATCH_COUNT:
        return data.BatchCount;
    case DataBaseManager::ENERGY:
        return data.Energy;
    case DataBaseManager::AMPLITUDE:
        return data.Amplitude;
    case DataBaseManager::WELD_PRESSURE:
        return UtilityFunction::getInstance()->RawValueToString(data.WeldPressure, 10, 1);
    case DataBaseManager::WELD_TIME:
        return UtilityFunction::getInstance()->RawValueToString(data.WeldTime, 100, 2);
    case DataBaseManager::PEAK_POWER:
        return data.PeakPower;
    case DataBaseManager::PRE_HEIGHT:
        return UtilityFunction::getInstance()->RawValueToString(data.Preheight, 100, 2);
    case DataBaseManager::POST_HEIGHT:
        return UtilityFunction::getInstance()->RawValueToString(data.PostHeight, 100, 2);
    case DataBaseManager::FORCE:
        return data.Force;
    case DataBaseManager::RESIDUAL:
        return data.Residual;;
    case DataBaseManager::FINAL_RESULT:
        return data.FinalResult;
    // case DataBaseManager::PRODUCTION_row_number:
    //     return row + 1;
    default:
        return QVariant();
    }

}

QHash<int, QByteArray> History::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[DataBaseManager::PRODUCTION_ID]            = "id";
    roles[DataBaseManager::PRODUCTION_WELDER_ID]     = "welder_id";
    roles[DataBaseManager::MODEL_ID]                 = "model_id";
    roles[DataBaseManager::PRODUCTION_CREATE_TIME]   = "create_time";
    roles[DataBaseManager::SERIAL_NUMBER]            = "serial_number";
    roles[DataBaseManager::CYCLE_COUNT]              = "cycle_count";
    roles[DataBaseManager::BATCH_COUNT]              = "batch_count";
    roles[DataBaseManager::ENERGY]                   = "energy";
    roles[DataBaseManager::AMPLITUDE]                = "amplitude";
    roles[DataBaseManager::WELD_PRESSURE]            = "weld_pressure";
    roles[DataBaseManager::WELD_TIME]                = "time";
    roles[DataBaseManager::PEAK_POWER]               = "power";
    roles[DataBaseManager::PRE_HEIGHT]               = "pre_height";
    roles[DataBaseManager::POST_HEIGHT]              = "post_height";
    roles[DataBaseManager::FORCE]                    = "force";
    roles[DataBaseManager::RESIDUAL]                 = "residual";
    roles[DataBaseManager::TRIGGER_PRESSURE]         = "trigger_pressure";
    roles[DataBaseManager::FINAL_RESULT]             = "final_result";
    // roles[QmlEnum::PRODUCTION_COLUMN::PRODUCTION_row_number]               = "row_number";

    return roles;
}

void History::setWelderID(int welderID)
{
    emit beginResetModel();

    if(welderID == 0)
        m_data = DataBaseManager::getInstance()->getProductionData();
    else
        m_data = DataBaseManager::getInstance()->getProductionData(welderID);

    emit endResetModel();
}


bool History::isAvailaleDiskUSB()
{
    bool bResult = false;
    m_USBDirectory.clear();
#ifdef RASPBERRY
    foreach (const QStorageInfo &storage, QStorageInfo::mountedVolumes()) {
        // qDebug() << "path:" << storage.rootPath() << "ready:" << storage.isReady();
        if(!storage.isReady())
            continue;

        QString path = storage.rootPath();
        if(path.startsWith("/media/pi/") && !path.contains("mmcblk")) {
            m_USBDirectory = path;
            return true;
        }
    }
#endif
    return bResult;
}

bool History::exportData()
{
    if(m_USBDirectory.isEmpty() == true)
        return false;

    QList<DataBaseManager::DB_PRODUCTION> exportList = DataBaseManager::getInstance()->getProductionData(m_deviceID, m_finalResult, true);

    if (exportList.isEmpty()) {
        qWarning() << "没有符合条件的数据可导出";
        return false;
    }
    QList<QStringList> rows;
    QStringList headers =
    {
            "日期",
            "循环值",
            "能量",
            "振幅",
            "焊接压力",
            "触发压力"
            "焊接时间",
            "峰值功率",
            "焊前高度",
            "焊后高度",
            "撕拉力",
            "残留度",
            "检测结果"
    };

    for(int i=0; i< exportList.count(); i++)
    {
        QString timeStr = UtilityFunction::getInstance()->timestampToString(exportList[i].CreateTime);
        QStringList value;
        value << timeStr
              << QString::number(exportList[i].CycleCount)
              << QString::number(exportList[i].Energy)
              << QString::number(exportList[i].Amplitude)
              << QString::number(exportList[i].WeldPressure)
              << QString::number(exportList[i].TriggertPressure)
              << QString::number(exportList[i].WeldTime)
              << QString::number(exportList[i].PeakPower)
              << QString::number(exportList[i].Preheight)
              << QString::number(exportList[i].PostHeight)
              << QString::number(exportList[i].Force)
              << QString::number(exportList[i].Residual)
              << QString::number(exportList[i].FinalResult);
        rows.append(value);
    }

    if(rows.empty())
        return false;

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDateTime = currentDateTime.toString("yyyyMMddHHmmss");
    QString localAppDirectory = QCoreApplication::applicationDirPath() + "/" + formattedDateTime + "-历史数据记录";
    QStringList localFiles;
    int filesCount = rows.count() / MAX_RECORDS_IN_ONE_FILE;
    int restRecords = rows.count() % MAX_RECORDS_IN_ONE_FILE;

    if(restRecords > 0) filesCount += 1;
    for(int i = 0; i < filesCount; i++)
    {
        localFiles.append(localAppDirectory + QString::number(i+1) + ".csv");
    }

    QList<QStringList> oneFileRecords;
    for(int i = 0; i < filesCount; i++)
    {
        oneFileRecords.clear();
        for(int j = 0; j < MAX_RECORDS_IN_ONE_FILE; j++)
        {
            if((j + i * MAX_RECORDS_IN_ONE_FILE) < rows.count())
                oneFileRecords.append(rows.at(j + i * MAX_RECORDS_IN_ONE_FILE));
            else
                break;
        }
        ExportToCSV(localFiles.at(i), headers, oneFileRecords);
    }

    ExportToCSVAsync(localFiles);
    return true;
}

bool History::ExportToCSV(const QString& filePath, const QStringList& headers, const QList<QStringList>& data)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件：" << filePath;
        return false;
    }

    QTextStream out(&file);
    out.setCodec("UTF-8");
    file.write("\xEF\xBB\xBF");

    // 写入表头
    out << headers.join(",") << "\n";

    // 写入数据
    for (const auto& row : data) {
        out << row.join(",") << "\n";
    }

    file.close();
    qDebug() << "数据已成功导出到：" << filePath;
    return true;
}

void History::ExportToCSVAsync(QStringList &localfiles)
{
    if(!m_exportThread)
    {
        m_exportThread = new QThread(this);
        m_exportWorker = new CSVExportWorker(localfiles, m_USBDirectory);
        m_exportWorker->moveToThread(m_exportThread);
        connect(m_exportThread, &QThread::started, static_cast<CSVExportWorker*>(m_exportWorker), &CSVExportWorker::exportToFile);
        connect(m_exportWorker, &CSVExportWorker::exportPrograss, this, &History::signalExportPrograss);
        connect(m_exportWorker, &CSVExportWorker::exportFinished, this, &History::onExportFinished);
        connect(m_exportThread, &QThread::finished, m_exportWorker, &QObject::deleteLater);
    }
    if(!m_exportThread->isRunning())
    {
        m_exportThread->start();
    }
}

void History::onExportFinished(bool success, const QString &message)
{
    m_exportThread->quit();
    m_exportThread->wait();
    m_exportThread->deleteLater();
    m_exportThread = nullptr;
    emit signalExportCompleted(success, message);
}
