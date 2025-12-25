import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15
import QtQml.Models 2.15
import Device 1.0

import QmlEnum 1.0
import GlobalMessageDefine  1.0
import GlobalSystemDefine   1.0
import DeviceInfoEnum       1.0
import DeviceObj            1.0
import GlobalLanguageDefine 1.0
import ProductionObj        1.0
import ManualObj            1.0
import ManualTable          1.0

Rectangle {
    id: swipe
    color: pRgb(153, 204, 255)
    radius: 5
    readonly property int qmlscreenIndicator: QmlEnum.AUTO_LEARNING_SCREEEN
    property int listSize: 0
    property int currentIndex: DeviceManager.SelectedDeviceIndex
    property int deviceCount: DeviceManager.DeviceCounter
    property bool heightOption: (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption : false
    property ManualObj manualObj: (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ManualObj : null

    Connections{
        target: manualObj
        function onNotifyCurrentSamplesChanged()
        {
            layoutDeviceInfo.sampleCount = manualObj.CurrentSamples
            if(manualObj.CurrentSamples >= manualObj.MaxModelSamples)
            {
                if(!manualObj.isSettingsValid())
                {
                    footer.showError(qsTr("请输入焊接参数！"))
                    return
                }
                manualObj.saveData()
                sigUpdateUI(0)
                sigRecover()
                if(deviceCount === 1)
                    loadViewpro(3, singlePro)
                else
                    loadViewpro(2, multiPro)
            }
        }
    }

    Component.onCompleted: {
        if(manualObj !== null)
        {
            manualObj.CurrentSamples = 0;
        }
    }

    Rectangle {
        id: singleProduction
        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.top: parent.top
        anchors.topMargin: 29
        width: 1220
        height: 664
        color: pRgb(43, 112, 173)
        radius: 5

        EquipmentInfor{
            id: layoutDeviceInfo
            x: 42
            y: 35
            width:  258
            //TODO Need to have a double check
            height: 225
            color: "#0c5696"
            deviceName:{
                if(currentIndex < deviceCount)
                    return DeviceManager.DeviceList[currentIndex].DeviceObj.WelderName
                else
                    return ""
            }
            deviceType:{
                if(currentIndex < deviceCount)
                    return DeviceManager.DeviceList[currentIndex].DeviceObj.WelderType === 0 ? "L20-VG" : "L20-TS"
                    return ""
            }
            connectionType:{
                if(currentIndex < deviceCount)
                    return DeviceManager.DeviceList[currentIndex].DeviceObj.ConnectType === 1 ? "RS232" : "TCP/IP"
                else
                    return ""
            }
            devcieStatus:{
                if(currentIndex < deviceCount)
                {
                    var connectState = DeviceManager.DeviceList[currentIndex].DeviceObj.ConnectState
                    return GlobalMessageDefine.getConnectState(connectState)
                }
                else
                {
                    return ""
                }
            }
            isLearning: true
            sampleCount: {
                if (swipe.currentIndex >= 0 && swipe.currentIndex < swipe.deviceCount)
                    return DeviceManager.DeviceList[swipe.currentIndex].ManualObj.CurrentSamples
                else
                    return 0
            }
        }

        WeldingParameter{
            id: s3_1
            width: 258
            height: 236
            x:42
            y:274
            color:  "#0c5696"
            presetEnergy:           (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ManualObj.EnergySetting : "0"
            presetAmplitude:        (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ManualObj.AmplitudeSetting : "0"
            presetTriggerPressure:  (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ManualObj.TriggerPressureSetting : "0.0"
            presetWeldPressure:     (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ManualObj.WeldPressureSetting : "0.0"
        }

        Button{
            id: s4
            x: 42
            //TODO Need to have a double check
            y: 520
            width:   258
            height:  45
            background: Rectangle{
                radius: 6
                color:  "#0c5696"
            }
            contentItem: Text {
                id: mt1
                text: GlobalLanguageDefine.strCreateModel // return qsTr("创建模型")
                font.pixelSize:  17
                color: pRgb(153, 204, 255)
                anchors.centerIn: parent  // 确保文本在按钮内居中对齐
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: GlobalSystemDefine.fontBold
            }
            onPressed: {
                if(!DeviceManager.DeviceList[currentIndex].ManualObj.isSettingsValid())
                {
                    footer.showError(qsTr("请输入焊接参数！"))
                    return
                }
                console.debug("rowCount: ", DeviceManager.DeviceList[currentIndex].ManualObj.rowCount())
                console.debug("CurrentIndex: ", currentIndex)
                if(DeviceManager.DeviceList[currentIndex].ManualObj.rowCount() >= DeviceManager.DeviceList[currentIndex].DeviceObj.MaxModelSamples)
                {
                    DeviceManager.DeviceList[currentIndex].ManualObj.saveData()
                    sigUpdateUI(0)
                    sigRecover()
                    if(deviceCount === 1)
                        loadViewpro(3, singlePro)
                    else
                        loadViewpro(2, multiPro)
                }
                else
                {
                    popup.openPop(5)
                }
            }
        }
        Button{
            id:s5
            anchors.left: s4.left
            anchors.top: s4.bottom
            anchors.topMargin:  10
            width:   258
            height:  45
            background: Rectangle{
                radius: 6
                border.color: pRgb(43, 112, 173)
                color: "#0c5696"
            }
            contentItem: Text {
                id:mt2
                anchors.centerIn: parent
                // text: qsTr("清除数据")
                text: GlobalLanguageDefine.strClearData
                font.pixelSize: 17
                color: pRgb(153, 204, 255)
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: GlobalSystemDefine.fontBold
            }
            onPressed: {
                DeviceManager.DeviceList[currentIndex].ManualObj.clearData()
            }
        }

        Item {
            Rectangle{
                id:rect
                x: 319
                y: 36
                width:842
                height: 582
                color: "#0c5696"
                radius: 3
            }
            Rectangle{
                width:840
                height: 580
                x: 320
                y: 37
                color: pRgb(43, 112, 173)
                Text{
                    id:t1
                    x:840/7/2+5-width/2
                    y:11
                    font.pixelSize: heightOption ? 10 : 16
                    // text: qsTr("全选")
                    text: GlobalLanguageDefine.strSelectAll
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(153, 204, 255)
                }
                Button{
                    id:bt1
                    width: 30
                    height: 30
                    x:15
                    y:8
                    background: Item {
                        width: parent.width
                        height: parent.height
                        Image {
                            id:im
                            anchors.fill: parent
                            source: {
                                if(DeviceManager.DeviceList[currentIndex].ManualObj.IsSelectedAll === false)
                                    return "qrc:/images/btn_unlock_double_line.png"
                                else
                                    return "qrc:/images/btn_lock_double_line.png"
                            }
                            fillMode: Image.PreserveAspectFit // 保持图片的宽高比，适应按钮大小
                        }
                    }
                    onPressed: {
                        tableFlag = true
                        if(im.source == "qrc:/images/btn_unlock_double_line.png")
                        {
                            im.source = "qrc:/images/btn_lock_double_line.png"
                            DeviceManager.DeviceList[currentIndex].ManualObj.IsSelectedAll = true
                        }
                        else
                        {
                            im.source = "qrc:/images/btn_unlock_double_line.png"
                            DeviceManager.DeviceList[currentIndex].ManualObj.IsSelectedAll = false
                        }
                    }
                }
                Text{
                    id: swipeCycleCountText
                    anchors.left: parent.left
                    anchors.leftMargin: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption === true ? 90 : 140
                    anchors.top: t1.top
                    font.pixelSize: heightOption ? 10 : 16
                    // text: qsTr("序号")
                    text: GlobalLanguageDefine.strCycleCount
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id: swipeWeldingTimeText
                    anchors.top: t1.top
                    anchors.left: parent.left
                    anchors.leftMargin: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption === true ? 160 : 260
                    font.pixelSize: heightOption ? 10 : 16
                    // text: qsTr("焊接时间")
                    text: GlobalLanguageDefine.strWeldingTime + "(s)"
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id: swipePowerText
                    anchors.top: t1.top
                    anchors.left: parent.left
                    anchors.leftMargin: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption === true ? 250 : 400
                    font.pixelSize: heightOption ? 10 : 16
                    // text: qsTr("功率")
                    text: GlobalLanguageDefine.strPower + "(W)"
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id: swipePreHeightText
                    anchors.top: t1.top
                    anchors.left: parent.left
                    anchors.leftMargin: 320
                    font.pixelSize: heightOption ? 10 : 16
                    text: GlobalLanguageDefine.strPreWeldHeight + "(mm)"
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                    visible: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption
                }
                Text{
                    id:swipePostHeightText
                    anchors.top: t1.top
                    anchors.left: parent.left
                    anchors.leftMargin: 430
                    font.pixelSize: heightOption ? 10 : 16
                    text: GlobalLanguageDefine.strPostWeldHeight + "(mm)"
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                    visible: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption
                }
                Text{
                    id:t6
                    x:840/8*5 + 840/8/2-width/2
                    y:11
                    font.pixelSize: heightOption ? 10 : 16
                    // text: qsTr("日期")
                    text: GlobalLanguageDefine.strDate
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id:t7
                    x:840/8*6 + 840/8/2-width/2
                    y:11
                    font.pixelSize: heightOption ? 10 : 16
                    // text: qsTr("拉力")
                    text: GlobalLanguageDefine.strTensile + "(N)"
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id:t8
                    x:840/8*7 + 840/8/2-width/2
                    y:11
                    font.pixelSize: heightOption ? 10 : 16
                    // text: qsTr("残留度")
                    text: GlobalLanguageDefine.strResidual + "(%)"
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                }
                ListView{
                    id: taskplanView
                    width:840
                    height: 535
                    y:40
                    clip: true
                    model: {
                        if (swipe.currentIndex >= 0 && swipe.currentIndex < swipe.deviceCount)
                            return DeviceManager.DeviceList[swipe.currentIndex].ManualObj
                        else
                            return 0
                    }
                    delegate: Rectangle{
                        id: regionItem
                        height: 36
                        width: 840
                        color: index % 2 === 0 ? "#afc3d8" : "#2d71ae"
                        Button{
                            id: bt
                            x:840/8/2-width/2
                            anchors.verticalCenter: parent.verticalCenter
                            width: 30
                            height: 30
                            background: Item {
                                width: parent.width
                                height: parent.height
                                Image {
                                    id:im1
                                    anchors.fill: parent
                                    fillMode: Image.PreserveAspectFit // 保持图片的宽高比，适应按钮大小
                                    source: {
                                        if(index % 2 !== 0)
                                        {
                                            if(is_selected === true)
                                                return "qrc:/images/btn_lock_double_line.png"
                                            else
                                                return "qrc:/images/btn_unlock_double_line.png"
                                        }
                                        else
                                        {
                                            if(is_selected === true)
                                                return "qrc:/images/btn_lock_single_line.png"
                                            else
                                                return "qrc:/images/btn_unlock_single_line.png"
                                        }
                                    }
                                }
                            }

                            onPressed: {
                                var isSelect = false
                                if(im1.source == "qrc:/images/btn_unlock_double_line.png")
                                {
                                    im1.source = "qrc:/images/btn_lock_double_line.png"
                                    isSelect = true
                                }
                                else if(im1.source == "qrc:/images/btn_lock_double_line.png")
                                {
                                    im1.source = "qrc:/images/btn_unlock_double_line.png"
                                    isSelect = false
                                }
                                else if(im1.source == "qrc:/images/btn_lock_single_line.png")
                                {
                                    im1.source = "qrc:/images/btn_unlock_single_line.png"
                                    isSelect = false
                                }
                                else if(im1.source == "qrc:/images/btn_unlock_single_line.png")
                                {
                                    im1.source = "qrc:/images/btn_lock_single_line.png"
                                    isSelect = true
                                }
                                var manualObj = DeviceManager.DeviceList[swipe.currentIndex].ManualObj
                                manualObj.setData(manualObj.index(index, 0), isSelect, ManualTable.IS_SELECTED)
                            }
                        }
                        Connections{
                            target: bt1
                            function onPressed(){
                                if(index % 2 === 0)
                                {
                                    if(im.source == "qrc:/images/btn_unlock_double_line.png")
                                        im1.source = "qrc:/images/btn_unlock_single_line.png"
                                    else
                                        im1.source = "qrc:/images/btn_lock_single_line.png"
                                }
                                else
                                {
                                    if(im.source == "qrc:/images/btn_unlock_double_line.png")
                                        im1.source = "qrc:/images/btn_unlock_double_line.png"
                                    else
                                        im1.source = "qrc:/images/btn_lock_double_line.png"
                                }
                            }
                        }
                        Text{
                            anchors.left: parent.left
                            anchors.leftMargin: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption === true ? 115 : 160
                            anchors.verticalCenter: parent.verticalCenter
                            font.pixelSize: 16
                            text: cycle_count
                            font.family: GlobalSystemDefine.fontBold
                            color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                        }
                        Text{
                            anchors.left: parent.left
                            anchors.leftMargin: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption === true ? 170 : 280
                            anchors.verticalCenter: parent.verticalCenter
                            font.pixelSize: 16
                            text: weld_time
                            font.family: GlobalSystemDefine.fontBold
                            color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                        }
                        Text{
                            anchors.left: parent.left
                            anchors.leftMargin: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption === true ? 270 : 420
                            anchors.verticalCenter: parent.verticalCenter
                            font.pixelSize: 16
                            text: peak_power
                            font.family: GlobalSystemDefine.fontBold
                            color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                        }
                        Text{
                            anchors.left: parent.left
                            anchors.leftMargin: 350
                            anchors.verticalCenter: parent.verticalCenter
                            font.pixelSize: 16
                            text: preheight
                            font.family: GlobalSystemDefine.fontBold
                            color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                            visible: DeviceManager.DeviceList[swipe.currentIndex].DeviceObj.HeightEncoderOption
                        }
                        Text{
                            anchors.left: parent.left
                            anchors.leftMargin: 450
                            anchors.verticalCenter: parent.verticalCenter
                            font.pixelSize: 16
                            text: postheight
                            font.family: GlobalSystemDefine.fontBold
                            color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                            visible: DeviceManager.DeviceList[swipe.currentIndex].DeviceObj.HeightEncoderOption
                        }
                        Text{
                            anchors.verticalCenter: parent.verticalCenter
                            x:840/8*5 + 840/8/2-width/2
                            font.pixelSize: 16
                            text: create_time
                            font.family: GlobalSystemDefine.fontBold
                            color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                        }
                        TextField{
                            id: textField
                            width: 100
                            height: 33
                            anchors.verticalCenter: parent.verticalCenter
                            x:840/8*6 + 840/8/2-width/2
                            horizontalAlignment: TextInput.AlignHCenter
                            verticalAlignment: TextInput.AlignVCenter
                            color: index % 2 === 0 ? "#014c8d" : pRgb(175, 195, 216)
                            font.family: GlobalSystemDefine.fontBold
                            font.pixelSize: 16
                            text: actual_force
                            inputMethodHints: Qt.ImhDigitsOnly
                            background: Rectangle{
                                radius: 3
                                border.width: 2
                                border.color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                                color: index % 2 !== 0 ? "#2d71ae" : "#afc3d8"
                            }
                            cursorDelegate: Rectangle {
                                width: textField.cursorWidth
                                height: textField.font.pixelSize * 1.5
                                color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                                visible: textField.activeFocus
                                anchors.verticalCenter: parent.verticalCenter
                                Text {
                                    text: "|"
                                    color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                                    font.pixelSize: textField.font.pixelSize
                                    anchors.centerIn: parent
                                }
                            }
                            MouseArea {
                                anchors.fill: parent
                                onPressed: {
                                    textField.forceActiveFocus()
                                    window.showPrimaryNumpad(textField.text, " ", 3, 0, 999999, textField.text, textField, function(val)
                                    {
                                        textField.text = val;
                                        var intRegex = /^[0-9]+$/
                                        if (!intRegex.test(textField.text))
                                            footer.showError(t7.text + GlobalLanguageDefine.strInputInterger)
                                        else
                                        {
                                            footer.hideError()
                                            DeviceManager.DeviceList[swipe.currentIndex].ManualObj.setData(
                                                        DeviceManager.DeviceList[swipe.currentIndex].ManualObj.index(index, 0),
                                                        parseInt(textField.text),
                                                        ManualTable.ACTUAL_FORCE
                                                        )
                                        }
                                    })
                                }
                            }
                        }
                        TextField{
                            id: textField1
                            width: 100
                            height: 33
                            anchors.verticalCenter: parent.verticalCenter
                            x:840/8*7 + 840/8/2-width/2
                            horizontalAlignment: TextInput.AlignHCenter
                            verticalAlignment: TextInput.AlignVCenter
                            // color: index % 2 === 0 ? pRgb(175, 195, 216) : "#014c8d"
                            color: index % 2 === 0 ? "#014c8d" : pRgb(175, 195, 216)
                            font.family: GlobalSystemDefine.fontBold
                            font.pixelSize: 16
                            text: actual_residual
                            inputMethodHints: Qt.ImhDigitsOnly
                            background: Rectangle{
                                radius: 3
                                border.width: 2
                                border.color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                                color: index % 2 !== 0 ? "#2d71ae" : "#afc3d8"
                            }
                            cursorDelegate: Rectangle {
                                width: textField1.cursorWidth
                                height: textField1.font.pixelSize * 1.5
                                color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                                visible: textField1.activeFocus
                                anchors.verticalCenter: parent.verticalCenter
                                Text {
                                    text: "|"
                                    color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                                    font.pixelSize: textField1.font.pixelSize
                                    anchors.centerIn: parent
                                }
                            }
                            MouseArea {
                                anchors.fill: parent
                                onPressed: {
                                    textField1.forceActiveFocus()
                                    window.showPrimaryNumpad(t8.text, " ", 3, 0, 999999, textField1.text, textField1, function(val)
                                    {
                                        textField1.text = val;
                                        var intRegex = /^[0-9]+$/
                                        if (!intRegex.test(textField1.text))
                                            footer.showError(t8.text + GlobalLanguageDefine.strInputInterger)
                                        else
                                        {
                                            footer.hideError()
                                            DeviceManager.DeviceList[swipe.currentIndex].ManualObj.setData(
                                                        DeviceManager.DeviceList[swipe.currentIndex].ManualObj.index(index, 0),
                                                        parseInt(textField1.text),
                                                        ManualTable.ACTUAL_RESIDUAL
                                                        )
                                        }
                                    })
                                }
                            }
                        }
                    }
                }
            }
        }

    }
}
