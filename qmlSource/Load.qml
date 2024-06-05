import QtQuick 2.0

Rectangle {
    color: pRgb(153, 204, 255)
    width: 1280
    height: 60
    property string loading: ""
    Image {
        id: imgname
        width: 229
        height: 127.5
        x:235
        y:205
        source: "qrc:/image/title.png"
    }
    Text {
        text: qsTr("在线监测系统")
        x:483
        y:244
        color: pRgb(43, 112, 173)
        font.family: fontBold
        font.pixelSize: 64
        width: 384
        height: 92
    }
    Text {
        text: qsTr("V2.0.0")
        color: pRgb(43, 112, 173)
        x:919
        y:266
        font.family: fontNormal
        font.pixelSize: 48
        width: 135
        height: 70
    }
    Text {
        id:lotext
        text: qsTr("Loading" + loading)
        color: pRgb(43, 112, 173)
        x:520
        y:411
        font.family: fontNormal
        font.pixelSize: 48
        width: 221
        height: 70
    }
    Timer {
        interval: 500
        running: true
        repeat:true
        onTriggered:{
            if(loading.length === 3){
                stop()
            }
            loading += "."
        }
    }
}
