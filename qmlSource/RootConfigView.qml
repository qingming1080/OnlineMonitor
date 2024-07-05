import QtQuick 2.0
import QtQuick.Controls 2.15
Rectangle {
    radius: 5
    color: pRgb(153, 204, 255)
    RootConfig{
        id:s1
        width: 300
        height: 613
        x:21
        y:25
    }
    RootConfig{
        id:s2
        width: 300
        height: 613
        x:334
        y:25
    }
    RootConfig{
        id:s3
        width: 300
        height: 613
        x:648
        y:25
    }
    RootConfig{
        id:s4
        width: 300
        height: 613
        x:963
        y:25
    }
    Button{
        id:btn1
        x:165
        y:654
        width: 243
        height: 52
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: pRgb(43, 112, 173)
            color: pRgb(43, 112, 173)
        }
        contentItem: Text {
            text: "客户密码重置"
            font.pixelSize: 20
            color: pRgb(153, 204, 255)
            anchors.centerIn: parent  // 确保文本在按钮内居中对齐
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: fontBold
        }
        onPressed: {

        }
    }
    Button{
        id:btn2
        x:519
        y:654
        width: 243
        height: 52
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: pRgb(43, 112, 173)
            color: pRgb(43, 112, 173)
        }
        contentItem: Text {
            text: "保存"
            font.pixelSize: 20
            color: pRgb(153, 204, 255)
            anchors.centerIn: parent  // 确保文本在按钮内居中对齐
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: fontBold
        }
        onPressed: {

        }
    }
    Button{
        id:btn3
        x:867
        y:654
        width: 243
        height: 52
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: pRgb(43, 112, 173)
            color: pRgb(43, 112, 173)
        }
        contentItem: Text {
            text: "初始化"
            font.pixelSize: 20
            color: pRgb(153, 204, 255)
            anchors.centerIn: parent  // 确保文本在按钮内居中对齐
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: fontBold
        }
        onPressed: {

        }
    }
    Text {
        id: version
        color: "#639ed6"
        x:895
        y:718
        font.family: fontBold
        font.pixelSize: 14
        text: qsTr("系统版本号: v2.0.1")
    }
    // 显示时间的文本
    Text {
        id: timeText
        anchors.left: version.right
        anchors.top: version.top
        anchors.leftMargin: 27
        font.pixelSize: 14
        font.family: fontBold
        color: "#639ed6"
        text: getCurrentTime()

        // 定时器每秒更新一次
        Timer {
            interval: 1  // 1秒
            repeat: true
            running: true
            onTriggered: {
                timeText.text = getCurrentTime()
            }
        }
    }
}
