#include "common.h"
#include "../definition.h"
constexpr char Common::NONE_ALARM[2]; //NO ALARM
constexpr char Common::OVERLOAD_ALARM[2]; //Overlaod Alarm
constexpr char Common::TIME_ALARM[2]; //Time limit Alarm
constexpr char Common::POWER_ALARM[2]; //Power limit Alarm
constexpr char Common::HEIGHT_ALARM[2]; //Height limit Alarm
Common::Common() {}

Common::~Common()
{

}

int Common::SetWeldSetting(const WELD_SETTING *_setting)
{
    if(_setting == nullptr)
        return ERROR;
    m_stWeldSetting.Energy = _setting->Energy;
    m_stWeldSetting.Amplitude = _setting->Amplitude;
    m_stWeldSetting.TPressure = _setting->TPressure;
    m_stWeldSetting.WPressure = _setting->WPressure;
    m_stWeldSetting.Time.Min = _setting->Time.Min;
    m_stWeldSetting.Time.Max = _setting->Time.Max;
    m_stWeldSetting.Power.Min = _setting->Power.Min;
    m_stWeldSetting.Power.Max = _setting->Power.Max;
    m_stWeldSetting.Preheight.Min = _setting->Preheight.Min;
    m_stWeldSetting.Preheight.Max = _setting->Preheight.Max;
    m_stWeldSetting.PostHeight.Min = _setting->PostHeight.Min;
    m_stWeldSetting.PostHeight.Max = _setting->PostHeight.Max;
    m_stWeldSetting.MODE_FLAGS.ModeFlags.WeldMode = _setting->MODE_FLAGS.ModeFlags.WeldMode;
    return OK;
}

void Common::GetWeldSetting(WELD_SETTING *_setting) const
{
    if(_setting == nullptr)
        return;
    _setting->Energy = m_stWeldSetting.Energy;
    _setting->Amplitude = m_stWeldSetting.Amplitude;
    _setting->TPressure = m_stWeldSetting.TPressure;
    _setting->WPressure = m_stWeldSetting.WPressure;
    _setting->Time.Min = m_stWeldSetting.Time.Min;
    _setting->Time.Max = m_stWeldSetting.Time.Max;
    _setting->Power.Min = m_stWeldSetting.Power.Min;
    _setting->Power.Max = m_stWeldSetting.Power.Max;
    _setting->Preheight.Min = m_stWeldSetting.Preheight.Min;
    _setting->Preheight.Max = m_stWeldSetting.Preheight.Max;
    _setting->PostHeight.Min = m_stWeldSetting.PostHeight.Min;
    _setting->PostHeight.Max = m_stWeldSetting.PostHeight.Max;
    _setting->MODE_FLAGS.ModeFlags.WeldMode = m_stWeldSetting.MODE_FLAGS.ModeFlags.WeldMode;
}

void Common::GetWeldResult(WELD_RESULT *_result) const
{
    if(_result == nullptr)
        return;
    _result->CycleCount = m_stWeldResult.CycleCount;
    _result->Energy = m_stWeldResult.Energy;
    _result->Width = m_stWeldResult.Width;
    _result->Time = m_stWeldResult.Time;
    _result->Power = m_stWeldResult.Power;
    _result->Preheight = m_stWeldResult.Preheight;
    _result->Amplitude = m_stWeldResult.Amplitude;
    _result->PostHeight = m_stWeldResult.PostHeight;
    _result->Amplitude2 = m_stWeldResult.Amplitude2;
    _result->PPHeight = m_stWeldResult.PPHeight;
    _result->WPressure = m_stWeldResult.WPressure;
    _result->TPressure = m_stWeldResult.TPressure;
    _result->AlarmFlag = m_stWeldResult.AlarmFlag;
}
