#include "providenceEE.h"
ProvidenceEE::ProvidenceEE(int welderID, QObject *parent)
    : QObject{parent}, m_WelderID(welderID)
{
#if RASPBERRY
    GenericLearning::SetDebugMode(1);
    ProcessParam[GenericLearning::TIME].Enable = true;
    ProcessParam[GenericLearning::POWER].Enable = true;
    ProcessParam[GenericLearning::PREHEIGHT].Enable = true;
    ProcessParam[GenericLearning::POSTHEIGHT].Enable = true;

    GenericLearning::GetAICentralizedProperty(CentralizedProperty);
    GenericLearning::GetAITrainedCoefficient(GenericLearning::PEEL_FORCE, 	PolynomialCoefficient[GenericLearning::STRENGTH0]);
    GenericLearning::GetAITrainedCoefficient(GenericLearning::RESIDUAL, 	PolynomialCoefficient[GenericLearning::STRENGTH1]);
#endif
}

void ProvidenceEE::ResetProcess()
{
#if RASPBERRY
    GenericLearning::ResetProcessParam();
    GenericLearning::ResetAIModel();
#endif
}

void ProvidenceEE::SetProcess(const bool isTrained)
{
#if RASPBERRY
    GenericLearning::ResetProcessParam();
    GenericLearning::ResetAIModel();
    GenericLearning::SetProcessParam(GenericLearning::TIME, ProcessParam[GenericLearning::TIME]);
    GenericLearning::SetProcessParam(GenericLearning::POWER, ProcessParam[GenericLearning::POWER]);
    GenericLearning::SetProcessParam(GenericLearning::PREHEIGHT, ProcessParam[GenericLearning::PREHEIGHT]);
    GenericLearning::SetProcessParam(GenericLearning::POSTHEIGHT, ProcessParam[GenericLearning::POSTHEIGHT]);
    if(isTrained == true)
    {
        GenericLearning::SetAICentralizedProperty(CentralizedProperty);
        GenericLearning::SetAITrainedCoefficient(GenericLearning::PEEL_FORCE, 	PolynomialCoefficient[GenericLearning::STRENGTH0]);
        GenericLearning::SetAITrainedCoefficient(GenericLearning::RESIDUAL, 	PolynomialCoefficient[GenericLearning::STRENGTH1]);
        cout << "Current Active Recipe has been Trained!" << endl;
    }
    else
    {
        GenericLearning::GetAICentralizedProperty(CentralizedProperty);
        GenericLearning::GetAITrainedCoefficient(GenericLearning::PEEL_FORCE, 	PolynomialCoefficient[GenericLearning::STRENGTH0]);
        GenericLearning::GetAITrainedCoefficient(GenericLearning::RESIDUAL, 	PolynomialCoefficient[GenericLearning::STRENGTH1]);
        cout << "Current Active Recipe is not Trained!" << endl;
    }
#endif
}

void ProvidenceEE::CalibrateSPCProcess(const QList<DataBaseManager::DB_MANUAL>& sourceList)
{
#if RASPBERRY
    GenericLearning::ResetProcessParam();
    for(int i = 0; i < sourceList.size(); i++)
	{
        INSIGHT_PARAM InsightParam;

        if(sourceList[i].IsSelected == true)
        {
            InsightParam.Power = sourceList[i].PeakPower;
            InsightParam.Time = sourceList[i].WeldTime;
            InsightParam.Preheight = sourceList[i].Preheight;
            InsightParam.PostHeight = sourceList[i].PostHeight;

            GenericLearning::UpdateCurrentValue(GenericLearning::TIME, 		InsightParam.Time);
            GenericLearning::UpdateCurrentValue(GenericLearning::POWER, 	InsightParam.Power);
            GenericLearning::UpdateCurrentValue(GenericLearning::PREHEIGHT, InsightParam.Preheight);
            GenericLearning::UpdateCurrentValue(GenericLearning::POSTHEIGHT,InsightParam.PostHeight);

            GenericLearning::UpdateProcessParameter();

            GenericLearning::GetProcessParam(GenericLearning::TIME, 		&ProcessParam[GenericLearning::TIME]);
            GenericLearning::GetProcessParam(GenericLearning::POWER, 		&ProcessParam[GenericLearning::POWER]);
            GenericLearning::GetProcessParam(GenericLearning::PREHEIGHT, 	&ProcessParam[GenericLearning::PREHEIGHT]);
            GenericLearning::GetProcessParam(GenericLearning::POSTHEIGHT, 	&ProcessParam[GenericLearning::POSTHEIGHT]);
        }
		
        // ++InsightFinish;
	}
#endif
}

void ProvidenceEE::CalibrateAIProcess(const QList<DataBaseManager::DB_MANUAL> &sourceList)
{
#if RASPBERRY
    GenericLearning::ResetAIModel();
    for(int i = 0; i < sourceList.size(); i++)
    {
        GenericLearning::AppendRawDataForAIModel(GenericLearning::TIME,			sourceList[i].WeldTime);
        GenericLearning::AppendRawDataForAIModel(GenericLearning::POWER,		sourceList[i].PeakPower);
        GenericLearning::AppendRawDataForAIModel(GenericLearning::PEEL_FORCE,	sourceList[i].ActualForce);
        GenericLearning::AppendRawDataForAIModel(GenericLearning::RESIDUAL,		sourceList[i].ActualResidual);
    }
    GenericLearning::TrainAIModel(GenericLearning::PEEL_FORCE);
    GenericLearning::TrainAIModel(GenericLearning::RESIDUAL);
    GenericLearning::GetAICentralizedProperty(CentralizedProperty);
    GenericLearning::GetAITrainedCoefficient(GenericLearning::PEEL_FORCE, 	PolynomialCoefficient[GenericLearning::STRENGTH0]);
    GenericLearning::GetAITrainedCoefficient(GenericLearning::RESIDUAL, 	PolynomialCoefficient[GenericLearning::STRENGTH1]);
    // m_isTrained = true;GenericLearning
    cout << "Training Completed!!!" << endl;
#endif
}

void ProvidenceEE::SetRelevantParam()
{

}

void ProvidenceEE::GetSPCProcess(GenericLearning::PROCESS_PARAM* _param) const
{
#if RASPBERRY
    if(_param != nullptr)
    {
        memcpy(_param, ProcessParam, sizeof(GenericLearning::PROCESS_PARAM) * GenericLearning::TOTALPARA);
    }
#endif
}

void ProvidenceEE::GetAIProcess(GenericLearning::CENTRALIZED_PROPERTY *_centralized, GenericLearning::AI_POLYNOMIAL_COEFFICIENT *_coefficient) const
{
#if RASPBERRY
    if((_centralized != nullptr) && (_coefficient != nullptr))
    {
        memcpy(_centralized, &CentralizedProperty, sizeof(GenericLearning::CENTRALIZED_PROPERTY));
        memcpy(_coefficient, PolynomialCoefficient, sizeof(GenericLearning::AI_POLYNOMIAL_COEFFICIENT) * GenericLearning::STRENGTH_MAX);
    }
#endif
}
