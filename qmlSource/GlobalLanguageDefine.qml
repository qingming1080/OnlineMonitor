pragma Singleton //we indicate that this QML Type is a singleton
import QtQuick 2.12
import LanguageEnum 1.0
QtObject
{
    id: globalLanguageDefine
    
    // 通用消息
    readonly property string strExceptionMesssage:      qsTr("异常信息")
    readonly property string strEnterPassword:          qsTr("请输入操作员密码")
    readonly property string strOK:                     qsTr("确认")
    readonly property string strCancel:                 qsTr("取消")
    readonly property string strWrongPassword:          qsTr("密码错误请重新输入!")
    readonly property string strNewPassword:            qsTr("请输入新密码")
    readonly property string strSampleInsufficient:     qsTr("样本数不足请继续采样!")
    readonly property string strInputRangeError:        qsTr("输入范围错误请重新输入!")
    readonly property string strSystemConfigSuccess:    qsTr("系统配置成功!")
    readonly property string strLoading:                qsTr("载入中")
    readonly property string strRomveDevice:           qsTr("是否删除当前设备")
    
    // 异常信息相关
    readonly property string strSuspiciousAppeared:     qsTr("出现可疑品")
    readonly property string strDefectiveAppeared:      qsTr("出现次品")
    readonly property string strYieldDropToLimit:       qsTr("良率下降至下限值")
    readonly property string strFrequentDefective:      qsTr("频繁出现次品")
    readonly property string strFrequentSuspicious:     qsTr("频繁出现可疑品")
    readonly property string strAutoLearnExceedLimit:   qsTr("自动学习次数超过上限值")
    readonly property string strAutoLearnCompleted:     qsTr("自动学习已完成")
    readonly property string strModelCreationCompleted: qsTr("创建模型已完成")
    readonly property string strSetupComplete:          qsTr("配置成功已连接")
    
    // 参数配置相关
    readonly property string strMaxProductionLimit:     qsTr("最大生产批量上下限（2w-100w）")
    readonly property string strLearnSampleLimit:       qsTr("学习样本数上下限（10~20个）")
    readonly property string strYieldRateLimit:         qsTr("良率下限区间（90-99）")
    readonly property string strSetParameters:          qsTr("设置参数")
    
    // 语言相关
    readonly property string strSimplifiedChinese:      qsTr("简体中文")
    readonly property string strEnglish:                qsTr("English")
    readonly property string strOtherLanguage:          qsTr("其他语言")
    
    // 设备信息
    readonly property string strEquipmentInfo:          qsTr("设备信息")
    readonly property string strDeviceName:             qsTr("设备名称")
    readonly property string strDeviceModel:            qsTr("设备型号")
    readonly property string strConnectionMethod:       qsTr("连接方式")
    readonly property string strDeviceStatus:           qsTr("设备状态")
    readonly property string strAddDevice:              qsTr("新增设备")
    readonly property string strDeleteDevice:           qsTr("删除设备")
    readonly property string strCustomized:             qsTr("自定义")
    
    // 系统界面
    readonly property string strSystemName:             qsTr("ProvidenceEE")
    readonly property string strProductionInterface:    qsTr("生产界面")
    readonly property string strHistoryRecord:          qsTr("历史记录")
    readonly property string strSystemConfig:           qsTr("系统配置")
    readonly property string strSystemVersion:          qsTr("系统版本号")
    readonly property string strSystemMessage:          qsTr("系统消息")
    
    // 生产模块
    readonly property string strCreateModel:            qsTr("创建模型")
    readonly property string strNewModel:               qsTr("新建模型")
    readonly property string strClearData:              qsTr("清除数据")
    readonly property string strSelectAll:              qsTr("全选")
    readonly property string strSerialNumber:           qsTr("序号")
    readonly property string strWeldingTime:            qsTr("焊接时间")
    readonly property string strPower:                  qsTr("功率")
    readonly property string strEnergy:                 qsTr("能量")
    readonly property string strWeldPressure:           qsTr("焊接压力")
    readonly property string strTriggerPressure:        qsTr("触发压力")
    readonly property string strTimeUpper:              qsTr("时间上限")
    readonly property string strTimeLower:              qsTr("时间下限")
    readonly property string strPowerUpper:             qsTr("功率上限")
    readonly property string strPowerLower:             qsTr("功率下限")
    readonly property string strPreheightUpper:         qsTr("预焊上限")
    readonly property string strPreheightLower:         qsTr("预焊下限")
    readonly property string strPostHeightUpper:        qsTr("终焊上限")
    readonly property string strPostHeightLower:        qsTr("终焊下限")
    readonly property string strDate:                   qsTr("日期")
    readonly property string strTensile:                qsTr("拉力")
    readonly property string strResidual:               qsTr("残留度")
    readonly property string strTime:                   qsTr("时间")
    
    // 实时良率
    readonly property string strRealtimeYield:          qsTr("实时良率")
    readonly property string strQualified:              qsTr("合格")
    readonly property string strGood:                   qsTr("良品")
    readonly property string strSuspicious:             qsTr("可疑")
    readonly property string strDefective:              qsTr("次品")
    readonly property string strTotal:                  qsTr("总计")
    readonly property string strResult:                 qsTr("结果")
    
    // 焊接相关
    readonly property string strWeldingParameter:       qsTr("焊接参数")
    readonly property string strWeldingResult:          qsTr("焊接结果")
    readonly property string strWeldingTrend:           qsTr("焊接趋势")
    readonly property string strYieldTrend:             qsTr("良率趋势")
    readonly property string strAmplitude:              qsTr("振幅")
    readonly property string strPressure:               qsTr("压力")
    readonly property string strPreWeldHeight:          qsTr("焊前高度")
    readonly property string strPostWeldHeight:         qsTr("焊后高度")
    readonly property string strParameterSetting:       qsTr("参数设置")
    
    // 系统配置
    readonly property string strDeviceConfig:           qsTr("设备配置")
    readonly property string strMaxProduction:          qsTr("最大生产批量")
    readonly property string strLearningSamples:        qsTr("学习样本数")
    readonly property string strYieldLowerLimit:        qsTr("良率下限")
    readonly property string strPort:                   qsTr("端口")
    readonly property string strRemoteEnd:              qsTr("远程端")
    readonly property string strClient:                 qsTr("客户端")
    readonly property string strHeightMode:             qsTr("高度模式")
    readonly property string strStart:                  qsTr("启动")
    readonly property string strClose:                  qsTr("关闭")
    readonly property string strNetwork:                qsTr("网络")
    readonly property string strNetworkPort:            qsTr("网络端口")
    readonly property string strServerPort:             qsTr("服务器端口")
    readonly property string strDevice:                 qsTr("设备")
    readonly property string strAddress:                qsTr("地址")
    readonly property string strLocal:                  qsTr("本地")
    readonly property string strBaudRate:               qsTr("波特率")
    readonly property string strDataBits:               qsTr("数据位")
    readonly property string strParity:                 qsTr("奇偶校验位")
    readonly property string strStopBits:               qsTr("停止位")
    readonly property string strSystemSave:             qsTr("系统保存")
    readonly property string strDeviceSave:             qsTr("设备保存")
    readonly property string strChangePassword:         qsTr("修改密码")
    readonly property string strOpenPending:            qsTr("是否开启待定")
    readonly property string strPending:                qsTr("待定")
    readonly property string strAlarm:                  qsTr("报警")
    readonly property string strReset:                  qsTr("复位")
    
    // 系统参数配置
    readonly property string strSystemParamConfig:      qsTr("系统参数配置")
    readonly property string strSingleFactorCoeff:      qsTr("单因素系数")
    readonly property string strGeneralCoeff:           qsTr("通用系数")
    readonly property string strOtherCoeff:             qsTr("其他系数")
    readonly property string strAutoLearnLimit:         qsTr("自动学习上限")
    readonly property string strCustomerPasswordReset:  qsTr("客户密码重置")
    readonly property string strSave:                   qsTr("保存")
    readonly property string strInitialize:             qsTr("初始化")
    
    // 时间设置
    readonly property string strTimeSettings:           qsTr("设置时间")
    readonly property string strEnterCurrentTime:       qsTr("请输入当前时间")
    readonly property string strYear:                   qsTr("年")
    readonly property string strMonth:                  qsTr("月")
    readonly property string strDay:                    qsTr("日")
    readonly property string strHour:                   qsTr("时")
    readonly property string strMinute:                 qsTr("分")
    readonly property string strSecond:                 qsTr("秒")

    readonly property string strInvalidNumeric:         qsTr("所有字段必须是数字!")
    readonly property string strInvalidYear:            qsTr("无效的年份!")
    readonly property string strInvalidMonth:           qsTr("无效的月份!")
    readonly property string strInvalidDay:             qsTr("无效的日期!")
    readonly property string strInvalidLeapYear:        qsTr("无效的日期：该年份不是闰年!")
    readonly property string strInvalidDate:            qsTr("无效的时间!")
    
    // 时间单位
    readonly property string strHour_Unit:              qsTr("小时")
    readonly property string strHours_Unit:             qsTr("小时")
    readonly property string strDay_Unit:               qsTr("天")
    readonly property string strDays_Unit:              qsTr("天")

    //连接状态
    readonly property string strConnectFailed:          qsTr("连接失败")
    readonly property string strDisconnected:           qsTr("未连接")
    readonly property string strConnecting:             qsTr("连接中")
    readonly property string strConnected:              qsTr("已连接")

    //Week
    readonly property string strSunday:                 qsTr("星期日")
    readonly property string strMonday:                 qsTr("星期一")
    readonly property string strTuesday:                qsTr("星期二")
    readonly property string strWednesday:              qsTr("星期三")
    readonly property string strThursday:               qsTr("星期四")
    readonly property string strFriday:                 qsTr("星期五")
    readonly property string strSaturday:               qsTr("星期六")

    //preset Unit

    readonly property string strEnergyUnit:             qsTr("J")
    readonly property string strAmplitudeUnit:          qsTr("μm")
    readonly property string strPressureUnit:           qsTr("Psi")
    readonly property string strPowerUnit:              qsTr("W")
    readonly property string strHeightUnit:             qsTr("mm")
    readonly property string strWeldTimeUnit:           qsTr("S")

}
