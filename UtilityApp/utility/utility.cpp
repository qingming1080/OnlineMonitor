#include "utility.h"
#include "../definition.h"
Utility::DATA_FORMAT    Utility::m_txtData[Utility::DIN_end];
int                     Utility::m_iMaxPower    = 5500;
Utility*                Utility::_Utility       = nullptr;
double Utility::String2FormatedData(DATA_TYPE index, QString data)
{
    QString strTemp = data.trimmed();
    if(strTemp.isEmpty() == true)
        return static_cast<double>(ERROR);

    QByteArray tmpArray = strTemp.toLatin1();
    const char *s = tmpArray.data();
    int i = 0;
    while(((*s >= '0') && (*s <= '9')) || (*s == '.') || (*s == '-'))
    {
        s++;
        i++;
    }
    strTemp.remove(i, strTemp.size() - i);
    double tmpValue = strTemp.toDouble();
    const int i_tmp = 1 / m_txtData[index].Factor;
    tmpValue =  tmpValue * i_tmp;
    return tmpValue;
}

QString Utility::FormatedData2String(DATA_TYPE index, double data)
{
    QString tmpStr;
    if(m_txtData[index].Format.contains("d") == true)
        tmpStr.sprintf(m_txtData[index].Format.toStdString().c_str(),   static_cast<int>(data * static_cast<double>(m_txtData[index].Factor)));
    else if(m_txtData[index].Format.contains("f") == true)
        tmpStr.sprintf(m_txtData[index].Format.toStdString().c_str(),   static_cast<double>(data * static_cast<double>(m_txtData[index].Factor)));
    else
        tmpStr.clear();
    return tmpStr;
}

QString Utility::FormatedData2String(DATA_TYPE index, float data)
{
    QString tmpStr;
    if(m_txtData[index].Format.contains("d") == true)
        tmpStr.sprintf(m_txtData[index].Format.toStdString().c_str(),   static_cast<int>(data * m_txtData[index].Factor));
    else if(m_txtData[index].Format.contains("f") == true)
        tmpStr.sprintf(m_txtData[index].Format.toStdString().c_str(),   static_cast<double>(data * m_txtData[index].Factor));
    else
        tmpStr.clear();
    return tmpStr;
}

QString Utility::FormatedData2String(DATA_TYPE index, int data)
{
    QString tmpStr;
    if(m_txtData[index].Format.contains("d") == true)
        tmpStr.sprintf(m_txtData[index].Format.toStdString().c_str(),   static_cast<int>(data * m_txtData[index].Factor));
    else if(m_txtData[index].Format.contains("f") == true)
        tmpStr.sprintf(m_txtData[index].Format.toStdString().c_str(),   static_cast<double>(data * m_txtData[index].Factor));
    else
        tmpStr.clear();
    return tmpStr;
}

QString Utility::FormatedData2String(DATA_TYPE index, long data)
{
    QString tmpStr;
    if(m_txtData[index].Format.contains("d") == true)
        tmpStr.sprintf(m_txtData[index].Format.toStdString().c_str(),   static_cast<long>(data * m_txtData[index].Factor));
    else if(m_txtData[index].Format.contains("f") == true)
        tmpStr.sprintf(m_txtData[index].Format.toStdString().c_str(),   static_cast<double>(data * m_txtData[index].Factor));
    else
        tmpStr.clear();
    return tmpStr;
}

float Utility::FormatedData2Float(DATA_TYPE index, int data)
{
    if(m_txtData[index].Format.contains("f") == true)
        return (data * m_txtData[index].Factor);
    else
        return static_cast<float>(ERROR);
}

int Utility::FormatedData2Integer(DATA_TYPE index, int data)
{
    if(m_txtData[index].Format.contains("d") == true)
        return static_cast<int>(data * m_txtData[index].Factor);
    else
        return static_cast<int>(ERROR);
}

