import QtQuick 2.0
import GlobalLanguageDefine 1.0
import GlobalSystemDefine 1.0
import LanguageEnum 1.0
//焊接结果
Rectangle {
    property string energy: ""
    property string amplitude: ""
    property string weldPressure: ""
    property string triggerPressure: ""
    property string weldTime: ""
    property string peakPower: ""
    property string preheight: ""
    property string postHeight: ""
    property bool heightOption:false
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

    Image {
        id: imageEnergy
        width: 18
        height: 18
        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.left: parent.left
        anchors.leftMargin: 10
        source: "qrc:/images/icon_energy.png"
    }
    Text {
        id: titleEnergy
        // text: qsTr("能量") + ": " + eqText3 + "J"
        text: GlobalLanguageDefine.strEnergy+ "(J)" + ": " + energy
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        color: pRgb(171, 206, 213)
        width: 100
        anchors.verticalCenter: imageEnergy.verticalCenter
        anchors.left: imageEnergy.right
        anchors.leftMargin: 3
    }

    Image {
        id: imagePower
        width: 18
        height: 18
        anchors.top: imageEnergy.bottom
        anchors.topMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 10
        source: "qrc:/images/icon_power.png"
    }

    Text {
        id: titlePower
        text: GlobalLanguageDefine.strPower + "(W)" + ": " + peakPower
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        color: pRgb(171, 206, 213)
        width: 100
        anchors.verticalCenter: imagePower.verticalCenter
        anchors.left: imagePower.right
        anchors.leftMargin: 3
    }

    Image {
        id: imageAmplitude
        width: 18
        height: 18
        anchors.top: imagePower.bottom
        anchors.topMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 10
        source: "qrc:/images/icon_amplitude.png"
    }

    Text {
        id: titleAmplitude
        // text: qsTr("振幅") + ": " + eqText3 + "J"
        text: GlobalLanguageDefine.strAmplitude + "(μm)" + ": " + amplitude
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        color: pRgb(171, 206, 213)
        width: 90
        anchors.verticalCenter: imageAmplitude.verticalCenter
        anchors.left: imageAmplitude.right
        anchors.leftMargin: 3
    }

    Image {
        id: imageWeldTime
        width: 18
        height: 18
        anchors.top: imageAmplitude.top
        anchors.left: titleAmplitude.right
        anchors.leftMargin: 10
        source: "qrc:/images/icon_weldtime.png"
        smooth: false
    }

    Text {
        id: titleWeldTime
        text: GlobalLanguageDefine.strTime + "(s)" + ": " + weldTime
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize:16
        color: pRgb(171, 206, 213)
        anchors.verticalCenter: imageWeldTime.verticalCenter
        anchors.left: imageWeldTime.right
        anchors.leftMargin: 3
    }

    Image {
        id: imageTP
        width: 18
        height: 18
        anchors.top: imageAmplitude.bottom
        anchors.topMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 10
        source: "qrc:/images/icon_tp.png"
    }

    Text {
        id: titleTP
        // text: qsTr("触发压力") + ": " + eqText3 + "J"
        text: GlobalLanguageDefine.strTriggerPressure + "(PSI)" + ": " + triggerPressure
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        color: pRgb(171, 206, 213)
        anchors.verticalCenter: imageTP.verticalCenter
        anchors.left: imageTP.right
        anchors.leftMargin: 3
    }

    Image {
        id: imageWP
        width: 18
        height: 18
        anchors.top: imageTP.bottom
        anchors.topMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 10
        source: "qrc:/images/icon_wp.png"
    }

    Text {
        id: titlePressure
        // text: qsTr("焊接压力") + ": " + eqText3 + "J"
        text: GlobalLanguageDefine.strWeldPressure + "(PSI)" + ": " + weldPressure
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        color: pRgb(171, 206, 213)
        anchors.verticalCenter: imageWP.verticalCenter
        anchors.left: imageWP.right
        anchors.leftMargin: 3
    }

    // Image {
    //     id: imagePreheight
    //     width: 17
    //     height: 17
    //     anchors.top: imageWP.bottom
    //     anchors.topMargin: 15
    //     anchors.left: parent.left
    //     anchors.leftMargin: 10
    //     source: "qrc:/images/icon_preheight.png"
    //     visible: heightOption
    // }

    // Text {
    //     id: titlePreheight
    //     // text: qsTr("焊前高度") + ": " + eqText4/100.0 + "mm"
    //     text: GlobalLanguageDefine.strShortPreheight + "(mm)" + ": " + preheight
    //     font.family: GlobalSystemDefine.fontBold
    //     font.bold: true
    //     font.pixelSize: 16
    //     color: pRgb(171, 206, 213)
    //     width: 90
    //     anchors.verticalCenter: imagePreheight.verticalCenter
    //     anchors.left: imagePreheight.right
    //     anchors.leftMargin: 3
    //     // visible: heightOption
    // }

    Image {
        id: imagePostheight
        width: 17
        height: 17
        anchors.top: imageWP.bottom
        anchors.topMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 10
        source: "qrc:/images/icon_postheight.png"
        visible: heightOption
    }

    Text {
        id: titlePostHeight
        // text: qsTr("焊后高度") + ": " + eqText5/100.0 + "mm"
        text: GlobalLanguageDefine.strPostWeldHeight + "(mm)" + ": " + postHeight
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        color: pRgb(171, 206, 213)
        anchors.verticalCenter: imagePostheight.verticalCenter
        anchors.left: imagePostheight.right
        anchors.leftMargin: 3
        visible: heightOption
    }











}
