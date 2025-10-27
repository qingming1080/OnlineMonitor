import QtQuick 2.15
import QtQuick.Controls 2.15

Popup {
    id: popup
    modal: true
    focus: true
    x: parent ? (parent.width - width)/2 : 0
    y: parent ? (parent.height - height)/2 : 0
    width: 400
    height: 150

    property alias message: messageText.text
    signal confirmed()

    background: Rectangle {
        radius: 8
        color: "#f0f0f0"
        border.color: "#004b8d"
        border.width: 2
    }

    Column {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20
        Text {
            id: messageText
            text: "提示信息"
            color: "#004b8d"
            font.pixelSize: 16
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 100
            height: 35
            text: "确定"
            onClicked: {
                popup.close()
                popup.confirmed()
            }
        }
    }

    function show(msg) {
        messageText.text = msg
        popup.open()
    }
}
