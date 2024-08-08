import QtQuick 2.0
import QtQuick.Controls 2.15
//焊接参数
Rectangle {
    color: pRgb(43, 112, 173)
    property string eqText1: ""
    property string eqText2: ""
    property string eqText3: ""
    property string eqText4: ""
    property string eqText5: ""
    property bool altitudeMode:DeviceManager.deviceList[swipeCurrIndex].pDeviceInformation.heightOption
                               === 1 ? true:false
    radius: 3
    Rectangle{
        y:42
        height: 1
        width: 97
        color: pRgb(174, 210, 216)
    }
    Text {
        text: qsTr("焊接参数")
        font.family: fontBold
        font.bold: true
        font.pixelSize: LanguageManger.language === "SimplifiedChinese" ? 20 : 18
        color: pRgb(153, 204, 255)
        x:17
        y:9
    }
    Image {
        id: im1
        source: "qrc:/image/shake.png"
        x:altitudeMode ? 17:30
        y:altitudeMode ? 50:58
        width: altitudeMode ? 25:30
        height: altitudeMode ? 25:30
    }
    Image {
        id: im2
        source: "qrc:/image/amplitude.png"
        anchors.top: im1.bottom
        anchors.left: im1.left
        anchors.topMargin: altitudeMode ? 12 :22
        width: altitudeMode ? 25:30
        height: altitudeMode ? 25:30
    }
    Image {
        id: im3
        source: "qrc:/image/pressure.png"
        anchors.top: im2.bottom
        anchors.left: im2.left
        anchors.topMargin: altitudeMode ? 12 :22
        width: altitudeMode ? 25:30
        height: altitudeMode ? 25:30
    }
    Image {
        id: im4
        source: "qrc:/image/height.png"
        anchors.top: im3.bottom
        anchors.left: im3.left
        anchors.topMargin: altitudeMode ? 12 :22
        visible: altitudeMode
        width: altitudeMode ? 25:30
        height: altitudeMode ? 25:30
    }
    Image {
        id: im5
        source: "qrc:/image/height.png"
        anchors.top: im4.bottom
        anchors.left: im4.left
        anchors.topMargin: altitudeMode ? 12 :22
        visible: altitudeMode
        width: altitudeMode ? 25:30
        height: altitudeMode ? 25:30
    }
    Text {
        id: t1
        text: qsTr("能量")
        font.family: fontBold
        font.bold: true
        font.pixelSize: LanguageManger.language === "SimplifiedChinese" ? 16 : 14
        color: pRgb(171, 206, 213)
        anchors.verticalCenter: im1.verticalCenter
        anchors.left: im1.right
        anchors.leftMargin: 10
    }
    Text {
        id: t2
        text: qsTr("振幅")
        font.family: fontBold
        font.bold: true
        font.pixelSize: LanguageManger.language === "SimplifiedChinese" ? 16 : 14
        color: pRgb(171, 206, 213)
        anchors.verticalCenter: im2.verticalCenter
        anchors.left: im2.right
        anchors.leftMargin: 10
    }
    Text {
        id: t3
        text: qsTr("压力")
        font.family: fontBold
        font.bold: true
        font.pixelSize: LanguageManger.language === "SimplifiedChinese" ? 16 : 14
        color: pRgb(171, 206, 213)
        anchors.verticalCenter: im3.verticalCenter
        anchors.left: im3.right
        anchors.leftMargin: 10
    }
    Text {
        id: t4
        text: qsTr("焊前高度")
        font.family: fontBold
        font.bold: true
        font.pixelSize: LanguageManger.language === "SimplifiedChinese" ? 16 : 14
        color: pRgb(171, 206, 213)
        anchors.verticalCenter: im4.verticalCenter
        anchors.left: im4.right
        anchors.leftMargin: 10
        visible: altitudeMode
    }
    Text {
        id: t5
        text: qsTr("焊后高度")
        font.family: fontBold
        font.bold: true
        font.pixelSize: LanguageManger.language === "SimplifiedChinese" ? 16 : 14
        color: pRgb(171, 206, 213)
        anchors.verticalCenter: im5.verticalCenter
        anchors.left: im5.right
        anchors.leftMargin: 10
        visible: altitudeMode
    }
    TextField{
        id:f1
        width: /*mode === 1 ? 75:*/98
        height: altitudeMode ? 28 :30
        anchors.left: t1.right
        anchors.leftMargin: altitudeMode ? 38:25
        anchors.verticalCenter: t1.verticalCenter
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter
        color: pRgb(43, 112, 173)
        font.family: fontBold
        font.bold: true
        font.pixelSize: 18
        inputMethodHints: Qt.ImhDigitsOnly
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: "#99ccff"
        }
        text:eqText1
        MouseArea {
            anchors.fill: parent
            onPressed: {
                f1.forceActiveFocus()
                keyboardYype = 0
            }
        }
    }
    TextField{
        id:f2
        width: /*mode === 1 ? 75:*/98
        height: altitudeMode ? 28 :30
        anchors.horizontalCenter: f1.horizontalCenter
        anchors.top: f1.bottom
        anchors.topMargin: !altitudeMode ? 23 : 10
        anchors.right:  f1.right
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter
        color: pRgb(43, 112, 173)
        font.family: fontBold
        font.bold: true
        font.pixelSize: 18
        inputMethodHints: Qt.ImhDigitsOnly
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: "#99ccff"
        }
        text:eqText2
        MouseArea {
            anchors.fill: parent
            onPressed: {
                f2.forceActiveFocus()
                keyboardYype = 0
            }
        }
    }
    TextField{
        id:f3
        width: /*mode === 1 ? 75:*/98
        height: altitudeMode ? 28 :30
        anchors.horizontalCenter: f2.horizontalCenter
        anchors.top: f2.bottom
        anchors.topMargin: !altitudeMode ? 23 : 10
        anchors.right:  f2.right
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter
        color: pRgb(43, 112, 173)
        font.family: fontBold
        font.bold: true
        font.pixelSize: 18
        inputMethodHints: Qt.ImhDigitsOnly
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: "#99ccff"
        }
        text:eqText3
        MouseArea {
            anchors.fill: parent
            onPressed: {
                f3.forceActiveFocus()
                keyboardYype = 0
            }
        }
    }
    TextField{
        id:f4
        width: /*mode === 1 ? 75:*/98
        height: altitudeMode ? 28 :30
        anchors.horizontalCenter: f3.horizontalCenter
        anchors.top: f3.bottom
        anchors.topMargin: 10
        anchors.right:  f3.right
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter
        color: pRgb(43, 112, 173)
        font.family: fontBold
        font.bold: true
        font.pixelSize: 18
        inputMethodHints: Qt.ImhDigitsOnly
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: "#99ccff"
        }
        text:eqText4
        visible: altitudeMode
        MouseArea {
            anchors.fill: parent
            onPressed: {
                f4.forceActiveFocus()
                keyboardYype = 0
            }
        }
    }
    TextField{
        id:f5
        width: /*mode === 1 ? 75:*/98
        height: altitudeMode ? 28 :30
        anchors.horizontalCenter: f4.horizontalCenter
        anchors.top: f4.bottom
        anchors.topMargin: 10
        anchors.right:  f4.right
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter
        color: pRgb(43, 112, 173)
        font.family: fontBold
        font.bold: true
        font.pixelSize: 18
        inputMethodHints: Qt.ImhDigitsOnly
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: "#99ccff"
        }
        text:eqText5
        visible: altitudeMode
        MouseArea {
            anchors.fill: parent
            onPressed: {
                f5.forceActiveFocus()
                keyboardYype = 0
            }
        }
    }
}
