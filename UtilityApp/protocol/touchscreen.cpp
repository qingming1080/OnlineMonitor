#include "touchscreen.h"
#include "../utility/utility.h"
#include "../definition.h"
#include <math.h>
void TouchScreen::ParseResultString2Data(const QString strData)
{
    double doubleTemp;
    Utility *_Utility = Utility::GetInstance();
    // M2010 *_ptrM2010 = M2010::Instance();

    QStringList list = strData.split(" ");
    QString strTemp = "";
    for(int i = 0; i < list.size(); i++)
    {
        strTemp = list[i];
        strTemp = strTemp.trimmed();
        if(strTemp != "")
        {
            list[i] = strTemp;
        }
        else
        {
            list.removeAt(i);
            i--;
        }
    }

    if(m_mapWeldData.size() == 0)
    {
        int indexWeldData = 0;
        m_mapWeldData.insert(indexWeldData, Utility::DINPresetNum);

        indexWeldData++;
        m_mapWeldData.insert(indexWeldData, Utility::DINCycleNum);

        indexWeldData++;
        m_mapWeldData.insert(indexWeldData, Utility::DINEnergy);

        indexWeldData++;
        m_mapWeldData.insert(indexWeldData, Utility::DINWidth);

        indexWeldData++;
        m_mapWeldData.insert(indexWeldData, Utility::DINTriggerPressure);

        indexWeldData++;
        m_mapWeldData.insert(indexWeldData, Utility::DINPressure);

        indexWeldData++;
        m_mapWeldData.insert(indexWeldData, Utility::DINAmplitude);

        indexWeldData++;
        m_mapWeldData.insert(indexWeldData, Utility::DINActTime);

        indexWeldData++;
        m_mapWeldData.insert(indexWeldData, Utility::DINActPower);

        indexWeldData++;
        m_mapWeldData.insert(indexWeldData, Utility::DINActPreHgt);

        indexWeldData++;
        m_mapWeldData.insert(indexWeldData, Utility::DINActHgt);

        indexWeldData++;
        m_mapWeldData.insert(indexWeldData, Utility::DINAlarmSign);
    }

    QMap<int, int>::const_iterator iter = m_mapWeldData.constBegin();
    while(iter != m_mapWeldData.constEnd())
    {
        if(iter.key() >= list.size())
            break;
        strTemp = list[iter.key()];
        switch(iter.value())
        {
        case Utility::DINPresetNum:
            break;
        case Utility::DINCycleNum:
            m_stWeldResult.CycleCount = strTemp.toInt();
            break;
        case Utility::DINEnergy:
            doubleTemp = _Utility->String2FormatedData(static_cast<Utility::DATA_TYPE>(iter.value()), strTemp);
            m_stWeldResult.Energy = static_cast<int>(doubleTemp);
            break;
        case Utility::DINWidth:
            doubleTemp = _Utility->String2FormatedData(static_cast<Utility::DATA_TYPE>(iter.value()), strTemp);
            m_stWeldResult.Width = static_cast<int>(doubleTemp);
            break;
        case Utility::DINTriggerPressure:
            doubleTemp = _Utility->String2FormatedData(static_cast<Utility::DATA_TYPE>(iter.value()), strTemp);
            m_stWeldResult.TPressure = static_cast<int>(doubleTemp);
            m_stWeldSetting.TPressure = static_cast<int>(doubleTemp);
            break;
        case Utility::DINPressure:
            doubleTemp = _Utility->String2FormatedData(static_cast<Utility::DATA_TYPE>(iter.value()), strTemp);
            m_stWeldResult.WPressure = static_cast<int>(doubleTemp);
            m_stWeldSetting.WPressure = static_cast<int>(doubleTemp);
            break;
        case Utility::DINAmplitude:
            doubleTemp = _Utility->String2FormatedData(static_cast<Utility::DATA_TYPE>(iter.value()), strTemp);
            m_stWeldResult.Amplitude = static_cast<int>(doubleTemp);
            m_stWeldSetting.Amplitude = static_cast<int>(doubleTemp);
            break;
        case Utility::DINActTime:
            doubleTemp = _Utility->String2FormatedData(static_cast<Utility::DATA_TYPE>(iter.value()), strTemp);
            m_stWeldResult.Time = std::round(doubleTemp);
            break;
        case Utility::DINActPower:
            doubleTemp = _Utility->String2FormatedData(static_cast<Utility::DATA_TYPE>(iter.value()), strTemp);
            m_stWeldResult.Power = static_cast<int>(doubleTemp);
            break;
        case Utility::DINActPreHgt:
            doubleTemp = _Utility->String2FormatedData(static_cast<Utility::DATA_TYPE>(iter.value()), strTemp);
            m_stWeldResult.Preheight = static_cast<int>(doubleTemp);
            break;
        case Utility::DINActHgt:
            doubleTemp = _Utility->String2FormatedData(static_cast<Utility::DATA_TYPE>(iter.value()), strTemp);
            m_stWeldResult.PostHeight = static_cast<int>(doubleTemp);
            break;
        case Utility::DINAlarmSign:
            m_stWeldResult.AlarmFlag = NONE_FAULT;
            if(strTemp == NONE_ALARM)
                m_stWeldResult.AlarmFlag = NONE_FAULT;
            else if(strTemp == OVERLOAD_ALARM)
                m_stWeldResult.AlarmFlag |= OVERLOAD_FAULT;
            else if(strTemp == TIME_ALARM)
            {
                m_stWeldResult.AlarmFlag |= TIME_FAULT;
                if(m_stWeldSetting.Time.Min != -1)
                {
                    if(m_stWeldResult.Time < m_stWeldSetting.Time.Min)
                        m_stWeldResult.AlarmFlag |= TIME_MIN_FAULT;
                }
                if(m_stWeldSetting.Time.Max |= -1)
                {
                    if(m_stWeldResult.Time > m_stWeldSetting.Time.Max)
                        m_stWeldResult.AlarmFlag |= TIME_MAX_FAULT;
                }
            }
            else if(strTemp == POWER_ALARM)
            {
                m_stWeldResult.AlarmFlag |= POWER_FAULT;
                if(m_stWeldSetting.Power.Min != -1)
                {
                    if(m_stWeldResult.Power < m_stWeldSetting.Power.Min)
                        m_stWeldResult.AlarmFlag |= POWER_MIN_FAULT;
                }
                if(m_stWeldSetting.Power.Max != -1)
                {
                    if(m_stWeldResult.Power > m_stWeldSetting.Power.Max)
                        m_stWeldResult.AlarmFlag |= POWER_MAX_FAULT;
                }
            }
            else if(strTemp == HEIGHT_ALARM)
            {
                m_stWeldResult.AlarmFlag |= HEIGHT_FAULT;
                if(m_stWeldSetting.PostHeight.Min != -1)
                {
                    if(m_stWeldResult.PostHeight < m_stWeldSetting.PostHeight.Min)
                        m_stWeldResult.AlarmFlag |= HEIGHT_MIN_FAULT;
                }
                if(m_stWeldSetting.PostHeight.Max != -1)
                {
                    if(m_stWeldResult.PostHeight > m_stWeldSetting.PostHeight.Max)
                        m_stWeldResult.AlarmFlag |= HEIGHT_MAX_FAULT;
                }
            }
            else
            {
                m_stWeldResult.AlarmFlag = NONE_FAULT;
            }
            break;
        default:
            break;
        }
        ++iter;
    }

    //TODO signal emit
}

