import QtQuick 2.0

Rectangle  {

    id: footer
    width: parent.width
    height: 50
    color: "transparent"
    property string versionText: GlobalLanguageDefine.strSystemVersion + ": " + GlobalSystemDefine.strVersionNumber
    property string currentTime: GlobalMessageDefine.getCurrentTime()

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
        anchors.right: timeText.left
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        anchors.top: parent.top
        anchors.topMargin: 25
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize:14
        text: footer.versionText
    }

    Text
    {
        id: timeText
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        anchors.bottom: version.bottom
        font.pixelSize: 14
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        color: "#639ed6"
        text: footer.currentTime

        Timer
        {
            id: timer
            interval: 1000
            repeat: true
            running: true
            onTriggered: footer.currentTime = GlobalMessageDefine.getCurrentTime()
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: footer.openTimeDialog()
        }
    }

    TimeSettingDialog {
          id: timeDialog
          onTimeSelected: (year, month, day, hour, minute, second) => {
              let date = new Date(year, month - 1, day, hour, minute, second)
              footer.currentTime = date.toLocaleString()
              footer.timeSelected(year, month, day, hour, minute, second)
          }
      }

    signal timeSelected(int year, int month, int day, int hour, int minute, int second)

    function openTimeDialog()
    {
          timeDialog.open()
    }


}
