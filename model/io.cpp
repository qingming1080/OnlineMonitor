#include "io.h"
#include "DataBase/databasemanager.h"
#include <QVariant>

#include <QDebug>
#include <QElapsedTimer>
#include "log/localrecord.h"

IO::IO(int welderID, QObject *parent)
    : QObject{parent}, m_welderID(welderID)
{
    QElapsedTimer timer;
    timer.start();

    _IO_Data data = DataBaseManager::getInstance()->getIOAvailabel(m_welderID);
    m_availabel = data.available==1?true:false;
    m_ioID = data.id;

    QString text = QString("%1号设备_IO_初始化耗时:%2ms").arg(welderID).arg(timer.elapsed());
    LocalRecord::getInstance()->addRecord(QDateTime::currentDateTime(), text);
}

bool IO::availabel() const
{
    return m_availabel;
}

void IO::setAvailabel(bool newAvailabel)
{
    if (m_availabel == newAvailabel)
        return;
    m_availabel = newAvailabel;
    emit availabelChanged();

    DataBaseManager::getInstance()->setIOData(m_ioID, QmlEnum::IO_available, newAvailabel?1:0);
}
