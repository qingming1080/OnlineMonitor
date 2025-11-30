#ifndef UTILITY_H
#define UTILITY_H
#include <QString>
class Utility
{

public:
    enum DATA_TYPE
    {
        // Data Index Numbers
        DINZero,
        DINGauge,               DINGaugeAWG,
        DINCrossSection,
        DINEnergy,              DINEnergyNoUnit,
        DINWidth,
        DINPressure,            DINPressureNoUnit,
        DINAmplitude,           DINAmplitudeNoUnit,
        DINActTime,             DINSetTime,                 DINSetTimeNoUnit,       DINActTimeNoUnit,           DINTimePl,              DINTimeMs,
        DINActPower,            DINActPowerNoUnit,          DINPowerPl,             DINPowerMs,                 DINPowerNoUnit,         DINPowerSupply,
        DINActPreHgt,           DINActPreHgtNoUnit,         DINPre_HgtPl,           DINPre_HgtMs,               DINPre_HgtNoUnit,
        DINActHgt,              DINActHgtNoUnit,            DINHeightPl,            DINHeightMs,                DINHeightNoUnit,   DINForcePl,             DINForceMs,

        //Used by IA detailed settings
        DINTriggerPressure,     DINTriggerPressureNoUnit,
        DINABDelay,             DINABDelayNoUnit,
        DINABDuration,          DINABDurationNoUnit,
        DINPartCounter,         DINStopCounter,
        DINSqueezeTime,         DINSqueezeTimeNoUnit,
        DINHoldTime,            DINHoldTimeNoUnit,
        DINAntiSpliceTime,      DINCutOffTime,
        DINCoolDur,             DINCoolDel,
        DINFlagBits,            DINHeightCorrection,        DINWidthCorrection,
        DINPreBurst,

        //Reference to FlagBits
        DINWeldMode,
        //Used for Amplitude Step Settings
        //DINAmpStepMode
        DINAmplitude2,
        DINEnergy2Step,         DINTime2Step,           DINPower2Step,
        DINFormulaArea,
        DINFormulaEnergyOffset,     DINFormulaWidthOffset,  DINFormulaPressureOffset,   DINFormulaAmplitudeOffset,
        DINFormulaEnergyMult,       DINFormulaWidthMult,    DINFormulaPressureMult,     DINFormulaAmplitudeMult,
        DINShrinkTubeTemperature,   DINShrinkTubeTime,
        DINServerPortNumber,
        DINHornCountLimit,          DINHornEnergyLimit,     DINAnvilCountLimit,         DINAnvilEnergyLimit,    DINGatherCountLimit,
        DINGatherEnergyLimit,       DINGuideCountLimit,     DINGuideEnergyLimit,        DINConverterLimit,
        DINPercentTeachMode,        DINSigmaTeachMode,
        DINGraphTimeMS,             DINGraphPower,          DINGraphHeight,
        DINTestQuantity,            DINSequenceQuantity,
        DINDefaultAmplitude,
        DINTeachModeQuantitySTD,    DINTeachModeQuantityAUTO,   DINTeachModeQuantitySIGMA,
        DINTuneFrequence,           DINFreqOffset,
        DINActualFrequence,
        DINALPHA,                   DINBETA,
        DIN_SPEC_FLOAT_LIMIT,       DIN_SPEC_INT_LIMIT,
        DINPresetCount,             DINPresetNum,           DINCycleNum,
        DINAlarmSign,
        DINDate,                    DINTime,
        DINPresetName,
        DIN_end,
    };
            QString FormatedData2String (DATA_TYPE index,   int data);
            QString FormatedData2String (DATA_TYPE index,   long data);
            QString FormatedData2String (DATA_TYPE index,   float data);
            QString FormatedData2String (DATA_TYPE index,   double data);

            float   FormatedData2Float  (DATA_TYPE index,   int data);
            int     FormatedData2Integer(DATA_TYPE index,   int data);

