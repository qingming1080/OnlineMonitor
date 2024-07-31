#ifndef LOCALRECORD_H
#define LOCALRECORD_H

#include <QObject>
#include <QThread>
#include <QDomDocument>
#include <QDateTime>
#include <QMutex>

struct Log_Data{
    QDateTime time;
    QString text;
};
Q_DECLARE_METATYPE(Log_Data);

class LocalRecord : public QThread
{
    Q_OBJECT
public:
    static LocalRecord* getInstance();

    void run() override;

signals:


public slots:
    /// 添加数据记录
//    void addRecord(const QVariant& data);
    void addRecord(const QDateTime& time, const QString& text);

private:
    explicit LocalRecord(QObject *parent = nullptr);

    void initData();

    void writeDataToLocalRecord(Log_Data data);

    void touchRecordFile(QString filePath);


private:
    static LocalRecord* s_pLocalRecord;

    QMutex* m_pMutex;

    // 缓存还没写入本地记录的数据
    QList<Log_Data> m_cacheList;
};

#endif // LOCALRECORD_H
