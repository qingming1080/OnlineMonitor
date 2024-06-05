import QtQuick 2.0
import QtQuick.Controls 2.15
//焊接参数
Rectangle {
    color: pRgb(43, 112, 173)
    radius: 3
    Text {
        text: qsTr("焊接参数")
        font.family: fontBold
        font.pixelSize: 20
        color: pRgb(153, 204, 255)
        x:17
        y:9
    }
    Image {
        id: im1
        source: "qrc:/image/振动.png"
        x:30
        y:58
    }
    Image {
        id: im2
        source: "qrc:/image/舞动振幅.png"
        anchors.top: im1.bottom
        anchors.left: im1.left
        anchors.topMargin: 22
    }
    Image {
        id: im3
        source: "qrc:/image/压力.png"
        anchors.top: im2.bottom
        anchors.left: im2.left
        anchors.topMargin: 22
    }
    Text {
        id: t1
        text: qsTr("能量")
        font.family: fontBold
        font.pixelSize: 16
        color: pRgb(171, 206, 213)
        x:75
        y:61
    }
    Text {
        id: t2
        text: qsTr("振幅")
        font.family: fontBold
        font.pixelSize: 16
        color: pRgb(171, 206, 213)
        anchors.top: t1.bottom
        anchors.left: t1.left
        anchors.topMargin: 31
    }
    Text {
        id: t3
        text: qsTr("压力")
        font.family: fontBold
        font.pixelSize: 16
        color: pRgb(171, 206, 213)
        anchors.top: t2.bottom
        anchors.left: t2.left
        anchors.topMargin: 31
    }
    TextField{
        id:f1
        width: 98
        height: 30
        x:126
        y:59
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter
        color: pRgb(43, 112, 173)
        font.family: fontBold
        font.pixelSize: 16
        background: Rectangle{
            radius: 6
            border.width: 3
            border.color: "#99ccff"
        }
    }
    TextField{
        id:f2
        width: 98
        height: 30
        anchors.left: f1.left
        anchors.top: f1.bottom
        anchors.topMargin: 25
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter
        color: pRgb(43, 112, 173)
        font.family: fontBold
        font.pixelSize: 16
        background: Rectangle{
            radius: 6
            border.width: 3
            border.color: "#99ccff"
        }
    }
    TextField{
        id:f3
        width: 98
        height: 30
        anchors.left: f2.left
        anchors.top: f2.bottom
        anchors.topMargin: 25
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter
        color: pRgb(43, 112, 173)
        font.family: fontBold
        font.pixelSize: 16
        background: Rectangle{
            radius: 6
            border.width: 3
            border.color: "#99ccff"
        }
    }
}
