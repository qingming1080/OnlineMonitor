#include "localrecord.h"
#include <QDir>
#include <QFile>
#include <QCoreApplication>
#include <QApplication>
#include <QThread>
#include <QDebug>
#include "signalmanager.h"

LocalRecord* LocalRecord::s_pLocalRecord = nullptr;

LocalRecord::LocalRecord(QObject *parent) : QThread(parent)
{
    m_pMutex = new QMutex();

    initData();

    connect(SignalManager::getInstance(), &SignalManager::signalAddRecord, this, &LocalRecord::addRecord, Qt::DirectConnection);
}

void LocalRecord::initData()
{
    QThread* thread = new QThread();
    this->moveToThread(thread);
}

void LocalRecord::touchLogFile(QString fileName)
{
    QFile file(fileName);
    // 文件是否存在
    if(!file.exists()){
        qDebug() << "创建文件";
        touchRecordFile(fileName);
    }
}

LocalRecord *LocalRecord::getInstance()
{
    if(s_pLocalRecord == nullptr)
        s_pLocalRecord = new LocalRecord();

    return s_pLocalRecord;
}

//void LocalRecord::addRecord(const QVariant& data)
//{
//    Log_Data setting = data.value<Log_Data>();
//    m_cacheList.push_back(setting);
//}

void LocalRecord::addRecord(const QDateTime &time, const QString &text)
{
    m_pMutex->lock();

    Log_Data setting {time, text};
    m_cacheList.push_back(setting);

    m_pMutex->unlock();
}

void LocalRecord::run()
{
    while(1){
        m_pMutex->lock();

        if(!m_cacheList.isEmpty()){
            writeDataToLocalRecord(m_cacheList.at(0));
            m_cacheList.removeAt(0);
        }

        m_pMutex->unlock();
        msleep(5);
    }
}

void LocalRecord::writeDataToLocalRecord(Log_Data data)
{
    // 使用 year(),month()等函数，会造成一分时，字符串为1而不为01的问题
    QString year    = data.time.toString("yyyy");
    QString month   = data.time.toString("MM");
    QString day     = data.time.toString("dd");
    QString hour    = data.time.toString("hh");
    QString minute  = data.time.toString("mm");
    QString second  = data.time.toString("ss");
    QString msec    = data.time.toString("zzz");

    QString fileDir = QCoreApplication::applicationDirPath()+QString("/record/%1").arg(data.time.toString("yyyyMMdd"));
    QDir dir(fileDir);
    // 路径不存在,则创建路径
    if(!dir.exists()){
        // 注：makePath创建绝对路径，makeDir创建子路径，即makePath不需要管record文件夹是否存在
        dir.mkpath(fileDir);
    }
    QString fileName = QCoreApplication::applicationDirPath()+QString("/record/%1/%2.xml").arg(data.time.toString("yyyyMMdd")).arg(data.time.toString("yyyyMMdd_hh"));;
    touchLogFile(fileName);

    QFile file(fileName);
    file.open(QIODevice::ReadWrite);
    QDomDocument doc;
    doc.setContent(&file);
    QDomElement root = doc.documentElement();
    file.close();

    QDomElement newNode = doc.createElement("node");
    root.appendChild(newNode);

    // 收到时间
    QDomElement timeNode = doc.createElement("Time");
    newNode.appendChild(timeNode);
    QDomText timeText = doc.createTextNode(QString("%1/%2/%3 %4:%5:%6:%7").arg(year, month, day, hour, minute, second, msec));
    timeNode.appendChild(timeText);


    // 表格数据
    QDomElement dataNode = doc.createElement("Text");
    newNode.appendChild(dataNode);
    QDomText dataText = doc.createTextNode(data.text);
    dataNode.appendChild(dataText);

    file.open(QIODevice::WriteOnly);
    QTextStream  stream(&file);
    doc.save(stream, 4);
    file.close();
}

void LocalRecord::touchRecordFile(QString filePath)
{
    QFile file(filePath);
    file.open(QIODevice::WriteOnly);

    // 新建DOM树
    QDomDocument doc;
    // 添加说明信息
    QString insData = "version=\"1.0\" encoding=\"UTF-8\"";
    QDomProcessingInstruction  ins=doc.createProcessingInstruction("xml",insData); //将文档声明添加到DOM树
    doc.appendChild(ins);

    QDomElement rootNode = doc.createElement("Record");
    doc.appendChild(rootNode);

    QTextStream  stream(&file);
    doc.save(stream, 4);
    file.close();
}
