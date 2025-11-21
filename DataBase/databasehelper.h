#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <QMutex>
#include <QObject>
#include <QQueue>
#include <QThread>
#include <QTimer>

#include "DataBase/databasemanager.h"


/*!
 * \brief The DataBaseHelper class 数据库操作队列处理
 */
class DataBaseHelper : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseHelper(QObject *parent = nullptr);
    ~DataBaseHelper();

    // 添加数据库操作
    //  insertOperation 插入操作
    //  updateOperation 更新操作
    void appendOperation(const DataBaseManager::DB_PRODUCTION &insertOperation,
                         const DataBaseManager::DB_MODEL &updateOperation);
    // 处理数据库操作
    void processOperation();

private:
    // 初始化定时器
    void initQTimer();

private:
    QMutex m_mutex;
    QTimer *m_timer;
    QThread *m_thread;
    QQueue<DataBaseManager::DB_PRODUCTION> m_insertOperationQueue;
    DataBaseManager::DB_MODEL m_updateOperation;
};

#endif // DATABASEHELPER_H
