import QtQuick 2.0
import QtQuick.Controls 2.15
import Device 1.0
import System 1.0
Rectangle {
    radius: 5
    color: pRgb(153, 204, 255)
    RootConfig{
        id:s1
        width: 300
        height: 613
        x:21
        y:25
        name: {
            if(DeviceManager.deviceList[0]){
                return DeviceManager.deviceList[0].pDeviceInformation.name
            }
            else{
                return ""
            }
        }
        model: {
            if(DeviceManager.deviceList[0]){
                return DeviceManager.deviceList[0].pDeviceInformation.model
            }
            else{
                return ""
            }
        }
        eqText1: {
            if(DeviceManager.deviceList[0]){
                return DeviceManager.deviceList[0].pSystem.singleFact
            }
            else{
                return ""
            }
        }
        eqText2: {
            if(DeviceManager.deviceList[0]){
                return DeviceManager.deviceList[0].pSystem.generalFact
            }
            else{
                return ""
            }
        }
        eqText3: {
            if(DeviceManager.deviceList[0]){
                return DeviceManager.deviceList[0].pSystem.otherFace
            }
            else{
                return ""
            }
        }
        eqText4: {
            if(DeviceManager.deviceList[0]){
                return DeviceManager.deviceList[0].pSystem.autoModel
            }
            else{
                return ""
            }
        }

    }
    RootConfig{
        id:s2
        width: 300
        height: 613
        x:334
        y:25
        name: {
            if(DeviceManager.deviceList[1]){
                return DeviceManager.deviceList[1].pDeviceInformation.name
            }
            else{
                return ""
            }
        }
        model: {
            if(DeviceManager.deviceList[1]){
                return DeviceManager.deviceList[1].pDeviceInformation.model
            }
            else{
                return ""
            }
        }
        eqText1: {
            if(DeviceManager.deviceList[1]){
                return DeviceManager.deviceList[1].pSystem.singleFact
            }
            else{
                return ""
            }
        }
        eqText2: {
            if(DeviceManager.deviceList[1]){
                return DeviceManager.deviceList[1].pSystem.generalFact
            }
            else{
                return ""
            }
        }
        eqText3: {
            if(DeviceManager.deviceList[1]){
                return DeviceManager.deviceList[1].pSystem.otherFace
            }
            else{
                return ""
            }
        }
        eqText4: {
            if(DeviceManager.deviceList[1]){
                return DeviceManager.deviceList[1].pSystem.autoModel
            }
            else{
                return ""
            }
        }
        visible: equipmentCount>=2 ? true : false
    }
    RootConfig{
        id:s3
        width: 300
        height: 613
        x:648
        y:25
        name: {
            if(DeviceManager.deviceList[2]){
                return DeviceManager.deviceList[2].pDeviceInformation.name
            }
            else{
                return ""
            }
        }
        model: {
            if(DeviceManager.deviceList[2]){
                return DeviceManager.deviceList[2].pDeviceInformation.model
            }
            else{
                return ""
            }
        }
        eqText1: {
            if(DeviceManager.deviceList[2]){
                return DeviceManager.deviceList[2].pSystem.singleFact
            }
            else{
                return ""
            }
        }
        eqText2: {
            if(DeviceManager.deviceList[2]){
                return DeviceManager.deviceList[2].pSystem.generalFact
            }
            else{
                return ""
            }
        }
        eqText3: {
            if(DeviceManager.deviceList[2]){
                return DeviceManager.deviceList[2].pSystem.otherFace
            }
            else{
                return ""
            }
        }
        eqText4: {
            if(DeviceManager.deviceList[2]){
                return DeviceManager.deviceList[2].pSystem.autoModel
            }
            else{
                return ""
            }
        }
        visible: equipmentCount>=3 ? true : false
    }
    RootConfig{
        id:s4
        width: 300
        height: 613
        x:963
        y:25
        name: {
            if(DeviceManager.deviceList[3]){
                return DeviceManager.deviceList[3].pDeviceInformation.name
            }
            else{
                return ""
            }
        }
        model: {
            if(DeviceManager.deviceList[3]){
                return DeviceManager.deviceList[3].pDeviceInformation.model
            }
            else{
                return ""
            }
        }
        eqText1: {
            if(DeviceManager.deviceList[3]){
                return DeviceManager.deviceList[3].pSystem.singleFact
            }
            else{
                return ""
            }
        }
        eqText2: {
            if(DeviceManager.deviceList[3]){
                return DeviceManager.deviceList[3].pSystem.generalFact
            }
            else{
                return ""
            }
        }
        eqText3: {
            if(DeviceManager.deviceList[3]){
                return DeviceManager.deviceList[3].pSystem.otherFace
            }
            else{
                return ""
            }
        }
        eqText4: {
            if(DeviceManager.deviceList[3]){
                return DeviceManager.deviceList[3].pSystem.autoModel
            }
            else{
                return ""
            }
        }
        visible: equipmentCount>=4 ? true : false
    }
    Button{
        id:btn1
        x:165
        y:654
        width: 243
        height: 52
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: pRgb(43, 112, 173)
            color: pRgb(43, 112, 173)
        }
        contentItem: Text {
            text: "客户密码重置"
            font.pixelSize: 20
            color: pRgb(153, 204, 255)
            anchors.centerIn: parent  // 确保文本在按钮内居中对齐
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: fontBold
        }
        onPressed: {

        }
    }
    Button{
        id:btn2
        x:519
        y:654
        width: 243
        height: 52
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: pRgb(43, 112, 173)
            color: pRgb(43, 112, 173)
        }
        contentItem: Text {
            text: "保存"
            font.pixelSize: 20
            color: pRgb(153, 204, 255)
            anchors.centerIn: parent  // 确保文本在按钮内居中对齐
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: fontBold
        }
        onPressed: {
            if(DeviceManager.deviceList[0]){
                DeviceManager.deviceList[0].pSystem.setSingleFact(s1.t1Edit.text)
                DeviceManager.deviceList[0].pSystem.setGeneralFact(s1.t2Edit.text)
                DeviceManager.deviceList[0].pSystem.setOtherFace(s1.t3Edit.text)
                DeviceManager.deviceList[0].pSystem.setAutoModel(s1.t4Edit.text)
            }
            if(DeviceManager.deviceList[1]){
                DeviceManager.deviceList[1].pSystem.setSingleFact(s2.t1Edit.text)
                DeviceManager.deviceList[1].pSystem.setGeneralFact(s2.t2Edit.text)
                DeviceManager.deviceList[1].pSystem.setOtherFace(s2.t3Edit.text)
                DeviceManager.deviceList[1].pSystem.setAutoModel(s2.t4Edit.text)
            }
            if(DeviceManager.deviceList[2]){
                DeviceManager.deviceList[2].pSystem.setSingleFact(s3.t1Edit.text)
                DeviceManager.deviceList[2].pSystem.setGeneralFact(s3.t2Edit.text)
                DeviceManager.deviceList[2].pSystem.setOtherFace(s3.t3Edit.text)
                DeviceManager.deviceList[2].pSystem.setAutoModel(s3.t4Edit.text)
            }
            if(DeviceManager.deviceList[3]){
                DeviceManager.deviceList[3].pSystem.setSingleFact(s4.t1Edit.text)
                DeviceManager.deviceList[3].pSystem.setGeneralFact(s4.t2Edit.text)
                DeviceManager.deviceList[3].pSystem.setOtherFace(s4.t3Edit.text)
                DeviceManager.deviceList[3].pSystem.setAutoModel(s4.t4Edit.text)
            }
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
            border.width: 2
            border.color: pRgb(43, 112, 173)
            color: pRgb(43, 112, 173)
        }
        contentItem: Text {
            text: "初始化"
            font.pixelSize: 20
            color: pRgb(153, 204, 255)
            anchors.centerIn: parent  // 确保文本在按钮内居中对齐
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: fontBold
        }
        onPressed: {

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