void TouchScreen::Parse1stString2Data(QString strFirst)
{
    QString strTemp;
    double doubleTemp;
    Utility *_Utility = Utility::GetInstance();
    int nameIdx = strFirst.indexOf("Part Name:");
    int colonIdx = strFirst.indexOf(":");
    int weldModeIdx = strFirst.indexOf("Weld Mode");
    int startIdx = colonIdx + 1;
    if(nameIdx == -1)
        return;
    strTemp = strFirst.mid(startIdx, (weldModeIdx - startIdx)).trimmed();
    m_stWeldSetting.PresetName = strTemp;

    if(weldModeIdx == -1)
        return;
    int settingIdx = -1;
    if(strFirst.indexOf("Energy") != -1)
    {
        m_stWeldSetting.MODE_FLAGS.ModeWord = ENERGY_MODE;
        settingIdx = strFirst.indexOf("Energy Setting:");
    }
    else if(strFirst.indexOf("Time") != -1)
    {
        m_stWeldSetting.MODE_FLAGS.ModeWord = TIME_MODE;
        settingIdx = strFirst.indexOf("Time Setting:");
    }
    else
    {
        settingIdx = -1;
    }
    if(settingIdx == -1)
        return;

    strFirst = strFirst.mid(settingIdx);
    colonIdx = strFirst.indexOf(":");
    startIdx = colonIdx + 1;
    strTemp = strFirst.mid(startIdx).trimmed();

    switch (m_stWeldSetting.MODE_FLAGS.ModeWord)
    {
    case ENERGY_MODE:
        doubleTemp = _Utility->String2FormatedData(Utility::DINEnergy, strTemp);
        m_stWeldSetting.Energy = static_cast<unsigned short>(doubleTemp);
        break;
    case TIME_MODE:
        doubleTemp = _Utility->String2FormatedData(Utility::DINTimePl, strTemp);
        m_stWeldSetting.Time.Max = static_cast<unsigned short>(doubleTemp);
        break;
    default:
        break;
    }
}

