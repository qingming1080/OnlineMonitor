#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>

class System : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id           READ id             WRITE setId             NOTIFY idChanged)
    Q_PROPERTY(int singleFact   READ singleFact     WRITE setSingleFact     NOTIFY singleFactChanged)
    Q_PROPERTY(int generalFact  READ generalFact    WRITE setGeneralFact    NOTIFY generalFactChanged)
    Q_PROPERTY(int otherFace    READ otherFace      WRITE setOtherFace      NOTIFY otherFaceChanged)
    Q_PROPERTY(int autoModel    READ autoModel      WRITE setAutoModel      NOTIFY autoModelChanged)
public:
    explicit System(int welderID = 0, QObject *parent = nullptr);

    int id() const;
    void setId(int newId);

    int singleFact() const;
    void setSingleFact(int newSingleFact);

    int generalFact() const;
    void setGeneralFact(int newGeneralFact);

    int otherFace() const;
    void setOtherFace(int newOtherFace);

    int autoModel() const;
    void setAutoModel(int newAutoModel);

signals:

    void idChanged();

    void singleFactChanged();

    void generalFactChanged();

    void otherFaceChanged();

    void autoModelChanged();

private:
    const int m_welderID;

    int m_id;
    int m_singleFact;
    int m_generalFact;
    int m_otherFace;
    int m_autoModel;

};

#endif // SYSTEM_H
