import QtQuick 2.0
import QtQuick.Controls 2.15
import Device 1.0

import GlobalLanguageDefine 1.0
import DeviceObj            1.0
import DeviceInfoEnum       1.0
import GlobalSystemDefine 1.0
//系统配置（小）
Rectangle {
    id: multiDeviceConfigure
    property string nameWelder: ""
    property int typeWelder: 0
    property int typeConnect: 0
    property bool isConnected: false
    property int currentIndex: -1
    property bool suspiciousOption: false
    property bool heightOption: false
    property alias backgroundColor: multiDeviceConfigure.color

    signal signalWelderSelected(var index)
    signal signalFreshConnected(var index)
    radius: 5
    width: 281
    height: 550
    color: "#2B70AD"
    MouseArea{
        anchors.fill: parent
        onPressed: {
            signalWelderSelected(currentIndex)
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
        // text: qsTr("设备信息")
        id: titleDeviceInfo
        text: GlobalLanguageDefine.strEquipmentInfo
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 20
        color: pRgb(153, 204, 255)
        // x:17
        // y:9
        anchors.top: parent.top
        anchors.topMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 20
    }
    Rectangle{
        anchors.top: titleDeviceInfo.bottom
        height: 1
        width: 97
        color: pRgb(174, 210, 216)
    }
    Text {
        id: deviceNameText
        // text: qsTr("设备名称") + ": " + eqText1
        text: GlobalLanguageDefine.strDeviceName + ": " + nameWelder
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        color: pRgb(171, 206, 213)
        // x:26
        // y:54
        anchors.top: parent.top
        anchors.topMargin: 60
        anchors.left: parent.left
        anchors.leftMargin: 30
    }
    Text {
        id: titleDeviceType
        // text: qsTr("设备型号") + ": " + eqText2
        text: {
            var str = GlobalLanguageDefine.strDeviceModel + ": "
            switch(typeWelder)
            {
            case DeviceInfoEnum.L20_VG:
                str += "L20_VG";
                break;
            case DeviceInfoEnum.L20_TS:
                str += "L20_TS";
                break;
            case DeviceInfoEnum.BRANSON_2000XC:
                str += "2000XC";
                break;
            default:
                str += "Other";
                break;
            }
            return str;
        }
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        color: pRgb(171, 206, 213)
        anchors.top:deviceNameText.bottom
        anchors.left: deviceNameText.left
        anchors.topMargin: 30
    }
    Text {
        id: titleConnectionType
        // text: qsTr("连接方式") + ": " + eqText3
        text: {
            var str = GlobalLanguageDefine.strConnectionMethod + ": "
            switch(typeConnect)
            {
            case DeviceInfoEnum.TCP_IP:
                str += "TCP/IP"
                break;
            case DeviceInfoEnum.RS232:
                str += "RS232"
                break;
            default:
                str += "TCP/IP"
                break;
            }
            return str
        }
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        color: pRgb(171, 206, 213)
        anchors.top:titleDeviceType.bottom
        anchors.left: titleDeviceType.left
        anchors.topMargin: 30
    }
    Text {
        id: titleDeviceStatus
        // text: qsTr("设备状态") + ": " + eqText4
        text: {
            var str = GlobalLanguageDefine.strDeviceStatus + ": "
            var isConnected = DeviceManager.DeviceList[currentIndex].DeviceObj.ConnectState
            str += GlobalMessageDefine.getConnectState(isConnected)
            return str
        }
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        color: pRgb(171, 206, 213)
        anchors.top: titleConnectionType.bottom
        anchors.left: titleConnectionType.left
        anchors.topMargin: 30
    }
    Button{
        width: 30
        height: 30
        x:248
        y:7
        background: Rectangle{
            color: "transparent"
            Image {
                anchors.fill: parent
                source: "qrc:/images/btn_fullscreen_enter.png"
            }
        }
        onPressed: {
            signalWelderSelected(currentIndex)
            loadViewsys(1, syscfg)
        }
    }
    Text {
        id: titleHeightOption
        // text: qsTr("高度模式")
        text: GlobalLanguageDefine.strHeightMode + ": "
        color: pRgb(177, 213, 219)
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        anchors.left: titleDeviceStatus.left
        anchors.top: titleDeviceStatus.bottom
        anchors.topMargin: 30
        // x:26
        // y:252
    }
    Text {
        id: s5
        // text: qsTr("启动")
        text: heightOption ? GlobalLanguageDefine.strStart : GlobalLanguageDefine.strClose
        color: pRgb(177, 213, 219)
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        anchors.verticalCenter: titleHeightOption.verticalCenter
        anchors.left: titleHeightOption.right
        anchors.leftMargin: 5
    }
    // RadioButton{
    //     id:bt1
    //     width: 30
    //     height: 30
    //     anchors.verticalCenter: s4.verticalCenter
    //     anchors.left: s4.right
    //     anchors.leftMargin: 10
    //     indicator: Rectangle
    //     {
    //         width: 30
    //         height: 30
    //         radius: 15
    //         color: heightOption ? "#0d988c" : pRgb(232, 232, 232)
    //         border.color: "#b1d5db"
    //         border.width: 2
    //     }
    // }

    // Text {
    //     id: s6
    //     // text: qsTr("关闭")
    //     text: GlobalLanguageDefine.strClose
    //     color: pRgb(177, 213, 219)
    //     font.family: GlobalSystemDefine.fontBold
    //     font.bold: true
    //     font.pixelSize: 16
    //     anchors.verticalCenter: bt2.verticalCenter
    //     anchors.left: bt2.right
    //     anchors.leftMargin: 5
    // }
    // RadioButton{
    //     id:bt2
    //     width: 30
    //     height: 30
    //     anchors.verticalCenter: s5.verticalCenter
    //     anchors.left: s5.right
    //     anchors.leftMargin: 8
    //     checked: true
    //     indicator: Rectangle
    //     {
    //         width: 30
    //         height: 30
    //         radius: 15
    //         color: !heightOption ? "#0d988c" : pRgb(232, 232, 232)
    //         border.color: "#b1d5db"
    //         border.width: 2
    //     }
    // }
    Text {
        id: s7
        // text: qsTr("是否开启待定")
        text: GlobalLanguageDefine.strOpenPending + ": "
        color: "#b1d5db"
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        anchors.top: titleHeightOption.bottom
        anchors.topMargin: 30
        anchors.left: titleHeightOption.left
        // x:24
        // y:319
    }

    Text {
        id: openPendingtext
        text: suspiciousOption ? GlobalLanguageDefine.strStart : GlobalLanguageDefine.strClose
        color: pRgb(177, 213, 219)
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        anchors.verticalCenter: s7.verticalCenter
        anchors.left: s7.right
        anchors.leftMargin: 5
    }

    Text {
        id: pinAlarmTitle
        text:{
            var pinName = ""
            switch(currentIndex)
            {
            case 0:
                pinName = "PIN1"
                break;
            case 1:
                pinName = "PIN4"
                break;
            case 2:
                pinName = "PIN7"
                break;
            case 3:
                pinName = "PIN10"
                break;
            default:
                break;
            }
            return pinName
        }
        color: pRgb(177, 213, 219)
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        verticalAlignment: Text.AlignVCenter
        anchors.left: s7.left
        anchors.top: parent.top
        anchors.topMargin: 380
    }
    Text {
        id: pinResetTitle
        text: {
            var pinName = ""
            switch(currentIndex)
            {
            case 0:
                pinName = "PIN2"
                break;
            case 1:
                pinName = "PIN5"
                break;
            case 2:
                pinName = "PIN8"
                break;
            case 3:
                pinName = "PIN11"
                break;
            default:
                break;
            }
            return pinName
        }
        color: pRgb(177, 213, 219)
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        verticalAlignment: Text.AlignVCenter
        anchors.left: pinAlarmTitle.left
        anchors.top: pinAlarmTitle.bottom
        anchors.topMargin: 15
    }
    Text {
        id: pinSuspectTitle
        text: {
            var pinName = ""
            switch(currentIndex)
            {
            case 0:
                pinName = "PIN3"
                break;
            case 1:
                pinName = "PIN6"
                break;
            case 2:
                pinName = "PIN9"
                break;
            case 3:
                pinName = "PIN12"
                break;
            default:
                break;
            }
            return pinName
        }
        color: pRgb(177, 213, 219)
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        verticalAlignment: Text.AlignVCenter
        anchors.left: pinResetTitle.left
        anchors.top: pinResetTitle.bottom
        anchors.topMargin: 15
    }
    Image {
        id: pinAlarmIcon
        source: "qrc:/images/icon_io_alarm"
        anchors.left: pinAlarmTitle.right
        anchors.leftMargin: 50
        anchors.verticalCenter: pinAlarmTitle.verticalCenter
        width: 22
        height: 22
    }
    Image {
        id: pinResetIcon
        source: "qrc:/images/icon_io_reset.png"
        anchors.left: pinAlarmIcon.left
        anchors.verticalCenter: pinResetTitle.verticalCenter
        width: 22
        height: 22
    }
    Image {
        id: pinSuspectIcon
        source: suspiciousOption ? "qrc:/images/icon_io_suspicious_on.png" : "qrc:/images/icon_io_suspicious_off.png"
        anchors.left: pinAlarmIcon.left
        anchors.verticalCenter: pinSuspectTitle.verticalCenter
        width: 22
        height: 22
    }
    Text {
        id: pinAlarmName
        // text: qsTr("报警")
        text: GlobalLanguageDefine.strAlarm
        color: pRgb(177, 213, 219)
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        verticalAlignment: Text.AlignVCenter
        anchors.top: pinAlarmTitle.top
        anchors.left: pinAlarmIcon.right
        anchors.leftMargin: 50
    }
    Text {
        id: pinResetName
        // text: qsTr("复位")
        text: GlobalLanguageDefine.strReset
        color: pRgb(177, 213, 219)
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        verticalAlignment: Text.AlignVCenter
        anchors.top: pinResetTitle.top
        anchors.left: pinAlarmName.left
    }
    Text {
        id: pinSuspectName
        // text: qsTr("待定")
        text: GlobalLanguageDefine.strPending
        color: pRgb(177, 213, 219)
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        verticalAlignment: Text.AlignVCenter
        anchors.top: pinSuspectTitle.top
        anchors.left: pinAlarmName.left
    }

    HBPrimaryButton {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        text: GlobalLanguageDefine.strRefresh
        onPressed: {
            signalFreshConnected(currentIndex)
        }
    }
}