void TouchScreen::Parse2ndString2Data(QString strSecond)
{
    int ABDelayIdx = strSecond.indexOf("AB Delay:");
    int ABDurationIdx = strSecond.indexOf("AB Duration:");
    int startIdx = -1;
    QString strTemp = "";
    double doubleTemp;
    Utility *_Utility = Utility::GetInstance();
    if(ABDelayIdx == -1)
        return;
    if(ABDurationIdx == -1)
        return;
    startIdx = strSecond.indexOf(":") + 1;
    strTemp = strSecond.mid(startIdx, ABDurationIdx - startIdx);
    doubleTemp = _Utility->String2FormatedData(Utility::DINABDelay, strTemp);
    m_stWeldSetting.ABDelay = static_cast<unsigned short>(doubleTemp);

    strSecond = strSecond.mid(ABDurationIdx);
    startIdx = strSecond.indexOf(":") + 1;
    strTemp = strSecond.mid(startIdx);
    doubleTemp = _Utility->String2FormatedData(Utility::DINABDuration, strTemp);
    m_stWeldSetting.ABDuration = static_cast<unsigned short>(doubleTemp);
}

void TouchScreen::Parse3rdString2Data(QString strThird)
{
    int qualityLimitIdx = strThird.indexOf("Quality Limits:");
    if(qualityLimitIdx == -1)
        return;
    int startIdx = strThird.indexOf(":") + 1;
    strThird = strThird.mid(startIdx);

    int indexQuality = 0;
    int index = -1;
    index = strThird.indexOf("Time");
    if(index != -1)
    {
        m_mapQuality.insert(indexQuality, Utility::DINTimePl);
        indexQuality++;
    }
    else
        indexQuality++;

    index = strThird.indexOf("Power");
    if(index != -1)
    {
        m_mapQuality.insert(indexQuality, Utility::DINPowerPl);
        indexQuality++;
    }
    else
        indexQuality++;

    index = strThird.indexOf("Pre Height");
    if(index != -1)
    {
        m_mapQuality.insert(indexQuality, Utility::DINPre_HgtPl);
        indexQuality++;
    }
    else
        indexQuality++;

    index = strThird.indexOf("Post Height");
    if(index != -1)
    {
        m_mapQuality.insert(indexQuality, Utility::DINHeightPl);
        indexQuality++;
    }
    else
        indexQuality++;
}

