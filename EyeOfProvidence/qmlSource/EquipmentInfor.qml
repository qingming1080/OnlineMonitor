import QtQuick 2.0
import GlobalLanguageDefine 1.0
import GlobalSystemDefine 1.0
import LanguageEnum 1.0
//设备信息
Rectangle {
    property string deviceName: ""
    property string deviceType: ""
    property string connectionType: ""
    property string devcieStatus: ""
    property int    sampleCount: 0
    property bool   isLearning: false
    color: pRgb(43, 112, 173)
    radius: 3
    width:  258
    //TODO Need to have a double check
    height: 255
    Item{
        anchors.left: parent.left
        anchors.top: parent.top
        width: parent.width
        height: 40
        Text {
            id: titleDeviceInfo
            // text: qsTr("设备信息")
            text: GlobalLanguageDefine.strEquipmentInfo
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
            font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 20 : 18
            color: pRgb(153, 204, 255)
            height: parent.height
            anchors.left: parent.left
            anchors.leftMargin: 17
            anchors.top: parent.top
            anchors.topMargin: 9
        }

        Text {
            text: GlobalLanguageDefine.strSample + ": " + sampleCount
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
            font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 20 : 18
            color: pRgb(153, 204, 255)
            anchors.top: titleDeviceInfo.top
            anchors.right: parent.right
            anchors.rightMargin: 10
            height: parent.height
            visible: isLearning
        }
    }


    //    CustomComboBox{
    //        id:com1
    //        width: 100
    //        height: 40
    //        anchors.top: parent.top
    //        anchors.topMargin: 10
    //        anchors.right: parent.right
    //        anchors.rightMargin: 20
    //        model: DeviceNames
    //        currentIndex: swipeCurrIndex
    //        onDataAlter: {
    //            swipeCurrIndex = com1.currentIndex
    //        }
    //        visible: switchingEquipment
    //    }
    Rectangle{
        y:42
        height: 1
        width: 97
        color: pRgb(174, 210, 216)
    }
    Text {
        id:t1
        // text: qsTr("设备名称") + ": " + eqText1
        text: GlobalLanguageDefine.strDeviceName + ": " + deviceName
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 16 : 14
        color: pRgb(171, 206, 213)
        x:/*mode === 1 ? 33 :*/ 39
        y:/*mode === 1 ? 54 :*/ 63
    }
    Text {
        id:t2
        // text: qsTr("设备型号") + ": " + eqText2
        text: GlobalLanguageDefine.strDeviceModel + ": " + deviceType
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 16 : 14
        color: pRgb(171, 206, 213)
        anchors.top:t1.bottom
        anchors.left: t1.left
        anchors.topMargin: 21
    }
    Text {
        id:t3
        // text: qsTr("连接方式") + ": " + eqText3
        text: GlobalLanguageDefine.strConnectionMethod + ": " + connectionType
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 16 : 14
        color: pRgb(171, 206, 213)
        anchors.top:t2.bottom
        anchors.left: t2.left
        anchors.topMargin: 21
    }
    Text {
        id:t4
        // text: qsTr("设备状态") + ": " + eqText4
        text: GlobalLanguageDefine.strDeviceStatus + ": " + devcieStatus
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 16 : 14
        color: pRgb(171, 206, 213)
        anchors.top:t3.bottom
        anchors.left: t3.left
        anchors.topMargin: 21
    }
}
