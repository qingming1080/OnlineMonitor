import QtQuick 2.0
//实时良率
Rectangle {
    property string eqText1: ""
    property string eqText2: ""
    property string eqText3: ""
    color: pRgb(43, 112, 173)
    radius: 3
    Text {
        text: qsTr("实时良率")
        font.family: fontBold
        font.pixelSize: 20
        color: pRgb(153, 204, 255)
        x:17
        y:9
    }
    Text {
        id:t1
        x:19
        y:90
        text: qsTr("合格: ") + eqText1
        font.family: fontBold
        font.pixelSize: 16
        color: pRgb(171, 206, 213)
    }
    Text {
        id:t2
        text: qsTr("可疑: ") + eqText2
        font.family: fontBold
        font.pixelSize: 16
        color: pRgb(171, 206, 213)
        anchors.left: t1.left
        anchors.top: t1.bottom
        anchors.topMargin: 25
    }
    Text {
        id:t3
        text: qsTr("次品: ") + eqText3
        font.family: fontBold
        font.pixelSize: 16
        color: pRgb(171, 206, 213)
        anchors.left: t2.left
        anchors.top: t2.bottom
        anchors.topMargin: 25
    }
    CustomRipple{
        x:140
        y:38
    }
}
