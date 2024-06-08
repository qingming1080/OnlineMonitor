import QtQuick 2.0
//焊接结果
Rectangle {
    property string eqText1: ""
    property string eqText2: ""
    property string eqText3: ""
    property string eqText4: ""
    property string eqText5: ""
    property var textMargin:{
        if(altitudeModel){
            return 17
        }
        else{
            return 30
        }
    }
    property var imgWidHei:{
        if(mode == 1){
            if(altitudeModel){
                return 20
            }
            else{
                return 31
            }
        }
        else{
            if(altitudeModel){
                return 24
            }
            else{
                return 36
            }
        }
    }
    color: pRgb(43, 112, 173)
    radius: 3
    Text {
        text: qsTr("焊接结果")
        font.family: fontBold
        font.pixelSize: mode === 1 ? 17 : 20
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
        y:{
            if(mode == 1){
                if(altitudeModel){
                    return 46
                }
                else{
                    return 72
                }
            }
            else{
                if(altitudeModel){
                    return 59
                }
                else{
                    return 85
                }
            }
        }
        text: qsTr("功率: ") + eqText1 + "W"
        font.family: fontBold
        font.pixelSize:mode === 1 ? 14: 16
        color: pRgb(171, 206, 213)
    }
    Text {
        id:t2
        text: qsTr("时间: ") + eqText2 + "S"
        font.family: fontBold
        font.pixelSize:mode === 1 ? 14: 16
        color: pRgb(171, 206, 213)
        anchors.left: t1.left
        anchors.top: t1.bottom
        anchors.topMargin: textMargin
    }
    Text {
        id:t3
        text: qsTr("能量: ") + eqText3 + "J"
        font.family: fontBold
        font.pixelSize:mode === 1 ? 14: 16
        color: pRgb(171, 206, 213)
        anchors.left: t2.left
        anchors.top: t2.bottom
        anchors.topMargin: textMargin
    }
    Text {
        id:t4
        text: qsTr("焊前高度: ") + eqText4 + "mm"
        font.family: fontBold
        font.pixelSize: mode === 1 ? 14:16
        color: pRgb(171, 206, 213)
        anchors.left: t3.left
        anchors.top: t3.bottom
        anchors.topMargin: textMargin
        visible: altitudeModel
    }
    Text {
        id:t5
        text: qsTr("焊后高度: ") + eqText5 + "mm"
        font.family: fontBold
        font.pixelSize: mode === 1 ? 14:16
        color: pRgb(171, 206, 213)
        anchors.left: t4.left
        anchors.top: t4.bottom
        anchors.topMargin: textMargin
        visible: altitudeModel
    }
    Image {
        id: im1
        width: imgWidHei
        height: imgWidHei
        x:mode == 1 ? 33 : 39
        y:{
            if(mode == 1){
                if(altitudeModel){
                    return 48
                }
                else{
                    return 68
                }
            }
            else{
                if(altitudeModel){
                    return 59
                }
                else{
                    return 79
                }
            }
        }
        source: "qrc:/image/组件.png"
    }
    Image {
        id: im2
        width: imgWidHei
        height: imgWidHei
        anchors.left: im1.left
        anchors.top: im1.bottom
        anchors.topMargin: {
            if(altitudeModel){
                return 14
            }
            else{
                return 17
            }
        }
        source: "qrc:/image/实例.png"
        Image{
            x:{
                if(altitudeModel){
                    return 12
                }
                else{
                    return 17
                }
            }
            y:6
            source: "qrc:/image/矢量 3.png"
        }
    }
    Image {
        id: im3
        width: imgWidHei
        height: imgWidHei
        anchors.left: im2.left
        anchors.top: im2.bottom
        anchors.topMargin: 17
        source: "qrc:/image/实例.png"
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
        anchors.topMargin: 17
        source: "qrc:/image/高度.png"
        visible: altitudeModel
    }
    Image {
        id: im5
        width: imgWidHei
        height: imgWidHei
        anchors.left: im4.left
        anchors.top: im4.bottom
        anchors.topMargin: 17
        source: "qrc:/image/高度.png"
        visible: altitudeModel
    }
}
