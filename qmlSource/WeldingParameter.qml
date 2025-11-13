import QtQuick 2.0
import QtQuick.Controls 2.15
import GlobalLanguageDefine 1.0
import GlobalSystemDefine 1.0
import LanguageEnum         1.0
//焊接参数

Rectangle {
    color: pRgb(43, 112, 173)
    property int presetEnergyValue: 0
    property int presetAmplitudeValue: 0
    property int presetWeldPressureValue: 0
    property int presetTriggerPressureValue: 0
    radius: 3
    Rectangle {
           width:  equipmentCount == 1 ? 117 : 129
           height: 35
           radius: 1
           anchors.left: parent.left
           anchors.top: parent.top
           color: "transparent"

           Text {
               // text: qsTr("焊接参数")
               id: weldingParameterText
               text: GlobalLanguageDefine.strWeldingParameter
               font.family: GlobalSystemDefine.fontBold
               font.bold: true
               font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 20 : 18
               color: pRgb(153, 204, 255)
               anchors.left: parent.left
               anchors.leftMargin: 17
               anchors.top: parent.top
               anchors.topMargin: 10
           }

           Rectangle{
               anchors.top: weldingParameterText.bottom
               anchors.topMargin: 5
               height: 1
               width: 97
               color: pRgb(174, 210, 216)
           }
       }

    Image {
        id: imageEnergy
        source: "qrc:/images/icon_energy.png"
        x: 17
        y: 70
        width: 25
        height: 25
    }
    Image {
        id: imageAmplitude
        source: "qrc:/images/icon_amplitude.png"
        anchors.top: imageEnergy.bottom
        anchors.left: imageEnergy.left
        anchors.topMargin: 12
        width: 25
        height: 25
    }
    Image {
        id: imageTriggerPressure
        source: "qrc:/images/icon_tp.png"
        anchors.top: imageAmplitude.bottom
        anchors.left: imageAmplitude.left
        anchors.topMargin: 12
        width: 25
        height: 25
    }
    Image {
        id: imageWeldPressure
        source: "qrc:/images/icon_wp.png"
        anchors.top: imageTriggerPressure.bottom
        anchors.left: imageTriggerPressure.left
        anchors.topMargin: 12
        width: 25
        height: 25
    }

    Text {
        id: titleEnergy
        // text: qsTr("能量")
        text: GlobalLanguageDefine.strEnergy + "(J)" + ": "
        height: 25
        width: 80
        font.family: GlobalSystemDefine.fontBold
        // font.bold: true
        font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 16 : 14
        color: pRgb(171, 206, 213)
        verticalAlignment: Text.AlignVCenter
        anchors.verticalCenter: imageEnergy.verticalCenter
        anchors.left: imageEnergy.right
        anchors.leftMargin: 10
    }
    Text {
        id: titleAmplitude
        // text: qsTr("振幅")
        text: GlobalLanguageDefine.strAmplitude + "(μm)" + ": "
        height: 25
        width: 80
        font.family: GlobalSystemDefine.fontBold
        // font.bold: true
        font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 16 : 14
        color: pRgb(171, 206, 213)
        verticalAlignment: Text.AlignVCenter
        anchors.verticalCenter: imageAmplitude.verticalCenter
        anchors.left: imageAmplitude.right
        anchors.leftMargin: 10
    }
    Text {
        id: titleTriggerPressure
        text: GlobalLanguageDefine.strTriggerPressure + "(PSI)" + ": "
        height: 25
        width: 80
        font.family: GlobalSystemDefine.fontBold
        // font.bold: true
        font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 16 : 14
        color: pRgb(171, 206, 213)
        verticalAlignment: Text.AlignVCenter
        anchors.verticalCenter: imageTriggerPressure.verticalCenter
        anchors.left: imageTriggerPressure.right
        anchors.leftMargin: 10
    }
    Text {
        id: titleWeldPressure
        // text: qsTr("压力")
        text: GlobalLanguageDefine.strWeldPressure + "(PSI)" + ": "
        height: 25
        width: 80
        font.family: GlobalSystemDefine.fontBold
        // font.bold: true
        font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 16 : 14
        color: pRgb(171, 206, 213)
        verticalAlignment: Text.AlignVCenter
        anchors.verticalCenter: imageWeldPressure.verticalCenter
        anchors.left: imageWeldPressure.right
        anchors.leftMargin: 10
    }
    TextField{
        id: fieldEnergy
        width: 80
        height: 28
        anchors.left: titleEnergy.right
        anchors.leftMargin:  38
        anchors.verticalCenter: titleEnergy.verticalCenter
        horizontalAlignment: TextInput.AlignHCenter
        color: pRgb(43, 112, 173)
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        inputMethodHints: Qt.ImhDigitsOnly
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: "#99ccff"
        }
        text: presetEnergyValue/* + GlobalLanguageDefine.strEnergyUnit*/
        MouseArea {
            anchors.fill: parent
            onPressed: {
                fieldEnergy.forceActiveFocus()
                keyboardType = 0
            }
        }
        onEditingFinished: {
             var intRegex = /^[0-9]+$/
             if (!intRegex.test(fieldEnergy.text))
                 footer.showError(titleEnergy.text + GlobalLanguageDefine.strInputInterger)
             else
                 footer.hideError()
         }
    }
    TextField{
        id: fieldAmplitude
        width: 80
        height: 28
        anchors.left: titleAmplitude.right
        anchors.leftMargin:  38
        anchors.verticalCenter: titleAmplitude.verticalCenter
        horizontalAlignment: TextInput.AlignHCenter
        color: pRgb(43, 112, 173)
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        inputMethodHints: Qt.ImhDigitsOnly
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: "#99ccff"
        }
        text: presetAmplitudeValue/* + GlobalLanguageDefine.strAmplitudeUnit*/
        MouseArea {
            anchors.fill: parent
            onPressed: {
                fieldAmplitude.forceActiveFocus()
                keyboardType = 0
            }
        }
        onEditingFinished: {
             var wpRegex = /^[0-9]+$/
             if (!wpRegex.test(fieldAmplitude.text))
                 footer.showError(titleAmplitude.text + GlobalLanguageDefine.strInputInterger)
             else
                 footer.hideError()
         }
    }
    TextField{
        id: fieldTriggerPressure
        width: 80
        height: 28
        anchors.left: titleTriggerPressure.right
        anchors.leftMargin: 38
        anchors.verticalCenter: titleTriggerPressure.verticalCenter
        horizontalAlignment: TextInput.AlignHCenter
        color: pRgb(43, 112, 173)
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        inputMethodHints: Qt.ImhDigitsOnly
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: "#99ccff"
        }
        text: presetTriggerPressureValue
        MouseArea {
            anchors.fill: parent
            onPressed: {
                fieldTP.forceActiveFocus()
                keyboardType = 0
            }
        }
        onEditingFinished: {
             var tpRegex = /^[0-9]+$/
             if (!tpRegex.test(fieldTP.text))
                 footer.showError(titleTriggerPressure.text + GlobalLanguageDefine.strInputInterger)
             else
                 footer.hideError()
         }
    }
    TextField{
        id: fieldWeldPressure
        width: 80
        height:  28
        anchors.left: titleWeldPressure.right
        anchors.leftMargin: 38
        anchors.verticalCenter: titleWeldPressure.verticalCenter
        horizontalAlignment: TextInput.AlignHCenter
        color: pRgb(43, 112, 173)
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        inputMethodHints: Qt.ImhDigitsOnly
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: "#99ccff"
        }
        text: presetWeldPressureValue/* + GlobalLanguageDefine.strPressureUnit*/
        MouseArea {
            anchors.fill: parent
            onPressed: {
                fieldWeldPressure.forceActiveFocus()
                keyboardType = 0
            }
        }
        onEditingFinished: {
             var wpRegex = /^[0-9]+$/
             if (!wpRegex.test(fieldWeldPressure.text))
                 footer.showError(titleWeldPressure.text + GlobalLanguageDefine.strInputInterger)
             else
                 footer.hideError()
         }
    }

}
