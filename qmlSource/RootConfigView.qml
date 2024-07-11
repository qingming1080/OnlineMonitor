import QtQuick 2.0
import QtQuick.Controls 2.15
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
        eqText1: System1.singleFact
        eqText2: System1.generalFact
        eqText3: System1.otherFace
        eqText4: System1.autoModel

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
        eqText1: System2.singleFact
        eqText2: System2.generalFact
        eqText3: System2.otherFace
        eqText4: System2.autoModel
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
        eqText1: System3.singleFact
        eqText2: System3.generalFact
        eqText3: System3.otherFace
        eqText4: System3.autoModel
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
        eqText1: System4.singleFact
        eqText2: System4.generalFact
        eqText3: System4.otherFace
        eqText4: System4.autoModel
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
            System1.setSingleFact(s1.t1Edit.text)
            System1.setGeneralFact(s1.t2Edit.text)
            System1.setOtherFace(s1.t3Edit.text)
            System1.setAutoModel(s1.t4Edit.text)
            System2.setSingleFact(s2.t1Edit.text)
            System2.setGeneralFact(s2.t2Edit.text)
            System2.setOtherFace(s2.t3Edit.text)
            System2.setAutoModel(s2.t4Edit.text)
            System3.setSingleFact(s3.t1Edit.text)
            System3.setGeneralFact(s3.t2Edit.text)
            System3.setOtherFace(s3.t3Edit.text)
            System3.setAutoModel(s3.t4Edit.text)
            System4.setSingleFact(s4.t1Edit.text)
            System4.setGeneralFact(s4.t2Edit.text)
            System4.setOtherFace(s4.t3Edit.text)
            System4.setAutoModel(s4.t4Edit.text)
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
