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
    property alias t2Edit: txtFieldGeneralFactorCoeff
    property alias t3Edit: txtFieldOtherFactorCoeff
    property alias t4Edit: txtFieldAutoLearnCountLimit
    color: pRgb(43, 112, 173)
    radius: 6
    Text {
        // text: qsTr("系统升级")
        id: systemSettingText
        text: GlobalLanguageDefine.strSystemParamConfig
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
        // text: qsTr("单因素系数") + ":
        id: titleSingleFactorCoeff
        text: GlobalLanguageDefine.strSingleFactorCoeff + ": "
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
    Text {
        // text: qsTr("通用系数") + ": "
        id: titleGeneralFactorCoeff
        text: GlobalLanguageDefine.strGeneralCoeff + ": "
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        color: "#abced5"
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.verticalCenter: txtFieldGeneralFactorCoeff.verticalCenter
    }
    TextField{
        id: txtFieldGeneralFactorCoeff
        width: 155
        height: 40
        anchors.left: parent.left
        anchors.leftMargin: 130
        anchors.top: txtFieldSingleFactorCoeff.bottom
        anchors.topMargin: 20
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
        text: eqText2
        inputMethodHints: Qt.ImhDigitsOnly
        MouseArea {
            anchors.fill: parent
            onPressed: {
                txtFieldGeneralFactorCoeff.forceActiveFocus()
                // keyboardType = 0
            }
        }
    }
    Text {
        // text: qsTr("其他系数") + ": "
        id: titleOtherFactorCoeff
        text: GlobalLanguageDefine.strOtherCoeff + ": "
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        color: "#abced5"
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.verticalCenter: txtFieldOtherFactorCoeff.verticalCenter
    }
    TextField{
        id: txtFieldOtherFactorCoeff
        width: 155
        height: 40
        anchors.left: parent.left
        anchors.leftMargin: 130
        anchors.top: txtFieldGeneralFactorCoeff.bottom
        anchors.topMargin: 20
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
        text: eqText3
        inputMethodHints: Qt.ImhDigitsOnly
        MouseArea {
            anchors.fill: parent
            onPressed: {
                txtFieldOtherFactorCoeff.forceActiveFocus()
                // keyboardType = 0
            }
        }
    }
    Text {
        // text: qsTr("自动学习上限") + ": "
        text: GlobalLanguageDefine.strAutoLearnLimit + ": "
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        color: "#abced5"
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.verticalCenter: txtFieldAutoLearnCountLimit.verticalCenter
    }
    TextField{
        id: txtFieldAutoLearnCountLimit
        width: 155
        height: 40
        anchors.left: parent.left
        anchors.leftMargin: 130
        anchors.top: txtFieldOtherFactorCoeff.bottom
        anchors.topMargin: 20
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
        text: eqText4
        inputMethodHints: Qt.ImhDigitsOnly
        MouseArea {
            anchors.fill: parent
            onPressed: {
                txtFieldAutoLearnCountLimit.forceActiveFocus()
                // keyboardType = 0
            }
        }
    }
}
