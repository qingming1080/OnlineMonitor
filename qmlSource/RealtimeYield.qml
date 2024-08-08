import QtQuick 2.0
//实时良率
Rectangle {
    property string eqText1: ""
    property string eqText2: ""
    property string eqText3: ""
    property string eqText4: ""
    property string eqText5: ""
    property bool revealing: true
    onHeightChanged: {
        if(height < 260 && height > 230){
            yuan.x = 110
            yuan.implicitWidth = 172
            yuan.implicitHeight = 172
        }
        else if(height < 250 && height > 220){
            yuan.implicitWidth = 140
            yuan.implicitHeight = 140
            yuan.x = 120
        }
        else{
            yuan.implicitWidth = 172
            yuan.implicitHeight = 172
            yuan.x = 150
        }
    }

    color: pRgb(43, 112, 173)
    radius: 3
    Rectangle{
        y:42
        height: 1
        width: 97
        color: pRgb(174, 210, 216)
    }
    Text {
        text: qsTr("实时良率")
        font.family: fontBold
        font.bold: true
        font.pixelSize: LanguageManger.language === "SimplifiedChinese" ? 20 : 18
        color: pRgb(153, 204, 255)
        x:17
        y:9
    }
    Text {
        id:t1
        x:19
        y:65
        text: qsTr("合格: ") + eqText1
        font.family: fontBold
        font.bold: true
        font.pixelSize: LanguageManger.language === "SimplifiedChinese" ?16 : 14
        color: pRgb(171, 206, 213)
    }
    Text {
        id:t2
        text: qsTr("可疑: ") + eqText2
        font.family: fontBold
        font.bold: true
        font.pixelSize: LanguageManger.language === "SimplifiedChinese" ?16 : 14
        color: pRgb(171, 206, 213)
        anchors.left: t1.left
        anchors.top: t1.bottom
        anchors.topMargin: 20
        visible:revealing
    }
    Text {
        id:t3
        text: qsTr("次品: ") + eqText3
        font.family: fontBold
        font.bold: true
        font.pixelSize: LanguageManger.language === "SimplifiedChinese" ?16 : 14
        color: pRgb(171, 206, 213)
        anchors.left: revealing === false ? t1.left : t2.left
        anchors.top: revealing === false ? t1.bottom : t2.bottom
        anchors.topMargin: 20
    }
    Text {
        id:t4
        text: qsTr("总计: ") + eqText4
        font.family: fontBold
        font.bold: true
        font.pixelSize: LanguageManger.language === "SimplifiedChinese" ?16 : 14
        color: pRgb(171, 206, 213)
        anchors.left: t3.left
        anchors.top: t3.bottom
        anchors.topMargin: 20
    }
    CustomRipple{
        id: yuan
        x:150
        y:58
        value:eqText5
    }
}
