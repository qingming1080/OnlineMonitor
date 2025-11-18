#include "providenceEE.h"
ProvidenceEE::ProvidenceEE(int welderID, QObject *parent)
    : QObject{parent}, m_WelderID(welderID)
{
#if RASPBERRY
    _ptrLearningUtility = new GenericLearning();
    _ptrLearningUtility->SetDebugMode(1);

    SetRelevantParam();

    ProcessParam[GenericLearning::TIME].Enable = true;
    ProcessParam[GenericLearning::POWER].Enable = true;
    ProcessParam[GenericLearning::PREHEIGHT].Enable = true;
    ProcessParam[GenericLearning::POSTHEIGHT].Enable = true;

    _ptrLearningUtility->GetAICentralizedProperty(CentralizedProperty);
    _ptrLearningUtility->GetAITrainedCoefficient(GenericLearning::PEEL_FORCE, 	PolynomialCoefficient[GenericLearning::STRENGTH0]);
    _ptrLearningUtility->GetAITrainedCoefficient(GenericLearning::RESIDUAL, 	PolynomialCoefficient[GenericLearning::STRENGTH1]);
#endif
}

void ProvidenceEE::ResetProcess()
{
#if RASPBERRY
    _ptrLearningUtility->ResetProcessParam();
    _ptrLearningUtility->ResetAIModel();
#endif
}

void ProvidenceEE::SetProcess()
{
#if RASPBERRY
    _ptrLearningUtility->ResetProcessParam();
    _ptrLearningUtility->ResetAIModel();
    _ptrLearningUtility->SetProcessParam(GenericLearning::TIME, ProcessParam[GenericLearning::TIME]);
    _ptrLearningUtility->SetProcessParam(GenericLearning::POWER, ProcessParam[GenericLearning::POWER]);
    _ptrLearningUtility->SetProcessParam(GenericLearning::PREHEIGHT, ProcessParam[GenericLearning::PREHEIGHT]);
    _ptrLearningUtility->SetProcessParam(GenericLearning::POSTHEIGHT, ProcessParam[GenericLearning::POSTHEIGHT]);

    _ptrLearningUtility->SetAICentralizedProperty(CentralizedProperty);
    _ptrLearningUtility->SetAITrainedCoefficient(GenericLearning::PEEL_FORCE, 	PolynomialCoefficient[GenericLearning::STRENGTH0]);
    _ptrLearningUtility->SetAITrainedCoefficient(GenericLearning::RESIDUAL, 	PolynomialCoefficient[GenericLearning::STRENGTH1]);

#endif
}

void ProvidenceEE::CalibrateSPCProcess(const QList<DataBaseManager::DB_MANUAL>& sourceList)
{
#if RASPBERRY
    _ptrLearningUtility->ResetProcessParam();
    for(int i = 0; i < sourceList.size(); i++)
	{
        _ptrLearningUtility->UpdateCurrentValue(GenericLearning::TIME, 		sourceList[i].WeldTime);
        _ptrLearningUtility->UpdateCurrentValue(GenericLearning::POWER, 	sourceList[i].PeakPower);
        _ptrLearningUtility->UpdateCurrentValue(GenericLearning::PREHEIGHT, sourceList[i].Preheight);
        _ptrLearningUtility->UpdateCurrentValue(GenericLearning::POSTHEIGHT,sourceList[i].PostHeight);

        _ptrLearningUtility->UpdateProcessParameter();

        _ptrLearningUtility->GetProcessParam(GenericLearning::TIME, 		&ProcessParam[GenericLearning::TIME]);
        _ptrLearningUtility->GetProcessParam(GenericLearning::POWER, 		&ProcessParam[GenericLearning::POWER]);
        _ptrLearningUtility->GetProcessParam(GenericLearning::PREHEIGHT, 	&ProcessParam[GenericLearning::PREHEIGHT]);
        _ptrLearningUtility->GetProcessParam(GenericLearning::POSTHEIGHT, 	&ProcessParam[GenericLearning::POSTHEIGHT]);
	}
#endif
}

void ProvidenceEE::CalibrateAIProcess(const QList<DataBaseManager::DB_MANUAL> &sourceList)
{
#if RASPBERRY
    _ptrLearningUtility->ResetAIModel();
    for(int i = 0; i < sourceList.size(); i++)
    {
        _ptrLearningUtility->AppendRawDataForAIModel(GenericLearning::TIME,			sourceList[i].WeldTime);
        _ptrLearningUtility->AppendRawDataForAIModel(GenericLearning::POWER,		sourceList[i].PeakPower);
        _ptrLearningUtility->AppendRawDataForAIModel(GenericLearning::PEEL_FORCE,	sourceList[i].ActualForce);
        _ptrLearningUtility->AppendRawDataForAIModel(GenericLearning::RESIDUAL,		sourceList[i].ActualResidual);
    }
    _ptrLearningUtility->TrainAIModel(GenericLearning::PEEL_FORCE);
    _ptrLearningUtility->TrainAIModel(GenericLearning::RESIDUAL);
    _ptrLearningUtility->GetAICentralizedProperty(CentralizedProperty);
    _ptrLearningUtility->GetAITrainedCoefficient(GenericLearning::PEEL_FORCE, 	PolynomialCoefficient[GenericLearning::STRENGTH0]);
    _ptrLearningUtility->GetAITrainedCoefficient(GenericLearning::RESIDUAL, 	PolynomialCoefficient[GenericLearning::STRENGTH1]);
#endif
}

