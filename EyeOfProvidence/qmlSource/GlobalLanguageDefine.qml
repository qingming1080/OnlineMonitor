pragma Singleton //we indicate that this QML Type is a singleton
import QtQuick      2.12
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
    readonly property string strRomveDevice:            qsTr("是否删除当前设备")

    //NumberKeyBoard
    readonly property string strKeyBoardMinimun:        qsTr("最小值")
    readonly property string strKeyBoardMaximum:        qsTr("最大值")
    readonly property string strKeyBoardDone:           qsTr("确认")
    readonly property string strKeyBoardCancel:         qsTr("返回")
    readonly property string strKeyBoardClr:            qsTr("清除")
    
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
    readonly property string strAutomaticLearningLimit: qsTr("自动学习上限")
    readonly property string strResidualThreshold:      qsTr("残留度阈值")
    readonly property string strPeelForceThreshold:     qsTr("撕拉力阈值")
    
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
    readonly property string strSystemTimeout:          qsTr("系统连接超时")
    readonly property string strContactInfo:            qsTr("灏博工业科技（西安）有限公司\n联系电话：029-84499505")
    readonly property string strcontactSupport:         qsTr("请联系技术支持")
    readonly property string strSystemAdmin:            qsTr("系统管理")

    // 生产模块
    readonly property string strCreateModel:            qsTr("创建模型")
    readonly property string strNewModel:               qsTr("新建模型")
    readonly property string strClearData:              qsTr("清除数据")
    readonly property string strAddRecord:              qsTr("添加记录")
    readonly property string strSelectAll:              qsTr("全选")
    readonly property string strCycleCount:             qsTr("循环计数")
    readonly property string strWeldingTime:            qsTr("焊接时间")
    readonly property string strPower:                  qsTr("功率")
    readonly property string strEnergy:                 qsTr("能量")
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
    readonly property string strWeldPressure:           qsTr("焊接压力")
    readonly property string strTriggerPressure:        qsTr("触发压力")
    readonly property string strPreWeldHeight:          qsTr("焊前高度")
    readonly property string strShortPreheight:         qsTr("预高")
    readonly property string strPostWeldHeight:         qsTr("焊后高度")
    readonly property string strShortPostHeight:        qsTr("终高")
    readonly property string strParameterSetting:       qsTr("参数设置")
    readonly property string strAbsoluteDistance:       qsTr("绝对距离")
    readonly property string strCollapseDistance:       qsTr("相对距离")
    
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
    readonly property string strOpenPending:            qsTr("待定模式")
    readonly property string strPending:                qsTr("待定")
    readonly property string strAlarm:                  qsTr("报警")
    readonly property string strReset:                  qsTr("复位")
    readonly property string strRefresh:                qsTr("刷新")
    readonly property string strSample:                 qsTr("采样")
    
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

    //Month
    readonly property string strJanuary:                qsTr("一月")
    readonly property string strFebruary:               qsTr("二月")
    readonly property string strMarch:                  qsTr("三月")
    readonly property string strApril:                  qsTr("四月")
    readonly property string strMay:                    qsTr("五月")
    readonly property string strJune:                   qsTr("六月")
    readonly property string strJuly:                   qsTr("七月")
    readonly property string strAugust:                 qsTr("八月")
    readonly property string strSeptember:              qsTr("九月")
    readonly property string strOctober:                qsTr("十月")
    readonly property string strNovember:               qsTr("十一月")
    readonly property string strDecember:               qsTr("十二月")


    readonly property string strNotification:           qsTr("提示")
    readonly property string strSetSystemTimeSucess:    qsTr("系统时间设置成功已生效！")


    //ValidMessage
    readonly property string strInputInterger:          qsTr("请输入整数！")
    readonly property string strInputFloat:             qsTr("请输入浮点数xx.xx!")
    readonly property string strEnter0And65535:         qsTr("请输入0~65535之间的数！")
    readonly property string strEnterValidIPAddress:    qsTr("请输入正确的IP地址！")
    readonly property string strDeviceNameRule:         qsTr("设备名称只能包含中文、字母、数字（1~8字符）！")
    readonly property string strEnterValidYear:         qsTr("请输入有效年份！")
    readonly property string strMonthRange:             qsTr("月份必须是1~12之间的整数！")
    readonly property string strEnterValidDay:          qsTr("请输入正确的日期（1~31）！")
    readonly property string strEnterValidHour:         qsTr("请输入正确的小时（0~23）！")
    readonly property string strEnterValidMinute:       qsTr("请输入正确的分钟（0~59）！")
    readonly property string strEnterValidSecond:       qsTr("请输入正确的秒数（0~59）！")

    //export
    readonly property string strExportButton:           qsTr("数据导出")
    readonly property string strNoUSB:                  qsTr("未插入U盘")
    readonly property string strUSBConnected:           qsTr("U盘已插入")
    readonly property string strExportIsOk:             qsTr("导出数据已完成!")
    readonly property string strExportFailed:           qsTr("没有找到可以使用的U盘或尝试再次导出")

    readonly property string strSystemSWUpgrade:        qsTr("系统软件升级")
    readonly property string strAvailableVersions:      qsTr("可用软件版本")
    readonly property string strSystemLicense:          qsTr("系统许可证导入")
    readonly property string strSystemSN:               qsTr("系统序列号")
    readonly property string strExpiredDays:            qsTr("剩余天数")
    readonly property string strReadUSB:                qsTr("读U盘")
    readonly property string strSoftwareUpgrade:        qsTr("软件升级")
    readonly property string strLoadLicense:            qsTr("导入许可证")

    enum EnumKeyboard{
        Delete,
        Clear,
        Login,
        FaceLogin,
        PasswordLogin
    }

    function numberToString(decimals_num, realValue)
    {
        var strValue = realValue.toFixed(decimals_num)
        return strValue
    }

    function decimalsNumber(decimals_num, text_input, suffix)
    {
        if(suffix === "IPV4" || suffix === "IPV6")
        {
            text_input.maximumLength = 15;
            return text_input.text;
        }
        var contrast = text_input.text
        /*Number of decimal points*/
        var num = contrast.split('.').length - 1
        if(num === 1)
            var position = contrast.indexOf(".");

        if(decimals_num === 0)
        {
            text_input.maximumLength = 8
            if(num >= 1)
            {
                /*Limit when the number of decimal points is greater than 1*/
                text_input.remove(text_input.cursorPosition - 1, text_input.cursorPosition)
            }
        }
        else
        {
            /*Limit total length*/
            if(position + 1 + decimals_num <= 8)
            {
                /*The number of digits before the decimal point
                  plus the number of digits after the decimal point is
                  the total length of the restriction*/
                text_input.maximumLength = position + 1 + decimals_num
            }
            else
                text_input.maximumLength = 8
        }
        return text_input.text
    }

    function handleWithDigitalKeyInput(data, text_input, suffix)
    {
        Qt.inputMethod.hide()
        if(data === GlobalLanguageDefine.EnumKeyboard.Clear)
            text_input.remove(0, text_input.cursorPosition)
        else if(data === GlobalLanguageDefine.EnumKeyboard.Delete)
        {
            if(text_input.isSelectedAll === true)
                text_input.remove(0, text_input.cursorPosition)
            else
                text_input.remove(text_input.cursorPosition - 1, text_input.cursorPosition)
        }
        else
        {
            var strInputText = text_input.text
            if(text_input.isSelectedAll === true)
                strInputText = data
            else
                strInputText += data
            if(GlobalLanguageDefine.isValidData(strInputText, suffix) === true)
            {
                text_input.text = strInputText
            }
        }
        text_input.isSelectedAll = false
    }

    function isValidData(strInputText, strUnit)
    {
        var validator = /^\d{0,6}?$/
        var bResult = false
        if(strUnit.toUpperCase() === "S")
        {
            validator = /^\d{0,6}(\.\d{0,3})?$/
        }
        else if(strUnit.toUpperCase() === "%")
        {
            validator = /^\d{0,3}?$/
        }
        else if(strUnit.toUpperCase() === "W")
        {
            validator = /^\d{0,4}?$/
        }
        else if(strUnit.toUpperCase() === "MM" || strUnit.toUpperCase() === "MM/S2" || strUnit.toUpperCase() === "MM/S")
        {
            validator = /^\d{0,3}(\.\d{0,2})?$/
        }
        else if(strUnit.toUpperCase() === "IN" || strUnit.toUpperCase() === "IN/S2" || strUnit.toUpperCase() === "IN/S")
        {
            validator = /^\d{0,2}(\.\d{0,4})?$/
        }
        else if(strUnit.toUpperCase() === "IPV4" || strUnit.toUpperCase() === "IPV6")
        {
            return true
        }
        else
        {
            validator = /^\d{0,7}(\.\d{0,2})?$/
        }

        if (validator.test(strInputText))
        {
            bResult = true
        }
        else
        {
            bResult = false
        }
        return bResult
    }
}
