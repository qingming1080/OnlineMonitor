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
    color: pRgb(43, 112, 173)
    radius: 6
    Text {
        // text: qsTr("系统软件升级")
        id: systemSettingText
        text: GlobalLanguageDefine.strSystemSWUpgrade
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
        // text: qsTr("软件版本") + ":
        id: titleSoftwareVersion
        text: GlobalLanguageDefine.strAvailableVersions + ": "
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        color: "#abced5"
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.verticalCenter: listSoftwareVersions.verticalCenter
    }
    CustomComboBox{
        id: listSoftwareVersions
        width: 155
        height: 40
        anchors.left: parent.left
        anchors.leftMargin: 130
        anchors.top: systemLine.bottom
        anchors.topMargin: 10
        displayText: "NONE"

        // model: WelderTypeModel
        // property int tmpIndex: DeviceManager.SelectedDeviceIndex
        // currentIndex: DeviceManager.DeviceList[tmpIndex].DeviceObj.WelderType
        // onCurrentIndexChanged:
        // {
        //     DeviceManager.DeviceList[tmpIndex].DeviceObj.WelderType = currentIndex
        // }
    }

    Row {
        width: parent.width - 10
        height: 40
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        spacing: 20
        HBPrimaryButton {
            id: btnReadUSB
            width: (parent.width - 20) / 2
            text: GlobalLanguageDefine.strReadUSB
            onPressed: {
            }
        }

        HBPrimaryButton {
            id: btnUpgrade
            width: (parent.width - 20) / 2
            text: GlobalLanguageDefine.strSoftwareUpgrade
            onPressed: {
            }
        }
    }
}
