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

    Q_INVOKABLE int id() const;
    Q_INVOKABLE void setId(int newId);

    Q_INVOKABLE int singleFact() const;
    Q_INVOKABLE void setSingleFact(int newSingleFact);

    Q_INVOKABLE int generalFact() const;
    Q_INVOKABLE void setGeneralFact(int newGeneralFact);

    Q_INVOKABLE int otherFace() const;
    Q_INVOKABLE void setOtherFace(int newOtherFace);

    Q_INVOKABLE int autoModel() const;
    Q_INVOKABLE void setAutoModel(int newAutoModel);

signals:

    void idChanged();

    void singleFactChanged();

    void generalFactChanged();

    void otherFaceChanged();

    void autoModelChanged();

private:
    const int m_welderID;

    int m_id;
    int m_singleFact{0};
    int m_generalFact{0};
    int m_otherFace{0};
    int m_autoModel{0};

};

#endif // SYSTEM_H
