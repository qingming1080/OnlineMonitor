#include "system.h"

System::System(int welderID, QObject *parent)
    : QObject{parent}, m_welderID(welderID)
{

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
