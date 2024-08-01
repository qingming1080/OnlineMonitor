import QtQuick 2.0
import QtQuick.Controls 2.15
import Device 1.0
import DeviceInformation 1.0
import IO 1.0
//系统配置（小）
Rectangle {
    property string eqText1: ""
    property string eqText2: ""
    property string eqText3: ""
    property string eqText4: ""
    property int sysCurrIndex: 0
    property int sysCurrIndex1: 0
    property bool undetermined: {
        if(DeviceManager.deviceList[sysCurrIndex1-1]){
            return DeviceManager.deviceList[sysCurrIndex1-1].pIO.availabel
        }
        else{
            false
        }
    }
    property bool heightOpation: false

    signal sigAltitudeModel(var tmp)
    radius: 5
    width: 281
    height: 504
    color: pRgb(43, 112, 173)
    MouseArea{
        anchors.fill: parent
        onPressed: {
            if(color == "#4a8ac4"){
                color = pRgb(43, 112, 173)
                currIndex = 0
            }
            else{
                sysCheck(sysCurrIndex1)
                currIndex = sysCurrIndex
            }
        }
    }
    onVisibleChanged: {
        if(visible){
            enabled = true
        }
        else{
            enabled = false
        }
    }

    Text {
        text: qsTr("设备信息")
        font.family: fontBold
        font.pixelSize: 17
        color: pRgb(153, 204, 255)
        x:17
        y:9
    }
    Rectangle{
        y:42
        height: 1
        width: 97
        color: pRgb(174, 210, 216)
    }
    Text {
        id:t1
        text: qsTr("设备名称: ") + eqText1
        font.family: fontBold
        font.pixelSize: 14
        color: pRgb(171, 206, 213)
        x:26
        y:54
    }
    Text {
        id:t2
        text: qsTr("设备型号: ") + eqText2
        font.family: fontBold
        font.pixelSize: 14
        color: pRgb(171, 206, 213)
        anchors.top:t1.bottom
        anchors.left: t1.left
        anchors.topMargin: 24
    }
    Text {
        id:t3
        text: qsTr("连接方式: ") + eqText3
        font.family: fontBold
        font.pixelSize: 14
        color: pRgb(171, 206, 213)
        anchors.top:t2.bottom
        anchors.left: t2.left
        anchors.topMargin: 24
    }
    Text {
        id:t4
        text: qsTr("设备状态: ") + eqText4
        font.family: fontBold
        font.pixelSize: 14
        color: pRgb(171, 206, 213)
        anchors.top:t3.bottom
        anchors.left: t3.left
        anchors.topMargin: 24
    }
    Button{
        width: 25
        height: 25
        x:248
        y:7
        background: Rectangle{
            color: "transparent"
            Image {
                anchors.fill: parent
                source: "qrc:/image/full.png"
            }
        }
        onPressed: {
            loadViewsys(1,syscfg)
            currentConfigId = sysCurrIndex1
            sigUpdateUI(sysCurrIndex-1)
        }
    }
    Text {
        id: s4
        text: qsTr("高度模式")
        color: pRgb(177, 213, 219)
        font.family: fontBold
        font.pixelSize: 14
        x:26
        y:252
    }
    Text {
        id: s5
        text: qsTr("启动")
        color: pRgb(177, 213, 219)
        font.family: fontBold
        font.pixelSize: 14
        anchors.top: s4.top
        anchors.left: s4.right
        anchors.leftMargin: 62
        anchors.topMargin: 3
    }
    RadioButton{
        id:bt1
        width: 20
        height: 20
        x:113
        y:255
        indicator: Rectangle
        {
            width: 20
            height: 20
            radius: 10
            color: heightOpation ? "#0d988c" : pRgb(232, 232, 232)
            border.color: "#b1d5db"
            border.width: 2
        }
        onPressed: {
            sigAltitudeModel(true)
            sigUpdateUI(sysCurrIndex1)
            DeviceManager.deviceList[sysCurrIndex1-1].pDeviceInformation.setHeightOption(1)
        }
    }
    Text {
        id: s6
        text: qsTr("关闭")
        color: pRgb(177, 213, 219)
        font.family: fontBold
        font.pixelSize: 14
        anchors.top: s5.top
        anchors.left: s5.right
        anchors.leftMargin: 48
    }
    RadioButton{
        id:bt2
        width: 20
        height: 20
        anchors.left: bt1.right
        anchors.top: bt1.top
        anchors.leftMargin: 56
        checked: true
        indicator: Rectangle
        {
            width: 20
            height: 20
            radius: 10
            color: !heightOpation ? "#0d988c" : pRgb(232, 232, 232)
            border.color: "#b1d5db"
            border.width: 2
        }
        onPressed: {
            sigAltitudeModel(false)
            sigUpdateUI(sysCurrIndex1)
            DeviceManager.deviceList[sysCurrIndex1-1].pDeviceInformation.setHeightOption(0)
        }
    }
    Text {
        id: s7
        text: qsTr("是否开启待定")
        color: "#99ccff"
        font.family: fontBold
        font.pixelSize: 17
        x:24
        y:319
    }
    Switch{
        id:ctl
        x:150
        y:317
        onPressed: {
            if(sysCurrIndex1 == 1){
                undetermined1 = !undetermined1
            }
            else if(sysCurrIndex1 ==2){
                undetermined2 = !undetermined2
            }
            else if(sysCurrIndex1 ==3){
                undetermined3 = !undetermined3
            }
            else if(sysCurrIndex1 ==4){
                undetermined4 = !undetermined4
            }
//            sigUndetermined(sysCurrIndex)
            DeviceManager.deviceList[sysCurrIndex1-1].pIO.setAvailabel(!ctl.checked)
        }

        indicator: Rectangle{
            id:indicator
            implicitWidth: 118
            implicitHeight:27
            x:ctl.leftPadding
            y:parent.height / 2 - height / 2
            border.width: 3
            radius: 15
            color: pRgb(232, 232, 232)
            border.color: "#99ccff"
            //小圆点
            Rectangle{
                id:smallRect
                width: 58
                height: 22
                radius: 15
                border.width: 3
                color: "#2b70ad"
                border.color: "#99ccff"
                anchors.verticalCenter: parent.verticalCenter
                //改变小圆点位置
                NumberAnimation on x{
                    to:smallRect.width
                    running: undetermined
                    duration: 0
                }
                NumberAnimation on x{
                    to:6
                    running: !undetermined
                    duration: 0
                }
            }
            Text {
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.topMargin: 3
                anchors.leftMargin: 14
                text: qsTr("关闭")
                color: undetermined? pRgb(43, 112, 173) : "#e5e6e7"
                font.family: fontBold
                font.pixelSize: 14
            }
            Text {
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: 3
                anchors.rightMargin: 14
                text: qsTr("启动")
                color: undetermined? "#e5e6e7" : pRgb(43, 112, 173)
                font.family: fontBold
                font.pixelSize: 14
            }
        }
    }
    Text {
        id: s8
        text: sysCurrIndex1 === 1 ? "PIN1" : sysCurrIndex1 === 2 ? "PIN4" :
        sysCurrIndex1 === 3 ? "PIN7" : sysCurrIndex1 === 4 ? "PIN10" : ""
        color: pRgb(177, 213, 219)
        font.family: fontBold
        font.pixelSize: 16
        x:18
        y:380
    }
    Text {
        id: s9
        text: sysCurrIndex1 === 1 ? "PIN2" : sysCurrIndex1 === 2 ? "PIN5" :
        sysCurrIndex1 === 3 ? "PIN8" : sysCurrIndex1 === 4 ? "PIN11" : ""
        color: pRgb(177, 213, 219)
        font.family: fontBold
        font.pixelSize: 16
        anchors.left: s8.left
        anchors.top: s8.bottom
        anchors.topMargin: 15
    }
    Text {
        id: s10
        text: sysCurrIndex1 === 1 ? "PIN3" : sysCurrIndex1 === 2 ? "PIN6" :
        sysCurrIndex1 === 3 ? "PIN9" : sysCurrIndex1 === 4 ? "PIN12" : ""
        color: pRgb(177, 213, 219)
        font.family: fontBold
        font.pixelSize: 16
        anchors.left: s9.left
        anchors.top: s9.bottom
        anchors.topMargin: 15
    }
    Image {
        id: im1
        source: "qrc:/image/alarm.png"
        x:93
        y:379
        width: 22
        height: 22
    }
    Image {
        id: im2
        source: "qrc:/image/restoration.png"
        anchors.left: im1.left
        anchors.top: im1.bottom
        anchors.topMargin: 18
        width: 22
        height: 22
    }
    Image {
        id: im3
        source: undetermined ? "qrc:/image/undetermined.png" : "qrc:/image/undetermined1.png"
        anchors.left: im2.left
        anchors.top: im2.bottom
        anchors.topMargin: 18
        width: 22
        height: 22
    }
    Text {
        id: s11
        text: qsTr("报警")
        color: pRgb(177, 213, 219)
        font.family: fontBold
        font.pixelSize: 16
        anchors.top: s8.top
        anchors.left: s8.right
        anchors.leftMargin: 109
    }
    Text {
        id: s12
        text: qsTr("复位")
        color: pRgb(177, 213, 219)
        font.family: fontBold
        font.pixelSize: 16
        anchors.top: s9.top
        anchors.left: s9.right
        anchors.leftMargin: 109
    }
    Text {
        id: s13
        text: qsTr("待定")
        color: pRgb(177, 213, 219)
        font.family: fontBold
        font.pixelSize: 16
        anchors.top: s10.top
        anchors.left: s10.right
        anchors.leftMargin: 109
    }
}
