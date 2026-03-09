import QtQuick                  2.0
import GlobalStyle              1.0
import GlobalSystemDefine       1.0
Rectangle{

    id: footer
    width: parent.width
    height: 100
    // color: GlobalStyle.backgroundColor
    color: pRgb(153, 204, 255)
    property string versionText: GlobalLanguageDefine.strSystemVersion + ": " + GlobalSystemDefine.strVersionNumber
    property string currentTime: GlobalMessageDefine.getCurrentTime()

    Connections{
        target: window
        function onSignalOneSecondEvent()
        {
            footer.currentTime = GlobalMessageDefine.getCurrentTime()
        }
    }

    ValidMessage
    {
        id: validMessage
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
    }

    function showError(msg)
    {
        validMessage.showError(msg)
    }

    function hideError()
    {
        validMessage.hideError()
    }

    Text
    {
        id: version
        color: "#639ed6"
        anchors.right: timeRect.left
        anchors.rightMargin: 20
        anchors.top: timeRect.top
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize:14
        text: footer.versionText
    }

    Rectangle {
        id: timeRect
        width: 150
        height: 40
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 45
        anchors.bottomMargin: -10
        color: "transparent"

        Text {
            id: timeText
            text: footer.currentTime
            font.pixelSize: 14
            font.family: GlobalSystemDefine.fontBold
            color: "#639ed6"
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked:
            {
                dateTimeSetting.visible = true
            }
        }
    }
}