void TouchScreen::Parse4thString2Data(QString strFourth)
{
    double doubleTemp;
    Utility *_Utility = Utility::GetInstance();
    int maximumIdx = strFourth.indexOf("Maximum:");
    if(maximumIdx == -1)
        return;
    int startIdx = strFourth.indexOf(":") + 1;
    strFourth = strFourth.mid(startIdx);
    QStringList list = strFourth.split("  ");
    QString strTemp = "";
    for(int i = 0; i < list.size(); i++)
    {
        strTemp = list[i];
        strTemp = strTemp.trimmed();
        if(strTemp != "")
        {
            list[i] = strTemp;
        }
        else
        {
            list.removeAt(i);
            i--;
        }
    }

    QMap<int, int>::const_iterator iterator = m_mapQuality.constBegin();
    while (iterator != m_mapQuality.constEnd())
    {
        strTemp = list[iterator.key()];
        doubleTemp = _Utility->String2FormatedData(static_cast<Utility::DATA_TYPE>(iterator.value()), strTemp);
        switch (iterator.value())
        {
        case Utility::DINTimePl:
            m_stWeldSetting.Time.Max = static_cast<unsigned short>(doubleTemp);
            break;
        case Utility::DINPowerPl:
            m_stWeldSetting.Power.Max = static_cast<unsigned short>(doubleTemp);
            break;
        case Utility::DINPre_HgtPl:
            m_stWeldSetting.Preheight.Max = static_cast<unsigned short>(doubleTemp);
            break;
        case Utility::DINHeightPl:
            m_stWeldSetting.PostHeight.Max = static_cast<unsigned short>(doubleTemp);
            break;
        default:
            break;
        }
        ++iterator;
    }
}

void TouchScreen::Parse5thString2Data(QString strFifth)
{
    double doubleTemp;
    Utility *_Utility = Utility::GetInstance();
    int maximumIdx = strFifth.indexOf("Minimum:");
    if(maximumIdx == -1)
        return;
    int startIdx = strFifth.indexOf(":") + 1;
    strFifth = strFifth.mid(startIdx);
    QStringList list = strFifth.split("  ");
    QString strTemp = "";
    for(int i = 0; i < list.size(); i++)
    {
        strTemp = list[i];
        strTemp = strTemp.trimmed();
        if(strTemp != "")
        {
            list[i] = strTemp;
        }
        else
        {
            list.removeAt(i);
            i--;
        }
    }

    QMap<int, int>::const_iterator iterator = m_mapQuality.constBegin();
    while (iterator != m_mapQuality.constEnd())
    {
        strTemp = list[iterator.key()];
        doubleTemp = _Utility->String2FormatedData(static_cast<Utility::DATA_TYPE>(iterator.value()), strTemp);
        switch (iterator.value())
        {
        case Utility::DINTimePl:
            m_stWeldSetting.Time.Min = static_cast<unsigned short>(doubleTemp);
            break;
        case Utility::DINPowerPl:
            m_stWeldSetting.Power.Min = static_cast<unsigned short>(doubleTemp);
            break;
        case Utility::DINPre_HgtPl:
            m_stWeldSetting.Preheight.Min = static_cast<unsigned short>(doubleTemp);
            break;
        case Utility::DINHeightPl:
            m_stWeldSetting.PostHeight.Min = static_cast<unsigned short>(doubleTemp);
            break;
        default:
            break;
        }
        ++iterator;
    }
}

