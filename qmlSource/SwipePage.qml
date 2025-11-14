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

// import Manual 1.0

Rectangle {
    id: swipe
    color: pRgb(153, 204, 255)
    radius: 5
    property int listSize: 0
    // property int swipeCurrIndex: -1
    property int currentIndex: DeviceManager.SelectedDeviceIndex
    property int deviceCount: DeviceManager.DeviceCounter
    property bool heightOption: (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption : false
    function newModel()
    {
        loader.sourceComponent = mode2
        loader1.sourceComponent = weld2
    }

    Connections{
        target: window
        function onSigNewModel(){
            newModel()
            createModel = true
        }
    }
    EquipmentInfor{
        id:s1
        x:42
        y:35
        width:  258
        //TODO Need to have a double check
        height: (mt1.text === "新建模型" || mt1.text === "New Model") ? 255 : 225
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
    }

    Loader{
        id:loader1
        asynchronous: true
        sourceComponent: weld1
    }
    Component{
        id: weld1
        Item {
            WeldingResult{
                id:s3
                width: 258
                height: 246
                x:42
                y:314
                color: "#0c5696"
                heightOption:       (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption : false
                energy:             (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ProductionObj.Energy : 0
                amplitude:          (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ProductionObj.Amplitude : 0
                weldPressure:       (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ProductionObj.WeldPressure : 0
                triggerPressure:    (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ProductionObj.TriggertPressure : 0
                peakPower:          (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ProductionObj.PeakPower : 0
                weldTime:           (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ProductionObj.WeldTime : 0
                preheight:          (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ProductionObj.Preheight : 0
                postHeight:         (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ProductionObj.PostHeight : 0

            }
        }
    }
    Component{
        id:weld2
        Item {
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
        }
    }
    Button{
        id:s4
        x: 42
        //TODO Need to have a double check
        y: (mt1.text === "新建模型" || mt1.text === "New Model") ? 580 : 520
        width:   258
        height:  45
        background: Rectangle{
            radius: 6
            color:  "#0c5696"
        }
        contentItem: Text {
            id: mt1
            text:
            {
                if(createModel)
                    return GlobalLanguageDefine.strCreateModel // return qsTr("创建模型")
                else
                    return GlobalLanguageDefine.strNewModel // return qsTr("新建模型")
            }
            font.pixelSize:  17
            color: pRgb(153, 204, 255)
            anchors.centerIn: parent  // 确保文本在按钮内居中对齐
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: GlobalSystemDefine.fontBold
        }
        onPressed: {
            // if(mt1.text === qsTr("新建模型"))
            if(mt1.text === GlobalLanguageDefine.strNewModel)
            {
                console.debug("Welder ID: ", currentIndex)
                popup.openPop(2)
            }
            // else if(mt1.text === qsTr("创建模型"))
            else if(mt1.text === GlobalLanguageDefine.strCreateModel)
            {
                if(!DeviceManager.DeviceList[currentIndex].ManualObj.isSettingsValid())
                {
                    footer.showError(qsTr("请输入焊接参数！"))
                    return
                }
                console.debug("rowCount: ", DeviceManager.DeviceList[currentIndex].ManualObj.rowCount())
                console.debug("CurrentIndex: ", currentIndex)
                if(DeviceManager.DeviceList[currentIndex].ManualObj.rowCount() >= DeviceManager.DeviceList[currentIndex].DeviceObj.MaxModelSamples)
                {
                    loader.sourceComponent = mode1
                    loader1.sourceComponent = weld1
                    DeviceManager.DeviceList[currentIndex].ManualObj.saveData()
                    sigUpdateUI(0)
                    sigRecover()
                    createModel = false
                }
                else
                {
                    popup.openPop(5)
                }
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
        // visible: (mt1.text === qsTr("创建模型")) ? true : false
        visible: (mt1.text === GlobalLanguageDefine.strCreateModel) ? true : false
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
    Loader{
        id:loader
        asynchronous: true
        sourceComponent: mode1
    }

    Component{
        id: mode1
        Item {
            x:0
            RealtimeYield{
                id:s2
                width:  300
                height:  255
                x: 329
                y: 35
                color:  "#0c5696"
                revealing:{
                    if(currentIndex < deviceCount)
                        return DeviceManager.DeviceList[currentIndex].DeviceObj.SuspiciousOption
                    else
                        return true
                }
                eqText1:{
                    if(currentIndex < deviceCount)
                        return DeviceManager.DeviceList[currentIndex].ProductionObj.GoodCycleCount
                    else
                        return ""
                }
                eqText2:{
                    if(currentIndex < deviceCount)
                        return DeviceManager.DeviceList[currentIndex].ProductionObj.SuspectCycleCount
                    else
                        return ""
                }
                eqText3:{
                    if(currentIndex < deviceCount)
                        return DeviceManager.DeviceList[currentIndex].ProductionObj.DefectiveCycleCount
                    else
                        return ""
                }
                eqText4:{
                    if(currentIndex < deviceCount)
                    {
                        return DeviceManager.DeviceList[currentIndex].ProductionObj.GoodCycleCount
                                + DeviceManager.DeviceList[currentIndex].ProductionObj.SuspectCycleCount
                                +DeviceManager.DeviceList[currentIndex].ProductionObj.DefectiveCycleCount
                    }
                    else{
                        return ""
                    }
                }
                eqText5:{
                    if(currentIndex < deviceCount)
                        return DeviceManager.DeviceList[currentIndex].ProductionObj.GoodRate
                    else
                        return ""
                }
            }
            YieldTrend{
                id:s6
                width:  514
                height:  255
                x: 658
                y: 35
                color:  "#0c5696"
                equiInforIndex:1
            }
            WeldingTrend{
                id:s7
                width:  502
                height:  311
                x: 329
                y: 314
                color:  "#0c5696"
            }
            AbnormalInfor{
                id:s8
                width:  313
                height:  311
                x: 858
                y: 314
                color:  "#0c5696"
            }
        }
    }
    Component{
        id: mode2
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
                    font.pixelSize: 16
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
                            source: "qrc:/images/btn_unlock_double_line.png"
                            fillMode: Image.PreserveAspectFit // 保持图片的宽高比，适应按钮大小
                        }
                    }
                    onPressed: {
                        tableFlag = true
                        if(im.source == "qrc:/images/btn_unlock_double_line.png"){
                            im.source = "qrc:/images/btn_lock_double_line.png"
                        }
                        else{
                            im.source = "qrc:/images/btn_unlock_double_line.png"
                        }
                    }
                }
                Text{
                    id: swipeCycleCountText
                    anchors.left: parent.left
                    anchors.leftMargin: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption === true ? 90 : 140
                    anchors.top: t1.top
                    font.pixelSize: 16
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
                    font.pixelSize: 16
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
                    font.pixelSize: 16
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
                    font.pixelSize: 16
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
                    font.pixelSize: 16
                    text: GlobalLanguageDefine.strPostWeldHeight + "(mm)"
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                    visible: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption
                }
                Text{
                    id:t6
                    x:840/8*5 + 840/8/2-width/2
                    y:11
                    font.pixelSize: 16
                    // text: qsTr("日期")
                    text: GlobalLanguageDefine.strDate
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id:t7
                    x:840/8*6 + 840/8/2-width/2
                    y:11
                    font.pixelSize: 16
                    // text: qsTr("拉力")
                    text: GlobalLanguageDefine.strTensile + "(N)"
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id:t8
                    x:840/8*7 + 840/8/2-width/2
                    y:11
                    font.pixelSize: 16
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
                                    keyboardType = 0
                                }
                            }
                            onEditingFinished: {
                                 var intRegex = /^[0-9]+$/
                                 if (!intRegex.test(textField.text))
                                     footer.showError(t7.text + GlobalLanguageDefine.strInputInterger)
                                 else
                                     footer.hideError()
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
                                    keyboardType = 0
                                }
                            }
                            onEditingFinished: {
                                 var intRegex = /^[0-9]+$/
                                 if (!intRegex.test(textField1.text))
                                     footer.showError(t8.text + GlobalLanguageDefine.strInputInterger)
                                 else
                                     footer.hideError()
                             }
                        }
                    }
                }
            }
        }
    }
}
