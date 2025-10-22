import QtQuick 2.0
import QtQuick.Controls 2.15
import GlobalLanguageDefine 1.0
import GlobalSystemDefine 1.0
import LanguageEnum         1.0
//焊接参数

Rectangle {
    color: pRgb(43, 112, 173)
    property string eqText1: ""
    property string eqText2: ""
    property string eqText3: ""
    property string eqText4: ""
    property string eqText5: ""
    property bool altitudeMode:DeviceManager.deviceList[swipeCurrIndex].DevInfoObject.heightOption === 1 ? true:false

    property int deviceID: DeviceManager.deviceList[swipeCurrIndex].DevInfoObject.id

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
        id: imageWeldPressure
        source: "qrc:/images/icon_wp.png"
        anchors.top: imageAmplitude.bottom
        anchors.left: imageAmplitude.left
        anchors.topMargin: 12
        width: 25
        height: 25
    }
    Image {
        id: imageTP
        source: "qrc:/images/icon_tp.png"
        anchors.top: imageWeldPressure.bottom
        anchors.left: imageWeldPressure.left
        anchors.topMargin: 12
        width: 25
        height: 25
    }

    Text {
        id: titleEnergy
        // text: qsTr("能量")
        text: GlobalLanguageDefine.strEnergy + ": "
        height: 25
        width: 50
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
        text: GlobalLanguageDefine.strAmplitude + ": "
        height: 25
        width: 50
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
        id: titleWeldPressure
        // text: qsTr("压力")
        text: GlobalLanguageDefine.strWeldPressure + ": "
        height: 25
        width: 50
        font.family: GlobalSystemDefine.fontBold
        // font.bold: true
        font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 16 : 14
        color: pRgb(171, 206, 213)
        verticalAlignment: Text.AlignVCenter
        anchors.verticalCenter: imageWeldPressure.verticalCenter
        anchors.left: imageWeldPressure.right
        anchors.leftMargin: 10
    }
    Text {
        id: titleTP
        text: GlobalLanguageDefine.strTP + ": "
        height: 25
        width: 50
        font.family: GlobalSystemDefine.fontBold
        // font.bold: true
        font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 16 : 14
        color: pRgb(171, 206, 213)
        verticalAlignment: Text.AlignVCenter
        anchors.verticalCenter: imageTP.verticalCenter
        anchors.left: imageTP.right
        anchors.leftMargin: 10
    }
    TextField{
        id: fieldEnergy
        width: 98
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
        validator: RegExpValidator { regExp: /^[0-9]+$/}
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: "#99ccff"
        }
        text: UtilityFunction.displayValue(eqText1) + GlobalLanguageDefine.strEnergyUnit
        MouseArea {
            anchors.fill: parent
            onPressed: {
                fieldEnergy.forceActiveFocus()
                keyboardType = 0
            }
        }
    }
    TextField{
        id: fieldAmplitude
        width: 98
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
        validator: RegExpValidator { regExp: /^[0-9]+$/}
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: "#99ccff"
        }
        text:UtilityFunction.displayValue(eqText2) + GlobalLanguageDefine.strAmplitudeUnit
        MouseArea {
            anchors.fill: parent
            onPressed: {
                fieldAmplitude.forceActiveFocus()
                keyboardType = 0
            }
        }
    }
    TextField{
        id: fieldWeldPressure
        width: 98
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
        validator: RegExpValidator { regExp: /^[0-9]+$/}
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: "#99ccff"
        }
        text: UtilityFunction.displayValue(eqText3,10,1) + GlobalLanguageDefine.strPressureUnit
        MouseArea {
            anchors.fill: parent
            onPressed: {
                fieldWeldPressure.forceActiveFocus()
                keyboardType = 0
            }
        }
    }
    TextField{
        id: fieldTP
        width: /*mode === 1 ? 75:*/98
        height: 28
        anchors.left: titleTP.right
        anchors.leftMargin: 38
        anchors.verticalCenter: titleTP.verticalCenter
        horizontalAlignment: TextInput.AlignHCenter
        color: pRgb(43, 112, 173)
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        inputMethodHints: Qt.ImhDigitsOnly
        validator: RegExpValidator { regExp: /^[0-9]+$/}
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: "#99ccff"
        }
        text: UtilityFunction.displayValue(eqText4,10,1) + GlobalLanguageDefine.strPressureUnit
        MouseArea {
            anchors.fill: parent
            onPressed: {
                fieldTP.forceActiveFocus()
                keyboardType = 0
            }
        }
    }

    ParameterSettingDialog {
        id: parameterSetting
        // onTimeSelected: {
        //     // 接收 timeDialog 中发出的 timeSelected 信号，并更新 timeText 显示的时间
        //     let date = new Date(year, month - 1, day, hour, minute, second);  // JavaScript 中月份是从 0 开始的
        //     timeText.text = date.toLocaleString();  // 将选中的时间转为本地时间字符串
        // }
    }

}
