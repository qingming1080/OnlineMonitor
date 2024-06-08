import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15
Rectangle {
    color: pRgb(153, 204, 255)
    SwipeView{
        id:view
        x:78
        y:29
        width: 1133
        height: 664
        background: Rectangle{
            radius: 5
            color: pRgb(43, 112, 173)
            Button{
                x:1098
                y:5
                width: 30
                height: 30
                background: Rectangle{
                    color: "transparent"
                    Image {
                        anchors.fill: parent
                        source: "qrc:/image/缩小.png"
                    }
                }
            }
        }
        ProductionModule{

        }
        ProductionModule{

        }
        ProductionModule{

        }
        ProductionModule{

        }
    }
    PageIndicator {
        id: indicator

        count: view.count
        currentIndex: view.currentIndex

        anchors.bottom: view.bottom
        anchors.horizontalCenter: parent.horizontalCenter
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
