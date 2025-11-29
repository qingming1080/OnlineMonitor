import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: loadingOverlay
    property alias progress: progressBar.value
    anchors.fill: parent
    color: "#80000000"
    // visible: false

    Rectangle {
        id: indicator
        anchors.centerIn: parent
        width: 200
        height: 100
        color: "white"
        radius: 10

        Column {
            anchors.centerIn: parent
            spacing: 20

            BusyIndicator {
                anchors.horizontalCenter: parent.horizontalCenter
                running: loadingOverlay.visible
            }

            Text {
                id: statusText
                text: qsTr("正在导出...")
                font.pixelSize: 16
                font.family: "宋体"
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }

    ProgressBar
    {
        id: progressBar
        width: 200
        height: 20
        anchors.top: indicator.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        value: 0

        style: ProgressBarStyle {
            background: Rectangle {
                radius: 8
                color: "#e0e0e0"
                border.color: "#cccccc"
                border.width: 1
                implicitWidth: 200
                implicitHeight: 20
            }
            progress: Rectangle {
                color: "#2196F3"  // 蓝色进度条
                radius: 8

                // 可选：添加渐变效果
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#42A5F5" }
                    GradientStop { position: 1.0; color: "#1976D2" }
                }
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        // 阻止背景点击
    }
}
