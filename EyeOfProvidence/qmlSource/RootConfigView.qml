import QtQuick              2.0
import QtQuick.Controls     2.15
import Device               1.0
import GlobalLanguageDefine 1.0
import GlobalSystemDefine   1.0
import GlobalMessageDefine  1.0
Rectangle {
    radius: 5
    color: pRgb(153, 204, 255)
    RootConfig{
        id:s1
        width: 300
        height: 613
        x:21
        y:25
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
            // text: qsTr("客户密码重置")
            text: GlobalLanguageDefine.strCustomerPasswordReset
            font.pixelSize: 20
            color: pRgb(153, 204, 255)
            anchors.centerIn: parent  // 确保文本在按钮内居中对齐
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
        }
        onPressed: {

        }
    }
    Button{
        id:rootSaveButton
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
        width: 243
        height: 52
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: pRgb(43, 112, 173)
            // color: pRgb(43, 112, 173)
            color: pRgb(153, 204, 255)
        }
        contentItem: Text {
            // text: qsTr("保存")
            text: GlobalLanguageDefine.strSave
            font.pixelSize: 20
            color: pRgb(43, 112, 173)
            anchors.centerIn: parent  // 确保文本在按钮内居中对齐
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
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
            // text: qsTr("初始化")
            text: GlobalLanguageDefine.strInitialize
            font.pixelSize: 20
            color: pRgb(153, 204, 255)
            anchors.centerIn: parent  // 确保文本在按钮内居中对齐
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
        }
        onPressed: {

        }
    }
}
