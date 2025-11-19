#include "providenceEE.h"
ProvidenceEE* ProvidenceEE::m_ptrInstance = nullptr;
ProvidenceEE::ProvidenceEE(QObject *parent)
    : QObject{parent}
{
#if RASPBERRY
    GenericLearning::SetDebugMode(1);

    SetRelevantParam();

    ProcessParam[GenericLearning::TIME].Enable = true;
    ProcessParam[GenericLearning::POWER].Enable = true;
    ProcessParam[GenericLearning::PREHEIGHT].Enable = true;
    ProcessParam[GenericLearning::POSTHEIGHT].Enable = true;

    GenericLearning::GetAICentralizedProperty(CentralizedProperty);
    GenericLearning::GetAITrainedCoefficient(GenericLearning::PEEL_FORCE, 	PolynomialCoefficient[GenericLearning::STRENGTH0]);
    GenericLearning::GetAITrainedCoefficient(GenericLearning::RESIDUAL, 	PolynomialCoefficient[GenericLearning::STRENGTH1]);
#endif
}

ProvidenceEE *ProvidenceEE::getInstance()
{
    if(m_ptrInstance == nullptr)
        m_ptrInstance = new ProvidenceEE();
    return m_ptrInstance;
}

void ProvidenceEE::ResetProcess()
{
#if RASPBERRY
    GenericLearning::ResetProcessParam();
    GenericLearning::ResetAIModel();
#endif
}

void ProvidenceEE::SetProcess()
{
#if RASPBERRY
    GenericLearning::ResetProcessParam();
    GenericLearning::ResetAIModel();
    GenericLearning::SetProcessParam(GenericLearning::TIME, ProcessParam[GenericLearning::TIME]);
    GenericLearning::SetProcessParam(GenericLearning::POWER, ProcessParam[GenericLearning::POWER]);
    GenericLearning::SetProcessParam(GenericLearning::PREHEIGHT, ProcessParam[GenericLearning::PREHEIGHT]);
    GenericLearning::SetProcessParam(GenericLearning::POSTHEIGHT, ProcessParam[GenericLearning::POSTHEIGHT]);

    GenericLearning::SetAICentralizedProperty(CentralizedProperty);
    GenericLearning::SetAITrainedCoefficient(GenericLearning::PEEL_FORCE, 	PolynomialCoefficient[GenericLearning::STRENGTH0]);
    GenericLearning::SetAITrainedCoefficient(GenericLearning::RESIDUAL, 	PolynomialCoefficient[GenericLearning::STRENGTH1]);

#endif
}

void ProvidenceEE::CalibrateSPCProcess(const QList<DataBaseManager::DB_MANUAL>& sourceList)
{
#if RASPBERRY
    GenericLearning::ResetProcessParam();
    for(int i = 0; i < sourceList.size(); i++)
	{
        GenericLearning::UpdateCurrentValue(GenericLearning::TIME, 		sourceList[i].WeldTime);
        GenericLearning::UpdateCurrentValue(GenericLearning::POWER, 	sourceList[i].PeakPower);
        GenericLearning::UpdateCurrentValue(GenericLearning::PREHEIGHT, sourceList[i].Preheight);
        GenericLearning::UpdateCurrentValue(GenericLearning::POSTHEIGHT,sourceList[i].PostHeight);

        GenericLearning::UpdateProcessParameter();

        GenericLearning::GetProcessParam(GenericLearning::TIME, 		&ProcessParam[GenericLearning::TIME]);
        GenericLearning::GetProcessParam(GenericLearning::POWER, 		&ProcessParam[GenericLearning::POWER]);
        GenericLearning::GetProcessParam(GenericLearning::PREHEIGHT, 	&ProcessParam[GenericLearning::PREHEIGHT]);
        GenericLearning::GetProcessParam(GenericLearning::POSTHEIGHT, 	&ProcessParam[GenericLearning::POSTHEIGHT]);
	}
#else
    Q_UNUSED(sourceList)
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
#else
    Q_UNUSED(sourceList)
#endif
}

void ProvidenceEE::SetRelevantParam()
{
#if RASPBERRY
    GenericLearning::SetGeneralFactorGoodnessRating(80);
    GenericLearning::SetSingleFactorGoodnessRating(20);
    GenericLearning::SetSpecificRangeSigmaSetting(5);
#endif
}

void ProvidenceEE::GetSPCProcess(GenericLearning::PROCESS_PARAM* _param) const
{
#if RASPBERRY
    if(_param != nullptr)
    {
        memcpy(_param, ProcessParam, sizeof(GenericLearning::PROCESS_PARAM) * GenericLearning::TOTALPARA);
    }
#else
    Q_UNUSED(_param)
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
#else
    Q_UNUSED(_centralized)
    Q_UNUSED(_coefficient)
#endif
}

void ProvidenceEE::UpdateNewComingValue(const GenericLearning::FACTOR_DEF factor, const int value)
{
#if RASPBERRY
    GenericLearning::UpdateCurrentValue(factor, value);
#else
    Q_UNUSED(factor)
    Q_UNUSED(value)
#endif
}

void ProvidenceEE::PredictFromAIModel(const GenericLearning::FACTOR_DEF factor, const int time, const int power, double &result)
{
#if RASPBERRY
    GenericLearning::PredictFromAIModel(factor, time, power, result);
#else
    Q_UNUSED(factor)
    Q_UNUSED(time)
    Q_UNUSED(power)
    Q_UNUSED(result)
#endif
}

bool ProvidenceEE::GetSPCGoodnessResult()
{
#if RASPBERRY
    return GenericLearning::GetGoodnessResult();
#else
    return true;
#endif
}

void ProvidenceEE::SetProcessPara(const DataBaseManager::DB_MODEL model, const bool isHeightEncoderEnabled)
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
    ProcessParam[GenericLearning::PREHEIGHT].Enable = isHeightEncoderEnabled;
    ProcessParam[GenericLearning::PREHEIGHT].SampleCount = model.SampleCount;
    ProcessParam[GenericLearning::POSTHEIGHT].Alpha = model.PostHeight.Alpha;
    ProcessParam[GenericLearning::POSTHEIGHT].Beta = model.PostHeight.Beta;
    ProcessParam[GenericLearning::POSTHEIGHT].Enable = isHeightEncoderEnabled;
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
