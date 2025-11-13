import QtQuick 2.0
import GlobalLanguageDefine 1.0
import GlobalSystemDefine 1.0
import LanguageEnum 1.0
//焊接结果
Rectangle {
    property int energy: 0
    property int amplitude: 0
    property int weldPressure: 0
    property int triggerPressure: 0
    property int weldTime: 0
    property int peakPower: 0
    property int preheight: 0
    property int postHeight: 0
    property bool altitudeMode:false
    property int powerY: 1
    property int imgY: 1
    property int imgtopMargin: 1
    property int imgcenterX: 1
    property int imgcenterY: 1

    property int textMargin:1
    property int imgWidHei:1

    color: pRgb(43, 112, 173)
    radius: 3
    Text {
        // text: qsTr("焊接结果")
        text: GlobalLanguageDefine.strWeldingResult
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 20 : 18
        color: pRgb(153, 204, 255)
        x:17
        y:9
    }
    Rectangle{
        y:42
        height: 1
        width: 97
        color: pRgb(174, 210, 216)
    }


    Text {
        id: titleEnergy
        // text: qsTr("能量") + ": " + eqText3 + "J"
        text: GlobalLanguageDefine.strEnergy+ "(J)" + ": " + energy
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        color: pRgb(171, 206, 213)
        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.left: parent.left
        anchors.leftMargin: 40
    }
    Text {
        id: titleAmplitude
        // text: qsTr("振幅") + ": " + eqText3 + "J"
        text: GlobalLanguageDefine.strAmplitude + "(μm)" + ": " + amplitude
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        color: pRgb(171, 206, 213)
        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.left: parent.left
        anchors.leftMargin: 150
    }
    Text {
        id: titleWeldTime
        text: GlobalLanguageDefine.strTime + "(s)" + ": " + weldTime
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize:16
        color: pRgb(171, 206, 213)
        anchors.top: parent.top
        anchors.topMargin: 80
        anchors.left: parent.left
        anchors.leftMargin: 40
    }
    Text {
        id: titlePower
        text: GlobalLanguageDefine.strPower + "(W)" + ": " + peakPower
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        color: pRgb(171, 206, 213)
        anchors.top: parent.top
        anchors.topMargin: 80
        anchors.left: parent.left
        anchors.leftMargin: 150
    }
    Text {
        id: titlePressure
        // text: qsTr("焊接压力") + ": " + eqText3 + "J"
        text: GlobalLanguageDefine.strWeldPressure + "(PSI)" + ": " + weldPressure
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        color: pRgb(171, 206, 213)
        anchors.top: parent.top
        anchors.topMargin: 110
        anchors.left: parent.left
        anchors.leftMargin: 40
    }
    Text {
        id: titleTP
        // text: qsTr("触发压力") + ": " + eqText3 + "J"
        text: GlobalLanguageDefine.strTriggerPressure + "(PSI)" + ": " + triggerPressure
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        color: pRgb(171, 206, 213)
        anchors.top: parent.top
        anchors.topMargin: 140
        anchors.left: parent.left
        anchors.leftMargin: 40
    }


    Text {
        id: titlePreheight
        // text: qsTr("焊前高度") + ": " + eqText4/100.0 + "mm"
        text: GlobalLanguageDefine.strPreWeldHeight + ": " + preheight + GlobalLanguageDefine.strHeightUnit
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        color: pRgb(171, 206, 213)
        anchors.top: parent.top
        anchors.topMargin: 170
        anchors.left: parent.left
        anchors.leftMargin: 40
        visible: altitudeMode
    }

    Text {
        id: titlePostHeight
        // text: qsTr("焊后高度") + ": " + eqText5/100.0 + "mm"
        text: GlobalLanguageDefine.strPostWeldHeight + ": " + postHeight + GlobalLanguageDefine.strHeightUnit
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        color: pRgb(171, 206, 213)
        anchors.top: parent.top
        anchors.topMargin: 200
        anchors.left: parent.left
        anchors.leftMargin: 40
        visible: altitudeMode
    }

    Image {
        id: imageEnergy
        width: 18
        height: 18
        anchors.top: titleEnergy.top
        anchors.topMargin: 3
        anchors.left: parent.left
        anchors.leftMargin: 10
        source: "qrc:/images/icon_energy.png"
    }

    Image {
        id: imageAmplitude
        width: 18
        height: 18
        anchors.top: titleAmplitude.top
        anchors.topMargin: 3
        anchors.left: parent.left
        anchors.leftMargin: 125
        source: "qrc:/images/icon_amplitude.png"
    }
    Image {
        id: imageWeldTime
        width: 18
        height: 18
        anchors.top: titleWeldTime.top
        anchors.topMargin: 3
        anchors.left: parent.left
        anchors.leftMargin: 10
        source: "qrc:/images/icon_weldtime.png"
        smooth: false
    }
    Image {
        id: imagePower
        width: 18
        height: 18
        anchors.top: titlePower.top
        anchors.topMargin: 3
        anchors.left: parent.left
        anchors.leftMargin: 125
        source: "qrc:/images/icon_power.png"
    }

    Image {
        id: imageWP
        width: 18
        height: 18
        anchors.top: titlePressure.top
        anchors.topMargin: 3
        anchors.left: parent.left
        anchors.leftMargin: 10
        source: "qrc:/images/icon_wp.png"
    }
    Image {
        id: imageTP
        width: 18
        height: 18
        anchors.top: titleTP.top
        anchors.topMargin: 3
        anchors.left: parent.left
        anchors.leftMargin: 10
        source: "qrc:/images/icon_tp.png"
    }
    Image {
        id: imagePreheight
        width: 17
        height: 17
        anchors.top: titlePreheight.top
        anchors.topMargin: 3
        anchors.left: parent.left
        anchors.leftMargin: 10
        source: "qrc:/images/icon_preheight.png"
        visible: altitudeMode
    }
    Image {
        id: imagePostheight
        width: 17
        height: 17
        anchors.top: titlePostHeight.top
        anchors.topMargin: 3
        anchors.left: parent.left
        anchors.leftMargin: 10
        source: "qrc:/images/icon_postheight.png"
        visible: altitudeMode
    }
}
