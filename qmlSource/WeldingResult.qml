import QtQuick 2.0
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
                        textMargin = 17
                        imgWidHei = 20
                        powerY = 46
                        imgY = 48
                    }
                    else{
                        imgcenterY = 6
                        imgcenterX = 17
                        imgtopMargin = 17
                        textMargin = 30
                        imgWidHei = 31
                        powerY = 72
                        imgY = 68
                    }
                }
                else if(index === 1){
                    altitudeMode = altitudeModel2
                    if(altitudeModel2){
                        imgcenterY = 4
                        imgcenterX = 10
                        imgtopMargin = 14
                        textMargin = 17
                        imgWidHei = 20
                        powerY = 46
                        imgY = 48
                    }
                    else{
                        imgcenterY = 6
                        imgcenterX = 17
                        imgtopMargin = 17
                        textMargin = 30
                        imgWidHei = 31
                        powerY = 72
                        imgY = 68
                    }
                }
                else if(index === 2){
                    altitudeMode = altitudeModel3
                    if(altitudeModel3){
                        imgcenterY = 4
                        imgcenterX = 10
                        imgtopMargin = 14
                        textMargin = 17
                        imgWidHei = 20
                        powerY = 46
                        imgY = 48
                    }
                    else{
                        imgcenterY = 6
                        imgcenterX = 17
                        imgtopMargin = 17
                        textMargin = 30
                        imgWidHei = 31
                        powerY = 72
                        imgY = 68
                    }
                }
                else if(index === 3){
                    altitudeMode = altitudeModel4
                    if(altitudeModel4){
                        imgcenterY = 4
                        imgcenterX = 10
                        imgtopMargin = 14
                        textMargin = 17
                        imgWidHei = 20
                        powerY = 46
                        imgY = 48
                    }
                    else{
                        imgcenterY = 6
                        imgcenterX = 17
                        imgtopMargin = 17
                        textMargin = 30
                        imgWidHei = 31
                        powerY = 72
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
                        textMargin = 17
                        imgWidHei = 24
                        powerY = 59
                        imgY = 59
                    }
                    else{
                        imgcenterY = 6
                        imgcenterX = 17
                        imgtopMargin = 17
                        textMargin = 30
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
                        textMargin = 17
                        imgWidHei = 24
                        powerY = 59
                        imgY = 59
                    }
                    else{
                        imgcenterY = 6
                        imgcenterX = 17
                        imgtopMargin = 17
                        textMargin = 30
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
                        textMargin = 17
                        imgWidHei = 24
                        powerY = 59
                        imgY = 59
                    }
                    else{
                        imgcenterY = 6
                        imgcenterX = 17
                        imgtopMargin = 17
                        textMargin = 30
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
                        textMargin = 17
                        imgWidHei = 24
                        powerY = 59
                        imgY = 59
                    }
                    else{
                        imgcenterY = 6
                        imgcenterX = 17
                        imgtopMargin = 17
                        textMargin = 30
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
        text: qsTr("焊接结果")
        font.family: fontBold
        font.pixelSize: /*mode === 1 ? 17 :*/ 20
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
        id:t1
        x:mode == 1 ? 80 : 92
        y:powerY
        text: qsTr("功率: ") + eqText1 + "W"
        font.family: fontBold
        font.pixelSize:/*mode === 1 ? 14:*/ 16
        color: pRgb(171, 206, 213)
    }
    Text {
        id:t2
        text: qsTr("时间: ") + eqText2 + "S"
        font.family: fontBold
        font.pixelSize:/*mode === 1 ? 14: */16
        color: pRgb(171, 206, 213)
        anchors.left: t1.left
        anchors.top: t1.bottom
        anchors.topMargin: textMargin
    }
    Text {
        id:t3
        text: qsTr("能量: ") + eqText3 + "J"
        font.family: fontBold
        font.pixelSize:/*mode === 1 ? 14:*/ 16
        color: pRgb(171, 206, 213)
        anchors.left: t2.left
        anchors.top: t2.bottom
        anchors.topMargin: textMargin
    }
    Text {
        id:t4
        text: qsTr("焊前高度: ") + eqText4 + "mm"
        font.family: fontBold
        font.pixelSize: /*mode === 1 ? 14:*/16
        color: pRgb(171, 206, 213)
        anchors.left: t3.left
        anchors.top: t3.bottom
        anchors.topMargin: textMargin
        visible:altitudeMode

    }
    Text {
        id:t5
        text: qsTr("焊后高度: ") + eqText5 + "mm"
        font.family: fontBold
        font.pixelSize: /*mode === 1 ? 14:*/16
        color: pRgb(171, 206, 213)
        anchors.left: t4.left
        anchors.top: t4.bottom
        anchors.topMargin: textMargin
        visible: altitudeMode
    }
    Image {
        id: im1
        width: imgWidHei
        height: imgWidHei
        x:/*mode == 1 ? 33 :*/ 39
        y:imgY
        source: "qrc:/image/module.png"
    }
    Image {
        id: im2
        width: imgWidHei
        height: imgWidHei
        anchors.left: im1.left
        anchors.top: im1.bottom
        anchors.topMargin: equipmentCount > 1 ? 20 :imgtopMargin
        source: "qrc:/image/instantiation.png"
        Image{
            x:imgcenterX
            y:imgcenterY
            source: "qrc:/image/vector.png"
        }
    }
    Image {
        id: im3
        width: imgWidHei
        height: imgWidHei
        anchors.left: im2.left
        anchors.top: im2.bottom
        anchors.topMargin: equipmentCount > 1 ? 20 :17
        source: "qrc:/image/instantiation.png"
        Image{
            anchors.centerIn: parent
            source: "qrc:/image/J.png"
        }
    }
    Image {
        id: im4
        width: imgWidHei
        height: imgWidHei
        anchors.left: im3.left
        anchors.top: im3.bottom
        anchors.topMargin: equipmentCount > 1 ? 20 :17
        source: "qrc:/image/height.png"
        visible:altitudeMode
    }
    Image {
        id: im5
        width: imgWidHei
        height: imgWidHei
        anchors.left: im4.left
        anchors.top: im4.bottom
        anchors.topMargin: equipmentCount > 1 ? 20 :17
        source: "qrc:/image/height.png"
        visible: altitudeMode
    }
}
