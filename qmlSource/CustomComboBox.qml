import QtQuick 2.0
import QtQuick.Controls 2.5
ComboBox{
    id:comboBox
    signal dataAlter()
    background: Rectangle{
        radius: 6
        border.width: 3
        border.color: "#99ccff"
    }
    contentItem: Rectangle {
        anchors.fill: parent
        color: "transparent"
        Text {
            text: comboBox.displayText
            color: pRgb(43, 112, 173)
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: fontBold
            font.bold: true
            font.pixelSize: 16
        }
    }
    indicator: Item {
        width: 24
        height: 24
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 8
        anchors.rightMargin: 10
        Image {
            source: "qrc:/image/polygon.png"  // 自定义图标的路径
            width: parent.width
            height: parent.height
            anchors.centerIn: parent
        }
    }
    delegate: ItemDelegate {
        width: parent.width
        contentItem: Rectangle{
            id:item
            width: parent.width
            height: parent.height
            Text {
                id:tt
                text: modelData
                font.pixelSize: 16  // 设置字体大小
                color: pRgb(43, 112, 173)
                anchors.centerIn: item
                font.family: fontBold
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                onEntered:  {
                    item.color = pRgb(43, 112, 173)  // 悬浮时背景颜色
                    tt.color = "white"
                }
                onExited: {
                    item.color = "white"
                    tt.color = pRgb(43, 112, 173)
                }
                onPressed: {
                    comboBox.currentIndex = index
                    comboBox.popup.visible = false
                    dataAlter()
                }
            }
        }
    }
}


