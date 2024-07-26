import QtQuick 2.0
import QtQuick.Controls 2.5
Rectangle {
    border.color: "transparent"
    property string btnText: ""
    property int index: 0
    property bool tmp: false
    property alias cbtnText: btText
    property alias btnCheck: btnStatus
    signal sigBtnSwitch(var index)
    color: pRgb(43, 112, 173)
    onTmpChanged: {
        if(tmp){
            btText.color = pRgb(177, 213, 219)
            btnStatus.visible = true
        }
        else{
            btText.color = pRgb(153, 204, 255)
            btnStatus.visible = false
        }
    }

    Rectangle{
        height: 59
        width: 1
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 1
        color: pRgb(177, 213, 219)
    }
    Rectangle{
        height: 59
        width: 1
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 1
        color: pRgb(177, 213, 219)
    }
    Text {
        id: btText
        anchors.centerIn: parent
        font.family: fontBold
        font.pixelSize: 24
        width: 96
        height: 35
        text: btnText
        color: pRgb(153, 204, 255)
    }
    Rectangle{
        id: btnStatus
        width: parent.width
        height: 5
        anchors.bottom: parent.bottom
        color:pRgb(177, 213, 219)
        visible: false
    }

    MouseArea{
        anchors.fill: parent
        onClicked: {
            if(!tmp){
                if(index !== 3){
                    tmp = true
                }
                sigBtnSwitch(index)
            }
        }
    }
}

