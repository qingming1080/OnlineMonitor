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
		double PowrStd;
		double ForceMean;
		double ResidualMean;
	};
private:
	static void displayCentralizedPropertyInfo(); 
	static void displayCoefficientInfo(const int tmpFactor);
	static int 	m_isDebugMode;
public:
	static int	ResetProcessParam();
	static int	GetProcessParam(FACTOR_DEF tmpFactor, PROCESS_PARAM* _param);
	static int	SetProcessParam(FACTOR_DEF tmpFactor, const PROCESS_PARAM param);
	static int	UpdateCurrentValue(FACTOR_DEF tmpFactor, const int value);
	static int	UpdateProcessParameter();
	/****************************************************************/
	/* generalRating range is 20% ~ 100% default 80%                */
	/****************************************************************/
	static void SetGeneralFactorGoodnessRating(const double generalRating);
	/****************************************************************/
	/* singleRating range is 20% ~ 100%  default 20%                */
	/****************************************************************/
	static void SetSingleFactorGoodnessRating(const double singleRating);
	/****************************************************************/
	/* Specific Sigma range is 3 ~ 5  default 5               */
	/****************************************************************/
	static void SetSpecificRangeSigmaSetting(const double sigmaSetting);
	
	static bool GetGoodnessResult();
	
	//Following definitions are for AI algorithm
	static int AppendRawDataForAIModel(const int tmpFactor, const double value);
	static int ResetAIModel();
	static int TrainAIModel(const int tmpFactor);
	static int PredictFromAIModel(const int tmpFactor, const double time, const double power, double& value);	
	static int GetAITrainedCoefficient(const int tmpFactor, GenericLearning::AI_POLYNOMIAL_COEFFICIENT& coefficient);
	static int SetAITrainedCoefficient(const int tmpFactor, const GenericLearning::AI_POLYNOMIAL_COEFFICIENT coefficient);
	static int GetAICentralizedProperty(GenericLearning::CENTRALIZED_PROPERTY& property);
	static int SetAICentralizedProperty(const GenericLearning::CENTRALIZED_PROPERTY property);
	static void SetDebugMode(const int isDebug);
	static int GetDebugMode();
};
#endif
