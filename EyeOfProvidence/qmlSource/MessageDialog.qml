import QtQuick              2.15
import QtQuick.Controls     2.15
import GlobalLanguageDefine 1.0
Popup {
    id: customPopup
    width: 400
    height: 300
    modal: true
    focus: true
    anchors.centerIn: parent

    property string popupTitle: ""
    property string popupText: ""

    function openFor(title, text) {
         popupTitle = title
         popupText = text
         open()
     }

    background: Rectangle {
        color: "#E8E8E8"
        border.color: "#2196F3"
        border.width: 2
        radius: 10
    }

    Column {
        anchors.centerIn: parent
        spacing: 15

        Label {
            text: customPopup.popupTitle
            font.pixelSize: 18
            font.bold: true
            color: "#2196F3"
        }

        Rectangle {
            width: 200
            height: 1
            color: "#2196F3"
        }

        Text {
            text: customPopup.popupText
            color: "#333"
            font.pixelSize: 14
            wrapMode: Text.Wrap
        }

        Button {
            text: GlobalLanguageDefine.strClose
            onClicked: customPopup.close()
            background: Rectangle {
                color: "#2196F3"
                radius: 5
            }
            contentItem: Text {
                text: parent.text
                color: "#E8E8E8"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}