void TouchScreen::Parse6thString2Data(QString strSixth)
{
    int indexWeldData = 0;
    if(strSixth.indexOf("PST") != -1)
    {
        m_mapWeldData.insert(indexWeldData, Utility::DINPresetNum);
        indexWeldData++;
    }
    else
    {
        indexWeldData++;
        return;
    }

    if(strSixth.indexOf("COUNT") != -1)
    {
        m_mapWeldData.insert(indexWeldData, Utility::DINCycleNum);
        indexWeldData++;
    }
    else
        indexWeldData++;

    if(strSixth.indexOf("ENER") != -1)
    {
        m_mapWeldData.insert(indexWeldData, Utility::DINEnergy);
        indexWeldData++;
    }
    else
        indexWeldData++;

    if(strSixth.indexOf("WDTH") != -1)
    {
        m_mapWeldData.insert(indexWeldData, Utility::DINWidth);
        indexWeldData++;
    }
    else
        indexWeldData++;

    if(strSixth.indexOf("T.PR") != -1)
    {
        m_mapWeldData.insert(indexWeldData, Utility::DINTriggerPressure);
        indexWeldData++;
    }
    else
        indexWeldData++;

    if(strSixth.indexOf("W.PR") != -1)
    {
        m_mapWeldData.insert(indexWeldData, Utility::DINPressure);
        indexWeldData++;
    }
    else
        indexWeldData++;

    if(strSixth.indexOf("AMP") != -1)
    {
        m_mapWeldData.insert(indexWeldData, Utility::DINAmplitude);
        indexWeldData++;
    }
    else
        indexWeldData++;

    if(strSixth.indexOf("TIME") != -1)
    {
        m_mapWeldData.insert(indexWeldData, Utility::DINActTime);
        indexWeldData++;
    }
    else
        indexWeldData++;

    if(strSixth.indexOf("PWR") != -1)
    {
        m_mapWeldData.insert(indexWeldData, Utility::DINActPower);
        indexWeldData++;
    }
    else
        indexWeldData++;

    if(strSixth.indexOf("PHGT") != -1)
    {
        m_mapWeldData.insert(indexWeldData, Utility::DINActPreHgt);
        indexWeldData++;
    }
    else
        indexWeldData++;

    if(strSixth.indexOf("HGHT") != -1)
    {
        m_mapWeldData.insert(indexWeldData, Utility::DINActHgt);
        indexWeldData++;
    }
    else
        indexWeldData++;

    if(strSixth.indexOf("ALRM") != -1)
    {
        m_mapWeldData.insert(indexWeldData, Utility::DINAlarmSign);
        indexWeldData++;
    }
    else
        indexWeldData++;
}

TouchScreen::TouchScreen()
{
    m_stWeldSetting.Time.Min = -1;
    m_stWeldSetting.Time.Max = -1;
    m_stWeldSetting.Power.Min = -1;
    m_stWeldSetting.Power.Max = -1;
    m_stWeldSetting.Preheight.Min = -1;
    m_stWeldSetting.Preheight.Max = -1;
    m_stWeldSetting.PostHeight.Min = -1;
    m_stWeldSetting.PostHeight.Max = -1;
}

int TouchScreen::ParseWeldResult(QString weldResult)
{
    QStringList listWeldResult = weldResult.split("\r\n");
    QString strTemp = "";
    for(int i = 0; i < listWeldResult.size(); i++)
    {
        strTemp = listWeldResult[i];
        strTemp = strTemp.trimmed();
        if(strTemp != "")
        {
            listWeldResult[i] = strTemp;
        }
        else
        {
            listWeldResult.removeAt(i);
            i--;
        }
    }

    if(listWeldResult.size() == 1)
    {
        if(listWeldResult[0] == "UUIA1")
            return OK;
        else
            ParseResultString2Data(listWeldResult[0]);
    }
    else
    {
        for(int i = 0; i < listWeldResult.size(); i++)
        {
            strTemp = listWeldResult[i];
            switch (i)
            {
            case 0:
                if(strTemp.indexOf("Part Name:", 0) != -1)
                {
                    m_mapQuality.clear();
                    m_mapWeldData.clear();
                    Parse1stString2Data(strTemp);
                }
                break;
            case 1:
                Parse2ndString2Data(strTemp);
                break;
            case 2:
                if(strTemp.indexOf("Quality Limits:", 0) != -1)
                    Parse3rdString2Data(strTemp);
                break;
            case 3:
                if(strTemp.indexOf("Maximum:", 0) != -1)
                    Parse4thString2Data(strTemp);
                break;
            case 4:
                if(strTemp.indexOf("Minimum:", 0) != -1)
                    Parse5thString2Data(strTemp);
                break;
            case 5:
                Parse6thString2Data(strTemp);
                break;
            case 6:
                ParseResultString2Data(strTemp);
                break;
            default:
                break;
            }
        }
    }
    return OK;
}
