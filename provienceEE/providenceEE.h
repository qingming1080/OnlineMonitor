#ifndef PROVIDENCEEE_H
#define PROVIDENCEEE_H

#include <QObject>
#include <iostream>
#include "tools/GenericLearning.h"
#include "define.h"
#include "model/manual.h"
#include "DataBase/databasemanager.h"
using namespace std;
class ProvidenceEE : public QObject
{
    Q_OBJECT
public:
    explicit ProvidenceEE(QObject *parent = nullptr);
    void ResetProcess();
    void SetProcess(const bool isTrained);
    void CalibrateSPCProcess(const QList<DataBaseManager::DB_MANUAL>& sourceList);
    void CalibrateAIProcess(const QList<DataBaseManager::DB_MANUAL>& sourceList);
    void SetRelevantParam();
    void GetSPCProcess(GenericLearning::PROCESS_PARAM* _param) const;
    void GetAIProcess(GenericLearning::CENTRALIZED_PROPERTY* _centralized, GenericLearning::AI_POLYNOMIAL_COEFFICIENT* _coefficient) const;
    static ProvidenceEE* GetInstance();
private:
    struct INSIGHT_PARAM{
        int Time;
        int Power;
        int Preheight;
        int PostHeight;
        int ActualPeelForce;
        int ActualResidual;
    };
    static ProvidenceEE* m_objProvidenceEE;
    static GenericLearning::PROCESS_PARAM ProcessParam[GenericLearning::TOTALPARA];
    static GenericLearning::AI_POLYNOMIAL_COEFFICIENT PolynomialCoefficient[GenericLearning::STRENGTH_MAX];
    static GenericLearning::CENTRALIZED_PROPERTY CentralizedProperty;
private:

private:

signals:
};

#endif // PROVIDENCEEE_H