void ProvidenceEE::SetRelevantParam()
{
#if RASPBERRY
    _ptrLearningUtility->SetGeneralFactorGoodnessRating(80);
    _ptrLearningUtility->SetSingleFactorGoodnessRating(20);
    _ptrLearningUtility->SetSpecificRangeSigmaSetting(5);
#endif
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

void ProvidenceEE::UpdateNewComingValue(const GenericLearning::FACTOR_DEF factor, const int value)
{
#if RASPBERRY
    _ptrLearningUtility->UpdateCurrentValue(factor, value);
#endif
}

void ProvidenceEE::PredictFromAIModel(const GenericLearning::FACTOR_DEF factor, const int time, const int power, double &result)
{
#if RASPBERRY
    _ptrLearningUtility->PredictFromAIModel(factor, time, power, result);
#endif
}

bool ProvidenceEE::GetSPCGoodnessResult()
{
#if RASPBERRY
    return _ptrLearningUtility->GetGoodnessResult();
#endif
}

void ProvidenceEE::SetProcessPara(const DataBaseManager::DB_MODEL model)
{
    ProcessParam[GenericLearning::TIME].Alpha = model.WeldTime.Alpha;
    ProcessParam[GenericLearning::TIME].Beta = model.WeldTime.Beta;             
    ProcessParam[GenericLearning::TIME].Enable = true;
    ProcessParam[GenericLearning::TIME].SampleCount = model.SampleCount;
    ProcessParam[GenericLearning::POWER].Alpha = model.PeakPower.Alpha;
    ProcessParam[GenericLearning::POWER].Beta = model.PeakPower.Beta;
    ProcessParam[GenericLearning::POWER].Enable = true;
    ProcessParam[GenericLearning::POWER].SampleCount = model.SampleCount;
    ProcessParam[GenericLearning::PREHEIGHT].Alpha = model.Preheight.Alpha;
    ProcessParam[GenericLearning::PREHEIGHT].Beta = model.Preheight.Beta;
    ProcessParam[GenericLearning::PREHEIGHT].Enable = true;
    ProcessParam[GenericLearning::PREHEIGHT].SampleCount = model.SampleCount;
    ProcessParam[GenericLearning::POSTHEIGHT].Alpha = model.PostHeight.Alpha;
    ProcessParam[GenericLearning::POSTHEIGHT].Beta = model.PostHeight.Beta;
    ProcessParam[GenericLearning::POSTHEIGHT].Enable = true;
    ProcessParam[GenericLearning::POSTHEIGHT].SampleCount = model.SampleCount;
}

void ProvidenceEE::SetPolynomialCoefficient(const DataBaseManager::DB_MODEL model)
{
    PolynomialCoefficient[GenericLearning::STRENGTH0].AlgorithmType = GenericLearning::POLYNOMIAL_FIT;
    PolynomialCoefficient[GenericLearning::STRENGTH0].P00 = model.PeelForce.P00;
    PolynomialCoefficient[GenericLearning::STRENGTH0].P10 = model.PeelForce.P10;
    PolynomialCoefficient[GenericLearning::STRENGTH0].P01 = model.PeelForce.P01;
    PolynomialCoefficient[GenericLearning::STRENGTH0].P20 = model.PeelForce.P20;
    PolynomialCoefficient[GenericLearning::STRENGTH0].P11 = model.PeelForce.P11;
    PolynomialCoefficient[GenericLearning::STRENGTH0].P02 = model.PeelForce.P02;

    PolynomialCoefficient[GenericLearning::STRENGTH1].AlgorithmType = GenericLearning::POLYNOMIAL_FIT;
    PolynomialCoefficient[GenericLearning::STRENGTH1].P00 = model.Residual.P00;
    PolynomialCoefficient[GenericLearning::STRENGTH1].P10 = model.Residual.P10;
    PolynomialCoefficient[GenericLearning::STRENGTH1].P01 = model.Residual.P01;
    PolynomialCoefficient[GenericLearning::STRENGTH1].P20 = model.Residual.P20;
    PolynomialCoefficient[GenericLearning::STRENGTH1].P11 = model.Residual.P11;
    PolynomialCoefficient[GenericLearning::STRENGTH1].P02 = model.Residual.P02;
}

void ProvidenceEE::SetCentralized(const DataBaseManager::DB_MODEL model)
{
    CentralizedProperty.TimeMean = model.Centralized.TimeMean;
    CentralizedProperty.TimeStd = model.Centralized.TimeStd;
    CentralizedProperty.PowerMean = model.Centralized.PowerMean;
    CentralizedProperty.PowerStd = model.Centralized.PowerStd;
    CentralizedProperty.ForceMean = model.Centralized.ForceMean;
    CentralizedProperty.ResidualMean = model.Centralized.ResidualMean;
}
