#include "databasehelper.h"
#include <QMutexLocker>
#include "databasehelper.h"
#include "signalmanager.h"

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
    m_insertOperationQueue.append(insertOperation);
    m_updateOperationQueue.append(updateOperation);

    if (!m_timer->isActive())
        m_timer->start(5000);
}

/*!
 * \brief 处理数据库操作
 */
void DataBaseHelper::processOperation()
{
    // 插入操作
    if (!m_insertOperationQueue.isEmpty())
    {
        DataBaseManager::DB_PRODUCTION production;
        {
            QMutexLocker locker(&m_mutex);
            production = m_insertOperationQueue.dequeue();
        }

        emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), QString("id: %1").arg(production.CycleCount));
        DataBaseManager::getInstance()->insertProductionRow(production);
    }

    // 更新操作
    if (!m_updateOperationQueue.isEmpty())
    {
        DataBaseManager::DB_MODEL production;
        {
            QMutexLocker locker(&m_mutex);
            production = m_updateOperationQueue.dequeue();
        }
        DataBaseManager::getInstance()->updateModelRecord(production.id, production);
    }

    if (m_insertOperationQueue.isEmpty() || m_updateOperationQueue.isEmpty())
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

