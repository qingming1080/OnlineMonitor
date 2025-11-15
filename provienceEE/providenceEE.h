#ifndef PROVIDENCEEE_H
#define PROVIDENCEEE_H

#include <QObject>
#include "tools/GenericLearning.h"
#include "DataBase/databasemanager.h"
using namespace std;
class ProvidenceEE : public QObject
{
    Q_OBJECT
public:
    explicit ProvidenceEE(int welderID = 0, QObject *parent = nullptr);
    void ResetProcess();
    void SetProcess(const bool isTrained);
    void CalibrateSPCProcess(const QList<DataBaseManager::DB_MANUAL>& sourceList);
    void CalibrateAIProcess(const QList<DataBaseManager::DB_MANUAL>& sourceList);
    void SetRelevantParam();
    void GetSPCProcess(GenericLearning::PROCESS_PARAM* _param) const;
    void GetAIProcess(GenericLearning::CENTRALIZED_PROPERTY* _centralized, GenericLearning::AI_POLYNOMIAL_COEFFICIENT* _coefficient) const;
private:
    struct INSIGHT_PARAM{
        int Time;
        int Power;
        int Preheight;
        int PostHeight;
        int ActualPeelForce;
        int ActualResidual;
    };
    GenericLearning::PROCESS_PARAM ProcessParam[GenericLearning::TOTALPARA];
    GenericLearning::AI_POLYNOMIAL_COEFFICIENT PolynomialCoefficient[GenericLearning::STRENGTH_MAX];
    GenericLearning::CENTRALIZED_PROPERTY CentralizedProperty;
private:
    int m_WelderID;
signals:
};

#endif // PROVIDENCEEE_H
