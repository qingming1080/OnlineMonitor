import QtQuick 2.0
//设备信息
Rectangle {
    property string eqText1: ""
    property string eqText2: ""
    property string eqText3: ""
    property string eqText4: ""
    color: pRgb(43, 112, 173)
    radius: 3
    Text {
        text: qsTr("设备信息")
        font.family: fontBold
        font.bold: true
        font.pixelSize: LanguageManger.language === "SimplifiedChinese" ? 20 : 18
        color: pRgb(153, 204, 255)
        x:17
        y:9
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
    //            sigUpdateUI(swipeCurrIndex)
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
        text: qsTr("设备名称: ") + eqText1
        font.family: fontBold
        font.bold: true
        font.pixelSize: LanguageManger.language === "SimplifiedChinese" ?16 : 14
        color: pRgb(171, 206, 213)
        x:/*mode === 1 ? 33 :*/ 39
        y:/*mode === 1 ? 54 :*/ 63
    }
    Text {
        id:t2
        text: qsTr("设备型号: ") + eqText2
        font.family: fontBold
        font.bold: true
        font.pixelSize: LanguageManger.language === "SimplifiedChinese" ?16 : 14
        color: pRgb(171, 206, 213)
        anchors.top:t1.bottom
        anchors.left: t1.left
        anchors.topMargin: 21
    }
    Text {
        id:t3
        text: qsTr("连接方式: ") + eqText3
        font.family: fontBold
        font.bold: true
        font.pixelSize: LanguageManger.language === "SimplifiedChinese" ?16 : 14
        color: pRgb(171, 206, 213)
        anchors.top:t2.bottom
        anchors.left: t2.left
        anchors.topMargin: 21
    }
    Text {
        id:t4
        text: qsTr("设备状态: ") + eqText4
        font.family: fontBold
        font.bold: true
        font.pixelSize: LanguageManger.language === "SimplifiedChinese" ?16 : 14
        color: pRgb(171, 206, 213)
        anchors.top:t3.bottom
        anchors.left: t3.left
        anchors.topMargin: 21
    }
}
