#include "versagraphic.h"
#include "../utility/utility.h"
#include "../definition.h"
#include <QDebug>
int Versagraphic::ParseResultString2Data(const QString strData)
{
    double doubleTemp;
    Utility *_Utility = Utility::GetInstance();
    // M2010 *_ptrM2010 = M2010::Instance();

    QStringList list = strData.split("\t");
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

    if(list.size() == 0)
        return ERROR;
    bool iResult = false;
    QString(list[0]).toInt(&iResult);
    if(iResult == false)
        return ERROR;

    m_mapWeldData.clear();
    int indexWeldData = 0;
    m_mapWeldData.insert(indexWeldData, Utility::DINCycleNum);
    indexWeldData++;

    m_mapWeldData.insert(indexWeldData, Utility::DINDate);
    indexWeldData++;

    m_mapWeldData.insert(indexWeldData, Utility::DINTime);
    indexWeldData++;

    m_mapWeldData.insert(indexWeldData, Utility::DINPresetName);
    indexWeldData++;

    m_mapWeldData.insert(indexWeldData, Utility::DINEnergy);
    indexWeldData++;

    m_mapWeldData.insert(indexWeldData, Utility::DINTriggerPressure);
    indexWeldData++;

    m_mapWeldData.insert(indexWeldData, Utility::DINPressure);
    indexWeldData++;

    m_mapWeldData.insert(indexWeldData, Utility::DINAmplitude);
    indexWeldData++;

    m_mapWeldData.insert(indexWeldData, Utility::DINTimePl);
    indexWeldData++;

    m_mapWeldData.insert(indexWeldData, Utility::DINTimeMs);
    indexWeldData++;

    m_mapWeldData.insert(indexWeldData, Utility::DINPowerPl);
    indexWeldData++;

    m_mapWeldData.insert(indexWeldData, Utility::DINPowerMs);
    indexWeldData++;

    m_mapWeldData.insert(indexWeldData, Utility::DINPre_HgtPl);
    indexWeldData++;

    m_mapWeldData.insert(indexWeldData, Utility::DINPre_HgtMs);
    indexWeldData++;

    m_mapWeldData.insert(indexWeldData, Utility::DINHeightPl);
    indexWeldData++;

    m_mapWeldData.insert(indexWeldData, Utility::DINHeightMs);
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
    m_stWeldSetting.MODE_FLAGS.ModeWord = WELD_MODE::ENERGY_MODE;
    m_stWeldSetting.ABDelay = 0;
    m_stWeldSetting.ABDuration = 0;
    m_stWeldSetting.Width = 0;
    QMap<int, int>::const_iterator iter = m_mapWeldData.constBegin();
    while(iter != m_mapWeldData.constEnd())
    {
        if(iter.key() >= list.size())
            break;
        strTemp = list[iter.key()];
        switch(iter.value())
        {
        case Utility::DINCycleNum:
            m_stWeldResult.CycleCount = strTemp.toInt();
            break;
        case Utility::DINDate:
            qDebug()<<"Date: " << strTemp;
            break;
        case Utility::DINTime:
            qDebug()<<"Time: " << strTemp;
            break;
        case Utility::DINPresetName:
            m_stWeldSetting.PresetName = strTemp;
            break;
        case Utility::DINEnergy:
            doubleTemp = _Utility->String2FormatedData(static_cast<Utility::DATA_TYPE>(iter.value()), strTemp);
            m_stWeldResult.Energy = static_cast<int>(doubleTemp);
            m_stWeldSetting.Energy = static_cast<int>(doubleTemp);
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
        case Utility::DINTimePl:
            doubleTemp = _Utility->String2FormatedData(static_cast<Utility::DATA_TYPE>(iter.value()), strTemp);
            m_stWeldSetting.Time.Max = static_cast<int>(doubleTemp);
            break;
        case Utility::DINTimeMs:
            doubleTemp = _Utility->String2FormatedData(static_cast<Utility::DATA_TYPE>(iter.value()), strTemp);
            m_stWeldSetting.Time.Min = static_cast<int>(doubleTemp);
            break;
        case Utility::DINPowerPl:
            doubleTemp = _Utility->String2FormatedData(static_cast<Utility::DATA_TYPE>(iter.value()), strTemp);
            m_stWeldSetting.Power.Max = static_cast<int>(doubleTemp);
            break;
        case Utility::DINPowerMs:
            doubleTemp = _Utility->String2FormatedData(static_cast<Utility::DATA_TYPE>(iter.value()), strTemp);
            m_stWeldSetting.Power.Min = static_cast<int>(doubleTemp);
            break;
        case Utility::DINPre_HgtPl:
            doubleTemp = _Utility->String2FormatedData(static_cast<Utility::DATA_TYPE>(iter.value()), strTemp);
            m_stWeldSetting.Preheight.Max = static_cast<int>(doubleTemp);
            break;
        case Utility::DINPre_HgtMs:
            doubleTemp = _Utility->String2FormatedData(static_cast<Utility::DATA_TYPE>(iter.value()), strTemp);
            m_stWeldSetting.Preheight.Min = static_cast<int>(doubleTemp);
            break;
        case Utility::DINHeightPl:
            doubleTemp = _Utility->String2FormatedData(static_cast<Utility::DATA_TYPE>(iter.value()), strTemp);
            m_stWeldSetting.PostHeight.Max = static_cast<int>(doubleTemp);
            break;
        case Utility::DINHeightMs:
            doubleTemp = _Utility->String2FormatedData(static_cast<Utility::DATA_TYPE>(iter.value()), strTemp);
            m_stWeldSetting.PostHeight.Min = static_cast<int>(doubleTemp);
            break;
        case Utility::DINActTime:
            doubleTemp = _Utility->String2FormatedData(static_cast<Utility::DATA_TYPE>(iter.value()), strTemp);
            m_stWeldResult.Time = static_cast<int>(doubleTemp);
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
                if(m_stWeldResult.Time < m_stWeldSetting.Time.Min)
                    m_stWeldResult.AlarmFlag |= TIME_MIN_FAULT;
                if(m_stWeldResult.Time > m_stWeldSetting.Time.Max)
                    m_stWeldResult.AlarmFlag |= TIME_MAX_FAULT;
            }
            else if(strTemp == POWER_ALARM)
            {
                m_stWeldResult.AlarmFlag |= POWER_FAULT;
                if(m_stWeldResult.Power < m_stWeldSetting.Power.Min)
                    m_stWeldResult.AlarmFlag |= POWER_MIN_FAULT;
                if(m_stWeldResult.Power > m_stWeldSetting.Power.Max)
                    m_stWeldResult.AlarmFlag |= POWER_MAX_FAULT;
            }
            else if(strTemp == HEIGHT_ALARM)
            {
                m_stWeldResult.AlarmFlag |= HEIGHT_FAULT;
                if(m_stWeldResult.PostHeight < m_stWeldSetting.PostHeight.Min)
                    m_stWeldResult.AlarmFlag |= HEIGHT_MIN_FAULT;
                if(m_stWeldResult.PostHeight > m_stWeldSetting.PostHeight.Max)
                    m_stWeldResult.AlarmFlag |= HEIGHT_MAX_FAULT;
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
    return OK;
}

Versagraphic::Versagraphic() {}

int Versagraphic::ParseWeldResult(QString weldResult)
{
    int iResult = ERROR;
    QStringList listWeldResult = weldResult.split("\r\n");
    QString strTemp = "";
    for(int i = 0; i < listWeldResult.size(); i++)
    {
        strTemp = listWeldResult[i];
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

    if(listWeldResult.size() > 0)
    {
        iResult = ParseResultString2Data(listWeldResult[0]);
    }
    return iResult;
}
