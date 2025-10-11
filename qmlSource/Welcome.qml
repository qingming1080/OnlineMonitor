import QtQuick 2.0
import GlobalLanguageDefine 1.0
import GlobalSystemDefine 1.0
import LanguageEnum 1.0
Rectangle {
    color: pRgb(153, 204, 255)
    width: 1280
    height: 60
    property string loading: ""
    Image {
        id: imgname
        width: 229
        height: 127.5
        x:235
        y:205
        source: "qrc:/images/logo_hb.png"
    }
    Text {
        text: GlobalLanguageDefine.strSystemName
        x: 483
        y: 254
        color: pRgb(43, 112, 173)
        font.family: GlobalSystemDefine.fontBold
        font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 64 : 60
        width: 384
        height: 92
    }
    Text {
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
        id:lotext
        // text: qsTr("Loading") + loading
        text: GlobalLanguageDefine.strLoading + loading
        color: pRgb(43, 112, 173)
        x:520
        y:411
        font.family: GlobalSystemDefine.fontNormal
        font.pixelSize: 48
        width: 221
        height: 70
    }
    Timer {
        interval: 1000
        running: true
        repeat: true
        onTriggered:{
            if(loading.length >= 3)
            {
                stop()
                window.releaseWelcomeScreen()
            }
            else
                loading += "."
        }
    }
}