            double  String2FormatedData (DATA_TYPE index,   QString data);
    static Utility* GetInstance         ();
protected:
    Utility();
private:
    struct DATA_FORMAT
    {
        long    Data;
        long    TempData;
        long    Min;
        long    Max;
        long    Incrementor;
        float   Factor;
        QString Format;
    };

    static constexpr int DEFAULTPRESSURE        = 200;
    static constexpr int DEFAULTAMPLITUDE       = 1;
    static constexpr int MINENERGY              = 1;
    static constexpr int MINWIDTH               = 1;
    static constexpr int MINWELDPRESSURE        = 10;
    static constexpr int MINAMPLITUDE           = 1;
    static constexpr int MINTIME                = 0;
    static constexpr int MINSETTIME             = 0;
    static constexpr int MINPOWER               = 0;
    static constexpr int MINPOWERSUPPLY         = 100;

    static constexpr int MINPREHEIGHT           = 0;
    static constexpr int MINHEIGHT              = 0;
    static constexpr int MINTRIGPRESSURE        = MINWELDPRESSURE;
    static constexpr int MINABDELAY             = 0;
    static constexpr int MINABDURATION          = 0;
    static constexpr int MINPARTCOUNT           = 0;
    static constexpr int MINSTOPCOUNT           = 0;
    static constexpr int MINSQUEEZETIME         = 0;
    static constexpr int MINHOLDTIME            = 0;
    static constexpr int MINANTISIDETIME        = 100;
    static constexpr int MINCUTOFFTIME          = 100;
    static constexpr int MINPREBURST            = 0;
    static constexpr int MINFORCE               = 0;
    static constexpr int MINCOOLDUR             = 100;
    static constexpr int MAXCOOLDUR             = 6000;
    static constexpr int MINCOOLDEL             = 0;
    static constexpr int MAXCOOLDEL             = 500;
    static constexpr int MAXENERGY              = 10000;              //Joules
    static constexpr int NORMALMAXWIDTH         = 800;                //mm * 100
    static constexpr int MAXWIDTH               = 900;                //mm * 100
    static constexpr int MAXWIDTH2032           = 980;                //mm * 100
    static constexpr int MAXWELDPRESSURE        = 900;                //PSI * 10
    static constexpr int MAXAMPLITUDE           = 150;                //microns
    static constexpr int MAXTIME                = 500;               //Seconds * 100
    static constexpr int MAXSETTIME             = 5000;              //Seconds * 1000
    static constexpr int MAXPOWERSUPPLY         = 6000;
    static constexpr int MAXSTEPTIME            = 5000;               //Seconds * 1000
    static constexpr int MINSTEPENERGY          = 0;                  //Joules

