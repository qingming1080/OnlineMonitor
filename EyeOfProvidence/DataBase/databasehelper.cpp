#include "databasehelper.h"
#include <QMutexLocker>
#include "databasehelper.h"

/*!
 * \brief 构造函数
 * \param parent 父对象
 */
DataBaseHelper::DataBaseHelper(QObject *parent)
    : QObject{parent}
    , m_timer(nullptr)
    , m_thread(nullptr)
{
    m_thread = new QThread(this);
    this->moveToThread(m_thread);

    connect(m_thread, &QThread::started, this, &DataBaseHelper::initQTimer);
    connect(m_thread, &QThread::finished, this, &QObject::deleteLater);

    m_thread->start();
}

/*!
 * \brief 析构函数
 */
DataBaseHelper::~DataBaseHelper()
{
    m_thread->quit();
    m_thread->wait();
}

/*!
 * \brief 添加数据库操作
 * \param insertOperation 插入操作
 * \param updateOperation 更新操作
 */
void DataBaseHelper::appendOperation(const DataBaseManager::DB_PRODUCTION &insertOperation,
                                     const DataBaseManager::DB_MODEL &updateOperation)
{
    QMutexLocker locker(&m_mutex);
    m_insertOperationList.append(insertOperation);
    if(m_updateOperationMap.contains(updateOperation.id) == true)
        m_updateOperationMap[updateOperation.id] = updateOperation;
    else
        m_updateOperationMap.insert(updateOperation.id, updateOperation);

    if (!m_timer->isActive())
        m_timer->start(5000);
}

/*!
 * \brief 处理数据库操作
 */
void DataBaseHelper::processOperation()
{
    QMutexLocker locker(&m_mutex);
    // 插入操作 - 使用批量插入提高性能
    if (!m_insertOperationList.isEmpty())
    {
        DataBaseManager::getInstance()->insertProductionRowBatch(m_insertOperationList);
        m_insertOperationList.clear();
    }
    if(!m_updateOperationMap.isEmpty())
    {
        DataBaseManager::getInstance()->updateModelRecordBatch(m_updateOperationMap);
        m_updateOperationMap.clear();
    }
    m_timer->stop();
}

/*!
 * \brief 初始化定时器
 */
void DataBaseHelper::initQTimer()
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &DataBaseHelper::processOperation);
}

