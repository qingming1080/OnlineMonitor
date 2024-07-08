import QtQuick 2.0
import QtCharts 2.15
import Device 1.0
import Trend 1.0
//焊接趋势
Rectangle {
    color: pRgb(43, 112, 173)
    property bool altitudeMode:false
    Connections{
        target: window
        function onSigUpdateUI(index){
            if(index === 0){
                altitudeMode = altitudeModel1
            }
            else if(index === 1){
                altitudeMode = altitudeModel2
            }
            else if(index === 2){
                altitudeMode = altitudeModel3
            }
            else if(index === 3){
                altitudeMode = altitudeModel4
            }
        }
    }

    radius: 3
    Text {
        text: qsTr("焊接趋势")
        font.family: fontBold
        font.pixelSize: mode === 1 ? 17:20
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
    property int timer: 0
    ChartView {
        id:chartView
        width: parent.width // 使图表的宽度等于父项的宽度
        height: parent.height // 使图表的高度等于父项的高度
        anchors.top: parent.top // 使图表的顶部与父项的顶部对齐
        anchors.right: parent.right // 使图表的右侧与父项的右侧对齐
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
        legend {
            font.pixelSize: 16
            font.bold: true
            labelColor: "#a3c7d0"
        }
        ValueAxis {
            id: myAxisX
            min: 0
            max: 10>timer? 10:timer+1
            tickCount: 11
            labelsColor: "#a3c7d0"
            labelsFont.pixelSize: 16
            labelsFont.bold: true
            labelFormat: '%d'
            gridVisible:false
        }
        ValueAxis{
            id:myAxisY
            min:0
            max:50
            tickCount: 9
            labelsColor: "#a3c7d0"
            labelsFont.pixelSize: 16
            labelsFont.bold: true
            labelFormat: '%d'
            gridVisible:false
            color:"#1398fa"
            visible: altitudeMode
        }
        ValueAxis{
            id:myAxisY1
            min:0
            max:50
            tickCount: 9
            labelsColor: "#a3c7d0"
            labelsFont.pixelSize: 16
            labelsFont.bold: true
            labelFormat: '%d'
            gridVisible:false
            color:"#ccb2f8"
            visible: altitudeMode
        }
        ValueAxis{
            id:myAxisY2
            min:0
            max:50
            tickCount: 9
            labelsColor: "#a3c7d0"
            labelsFont.pixelSize: 16
            labelsFont.bold: true
            labelFormat: '%d'
            gridVisible:false
            color:"#d5b989"
        }
        ValueAxis{
            id:myAxisY3
            min:0
            max:50
            tickCount: 9
            labelsColor: "#a3c7d0"
            labelsFont.pixelSize: 16
            labelsFont.bold: true
            labelFormat: '%d'
            gridVisible:false
            color:"#cd9caa"
        }
        LineSeries {
            id:lineSeries2
            name: "焊前高度"
            axisX: myAxisX
            axisY:myAxisY
            color: "#1398fa"
            width: 3
            visible: altitudeMode
            VXYModelMapper{
                model: DeviceManager.deviceList[0].pTrend.pBeforeModel
                series: lineSeries2
                firstRow: 0
                xColumn: 1
                yColumn: 2
            }
        }
        LineSeries {
            id:lineSeries3
            name: "焊后高度"
            axisX: myAxisX
            axisY:myAxisY1
            color: "#ccb2f8"
            width: 3
            visible: altitudeMode
            VXYModelMapper{
                model: DeviceManager.deviceList[0].pTrend.pAfterModel
                series: lineSeries3
                firstRow: 0
                xColumn: 1
                yColumn: 2
            }
        }
        LineSeries {
            id:lineSeries
            name: "功率"
            axisX: myAxisX
            axisY:myAxisY2
            color: "#d5b989"
            width: 3
            VXYModelMapper{
                model: DeviceManager.deviceList[0].pTrend.pPowerModel
                series: lineSeries
                firstRow: 0
                xColumn: 1
                yColumn: 2
            }
        }
        LineSeries {
            id:lineSeries1
            name: "时间"
            axisX: myAxisX
            axisY:myAxisY3
            color: "#cd9caa"
            width: 3
            VXYModelMapper{
                model: DeviceManager.deviceList[0].pTrend.pTimeModel
                series: lineSeries1
                firstRow: 0
                xColumn: 1
                yColumn: 2
            }
        }
//        Timer{
//            interval: 1000
//            running: true
//            repeat: true
//            onTriggered: {
//                lineSeries1.append(timer,Math.random()*50)
//                lineSeries2.append(timer,Math.random()*50)
//                lineSeries3.append(timer,Math.random()*50)
//                lineSeries.append(timer,Math.random()*50)
//                timer = timer+1
//            }
//        }
    }
}
