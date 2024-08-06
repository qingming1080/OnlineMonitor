import QtQuick 2.0
import QtQuick.Controls 2.5
import QtCharts 2.15
import Device 1.0
import Trend 1.0
import CustomTimeChart 1.0

//良率趋势
Rectangle {
    property var startTime: Date.fromLocaleString(Qt.locale(), DeviceManager.deviceList[swipeCurrIndex].pTrend.startTime, "yyyy-MM-dd hh:mm:ss")
    property var endTime: Date.fromLocaleString(Qt.locale(), DeviceManager.deviceList[swipeCurrIndex].pTrend.endTime, "yyyy-MM-dd hh:mm:ss")
    property int equiInforIndex: 0
    property int btnIndex: 1
    onHeightChanged: {
        if(height < 260){
            if(mode == 1){
                btns.x = 180
                chart.width = 500
                chart.height = 200
            }
            else{
                btns.x = 200
                chart.width = 540
                chart.height = 220
            }
        }
        else{
            btns.x =  269
            chart.width = 590
            chart.height = 240
        }
    }
    function btnSwitch(){
        if(btnIndex === 1){
            bbbb.border.color = "#007dbc"
            b.border.color = "#00488d"
            bb.border.color = "#007dbc"
            bbb.border.color = "#007dbc"
            t1.color = "#00488d"
            t2.color = "#b1d5db"
            t3.color = "#b1d5db"
            t4.color = "#b1d5db"
        }
        else if(btnIndex === 2){
            bbbb.border.color = "#007dbc"
            b.border.color = "#007dbc"
            bb.border.color = "#00488d"
            bbb.border.color = "#007dbc"
            t2.color = "#00488d"
            t1.color = "#b1d5db"
            t3.color = "#b1d5db"
            t4.color = "#b1d5db"
        }
        else if(btnIndex === 3){
            bbbb.border.color = "#007dbc"
            b.border.color = "#007dbc"
            bb.border.color = "#007dbc"
            bbb.border.color = "#00488d"
            t3.color = "#00488d"
            t2.color = "#b1d5db"
            t1.color = "#b1d5db"
            t4.color = "#b1d5db"
        }
        else if(btnIndex === 4){
            bbbb.border.color = "#00488d"
            b.border.color = "#007dbc"
            bb.border.color = "#007dbc"
            bbb.border.color = "#007dbc"
            t4.color = "#00488d"
            t3.color = "#b1d5db"
            t2.color = "#b1d5db"
            t1.color = "#b1d5db"
        }
    }

    onBtnIndexChanged: {
        btnSwitch()
    }

    onVisibleChanged: {
        if(visible){
            enabled = true
        }
        else{
            enabled = false
        }
    }
    color: pRgb(43, 112, 173)
    radius: 3
    Text {
        text: qsTr("良率趋势")
        font.family: fontBold
        font.pixelSize: mode === 1 ? 17 : 20
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
        id:btns
        width: 320
        height: 34
        x:269
        y:12
        border.color: "#195f9f"
        border.width: 2
        radius: 4
        color:"#007dbc"
        Component.onCompleted: {
            btnSwitch()
            if(equipmentCount > 0){
                chart.setIndex(swipeCurrIndex)
            }
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
                color:pRgb(177, 213, 219)
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
                b.color = pRgb(177, 213, 219)
                bb.color = "#007dbc"
                bbb.color = "#007dbc"
                bbbb.color = "#007dbc"
                buttonSynchronization(equiInforIndex,1)
                DeviceManager.deviceList[swipeCurrIndex].pTrend.setYieldType(0)
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
                b.color = "#007dbc"
                bb.color = pRgb(177, 213, 219)
                bbb.color = "#007dbc"
                bbbb.color = "#007dbc"
                buttonSynchronization(equiInforIndex,2)
                DeviceManager.deviceList[swipeCurrIndex].pTrend.setYieldType(1)
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
                b.color = "#007dbc"
                bb.color = "#007dbc"
                bbb.color = pRgb(177, 213, 219)
                bbbb.color = "#007dbc"
                buttonSynchronization(equiInforIndex,3)
                DeviceManager.deviceList[swipeCurrIndex].pTrend.setYieldType(2)
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
                b.color = "#007dbc"
                bb.color = "#007dbc"
                bbb.color = "#007dbc"
                bbbb.color = pRgb(177, 213, 219)
                buttonSynchronization(equiInforIndex,4)
                DeviceManager.deviceList[swipeCurrIndex].pTrend.setYieldType(3)
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

    Connections{
        target: window
        function onSigSwipeCurrIndex(swipeCurrIndex){
            chart.setSwipeCurrIndex(swipeCurrIndex)
        }
    }

    property int timer: 0
    CustomTimeChart{
        id:chart
        anchors.top: line.bottom // 使图表的顶部与父项的顶部对齐
        fillColor: "transparent"
        width: 590
    }

//    ChartView {
//        id:chart
//        anchors.top: line.bottom // 使图表的顶部与父项的顶部对齐
//        width: 590
//        height: 240
//        antialiasing: true
//        backgroundColor: "transparent"
//        animationOptions: ChartView.SeriesAnimations
//        titleColor: "red"
//        titleFont.family: fontBold
//        titleFont.pixelSize: 20
//        margins.left: 10
//        margins.right: 10
//        margins.top: 10
//        margins.bottom: 10
//        legend.visible: false
//        DateTimeAxis {
//            id: myAxisX
//            format: "MM-dd hh:mm" // 时间格式
//            tickCount: 5
//            min: startTime
//            max: endTime
//            labelsColor: "#a3c7d0"
//            labelsFont.pixelSize: 12
//            labelsFont.bold: true
//            gridVisible:false
//        }
//        ValueAxis{
//            id:myAxisY
//            min:0
//            max:100
//            tickCount: 3
//            labelsColor: "#a3c7d0"
//            labelsFont.pixelSize: 16
//            labelsFont.bold: true
//            labelFormat: '%d%'
//            color:"#1398fa"
//            lineVisible: false

//        }
//        LineSeries {
//            id:lineSeries
//            axisX: myAxisX
//            axisY:myAxisY
//            color: "#1398fa"
//            width: 3
//            VXYModelMapper{
//                model: DeviceManager.deviceList[swipeCurrIndex].pTrend.pYieldTrend
//                series: lineSeries
//                firstRow: 0
//                xColumn: 1
//                yColumn: 2
//            }
//            useOpenGL: true
//        }
//        ScatterSeries{
//            id:lineSeries1
//            axisX: myAxisX
//            axisY:myAxisY
//            markerSize: 10
//            useOpenGL: true
//        }
//    }

}
