import QtQuick              2.0
import GlobalLanguageDefine 1.0
import GlobalSystemDefine   1.0
import LanguageEnum         1.0
Rectangle {
    color: pRgb(153, 204, 255)
    width: 1280
    height: 60
    property string systemStatusText:   GlobalLanguageDefine.strLoading
    property bool   isConnected:        false
    property bool   isContactInfo:      false
    property int    waitSeconds:        0
    property int    maxWaitSeconds:     15
    Image {
        id: imgname
        width: 229
        height: 127.5
        x:235
        y:205
        source: "qrc:/images/logo_hb.png"
    }
    Text {
        id: systemNameText
        text: GlobalLanguageDefine.strSystemName
        x: 483
        y: 254
        color: pRgb(43, 112, 173)
        font.family: GlobalSystemDefine.fontBold
        font.pixelSize: 60
        width: 384
        height: 92
    }
    Text {
        id: systemVersionText
        text: GlobalSystemDefine.strVersionNumber
        color: pRgb(43, 112, 173)
        x: 919
        y: 266
        font.family: GlobalSystemDefine.fontBold
        font.pixelSize: 48
        width: 135
        height: 70
    }
    Text {
        id: lotext
        text: systemStatusText
        color: pRgb(43, 112, 173)
        anchors.top: systemVersionText.bottom
        anchors.topMargin: 30
        anchors.right: parent.right
        anchors.rightMargin: 600
        font.family: GlobalSystemDefine.fontNormal
        font.pixelSize: 48
        width: 221
        height: 70
    }

    Text {
        id: contactInfoText
        text: GlobalLanguageDefine.strContactInfo
        color: pRgb(43, 112, 173)
        anchors.top: lotext.bottom
        anchors.topMargin: 55
        anchors.left: parent.left
        anchors.leftMargin: 350
        font.family: GlobalSystemDefine.fontNormal
        visible: isContactInfo
        font.pixelSize: 48
        width: 221
        height: 70
    }

    Connections {
        target: DeviceManager
        function onNotifyConnectionStateChanged(connected)
        {
            isConnected = connected
            if (connected)
            {
                waitSeconds = 0
                systemStatusText = ""
                ModbusClient.setLearnLedStatus(true);
                ModbusClient.setPilotLedStatus(true);
                ModbusClient.setReadyLedStatus(true);
                ModbusClient.setAlarmLedStatus(true);
                systemStatusText = ""
            }
            else
            {
                waitSeconds = 0
                loadingTimer.start()
                systemStatusText = ""
                window.showWelcomeScreen()
            }
        }
    }

    Timer {
        id: loadingTimer
        interval: 1000
        running: true
        repeat: true
        onTriggered: {
            if(IsRaspberry === false)
            {
                stop()
                window.releaseWelcomeScreen()
            }
            else
            {
                waitSeconds++
                if(waitSeconds >= maxWaitSeconds && !isConnected)
                {
                    stop()
                    systemStatusText = GlobalLanguageDefine.strSystemTimeout + "....." + "\n" + GlobalLanguageDefine.strcontactSupport
                    isContactInfo = true
                    return
                }
                if((isConnected == true) && (systemStatusText.length > 5))
                {
                    stop()
                    isContactInfo = false
                    ModbusClient.setLearnLedStatus(false);
                    ModbusClient.setPilotLedStatus(false);
                    ModbusClient.setReadyLedStatus(false);
                    ModbusClient.setAlarmLedStatus(false);
                    window.releaseWelcomeScreen()
                }
                systemStatusText += "."
            }
        }
    }
}