    static constexpr int MAXPREHEIGHT           = 1500;               //mm * 100
    static constexpr int MAXHEIGHT              = 1500;               //mm * 100
    static constexpr int MAXTRIGPRESSURE        = 900;                //PSI * 10
    static constexpr int NORMALMAXTRIGPRESSURE  = 800;           //PSI * 10
    static constexpr int MAXABDELAY             = 50;                 //Seconds * 100
    static constexpr int MAXABDURATION          = 200;                //Seconds * 100
    static constexpr int MAXPARTCOUNT           = 30000;              //Pieces
    static constexpr int MAXSTOPCOUNT           = 1000;               //Pieces
    static constexpr int MAXSQUEEZETIME         = 200;                //Seconds * 100
    static constexpr int MAXHOLDTIME            = 200;                //Seconds * 100
    static constexpr int MAXANTISIDETIME        = 1000;               //Secs * 200
    static constexpr int MAXCUTOFFTIME          = 1000;               //Secs * 200
    static constexpr int MAXPREBURST            = 50;                 //Seconds * 1000
    static constexpr double MAXFORCE            = (1.2 * MAXWELDPRESSURE);  //PSI * 10
    static constexpr int MINWIREAREA            = 10;
    static constexpr int MAXWIREAREA            = 4000;                 //* 100
    static constexpr int MINWIREAREA_AWG        = 5;
    static constexpr int MAXWIREAREA_AWG        = 27;
    static constexpr double MINWIREREF          = 0.1;
    static constexpr int MAXWIREREF             = 40;
    static constexpr int DEFWIREAREA            = 10;
    static constexpr int MINEDITWIRE            = 10;
    static constexpr int MAXEDITWIRE            = 2000;
    static constexpr int MINFORMULAAREA         = 0;
    static constexpr int MAXFORMULAAREA         = 40;
    static constexpr int MINSTEPAMPLITUDE       = 2;                  //Min value of Amplitude2
    static constexpr int DEFAULTSTEP            = 0;                  //Default values of all Steps
    static constexpr int ZEROHEIGHTPRESSURE     = 256;              //PSI * 10
    static constexpr int DEFAULTUNLOADTIME      = 300;              //secs * 200
    static constexpr int MAXHORNCOUNTLIMIT      = 20000000;
    static constexpr int MINHORNCOUNTLIMIT      = 0;
    static constexpr int MAXHORNENERGYLIMIT     = 2000000;
    static constexpr int MINHORNENERGYLIMIT     = 0;
    static constexpr int MAXANVILCOUNTLIMIT     = 20000000;
    static constexpr int MINANVILCOUNTLIMIT     = 0;
    static constexpr int MAXANVILENERGYLIMIT    = 2000000;
    static constexpr int MINANVILENERGYLIMIT    = 0;
    static constexpr int MAXGATHERCOUNTLIMIT    = 20000000;
    static constexpr int MINGATHERCOUNTLIMIT    = 0;
    static constexpr int MAXGATHERENERGYLIMIT   = 2000000;
    static constexpr int MINGATHERENERGYLIMIT   = 0;
    static constexpr int MAXGUIDECOUNTLIMIT     = 20000000;
    static constexpr int MINGUIDECOUNTLIMIT     = 0;
    static constexpr int MAXGUIDEENERGYLIMIT    = 2000000;
    static constexpr int MINGUIDEENERGYLIMIT    = 0;
    static constexpr int MAXCONVERTERLIMIT      = 20000000;
    static constexpr int MINCONVERTERLIMIT      = 0;
    static constexpr int MAXPERCENTTEACHMODE    = 100;
    static constexpr int MINPERCENTTEACHMODE    = 1;
    static constexpr int MAXSIGMATEACHMODE      = 9;
    static constexpr int MINSIGMATEACHMODE      = 1;
    static constexpr int MINTESTQUANTITY        = 1;
    static constexpr int MAXTESTQUANTITY        = 50;
    static constexpr int MINSEQUENCEQUANTITY    = 1;
    static constexpr int MAXSEQUENCEQUANTITY    = 500;
    static constexpr int MINTEACHMODEQUANTITY_STD  = 1;
    static constexpr int MAXTEACHMODEQUANTITY_STD  = 50;
    static constexpr int MINTEACHMODEQUANTITY_AUTO = 15;
    static constexpr int MAXTEACHMODEQUANTITY_AUTO = 50;
    static constexpr int MINTEACHMODEQUANTITY_SIGMA = 1;
    static constexpr int MAXTEACHMODEQUANTITY_SIGMA = 50;
    static constexpr int MINTUNEFREQUENCE       = 19450;
    static constexpr int MAXTUNEFREQUENCE       = 20450;
    static constexpr int MINFREQOFFSET          = -500;
    static constexpr int MAXFREQOFFSET          = 500;
    static constexpr int MINFREQUENCE           = 19450;
    static constexpr int MAXFREQUENCE           = 20450;

    static DATA_FORMAT m_txtData[DIN_end];
    static int         m_iMaxPower;
    static Utility*    _Utility;

    void initTextData();
    void setTextData(const enum DATA_TYPE index, const int data, const int min, const int max, const int incrementor, const double factor, const QString formater);

};

#endif // UTILITY_H
