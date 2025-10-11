import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15
import Device 1.0
import DeviceInformation 1.0
import GlobalLanguageDefine 1.0
import GlobalMessageDefine 1.0
import DeviceInfoEnum 1.0

//多设备生产界面
Rectangle {
    color: pRgb(153, 204, 255)
    property int itemCount: 0
    Connections{
        target: mpro
        function onSigBtnSynchronization(index,time){
            if(index === 1){
                s5.btnIndex = time
            }
            else if(index === 2){
                s6.btnIndex = time
            }
        }
    }
    function swichCount(){
        if(itemCount == 2){
            r1.height = 581
            r2.height = 581
            r3.visible = false
            r4.visible = false
            s1.x = 28
            s1.y = 42
            s2.x = 284
            s2.y = 42
            s3.x = 28
            s3.y = 42
            s4.x = 284
            s4.y = 42

            s1.width = 243
            s1.height = 237
            s2.width = 289
            s2.height = 238
            s3.width = 243
            s3.height = 237
            s4.width = 289
            s4.height = 238
        }
        else if(itemCount == 3){
            r1.height = 581
            r2.height = 287
            r3.visible = false
            r4.visible = true
            s1.x = 28
            s1.y = 42
            s2.x = 284
            s2.y = 42
            s3.x = 35
            s3.y = 36
            s4.x = 280
            s4.y = 36

            s1.width = 243
            s1.height = 237
            s2.width = 289
            s2.height = 238
            s3.width = 233
            s3.height = 227
            s4.width = 277
            s4.height = 228
        }
        else if(itemCount == 4){
            r1.height = 287
            r2.height = 287
            r3.visible = true
            r4.visible = true

            s1.x = 35
            s1.y = 36
            s2.x = 280
            s2.y = 36
            s3.x = 35
            s3.y = 36
            s4.x = 280
            s4.y = 36

            s1.width = 233
            s1.height = 227
            s2.width = 277
            s2.height = 228
            s3.width = 233
            s3.height = 227
            s4.width = 277
            s4.height = 228
        }
    }

    onItemCountChanged: {
        swichCount()
    }
    Rectangle{
        id:r1
        x:28
        y:44
        width: 600
        height: 581
        radius: 5
        color: pRgb(43, 112, 173)
        onHeightChanged: {
            if(height>290){
                s5.visible = true
            }
            else{
                s5.visible = false
            }
        }

        EquipmentInfor{
            id:s1
            x:28
            y:42
            width: 243
            height: 237
            radius: 3
            color: "#0c5596"
            eqText1:{
                if(DeviceManager.deviceList[0]){
                    return DeviceManager.deviceList[0].DevInfoObject.name
                }
                else{
                    return ""
                }
            }
            eqText2:{
                if(DeviceManager.deviceList[0]){
                    return DeviceManager.deviceList[0].DevInfoObject.model
                }
                else{
                    return ""
                }
            }
            eqText3:{
                if(DeviceManager.deviceList[0]){
                    return DeviceManager.deviceList[0].DevInfoObject.ConnectType === 1
                            ? "RS232" : "TCP/IP"
                }
                else{
                    return ""
                }
            }
            eqText4:{
                if(DeviceManager.deviceList[0])
                {
                    var connectState = DeviceManager.deviceList[0].DevInfoObject.ConnectState
                    return GlobalMessageDefine.getConnectState(connectState)
                }
                else
                    return ""

            }
        }
        RealtimeYield{
            id:s2
            width: 289
            height: 238
            x:284
            y:42
            radius: 3
            color: "#0c5596"
            revealing:{
                if(DeviceManager.deviceList[0]){
                    return DeviceManager.deviceList[0].pIO.availabel
                }
                else{
                    return true
                }
            }
            eqText1:{
                if(DeviceManager.deviceList[0]){
                    return DeviceManager.deviceList[0].DevInfoObject.goodCycles
                }
                else{
                    return ""
                }
            }
            eqText2:{
                if(DeviceManager.deviceList[0]){
                    return DeviceManager.deviceList[0].DevInfoObject.suspectCycles
                }
                else{
                    return ""
                }
            }
            eqText3:{
                if(DeviceManager.deviceList[0]){
                    return DeviceManager.deviceList[0].DevInfoObject.notDefinite
                }
                else{
                    return ""
                }
            }
            eqText4:{
                if(DeviceManager.deviceList[0]){
                    return DeviceManager.deviceList[0].DevInfoObject.goodCycles
                            + DeviceManager.deviceList[0].DevInfoObject.notDefinite
                            +DeviceManager.deviceList[0].DevInfoObject.suspectCycles
                }
                else{
                    return ""
                }
            }
            eqText5:{
                if(DeviceManager.deviceList[0]){
                    return DeviceManager.deviceList[0].DevInfoObject.goodRate
                }
                else{
                    return ""
                }
            }
        }
        YieldTrend{
            id:s5
            width: 545
            height: 254
            x:28
            y:298
            radius: 3
            color: "#0c5596"
            equiInforIndex:1
        }
        Button{
            width: 30
            height: 30
            x:566
            y:6
            background: Rectangle{
                color: "transparent"
                Image {
                    anchors.fill: parent
                    source: "qrc:/images/btn_fullscreen_enter.png"
                }
            }
            onPressed: {
                swipevis = true
                mpro.swipeIndex = 0
                swipeCurrIndex = 0
                loadViewpro(3,swipe)
                sigUpdateUI(0)
            }
        }
    }
    Rectangle{
        id:r2
        x:654
        y:44
        width: 600
        height: 581
        radius: 5
        color: pRgb(43, 112, 173)
        onHeightChanged: {
            if(height > 290){
                s6.visible = true
            }
            else{
                s6.visible = false
            }
        }
        EquipmentInfor{
            id:s3
            x:28
            y:42
            width: 243
            height: 237
            radius: 3
            color: "#0c5596"
            eqText1:{
                if(DeviceManager.deviceList[1])
                {
                    return DeviceManager.deviceList[1].DevInfoObject.name
                }
                else
                {
                    return ""
                }
            }
            eqText2:{
                if(DeviceManager.deviceList[1])
                {
                    return DeviceManager.deviceList[1].DevInfoObject.model
                }
                else
                {
                    return ""
                }
            }
            eqText3:{
                if(DeviceManager.deviceList[1]){
                    return DeviceManager.deviceList[1].DevInfoObject.ConnectType === 1
                            ? "RS232" : "TCP/IP"
                }
                else{
                    return ""
                }
            }
            eqText4:{
                if(DeviceManager.deviceList[1])
                {
                    var connectState = DeviceManager.deviceList[1].DevInfoObject.ConnectState
                    return GlobalMessageDefine.getConnectState(connectState)
                }
                else
                    return ""
            }
        }
        RealtimeYield{
            id:s4
            width: 289
            height: 238
            x:284
            y:42
            radius: 3
            color: "#0c5596"
            revealing:{
                if(DeviceManager.deviceList[1]){
                    return DeviceManager.deviceList[1].pIO.availabel
                }
                else{
                    return true
                }
            }
            eqText1:{
                if(DeviceManager.deviceList[1]){
                    return DeviceManager.deviceList[1].DevInfoObject.goodCycles
                }
                else{
                    return ""
                }
            }
            eqText2:{
                if(DeviceManager.deviceList[1]){
                    return DeviceManager.deviceList[1].DevInfoObject.suspectCycles
                }
                else{
                    return ""
                }
            }
            eqText3:{
                if(DeviceManager.deviceList[1]){
                    return DeviceManager.deviceList[1].DevInfoObject.notDefinite
                }
                else{
                    return ""
                }
            }
            eqText4:{
                if(DeviceManager.deviceList[1]){
                    return DeviceManager.deviceList[1].DevInfoObject.goodCycles
                            + DeviceManager.deviceList[1].DevInfoObject.notDefinite
                            +DeviceManager.deviceList[1].DevInfoObject.suspectCycles
                }
                else{
                    return ""
                }
            }
            eqText5:{
                if(DeviceManager.deviceList[1]){
                    return DeviceManager.deviceList[1].DevInfoObject.goodRate
                }
                else{
                    return ""
                }
            }
        }
        YieldTrend{
            id:s6
            width: 545
            height: 254
            x:28
            y:298
            radius: 3
            color: "#0c5596"
            equiInforIndex:2
        }
        Button{
            width: 30
            height: 30
            x:566
            y:6
            background: Rectangle{
                color: "transparent"
                Image {
                    anchors.fill: parent
                    source: "qrc:/images/btn_fullscreen_enter.png"
                }
            }
            onPressed: {
                swipevis = true
                mpro.swipeIndex = 1
                swipeCurrIndex = 1
                loadViewpro(3,swipe)
                sigUpdateUI(1)
            }
        }
    }
    Rectangle{
        id:r3
        x:28
        y:338
        width: 600
        height: 287
        radius: 5
        color: pRgb(43, 112, 173)
        onVisibleChanged: {
            if(visible){
                enabled = true
            }
            else{
                enabled = false
            }
        }

        EquipmentInfor{
            id:s7
            x:35
            y:36
            width: 233
            height: 227
            radius: 3
            color: "#0c5596"
            eqText1:{
                if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].DevInfoObject.name
                }
                else if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].DevInfoObject.name
                }
                else{
                    return ""
                }
            }
            eqText2:{
                if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].DevInfoObject.model
                }
                else if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].DevInfoObject.model
                }
                else{
                    return ""
                }
            }
            eqText3:{
                if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].DevInfoObject.ConnectType === 1
                            ? "RS232" : "TCP/IP"
                }
                else if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].DevInfoObject.ConnectType === 1
                            ? "RS232" : "TCP/IP"
                }
                else{
                    return ""
                }
            }
            eqText4:{
                var connectState = 0
                if(DeviceManager.deviceList[2])
                {
                    connectState = DeviceManager.deviceList[2].DevInfoObject.ConnectState
                    return GlobalMessageDefine.getConnectState(connectState)
                }
                else if(DeviceManager.deviceList[3])
                {
                    connectState = DeviceManager.deviceList[3].DevInfoObject.ConnectState
                    return GlobalMessageDefine.getConnectState(connectState)
                }
                else
                {
                    return ""
                }
            }
        }
        RealtimeYield{
            id:s8
            width: 277
            height: 228
            x:280
            y:35
            radius: 3
            color: "#0c5596"
            revealing:{
                if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].pIO.availabel
                }
                else if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].pIO.availabel
                }
                else{
                    return true
                }
            }
            eqText1:{
                if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].DevInfoObject.goodCycles
                }
                else if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].DevInfoObject.goodCycles
                }
                else{
                    return ""
                }
            }
            eqText2:{
                if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].DevInfoObject.suspectCycles
                }
                else if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].DevInfoObject.suspectCycles
                }
                else{
                    return ""
                }
            }
            eqText3:{
                if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].DevInfoObject.notDefinite
                }
                else if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].DevInfoObject.notDefinite
                }
                else{
                    return ""
                }
            }
            eqText4:{
                if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].DevInfoObject.goodCycles
                            + DeviceManager.deviceList[2].DevInfoObject.notDefinite
                            +DeviceManager.deviceList[2].DevInfoObject.suspectCycles
                }
                else if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].DevInfoObject.goodCycles
                            + DeviceManager.deviceList[3].DevInfoObject.notDefinite
                            +DeviceManager.deviceList[3].DevInfoObject.suspectCycles
                }
                else{
                    return ""
                }
            }
            eqText5:{
                if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].DevInfoObject.goodRate
                }
                else if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].DevInfoObject.goodRate
                }
                else{
                    return ""
                }
            }
        }
        Button{
            width: 30
            height: 30
            x:566
            y:6
            background: Rectangle{
                color: "transparent"
                Image {
                    anchors.fill: parent
                    source: "qrc:/images/btn_fullscreen_enter.png"
                }
            }
            onPressed: {
                swipevis = true
                mpro.swipeIndex = 2
                swipeCurrIndex = 2
                loadViewpro(3,swipe)
                sigUpdateUI(2)
            }
        }
    }
    Rectangle{
        id:r4
        x:654
        y:338
        width: 600
        height: 287
        radius: 5
        color: pRgb(43, 112, 173)
        onVisibleChanged: {
            if(visible){
                enabled = true
            }
            else{
                enabled = false
            }
        }
        EquipmentInfor{
            id:s10
            x:35
            y:36
            width: 233
            height: 227
            radius: 3
            color: "#0c5596"
            eqText1:{
                if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].DevInfoObject.name
                }
                else if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].DevInfoObject.name
                }
                else{
                    return ""
                }
            }
            eqText2:{
                if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].DevInfoObject.model
                }
                else if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].DevInfoObject.model
                }
                else{
                    return ""
                }
            }
            eqText3:{
                if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].DevInfoObject.ConnectType === 1
                            ? "RS232" : "TCP/IP"
                }
                else if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].DevInfoObject.ConnectType === 1
                            ? "RS232" : "TCP/IP"
                }
                else{
                    return ""
                }
            }
            eqText4:{
                var connectState = 0
                if(DeviceManager.deviceList[3])
                {
                    connectState = DeviceManager.deviceList[3].DevInfoObject.ConnectState
                    return GlobalMessageDefine.getConnectState(connectState)
                }
                else if(DeviceManager.deviceList[2])
                {
                    connectState = DeviceManager.deviceList[2].DevInfoObject.ConnectState
                    return GlobalMessageDefine.getConnectState(connectState)
                }
                else
                {
                    return ""
                }
            }
        }
        RealtimeYield{
            id:s11
            width: 277
            height: 228
            x:280
            y:35
            radius: 3
            color: "#0c5596"
            revealing:{
                if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].pIO.availabel
                }
                else if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].pIO.availabel
                }
                else{
                    return true
                }
            }
            eqText1:{
                if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].DevInfoObject.goodCycles
                }
                else if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].DevInfoObject.goodCycles
                }
                else{
                    return ""
                }
            }
            eqText2:{
                if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].DevInfoObject.suspectCycles
                }
                else if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].DevInfoObject.suspectCycles
                }
                else{
                    return ""
                }
            }
            eqText3:{
                if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].DevInfoObject.notDefinite
                }
                else if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].DevInfoObject.notDefinite
                }
                else{
                    return ""
                }
            }
            eqText4:{
                if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].DevInfoObject.goodCycles
                            + DeviceManager.deviceList[3].DevInfoObject.notDefinite
                            +DeviceManager.deviceList[3].DevInfoObject.suspectCycles
                }
                else if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].DevInfoObject.goodCycles
                            + DeviceManager.deviceList[2].DevInfoObject.notDefinite
                            +DeviceManager.deviceList[2].DevInfoObject.suspectCycles
                }
                else{
                    return ""
                }
            }
            eqText5:{
                if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].DevInfoObject.goodRate
                }
                else if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].DevInfoObject.goodRate
                }
                else{
                    return ""
                }
            }
        }
        Button{
            width: 30
            height: 30
            x:566
            y:6
            background: Rectangle{
                color: "transparent"
                Image {
                    anchors.fill: parent
                    source: "qrc:/images/btn_fullscreen_enter.png"
                }
            }
            onPressed: {
                swipevis = true
                if(equipmentCount === 4){
                    mpro.swipeIndex = 3
                    swipeCurrIndex = 3
                }
                else{
                    mpro.swipeIndex = 2
                    swipeCurrIndex = 2
                }
                loadViewpro(3,swipe)
                sigUpdateUI(3)
            }
        }
    }

       // Button{
       //     id:b1
       //     x:195
       //     y:654
       //     width: 243
       //     height: 52
       //     background: Rectangle{
       //         radius: 6
       //         color: pRgb(43, 112, 173)
       //     }
       //     contentItem: Text {
       //         id:mt1
       //         anchors.centerIn: parent
       //         text: "新建模型"
       //         font.pixelSize: 20
       //         color: pRgb(153, 204, 255)
       //         horizontalAlignment: Text.AlignHCenter
       //         verticalAlignment: Text.AlignVCenter
       //         font.family: fontBold
       //     }
       //     onPressed: {
       //         mt1.text = "创建模型"
       //         mt2.text = "清除数据"
       //     }
       // }
    Button{
        id:b2
        width: 243
        height: 52
        x:228
        y:654
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: pRgb(43, 112, 173)
            color: itemCount === 4 ? pRgb(232, 232, 232) : pRgb(43, 112, 173)
        }
        contentItem: Text {
            id:mt2
            anchors.centerIn: parent
            // text: qsTr("新增设备")
            text: GlobalLanguageDefine.strAddDevice
            font.pixelSize: 20
            color: pRgb(153, 204, 255)
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
        }
        onPressed: {
            // if(mt2.text === qsTr("新增设备"))
            if(mt2.text === GlobalLanguageDefine.strAddDevice)
            {
                popup.openPop(8)
            }
        }
    }
    Button{
        id:b3
        width: 243
        height: 52
        x:813
        y:654
        background: Rectangle{
            radius: 6
            color: pRgb(43, 112, 173)
        }
        contentItem: Text {
            id:mt3
            anchors.centerIn: parent
            // text: qsTr( "系统消息")
            text: GlobalLanguageDefine.strSystemMessage
            font.pixelSize: 20
            color: pRgb(153, 204, 255)
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
        }
        onPressed: {
            popup.openPop(6)
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
            // drag.target: timeDialog
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
