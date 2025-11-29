import QtQuick 2.15
import QtQuick.Controls 2.15
import GlobalSystemDefine 1.0

Item {
    id: validText
    property string text: ""
    property color textColor: "#D31245"
    property int fontSize: 18
    property bool visibleWhenEmpty: false
    anchors.left: parent.left
    anchors.leftMargin: 30

    visible: visibleWhenEmpty || text !== ""

    Text {
        id: message
        text: validText.text
        color: validText.textColor
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: validText.fontSize
        wrapMode: Text.WordWrap
    }

    implicitHeight: message.implicitHeight

    function showError(msg)
    {
        validText.text = msg
    }

    function hideError()
    {
        validText.text = ""
    }
}
