import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15
import Device 1.0
import DeviceInformation 1.0
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
                    return DeviceManager.deviceList[0].pDeviceInformation.name
                }
                else{
                    return ""
                }
            }
            eqText2:{
                if(DeviceManager.deviceList[0]){
                    return DeviceManager.deviceList[0].pDeviceInformation.model
                }
                else{
                    return ""
                }
            }
            eqText3:{
                if(DeviceManager.deviceList[0]){
                    return DeviceManager.deviceList[0].pDeviceInformation.connectType === 1
                            ? "RS232" : "网络连接"
                }
                else{
                    return ""
                }
            }
            eqText4:{
                if(DeviceManager.deviceList[0]){
                    return DeviceManager.deviceList[0].pDeviceInformation.state
                }
                else{
                    return ""
                }
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
                    return DeviceManager.deviceList[0].pDeviceInformation.goodCycles
                }
                else{
                    return ""
                }
            }
            eqText2:{
                if(DeviceManager.deviceList[0]){
                    return DeviceManager.deviceList[0].pDeviceInformation.suspectCycles
                }
                else{
                    return ""
                }
            }
            eqText3:{
                if(DeviceManager.deviceList[0]){
                    return DeviceManager.deviceList[0].pDeviceInformation.notDefinite
                }
                else{
                    return ""
                }
            }
            eqText4:{
                if(DeviceManager.deviceList[0]){
                    return DeviceManager.deviceList[0].pDeviceInformation.goodCycles
                    + DeviceManager.deviceList[0].pDeviceInformation.notDefinite
                    +DeviceManager.deviceList[0].pDeviceInformation.suspectCycles
                }
                else{
                    return ""
                }
            }
            eqText5:{
                if(DeviceManager.deviceList[0]){
                    return DeviceManager.deviceList[0].pDeviceInformation.goodRate
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
            btnIndex:rect1
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
                    source: "qrc:/image/full.png"
                }
            }
            onPressed: {
                mpro.swipeIndex = 0
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
            if(height>290){
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
                if(DeviceManager.deviceList[1]){
                    return DeviceManager.deviceList[1].pDeviceInformation.name
                }
                else{
                    return ""
                }
            }
            eqText2:{
                if(DeviceManager.deviceList[1]){
                    return DeviceManager.deviceList[1].pDeviceInformation.model
                }
                else{
                    return ""
                }
            }
            eqText3:{
                if(DeviceManager.deviceList[1]){
                    return DeviceManager.deviceList[1].pDeviceInformation.connectType === 1
                            ? "RS232" : "网络连接"
                }
                else{
                    return ""
                }
            }
            eqText4:{
                if(DeviceManager.deviceList[1]){
                    return DeviceManager.deviceList[1].pDeviceInformation.state
                }
                else{
                    return ""
                }
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
                    return DeviceManager.deviceList[1].pDeviceInformation.goodCycles
                }
                else{
                    return ""
                }
            }
            eqText2:{
                if(DeviceManager.deviceList[1]){
                    return DeviceManager.deviceList[1].pDeviceInformation.suspectCycles
                }
                else{
                    return ""
                }
            }
            eqText3:{
                if(DeviceManager.deviceList[1]){
                    return DeviceManager.deviceList[1].pDeviceInformation.notDefinite
                }
                else{
                    return ""
                }
            }
            eqText4:{
                if(DeviceManager.deviceList[1]){
                    return DeviceManager.deviceList[1].pDeviceInformation.goodCycles
                    + DeviceManager.deviceList[1].pDeviceInformation.notDefinite
                    +DeviceManager.deviceList[1].pDeviceInformation.suspectCycles
                }
                else{
                    return ""
                }
            }
            eqText5:{
                if(DeviceManager.deviceList[1]){
                    return DeviceManager.deviceList[1].pDeviceInformation.goodRate
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
            btnIndex:rect2
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
                    source: "qrc:/image/full.png"
                }
            }
            onPressed: {
                mpro.swipeIndex = 1
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
                    return DeviceManager.deviceList[2].pDeviceInformation.name
                }
                else if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].pDeviceInformation.name
                }
                else{
                    return ""
                }
            }
            eqText2:{
                if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].pDeviceInformation.model
                }
                else if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].pDeviceInformation.model
                }
                else{
                    return ""
                }
            }
            eqText3:{
                if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].pDeviceInformation.connectType === 1
                            ? "RS232" : "网络连接"
                }
                else if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].pDeviceInformation.connectType === 1
                            ? "RS232" : "网络连接"
                }
                else{
                    return ""
                }
            }
            eqText4:{
                if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].pDeviceInformation.state
                }
                else if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].pDeviceInformation.state
                }
                else{
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
                    return DeviceManager.deviceList[2].pDeviceInformation.goodCycles
                }
                else if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].pDeviceInformation.goodCycles
                }
                else{
                    return ""
                }
            }
            eqText2:{
                if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].pDeviceInformation.suspectCycles
                }
                else if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].pDeviceInformation.suspectCycles
                }
                else{
                    return ""
                }
            }
            eqText3:{
                if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].pDeviceInformation.notDefinite
                }
                else if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].pDeviceInformation.notDefinite
                }
                else{
                    return ""
                }
            }
            eqText4:{
                if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].pDeviceInformation.goodCycles
                    + DeviceManager.deviceList[2].pDeviceInformation.notDefinite
                    +DeviceManager.deviceList[2].pDeviceInformation.suspectCycles
                }
                else if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].pDeviceInformation.goodCycles
                    + DeviceManager.deviceList[3].pDeviceInformation.notDefinite
                    +DeviceManager.deviceList[3].pDeviceInformation.suspectCycles
                }
                else{
                    return ""
                }
            }
            eqText5:{
                if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].pDeviceInformation.goodRate
                }
                else if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].pDeviceInformation.goodRate
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
                    source: "qrc:/image/full.png"
                }
            }
            onPressed: {
                mpro.swipeIndex = 2
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
                    return DeviceManager.deviceList[3].pDeviceInformation.name
                }
                else if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].pDeviceInformation.name
                }
                else{
                    return ""
                }
            }
            eqText2:{
                if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].pDeviceInformation.model
                }
                else if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].pDeviceInformation.model
                }
                else{
                    return ""
                }
            }
            eqText3:{
                if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].pDeviceInformation.connectType === 1
                            ? "RS232" : "网络连接"
                }
                else if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].pDeviceInformation.connectType === 1
                            ? "RS232" : "网络连接"
                }
                else{
                    return ""
                }
            }
            eqText4:{
                if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].pDeviceInformation.state
                }
                else if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].pDeviceInformation.state
                }
                else{
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
                    return DeviceManager.deviceList[3].pDeviceInformation.goodCycles
                }
                else if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].pDeviceInformation.goodCycles
                }
                else{
                    return ""
                }
            }
            eqText2:{
                if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].pDeviceInformation.suspectCycles
                }
                else if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].pDeviceInformation.suspectCycles
                }
                else{
                    return ""
                }
            }
            eqText3:{
                if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].pDeviceInformation.notDefinite
                }
                else if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].pDeviceInformation.notDefinite
                }
                else{
                    return ""
                }
            }
            eqText4:{
                if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].pDeviceInformation.goodCycles
                    + DeviceManager.deviceList[3].pDeviceInformation.notDefinite
                    +DeviceManager.deviceList[3].pDeviceInformation.suspectCycles
                }
                else if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].pDeviceInformation.goodCycles
                    + DeviceManager.deviceList[2].pDeviceInformation.notDefinite
                    +DeviceManager.deviceList[2].pDeviceInformation.suspectCycles
                }
                else{
                    return ""
                }
            }
            eqText5:{
                if(DeviceManager.deviceList[3]){
                    return DeviceManager.deviceList[3].pDeviceInformation.goodRate
                }
                else if(DeviceManager.deviceList[2]){
                    return DeviceManager.deviceList[2].pDeviceInformation.goodRate
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
                    source: "qrc:/image/full.png"
                }
            }
            onPressed: {
                if(equipmentCount === 4){
                    mpro.swipeIndex = 3
                }
                else{
                    mpro.swipeIndex = 2
                }
                loadViewpro(3,swipe)
                sigUpdateUI(3)
            }
        }
    }

