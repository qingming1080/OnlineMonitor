import QtQuick 2.0
import GlobalLanguageDefine 1.0
import GlobalSystemDefine 1.0
import LanguageEnum 1.0
//焊接结果
Rectangle {
    property string eqText1: ""
    property string eqText2: ""
    property string eqText3: ""
    property string eqText4: ""
    property string eqText5: ""
    property bool altitudeMode:false
    property int powerY: 1
    property int imgY: 1
    property int imgtopMargin: 1
    property int imgcenterX: 1
    property int imgcenterY: 1
    Component.onCompleted: {
        sigUpdateUI(swipeCurrIndex)
    }

    Connections{
        target: window
        function onSigUpdateUI(index){
            if(mode == 1){
                if(index === 0){
                    altitudeMode = altitudeModel1
                    if(altitudeModel1){
                        imgcenterY = 4
                        imgcenterX = 10
                        imgtopMargin = 14
                        textMargin = 23
                        imgWidHei = 20
                        powerY = 50
                        imgY = 48
                    }
                    else{
                        imgcenterY = 6
                        imgcenterX = 17
                        imgtopMargin = 17
                        textMargin = 35
                        imgWidHei = 31
                        powerY = 75
                        imgY = 68
                    }
                }
                else if(index === 1){
                    altitudeMode = altitudeModel2
                    if(altitudeModel2){
                        imgcenterY = 4
                        imgcenterX = 10
                        imgtopMargin = 14
                        textMargin = 23
                        imgWidHei = 20
                        powerY = 50
                        imgY = 48
                    }
                    else{
                        imgcenterY = 6
                        imgcenterX = 17
                        imgtopMargin = 17
                        textMargin = 35
                        imgWidHei = 31
                        powerY = 75
                        imgY = 68
                    }
                }
                else if(index === 2){
                    altitudeMode = altitudeModel3
                    if(altitudeModel3){
                        imgcenterY = 4
                        imgcenterX = 10
                        imgtopMargin = 14
                        textMargin = 23
                        imgWidHei = 20
                        powerY = 50
                        imgY = 48
                    }
                    else{
                        imgcenterY = 6
                        imgcenterX = 17
                        imgtopMargin = 17
                        textMargin = 35
                        imgWidHei = 31
                        powerY = 75
                        imgY = 68
                    }
                }
                else if(index === 3){
                    altitudeMode = altitudeModel4
                    if(altitudeModel4){
                        imgcenterY = 4
                        imgcenterX = 10
                        imgtopMargin = 14
                        textMargin = 23
                        imgWidHei = 20
                        powerY = 50
                        imgY = 48
                    }
                    else{
                        imgcenterY = 6
                        imgcenterX = 17
                        imgtopMargin = 17
                        textMargin = 35
                        imgWidHei = 31
                        powerY = 75
                        imgY = 68
                    }
                }
            }
            else{
                if(index === 0){
                    altitudeMode = altitudeModel1
                    if(altitudeModel1){
                        imgcenterY = 4
                        imgcenterX = 10
                        imgtopMargin = 14
                        textMargin = 23
                        imgWidHei = 24
                        powerY = 65
                        imgY = 59
                    }
                    else{
                        imgcenterY = 6
                        imgcenterX = 17
                        imgtopMargin = 17
                        textMargin = 35
                        imgWidHei = 36
                        powerY = 85
                        imgY = 79
                    }
                }
                else if(index === 1){
                    altitudeMode = altitudeModel2
                    if(altitudeModel2){
                        imgcenterY = 4
                        imgcenterX = 10
                        imgtopMargin = 14
                        textMargin = 23
                        imgWidHei = 24
                        powerY = 59
                        imgY = 59
                    }
                    else{
                        imgcenterY = 6
                        imgcenterX = 17
                        imgtopMargin = 17
                        textMargin = 35
                        imgWidHei = 36
                        powerY = 85
                        imgY = 79
                    }
                }
                else if(index === 2){
                    altitudeMode = altitudeModel3
                    if(altitudeModel3){
                        imgcenterY = 4
                        imgcenterX = 10
                        imgtopMargin = 14
                        textMargin = 23
                        imgWidHei = 24
                        powerY = 59
                        imgY = 59
                    }
                    else{
                        imgcenterY = 6
                        imgcenterX = 17
                        imgtopMargin = 17
                        textMargin = 35
                        imgWidHei = 36
                        powerY = 85
                        imgY = 79
                    }
                }
                else if(index === 3){
                    altitudeMode = altitudeModel4
                    if(altitudeModel4){
                        imgcenterY = 4
                        imgcenterX = 10
                        imgtopMargin = 14
                        textMargin = 23
                        imgWidHei = 24
                        powerY = 59
                        imgY = 59
                    }
                    else{
                        imgcenterY = 6
                        imgcenterX = 17
                        imgtopMargin = 17
                        textMargin = 35
                        imgWidHei = 36
                        powerY = 85
                        imgY = 79
                    }
                }
            }
        }
    }

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
        id: titlePower
        anchors.left: imagePower.left
        anchors.leftMargin: mode == 1 ? 80 : 92
        // y: powerY
        anchors.verticalCenter: imagePower.verticalCenter
        // text: qsTr("功率") + ": " + eqText1 + "W"
        text: GlobalLanguageDefine.strPower + ": " + eqText1 + GlobalLanguageDefine.strPowerUnit
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize:/*mode === 1 ? 14:*/ 16
        color: pRgb(171, 206, 213)
    }
    Text {
        id: titleWeldTime
        // text: qsTr("时间") + ": " + eqText2/100.0 + "S"
        text: GlobalLanguageDefine.strTime + ": " + eqText2 + GlobalLanguageDefine.strWeldTimeUnit
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize:/*mode === 1 ? 14: */16
        color: pRgb(171, 206, 213)
        anchors.left: titlePower.left
        anchors.verticalCenter: imageWeldTime.verticalCenter
    }
    Text {
        id: titleEnergy
        // text: qsTr("能量") + ": " + eqText3 + "J"
        text: GlobalLanguageDefine.strEnergy + ": " + eqText3 + GlobalLanguageDefine.strEnergyUnit
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize:/*mode === 1 ? 14:*/ 16
        color: pRgb(171, 206, 213)
        anchors.left: titleWeldTime.left
        anchors.verticalCenter: imageEnergy.verticalCenter
    }

    Text {
        id: titlePreheight
        // text: qsTr("焊前高度") + ": " + eqText4/100.0 + "mm"
        text: GlobalLanguageDefine.strPreWeldHeight + ": " + eqText4 + GlobalLanguageDefine.strHeightUnit
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: /*mode === 1 ? 14:*/16
        color: pRgb(171, 206, 213)
        anchors.left: titleEnergy.left
        anchors.verticalCenter: imagePreheight.verticalCenter
        visible: altitudeMode
    }

    Text {
        id: titlePostHeight
        // text: qsTr("焊后高度") + ": " + eqText5/100.0 + "mm"
        text: GlobalLanguageDefine.strPostWeldHeight + ": " + eqText5 + GlobalLanguageDefine.strHeightUnit
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: /*mode === 1 ? 14:*/16
        color: pRgb(171, 206, 213)
        anchors.left: titlePreheight.left
        anchors.verticalCenter: imagePostHeight.verticalCenter
        visible: altitudeMode
    }

    Image {
        id: imagePower
        width: imgWidHei
        height: imgWidHei
        x:/*mode == 1 ? 33 :*/ 39
        y:imgY
        source: "qrc:/images/icon_power.png"
    }

    Image {
        id: imageWeldTime
        width: imgWidHei
        height: imgWidHei
        anchors.left: imagePower.left
        anchors.top: imagePower.bottom
        anchors.topMargin: equipmentCount > 1 ? 20 :imgtopMargin
        source: "qrc:/images/instantiation.png"
        Image{
            width: parent.width/2 - 5
            height: parent.height/2 - 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Math.round(parent.height / 2 - 2)
            anchors.left: parent.left
            anchors.leftMargin: Math.round(parent.width / 2 - 2)
            source: "qrc:/images/vector.png"
        }
    }

    Image {
        id: imageEnergy
        width: imgWidHei
        height: imgWidHei
        anchors.left: imageWeldTime.left
        anchors.top: imageWeldTime.bottom
        anchors.topMargin: equipmentCount > 1 ? 20 :17
        source: "qrc:/images/instantiation.png"
        Image{
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: Math.round(parent.width / 2 - 5)
            source: "qrc:/images/icon_energy_unit.png"
        }
    }

    Image {
        id: imagePreheight
        width: imgWidHei
        height: imgWidHei
        anchors.left: imageEnergy.left
        anchors.top: imageEnergy.bottom
        anchors.topMargin: equipmentCount > 1 ? 20 :17
        source: "qrc:/images/icon_preheight.png"
        visible:altitudeMode
    }
    Image {
        id: imagePostHeight
        width: imgWidHei
        height: imgWidHei
        anchors.left: imagePreheight.left
        anchors.top: imagePreheight.bottom
        anchors.topMargin: equipmentCount > 1 ? 20 :17
        source: "qrc:/images/icon_preheight.png"
        visible: altitudeMode
    }
}
