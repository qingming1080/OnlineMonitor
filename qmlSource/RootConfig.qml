import QtQuick 2.0
import QtQuick.Controls 2.15
Rectangle {
    property string name: ""
    property string model: ""
    property string eqText1: ""
    property string eqText2: ""
    property string eqText3: ""
    property string eqText4: ""
    property alias t1Edit: t1
    property alias t2Edit: t2
    property alias t3Edit: t3
    property alias t4Edit: t4
    color: pRgb(43, 112, 173)
    radius: 6
    Text {
        text: qsTr("系统参数配置")
        font.family: fontBold
        font.bold: true
        font.pixelSize: 20
        color: pRgb(153, 204, 255)
        x:17
        y:9
    }
    Rectangle{
        y:42
        height: 1
        width: 146
        color: pRgb(174, 210, 216)
    }
    Text {
        text: qsTr("设备名称:") + name
        font.family: fontBold
        font.bold: true
        font.pixelSize: 16
        color: "#abced5"
        x:15
        y:69
    }
    Text {
        text: qsTr("设备型号:") + model
        font.family: fontBold
        font.bold: true
        font.pixelSize: 16
        color: "#abced5"
        x:15
        y:121
    }
    Text {
        text: qsTr("单因素系数:")
        font.family: fontBold
        font.bold: true
        font.pixelSize: 16
        color: "#abced5"
        x:15
        y:189
    }
    TextField{
        id:t1
        width: 155
        height: 40
        x:130
        y:187
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter
        color: pRgb(43, 112, 173)
        font.family: fontBold
        font.bold: true
        font.pixelSize: 16
        background: Rectangle{
            radius: 6
            border.width: 3
            border.color: "#99ccff"
        }
        text: eqText1
        inputMethodHints: Qt.ImhDigitsOnly
        MouseArea {
            anchors.fill: parent
            onPressed: {
                t1.forceActiveFocus()
                keyboardYype = 0
            }
        }
    }
    Text {
        text: qsTr("通用系数:")
        font.family: fontBold
        font.bold: true
        font.pixelSize: 16
        color: "#abced5"
        x:15
        y:253
    }
    TextField{
        id:t2
        width: 155
        height: 40
        x:130
        y:247
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter
        color: pRgb(43, 112, 173)
        font.family: fontBold
        font.bold: true
        font.pixelSize: 16
        background: Rectangle{
            radius: 6
            border.width: 3
            border.color: "#99ccff"
        }
        text: eqText2
        inputMethodHints: Qt.ImhDigitsOnly
        MouseArea {
            anchors.fill: parent
            onPressed: {
                t2.forceActiveFocus()
                keyboardYype = 0
            }
        }
    }
    Text {
        text: qsTr("其他系数:")
        font.family: fontBold
        font.bold: true
        font.pixelSize: 16
        color: "#abced5"
        x:15
        y:325
    }
    TextField{
        id:t3
        width: 155
        height: 40
        x:130
        y:317
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter
        color: pRgb(43, 112, 173)
        font.family: fontBold
        font.bold: true
        font.pixelSize: 16
        background: Rectangle{
            radius: 6
            border.width: 3
            border.color: "#99ccff"
        }
        text: eqText3
        inputMethodHints: Qt.ImhDigitsOnly
        MouseArea {
            anchors.fill: parent
            onPressed: {
                t3.forceActiveFocus()
                keyboardYype = 0
            }
        }
    }
    Text {
        text: qsTr("自动学习上限:")
        font.family: fontBold
        font.bold: true
        font.pixelSize: 16
        color: "#abced5"
        x:15
        y:394
    }
    TextField{
        id:t4
        width: 155
        height: 40
        x:130
        y:382
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter
        color: pRgb(43, 112, 173)
        font.family: fontBold
        font.bold: true
        font.pixelSize: 16
        background: Rectangle{
            radius: 6
            border.width: 3
            border.color: "#99ccff"
        }
        text: eqText4
        inputMethodHints: Qt.ImhDigitsOnly
        MouseArea {
            anchors.fill: parent
            onPressed: {
                t4.forceActiveFocus()
                keyboardYype = 0
            }
        }
    }
}
