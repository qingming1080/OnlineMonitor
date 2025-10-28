import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.5
import Device 1.0
import DeviceInformation 1.0
import QmlEnum 1.0
import GlobalLanguageDefine 1.0
import GlobalSystemDefine   1.0
import GlobalMessageDefine  1.0
import LanguageEnum         1.0
import DeviceInfoEnum       1.0

//系统配置
Rectangle {
    id: sysUI
    // property bool isFirstDeviceConfigured: false
    // property string firstDeviceLocalIp: ""

    property int itemCount: equipmentCount
    property int currIndex: 0
    property int currentConfigId: 0 // 多设备时放大界面数据判断
    property int networkId: 1
    property int rs232Id: 1
    property int loadType: 0
    property bool musysTmp1: false
    property bool musysTmp2: false
    property bool musysTmp3: false
    property bool musysTmp4: false

    property bool undetermined1: false
    property bool undetermined2: false
    property bool undetermined3: false
    property bool undetermined4: false

    MessageDialog
    {
        id:isValidMessageDialog
    }
    property bool undeterMined: {
        //if(equipmentCount === 1){
        if(equipmentCount === 0){
            if(DeviceManager.DeviceList[0]){
                return DeviceManager.DeviceList[0].pIO.availabel
            }
            else{
                return false
            }
        }
        else{
            if(DeviceManager.DeviceList[currentConfigId-1]){
                return DeviceManager.DeviceList[currentConfigId-1].pIO.availabel
            }
            else{
                return false
            }
        }
    }
    property bool altitudMode:{
        if(DeviceManager.DeviceList[currentConfigId-1]){
            return DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.heightOption
                    === 1 ? true:false
        }
        else {
            return false
        }
    }
    property bool oneself: false
    property bool btnDefault: false
    property var sysViews: []
    Component.onCompleted: {
        loadViewsys(1,syscfg)
    }

    color: pRgb(153, 204, 255)

    signal sigSysCheck(var id)
    signal sigAddDevice()
    function sysCheck(id){
        sigSysCheck(id)
    }
    function loadViewsys(viewName, component) {
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
        if(isAdd){
            loadViewsys(1, syscfg)
        }
        else{
            loadViewsys(2, musys)
            // currIndex = 0
        }
    }
    ///TODO    onItemCountChanged

    onItemCountChanged: {
        if(itemCount == 0){
            musysTmp1 = false
            musysTmp2 = false
            musysTmp3 = false
            musysTmp4 = false
        }
        else if(itemCount == 1){
            musysTmp1 = true
            musysTmp2 = false
            musysTmp3 = false
            musysTmp4 = false
        }
        else if(itemCount == 2){
            musysTmp1 = true
            musysTmp2 = true
            musysTmp3 = false
            musysTmp4 = false
        }
        else if(itemCount == 3){
            musysTmp1 = true
            musysTmp2 = true
            musysTmp3 = true
            musysTmp4 = false
        }
        else if(itemCount == 4){
            musysTmp1 = true
            musysTmp2 = true
            musysTmp3 = true
            musysTmp4 = true
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
                target: sysUI

                //TODO onSigAddDevice
                function onSigAddDevice(){
                    DeviceManager.addDevice(maxProductionTextField.text,learningSamplesTextField.text,
                                            yieldLowerLimitTextField.text,t7.text,t8.text,clientIPTextField.text,
                                            // altitudMode?1:0,t4.text,com1.currentText,loadType,networkId)
                                           altitudMode?1:0,t4.text,com1.currentText,loadType,loadType ? rs232Id:networkId )
                    // networkId = 1
                    // rs232Id = 1
                    // loadType = 0
                    // DeviceManager.DeviceListChanged()

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

                    //TODO

                    text:{
                        // if(equipmentCount === 1){
                        if(equipmentCount === 0){
                            if(DeviceManager.DeviceList[0]){
                                DeviceManager.DeviceList[0].DevInfoObject.maxBacth
                            }
                            else{
                                return 20000
                            }
                        }
                        else{
                            if(DeviceManager.DeviceList[currentConfigId-1]){
                                DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.maxBacth
                            }
                            else{
                                return 20000
                            }
                        }
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
                            isValidMessageDialog.openFor(titleMaxProduction.text, "请输入20000~1000000之间整数！")
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
                        // if(equipmentCount === 1){
                        if(equipmentCount === 0){
                            if(DeviceManager.DeviceList[0]){
                                DeviceManager.DeviceList[0].DevInfoObject.sample
                            }
                            else{
                                return 20
                            }
                        }
                        else{
                            if(DeviceManager.DeviceList[currentConfigId-1]){
                                DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.sample
                            }
                            else{
                                return 20
                            }
                        }
                    }
                    onEditingFinished: {
                        var learningSamplesRegex = /^(1[0-9]|20)$/
                        if (!learningSamplesRegex.test(learningSamplesTextField.text))
                            isValidMessageDialog.openFor(titleLearningSamples.text, "请输入10~20之间的整数！")
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
                        // if(equipmentCount === 1){
                        if(equipmentCount === 0){
                            if(DeviceManager.DeviceList[0]){
                                DeviceManager.DeviceList[0].DevInfoObject.lowerLimit
                            }
                            else{
                                return 99
                            }
                        }
                        else{
                            if(DeviceManager.DeviceList[currentConfigId-1]){
                                DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.lowerLimit
                            }
                            else{
                                return 99
                            }
                        }
                    }
                    onEditingFinished: {
                        var yieldLowerLimitRegex = /^[1-9][0-9]$/
                        if (!yieldLowerLimitRegex.test(yieldLowerLimitTextField.text))
                            isValidMessageDialog.openFor(titleYieldLowerLimit.text, "请输入两位整数！")
                    }
                }

                Text {
                    id: s7
                    // text: qsTr("端口")
                    text: GlobalLanguageDefine.strPort + ": "
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
                       // if(equipmentCount === 1){
                        if(equipmentCount === 0){
                            if(DeviceManager.DeviceList[0]){
                                DeviceManager.DeviceList[0].DevInfoObject.lowerLimit
                            }
                            else{
                                return ""
                            }
                        }
                        else{
                            if(DeviceManager.DeviceList[currentConfigId-1]){
                                DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.lowerLimit
                            }
                            else{
                                return ""
                            }
                        }
                    }

                    onEditingFinished: {
                        var portRegex = /^([0-9]|[1-9][0-9]{1,4}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])$/
                        if (!portRegex.test(t7.text))
                            isValidMessageDialog.openFor(s7.text, "请输入0~65535之间的整数！")
                    }
                }

                Text {
                    id: s8
                    // text: qsTr("远程端") + "IP"
                    text: GlobalLanguageDefine.strRemoteEnd + "IP" + ": "
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
                    text:{
                        // if(equipmentCount === 1){
                        if(equipmentCount === 0){
                            if(DeviceManager.DeviceList[0]){
                                DeviceManager.DeviceList[0].DevInfoObject.lowerLimit
                            }
                            else{
                                return ""
                            }
                        }
                        else{
                            if(DeviceManager.DeviceList[currentConfigId-1]){
                                DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.lowerLimit
                            }
                            else{
                                return ""
                            }
                        }
                    }
                    onEditingFinished: {
                        var ipRegex = /^(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)(\.(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)){3}$/
                        if (!ipRegex.test(t8.text))
                            isValidMessageDialog.openFor(s8.text, "请输入正确的IP地址！")
                    }
                }


                Text {
                    id: titleClientIP
                    // text: qsTr("客户端") + "IP"
                    text: GlobalLanguageDefine.strClient + "IP" + ": "
                    color: pRgb(177, 213, 219)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    font.pixelSize: 18
                    anchors.left: s8.left
                    anchors.top: clientIPTextField.top
                    anchors.topMargin: 10
                }
                TextField{
                    id: clientIPTextField
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
                            clientIPTextField.forceActiveFocus()
                            keyboardType = 0
                        }
                    }
                    text:{
                        // if(equipmentCount === 1){
                        if(equipmentCount === 0){
                            if(DeviceManager.DeviceList[0]){
                                DeviceManager.DeviceList[0].DevInfoObject.lowerLimit
                            }
                            else{
                                return ""
                            }
                        }
                        else{
                            if(DeviceManager.DeviceList[currentConfigId-1]){
                                DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.lowerLimit
                            }
                            else{
                                return ""
                            }
                        }
                    }
                    onEditingFinished: {
                        var portRegex = /^(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)(\.(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)){3}$/
                        if (!portRegex.test(clientIPTextField.text))
                            isValidMessageDialog.openFor(titleClientIP.text, "请输入正确的IP地址！")
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
                    anchors.left: titleClientIP.left
                    anchors.top: titleClientIP.top
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
                    anchors.left: clientIPTextField.left

                }
                RadioButton{
                    id:bt1
                    width: 34
                    height: 34
                    anchors.left: s5.right
                    anchors.verticalCenter: titleHeightMode.verticalCenter
                    anchors.leftMargin: 10

                    checked: altitudMode
                    indicator: Rectangle
                    {
                        width: 34
                        height: 34
                        radius: 17
                        color: altitudMode ? "#0d988c" : pRgb(232, 232, 232)
                        border.color: "#b1d5db"
                        border.width: 2
                    }
                    onPressed: {
                        if(equipmentCount > 1){
                            sigUndetermined(currentConfigId)
                        }
                        if(isAdd){
                            altitudMode = true
                        }
                        // else if(equipmentCount === 1){
                        else if(equipmentCount === 0){
                            DeviceManager.DeviceList[0].DevInfoObject.setHeightOption(1)
                        }
                        else{
                            DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.setHeightOption(1)
                        }
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
                    checked: !altitudMode
                    indicator: Rectangle
                    {
                        width: 34
                        height: 34
                        radius: 17
                        color: !altitudMode ? "#0d988c" : pRgb(232, 232, 232)
                        border.color: "#b1d5db"
                        border.width: 2
                    }
                    onPressed: {
                        if(isAdd){
                            altitudMode = false
                        }
                        // else if(equipmentCount === 1){
                        else if(equipmentCount === 0){
                            DeviceManager.DeviceList[0].DevInfoObject.setHeightOption(0)
                        }
                        else{
                            DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.setHeightOption(0)
                        }
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
                    text:{
                        // if(equipmentCount === 1){
                        if(equipmentCount === 0){
                            if(DeviceManager.DeviceList[0]){
                                return DeviceManager.DeviceList[0].DevInfoObject.name
                            }
                            else{
                                return ""
                            }
                        }
                        else{
                            if(DeviceManager.DeviceList[currentConfigId-1]){
                                return DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.name
                            }
                            else{
                                return ""
                            }
                        }
                    }
                    onEditingFinished: {
                        var nameRegex = /^[\u4e00-\u9fa5A-Za-z0-9]+$/
                        if (!nameRegex.test(t4.text))
                            isValidMessageDialog.openFor(s14.text, "设备名称只能包含中文、字母、数字（1~8字符）！")
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
                    model: ["L20-VG", "L20-TS", "20DP", "20MA", GlobalLanguageDefine.strCustomized]
                    displayText:{
                        if(isAdd){
                            return currentText
                        }
                       // else if(equipmentCount === 1){
                        else if(equipmentCount === 0){
                            if(DeviceManager.DeviceList[0]){
                                 // DeviceManager.DeviceListChanged()
                                return DeviceManager.DeviceList[0].DevInfoObject.model
                            }
                            else{
                                return ""
                            }
                        }
                        else{
                            if(DeviceManager.DeviceList[currentConfigId-1]){
                                 // DeviceManager.DeviceListChanged()
                                return DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.model
                            }
                            else{
                                return ""
                            }
                        }

                    }
                    onDataAlter: {
                        if(isAdd){
                            return com1.currentText
                        }
                        //else if(equipmentCount === 1){
                        else if(equipmentCount === 0){
                             DeviceManager.DeviceListChanged()
                            DeviceManager.DeviceList[0].DevInfoObject.setModel(com1.currentText)
                        }
                        else{
                             DeviceManager.DeviceListChanged()
                            DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.setModel(com1.currentText)
                        }

                    }
                }



                Switch{
                    id:ctl1
                    x:228
                    y:147
                    onPressed: {
                        if(isAdd){

                        }
                       // if(equipmentCount === 1){
                        if(equipmentCount === 0){
                            if(ctl1.checked){
                                DeviceManager.DeviceList[0].DevInfoObject.ConnectType = 1
                            }
                            else{
                                DeviceManager.DeviceList[0].DevInfoObject.ConnectType = 0
                            }
                        }
                        else{
                            if(ctl1.checked){
                                DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.ConnectType = 1
                            }
                            else{
                                DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.ConnectType = 0
                            }
                        }
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
                                    if(isAdd){
                                        return ctl1.checked
                                    }
                                    //else if(equipmentCount === 1){
                                    else if(equipmentCount === 1){
                                        return DeviceManager.DeviceList[0].DevInfoObject.ConnectType !== 0? true : false
                                    }
                                    else{
                                        return DeviceManager.DeviceList[currentConfigId - 1].DevInfoObject.ConnectType !== 0? true : false
                                    }
                                }
                                duration: 0
                            }
                            NumberAnimation on x{
                                to:8
                                running: {
                                    if(isAdd){
                                        return !ctl1.checked
                                    }
                                    // else if(equipmentCount === 1){
                                    else if(equipmentCount === 1){
                                        return DeviceManager.DeviceList[0].DevInfoObject.ConnectType !== 0? false : true
                                    }
                                    else{
                                        return DeviceManager.DeviceList[currentConfigId - 1].DevInfoObject.ConnectType !== 0? false : true
                                    }
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
                                if(isAdd){
                                    return ctl1.checked ? pRgb(43, 112, 173) : "#e5e6e7"
                                }
                                // else if(equipmentCount === 1){
                                else if(equipmentCount === 1){
                                    return DeviceManager.DeviceList[0].DevInfoObject.ConnectType !== 0 ? pRgb(43, 112, 173) : "#e5e6e7"
                                }
                                else{
                                    return DeviceManager.DeviceList[currentConfigId - 1].DevInfoObject.ConnectType !== 0 ? pRgb(43, 112, 173) : "#e5e6e7"
                                }
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
                                if(isAdd){
                                    return !ctl1.checked ? pRgb(43, 112, 173) : "#e5e6e7"
                                }
                                // else if(equipmentCount === 1){
                                else if(equipmentCount === 1){
                                    return DeviceManager.DeviceList[0].DevInfoObject.ConnectType !== 0? "#e5e6e7" : pRgb(43, 112, 173)
                                }
                                else{
                                    return DeviceManager.DeviceList[currentConfigId - 1].DevInfoObject.ConnectType !== 0? "#e5e6e7" : pRgb(43, 112, 173)
                                }
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
                    sourceComponent: {
                        if(isAdd){
                            loadType = ctl1.checked ? 1 : 0
                            return ctl1.checked ? rect2 : rect1
                        }
                        // else if(equipmentCount === 1){
                        else if(equipmentCount === 1){
                            // DeviceManager.DeviceListChanged()
                            return DeviceManager.DeviceList[0].DevInfoObject.ConnectType === 0 ? rect1 : rect2
                        }
                        else{
                            // DeviceManager.DeviceListChanged()
                            return DeviceManager.DeviceList[currentConfigId - 1].DevInfoObject.ConnectType === 0 ? rect1 : rect2
                        }

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
                            model: ["ETH1", "ETH2", "ETH3", "ETH4"]
                            onDisplayTextChanged: {
                                if(isAdd){
                                    networkId = com2.currentIndex+1

                                    console.log("currentText: ",currentText,"equipmentCount:",equipmentCount, "networkId:", networkId)
                                }
                            }

                            displayText: {
                                if(isAdd){
                                    console.log("currentText: ",currentText,"equipmentCount:",equipmentCount,"currentConfigId:",currentConfigId)
                                    return currentText

                                }
                                // else if(equipmentCount === 1){
                                else if(equipmentCount === 0){
                                     console.log("currentText: ",currentText,"equipmentCount<0:",equipmentCount, "networkId:", networkId,"currentConfigId:",currentConfigId)
                                    if(DeviceManager.DeviceList[0].DevInfoObject.connectID === 1){
                                        return "ETH1"
                                    }
                                    else if(DeviceManager.DeviceList[0].DevInfoObject.connectID === 2){
                                        return "ETH2"
                                    }
                                    else if(DeviceManager.DeviceList[0].DevInfoObject.connectID === 3){
                                        return "ETH3"
                                    }
                                    else if(DeviceManager.DeviceList[0].DevInfoObject.connectID === 4){
                                        return "ETH4"
                                    }

                                }
                                else{
                                     console.log("currentText: ",currentText,"equipmentCount>>0:",equipmentCount, "networkId:", networkId,"currentConfigId:",currentConfigId)
                                    if(DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.connectID === 1){
                                        return "ETH1"
                                    }
                                    else if(DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.connectID === 2){
                                        return "ETH2"
                                    }
                                    else if(DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.connectID === 3){
                                        return "ETH3"
                                    }
                                    else if(DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.connectID === 4){
                                        return "ETH4"
                                    }

                                }
                            }
                            onDataAlter: {
                                // if(equipmentCount === 1){
                                 console.log("currentText: ",currentText,"equipmentCount>>0:",equipmentCount, "networkId:", networkId,"currentConfigId:",currentConfigId)
                                if(equipmentCount === 0){
                                    DeviceManager.DeviceList[0].DevInfoObject.setConnectID(com2.currentIndex+1)
                                }
                                else{
                                    DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.setConnectID(com2.currentIndex+1)
                                }
                                 DeviceManager.DeviceListChanged()

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
                            //TODO
                            text: {
                                if(com2.displayText === "ETH1"){

                                    return NetworkModel.getDataByWelderID(2,QmlEnum.NETWORK_server_port)
                                }
                                else if(com2.displayText === "ETH2"){
                                    return NetworkModel.getDataByWelderID(3,QmlEnum.NETWORK_server_port)
                                }
                                else if(com2.displayText === "ETH3"){
                                    return NetworkModel.getDataByWelderID(4,QmlEnum.NETWORK_server_port)
                                }
                                else if(com2.displayText === "ETH4"){
                                    return NetworkModel.getDataByWelderID(5,QmlEnum.NETWORK_server_port)
                                }
                            }

                            onTextChanged: {
                                   if (com2.displayText === "ETH1") {
                                       NetworkModel.setNetworkData(2, QmlEnum.NETWORK_server_port, t5.text);
                                   } else if (com2.displayText === "ETH2") {
                                       NetworkModel.setNetworkData(3, QmlEnum.NETWORK_server_port, t5.text);
                                   } else if (com2.displayText === "ETH3") {
                                       NetworkModel.setNetworkData(4, QmlEnum.NETWORK_server_port, t5.text);
                                   } else if (com2.displayText === "ETH4") {
                                       NetworkModel.setNetworkData(5, QmlEnum.NETWORK_server_port, t5.text);
                                   }

                               }
                            onEditingFinished: {
                                var portRegex = /^([0-9]|[1-9][0-9]{1,4}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])$/
                                if (!portRegex.test(t5.text))
                                    isValidMessageDialog.openFor(s17.text,"请输入0~65535之间的整数！")
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
                                   //TODO
                            text:{
                                if(com2.displayText === "ETH1"){
                                    return NetworkModel.getDataByWelderID(2,QmlEnum.NETWORK_remote_ip)
                                }
                                else if(com2.displayText === "ETH2"){
                                    return NetworkModel.getDataByWelderID(3,QmlEnum.NETWORK_remote_ip)
                                }
                                else if(com2.displayText === "ETH3"){
                                    return NetworkModel.getDataByWelderID(4,QmlEnum.NETWORK_remote_ip)
                                }
                                else if(com2.displayText === "ETH4"){
                                    return NetworkModel.getDataByWelderID(5,QmlEnum.NETWORK_remote_ip)
                                }
                            }

                            onTextChanged: {
                                   if (com2.displayText === "ETH1") {
                                       NetworkModel.setNetworkData(2, QmlEnum.NETWORK_remote_ip, t6.text);
                                   } else if (com2.displayText === "ETH2") {
                                       NetworkModel.setNetworkData(3, QmlEnum.NETWORK_remote_ip, t6.text);
                                   } else if (com2.displayText === "ETH3") {
                                       NetworkModel.setNetworkData(4, QmlEnum.NETWORK_remote_ip, t6.text);
                                   } else if (com2.displayText === "ETH4") {
                                       NetworkModel.setNetworkData(5, QmlEnum.NETWORK_remote_ip, t6.text);
                                   }

                               }
                            onEditingFinished: {
                                var ipRegex = /^(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)(\.(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)){3}$/
                                if (!ipRegex.test(t6.text))
                                    isValidMessageDialog.openFor(s18.text,"请输入正确的IP地址")
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

                            text: {
                                if (com2.displayText === "ETH1") {
                                    return NetworkModel.getDataByWelderID(2, QmlEnum.NETWORK_local_ip)
                                }
                                else if (com2.displayText === "ETH2") {
                                    return NetworkModel.getDataByWelderID(3, QmlEnum.NETWORK_local_ip)
                                }
                                else if (com2.displayText === "ETH3") {
                                    return NetworkModel.getDataByWelderID(4, QmlEnum.NETWORK_local_ip)
                                }
                                else if (com2.displayText === "ETH4") {
                                    return NetworkModel.getDataByWelderID(5, QmlEnum.NETWORK_local_ip)
                                }
                            }

                            onTextChanged: {
                                   if (com2.displayText === "ETH1") {
                                       console.log("1DeviceManager.DeviceListChanged()111111111111text")
                                       NetworkModel.setNetworkData(2, QmlEnum.NETWORK_local_ip, t7.text);
                                   } else if (com2.displayText === "ETH2") {
                                       NetworkModel.setNetworkData(3, QmlEnum.NETWORK_local_ip, t7.text);
                                   } else if (com2.displayText === "ETH3") {
                                       NetworkModel.setNetworkData(4, QmlEnum.NETWORK_local_ip, t7.text);
                                   } else if (com2.displayText === "ETH4") {
                                       NetworkModel.setNetworkData(5, QmlEnum.NETWORK_local_ip, t7.text);
                                   }
                            }
                            onEditingFinished: {
                                var ipRegex = /^(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)(\.(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)){3}$/
                                if (!ipRegex.test(t7.text))
                                    isValidMessageDialog.openFor(s19.text,"请输入正确的IP地址")
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
                            id:com3
                            width: 243
                            height: 40
                            x:233
                            y:40
                            model: ["COM1", "COM2"]
                            onDisplayTextChanged: {
                                if(isAdd){
                                    console.log("rs232-onDisplayTextChanged-currentTex1t: ",currentText,"equipmentCount:",equipmentCount)
                                    rs232Id = com3.currentIndex+1
                                    console.log("rs232-onDisplayTextChanged-currentTex2t: ",currentText,"equipmentCount:",equipmentCount,"rs232Id:" , rs232Id)
                                }
                            }
                            displayText: {
                                if(isAdd){
                                    console.log("rs232-currentText: ",currentText,"equipmentCount:",equipmentCount)
                                    return currentText
                                }
                                // else if(equipmentCount === 1){
                                else if(equipmentCount === 0){
                                    if(DeviceManager.DeviceList[0].DevInfoObject.connectID === 1){
                                        return "COM1"
                                    }
                                    else if(DeviceManager.DeviceList[0].DevInfoObject.connectID === 2){
                                        return "COM2"
                                    }

                                }
                                else{
                                    if(DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.connectID === 1){
                                        return "COM1"
                                    }
                                    else if(DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.connectID === 2){
                                        return "COM2"
                                    }

                                }
                            }
                            onDataAlter: {
                                // if(equipmentCount === 1){
                                    if(equipmentCount === 0){
                                     console.log("rs232-onDataAlter-currentText: ",currentText,"equipmentCount:",equipmentCount)
                                    DeviceManager.DeviceList[0].DevInfoObject.setConnectID(com3.currentIndex+1)
                                }
                                else{
                                    console.log("rs232-onDataAlter-currentText2: ",currentText,"equipmentCount:",equipmentCount)
                                    DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.setConnectID(com3.currentIndex+1)
                                }
                                    DeviceManager.DeviceListChanged()

                            }
                        }
                        CustomComboBox{
                            id:com4
                            width: 243
                            height: 40
                            x:233
                            y:97
                            model: ["2400", "4800", "9600", "19200", "38400", "115200"]
                            displayText:{
                                if(com3.displayText === "COM1"){
                                    return RS232Model.getDataByWelderID(1,QmlEnum.RS232_baud_rate)
                                }
                                else if(com3.displayText === "COM2"){
                                    return RS232Model.getDataByWelderID(2,QmlEnum.RS232_baud_rate)
                                }

                            }
                            onDataAlter: {
                                if(com3.displayText === "COM1"){
                                    RS232Model.setRS232Data(1,QmlEnum.RS232_baud_rate,currentText)
                                }
                                else if(com3.displayText === "COM2"){
                                    RS232Model.setRS232Data(2,QmlEnum.RS232_baud_rate,currentText)
                                }
                                com4.displayText = currentText
                                DeviceManager.DeviceListChanged()

                            }
                        }
                        CustomComboBox{
                            id:com5
                            width: 243
                            height: 40
                            x:233
                            y:151
                            model: ["7bit", "8bit"]
                            displayText:{
                                if(com3.displayText === "COM1"){
                                    return RS232Model.getDataByWelderID(1,QmlEnum.RS232_data_bit)
                                }
                                else if(com3.displayText === "COM2"){
                                    return RS232Model.getDataByWelderID(2,QmlEnum.RS232_data_bit)
                                }
                            }
                            onDataAlter: {
                                if(com3.displayText === "COM1"){
                                    if(com5.currentIndex === 0){
                                        RS232Model.setRS232Data(1,QmlEnum.RS232_data_bit,7)
                                    }
                                    else if(com5.currentIndex === 1){
                                        RS232Model.setRS232Data(1,QmlEnum.RS232_data_bit,8)
                                    }
                                }
                                else if(com3.displayText === "COM2"){
                                    if(com5.currentIndex === 0){
                                        RS232Model.setRS232Data(2,QmlEnum.RS232_data_bit,7)
                                    }
                                    else if(com5.currentIndex === 1){
                                        RS232Model.setRS232Data(2,QmlEnum.RS232_data_bit,8)
                                    }
                                }
                                com5.displayText = currentText
                                DeviceManager.DeviceListChanged()

                            }
                        }
                        CustomComboBox{
                            id:com6
                            width: 243
                            height: 40
                            x:233
                            y:206
                            model: ["None", "Odd", "Even"]
                            displayText: {
                                if(com3.displayText === "COM1"){
                                    return RS232Model.getDataByWelderID(1,QmlEnum.RS232_parity_bit)
                                }
                                else if(com3.displayText === "COM2"){
                                    return RS232Model.getDataByWelderID(2,QmlEnum.RS232_parity_bit)
                                }

                            }
                            onDataAlter: {
                                if(com3.displayText === "COM1"){
                                    RS232Model.setRS232Data(1,QmlEnum.RS232_parity_bit,currentText)
                                }
                                else if(com3.displayText === "COM2"){
                                    RS232Model.setRS232Data(2,QmlEnum.RS232_parity_bit,currentText)
                                }
                                com6.displayText = currentText
                                DeviceManager.DeviceListChanged()

                            }
                        }
                        CustomComboBox{
                            id:com7
                            width: 243
                            height: 40
                            x:233
                            y:265
                            model: ["1bit", "1.5bit", "2bit"]
                            displayText:{
                                if(com3.displayText === "COM1"){
                                    return RS232Model.getDataByWelderID(1,QmlEnum.RS232_stop_bit)
                                }
                                else if(com3.displayText === "COM2"){
                                    return RS232Model.getDataByWelderID(2,QmlEnum.RS232_stop_bit)
                                }

                            }
                            onDataAlter: {
                                if(com3.displayText === "COM1"){
                                    if(com7.currentIndex === 0){
                                        RS232Model.setRS232Data(1,QmlEnum.RS232_stop_bit,1)
                                    }
                                    else if(com7.currentIndex === 1){
                                        RS232Model.setRS232Data(1,QmlEnum.RS232_stop_bit,1.5)
                                    }
                                    else if(com7.currentIndex === 2){
                                        RS232Model.setRS232Data(1,QmlEnum.RS232_stop_bit,2)
                                    }
                                }
                                else if(com3.displayText === "COM2"){
                                    if(com7.currentIndex === 0){
                                        RS232Model.setRS232Data(2,QmlEnum.RS232_stop_bit,1)
                                    }
                                    else if(com7.currentIndex === 1){
                                        RS232Model.setRS232Data(2,QmlEnum.RS232_stop_bit,1.5)
                                    }
                                    else if(com7.currentIndex === 2){
                                        RS232Model.setRS232Data(2,QmlEnum.RS232_stop_bit,2)
                                    }
                                }
                                com7.displayText = currentText
                                DeviceManager.DeviceListChanged()
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
                    visible: equipmentCount > 1 ? true : false
                    //visible: equipmentCount > 1
                    background: Rectangle{
                        color: "transparent"
                        Image {
                            anchors.fill: parent
                            source: "qrc:/images/btn_fullscreen_exit.png"
                        }
                    }
                    onPressed: {
                        loadViewsys(2,musys)
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
                    if(maxProductionTextField.text >= 20000 && maxProductionTextField.text <= 1000000){
                        if(learningSamplesTextField.text >= 10 && learningSamplesTextField.text <= 20){
                            if(yieldLowerLimitTextField.text >= 90 && yieldLowerLimitTextField.text <= 99){
                                if(isAdd){
                                    Qt.callLater(sigAddDevice)
                                    if(!oneself){
                                        switchUI(1)
                                    }
                                    oneself = false
                                    sigUndetermined(1)
                                    loadViewsys(2,musys)
                                    isAdd = false
                                    return
                                }
                                //if(full.visible){//设置多设备时配置存储
                                if(equipmentCount > 1){//设置多设备时配置存储
                                    DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.setProductionMaxBacth(maxProductionTextField.text)
                                    DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.setMaxModelSamples(learningSamplesTextField.text)
                                    DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.setYieldRateLowerLimit(yieldLowerLimitTextField.text)
                                    DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.setWelderName(t4.text)
                                }
                                else{
                                    // DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.setMaxBacth(t1.text)
                                    // DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.setSample(t2.text)
                                    // DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.setLowerLimit(t3.text)
                                    // DeviceManager.DeviceList[currentConfigId-1].DevInfoObject.setName(t4.text)
                                    DeviceManager.DeviceList[0].DevInfoObject.setProductionMaxBacth(maxProductionTextField.text)
                                    DeviceManager.DeviceList[0].DevInfoObject.setMaxModelSamples(learningSamplesTextField.text)
                                    DeviceManager.DeviceList[0].DevInfoObject.setYieldRateLowerLimit(yieldLowerLimitTextField.text)
                                    DeviceManager.DeviceList[0].DevInfoObject.setWelderName(t4.text)
                                }
                                loadViewsys(2,musys)
                            }
                            else{
                                popup.openPop(11)
                            }
                        }
                        else{
                            popup.openPop(11)
                        }
                    }
                    else{
                        popup.openPop(11)
                    }
                }
            }
        }
    }

    Component{
        id: musys
        //TODO
        Item{
            MultideviceSystemConfig{
                id:s1
                x:41
                y:68
                sysCurrIndex:DeviceManager.DeviceList[0].DevInfoObject.id
                sysCurrIndex1:1
                heightOpation:{
                    if(DeviceManager.DeviceList[0]){
                        return DeviceManager.DeviceList[0].DevInfoObject.heightOption
                                === 1 ? true:false
                    }
                    else{
                        return false
                    }
                }
                visible: musysTmp1
                eqText1:{
                    if(DeviceManager.DeviceList[0]){
                        DeviceManager.DeviceList[0].DevInfoObject.name
                    }
                    else{
                        return ""
                    }
                }
                eqText2:{
                    if(DeviceManager.DeviceList[0]){
                        DeviceManager.DeviceList[0].DevInfoObject.model
                    }
                    else{
                        return ""
                    }
                }
                eqText3:{
                    if(DeviceManager.DeviceList[0]){
                        DeviceManager.DeviceList[0].DevInfoObject.ConnectType === 0  ? "TCP/IP" : "RS232"
                    }
                    else{
                        return ""
                    }
                }
                eqText4:{
                    if(DeviceManager.DeviceList[0])
                    {
                        var connectState = DeviceManager.DeviceList[0].DevInfoObject.ConnectState
                        return GlobalMessageDefine.getConnectState(connectState)
                    }
                    else{
                        return ""
                    }
                }
                onSigAltitudeModel: {
                    if(visible){
                        altitudeModel1 = tmp
                    }
                }
            }
            MultideviceSystemConfig{
                id:s2
                x:347
                y:68
                sysCurrIndex:DeviceManager.DeviceList[1].DevInfoObject.id
                sysCurrIndex1:2
                heightOpation:{
                    if(DeviceManager.DeviceList[1]){
                        return DeviceManager.DeviceList[1].DevInfoObject.heightOption
                                === 1 ? true:false
                    }
                    else{
                        return false
                    }
                }
                visible: musysTmp2
                eqText1:{
                    if(DeviceManager.DeviceList[1]){
                        DeviceManager.DeviceList[1].DevInfoObject.name
                    }
                    else{
                        return ""
                    }
                }
                eqText2:{
                    if(DeviceManager.DeviceList[1]){
                        DeviceManager.DeviceList[1].DevInfoObject.model
                    }
                    else{
                        return ""
                    }
                }
                eqText3:{
                    if(DeviceManager.DeviceList[1]){
                        DeviceManager.DeviceList[1].DevInfoObject.ConnectType === 0 ? "TCP/IP" : "RS232"
                    }
                    else{
                        return ""
                    }
                }
                eqText4:{
                    if(DeviceManager.DeviceList[1])
                    {
                        var connectState = DeviceManager.DeviceList[1].DevInfoObject.ConnectState
                        return GlobalMessageDefine.getConnectState(connectState)
                    }
                    else{
                        return ""
                    }
                }
                onSigAltitudeModel: {
                    if(visible){
                        altitudeModel2 = tmp
                    }
                }
            }
            MultideviceSystemConfig{
                id:s3
                x:654
                y:68
                sysCurrIndex: DeviceManager.DeviceList[2].DevInfoObject.id
                sysCurrIndex1: 3
                heightOpation:{
                    if(DeviceManager.DeviceList[2]){
                        return DeviceManager.DeviceList[2].DevInfoObject.heightOption
                                === 1 ? true:false
                    }
                    else if(DeviceManager.DeviceList[3]){
                        return DeviceManager.DeviceList[3].DevInfoObject.heightOption
                                === 1 ? true : false
                    }
                    else{
                        return false
                    }
                }
                visible: musysTmp3
                eqText1:{
                    if(DeviceManager.DeviceList[2]){
                        DeviceManager.DeviceList[2].DevInfoObject.name
                    }
                    else if(DeviceManager.DeviceList[3]){
                        DeviceManager.DeviceList[3].DevInfoObject.name
                    }
                    else{
                        return ""
                    }
                }
                eqText2:{
                    if(DeviceManager.DeviceList[2]){
                        DeviceManager.DeviceList[2].DevInfoObject.model
                    }
                    else if(DeviceManager.DeviceList[3]){
                        DeviceManager.DeviceList[3].DevInfoObject.model
                    }
                    else{
                        return ""
                    }
                }
                eqText3:{
                    if(DeviceManager.DeviceList[2]){
                        DeviceManager.DeviceList[2].DevInfoObject.ConnectType === 0  ? "TCP/IP" : "RS232"
                    }
                    else if(DeviceManager.DeviceList[3]){
                        DeviceManager.DeviceList[3].DevInfoObject.ConnectType === 0  ? "TCP/IP" : "RS232"
                    }
                    else{
                        return ""
                    }
                }
                eqText4:{
                    var connectState = 0
                    if(DeviceManager.DeviceList[2])
                    {
                        connectState = DeviceManager.DeviceList[2].DevInfoObject.ConnectState
                        return GlobalMessageDefine.getConnectState(connectState)
                    }
                    else if(DeviceManager.DeviceList[3])
                    {
                        connectState = DeviceManager.DeviceList[3].DevInfoObject.ConnectState
                        return GlobalMessageDefine.getConnectState(connectState)
                    }
                    else{
                        return ""
                    }
                }
                onSigAltitudeModel: {
                    if(visible){
                        altitudeModel3 = tmp
                    }
                }
            }
            MultideviceSystemConfig{
                id:s4
                x:961
                y:68
                sysCurrIndex:DeviceManager.DeviceList[3].DevInfoObject.id
                sysCurrIndex1:4
                visible: musysTmp4
                heightOpation:{
                    if(DeviceManager.DeviceList[3]){
                        return DeviceManager.DeviceList[3].DevInfoObject.heightOption
                                === 1 ? true:false
                    }
                    else if(DeviceManager.DeviceList[2]){
                        return DeviceManager.DeviceList[2].DevInfoObject.heightOption
                                === 1 ? true:false
                    }
                    else{
                        return false
                    }
                }
                eqText1:{
                    if(DeviceManager.DeviceList[3]){
                        DeviceManager.DeviceList[3].DevInfoObject.name
                    }
                    else if(DeviceManager.DeviceList[2]){
                        DeviceManager.DeviceList[2].DevInfoObject.name
                    }
                    else{
                        return ""
                    }
                }
                eqText2:{
                    if(DeviceManager.DeviceList[3]){
                        DeviceManager.DeviceList[3].DevInfoObject.model
                    }
                    else if(DeviceManager.DeviceList[2]){
                        DeviceManager.DeviceList[2].DevInfoObject.model
                    }
                    else{
                        return ""
                    }
                }
                eqText3:{
                    if(DeviceManager.DeviceList[3]){
                        DeviceManager.DeviceList[3].DevInfoObject.ConnectType === 0  ? "TCP/IP" : "RS232"
                    }
                    else if(DeviceManager.DeviceList[2]){
                        DeviceManager.DeviceList[2].DevInfoObject.ConnectType === 0  ? "TCP/IP" : "RS232"
                    }
                    else{
                        return ""
                    }
                }
                eqText4:{
                    var connectState = 0
                    if(DeviceManager.DeviceList[3])
                    {
                        connectState = DeviceManager.DeviceList[3].DevInfoObject.ConnectState
                        return GlobalMessageDefine.getConnectState(connectState)
                    }
                    else if(DeviceManager.DeviceList[2])
                    {
                        connectState = DeviceManager.DeviceList[2].DevInfoObject.ConnectState
                        return GlobalMessageDefine.getConnectState(connectState)
                    }
                    else{
                        return ""
                    }
                }
                onSigAltitudeModel: {
                    if(visible){
                        altitudeModel4 = tmp
                    }
                }
            }

            Connections{
                target: sysUI
                function onSigSysCheck(id){
                    s1.color = pRgb(43, 112, 173)
                    s2.color = pRgb(43, 112, 173)
                    s3.color = pRgb(43, 112, 173)
                    s4.color = pRgb(43, 112, 173)
                    if(id === 1){
                        s1.color = "#4a8ac4"
                    }
                    else if(id === 2){
                        s2.color = "#4a8ac4"
                    }
                    else if(id === 3){
                        s3.color = "#4a8ac4"
                    }
                    else if(id === 4){
                        s4.color = "#4a8ac4"
                    }
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
                    DeviceManager.removeDevice(currIndex)
                    //                    var a = altitudeModel1
                    //                    var b = altitudeModel2
                    //                    var c = altitudeModel3
                    //                    var d = altitudeModel4
                    //                    var p1 = undetermined1
                    //                    var p2 = undetermined2
                    //                    var p3 = undetermined3
                    //                    var p4 = undetermined4
                    //                    altitudeModel1 = false
                    //                    altitudeModel2 = false
                    //                    altitudeModel3 = false
                    //                    altitudeModel4 = false
                    //                    undetermined1 = false
                    //                    undetermined2 = false
                    //                    undetermined3 = false
                    //                    undetermined4 = false
                    if(currIndex == 1){
                        s1.color = pRgb(43, 112, 173)
                        //                        if(equipmentCount == 3){
                        //                            altitudeModel1 = b
                        //                            altitudeModel2 = c
                        //                            altitudeModel3 = d
                        //                            undetermined1 = p2
                        //                            undetermined2 = p3
                        //                            undetermined3 = p4
                        //                        }
                        //                        else if(equipmentCount == 2){
                        //                            altitudeModel1 = b
                        //                            altitudeModel2 = c
                        //                            undetermined1 = p2
                        //                            undetermined2 = p3
                        //                        }
                        //                        else if(equipmentCount == 1){
                        //                            altitudeModel1 = b
                        //                            btnDefault = b
                        //                            undetermined1 = p2
                        //                        }
                    }
                    else if(currIndex == 2){
                        s2.color = pRgb(43, 112, 173)
                        //                        if(equipmentCount == 3){
                        //                            altitudeModel1 = a
                        //                            altitudeModel2 = c
                        //                            altitudeModel3 = d
                        //                            undetermined1 = p1
                        //                            undetermined2 = p3
                        //                            undetermined3 = p4
                        //                        }
                        //                        else if(equipmentCount == 2){
                        //                            altitudeModel1 = a
                        //                            altitudeModel2 = c
                        //                            undetermined1 = p1
                        //                            undetermined2 = p3
                        //                        }
                        //                        else if(equipmentCount == 1){
                        //                            altitudeModel1 = a
                        //                            btnDefault = a
                        //                            undetermined1 = p1
                        //                        }
                    }
                    else if(currIndex == 3){
                        s3.color = pRgb(43, 112, 173)
                        //                        if(equipmentCount == 3){
                        //                            altitudeModel1 = a
                        //                            altitudeModel2 = b
                        //                            altitudeModel3 = d
                        //                            undetermined1 = p1
                        //                            undetermined2 = p2
                        //                            undetermined3 = p4
                        //                        }
                        //                        else if(equipmentCount == 2){
                        //                            altitudeModel1 = a
                        //                            altitudeModel2 = b
                        //                            undetermined1 = p1
                        //                            undetermined2 = p2
                        //                        }
                        //                        else if(equipmentCount == 1){
                        //                            altitudeModel1 = a
                        //                            btnDefault = a
                        //                            undetermined1 = p1
                        //                        }
                    }
                    else if(currIndex == 4){
                        s4.color = pRgb(43, 112, 173)
                        //                        if(equipmentCount == 3){
                        //                            altitudeModel1 = a
                        //                            altitudeModel2 = b
                        //                            altitudeModel3 = c
                        //                            undetermined1 = p1
                        //                            undetermined2 = p2
                        //                            undetermined3 = p3
                        //                        }
                        //                        else if(equipmentCount == 2){
                        //                            altitudeModel1 = a
                        //                            altitudeModel2 = b
                        //                            undetermined1 = p1
                        //                            undetermined2 = p2
                        //                        }
                        //                        else if(equipmentCount == 1){
                        //                            altitudeModel1 = a
                        //                            btnDefault = a
                        //                            undetermined1 = p1
                        //                        }
                    }
                    // currIndex = 0
                }
            }
            Button{
                id:btn1
                x:210
                y:654
                width: 243
                height: 52
                enabled: itemCount === 4 ? false : true
                background: Rectangle{
                    radius: 6
                    border.width: 2
                    border.color: pRgb(43, 112, 173)
                    color: itemCount === 4 ? pRgb(232, 232, 232) : pRgb(43, 112, 173)
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
                    isAdd = true
                    oneself = true //打开就是新增完设备就是进入生产页面
                    // isFirstDeviceConfigured = updateIsFirstDeviceConfigured()
                    // console.log("isFirstDeviceConfigured :" + isFirstDeviceConfigured)
                    if (equipmentCount >= 0 && equipmentCount <= 3) {
                        currentConfigId = equipmentCount + 1;
                    }
                    // popup.openPop(8)
                    switchUI(3)
                    isAdd = true
                    sigSysConfig()
                }
            }
            Button{
                id:btn2
                x:542
                y:654
                width: 243
                height: 52
                enabled: currIndex === 0 ? false : true
                background: Rectangle{
                    radius: 6
                    border.width: 2
                    border.color: pRgb(43, 112, 173)
                    color: currIndex === 0 ? pRgb(232, 232, 232) : pRgb(43, 112, 173)
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
                    if (equipmentCount > 0) {
                        currentConfigId = equipmentCount - 1;
                    }
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

    Text {
        id: version
        color: "#639ed6"
        anchors.top: timeText.top
        anchors.right: timeText.left
        anchors.rightMargin: 20
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 14
        // text: qsTr("系统版本号") + ": " + "v2.0.1"
        text: GlobalLanguageDefine.strSystemVersion + ": " + GlobalSystemDefine.strVersionNumber
    }
    // 显示时间的文本
    Text {
        id: timeText
        y:718
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 10
        anchors.bottomMargin: 5
        font.pixelSize: 14
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        color: "#639ed6"
        text: GlobalMessageDefine.getCurrentTime()

        // 定时器每秒更新一次
        Timer {
            interval: 1  // 1秒
            repeat: true
            running: true
            onTriggered: {
                timeText.text = GlobalMessageDefine.getCurrentTime()
            }
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            // drag.target: timeDissalog
            onClicked: {
                timeDialog.open()  // 点击时弹出对话框
            }
        }
    }

    TimeSettingDialog {
        id: timeDialog
        onTimeSelected: {
            // 接收 timeDialog 中发出的 timeSelected 信号，并更新 timeText 显示的时间
            let date = new Date(year, month - 1, day, hour, minute, second);  // JavaScript 中月份是从 0 开始的
            timeText.text = date.toLocaleString();  // 将选中的时间转为本地时间字符串
        }
    }
}
