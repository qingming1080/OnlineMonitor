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
    static ProvidenceEE* getInstance();
    void ResetProcess();
    void SetProcess();
    void CalibrateSPCProcess(const QList<DataBaseManager::DB_MANUAL>& sourceList);
    void CalibrateAIProcess(const QList<DataBaseManager::DB_MANUAL>& sourceList);
    void SetRelevantParam();
    void GetSPCProcess(GenericLearning::PROCESS_PARAM* _param) const;
    void GetAIProcess(GenericLearning::CENTRALIZED_PROPERTY* _centralized, GenericLearning::AI_POLYNOMIAL_COEFFICIENT* _coefficient) const;

    void UpdateNewComingValue(const GenericLearning::FACTOR_DEF factor, const int value);
    void PredictFromAIModel(const GenericLearning::FACTOR_DEF factor, const int time, const int power, double &result);
    bool GetSPCGoodnessResult();


    void SetProcessPara(const DataBaseManager::DB_MODEL model, const bool isHeightEncoderEnabled);
    void SetPolynomialCoefficient(const DataBaseManager::DB_MODEL model);
    void SetCentralized(const DataBaseManager::DB_MODEL mode);
private:
    explicit ProvidenceEE(QObject *parent = nullptr);
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
    static ProvidenceEE* m_ptrInstance;
signals:
};

#endif // PROVIDENCEEE_H