Utility *Utility::GetInstance()
{
    return (_Utility != nullptr) ? _Utility : (_Utility = new Utility());
}

Utility::Utility() {
    initTextData();
}

void Utility::initTextData()
{
    //          index                       data    min                          max                        incrementor factor                      formater
    QString str = QString("%.2fmm").append(QChar(0xB2));
    setTextData(DINGauge,                   0,      MINEDITWIRE,                 MAXEDITWIRE,                1,      static_cast<double>(0.01),      str);//"%.2fmm²"
    setTextData(DINGaugeAWG,                0,      MINWIREAREA_AWG,             MAXWIREAREA_AWG,            1,      1,                              "%dAWG");
    str = QString("%.2fmm").append(QChar(0xB2));
    setTextData(DINCrossSection,            0,      MINWIREAREA,                 MAXWIREAREA,                1,      static_cast<double>(0.01),      str);//"%.2fmm²"
    setTextData(DINEnergy,                  0,      MINENERGY,                   MAXENERGY,                  2,      1,                              "%dJ");
    setTextData(DINEnergyNoUnit,            0,      MINENERGY,                   MAXENERGY,                  2,      1,                              "%d");

    setTextData(DINWidth,                   0,      MINWIDTH,                    NORMALMAXWIDTH,             2,      static_cast<double>(0.01),      "%.2fmm");
    setTextData(DINPressure,                0,      MINWELDPRESSURE,             MAXWELDPRESSURE,            2,      static_cast<double>(0.1),       "%.1fpsi");
    setTextData(DINPressureNoUnit,          0,      MINWELDPRESSURE,             MAXWELDPRESSURE,            2,      static_cast<double>(0.1),       "%.1f");
    setTextData(DINTriggerPressure,         0,      MINTRIGPRESSURE,             NORMALMAXTRIGPRESSURE,      2,      static_cast<double>(0.1),       "%.1fpsi");
    setTextData(DINTriggerPressureNoUnit,   0,      MINTRIGPRESSURE,             NORMALMAXTRIGPRESSURE,      2,      static_cast<double>(0.1),       "%.1f");

    // Force is actually not displayed anywhere
    setTextData(DINForcePl,                 0,      MINFORCE,                    static_cast<int>(MAXFORCE), 2,      static_cast<double>(0.1),       "%.1fpsi");
    setTextData(DINForceMs,                 0,      MINFORCE,                    static_cast<int>(MAXFORCE), 2,      static_cast<double>(0.1),       "%.1fpsi");

    str = QString("%d%1%2").arg(QString(QChar(0x03BC))).arg("m");
    setTextData(DINAmplitude,               0,      MINAMPLITUDE,                MAXAMPLITUDE,               1,      1,                              str);
    setTextData(DINAmplitudeNoUnit,         0,      MINAMPLITUDE,                MAXAMPLITUDE,               1,      1,                              "%d");

    setTextData(DINActTime,                 0,      MINTIME,                     MAXTIME,                    2,      static_cast<double>(0.01),      "%.2fs");
    setTextData(DINSetTime,                 0,      MINSETTIME,                  MAXSETTIME,                 2,      static_cast<double>(0.001),     "%.2fs");
    setTextData(DINSetTimeNoUnit,           0,      MINSETTIME,                  MAXSETTIME,                 2,      static_cast<double>(0.01),      "%.2f");
    setTextData(DINActTimeNoUnit,           0,      MINTIME,                     MAXTIME,                    2,      static_cast<double>(0.01),      "%.2f");
    setTextData(DINTimePl,                  0,      MINTIME,                     MAXTIME,                    2,      static_cast<double>(0.01),       "%.2fs");
    setTextData(DINTimeMs,                  0,      MINTIME,                     MAXTIME,                    2,      static_cast<double>(0.01),       "%.2fs");
    setTextData(DINActPower,                0,      MINPOWER,                    m_iMaxPower,                100,    1,                              "%dW");
    setTextData(DINActPowerNoUnit,          0,      MINPOWER,                    m_iMaxPower,                100,    1,                              "%d");
    setTextData(DINPowerPl,                 0,      MINPOWER,                    m_iMaxPower,                100,    1,                              "%dW");
    //    SetTextData(DINPowerMs, 0, MINPOWER,
    //                _Interface->StatusData.Soft_Settings.SonicGenWatts, 100, 1, "%dW");
    setTextData(DINPowerMs,                 0,      MINPOWER,                    m_iMaxPower,                100,    1,                              "%dW");
    setTextData(DINPowerNoUnit,             0,      MINPOWER,                    m_iMaxPower,                100,    1,                              "%d");
    setTextData(DINPowerSupply,             0,      MINPOWERSUPPLY,              MAXPOWERSUPPLY,             100,    1,                              "%dw");

    setTextData(DINActPreHgt,               0,      MINHEIGHT,                   MAXHEIGHT,                  2,      static_cast<double>(0.01),       "%.2fmm");
    setTextData(DINActPreHgtNoUnit,         0,      MINHEIGHT,                   MAXHEIGHT,                  2,      static_cast<double>(0.01),       "%.2f");
    setTextData(DINPre_HgtPl,               0,      MINHEIGHT,                   MAXHEIGHT,                  2,      static_cast<double>(0.01),       "%.2fmm");
    setTextData(DINPre_HgtMs,               0,      MINHEIGHT,                   MAXHEIGHT,                  2,      static_cast<double>(0.01),       "%.2fmm");
    setTextData(DINPre_HgtNoUnit,           0,      MINHEIGHT,                   MAXHEIGHT,                  2,      static_cast<double>(0.01),       "%.2f");
    setTextData(DINActHgt,                  0,      MINHEIGHT,                   MAXHEIGHT,                  2,      static_cast<double>(0.01),       "%.2fmm");
    setTextData(DINActHgtNoUnit,            0,      MINHEIGHT,                   MAXHEIGHT,                  2,      static_cast<double>(0.01),       "%.2f");
    setTextData(DINHeightPl,                0,      MINHEIGHT,                   MAXHEIGHT,                  2,      static_cast<double>(0.01),       "%.2fmm");
    setTextData(DINHeightMs,                0,      MINHEIGHT,                   MAXHEIGHT,                  2,      static_cast<double>(0.01),       "%.2fmm");
    setTextData(DINHeightNoUnit,            0,      MINHEIGHT,                   MAXHEIGHT,                  2,      static_cast<double>(0.01),       "%.2f");

    setTextData(DINHeightCorrection,        0,      MINHEIGHT,                   MAXHEIGHT,                  2,      static_cast<double>(0.01),       "%.2fmm");
    setTextData(DINWidthCorrection,         0,      MINWIDTH,                    MAXWIDTH2032,               2,      static_cast<double>(0.01),       "%.2fmm");

    setTextData(DINABDelay,                 0,      MINABDELAY,                  MAXABDELAY,                 2,      static_cast<double>(0.01),       "%.2fs");
    setTextData(DINABDelayNoUnit,           0,      MINABDELAY,                  MAXABDELAY,                 2,      static_cast<double>(0.01),       "%.2f");
    setTextData(DINABDuration,              0,      MINABDURATION,               MAXABDURATION,              2,      static_cast<double>(0.01),       "%.2fs");
    setTextData(DINABDurationNoUnit,        0,      MINABDURATION,               MAXABDURATION,              2,      static_cast<double>(0.01),       "%.2f");
    setTextData(DINPartCounter,             0,      MINPARTCOUNT,                MAXPARTCOUNT,               0,      1,                              "%dPcs");
    setTextData(DINStopCounter,             0,      MINSTOPCOUNT,                MAXSTOPCOUNT,               2,      1,                              "%dPcs");
    setTextData(DINSqueezeTime,             0,      MINSQUEEZETIME,              MAXSQUEEZETIME,             2,      static_cast<double>(0.01),       "%.2fs");
    setTextData(DINSqueezeTimeNoUnit,       0,      MINSQUEEZETIME,              MAXSQUEEZETIME,             2,      static_cast<double>(0.01),       "%.2f");
    setTextData(DINHoldTime,                0,      MINHOLDTIME,                 MAXHOLDTIME,                2,      static_cast<double>(0.01),       "%.2fs");
    setTextData(DINHoldTimeNoUnit,          0,      MINHOLDTIME,                 MAXHOLDTIME,                2,      static_cast<double>(0.01),       "%.2f");

    setTextData(DINAntiSpliceTime,          0,      MINANTISIDETIME,             MAXANTISIDETIME,            2,      static_cast<double>(0.005),      "%.1fs" );
    setTextData(DINCutOffTime,              0,      MINCUTOFFTIME,               MAXCUTOFFTIME,              2,      static_cast<double>(0.005),      "%.1fs");

    // Flag word is a bit field and must have all bits active
    setTextData(DINFlagBits,                0,      0x8000,                      0x7FFF,                     0,      1,                              "");

    setTextData(DINPreBurst,                0,      MINPREBURST,                 MAXPREBURST,                10,     static_cast<double>(0.01),       "%.2fs");
    setTextData(DINWeldMode,                0,      0,                           2,                          1,      1,                              "");

    setTextData(DINEnergy2Step,             0,      MINSTEPENERGY,               MAXENERGY,                  2,      1,                              "%dJ");
    setTextData(DINPower2Step,              0,      MINPOWER,                    m_iMaxPower,                100,    1,                              "%dW");
    setTextData(DINTime2Step,               0,      MINTIME,                     MAXSTEPTIME,                2,      static_cast<double>(0.001),      "%.2fs");
    setTextData(DINCoolDur,                 0,      MINCOOLDUR,                  MAXCOOLDUR,                 1,      static_cast<double>(0.01),       "%.2fs");
    setTextData(DINCoolDel,                 0,      MINCOOLDEL,                  MAXCOOLDEL,                 1,      static_cast<double>(0.01),       "%.2fs");

    str = QString("%.2fmm").append(QChar(0xB2));
    setTextData(DINFormulaArea,             0,      MINFORMULAAREA,              MAXFORMULAAREA,             1,      1,                              str);//"%.2fmm²"
    setTextData(DINFormulaWidthOffset,      0,      0,                           0,                          1,      1,                              "%dmm");

    // setTextData(DINServerPortNumber,        0, MINSERVER_PORT_NUMBER, MAXSERVER_PORT_NUMBER, 1, 1, "%d");
    setTextData(DINHornCountLimit,          0,      MINHORNCOUNTLIMIT,           MAXHORNCOUNTLIMIT,          1,      1,                              "%d");
    setTextData(DINHornEnergyLimit,         0,      MINHORNENERGYLIMIT,          MAXHORNENERGYLIMIT,         1,      1,                              "%.1fKJ");
    setTextData(DINAnvilCountLimit,         0,      MINANVILCOUNTLIMIT,          MAXANVILCOUNTLIMIT,         1,      1,                              "%d");
    setTextData(DINAnvilEnergyLimit,        0,      MINANVILENERGYLIMIT,         MAXANVILENERGYLIMIT,        1,      1,                              "%.1fKJ");
    setTextData(DINGatherCountLimit,        0,      MINGATHERCOUNTLIMIT,         MAXGATHERCOUNTLIMIT,        1,      1,                              "%d");
    setTextData(DINGatherEnergyLimit,       0,      MINGATHERENERGYLIMIT,        MAXGATHERENERGYLIMIT,       1,      1,                              "%.1fKJ");
    setTextData(DINGuideCountLimit,         0,      MINGUIDECOUNTLIMIT,          MAXGUIDECOUNTLIMIT,         1,      1,                              "%d");
    setTextData(DINGuideEnergyLimit,        0,      MINGUIDEENERGYLIMIT,         MAXGUIDEENERGYLIMIT,        1,      1,                              "%.1fKJ");
    setTextData(DINConverterLimit,          0,      MINCONVERTERLIMIT,           MAXCONVERTERLIMIT,          1,      1,                              "%d");
    setTextData(DINPercentTeachMode,        0,      MINPERCENTTEACHMODE,         MAXPERCENTTEACHMODE,        1,      1,                              "%d%");
    setTextData(DINSigmaTeachMode,          0,      MINSIGMATEACHMODE,           MAXSIGMATEACHMODE,          1,      1,                              "%d");
    setTextData(DINGraphTimeMS,             0,      MINTIME,                     MAXTIME,                    2,      1,                              "%d");
    setTextData(DINGraphPower,              0,      MINPOWER,                    m_iMaxPower,                100,    1,                              "%d");
    setTextData(DINGraphHeight,             0,      MINHEIGHT,                   MAXHEIGHT,                  2,      static_cast<double>(0.01),       "%.2f");
    setTextData(DINTestQuantity,            0,      MINTESTQUANTITY,             MAXTESTQUANTITY,            1,      1,                              "%d");
    setTextData(DINSequenceQuantity,        0,      MINSEQUENCEQUANTITY,         MAXSEQUENCEQUANTITY,        1,      1,                              "%d");
    str = QString("%d%1%2").arg(QString(QChar(0x03BC))).arg("m");
    setTextData(DINDefaultAmplitude,        0,      MINAMPLITUDE,                MAXAMPLITUDE,               1,      1,                              str);//"%dμm"
    setTextData(DINTeachModeQuantitySTD,    0,      MINTEACHMODEQUANTITY_STD,    MAXTEACHMODEQUANTITY_STD,   1,      1,                              "%d");
    setTextData(DINTeachModeQuantityAUTO,   0,      MINTEACHMODEQUANTITY_AUTO,   MAXTEACHMODEQUANTITY_AUTO,  1,      1,                              "%d");
    setTextData(DINTeachModeQuantitySIGMA,  0,      MINTEACHMODEQUANTITY_SIGMA,  MAXTEACHMODEQUANTITY_SIGMA, 1,      1,                              "%d");
    setTextData(DINTuneFrequence,           0,      MINTUNEFREQUENCE,            MAXTUNEFREQUENCE,           100,    1,                              "%dHz");
    setTextData(DINFreqOffset,              0,      MINFREQOFFSET,               MAXFREQOFFSET,              100,    1,                              "%dHz");
    setTextData(DINActualFrequence,         0,      MINFREQUENCE,                MAXFREQUENCE,               100,    1,                              "%dHz");
    setTextData(DINALPHA,                   0,      0,                           0,                          0,      1.00,                           "%.4f");
    setTextData(DINBETA,                    0,      0,                           0,                          0,      1.00,                           "%.4f");
    setTextData(DIN_SPEC_FLOAT_LIMIT,       0,      0,                           0,                          0,      1.00,                           "%.2f");
    setTextData(DIN_SPEC_INT_LIMIT,         0,      0,                           0,                          0,      1,                              "%d");
    setTextData(DINPresetCount,             0,      MINPARTCOUNT,                MAXPARTCOUNT,               0,      1,                              "%d");
}

void Utility::setTextData(const DATA_TYPE index, const int data, const int min, const int max, const int incrementor, const double factor, const QString formater)
{
    m_txtData[index].Data           = data;
    m_txtData[index].Min            = min;
    m_txtData[index].Max            = max;
    m_txtData[index].Incrementor    = incrementor;
    m_txtData[index].Factor         = factor;
    m_txtData[index].Format         = formater;
}
