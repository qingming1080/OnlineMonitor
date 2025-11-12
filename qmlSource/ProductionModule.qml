import QtQuick 2.15
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15
import Device 1.0

import QmlEnum 1.0
import GlobalLanguageDefine 1.0
import GlobalSystemDefine   1.0
import GlobalMessageDefine  1.0
import DeviceInfoEnum       1.0
import DeviceObj            1.0
import ProductionObj        1.0

Rectangle {
    id:mpro
    color: pRgb(153, 204, 255)
    property bool tableFlag: false
    property var proViews: []
    property int rect1: 1
    property int rect2: 1

    property int currentIndex: DeviceManager.SelectedDeviceIndex
    property int equipmentCount: -1
    property int listSize: 0
    property bool altitudeMode: DeviceManager.DeviceList[0].DeviceObj.HeightEncoderOption === 1 ? true : false
    property bool switchingEquipment: false
    signal sigBtnSynchronization(var index,var time)

    onRect1Changed: {
        sigBtnSynchronization(1,rect1)
    }
    onRect2Changed: {
        sigBtnSynchronization(2,rect2)
    }

    function loadViewpro(viewName, component)
    {
        if(viewName === 3){
            switchingEquipment = true
        }
        else{
            switchingEquipment = false
        }

        // prostack.pop()
        // if (proViews[viewName]) {
        //     // 如果视图已缓存，直接显示
        //     prostack.push(proViews[viewName]);
        // } else {
        //     // 创建视图并缓存
        //     var newItem = component.createObject(prostack);
        //     proViews[viewName] = newItem;
        //     prostack.push(newItem);
        // }
        prostack.clear();
        var newItem = component.createObject(prostack);
        proViews[viewName] = newItem;
        prostack.push(newItem);
    }

    Component.onCompleted: {
        loadViewpro(3, swipe)
        if(DeviceManager.DeviceCounter > 1)
        {
            mode = 1
            loadViewpro(2, multipro)
        }
        else
        {
            mode = 0
            loadViewpro(1, autopro)
        }
    }

    Connections{
        target: DeviceManager
        function onNotifyDeviceCounterChanged()
        {
            if(DeviceManager.DeviceCounter > 1)
            {
                mode = 1
                loadViewpro(2, multipro)
            }
            else
            {
                mode = 0
                loadViewpro(1, autopro)
            }
        }
    }

    StackView{
        id: prostack
    }
    Component{
        id: autopro
        Item{
            Connections{
                target: window
                function onSigOneModel(){
                    // mt1.text = qsTr("创建模型")
                    mt1.text = GlobalLanguageDefine.strCreateModel
                    // mt2.text = qsTr("清除数据")
                    mt2.text = GlobalLanguageDefine.strClearData
                    loader.sourceComponent = mode2
                    loader1.sourceComponent = weld2
                }
            }

            EquipmentInfor{
                id: s1
                x: mode == 1 ? 52 : 29
                y: mode == 1 ? 35 : 20
                width: mode == 1 ? 208 : 243
                height: mode == 1 ? 203 : 258
                color: mode == 1 ? "#0c5696" : pRgb(43, 112, 173)
                deviceName: DeviceManager.DeviceList[0].DeviceObj.WelderName
                deviceType: DeviceManager.DeviceList[0].DeviceObj.WelderType === 0 ? "L20-VG" : "L20-TS"
                connectionType: DeviceManager.DeviceList[0].DeviceObj.ConnectType === 1 ? "RS232" : "TCP/IP"
                devcieStatus:{
                    var connectState = DeviceManager.DeviceList[0].DeviceObj.ConnectState
                    return GlobalMessageDefine.getConnectState(connectState)
                }
            }

            Loader{
                id:loader1
                sourceComponent: weld1
            }
            Component{
                id:weld1
                Item {
                    WeldingResult{
                        id:s3
                        width: mode == 1 ? 212 : 245
                        height: mode == 1 ? 215 : 249
                        x: mode == 1 ? 50 : 29
                        y: mode == 1 ? 248 : 289
                        color: mode == 1 ? "#0c5696" : pRgb(43, 112, 173)
                        altitudeMode:       DeviceManager.DeviceList[[0]] ? DeviceManager.DeviceList[[0]].DeviceObj.HeightEncoderOption : fasle
                        energy:             DeviceManager.DeviceList[[0]] ? DeviceManager.DeviceList[[0]].ProductionObj.Energy : 0
                        amplitude:          DeviceManager.DeviceList[[0]] ? DeviceManager.DeviceList[[0]].ProductionObj.Amplitude : 0
                        weldPressure:       DeviceManager.DeviceList[[0]] ? DeviceManager.DeviceList[[0]].ProductionObj.WeldPressure : 0
                        triggerPressure:    DeviceManager.DeviceList[[0]] ? DeviceManager.DeviceList[[0]].ProductionObj.TriggertPressure : 0
                        peakPower:          DeviceManager.DeviceList[[0]] ? DeviceManager.DeviceList[[0]].ProductionObj.PeakPower : 0
                        weldTime:           DeviceManager.DeviceList[[0]] ? DeviceManager.DeviceList[[0]].ProductionObj.WeldTime : 0
                        preheight:          DeviceManager.DeviceList[[0]] ? DeviceManager.DeviceList[[0]].ProductionObj.Preheight : 0
                        postHeight:         DeviceManager.DeviceList[[0]] ? DeviceManager.DeviceList[[0]].ProductionObj.PostHeight : 0
                    }
                }
            }
            Component{
                id:weld2
                Item {
                    WeldingParameter{
                        id:s3_1
                        width: mode == 1 ? 212 : 245
                        height: mode == 1 ? 215 : 249
                        x: mode == 1 ? 50 : 29
                        y: mode == 1 ? 248 : 289
                        color: mode == 1 ? "#0c5696" : pRgb(43, 112, 173)
                        presetEnergyValue:          DeviceManager.DeviceList[0].ProductionObj.Energy
                        presetAmplitudeValue:       DeviceManager.DeviceList[0].ProductionObj.Amplitude
                        presetWeldPressureValue:    DeviceManager.DeviceList[0].ProductionObj.WeldPressure
                        presetTriggerPressureValue: DeviceManager.DeviceList[0].ProductionObj.TriggertPressure

                    }
                }
            }
            Button{
                id:s4
                x:mode == 1 ? 50 : 31
                y:mode == 1 ? 482 : 553
                width: mode == 1 ?  210 :243
                height: mode == 1 ? 45 : 52
                background: Rectangle{
                    radius: 6
                    color: mode == 1 ? "#0c5696" : pRgb(43, 112, 173)
                }
                contentItem: Text {
                    id: mt1
                    // text: "新建模型"
                    text: GlobalLanguageDefine.strNewModel
                    font.pixelSize: mode == 1 ? 17:20
                    color: pRgb(153, 204, 255)
                    anchors.centerIn: parent  // 确保文本在按钮内居中对齐
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.family: GlobalSystemDefine.fontBold
                }
                onPressed: {
                    // if(mt1.text === "新建模型")
                    if(mt1.text === GlobalLanguageDefine.strNewModel)
                    {
                        popup.openPop(3)
                    }
                    // else if(mt1.text === "创建模型")
                    else if(mt1.text === GlobalLanguageDefine.strCreateModel)
                    {
                        if(DeviceManager.DeviceList[0].DeviceObj.YieldRateLowerLimit <= listSize)
                        {
                            loader.sourceComponent = mode1
                            loader1.sourceComponent = weld1
                            Manual.save()
                            console.log("Pressed, mt1.text:", mt1.text)
                            // mt1.text = "新建模型"
                            mt1.text = GlobalLanguageDefine.strNewModel
                            // mt2.text = "新增设备"
                            mt2.text = GlobalLanguageDefine.strAddDevice
                            sigUpdateUI(0)
                        }
                        else{
                            popup.openPop(5)
                        }
                    }
                }
            }

            Button{
                id:s5
                anchors.left: s4.left
                anchors.top: s4.bottom
                anchors.topMargin: mode == 1 ? 23 : 31
                width: mode == 1 ?  210 :243
                height: mode == 1 ? 45 : 52
                background: Rectangle{
                    radius: 6
                    color: mode == 1 ? "#0c5696" : pRgb(43, 112, 173)
                }
                contentItem: Text {
                    id:mt2
                    anchors.centerIn: parent
                    // text: qsTr("新增设备")
                    text: GlobalLanguageDefine.strAddDevice
                    font.pixelSize:mode == 1 ? 17: 20
                    color: pRgb(153, 204, 255)
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.family: GlobalSystemDefine.fontBold
                }
                onPressed: {
                    // if(mt2.text == "新增设备")
                    if(mt2.text === GlobalLanguageDefine.strAddDevice)
                    {
                        popup.openPop(8)
                    }
                    else if(mt2.text === GlobalLanguageDefine.strClearData)
                    {
                        Manual.clearData()
                    }
                }
            }
            Loader{
                id:loader
                sourceComponent: mode1
            }

            Component{
                id:mode1
                Item {
                    x:0
                    RealtimeYield{
                        id:s2
                        width: mode === 1 ? 288:346
                        height: mode === 1 ? 235:283
                        x:mode === 1 ? 269:286
                        y:mode === 1 ? 35:20
                        color: mode === 1 ? "#0c5696" : pRgb(43, 112, 173)
                        revealing: DeviceManager.DeviceList[0].DeviceObj.SuspiciousOption

                        eqText1:{
                            if(DeviceManager.DeviceList[0]){
                                return DeviceManager.DeviceList[0].ProductionObj.GoodCycleCount
                            }
                            else{
                                return ""
                            }
                        }
                        eqText2:{
                            if(DeviceManager.DeviceList[0]){
                                return DeviceManager.DeviceList[0].ProductionObj.SuspectCycleCount
                            }
                            else{
                                return ""
                            }
                        }
                        eqText3:{
                            if(DeviceManager.DeviceList[0]){
                                return DeviceManager.DeviceList[0].ProductionObj.DefectiveCycleCount
                            }
                            else{
                                return ""
                            }
                        }
                        eqText4:{
                            if(DeviceManager.DeviceList[0]){
                                return DeviceManager.DeviceList[0].ProductionObj.GoodCycleCount
                                        + DeviceManager.DeviceList[0].ProductionObj.SuspectCycleCount
                                        +DeviceManager.DeviceList[0].ProductionObj.DefectiveCycleCount
                            }
                            else{
                                return ""
                            }
                        }
                        eqText5:{
                            if(DeviceManager.DeviceList[0]){
                                return DeviceManager.DeviceList[0].ProductionObj.GoodRate
                            }
                            else{
                                return ""
                            }
                        }
                    }
                    YieldTrend{
                        id:s6
                        width: mode === 1 ? 514:609
                        height: mode === 1 ? 235:283
                        x:mode === 1 ? 568:645
                        y:mode === 1 ? 35:20
                        color: mode === 1 ? "#0c5696" : pRgb(43, 112, 173)
                        equiInforIndex:1
                    }
                    WeldingTrend{
                        id:s7
                        width: mode === 1 ? 502:596
                        height: mode === 1 ? 311:370
                        x:mode === 1 ? 269:286
                        y:mode === 1 ? 284:318
                        color: mode === 1 ? "#0c5696" : pRgb(43, 112, 173)
                    }
                    AbnormalInfor{
                        id:s8
                        width: mode === 1 ? 303:359
                        height: mode === 1 ? 311:370
                        x:mode === 1 ? 778:895
                        y:mode === 1 ? 284:318
                        color: mode === 1 ? "#0c5696" : pRgb(43, 112, 173)
                    }
                }
            }

            Component{
                id:mode2
                Item {
                    Rectangle{
                        id:rect
                        x:mode === 1 ? 269:287
                        y:mode === 1 ? 36:20
                        width: mode === 1 ? 812 : 964
                        height: mode === 1 ? 560:668
                        color: mode === 1 ? "#0c5696" : pRgb(43, 112, 173)
                        radius: 3
                    }
                    Rectangle{
                        width: mode === 1 ? 808:960
                        height: mode === 1 ? 556:664
                        x:mode === 1 ? 272:289
                        y:mode === 1 ? 37:22
                        color: pRgb(43, 112, 173)
                        Text{
                            id:t1
                            x:808/7/2+5-width/2
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
                            id: titleSerialNumberText
                            anchors.top: t1.top
                            anchors.left: t1.right
                            anchors.leftMargin: altitudeMode ? 50 : 100
                            font.pixelSize: 16
                            // text: qsTr("序号")
                            text: GlobalLanguageDefine.strSerialNumber
                            font.family: GlobalSystemDefine.fontBold
                            color: pRgb(171, 206, 213)
                        }
                        Text{
                            id: titleWeldTimeText
                            anchors.top: t1.top
                            anchors.left: titleSerialNumberText.right
                            anchors.leftMargin: altitudeMode? 50 : 100
                            font.pixelSize: 16
                            // text: qsTr("焊接时间")
                            text: GlobalLanguageDefine.strWeldingTime
                            font.family: GlobalSystemDefine.fontBold
                            color: pRgb(171, 206, 213)
                        }
                        Text{
                            id: titlePowerText
                            anchors.top: t1.top
                            anchors.left: titleWeldTimeText.right
                            anchors.leftMargin:  altitudeMode? 50 : 120
                            font.pixelSize: 16
                            // text: qsTr("功率")
                            text: GlobalLanguageDefine.strPower
                            font.family: GlobalSystemDefine.fontBold
                            color: pRgb(171, 206, 213)
                        }
                        // TODO   当时高度模式开启时显示高度结果
                        Text{
                            id: titlePreheightText
                            anchors.top: t1.top
                            anchors.left: titlePowerText.right
                            anchors.leftMargin:  altitudeMode ? 50 : 0
                            font.pixelSize: 16
                            text: GlobalLanguageDefine.strPreWeldHeight
                            font.family: GlobalSystemDefine.fontBold
                            color: pRgb(171, 206, 213)
                            visible: altitudeMode ? 1 : 0
                        }
                        Text{
                            id: titlePostheightText
                            anchors.top: t1.top
                            anchors.left: titlePreheightText.right
                            anchors.leftMargin: altitudeMode ? 50 : 0
                            font.pixelSize: 16
                            text: GlobalLanguageDefine.strPostWeldHeight
                            font.family: GlobalSystemDefine.fontBold
                            color: pRgb(171, 206, 213)
                            visible: altitudeMode ? 1 : 0
                        }
                        Text{
                            id: titleDateText
                            anchors.top: t1.top
                            anchors.left: titlePostheightText.right
                            anchors.leftMargin: altitudeMode ? 65 : 0
                            font.pixelSize: 16
                            // text: qsTr("日期")
                            text: GlobalLanguageDefine.strDate
                            font.family: GlobalSystemDefine.fontBold
                            color: pRgb(171, 206, 213)
                        }
                        Text{
                            id: titleTensileText
                            anchors.top: t1.top
                            anchors.left: titleDateText.right
                            anchors.leftMargin: altitudeMode ? 85 :75
                            font.pixelSize: 16
                            // text: qsTr("拉力")
                            text: GlobalLanguageDefine.strTensile
                            font.family: GlobalSystemDefine.fontBold
                            color: pRgb(171, 206, 213)
                        }
                        Text{
                            id: residualText
                            anchors.top: t1.top
                            anchors.left: titleTensileText.right
                            anchors.leftMargin: altitudeMode ? 70 : 70
                            font.pixelSize: 16
                            // text: qsTr("残留度")
                            text: GlobalLanguageDefine.strResidual
                            font.family: GlobalSystemDefine.fontBold
                            color: pRgb(171, 206, 213)
                        }

                        ListView{
                            id: taskplanView
                            width: 960
                            height: 615
                            y:40
                            clip: true
                            model: Manual
                            onCountChanged:{
                                listSize = taskplanView.count
                            }
                            delegate: Rectangle{
                                id: regionItem
                                height: 36
                                width: 960
                                color: index % 2 === 0 ? "#afc3d8" : "#2d71ae"
                                // MouseArea {
                                //     id: mouseArea
                                //     anchors.fill: parent
                                //     onPressed: {
                                //         taskplanView.currentIndex   = index
                                //         presetEnergy                = Manual.data(Manual.index(index,0),QmlEnum.MANUAL_preEnergy)
                                //         presetAmplitude             = Manual.data(Manual.index(index,0),QmlEnum.MANUAL_preAmplitude)
                                //         presetWeldPressure          = Manual.data(Manual.index(index,0),QmlEnum.MANUAL_preWP)
                                //         presetTriggerPressure       = Manual.data(Manual.index(index,0),QmlEnum.MANUAL_preTP)
                                //     }
                                // }
                                Button{
                                    id:bt
                                    x:960/8/2-width/2
                                    anchors.verticalCenter: parent.verticalCenter
                                    width: 30
                                    height: 30
                                    background: Item {
                                        width: parent.width
                                        height: parent.height
                                        Image {
                                            id:im1
                                            anchors.fill: parent
                                            source: index % 2 !== 0 ? "qrc:/images/btn_lock_double_line.png" : "qrc:/images/btn_lock_single_line.png"
                                            fillMode: Image.PreserveAspectFit // 保持图片的宽高比，适应按钮大小
                                        }
                                    }
                                    onPressed: {

                                        if(im1.source == "qrc:/images/btn_unlock_double_line.png"){
                                            im1.source = "qrc:/images/btn_lock_double_line.png"
                                        }
                                        else if(im1.source == "qrc:/images/btn_lock_double_line.png"){
                                            im1.source = "qrc:/images/btn_unlock_double_line.png"
                                        }
                                        else if(im1.source == "qrc:/images/btn_lock_single_line.png"){
                                            im1.source = "qrc:/images/btn_unlock_single_line.png"
                                        }
                                        else if(im1.source == "qrc:/images/btn_unlock_single_line.png"){
                                            im1.source = "qrc:/images/btn_lock_single_line.png"
                                        }

                                    }
                                }
                                Connections{
                                    target: bt1
                                    function onPressed(){
                                        if(index % 2 === 0){
                                            if(im.source == "qrc:/images/btn_unlock_double_line.png"){
                                                im1.source = "qrc:/images/btn_unlock_single_line.png"
                                            }
                                            else{
                                                im1.source = "qrc:/images/btn_lock_single_line.png"
                                            }
                                        }
                                        else{
                                            if(im.source == "qrc:/images/btn_unlock_double_line.png"){
                                                im1.source = "qrc:/images/btn_unlock_double_line.png"
                                            }
                                            else{
                                                im1.source = "qrc:/images/btn_lock_double_line.png"
                                            }
                                        }
                                    }
                                }
                                Text{
                                    anchors.left: parent.left
                                    anchors.leftMargin: altitudeMode ? 140 : 180
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.pixelSize: 16
                                    text: cycle_count
                                    font.family: GlobalSystemDefine.fontBold
                                    color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                                }
                                Text{
                                    anchors.left: parent.left
                                    anchors.leftMargin: altitudeMode ? 220 : 320
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.pixelSize: 16
                                    text: UtilityFunction.displayValue(time,100,2) + GlobalLanguageDefine.strWeldTimeUnit
                                    font.family: GlobalSystemDefine.fontBold
                                    color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                                }
                                Text{
                                    anchors.left: parent.left
                                    anchors.leftMargin: altitudeMode ? 320 : 485
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.pixelSize: 16
                                    text: UtilityFunction.displayValue(power) + GlobalLanguageDefine.strPowerUnit
                                    font.family: GlobalSystemDefine.fontBold
                                    color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                                }
                                //TODO preheight postheight
                                Text{
                                    anchors.left: parent.left
                                    anchors.leftMargin: 410
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.pixelSize: 16
                                    text: UtilityFunction.displayValue(preheight,100,2) +  GlobalLanguageDefine.strHeightUnit
                                    font.family: GlobalSystemDefine.fontBold
                                    color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                                    visible: altitudeMode ? 1 : 0
                                }
                                Text{
                                    anchors.left: parent.left
                                    anchors.leftMargin: 520
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.pixelSize: 16
                                    text: UtilityFunction.displayValue(postheight,100,2) +  GlobalLanguageDefine.strHeightUnit
                                    font.family: GlobalSystemDefine.fontBold
                                    color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                                    visible: altitudeMode ? 1 : 0
                                }

                                Text{
                                    anchors.verticalCenter: parent.verticalCenter
                                    x: 960/8*5 + 960/8/2-width/2
                                    font.pixelSize: 16
                                    text: UtilityFunction.timestampToString(create_time).split(" ")[0]
                                    font.family: GlobalSystemDefine.fontBold
                                    color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                                }
                                TextField{
                                    id: textField
                                    width: 100
                                    height: 33
                                    anchors.verticalCenter: parent.verticalCenter
                                    x: 960/8*6 + 960/8/2-width/2
                                    horizontalAlignment: TextInput.AlignHCenter
                                    verticalAlignment: TextInput.AlignVCenter
                                    //color: index % 2 === 0 ? pRgb(175, 195, 216) : "#014c8d"
                                    color: index % 2 === 0 ? "#014c8d" : pRgb(175, 195, 216)
                                    font.family: GlobalSystemDefine.fontBold
                                    font.pixelSize: 16
                                    text:actual_force /*+ GlobalLanguageDefine.strActualForceUnit*/
                                    inputMethodHints: Qt.ImhDigitsOnly
                                    background: Rectangle{
                                        radius: 3
                                        border.width: 2
                                        border.color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                                        color: index % 2 !== 0 ? "#2d71ae" : "#afc3d8"
                                    }
                                    cursorDelegate: Rectangle {
                                        width: textField.cursorWidth
                                        height: textField.font.pixelSize * 1.1
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
                                             footer.showError(titleTensileText.text + GlobalLanguageDefine.strInputInterger)
                                         else
                                             footer.hideError()
                                     }
                                }
                                TextField{
                                    id: textField1
                                    width: 100
                                    height: 33
                                    anchors.verticalCenter: parent.verticalCenter
                                    x: 960/8*7 + 960/8/2-width/2
                                    horizontalAlignment: TextInput.AlignHCenter
                                    verticalAlignment: TextInput.AlignVCenter
                                    //color: index % 2 === 0 ? pRgb(175, 195, 216) : "#014c8d"
                                    color: index % 2 === 0 ? "#014c8d" : pRgb(175, 195, 216)
                                    font.family: GlobalSystemDefine.fontBold
                                    font.pixelSize: 16
                                    text:actual_degree /*+ GlobalLanguageDefine.strActualDegreeUnit*/
                                    inputMethodHints: Qt.ImhDigitsOnly
                                    background: Rectangle{
                                        radius: 6
                                        border.width: 3
                                        border.color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                                        color: index % 2 !== 0 ? "#2d71ae" : "#afc3d8"
                                    }
                                    cursorDelegate: Rectangle {
                                        width: textField1.cursorWidth
                                        height: textField.font.pixelSize * 1.1
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
                                             footer.showError(residualText.text + GlobalLanguageDefine.strInputInterger)
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
    }

    Component{
        id: multipro
        MultideviceProductionModule{
            id: mupMode
            width: 1280
            height: 740
            itemCount:DeviceManager.DeviceCounter
        }
    }

    Component{
        id:swipe
        SwipeProductionModule{
            id: mupMode
            width: 1280
            height: 740
        }
    }

}
