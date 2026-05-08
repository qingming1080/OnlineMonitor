pragma Singleton //we indicate that this QML Type is a singleton
import QtQuick 2.12
QtObject
{
    id: globalSystemDefine
    
    property FontLoader normal: FontLoader{
        source: "qrc:/fonts/SourceHanSansCN-Normal.ttf"
    }
    property FontLoader bold: FontLoader {
        source: "qrc:/fonts/SourceHanSansCN-Bold.ttf"
    }

    property string fontNormal: normal.name
    property string fontBold: bold.name

    // Version Number
    readonly property string strVersionNumber:      "V2.0.6"
}
