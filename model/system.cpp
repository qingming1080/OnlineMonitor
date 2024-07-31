#include "system.h"
#include "DataBase/databasemanager.h"

#include "signalmanager.h"
#include <QDebug>
#include <QElapsedTimer>
#include "log/localrecord.h"

System::System(int welderID, QObject *parent)
    : QObject{parent}, m_welderID(welderID)
{
    QElapsedTimer timer;
    timer.start();

    QList<_System_Data> result = DataBaseManager::getInstance()->getSystemData(m_welderID);
    if(result.size() != 0)
    {
        _System_Data data = result.at(0);
        m_id = data.id;
        m_singleFact = data.single_fact_setting;
        m_generalFact = data.general_fact_setting;
        m_otherFace = data.other_fact_setting;
        m_autoModel = data.auto_model_limit;
    }

    QString text = QString("%1号设备_System_初始化耗时:%2ms").arg(welderID).arg(timer.elapsed());
    emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), text);
}

int System::id() const
{
    return m_id;
}

void System::setId(int newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

int System::singleFact() const
{
    return m_singleFact;
}

void System::setSingleFact(int newSingleFact)
{
    if (m_singleFact == newSingleFact)
        return;
    m_singleFact = newSingleFact;
    emit singleFactChanged();
}

int System::generalFact() const
{
    return m_generalFact;
}

void System::setGeneralFact(int newGeneralFact)
{
    if (m_generalFact == newGeneralFact)
        return;
    m_generalFact = newGeneralFact;
    emit generalFactChanged();
}

int System::otherFace() const
{
    return m_otherFace;
}

void System::setOtherFace(int newOtherFace)
{
    if (m_otherFace == newOtherFace)
        return;
    m_otherFace = newOtherFace;
    emit otherFaceChanged();
}

int System::autoModel() const
{
    return m_autoModel;
}

void System::setAutoModel(int newAutoModel)
{
    if (m_autoModel == newAutoModel)
        return;
    m_autoModel = newAutoModel;
    emit autoModelChanged();
}
