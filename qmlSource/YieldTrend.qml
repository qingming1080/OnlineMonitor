import QtQuick 2.0
import QtQuick.Controls 2.5
import QtCharts 2.15
//良率趋势
Rectangle {
    property var startTime: Date.fromLocaleString(Qt.locale(), "2001-01-01 01:00:00", "yyyy-MM-dd hh:mm:ss")
    property var endTime: Date.fromLocaleString(Qt.locale(), "2001-01-01 02:00:00", "yyyy-MM-dd hh:mm:ss")
    color: pRgb(43, 112, 173)
    radius: 3
    Text {
        text: qsTr("设备信息")
        font.family: fontBold
        font.pixelSize: 20
        color: pRgb(153, 204, 255)
        x:17
        y:9
    }
    Rectangle{
        id:line
        y:42
        height: 1
        width: 97
        color: pRgb(174, 210, 216)
    }
    Rectangle{
        width: 320
        height: 34
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 12
        anchors.leftMargin: 269
        border.color: "#195f9f"
        border.width: 2
        radius: 4
        color:"#007dbc"
        Component.onCompleted: {
            bbbb.border.color = "#007dbc"
            b.border.color = "#00488d"
            bb.border.color = "#007dbc"
            bbb.border.color = "#007dbc"
            t1.color = "#00488d"
            t2.color = "#b1d5db"
            t3.color = "#b1d5db"
            t4.color = "#b1d5db"
        }

        Button{
            id:b1
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 2
            anchors.leftMargin: 2
            checkable: true
            width: 79
            height: 30
            background: Rectangle{
                id:b
                color:"#007dbc"
                radius: 3
            }
            onClicked: {
                bbbb.border.color = "#007dbc"
                b.border.color = "#00488d"
                bb.border.color = "#007dbc"
                bbb.border.color = "#007dbc"
                t1.color = "#00488d"
                t2.color = "#b1d5db"
                t3.color = "#b1d5db"
                t4.color = "#b1d5db"
            }
            contentItem: Text {
                id:t1
                anchors.centerIn: parent
                text: "1小时"
                font.pixelSize: 16
                color: pRgb(153, 204, 255)
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: fontNormal
            }
        }
        Button{
            id:b2
            anchors.left: b1.right
            anchors.top: b1.top
            width: 79
            height: 30
            background: Rectangle{
                id:bb
                color:"#007dbc"
                radius: 3
            }
            onClicked: {
                bbbb.border.color = "#007dbc"
                b.border.color = "#007dbc"
                bb.border.color = "#00488d"
                bbb.border.color = "#007dbc"
                t2.color = "#00488d"
                t1.color = "#b1d5db"
                t3.color = "#b1d5db"
                t4.color = "#b1d5db"
            }
            contentItem: Text {
                id:t2
                anchors.centerIn: parent
                text: "24小时"
                font.pixelSize: 16
                color: pRgb(153, 204, 255)
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: fontNormal
            }
        }
        Button{
            id:b3
            anchors.left: b2.right
            anchors.top: b2.top
            width: 79
            height: 30
            background: Rectangle{
                id:bbb
                color:"#007dbc"
                radius: 3
            }
            onClicked: {
                bbbb.border.color = "#007dbc"
                b.border.color = "#007dbc"
                bb.border.color = "#007dbc"
                bbb.border.color = "#00488d"
                t3.color = "#00488d"
                t2.color = "#b1d5db"
                t1.color = "#b1d5db"
                t4.color = "#b1d5db"
            }
            contentItem: Text {
                id:t3
                anchors.centerIn: parent
                text: "7天"
                font.pixelSize: 16
                color: pRgb(153, 204, 255)
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: fontNormal
            }
        }
        Button{
            id:b4
            anchors.left: b3.right
            anchors.top: b3.top
            width: 79
            height: 30
            background: Rectangle{
                id:bbbb
                color: "#007dbc"
                radius: 3
            }
            onClicked: {
                bbbb.border.color = "#00488d"
                b.border.color = "#007dbc"
                bb.border.color = "#007dbc"
                bbb.border.color = "#007dbc"
                t4.color = "#00488d"
                t3.color = "#b1d5db"
                t2.color = "#b1d5db"
                t1.color = "#b1d5db"
            }
            contentItem: Text {
                id:t4
                anchors.centerIn: parent
                text: "30天"
                font.pixelSize: 16
                color: pRgb(153, 204, 255)
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: fontNormal
            }
        }
    }

    property int timer: 0
    ChartView {
        anchors.top: line.bottom // 使图表的顶部与父项的顶部对齐
        width: 590
        height: 240
        antialiasing: true
        backgroundColor: "transparent"
        animationOptions: ChartView.SeriesAnimations
        titleColor: "red"
        titleFont.family: fontBold
        titleFont.pixelSize: 20
        margins.left: 10
        margins.right: 10
        margins.top: 10
        margins.bottom: 10
        legend.visible: false
        DateTimeAxis {
            id: myAxisX
            format: "hh:mm" // 时间格式
            tickCount: 5
            min: startTime
            max: endTime
            labelsColor: "#a3c7d0"
            labelsFont.pixelSize: 16
            labelsFont.bold: true
            gridVisible:false
        }
        ValueAxis{
            id:myAxisY
            min:0
            max:100
            tickCount: 3
            labelsColor: "#a3c7d0"
            labelsFont.pixelSize: 16
            labelsFont.bold: true
            labelFormat: '%d%'
            color:"#1398fa"
            lineVisible: false

        }
        LineSeries {
            id:lineSeries
            axisX: myAxisX
            axisY:myAxisY
            color: "#1398fa"
            width: 3
        }
        ScatterSeries{
            id:lineSeries1
            axisX: myAxisX
            axisY:myAxisY
            markerSize: 10
        }

        Component.onCompleted: {
            lineSeries.append(Date.fromLocaleString(Qt.locale(), "2001-01-01 01:00:00", "yyyy-MM-dd hh:mm:ss"), 10)
            lineSeries.append(Date.fromLocaleString(Qt.locale(), "2001-01-01 01:10:00", "yyyy-MM-dd hh:mm:ss"), 10)
            lineSeries.append(Date.fromLocaleString(Qt.locale(), "2001-01-01 01:20:00", "yyyy-MM-dd hh:mm:ss"), 20)
            lineSeries.append(Date.fromLocaleString(Qt.locale(), "2001-01-01 01:30:00", "yyyy-MM-dd hh:mm:ss"), 30)
            lineSeries.append(Date.fromLocaleString(Qt.locale(), "2001-01-01 01:40:00", "yyyy-MM-dd hh:mm:ss"), 40)
            lineSeries.append(Date.fromLocaleString(Qt.locale(), "2001-01-01 01:50:00", "yyyy-MM-dd hh:mm:ss"), 50)
            lineSeries.append(Date.fromLocaleString(Qt.locale(), "2001-01-01 01:60:00", "yyyy-MM-dd hh:mm:ss"), 60)

            lineSeries1.append(Date.fromLocaleString(Qt.locale(), "2001-01-01 01:00:00", "yyyy-MM-dd hh:mm:ss"), 10)
            lineSeries1.append(Date.fromLocaleString(Qt.locale(), "2001-01-01 01:10:00", "yyyy-MM-dd hh:mm:ss"), 10)
            lineSeries1.append(Date.fromLocaleString(Qt.locale(), "2001-01-01 01:20:00", "yyyy-MM-dd hh:mm:ss"), 20)
            lineSeries1.append(Date.fromLocaleString(Qt.locale(), "2001-01-01 01:30:00", "yyyy-MM-dd hh:mm:ss"), 30)
            lineSeries1.append(Date.fromLocaleString(Qt.locale(), "2001-01-01 01:40:00", "yyyy-MM-dd hh:mm:ss"), 40)
            lineSeries1.append(Date.fromLocaleString(Qt.locale(), "2001-01-01 01:50:00", "yyyy-MM-dd hh:mm:ss"), 50)
            lineSeries1.append(Date.fromLocaleString(Qt.locale(), "2001-01-01 01:60:00", "yyyy-MM-dd hh:mm:ss"), 60)
        }
    }
}
