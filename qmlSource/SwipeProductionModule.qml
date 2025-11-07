import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15
import QtQml.Models 2.15
import GlobalLanguageDefine 1.0
import GlobalSystemDefine 1.0
import GlobalMessageDefine 1.0

Rectangle {
    color: pRgb(153, 204, 255)
    SwipePage {
        id:view
        x:30
        y:29
        width: 1220
        height: 664
        color: pRgb(43, 112, 173)
        radius: 5
    }

    Button{
        x:1206
        y:34
        width: 40
        height: 40
        background: Rectangle{
            color: "transparent"
            Image {
                anchors.centerIn: parent
                source: "qrc:/images/btn_fullscreen_exit.png"
            }
        }
        onPressed: {
            if(equipmentCount === 3){
                swipeCurrIndex = 0
            }
            swipevis = false
            loadViewpro(2,multipro)
        }
        visible: !createModel
    }
}
