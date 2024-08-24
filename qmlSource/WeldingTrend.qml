import QtQuick 2.0
import QtCharts 2.15
import Device 1.0
import Trend 1.0
//import CustomChart 1.0
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
        font.bold: true
        font.pixelSize: LanguageManger.language === "SimplifiedChinese" ? 20 : 18
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
    //    CustomChart {
    //        id:chartView
    //        anchors.fill: parent
    //        fillColor: "transparent"
    //        width: parent.width // 使图表的宽度等于父项的宽度
    //        height: parent.height // 使图表的高度等于父项的高度
    //        anchors.top: parent.top // 使图表的顶部与父项的顶部对齐
    //        anchors.right: parent.right // 使图表的右侧与父项的右侧对齐
    //        anchors.topMargin: 10
    //    }

    ChartView {
        id:chartView
        width: parent.width // 使图表的宽度等于父项的宽度
        height: parent.height // 使图表的高度等于父项的高度
        anchors.top: parent.top // 使图表的顶部与父项的顶部对齐
        anchors.right: parent.right // 使图表的右侧与父项的右侧对齐
        antialiasing: true
        backgroundColor: "transparent"
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
            font.family: fontBold
        }
        Component.onCompleted: {
            sigUpdateUI(swipeCurrIndex)
            chartUpdata()
        }

        Component.onDestruction: {
            DeviceManager.deviceList[0].pTrend.setFrontSeries(null)
            DeviceManager.deviceList[0].pTrend.setBackSeries(null)
            DeviceManager.deviceList[0].pTrend.setTimeSeries(null)
            DeviceManager.deviceList[0].pTrend.setPowerSeries(null)
            DeviceManager.deviceList[1].pTrend.setFrontSeries(null)
            DeviceManager.deviceList[1].pTrend.setBackSeries(null)
            DeviceManager.deviceList[1].pTrend.setTimeSeries(null)
            DeviceManager.deviceList[1].pTrend.setPowerSeries(null)
            DeviceManager.deviceList[2].pTrend.setFrontSeries(null)
            DeviceManager.deviceList[2].pTrend.setBackSeries(null)
            DeviceManager.deviceList[2].pTrend.setTimeSeries(null)
            DeviceManager.deviceList[2].pTrend.setPowerSeries(null)
            DeviceManager.deviceList[3].pTrend.setFrontSeries(null)
            DeviceManager.deviceList[3].pTrend.setBackSeries(null)
            DeviceManager.deviceList[3].pTrend.setTimeSeries(null)
            DeviceManager.deviceList[3].pTrend.setPowerSeries(null)
        }

        ValueAxis {
            id: myAxisX
            min: DeviceManager.deviceList[swipeCurrIndex].pTrend.idMinX
            max: DeviceManager.deviceList[swipeCurrIndex].pTrend.idMaxX
            tickCount: 5
            labelsColor: "#a3c7d0"
            labelsFont.pixelSize: 12
            labelsFont.bold: true
            labelFormat: '%d'
            gridVisible:false
        }
        ValueAxis{
            id:myAxisY
            min:DeviceManager.deviceList[swipeCurrIndex].pTrend.beforeMinY
            max:DeviceManager.deviceList[swipeCurrIndex].pTrend.beforeMaxY
            tickCount: 9
            labelsColor: "#a3c7d0"
            labelsFont.pixelSize: 12
            labelsFont.bold: true
            labelFormat: '%d'
            gridVisible:false
            color:"#1398fa"
            visible: altitudeMode
        }
        ValueAxis{
            id:myAxisY1
            min:DeviceManager.deviceList[swipeCurrIndex].pTrend.afterMinY
            max:DeviceManager.deviceList[swipeCurrIndex].pTrend.afterMaxY
            tickCount: 9
            labelsColor: "#a3c7d0"
            labelsFont.pixelSize: 12
            labelsFont.bold: true
            labelFormat: '%d'
            gridVisible:false
            color:"#ccb2f8"
            visible: altitudeMode
        }
        ValueAxis{
            id:myAxisY2
            min:DeviceManager.deviceList[swipeCurrIndex].pTrend.powerMinY
            max:DeviceManager.deviceList[swipeCurrIndex].pTrend.powerMaxY
            tickCount: 9
            labelsColor: "#a3c7d0"
            labelsFont.pixelSize: 12
            labelsFont.bold: true
            labelFormat: '%d'
            gridVisible:false
            color:"#d5b989"
        }
        ValueAxis{
            id:myAxisY3
            min:DeviceManager.deviceList[swipeCurrIndex].pTrend.timeMinY
            max:DeviceManager.deviceList[swipeCurrIndex].pTrend.timeMaxY
            tickCount: 9
            labelsColor: "#a3c7d0"
            labelsFont.pixelSize: 12
            labelsFont.bold: true
            labelFormat: '%.2f'
            gridVisible:false
            color:"#cd9caa"
        }
        LineSeries {
            id:lineSeries
            name: "功率"
            axisX: myAxisX
            axisY:myAxisY2
            color: "#d5b989"
            width: 3

        }
        LineSeries {
            id:lineSeries1
            name: "时间"
            axisX: myAxisX
            axisY:myAxisY3
            color: "#cd9caa"
            width: 3

        }
        LineSeries {
            id:lineSeries2
            name: "焊前高度"
            axisX: myAxisX
            axisY:myAxisY
            color: "#1398fa"
            width: 3
            visible: altitudeMode

        }
        LineSeries {
            id:lineSeries3
            name: "焊后高度"
            axisX: myAxisX
            axisY:myAxisY1
            color: "#ccb2f8"
            width: 3
            visible: altitudeMode

        }
        Connections
        {
            target: DeviceManager
            function onDeviceNumChanged(){
                chartUpdata()
            }
        }
        function chartUpdata(){
            if(equipmentCount === 1){
                DeviceManager.deviceList[0].pTrend.setFrontSeries((chartView.series(lineSeries2.name)))
                DeviceManager.deviceList[0].pTrend.setBackSeries((chartView.series(lineSeries3.name)))
                DeviceManager.deviceList[0].pTrend.setTimeSeries((chartView.series(lineSeries1.name)))
                DeviceManager.deviceList[0].pTrend.setPowerSeries((chartView.series(lineSeries.name)))
                return
            }
            if(swipevis){
                if(equipmentCount === 2){
                    if(swipeCurrIndex === 0){
                        DeviceManager.deviceList[0].pTrend.setFrontSeries((chartView.series(lineSeries2.name)))
                        DeviceManager.deviceList[0].pTrend.setBackSeries((chartView.series(lineSeries3.name)))
                        DeviceManager.deviceList[0].pTrend.setTimeSeries((chartView.series(lineSeries1.name)))
                        DeviceManager.deviceList[0].pTrend.setPowerSeries((chartView.series(lineSeries.name)))

                        DeviceManager.deviceList[1].pTrend.setFrontSeries(null)
                        DeviceManager.deviceList[1].pTrend.setBackSeries(null)
                        DeviceManager.deviceList[1].pTrend.setTimeSeries(null)
                        DeviceManager.deviceList[1].pTrend.setPowerSeries(null)
                    }
                    else if(swipeCurrIndex === 1){
                        DeviceManager.deviceList[1].pTrend.setFrontSeries((chartView.series(lineSeries2.name)))
                        DeviceManager.deviceList[1].pTrend.setBackSeries((chartView.series(lineSeries3.name)))
                        DeviceManager.deviceList[1].pTrend.setTimeSeries((chartView.series(lineSeries1.name)))
                        DeviceManager.deviceList[1].pTrend.setPowerSeries((chartView.series(lineSeries.name)))

                        DeviceManager.deviceList[0].pTrend.setFrontSeries(null)
                        DeviceManager.deviceList[0].pTrend.setBackSeries(null)
                        DeviceManager.deviceList[0].pTrend.setTimeSeries(null)
                        DeviceManager.deviceList[0].pTrend.setPowerSeries(null)
                    }

                }
                else if(equipmentCount === 3){
                    if(swipeCurrIndex === 0){
                        DeviceManager.deviceList[0].pTrend.setFrontSeries((chartView.series(lineSeries2.name)))
                        DeviceManager.deviceList[0].pTrend.setBackSeries((chartView.series(lineSeries3.name)))
                        DeviceManager.deviceList[0].pTrend.setTimeSeries((chartView.series(lineSeries1.name)))
                        DeviceManager.deviceList[0].pTrend.setPowerSeries((chartView.series(lineSeries.name)))

                        DeviceManager.deviceList[1].pTrend.setFrontSeries(null)
                        DeviceManager.deviceList[1].pTrend.setBackSeries(null)
                        DeviceManager.deviceList[1].pTrend.setTimeSeries(null)
                        DeviceManager.deviceList[1].pTrend.setPowerSeries(null)
                        DeviceManager.deviceList[2].pTrend.setFrontSeries(null)
                        DeviceManager.deviceList[2].pTrend.setBackSeries(null)
                        DeviceManager.deviceList[2].pTrend.setTimeSeries(null)
                        DeviceManager.deviceList[2].pTrend.setPowerSeries(null)
                    }
                    else if(swipeCurrIndex === 1){
                        DeviceManager.deviceList[1].pTrend.setFrontSeries((chartView.series(lineSeries2.name)))
                        DeviceManager.deviceList[1].pTrend.setBackSeries((chartView.series(lineSeries3.name)))
                        DeviceManager.deviceList[1].pTrend.setTimeSeries((chartView.series(lineSeries1.name)))
                        DeviceManager.deviceList[1].pTrend.setPowerSeries((chartView.series(lineSeries.name)))

                        DeviceManager.deviceList[0].pTrend.setFrontSeries(null)
                        DeviceManager.deviceList[0].pTrend.setBackSeries(null)
                        DeviceManager.deviceList[0].pTrend.setTimeSeries(null)
                        DeviceManager.deviceList[0].pTrend.setPowerSeries(null)
                        DeviceManager.deviceList[2].pTrend.setFrontSeries(null)
                        DeviceManager.deviceList[2].pTrend.setBackSeries(null)
                        DeviceManager.deviceList[2].pTrend.setTimeSeries(null)
                        DeviceManager.deviceList[2].pTrend.setPowerSeries(null)
                    }
                    else if(swipeCurrIndex === 2){
                        DeviceManager.deviceList[2].pTrend.setFrontSeries((chartView.series(lineSeries2.name)))
                        DeviceManager.deviceList[2].pTrend.setBackSeries((chartView.series(lineSeries3.name)))
                        DeviceManager.deviceList[2].pTrend.setTimeSeries((chartView.series(lineSeries1.name)))
                        DeviceManager.deviceList[2].pTrend.setPowerSeries((chartView.series(lineSeries.name)))

                        DeviceManager.deviceList[1].pTrend.setFrontSeries(null)
                        DeviceManager.deviceList[1].pTrend.setBackSeries(null)
                        DeviceManager.deviceList[1].pTrend.setTimeSeries(null)
                        DeviceManager.deviceList[1].pTrend.setPowerSeries(null)
                        DeviceManager.deviceList[0].pTrend.setFrontSeries(null)
                        DeviceManager.deviceList[0].pTrend.setBackSeries(null)
                        DeviceManager.deviceList[0].pTrend.setTimeSeries(null)
                        DeviceManager.deviceList[0].pTrend.setPowerSeries(null)
                    }
                }
                else if(equipmentCount === 4){
                    if(swipeCurrIndex === 0){
                        DeviceManager.deviceList[0].pTrend.setFrontSeries((chartView.series(lineSeries2.name)))
                        DeviceManager.deviceList[0].pTrend.setBackSeries((chartView.series(lineSeries3.name)))
                        DeviceManager.deviceList[0].pTrend.setTimeSeries((chartView.series(lineSeries1.name)))
                        DeviceManager.deviceList[0].pTrend.setPowerSeries((chartView.series(lineSeries.name)))

                        DeviceManager.deviceList[1].pTrend.setFrontSeries(null)
                        DeviceManager.deviceList[1].pTrend.setBackSeries(null)
                        DeviceManager.deviceList[1].pTrend.setTimeSeries(null)
                        DeviceManager.deviceList[1].pTrend.setPowerSeries(null)
                        DeviceManager.deviceList[2].pTrend.setFrontSeries(null)
                        DeviceManager.deviceList[2].pTrend.setBackSeries(null)
                        DeviceManager.deviceList[2].pTrend.setTimeSeries(null)
                        DeviceManager.deviceList[2].pTrend.setPowerSeries(null)
                        DeviceManager.deviceList[3].pTrend.setFrontSeries(null)
                        DeviceManager.deviceList[3].pTrend.setBackSeries(null)
                        DeviceManager.deviceList[3].pTrend.setTimeSeries(null)
                        DeviceManager.deviceList[3].pTrend.setPowerSeries(null)
                    }
                    else if(swipeCurrIndex === 1){
                        DeviceManager.deviceList[1].pTrend.setFrontSeries((chartView.series(lineSeries2.name)))
                        DeviceManager.deviceList[1].pTrend.setBackSeries((chartView.series(lineSeries3.name)))
                        DeviceManager.deviceList[1].pTrend.setTimeSeries((chartView.series(lineSeries1.name)))
                        DeviceManager.deviceList[1].pTrend.setPowerSeries((chartView.series(lineSeries.name)))

                        DeviceManager.deviceList[0].pTrend.setFrontSeries(null)
                        DeviceManager.deviceList[0].pTrend.setBackSeries(null)
                        DeviceManager.deviceList[0].pTrend.setTimeSeries(null)
                        DeviceManager.deviceList[0].pTrend.setPowerSeries(null)
                        DeviceManager.deviceList[2].pTrend.setFrontSeries(null)
                        DeviceManager.deviceList[2].pTrend.setBackSeries(null)
                        DeviceManager.deviceList[2].pTrend.setTimeSeries(null)
                        DeviceManager.deviceList[2].pTrend.setPowerSeries(null)
                        DeviceManager.deviceList[3].pTrend.setFrontSeries(null)
                        DeviceManager.deviceList[3].pTrend.setBackSeries(null)
                        DeviceManager.deviceList[3].pTrend.setTimeSeries(null)
                        DeviceManager.deviceList[3].pTrend.setPowerSeries(null)
                    }
                    else if(swipeCurrIndex === 2){
                        DeviceManager.deviceList[2].pTrend.setFrontSeries((chartView.series(lineSeries2.name)))
                        DeviceManager.deviceList[2].pTrend.setBackSeries((chartView.series(lineSeries3.name)))
                        DeviceManager.deviceList[2].pTrend.setTimeSeries((chartView.series(lineSeries1.name)))
                        DeviceManager.deviceList[2].pTrend.setPowerSeries((chartView.series(lineSeries.name)))

                        DeviceManager.deviceList[1].pTrend.setFrontSeries(null)
                        DeviceManager.deviceList[1].pTrend.setBackSeries(null)
                        DeviceManager.deviceList[1].pTrend.setTimeSeries(null)
                        DeviceManager.deviceList[1].pTrend.setPowerSeries(null)
                        DeviceManager.deviceList[0].pTrend.setFrontSeries(null)
                        DeviceManager.deviceList[0].pTrend.setBackSeries(null)
                        DeviceManager.deviceList[0].pTrend.setTimeSeries(null)
                        DeviceManager.deviceList[0].pTrend.setPowerSeries(null)
                        DeviceManager.deviceList[3].pTrend.setFrontSeries(null)
                        DeviceManager.deviceList[3].pTrend.setBackSeries(null)
                        DeviceManager.deviceList[3].pTrend.setTimeSeries(null)
                        DeviceManager.deviceList[3].pTrend.setPowerSeries(null)
                    }
                    else if(swipeCurrIndex === 3){
                        DeviceManager.deviceList[3].pTrend.setFrontSeries((chartView.series(lineSeries2.name)))
                        DeviceManager.deviceList[3].pTrend.setBackSeries((chartView.series(lineSeries3.name)))
                        DeviceManager.deviceList[3].pTrend.setTimeSeries((chartView.series(lineSeries1.name)))
                        DeviceManager.deviceList[3].pTrend.setPowerSeries((chartView.series(lineSeries.name)))

                        DeviceManager.deviceList[1].pTrend.setFrontSeries(null)
                        DeviceManager.deviceList[1].pTrend.setBackSeries(null)
                        DeviceManager.deviceList[1].pTrend.setTimeSeries(null)
                        DeviceManager.deviceList[1].pTrend.setPowerSeries(null)
                        DeviceManager.deviceList[2].pTrend.setFrontSeries(null)
                        DeviceManager.deviceList[2].pTrend.setBackSeries(null)
                        DeviceManager.deviceList[2].pTrend.setTimeSeries(null)
                        DeviceManager.deviceList[2].pTrend.setPowerSeries(null)
                        DeviceManager.deviceList[0].pTrend.setFrontSeries(null)
                        DeviceManager.deviceList[0].pTrend.setBackSeries(null)
                        DeviceManager.deviceList[0].pTrend.setTimeSeries(null)
                        DeviceManager.deviceList[0].pTrend.setPowerSeries(null)
                    }
                }
            }
        }
        onVisibleChanged: {
            if(visible){
                chartUpdata()
            }
        }
    }

}
