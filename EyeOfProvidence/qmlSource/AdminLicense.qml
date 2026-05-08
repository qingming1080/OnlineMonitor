import QtQuick              2.0
import QtQuick.Controls     2.15
import GlobalLanguageDefine 1.0
import GlobalSystemDefine   1.0
import LanguageEnum         1.0
Rectangle {
    property string eqText1: ""
    property string eqText2: ""
    property string eqText3: ""
    property string eqText4: ""
    property alias t1Edit: txtFieldSingleFactorCoeff
    color: pRgb(43, 112, 173)
    radius: 6
    Text {
        // text: qsTr("系统许可证导入")
        id: systemSettingText
        text: GlobalLanguageDefine.strSystemLicense
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

    Rectangle{
        id: systemLine
        y: 42
        height: 1
        width: 146
        color: pRgb(174, 210, 216)
    }

    Text {
        // text: qsTr("系统许可证") + ":
        id: titleSystemSN
        text: GlobalLanguageDefine.strSystemSN + ": "
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        color: "#abced5"
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.verticalCenter: txtFieldSingleFactorCoeff.verticalCenter
    }
    TextField{
        id: txtFieldSingleFactorCoeff
        width: 155
        height: 40
        anchors.left: parent.left
        anchors.leftMargin: 130
        anchors.top: systemLine.bottom
        anchors.topMargin: 10
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter
        color: pRgb(43, 112, 173)
        font.family: GlobalSystemDefine.fontBold
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
                txtFieldSingleFactorCoeff.forceActiveFocus()
                // keyboardType = 0
            }
        }
    }

}
