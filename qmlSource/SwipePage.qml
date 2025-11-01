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
// import Manual 1.0

Rectangle {
    color: pRgb(153, 204, 255)
    radius: 5
    property int listSize: 0
    property int parameter1: 0
    property int parameter2: 0
    property int parameter3: 0
    property int parameter4: 0
    property int parameter5: 0
     property bool altitudeMode:DeviceManager.DeviceList[swipeCurrIndex].DeviceObj.heightOption === 1 ? true:false
    function newModel(){
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
 //  TEST 2024_08_18
    // Button{
    //     height: 50
    //     width: 100
    //     text: "刷新"
    //     onClicked: DeviceManager.DeviceList[swipeCurrIndex].test()
    // }
    EquipmentInfor{
        id:s1
        x:42
        y:35
        width:  258
        //TODO Need to have a double check
        height: (mt1.text === "新建模型" || mt1.text === "New Model") ? 255 : 225
        color: "#0c5696"
        eqText1:{
            if(DeviceManager.DeviceList[swipeCurrIndex]){
                return DeviceManager.DeviceList[swipeCurrIndex].DeviceObj.name
            }
            else{
                return ""
            }
        }
        eqText2:{
            if(DeviceManager.DeviceList[swipeCurrIndex]){
                return DeviceManager.DeviceList[swipeCurrIndex].DeviceObj.model
            }
            else{
                return ""
            }
        }
        eqText3:{
            if(DeviceManager.DeviceList[swipeCurrIndex]){
                return DeviceManager.DeviceList[swipeCurrIndex].DeviceObj.ConnectType === 1
                        ? "RS232" : "TCP/IP"
            }
            else{
                return ""
            }
        }
        eqText4:{
            if(DeviceManager.DeviceList[swipeCurrIndex])
            {
                var connectState = DeviceManager.DeviceList[swipeCurrIndex].DeviceObj.ConnectState
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
        asynchronous:true
        sourceComponent: weld1
    }
    Component{
        id:weld1
        Item {
            WeldingResult{
                id:s3
                width:  258
                height:  246
                x:42
                y:314
                color: "#0c5696"

                eqText1: DeviceManager.DeviceList[swipeCurrIndex] ? DeviceManager.DeviceList[swipeCurrIndex].DeviceObj.power : ""

                eqText2: DeviceManager.DeviceList[swipeCurrIndex] ? DeviceManager.DeviceList[swipeCurrIndex].DeviceObj.time  : ""

                eqText3: DeviceManager.DeviceList[swipeCurrIndex] ? DeviceManager.DeviceList[swipeCurrIndex].DeviceObj.energy  : ""

                eqText4: DeviceManager.DeviceList[swipeCurrIndex]  ? DeviceManager.DeviceList[swipeCurrIndex].DeviceObj.heightPre : ""

                eqText5: DeviceManager.DeviceList[swipeCurrIndex]   ? DeviceManager.DeviceList[swipeCurrIndex].DeviceObj.heightPost : ""

            }
        }
    }
    Component{
        id:weld2
        Item {
            WeldingParameter{
                id:s3_1
                width:  258
                height:  236
                x:42
                y:274
                color:  "#0c5696"
                eqText1:parameter1
                eqText2:parameter2
                eqText3:parameter3
                eqText4:parameter4
                eqText5:parameter5
            }
        }
    }
    Button{
        id:s4
        x: 42
        //TODO Need to have a double check
        y: (mt1.text === "新建模型" || mt1.text === "New Model") ? 580 :520
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
                {
                    // return qsTr("创建模型")
                    return GlobalLanguageDefine.strCreateModel
                }
                else
                {
                    // return qsTr("新建模型")
                    return GlobalLanguageDefine.strNewModel
                }
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
                Manual.setWelderID(swipeCurrIndex + 1)
                Manual.startReading()
                popup.openPop(2)
            }
            // else if(mt1.text === qsTr("创建模型"))
            else if(mt1.text === GlobalLanguageDefine.strCreateModel)
            {
                console.debug("rowCount: ", Manual.rowCount())
                console.debug("CurrentIndex: ", swipeCurrIndex)
                if(DeviceManager.DeviceList[swipeCurrIndex].DeviceObj.sample <= Manual.rowCount())
                {
                    loader.sourceComponent = mode1
                    loader1.sourceComponent = weld1
                    Manual.save()
                    Manual.stopReading()
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
            Manual.clearData()
        }
    }
    Loader{
        id:loader
        asynchronous:true
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
                    if(DeviceManager.DeviceList[swipeCurrIndex]){
                        return DeviceManager.DeviceList[swipeCurrIndex].pIO.availabel
                    }
                    else{
                        return true
                    }
                }
                eqText1:{
                    if(DeviceManager.DeviceList[swipeCurrIndex]){
                        return DeviceManager.DeviceList[swipeCurrIndex].ProductionObj.GoodCycleCount
                    }
                    else{
                        return ""
                    }
                }
                eqText2:{
                    if(DeviceManager.DeviceList[swipeCurrIndex]){
                        return DeviceManager.DeviceList[swipeCurrIndex].ProductionObj.SuspectCycleCount
                    }
                    else{
                        return ""
                    }
                }
                eqText3:{
                    if(DeviceManager.DeviceList[swipeCurrIndex]){
                        return DeviceManager.DeviceList[swipeCurrIndex].ProductionObj.DefectiveCycleCount
                    }
                    else{
                        return ""
                    }
                }
                eqText4:{
                    if(DeviceManager.DeviceList[swipeCurrIndex]){
                        return DeviceManager.DeviceList[swipeCurrIndex].ProductionObj.GoodCycleCount
                                + DeviceManager.DeviceList[swipeCurrIndex].ProductionObj.SuspectCycleCount
                                +DeviceManager.DeviceList[swipeCurrIndex].ProductionObj.DefectiveCycleCount
                    }
                    else{
                        return ""
                    }
                }
                eqText5:{
                    if(DeviceManager.DeviceList[swipeCurrIndex]){
                        return DeviceManager.DeviceList[swipeCurrIndex].ProductionObj.GoodRate
                    }
                    else{
                        return ""
                    }
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
        id:mode2
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
                    id: swipeSerialNumberText
                    anchors.left: parent.left
                    anchors.leftMargin: altitudeMode ? 110 : 150
                    anchors.top: t1.top
                    font.pixelSize: 16
                    // text: qsTr("序号")
                    text: GlobalLanguageDefine.strSerialNumber
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id: swipeWeldingTimeText
                    anchors.top: t1.top
                    anchors.left: parent.left
                    anchors.leftMargin: altitudeMode ? 170 : 270
                    font.pixelSize: 16
                    // text: qsTr("焊接时间")
                    text: GlobalLanguageDefine.strWeldingTime
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id: swipePowerText
                    anchors.top: t1.top
                    anchors.left: parent.left
                    anchors.leftMargin:  altitudeMode ? 270 : 420
                    font.pixelSize: 16
                    // text: qsTr("功率")
                    text: GlobalLanguageDefine.strPower
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id: swipePreHeightText
                    anchors.top: t1.top
                    anchors.left: parent.left
                    anchors.leftMargin: 350
                    font.pixelSize: 16
                    text: GlobalLanguageDefine.strPreWeldHeight
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                    visible: altitudeMode
                }
                Text{
                    id:swipePostHeightText
                    anchors.top: t1.top
                    anchors.left: parent.left
                    anchors.leftMargin: 450
                    font.pixelSize: 16
                    text: GlobalLanguageDefine.strPostWeldHeight
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                    visible: altitudeMode
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
                    text: GlobalLanguageDefine.strTensile
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id:t8
                    x:840/8*7 + 840/8/2-width/2
                    y:11
                    font.pixelSize: 16
                    // text: qsTr("残留度")
                    text: GlobalLanguageDefine.strResidual
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                }
                ListView{
                    id: taskplanView
                    width:840
                    height: 535
                    y:40
                    clip: true
                    model: Manual
                    onCountChanged:{
                        listSize = taskplanView.count
                    }
                    delegate: Rectangle{
                        id: regionItem
                        height: 36
                        width: 840
                        color: index % 2 === 0 ? "#afc3d8" : "#2d71ae"
                        MouseArea {
                            id: mouseArea
                            anchors.fill: parent
                            onPressed: {
                                taskplanView.currentIndex = index
                                parameter1 = Manual.data(Manual.index(index,0),QmlEnum.MANUAL_preEnergy)
                                parameter2 = Manual.data(Manual.index(index,0),QmlEnum.MANUAL_preAmplitude)
                                parameter3 = Manual.data(Manual.index(index,0),QmlEnum.MANUAL_preWP)
                                parameter4 = Manual.data(Manual.index(index,0),QmlEnum.MANUAL_preTP)
                            }
                        }
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
                                Manual.setData(Manual.index(index, 0), isSelect, QmlEnum.MANUAL_COLUMN.MANUAL_selected)
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
                            anchors.leftMargin: altitudeMode ? 115 : 160
                            anchors.verticalCenter: parent.verticalCenter
                            font.pixelSize: 16
                            text: serial_number
                            font.family: GlobalSystemDefine.fontBold
                            color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                        }
                        Text{
                            anchors.left: parent.left
                            anchors.leftMargin: altitudeMode ? 170 : 280
                            anchors.verticalCenter: parent.verticalCenter
                            font.pixelSize: 16
                            text: UtilityFunction.displayValue(time,100,2) + GlobalLanguageDefine.strWeldTimeUnit
                            font.family: GlobalSystemDefine.fontBold
                            color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                        }
                        Text{
                            anchors.left: parent.left
                            anchors.leftMargin: altitudeMode ? 270 : 420
                            anchors.verticalCenter: parent.verticalCenter
                            font.pixelSize: 16
                            text: UtilityFunction.displayValue(power) + GlobalLanguageDefine.strPowerUnit
                            font.family: GlobalSystemDefine.fontBold
                            color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                        }
                        Text{
                            anchors.left: parent.left
                            anchors.leftMargin: 350
                            anchors.verticalCenter: parent.verticalCenter
                            font.pixelSize: 16
                            text: UtilityFunction.displayValue(preheight,100,2) + GlobalLanguageDefine.strHeightUnit
                            font.family: GlobalSystemDefine.fontBold
                            color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                            visible: altitudeMode
                        }
                        Text{
                            anchors.left: parent.left
                            anchors.leftMargin: 450
                            anchors.verticalCenter: parent.verticalCenter
                            font.pixelSize: 16
                            text: UtilityFunction.displayValue(postheight,100,2) + GlobalLanguageDefine.strHeightUnit
                            font.family: GlobalSystemDefine.fontBold
                            color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                            visible: altitudeMode
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
                            text:actual_degree /*+ GlobalLanguageDefine.strActualDegreeUnit*/
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