//    Button{
//        id:b1
//        x:195
//        y:654
//        width: 243
//        height: 52
//        background: Rectangle{
//            radius: 6
//            color: pRgb(43, 112, 173)
//        }
//        contentItem: Text {
//            id:mt1
//            anchors.centerIn: parent
//            text: "新建模型"
//            font.pixelSize: 20
//            color: pRgb(153, 204, 255)
//            horizontalAlignment: Text.AlignHCenter
//            verticalAlignment: Text.AlignVCenter
//            font.family: fontBold
//        }
//        onClicked: {
//            mt1.text = "创建模型"
//            mt2.text = "清除数据"
//        }
//    }
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
            text: "新增设备"
            font.pixelSize: 20
            color: pRgb(153, 204, 255)
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: fontBold
        }
        onPressed: {
            if(mt2.text == "新增设备"){
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
            text: "系统消息"
            font.pixelSize: 20
            color: pRgb(153, 204, 255)
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: fontBold
        }
        onClicked: {
            popup.openPop(6)
        }
    }
    Text {
        id: version
        color: "#639ed6"
        x:895
        y:718
        font.family: fontBold
        font.pixelSize: 14
        text: qsTr("系统版本号: v2.0.1")
    }
    // 显示时间的文本
    Text {
        id: timeText
        anchors.left: version.right
        anchors.top: version.top
        anchors.leftMargin: 27
        font.pixelSize: 14
        font.family: fontBold
        color: "#639ed6"
        text: getCurrentTime()

        // 定时器每秒更新一次
        Timer {
            interval: 1  // 1秒
            repeat: true
            running: true
            onTriggered: {
                timeText.text = getCurrentTime()
            }
        }
    }
}
