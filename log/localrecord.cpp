#include "localrecord.h"
#include <QDir>
#include <QFile>
#include <QCoreApplication>
#include <QApplication>
#include <QThread>
#include <QDebug>

LocalRecord* LocalRecord::s_pLocalRecord = nullptr;
QString log_file_path = "";

LocalRecord::LocalRecord(QObject *parent) : QThread(parent)
{
    initData();
}

void LocalRecord::initData()
{
    QDateTime time = QDateTime::currentDateTime();
    // 使用 year(),month()等函数，会造成一分时，字符串为1而不为01的问题
    QString year    = time.toString("yyyy");
    QString month   = time.toString("MM");
    QString day     = time.toString("dd");
    QString hour    = time.toString("hh");
    QString minute  = time.toString("mm");
    QString second  = time.toString("ss");
    QString msec    = time.toString("zzz");
    QString dirPath = QCoreApplication::applicationDirPath()+QString("/record/%1_%2").arg(year).arg(month);;
    QDir dir(dirPath);
    // 路径不存在,则创建路径
    if(!dir.exists()){
        // 注：makePath创建绝对路径，makeDir创建子路径，即makePath不需要管record文件夹是否存在
        dir.mkpath(dirPath);
    }
    log_file_path = dirPath+ "/" +QString("%1_%2_%3_%4_%5_%6.xml").arg(year, month, day, hour, minute, second);
    QFile file(log_file_path);
    // 文件是否存在
    if(!file.exists()){
        qDebug() << "创建文件";
        touchRecordFile(log_file_path);
    }

    QThread* thread = new QThread();
    this->moveToThread(thread);
}

LocalRecord *LocalRecord::getInstance()
{
    if(s_pLocalRecord == nullptr)
        s_pLocalRecord = new LocalRecord();

    return s_pLocalRecord;
}

void LocalRecord::addRecord(const QVariant& data)
{
    Log_Data setting = data.value<Log_Data>();
    m_cacheList.push_back(setting);
}

void LocalRecord::addRecord(const QDateTime &time, const QString &text)
{
    Log_Data setting {time, text};
    m_cacheList.push_back(setting);
}

void LocalRecord::run()
{
    while(1){
        if(!m_cacheList.isEmpty()){
            writeDataToLocalRecord(m_cacheList.at(0));
            m_cacheList.removeAt(0);
        }
        QApplication::processEvents();
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

    QFile file(log_file_path);
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
