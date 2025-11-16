#ifndef GL_H_
#define GL_H_
// #ifndef __VXWORKS__
// enum RESULT
// {
// 	ERROR = -1,
// 	OK = 0
// };
// #endif
class GenericLearning
{
public:
	enum FACTOR_DEF
	{
		UNDEFINE = -1,
		TIME,
		POWER,
		PREHEIGHT,
		POSTHEIGHT,
		TOTALPARA,
		PEEL_FORCE = TOTALPARA,
		RESIDUAL,
	};
	
	struct PROCESS_PARAM
	{
		double	Alpha;
		double	Beta;
		int		SampleCount;
		bool	Enable;
	};
	//Following definitions are for AI algorithm only.
	enum AI_ALGORITHM
	{
		POLYNOMIAL_FIT 				= 0,
		GAUSSIAN_PROCESS_REGRESSION = 1
	};
	
	enum PREDICT_TYPE
	{
		STRENGTH0 	= 0,
		STRENGTH1,
		STRENGTH_MAX
	};
	
	struct AI_POLYNOMIAL_COEFFICIENT
	{
		AI_ALGORITHM AlgorithmType;
		double P00;
		double P10;
		double P01;
		double P20;
		double P11;
		double P02;
	};
	
	struct CENTRALIZED_PROPERTY
	{
		double TimeMean;
		double TimeStd;
		double PowerMean;
        double PowerStd;
		double ForceMean;
		double ResidualMean;
	};
private:
    void displayCentralizedPropertyInfo();
    void displayCoefficientInfo(const int tmpFactor);
    int 	m_isDebugMode;
public:
    int	ResetProcessParam();
    int	GetProcessParam(FACTOR_DEF tmpFactor, PROCESS_PARAM* _param);
    int	SetProcessParam(FACTOR_DEF tmpFactor, const PROCESS_PARAM param);
    int	UpdateCurrentValue(FACTOR_DEF tmpFactor, const int value);
    int	UpdateProcessParameter();
	/****************************************************************/
	/* generalRating range is 20% ~ 100% default 80%                */
	/****************************************************************/
    void SetGeneralFactorGoodnessRating(const double generalRating);
	/****************************************************************/
	/* singleRating range is 20% ~ 100%  default 20%                */
	/****************************************************************/
    void SetSingleFactorGoodnessRating(const double singleRating);
	/****************************************************************/
	/* Specific Sigma range is 3 ~ 5  default 5               */
	/****************************************************************/
    void SetSpecificRangeSigmaSetting(const double sigmaSetting);
	
    bool GetGoodnessResult();
	
	//Following definitions are for AI algorithm
    int AppendRawDataForAIModel(const int tmpFactor, const double value);
    int ResetAIModel();
    int TrainAIModel(const int tmpFactor);
    int PredictFromAIModel(const int tmpFactor, const double time, const double power, double& value);
    int GetAITrainedCoefficient(const int tmpFactor, GenericLearning::AI_POLYNOMIAL_COEFFICIENT& coefficient);
    int SetAITrainedCoefficient(const int tmpFactor, const GenericLearning::AI_POLYNOMIAL_COEFFICIENT coefficient);
    int GetAICentralizedProperty(GenericLearning::CENTRALIZED_PROPERTY& property);
    int SetAICentralizedProperty(const GenericLearning::CENTRALIZED_PROPERTY property);
    void SetDebugMode(const int isDebug);
    int GetDebugMode();
};
#endif
