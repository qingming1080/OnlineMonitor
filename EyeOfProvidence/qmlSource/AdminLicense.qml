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
    property alias t1Edit: txtSystemSN
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
        anchors.verticalCenter: txtSystemSN.verticalCenter
    }

    Text {
        id: txtSystemSN
        text: "N/A"
        font.family: GlobalSystemDefine.fontBold
        font.bold: false
        font.pixelSize: 16
        color: "#abced5"
        width: 155
        height: 40
        anchors.left: parent.left
        anchors.leftMargin: 130
        anchors.top: systemLine.bottom
        anchors.topMargin: 10
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        // text: qsTr("剩余天数") + ":
        id: titleExpiredDays
        text: GlobalLanguageDefine.strExpiredDays + ": "
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        color: "#abced5"
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.verticalCenter: txtExpiredDays.verticalCenter
    }

    Text {
        id : txtExpiredDays
        text: "N/A"
        font.family: GlobalSystemDefine.fontBold
        font.bold: false
        font.pixelSize: 16
        color: "#abced5"
        width: 155
        height: 40
        anchors.left: parent.left
        anchors.leftMargin: 130
        anchors.top: txtSystemSN.bottom
        anchors.topMargin: 10
        verticalAlignment: Text.AlignVCenter
    }

    HBPrimaryButton {
        id: btnLoadLicense
        height: 40
        width: (parent.width - 20) / 2
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        text: GlobalLanguageDefine.strLoadLicense
        onPressed: {
        }
    }


}
