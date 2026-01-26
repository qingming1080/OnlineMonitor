import QtQuick              2.0
import QmlEnum              1.0
import GlobalLanguageDefine 1.0
import GlobalMessageDefine  1.0
import GlobalSystemDefine   1.0
import LanguageEnum         1.0
//异常信息
Rectangle {
    color: pRgb(43, 112, 173)
    property color listColor: pRgb(153, 204, 255)
    radius: 3
    Text {
        text: GlobalLanguageDefine.strExceptionMesssage
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 20 : 18
        color: pRgb(153, 204, 255)
        x:17
        y:9
    }
    Rectangle{
        y:42
        height: 1
        width: 97
        color: pRgb(174, 210, 216)
    }
    ListView{
        id: taskplanView
        width: 270
        height: 220
        x:24
        y:68
        model: Message
        clip: true
        delegate: Rectangle{
            id: regionItem
            height: 40
            Row{
                anchors.fill: parent
                spacing: 10
                Text{
                    font.pixelSize: 16
                    text: GlobalMessageDefine.getGlobalMessage(messageType, time, welderID)
                    width: 270
                    wrapMode: Text.WordWrap
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    color:listColor
                }
            }

        }
    }
}
