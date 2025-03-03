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
        text: qsTr("全视之眼系统")
        x:483
        y:254
        color: pRgb(43, 112, 173)
        font.family: fontBold
        font.pixelSize: LanguageManger.language === "SimplifiedChinese" ? 64 : 40
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
