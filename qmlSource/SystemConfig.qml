import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.5
import Device 1.0
import DeviceObj            1.0
import QmlEnum 1.0
import GlobalLanguageDefine 1.0
import GlobalSystemDefine   1.0
import GlobalMessageDefine  1.0
import LanguageEnum         1.0
import DeviceInfoEnum       1.0

//系统配置
Rectangle {
    id: layoutSystemConfig
    property var sysViews: []
    Component.onCompleted: {
        loadViewsys(1, syscfg)
    }

    color: pRgb(153, 204, 255)

    signal sigAddDevice()

    function loadViewsys(viewName, component)
    {
        loader1.pop()
        if (sysViews[viewName]) {
            // 如果视图已缓存，直接显示
            loader1.push(sysViews[viewName]);
        } else {
            // 创建视图并缓存
            var newItem = component.createObject(loader1);
            sysViews[viewName] = newItem;
            loader1.push(newItem);
        }
    }

    Connections{
        target: window
        function onSigSysConfig(){
            Qt.callLater(configCheck)
        }
    }

    function configCheck(){
        if(DeviceManager.DeviceCounter === 0)
        {
            loadViewsys(1, syscfg)
        }
        else
        {
            loadViewsys(2, musys)
        }
    }

    StackView{
        id:loader1
        //禁用动画
        pushEnter: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 0
                to:1
                duration: 0
            }
        }

        // 退出项的动画过渡
        pushExit: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 1
                to:0
                duration: 0
            }
        }

        // 退出进入项的动画过渡
        popEnter: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 0
                to:1
                duration: 0
            }
        }

        // 退出进入项的动画过渡
        popExit: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 1
                to:0
                duration: 0
            }
        }
    }

    Component{
        id: syscfg
        Item {
            Connections{
                target: layoutSystemConfig
                function onSigAddDevice()
                {
                    DeviceManager.addDevice()
                }
            }

            Rectangle{
                x:30
                y:25
                width: 463
                height: 613
                color: pRgb(43, 112, 173)
                radius: 3
                Text {
                    id: name
                    // text: qsTr("设备配置")
                    text: GlobalLanguageDefine.strDeviceConfig
                    color: pRgb(153, 204, 255)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    font.pixelSize: 20
                    x:33
                    y:16
                }
                Rectangle{
                    y:46
                    width: 126
                    height: 1
                    color: pRgb(174, 210, 216)
                }
                Text {
                    id: titleMaxProduction
                    x:35
                    y:75
                    // text: qsTr("最大生产批量")
                    text: GlobalLanguageDefine.strMaxProduction + ": "
                    color: pRgb(177, 213, 219)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    font.pixelSize: 18
                }
                TextField{
                    id: maxProductionTextField
                    width: 180
                    height: 40
                    anchors.top: parent.top
                    anchors.topMargin: 66
                    anchors.left: titleMaxProduction.right
                    anchors.leftMargin: 37
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    color: pRgb(43, 112, 173)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    font.pixelSize: 18
                    maximumLength: 7
                    inputMethodHints: Qt.ImhDigitsOnly
                    background: Rectangle{
                        radius: 6
                        border.width: 3
                        border.color: "#99ccff"
                    }
                    text: {
                        if(DeviceManager.SelectedDeviceIndex === -1)
                            return ""
                        else
                            DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.ProductionMaxBacth
                    }
                    MouseArea {
                        anchors.fill: parent
                        onPressed: {
                            maxProductionTextField.forceActiveFocus()
                            keyboardType = 0
                        }
                    }
                    onEditingFinished: {
                        var maxProductionRegex = /^(?:[2-9]\d{4}|[1-9]\d{5}|1000000)$/
                        if (!maxProductionRegex.test(maxProductionTextField.text))
                        {
                            footer.showError(titleMaxProduction.text + GlobalLanguageDefine.strMaxProductionLimit)
                        }
                        else
                        {
                            footer.hideError()
                            console.debug("111111111111111111: ", titleMaxProduction.text)
                            DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.ProductionMaxBacth = titleMaxProduction.text
                        }
                    }
                }

                Text {
                    id: titleLearningSamples
                    // text: qsTr("学习样本数")
                    text: GlobalLanguageDefine.strLearningSamples + ": "
                    color: pRgb(177, 213, 219)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    font.pixelSize: 18
                    anchors.left: titleMaxProduction.left
                    anchors.top: titleMaxProduction.bottom
                    anchors.topMargin: 41
                }
                TextField{
                    id: learningSamplesTextField
                    width: 180
                    height: 40
                    anchors.top: maxProductionTextField.bottom
                    anchors.topMargin: 30
                    anchors.left: maxProductionTextField.left
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    color: pRgb(43, 112, 173)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    font.pixelSize: 18
                     maximumLength: 2
                    inputMethodHints: Qt.ImhDigitsOnly
                    background: Rectangle{
                        radius: 6
                        border.width: 3
                        border.color: "#99ccff"
                    }
                    MouseArea {
                        anchors.fill: parent
                        onPressed: {
                            learningSamplesTextField.forceActiveFocus()
                            keyboardType = 0
                        }
                    }
                    text:{
                        var index = DeviceManager.SelectedDeviceIndex
                        if(index === -1)
                            return ""
                        else
                            DeviceManager.DeviceList[index].DeviceObj.MaxModelSamples
                    }
                    onEditingFinished: {
                        var learningSamplesRegex = /^(1[0-9]|20)$/
                        if (!learningSamplesRegex.test(learningSamplesTextField.text))
                            footer.showError(titleLearningSamples.text + GlobalLanguageDefine.strLearnSampleLimit)
                        else
                        {
                            footer.hideError()
                            DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.MaxModelSamples = learningSamplesTextField.text
                        }
                    }
                }
                Text {
                    id: titleYieldLowerLimit
                    // text: qsTr("良率下限")
                    text: GlobalLanguageDefine.strYieldLowerLimit + ": "
                    color: pRgb(177, 213, 219)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    font.pixelSize: 18
                    anchors.left: titleLearningSamples.left
                    anchors.top: titleLearningSamples.bottom
                    anchors.topMargin: 45
                }
                TextField{
                    id: yieldLowerLimitTextField
                    width: 180
                    height: 40
                    anchors.top: learningSamplesTextField.bottom
                    anchors.topMargin: 30
                    anchors.left: learningSamplesTextField.left
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    color: pRgb(43, 112, 173)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    font.pixelSize: 18
                    inputMethodHints: Qt.ImhDigitsOnly
                    maximumLength: 2
                    property int tmpIndex: DeviceManager.SelectedDeviceIndex
                    background: Rectangle{
                        radius: 6
                        border.width: 3
                        border.color: "#99ccff"
                    }
                    MouseArea {
                        anchors.fill: parent
                        onPressed: {
                            yieldLowerLimitTextField.forceActiveFocus()
                            keyboardType = 0
                        }
                    }
                    text:{
                        if(tmpIndex === -1)
                            return ""
                        else
                            DeviceManager.DeviceList[tmpIndex].DeviceObj.YieldRateLowerLimit

                    }
                    onEditingFinished: {
                        var yieldLowerLimitRegex = /^[1-9][0-9]$/
                        if (!yieldLowerLimitRegex.test(yieldLowerLimitTextField.text))
                            footer.showError(titleYieldLowerLimit.text + GlobalLanguageDefine.strInputInterger)
                        else
                        {
                            footer.hideError()
                            DeviceManager.DeviceList[tmpIndex].DeviceObj.YieldRateLowerLimit = yieldLowerLimitTextField.text
                        }
                    }
                }

                Text {
                    id: s7
                    text: GlobalLanguageDefine.strAutomaticLearningLimit + ": "
                    color: pRgb(177, 213, 219)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    font.pixelSize: 18
                    anchors.left: titleYieldLowerLimit.left
                    anchors.top: titleYieldLowerLimit.bottom
                    anchors.topMargin: 45
                }
                TextField{
                    id:t7
                    width: 180
                    height: 40
                    anchors.top: yieldLowerLimitTextField.bottom
                    anchors.topMargin: 30
                    anchors.left: yieldLowerLimitTextField.left
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    color: pRgb(43, 112, 173)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    font.pixelSize: 18
                    inputMethodHints: Qt.ImhDigitsOnly
                    maximumLength: 5
                    property int tmpIndex: DeviceManager.SelectedDeviceIndex
                    background: Rectangle{
                        radius: 6
                        border.width: 3
                        border.color: "#99ccff"
                    }
                    MouseArea {
                        anchors.fill: parent
                        onPressed: {
                            t7.forceActiveFocus()
                            keyboardType = 0
                        }
                    }
                    text:{
                        if(tmpIndex === -1)
                            return ""
                        else
                            return DeviceManager.DeviceList[tmpIndex].DeviceObj.AutoLearningCount
                    }

                    onEditingFinished: {
                        var portRegex = /^([0-9]|[1-9][0-9]{1,4}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])$/
                        if (!portRegex.test(t7.text))
                            footer.showError(s7.text + GlobalLanguageDefine.strEnter0And65535)
                        else
                        {
                            footer.hideError()
                            DeviceManager.DeviceList[tmpIndex].DeviceObj.AutoLearningCount = t7.text
                        }
                    }
                }

                Text {
                    id: s8
                    text: GlobalLanguageDefine.strResidualThreshold + ": "
                    color: pRgb(177, 213, 219)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    font.pixelSize: 18
                    anchors.left: s7.left
                    anchors.top: t8.top
                    anchors.topMargin: 10
                }
                TextField{
                    id:t8
                    width: 180
                    height: 40
                    anchors.top: t7.bottom
                    anchors.topMargin: 30
                    anchors.left: t7.left
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    color: pRgb(43, 112, 173)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    font.pixelSize: 18
                    inputMethodHints: Qt.ImhDigitsOnly
                    background: Rectangle{
                        radius: 6
                        border.width: 3
                        border.color: "#99ccff"
                    }
                    MouseArea {
                        anchors.fill: parent
                        onPressed: {
                            t8.forceActiveFocus()
                            keyboardType = 0
                        }
                    }
                    property int tmpIndex: DeviceManager.SelectedDeviceIndex
                    text:{
                        if(tmpIndex === -1)
                            return ""
                        else
                            DeviceManager.DeviceList[tmpIndex].DeviceObj.ResidualThreshold
                    }
                    onEditingFinished: {
                        var ipRegex = /^(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)(\.(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)){3}$/
                        if (!ipRegex.test(t8.text))
                            footer.showError(s8.text + GlobalLanguageDefine.strEnterValidIPAddress)
                        else
                        {
                            footer.hideError()
                            DeviceManager.DeviceList[tmpIndex].DeviceObj.ResidualThreshold = s8.text
                        }
                    }
                }


                Text {
                    id: titlePeelForceThreshold
                    text: GlobalLanguageDefine.strPeelForceThreshold + ": "
                    color: pRgb(177, 213, 219)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    font.pixelSize: 18
                    anchors.left: s8.left
                    anchors.top: peelForceThresholdField.top
                    anchors.topMargin: 10
                }
                TextField{
                    id: peelForceThresholdField
                    width: 180
                    height: 40
                    anchors.top: t8.bottom
                    anchors.topMargin: 30
                    anchors.left: t8.left
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    color: pRgb(43, 112, 173)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    font.pixelSize: 18
                    inputMethodHints: Qt.ImhDigitsOnly
                    background: Rectangle{
                        radius: 6
                        border.width: 3
                        border.color: "#99ccff"
                    }
                    MouseArea {
                        anchors.fill: parent
                        onPressed: {
                            peelForceThresholdField.forceActiveFocus()
                            keyboardType = 0
                        }
                    }
                    property int tmpIndex: DeviceManager.SelectedDeviceIndex
                    text:{
                        if(tmpIndex === -1)
                            return ""
                        else
                            return DeviceManager.DeviceList[tmpIndex].DeviceObj.ForceThreshold
                    }
                    onEditingFinished: {
                        var portRegex = /^(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)(\.(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)){3}$/
                        if (!portRegex.test(peelForceThresholdField.text))
                            footer.showError(titlePeelForceThreshold.text + GlobalLanguageDefine.strEnterValidIPAddress)
                        else
                        {
                            footer.hideError()
                            DeviceManager.DeviceList[tmpIndex].DeviceObj.ForceThreshold = peelForceThresholdField.text
                        }
                    }
                }


                Text {
                    id: titleHeightMode
                    // text: qsTr("高度模式")
                    text: GlobalLanguageDefine.strHeightMode + ": "
                    color: pRgb(177, 213, 219)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    font.pixelSize: 18
                    anchors.left: titlePeelForceThreshold.left
                    anchors.top: titlePeelForceThreshold.top
                    anchors.topMargin: 80
                }
                Text {
                    id: s5
                    // text: qsTr("启动")
                    text: GlobalLanguageDefine.strStart + ": "
                    color: pRgb(177, 213, 219)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    font.pixelSize: 18
                    anchors.verticalCenter: titleHeightMode.verticalCenter
                    anchors.left: peelForceThresholdField.left

                }
                RadioButton{
                    id: bt1
                    width: 34
                    height: 34
                    anchors.left: s5.right
                    anchors.verticalCenter: titleHeightMode.verticalCenter
                    anchors.leftMargin: 10
                    checked: DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.HeightEncoderOption
                    indicator: Rectangle
                    {
                        width: 34
                        height: 34
                        radius: 17
                        color: DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.HeightEncoderOption ? "#0d988c" : pRgb(232, 232, 232)
                        border.color: "#b1d5db"
                        border.width: 2
                    }
                    onPressed: {
                        DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.HeightEncoderOption = true
                    }
                }
                Text {
                    id: s6
                    // text: qsTr("关闭")
                    text: GlobalLanguageDefine.strClose + ": "
                    color: pRgb(177, 213, 219)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    font.pixelSize: 18
                    anchors.top: s5.top
                    anchors.left: s5.right
                    anchors.leftMargin: 55
                }
                RadioButton{
                    id:bt2
                    width: 34
                    height: 34
                    anchors.left: bt1.right
                    anchors.top: bt1.top
                    anchors.leftMargin: 65
                    checked: !DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.HeightEncoderOption
                    indicator: Rectangle
                    {
                        width: 34
                        height: 34
                        radius: 17
                        color: !DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.HeightEncoderOption ? "#0d988c" : pRgb(232, 232, 232)
                        border.color: "#b1d5db"
                        border.width: 2
                    }
                    onPressed: {
                        DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.HeightEncoderOption = false
                    }
                }

                Text {
                    id: titleOpenPendingOption
                    text: GlobalLanguageDefine.strOpenPending + ": "
                    color: pRgb(177, 213, 219)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    font.pixelSize: 18
                    anchors.left: titleHeightMode.left
                    anchors.top: titleHeightMode.top
                    anchors.topMargin: 70
                }
                Text {
                    id: openPendingStatrtext
                    text: GlobalLanguageDefine.strStart + ": "
                    color: pRgb(177, 213, 219)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    font.pixelSize: 18
                    anchors.verticalCenter: titleOpenPendingOption.verticalCenter
                    anchors.left: peelForceThresholdField.left

                }
                RadioButton{
                    id: openPeningStartButton
                    width: 34
                    height: 34
                    anchors.left: s5.right
                    anchors.verticalCenter: titleOpenPendingOption.verticalCenter
                    anchors.leftMargin: 10
                    checked: DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.SuspiciousOption
                    indicator: Rectangle
                    {
                        width: 34
                        height: 34
                        radius: 17
                        color: DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.SuspiciousOption ? "#0d988c" : pRgb(232, 232, 232)
                        border.color: "#b1d5db"
                        border.width: 2
                    }
                    onPressed: {
                        DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.SuspiciousOption = true
                    }
                }
                Text {
                    id: openPendingClosetext
                    // text: qsTr("关闭")
                    text: GlobalLanguageDefine.strClose + ": "
                    color: pRgb(177, 213, 219)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    font.pixelSize: 18
                    anchors.top: openPendingStatrtext.top
                    anchors.left: s5.right
                    anchors.leftMargin: 55
                }
                RadioButton{
                    id: peningCloseButton
                    width: 34
                    height: 34
                    anchors.left: openPeningStartButton.right
                    anchors.top: openPeningStartButton.top
                    anchors.leftMargin: 65
                    checked: !DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.SuspiciousOption
                    indicator: Rectangle
                    {
                        width: 34
                        height: 34
                        radius: 17
                        color: !DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.SuspiciousOption ? "#0d988c" : pRgb(232, 232, 232)
                        border.color: "#b1d5db"
                        border.width: 2
                    }
                    onPressed: {
                        DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.SuspiciousOption = false
                    }
                }
            }
            Rectangle{
                x:515
                y:25
                width: 753
                height: 613
                color: pRgb(43, 112, 173)
                radius: 3
                Text {
                    id: s14
                    x:23
                    y:74
                    // text: qsTr("设备名称")
                    text: GlobalLanguageDefine.strDeviceName + ": "
                    color: pRgb(177, 213, 219)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    font.pixelSize: 18
                }
                TextField{
                    id:t4
                    width: 180
                    height: 40
                    anchors.top: parent.top
                    anchors.topMargin: 66
                    anchors.left: s14.right
                    anchors.leftMargin: 23
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    color: pRgb(43, 112, 173)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    font.pixelSize: 18
                    maximumLength: 8
                    background: Rectangle{
                        radius: 6
                        border.width: 3
                        border.color: "#99ccff"
                    }
                    MouseArea {
                        anchors.fill: parent
                        onPressed: {
                            t4.forceActiveFocus()
                            keyboardType = 1
                        }
                    }
                    property int tmpIndex: DeviceManager.SelectedDeviceIndex
                    text:{
                        if(tmpIndex === -1)
                            return ""
                        else
                            return DeviceManager.DeviceList[tmpIndex].DeviceObj.WelderName
                    }
                    onEditingFinished: {
                        var nameRegex = /^[\u4e00-\u9fa5A-Za-z0-9]+$/
                        if (!nameRegex.test(t4.text))
                            footer.showError(s14.text + GlobalLanguageDefine.strDeviceNameRule)
                        else
                        {
                            footer.hideError()
                            DeviceManager.DeviceList[tmpIndex].DeviceObj.WelderName = t4.text
                        }
                    }
                }
                Text {
                    id: s15
                    // text: qsTr("设备型号")
                    text: GlobalLanguageDefine.strDeviceModel + ": "
                    color: pRgb(177, 213, 219)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    font.pixelSize: 18
                    anchors.top: s14.top
                    anchors.left: s14.right
                    anchors.leftMargin: 273
                }
                CustomComboBox{
                    id:com1
                    width: 180
                    height: 40
                    anchors.top: parent.top
                    anchors.topMargin: 66
                    anchors.left: s15.right
                    anchors.leftMargin: 23
                    model: WelderTypeModel
                    property int tmpIndex: DeviceManager.SelectedDeviceIndex
                    currentIndex: DeviceManager.DeviceList[tmpIndex].DeviceObj.WelderType
                    onAccepted: {
                        DeviceManager.DeviceList[tmpIndex].DeviceObj.WelderType = currentIndex
                    }
                }

                Switch{
                    id:ctl1
                    x:228
                    y:147
                    property int tmpIndex: DeviceManager.SelectedDeviceIndex
                    onPressed: {
                        if(ctl1.checked)
                            DeviceManager.DeviceList[tmpIndex].DeviceObj.ConnectType = DeviceInfoEnum.TCP_IP
                        else
                            DeviceManager.DeviceList[tmpIndex].DeviceObj.ConnectType = DeviceInfoEnum.RS232
                    }
                    indicator: Rectangle{
                        id:indicator1
                        implicitWidth: 339
                        implicitHeight:40
                        x:ctl1.leftPadding
                        y:parent.height / 2 - height / 2
                        border.width: 3
                        radius: 20
                        color: pRgb(232, 232, 232)
                        border.color: "#99ccff"
                        //小圆点
                        Rectangle{
                            id:smallRect1
                            width: 163
                            height: 35
                            radius: 20
                            border.width: 3
                            color: "#2b70ad"
                            border.color: "#99ccff"
                            anchors.verticalCenter: parent.verticalCenter
                            //改变小圆点位置
                            NumberAnimation on x{
                                to:smallRect1.width
                                running: {
                                    var bResult = false;
                                    var tmpIndex = DeviceManager.SelectedDeviceIndex
                                    switch(DeviceManager.DeviceList[tmpIndex].DeviceObj.ConnectType)
                                    {
                                    case DeviceInfoEnum.TCP_IP:
                                        bResult = false;
                                        break;
                                    case DeviceInfoEnum.RS232:
                                        bResult = true;
                                        break;
                                    default:
                                        bResult = true;
                                        break;
                                    }
                                    return bResult;
                                }
                                duration: 0
                            }
                            NumberAnimation on x{
                                to: 8
                                running: {
                                    var bResult = false;
                                    var tmpIndex = DeviceManager.SelectedDeviceIndex
                                    switch(DeviceManager.DeviceList[tmpIndex].DeviceObj.ConnectType)
                                    {
                                    case DeviceInfoEnum.TCP_IP:
                                        bResult = true;
                                        break;
                                    case DeviceInfoEnum.RS232:
                                        bResult = false;
                                        break;
                                    default:
                                        bResult = true;
                                        break;
                                    }
                                    return bResult;
                                }
                                duration: 0
                            }
                        }
                        Text {
                            anchors.left: parent.left
                            anchors.top: parent.top
                            anchors.topMargin: 9
                            anchors.leftMargin: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 63 : 50
                            // text: qsTr("网络")
                            text: "TCP/IP"
                            color: {
                                return DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.ConnectType !== DeviceInfoEnum.TCP_IP ? pRgb(43, 112, 173) : "#e5e6e7"
                            }
                            font.family: GlobalSystemDefine.fontBold
                            font.bold: true
                            font.pixelSize: 18
                        }
                        Text {
                            anchors.right: parent.right
                            anchors.top: parent.top
                            anchors.topMargin: 9
                            anchors.rightMargin: 63
                            text: "RS232"
                            color: {
                                return DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.ConnectType !== DeviceInfoEnum.TCP_IP ? "#e5e6e7" : pRgb(43, 112, 173)
                            }
                            font.family: GlobalSystemDefine.fontBold
                            font.bold: true
                            font.pixelSize: 18
                        }
                    }
                }
                Loader{
                    id:loader
                    focus: true
                    property int tmpIndex: DeviceManager.SelectedDeviceIndex
                    sourceComponent: {
                        return DeviceManager.DeviceList[tmpIndex].DeviceObj.ConnectType === DeviceInfoEnum.TCP_IP ? rect1 : rect2
                    }
                }
                Component{
                    id:rect1
                    Rectangle{
                        x:110
                        y:226
                        width: 600
                        height: 343
                        radius: 6
                        color: "#78b0e7"
                        Text {
                            id: s16
                            // text: qsTr("网络端口")
                            text: GlobalLanguageDefine.strNetworkPort + ": "
                            color: pRgb(43, 112, 173)
                            font.family: GlobalSystemDefine.fontBold
                            font.bold: true
                            font.pixelSize: 18
                            x:101
                            y:63
                        }
                        Text {
                            id: s17
                            // text: qsTr("服务器端口")
                            text: GlobalLanguageDefine.strServerPort + ": "
                            color: pRgb(43, 112, 173)
                            font.family: GlobalSystemDefine.fontBold
                            font.bold: true
                            font.pixelSize: 18
                            anchors.left: s16.left
                            anchors.top: s16.bottom
                            anchors.topMargin: 33
                        }
                        Text {
                            id: s18
                            // text: qsTr("设备") + "IP" + qsTr("地址")
                            text: GlobalLanguageDefine.strDevice + "IP" + GlobalLanguageDefine.strAddress + ": "
                            color: pRgb(43, 112, 173)
                            font.family: GlobalSystemDefine.fontBold
                            font.bold: true
                            font.pixelSize: 18
                            anchors.left: s17.left
                            anchors.top: s17.bottom
                            anchors.topMargin: 33
                        }
                        Text {
                            id: s19
                            // text: qsTr("本地") + "IP" + qsTr("地址")
                            text: GlobalLanguageDefine.strLocal + "IP" + GlobalLanguageDefine.strAddress + ": "
                            color: pRgb(43, 112, 173)
                            font.family: GlobalSystemDefine.fontBold
                            font.bold: true
                            font.pixelSize: 18
                            anchors.left: s18.left
                            anchors.top: s18.bottom
                            anchors.topMargin: 33
                        }
                        //TODO CustomComboBox
                        CustomComboBox{
                            id:com2
                            width: 243
                            height: 40
                            x:233
                            y:55
                            model: NetworkModel
                            property int tmpIndex: DeviceManager.SelectedDeviceIndex
                            property int tmpPort: DeviceManager.DeviceList[tmpIndex].DeviceObj.EthNumber
                            currentIndex: NetworkModel.getKeyRoleIndex(tmpPort)
                            onAccepted: {
                                console.debug("index: ", currentIndex)
                                var value = model.get(currentIndex).value;
                                console.debug("value: ", value)
                                DeviceManager.DeviceList[tmpIndex].DeviceObj.EthNumber = value
                            }
                        }

                        TextField{
                            id:t5
                            width: 243
                            height: 40
                            anchors.top: com2.bottom
                            anchors.topMargin: 17
                            anchors.left: com2.left
                            horizontalAlignment: TextInput.AlignHCenter
                            verticalAlignment: TextInput.AlignVCenter
                            color: pRgb(43, 112, 173)
                            font.family: GlobalSystemDefine.fontBold
                            font.bold: true
                            font.pixelSize: 18
                            maximumLength: 5
                            inputMethodHints: Qt.ImhDigitsOnly
                            background: Rectangle{
                                radius: 6
                                border.width: 3
                                border.color: "#99ccff"
                            }
                            MouseArea {
                                anchors.fill: parent
                                onPressed: {
                                    t5.forceActiveFocus()
                                    keyboardType = 0
                                }
                            }
                            property int tmpIndex: DeviceManager.SelectedDeviceIndex
                            text: DeviceManager.DeviceList[tmpIndex].DeviceObj.PortNumber
                            onEditingFinished: {
                                var portRegex = /^([0-9]|[1-9][0-9]{1,4}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])$/
                                if (!portRegex.test(t5.text))
                                    footer.showError(s17.text + GlobalLanguageDefine.strEnter0And65535)
                                else
                                {
                                    footer.hideError()
                                    DeviceManager.DeviceList[tmpIndex].DeviceObj.PortNumber = t5.text
                                }
                            }

                        }
                        TextField{
                            id:t6
                            width: 243
                            height: 40
                            anchors.top: t5.bottom
                            anchors.topMargin: 17
                            anchors.left: t5.left
                            horizontalAlignment: TextInput.AlignHCenter
                            verticalAlignment: TextInput.AlignVCenter
                            color: pRgb(43, 112, 173)
                            font.family: GlobalSystemDefine.fontBold
                            font.bold: true
                            font.pixelSize: 18
                            inputMethodHints: Qt.ImhDigitsOnly
                            background: Rectangle{
                                radius: 6
                                border.width: 3
                                border.color: "#99ccff"
                            }
                            MouseArea {
                                anchors.fill: parent
                                onPressed: {
                                    t6.forceActiveFocus()
                                    keyboardType = 0
                                }
                            }
                            property int tmpIndex: DeviceManager.SelectedDeviceIndex
                            text: DeviceManager.DeviceList[tmpIndex].DeviceObj.RemoteIP
                            onEditingFinished: {
                                var ipRegex = /^(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)(\.(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)){3}$/
                                if (!ipRegex.test(t6.text))
                                    footer.showError(s18.text + "请输入正确的IP地址")
                                else
                                {
                                    footer.hideError()
                                    DeviceManager.DeviceList[tmpIndex].DeviceObj.RemoteIP = t6.text
                                }
                            }
                        }

                        TextField {
                            id: t7
                            width: 243
                            height: 40
                            anchors.top: t6.bottom
                            anchors.topMargin: 17
                            anchors.left: t6.left
                            horizontalAlignment: TextInput.AlignHCenter
                            verticalAlignment: TextInput.AlignVCenter
                            color: pRgb(43, 112, 173)
                            font.family: GlobalSystemDefine.fontBold
                            font.bold: true
                            font.pixelSize: 18
                            inputMethodHints: Qt.ImhDigitsOnly
                            background: Rectangle {
                                radius: 6
                                border.width: 3
                                border.color: "#99ccff"
                            }

                            MouseArea {
                                anchors.fill: parent
                                onPressed: {
                                    t7.forceActiveFocus()
                                    keyboardType = 0
                                }
                            }
                            property int tmpIndex: DeviceManager.SelectedDeviceIndex
                            text: DeviceManager.DeviceList[tmpIndex].DeviceObj.LocalIP
                            onEditingFinished: {
                                var ipRegex = /^(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)(\.(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)){3}$/
                                if (!ipRegex.test(t7.text))
                                    footer.showError(s19.text + "请输入正确的IP地址")
                                else
                                {
                                    footer.hideError()
                                    DeviceManager.DeviceList[tmpIndex].DeviceObj.LocalIP = t7.text
                                }
                            }
                        }
                    }
                }
                Component{
                    id:rect2
                    Rectangle{
                        x:110
                        y:226
                        width: 600
                        height: 343
                        radius: 6
                        color: "#78b0e7"
                        Text {
                            id: s20
                            // text: qsTr("端口")
                            text: GlobalLanguageDefine.strPort + ": "
                            color: pRgb(43, 112, 173)
                            font.family: GlobalSystemDefine.fontBold
                            font.bold: true
                            font.pixelSize: 18
                            x:101
                            y:48
                        }
                        Text {
                            id: s21
                            // text: qsTr("波特率")
                            text: GlobalLanguageDefine.strBaudRate + ": "
                            color: pRgb(43, 112, 173)
                            font.family: GlobalSystemDefine.fontBold
                            font.bold: true
                            font.pixelSize: 18
                            x:101
                            y:105
                        }
                        Text {
                            id: s22
                            // text: qsTr("数据位")
                            text: GlobalLanguageDefine.strDataBits + ": "
                            color: pRgb(43, 112, 173)
                            font.family: GlobalSystemDefine.fontBold
                            font.bold: true
                            font.pixelSize: 18
                            x:101
                            y:159
                        }
                        Text {
                            id: s23
                            // text: qsTr("奇偶校验位")
                            text: GlobalLanguageDefine.strParity + ": "
                            color: pRgb(43, 112, 173)
                            font.family: GlobalSystemDefine.fontBold
                            font.bold: true
                            font.pixelSize: 18
                            x:101
                            y:214
                        }
                        Text {
                            id: s24
                            // text: qsTr("停止位")
                            text: GlobalLanguageDefine.strStopBits + ": "
                            color: pRgb(43, 112, 173)
                            font.family: GlobalSystemDefine.fontBold
                            font.bold: true
                            font.pixelSize: 18
                            x:101
                            y:273
                        }
                        CustomComboBox{
                            id: comboComPort
                            width: 243
                            height: 40
                            x:233
                            y:40
                            model: ComModel
                            currentIndex: DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.ComNumber
                            onAccepted: {
                                console.debug("index: ", currentIndex)
                                var value = model.get(currentIndex).value;
                                console.debug("value: ", value)
                                DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.ComNumber = value
                            }
                        }
                        CustomComboBox{
                            id: comboBaudRate
                            width: 243
                            height: 40
                            x:233
                            y:97
                            model: BaudRateModel
                            currentIndex: DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.BaudRate
                            onAccepted: {
                                console.debug("index: ", currentIndex)
                                var value = model.get(currentIndex).value;
                                console.debug("value: ", value)
                                DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.BaudRate = value
                            }
                        }
                        CustomComboBox{
                            id: comboDataBits
                            width: 243
                            height: 40
                            x:233
                            y:151
                            model: DataBitsModel
                            currentIndex:DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.DataBits
                            onAccepted: {
                                console.debug("index: ", currentIndex)
                                var value = model.get(currentIndex).value;
                                console.debug("value: ", value)
                                DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.DataBits = value
                            }
                        }
                        CustomComboBox{
                            id:com6
                            width: 243
                            height: 40
                            x:233
                            y:206
                            model: ParityModel
                            currentIndex:DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.ParityBits
                            onAccepted: {
                                console.debug("index: ", currentIndex)
                                var value = model.get(currentIndex).value;
                                console.debug("value: ", value)
                                DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.ParityBits = value
                            }
                        }
                        CustomComboBox{
                            id: comboStopBits
                            width: 243
                            height: 40
                            x:233
                            y:265
                            model: StopBitsModel
                            currentIndex:  DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.StopBits
                            onAccepted: {
                                console.debug("index: ", currentIndex)
                                var value = model.get(currentIndex).value;
                                console.debug("value: ", value)
                                DeviceManager.DeviceList[DeviceManager.SelectedDeviceIndex].DeviceObj.StopBits = value
                            }
                        }
                    }
                }
                Button{
                    id:full
                    width: 30
                    height: 30
                    x:1170
                    y:10
                    visible: DeviceManager.DeviceCounter > 1 ? true : false
                    background: Rectangle{
                        color: "transparent"
                        Image {
                            anchors.fill: parent
                            source: "qrc:/images/btn_fullscreen_exit.png"
                        }
                    }
                    onPressed: {
                        loadViewsys(2, musys)
                    }
                }
            }

            Button{
                id: deviceSaveButton
                anchors.top: parent.bottom
                anchors.topMargin: 660
                anchors.left: parent.right
                anchors.leftMargin: 520
                width: 243
                height: 52
                background: Rectangle{
                    radius: 6
                    color: pRgb(43, 112, 173)
                }
                contentItem: Text {
                    // text: qsTr("设备保存")
                    text: GlobalLanguageDefine.strDeviceSave
                    font.pixelSize: 20
                    color: pRgb(153, 204, 255)
                    anchors.centerIn: parent  // 确保文本在按钮内居中对齐
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                }
                onPressed: {
                    // DeviceManager.saveDevice()
                    console.log("DeviceManager object:", DeviceManager)
                    var result = DeviceManager.saveDevice()
                    console.log("saveDevice result:", result)
                    loadViewsys(2, musys)
                }
            }
        }
    }

    Component{
        id: musys
        Item{
            readonly property string backgroundColor: "#2B70AD"
            readonly property string selectedColor: "#4a8ac4"
            function selectDevice(index)
            {
                s1.color = backgroundColor
                s2.color = backgroundColor
                s3.color = backgroundColor
                s4.color = backgroundColor
                switch(index)
                {
                case 0:
                    s1.color = selectedColor;
                    break;
                case 1:
                    s2.color = selectedColor;
                    break;
                case 2:
                    s3.color = selectedColor
                    break;
                case 3:
                    s4.color = selectedColor
                    break;
                default:
                    break;
                }
            }
            MultideviceSystemConfig
            {
                id:s1
                x:41
                y:68
                currentIndex: 0
                heightOption: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption
                suspiciousOption: DeviceManager.DeviceList[currentIndex].DeviceObj.SuspiciousOption
                visible: (DeviceManager.DeviceCounter > currentIndex) ? true : false
                nameWelder: DeviceManager.DeviceList[currentIndex].DeviceObj.WelderName
                typeWelder: DeviceManager.DeviceList[currentIndex].DeviceObj.WelderType
                typeConnect: DeviceManager.DeviceList[currentIndex].DeviceObj.ConnectType
                isConnected: DeviceManager.DeviceList[currentIndex].DeviceObj.ConnectState
                onSignalWelderSelected: {
                        selectDevice(index)
                        DeviceManager.SelectedDeviceIndex = index
                }
            }
            MultideviceSystemConfig{
                id:s2
                x:347
                y:68
                currentIndex: 1
                heightOption: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption
                suspiciousOption: DeviceManager.DeviceList[currentIndex].DeviceObj.SuspiciousOption
                visible: (DeviceManager.DeviceCounter > currentIndex) ? true : false
                nameWelder: DeviceManager.DeviceList[currentIndex].DeviceObj.WelderName
                typeWelder: DeviceManager.DeviceList[currentIndex].DeviceObj.WelderType
                typeConnect: DeviceManager.DeviceList[currentIndex].DeviceObj.ConnectType
                isConnected: DeviceManager.DeviceList[currentIndex].DeviceObj.ConnectState
                onSignalWelderSelected: {
                        selectDevice(index)
                        DeviceManager.SelectedDeviceIndex = index
                }
            }
            MultideviceSystemConfig{
                id:s3
                x:654
                y:68
                currentIndex: 2
                heightOption: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption
                suspiciousOption: DeviceManager.DeviceList[currentIndex].DeviceObj.SuspiciousOption
                visible: (DeviceManager.DeviceCounter > currentIndex) ? true : false
                nameWelder: DeviceManager.DeviceList[currentIndex].DeviceObj.WelderName
                typeWelder: DeviceManager.DeviceList[currentIndex].DeviceObj.WelderType
                typeConnect: DeviceManager.DeviceList[currentIndex].DeviceObj.ConnectType
                isConnected: DeviceManager.DeviceList[currentIndex].DeviceObj.ConnectState
                onSignalWelderSelected: {
                        selectDevice(index)
                        DeviceManager.SelectedDeviceIndex = index
                }
            }
            MultideviceSystemConfig{
                id:s4
                x:961
                y:68
                currentIndex: 3
                heightOption: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption
                suspiciousOption: DeviceManager.DeviceList[currentIndex].DeviceObj.SuspiciousOption
                visible: (DeviceManager.DeviceCounter > currentIndex) ? true : false
                nameWelder: DeviceManager.DeviceList[currentIndex].DeviceObj.WelderName
                typeWelder: DeviceManager.DeviceList[currentIndex].DeviceObj.WelderType
                typeConnect: DeviceManager.DeviceList[currentIndex].DeviceObj.ConnectType
                isConnected: DeviceManager.DeviceList[currentIndex].DeviceObj.ConnectState
                onSignalWelderSelected: {
                        selectDevice(index)
                        DeviceManager.SelectedDeviceIndex = index
                }
            }
            Connections{
                target: window
                function onSigStatusReset(){
                    s1.color = pRgb(43, 112, 173)
                    s2.color = pRgb(43, 112, 173)
                    s3.color = pRgb(43, 112, 173)
                    s4.color = pRgb(43, 112, 173)
                }
                function onSigDelDevice(){
                    DeviceManager.removeDevice()
                }
            }
            Button{
                id:btn1
                x:210
                y:654
                width: 243
                height: 52
                enabled: DeviceManager.DeviceCounter === 4 ? false : true
                background: Rectangle{
                    radius: 6
                    border.width: 2
                    border.color: pRgb(43, 112, 173)
                    color: DeviceManager.DeviceCounter === 4 ? pRgb(232, 232, 232) : pRgb(43, 112, 173)
                }
                contentItem: Text {
                    // text: qsTr( "新增设备")
                    text: GlobalLanguageDefine.strAddDevice
                    font.pixelSize: 20
                    color: pRgb(153, 204, 255)
                    anchors.centerIn: parent  // 确保文本在按钮内居中对齐
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                }
                onPressed: {
                    // popup.openPop(8)
                    DeviceManager.addDevice()
                    switchUI(3)
                    sigSysConfig()
                }
            }
            Button{
                id:btn2
                x:542
                y:654
                width: 243
                height: 52
                enabled: DeviceManager.DeviceCounter === 0 ? false : true
                background: Rectangle{
                    radius: 6
                    border.width: 2
                    border.color: pRgb(43, 112, 173)
                    color: DeviceManager.DeviceCounter === 0 ? pRgb(232, 232, 232) : pRgb(43, 112, 173)
                }
                contentItem: Text {
                    // text: qsTr("删除设备")
                    text: GlobalLanguageDefine.strDeleteDevice
                    font.pixelSize: 20
                    color: pRgb(153, 204, 255)
                    anchors.centerIn: parent  // 确保文本在按钮内居中对齐
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                }
                onPressed: {
                    popup.openPop(12)
                }
            }
            Button{
                id:btn3
                x:867
                y:654
                width: 243
                height: 52
                background: Rectangle{
                    radius: 6
                    color: pRgb(43, 112, 173)
                }
                contentItem: Text {
                    // text: qsTr("修改密码")
                    text: GlobalLanguageDefine.strChangePassword
                    font.pixelSize: 20
                    color: pRgb(153, 204, 255)
                    anchors.centerIn: parent  // 确保文本在按钮内居中对齐
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                }
                onPressed: {
                    popup.openPop(7)

                }
            }
        }
    }
}
