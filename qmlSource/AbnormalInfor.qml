import QtQuick 2.0
//异常信息
Rectangle {
    color: pRgb(43, 112, 173)
    radius: 3
    Text {
        text: qsTr("异常信息")
        font.family: fontBold
        font.pixelSize: 20
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
}
