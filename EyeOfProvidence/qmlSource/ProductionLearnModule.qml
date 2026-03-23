import QtQuick              2.0
import QtQuick.Controls     1.4
import QtQuick.Controls     2.15
import QtQml.Models         2.15
import Device               1.0

import QmlEnum              1.0
import GlobalMessageDefine  1.0
import GlobalSystemDefine   1.0
import DeviceInfoEnum       1.0
import DeviceObj            1.0
import GlobalLanguageDefine 1.0
import ProductionObj        1.0
import ManualObj            1.0
import ManualTable          1.0
import GlobalStyle          1.0
import LanguageEnum         1.0

Rectangle {
    id: swipe
    color: pRgb(153, 204, 255)
    radius: 5
    readonly property int qmlscreenIndicator: QmlEnum.AUTO_LEARNING_SCREEEN
    property string tmpValue: ""
    property int listSize: 0
    property int currentIndex: DeviceManager.SelectedDeviceIndex
    property int deviceCount: DeviceManager.DeviceCounter
    property bool heightOption: (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption : false
    property ManualObj manualObj: (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ManualObj : null
    property DeviceObj deviceObj: (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].DeviceObj : null
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
                DeviceManager.DeviceList[currentIndex].ProductionObj.ModelStatus = true
                if(stillNeedToLearning() === true)
                {
                    layoutWeldParameter.txtEnergy       = DeviceManager.DeviceList[swipe.currentIndex].ManualObj.EnergySetting
                    layoutWeldParameter.txtAmplitude    = DeviceManager.DeviceList[swipe.currentIndex].ManualObj.AmplitudeSetting
                    layoutWeldParameter.txtTP           = DeviceManager.DeviceList[swipe.currentIndex].ManualObj.TriggerPressureSetting
                    layoutWeldParameter.txtWP           = DeviceManager.DeviceList[swipe.currentIndex].ManualObj.WeldPressureSetting
                }
                else
                {
                    if(DeviceManager.DeviceCounter > 1)
                        loadViewpro(2, null)
                    else
                        loadViewpro(3, null)
                }
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
        color: GlobalStyle.backgroundColor
        radius: 5

        EquipmentInfor{
            id: layoutDeviceInfo
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: parent.top
            anchors.topMargin: 5
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
                if(currentIndex < deviceCount){
                    switch(DeviceManager.DeviceList[currentIndex].DeviceObj.WelderType){
                    case 0:
                        return "L20-VG"
                    case 1:
                        return "L20-TS"
                    case 2:
                        return "2000XC"
                    default:
                        return "Other"
                    }
                }
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
            id: layoutWeldParameter
            width: 258
            height: 236
            anchors.top: layoutDeviceInfo.bottom
            anchors.topMargin: 15
            anchors.left: layoutDeviceInfo.left
            color:  "#0c5696"
            is2000XDevice:          (deviceObj.WelderType === DeviceInfoEnum.BRANSON_2000XC) ? true : false
            presetEnergy:           (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ManualObj.EnergySetting : "0"
            presetAmplitude:        (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ManualObj.AmplitudeSetting : "0"
            presetTriggerPressure:  (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ManualObj.TriggerPressureSetting : "0.0"
            presetWeldPressure:     (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ManualObj.WeldPressureSetting : "0.0"
        }

        Button{
            id: btnCreateModel
            anchors.left: layoutDeviceInfo.left
            anchors.top: layoutWeldParameter.bottom
            anchors.topMargin: 15
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
                    if(deviceCount === 1)
                        loadViewpro(3, null)
                    else
                        loadViewpro(2, null)
                }
                else
                {
                    popup.openPop(5)
                }
            }
        }
        Button{
            id: btnClear
            anchors.left: btnCreateModel.left
            anchors.top: btnCreateModel.bottom
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
        Button{
            id: btnNewAdd
            anchors.left: btnCreateModel.left
            anchors.top: btnClear.bottom
            anchors.topMargin:  10
            width:   258
            height:  45
            background: Rectangle{
                radius: 6
                border.color: pRgb(43, 112, 173)
                color: "#0c5696"
            }
            contentItem: Text {
                anchors.centerIn: parent
                text: GlobalLanguageDefine.strAddRecord
                font.pixelSize: 17
                color: pRgb(153, 204, 255)
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: GlobalSystemDefine.fontBold
            }
            onPressed: {
                DeviceManager.DeviceList[currentIndex].ManualObj.addNewRecordByManual()
            }

        }

        Rectangle{
            id: tableviewBackgroud
            anchors.left: layoutDeviceInfo.right
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.top: layoutDeviceInfo.top
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            color: "#0c5696"
            radius: 3
            Rectangle{
                id: listBackgroud
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: 40
                anchors.bottom: parent.bottom
                color: pRgb(43, 112, 173)
            }
            Item {
                id: listHeader
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                height: 40
                Button{
                    id: btnLockAll
                    width: 30
                    height: 30
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    anchors.verticalCenter: parent.verticalCenter
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
                    id: txtTotalChecked
                    anchors.left: btnLockAll.right
                    anchors.leftMargin: 5
                    anchors.verticalCenter: btnLockAll.verticalCenter
                    font.pixelSize: 16
                    // text: qsTr("全选")
                    text: GlobalLanguageDefine.strSelectAll
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(153, 204, 255)
                }

                Text{
                    id: txtCycleCount
                    anchors.left: parent.left
                    anchors.leftMargin: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption === true ? 80 : 120 //80 : 120
                    anchors.top: txtTotalChecked.top
                    font.pixelSize: 16
                    // text: qsTr("序号")
                    text: GlobalLanguageDefine.strCycleCount
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id: txtWeldTime
                    anchors.top: txtTotalChecked.top
                    anchors.left: parent.left
                    anchors.leftMargin: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption === true ? 180 : 260 //100 : 120
                    font.pixelSize: 16
                    // text: qsTr("焊接时间")
                    text: GlobalLanguageDefine.strWeldingTime + "(s)"
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id: txtPeakPower
                    anchors.top: txtTotalChecked.top
                    anchors.left: parent.left
                    anchors.leftMargin: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption === true ? 290 : 410 //110 : 150
                    font.pixelSize: 16
                    // text: qsTr("功率")
                    text: (deviceObj.WelderType !== DeviceInfoEnum.BRANSON_2000XC) ? GlobalLanguageDefine.strPower + "(W)" : GlobalLanguageDefine.strPower + "(%)"
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id: txtPreheight
                    anchors.top: txtTotalChecked.top
                    anchors.left: parent.left
                    anchors.leftMargin: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption === true ? 380 : 500 //90
                    font.pixelSize: 16
                    text: GlobalLanguageDefine.strPreWeldHeight + "(mm)"
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                    visible: heightOption
                }
                Text{
                    id: txtPostHeight
                    anchors.top: txtTotalChecked.top
                    anchors.left: parent.left
                    anchors.leftMargin: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption === true ? 520: 520 //140
                    font.pixelSize: 16
                    text: GlobalLanguageDefine.strPostWeldHeight + "(mm)"
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                    visible: heightOption
                }
                Text{
                    id: txtDateTime
                    anchors.top: txtTotalChecked.top
                    anchors.left: parent.left
                    anchors.leftMargin: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption === true ? 665: 550 //145 : 150
                    font.pixelSize: 16
                    // text: qsTr("日期")
                    text: GlobalLanguageDefine.strDate
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id: txtPeelForce
                    anchors.top: txtTotalChecked.top
                    anchors.left: parent.left
                    anchors.leftMargin: {
                        if(DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption === true)
                        {
                            if(LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE)
                                return 740 //75
                            else
                                return 715 //50
                        }
                        else
                        {
                            if(LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE)
                                return 665 //
                            else
                                return 640
                        }
                    }
                    font.pixelSize: 16
                    // text: qsTr("拉力")
                    text: GlobalLanguageDefine.strTensile + "(N)"
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id: txtResidual
                    anchors.top: txtTotalChecked.top
                    anchors.left: parent.left
                    anchors.leftMargin: {
                        if(DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption === true)
                        {
                            if(LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE)
                                return 845 //105
                            else
                                return 830 //115 : 160
                        }
                        else
                        {
                            if(LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE)
                                return 815
                            else
                                return 800
                        }
                    }
                    font.pixelSize: 16
                    // text: qsTr("残留度")
                    text: GlobalLanguageDefine.strResidual + "(%)"
                    font.family: GlobalSystemDefine.fontBold
                    color: pRgb(171, 206, 213)
                }
            }

            ListView{
                id: taskplanView
                anchors.top: listHeader.bottom
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                // anchors.leftMargin: 5
                anchors.right: parent.right
                // anchors.rightMargin: 5
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
                    width: taskplanView.width
                    color: index % 2 === 0 ? "#afc3d8" : "#2d71ae"
                    Button{
                        id: btnLock
                        anchors.left: parent.left
                        anchors.leftMargin: 15
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
                        target: btnLock
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
                        anchors.leftMargin: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption === true ? 100 : 130
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 16
                        text: cycle_count
                        font.family: GlobalSystemDefine.fontBold
                        color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                        visible: !is_by_manual
                    }
                    TextField{
                        id: fieldCycleCount
                        width: 90
                        height: 33
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption === true ? 75: 110 //50 : 90
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                        color: index % 2 === 0 ? "#014c8d" : pRgb(175, 195, 216)
                        font.family: GlobalSystemDefine.fontBold
                        font.pixelSize: 16
                        text: cycle_count
                        inputMethodHints: Qt.ImhDigitsOnly
                        visible: is_by_manual
                        background: Rectangle{
                            radius: 3
                            border.width: 2
                            border.color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                            color: index % 2 !== 0 ? "#2d71ae" : "#afc3d8"
                        }
                        cursorDelegate: Rectangle {
                            width: fieldCycleCount.cursorWidth
                            height: fieldCycleCount.font.pixelSize * 1.5
                            color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                            visible: fieldCycleCount.activeFocus
                            anchors.verticalCenter: parent.verticalCenter
                            Text {
                                text: "|"
                                color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                                font.pixelSize: fieldCycleCount.font.pixelSize
                                anchors.centerIn: parent
                            }
                        }
                        MouseArea {
                            anchors.fill: parent
                            onPressed: {
                                fieldCycleCount.forceActiveFocus()
                                tmpValue = fieldCycleCount.text
                                window.showPrimaryNumpad(txtCycleCount.text, " ", 3, 0, 999999, fieldCycleCount.text, fieldCycleCount, function(val)
                                {
                                    var intRegex = /^[0-9]+$/
                                    if (!intRegex.test(val))
                                    {
                                        footer.showError(txtCycleCount.text + " " + GlobalLanguageDefine.strInputInterger)
                                        fieldCycleCount.text = tmpValue;
                                    }
                                    else
                                    {
                                        footer.hideError()
                                        DeviceManager.DeviceList[swipe.currentIndex].ManualObj.setData(
                                                    DeviceManager.DeviceList[swipe.currentIndex].ManualObj.index(index, 0),
                                                    parseInt(fieldCycleCount.text),
                                                    ManualTable.CYCLE_COUNT
                                                    )
                                    }
                                })
                            }
                        }
                    }

                    Text{
                        anchors.left: parent.left
                        anchors.leftMargin: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption === true ? 200 : 280 //200
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 16
                        text: weld_time
                        font.family: GlobalSystemDefine.fontBold
                        color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                        visible: !is_by_manual
                    }
                    TextField{
                        id: fieldWeldTime
                        width: 100
                        height: 33
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption === true ? 175: 255
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                        color: index % 2 === 0 ? "#014c8d" : pRgb(175, 195, 216)
                        font.family: GlobalSystemDefine.fontBold
                        font.pixelSize: 16
                        text: weld_time
                        inputMethodHints: Qt.ImhDigitsOnly
                        visible: is_by_manual
                        background: Rectangle{
                            radius: 3
                            border.width: 2
                            border.color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                            color: index % 2 !== 0 ? "#2d71ae" : "#afc3d8"
                        }
                        cursorDelegate: Rectangle {
                            width: fieldWeldTime.cursorWidth
                            height: fieldWeldTime.font.pixelSize * 1.5
                            color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                            visible: fieldWeldTime.activeFocus
                            anchors.verticalCenter: parent.verticalCenter
                            Text {
                                text: "|"
                                color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                                font.pixelSize: fieldWeldTime.font.pixelSize
                                anchors.centerIn: parent
                            }
                        }
                        MouseArea {
                            anchors.fill: parent
                            onPressed: {
                                fieldWeldTime.forceActiveFocus()
                                tmpValue = fieldWeldTime.text
                                window.showPrimaryNumpad(txtWeldTime.text, " ", 3, 0, 999999, fieldWeldTime.text, fieldWeldTime, function(val)
                                {
                                    var intRegex = /^[0-9]+(.[0-9]{1,2})?$/
                                    if (!intRegex.test(val))
                                    {
                                        footer.showError(txtWeldTime.text + " " + GlobalLanguageDefine.strInputFloat)
                                        fieldWeldTime.text = tmpValue;
                                    }
                                    else
                                    {
                                        footer.hideError()
                                        DeviceManager.DeviceList[swipe.currentIndex].ManualObj.setData(
                                                    DeviceManager.DeviceList[swipe.currentIndex].ManualObj.index(index, 0),
                                                    parseFloat(fieldWeldTime.text) * 100,
                                                    ManualTable.WELD_TIME
                                                    )
                                    }
                                })
                            }
                        }
                    }

                    Text{
                        anchors.left: parent.left
                        anchors.leftMargin: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption === true ? 300 : 420 //
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 16
                        text: peak_power
                        font.family: GlobalSystemDefine.fontBold
                        color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                        visible: !is_by_manual
                    }
                    TextField{
                        id: fieldPeakPower
                        width: 90
                        height: 33
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption === true ? 285: 400
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                        color: index % 2 === 0 ? "#014c8d" : pRgb(175, 195, 216)
                        font.family: GlobalSystemDefine.fontBold
                        font.pixelSize: 16
                        text: peak_power
                        inputMethodHints: Qt.ImhDigitsOnly
                        visible: is_by_manual
                        background: Rectangle{
                            radius: 3
                            border.width: 2
                            border.color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                            color: index % 2 !== 0 ? "#2d71ae" : "#afc3d8"
                        }
                        cursorDelegate: Rectangle {
                            width: fieldPeakPower.cursorWidth
                            height: fieldPeakPower.font.pixelSize * 1.5
                            color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                            visible: fieldPeakPower.activeFocus
                            anchors.verticalCenter: parent.verticalCenter
                            Text {
                                text: "|"
                                color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                                font.pixelSize: fieldPeakPower.font.pixelSize
                                anchors.centerIn: parent
                            }
                        }
                        MouseArea {
                            anchors.fill: parent
                            onPressed: {
                                fieldPeakPower.forceActiveFocus()
                                tmpValue = fieldPeakPower.text
                                window.showPrimaryNumpad(txtPeakPower.text, " ", 3, 0, 999999, fieldPeakPower.text, fieldPeakPower, function(val)
                                {
                                    var intRegex = /^[0-9]+$/
                                    if (!intRegex.test(val))
                                    {
                                        footer.showError(txtPeakPower.text + " " + GlobalLanguageDefine.strInputInterger)
                                        fieldPeakPower.text = tmpValue;
                                    }
                                    else
                                    {
                                        footer.hideError()
                                        DeviceManager.DeviceList[swipe.currentIndex].ManualObj.setData(
                                                    DeviceManager.DeviceList[swipe.currentIndex].ManualObj.index(index, 0),
                                                    parseInt(fieldPeakPower.text),
                                                    ManualTable.PEAK_POWER
                                                    )
                                    }
                                })
                            }
                        }
                    }

                    Text{
                        anchors.left: parent.left
                        anchors.leftMargin: 410
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 16
                        text: preheight
                        font.family: GlobalSystemDefine.fontBold
                        color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                        visible: DeviceManager.DeviceList[swipe.currentIndex].DeviceObj.HeightEncoderOption && !is_by_manual
                    }
                    TextField{
                        id: fieldPreheight
                        width: 90
                        height: 33
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 390
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                        color: index % 2 === 0 ? "#014c8d" : pRgb(175, 195, 216)
                        font.family: GlobalSystemDefine.fontBold
                        font.pixelSize: 16
                        text: preheight
                        inputMethodHints: Qt.ImhDigitsOnly
                        visible: DeviceManager.DeviceList[swipe.currentIndex].DeviceObj.HeightEncoderOption && is_by_manual
                        background: Rectangle{
                            radius: 3
                            border.width: 2
                            border.color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                            color: index % 2 !== 0 ? "#2d71ae" : "#afc3d8"
                        }
                        cursorDelegate: Rectangle {
                            width: fieldPreheight.cursorWidth
                            height: fieldPreheight.font.pixelSize * 1.5
                            color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                            visible: fieldPreheight.activeFocus
                            anchors.verticalCenter: parent.verticalCenter
                            Text {
                                text: "|"
                                color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                                font.pixelSize: fieldPreheight.font.pixelSize
                                anchors.centerIn: parent
                            }
                        }
                        MouseArea {
                            anchors.fill: parent
                            onPressed: {
                                fieldPreheight.forceActiveFocus()
                                tmpValue = fieldPreheight.text
                                window.showPrimaryNumpad(txtPreheight.text, " ", 3, 0, 999999, fieldPreheight.text, fieldPreheight, function(val)
                                {
                                    var intRegex = /^[0-9]+(.[0-9]{1,2})?$/
                                    if (!intRegex.test(val))
                                    {
                                        footer.showError(txtPreheight.text + " " + GlobalLanguageDefine.strInputFloat)
                                        fieldPreheight.text = tmpValue;
                                    }
                                    else
                                    {
                                        footer.hideError()
                                        DeviceManager.DeviceList[swipe.currentIndex].ManualObj.setData(
                                                    DeviceManager.DeviceList[swipe.currentIndex].ManualObj.index(index, 0),
                                                    parseFloat(fieldPreheight.text) * 100,
                                                    ManualTable.PRE_HEIGHT
                                                    )
                                    }
                                })
                            }
                        }
                    }

                    Text{
                        anchors.left: parent.left
                        anchors.leftMargin: 550
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 16
                        text: postheight
                        font.family: GlobalSystemDefine.fontBold
                        color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                        visible: DeviceManager.DeviceList[swipe.currentIndex].DeviceObj.HeightEncoderOption && !is_by_manual
                    }

                    TextField{
                        id: fieldPostHeight
                        width: 90
                        height: 33
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 530
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                        color: index % 2 === 0 ? "#014c8d" : pRgb(175, 195, 216)
                        font.family: GlobalSystemDefine.fontBold
                        font.pixelSize: 16
                        text: postheight
                        inputMethodHints: Qt.ImhDigitsOnly
                        visible: DeviceManager.DeviceList[swipe.currentIndex].DeviceObj.HeightEncoderOption && is_by_manual
                        background: Rectangle{
                            radius: 3
                            border.width: 2
                            border.color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                            color: index % 2 !== 0 ? "#2d71ae" : "#afc3d8"
                        }
                        cursorDelegate: Rectangle {
                            width: fieldPostHeight.cursorWidth
                            height: fieldPostHeight.font.pixelSize * 1.5
                            color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                            visible: fieldPostHeight.activeFocus
                            anchors.verticalCenter: parent.verticalCenter
                            Text {
                                text: "|"
                                color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                                font.pixelSize: fieldPostHeight.font.pixelSize
                                anchors.centerIn: parent
                            }
                        }
                        MouseArea {
                            anchors.fill: parent
                            onPressed: {
                                fieldPostHeight.forceActiveFocus()
                                tmpValue = fieldPostHeight.text
                                window.showPrimaryNumpad(txtPostHeight.text, " ", 3, 0, 999999, fieldPostHeight.text, fieldPostHeight, function(val)
                                {
                                    var intRegex = /^[0-9]+(.[0-9]{1,2})?$/
                                    if (!intRegex.test(val))
                                    {
                                        footer.showError(txtPostHeight.text + " " + GlobalLanguageDefine.strInputFloat)
                                        fieldPostHeight.text = tmpValue;
                                    }
                                    else
                                    {
                                        footer.hideError()
                                        DeviceManager.DeviceList[swipe.currentIndex].ManualObj.setData(
                                                    DeviceManager.DeviceList[swipe.currentIndex].ManualObj.index(index, 0),
                                                    parseFloat(fieldPostHeight.text) * 100,
                                                    ManualTable.POST_HEIGHT
                                                    )
                                    }
                                })
                            }
                        }
                    }


                    Text{
                        anchors.left: parent.left
                        anchors.leftMargin: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption === true ? 645 : 530
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 16
                        text: create_time
                        font.family: GlobalSystemDefine.fontBold
                        color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                    }
                    TextField{
                        id: fieldForce
                        width: 100
                        height: 33
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption === true ? 715: 640 //50 : 90
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
                            width: fieldForce.cursorWidth
                            height: fieldForce.font.pixelSize * 1.5
                            color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                            visible: fieldForce.activeFocus
                            anchors.verticalCenter: parent.verticalCenter
                            Text {
                                text: "|"
                                color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                                font.pixelSize: fieldForce.font.pixelSize
                                anchors.centerIn: parent
                            }
                        }
                        MouseArea {
                            anchors.fill: parent
                            onPressed: {
                                fieldForce.forceActiveFocus()
                                tmpValue = fieldForce.text
                                window.showPrimaryNumpad(txtPeelForce.text, " ", 3, 0, 999999, fieldForce.text, fieldForce, function(val)
                                {
                                    var intRegex = /^[0-9]+$/
                                    if (!intRegex.test(val))
                                    {
                                        footer.showError(txtPeelForce.text + " "+ GlobalLanguageDefine.strInputInterger)
                                        fieldForce.text = tmpValue;
                                    }
                                    else
                                    {
                                        footer.hideError()
                                        DeviceManager.DeviceList[swipe.currentIndex].ManualObj.setData(
                                                    DeviceManager.DeviceList[swipe.currentIndex].ManualObj.index(index, 0),
                                                    parseInt(fieldForce.text),
                                                    ManualTable.ACTUAL_FORCE
                                                    )
                                    }
                                })
                            }
                        }
                    }

                    TextField{
                        id: fieldResidual
                        width: 100
                        height: 33
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption === true ? 830: 800 //115 : 160
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
                            width: fieldResidual.cursorWidth
                            height: fieldResidual.font.pixelSize * 1.5
                            color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                            visible: fieldResidual.activeFocus
                            anchors.verticalCenter: parent.verticalCenter
                            Text {
                                text: "|"
                                color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                                font.pixelSize: fieldResidual.font.pixelSize
                                anchors.centerIn: parent
                            }
                        }
                        MouseArea {
                            anchors.fill: parent
                            onPressed: {
                                fieldResidual.forceActiveFocus()
                                tmpValue = fieldResidual.text
                                window.showPrimaryNumpad(txtResidual.text, " ", 3, 0, 999999, fieldResidual.text, fieldResidual, function(val)
                                {
                                    var intRegex = /^[0-9]+$/
                                    if (!intRegex.test(val))
                                    {
                                        footer.showError(txtResidual.text + " " + GlobalLanguageDefine.strInputInterger)
                                        fieldResidual.text = tmpValue;
                                    }
                                    else
                                    {
                                        footer.hideError()
                                        DeviceManager.DeviceList[swipe.currentIndex].ManualObj.setData(
                                                    DeviceManager.DeviceList[swipe.currentIndex].ManualObj.index(index, 0),
                                                    parseInt(fieldResidual.text),
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
