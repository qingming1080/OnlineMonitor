import QtQuick              2.0
import QtCharts             2.15
import Device               1.0
import TrendObj             1.0
import GlobalLanguageDefine 1.0
import GlobalSystemDefine   1.0
import LanguageEnum         1.0
//import CustomChart 1.0
//焊接趋势
Rectangle {
    color: pRgb(43, 112, 173)
    property bool optionHeightEncoder: false
    property bool is2000XDevice: false
    property int currentIndex: DeviceManager.SelectedDeviceIndex
    property int deviceCount: DeviceManager.DeviceCounter;
    property int currentWelderId: DeviceManager.DeviceList[currentIndex].WelderID
    property Device objDevice: DeviceManager.DeviceList[currentIndex]
    onCurrentIndexChanged:{
        chartUpdate()
    }

    Connections{
        target: objDevice
        function onNotifyWeldTrendChanged(weldID)
        {
            if(weldID === currentWelderId)
            {
                chartUpdate()
            }
        }
    }

    function chartUpdate()
    {
        if(currentIndex < deviceCount)
        {
            DeviceManager.DeviceList[currentIndex].TrendObj.setPreheightSeries((chartView.series(lineSeriesPreheight.name)))
            DeviceManager.DeviceList[currentIndex].TrendObj.setPostHeightSeries((chartView.series(lineSeriesPostHeight.name)))
            DeviceManager.DeviceList[currentIndex].TrendObj.setWeldTimeSeries((chartView.series(lineSeriesWeldTime.name)))
            DeviceManager.DeviceList[currentIndex].TrendObj.setPeakPowerSeries((chartView.series(lineSeriesPeakPower.name)))
            DeviceManager.DeviceList[currentIndex].TrendObj.updateXYAxisRanges();
            DeviceManager.DeviceList[currentIndex].TrendObj.updateSeries();
        }
    }

    radius: 3
    Text {
        // text: qsTr("焊接趋势")
        text: GlobalLanguageDefine.strWeldingTrend
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 20 : 18
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

    ChartView {
        id: chartView
        // width: parent.width // 使图表的宽度等于父项的宽度
        // height: parent.height // 使图表的高度等于父项的高度
        anchors.top: parent.top // 使图表的顶部与父项的顶部对齐
        anchors.topMargin: -5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -5
        anchors.right: parent.right // 使图表的右侧与父项的右侧对齐
        anchors.rightMargin: -5
        anchors.left: parent.left
        anchors.leftMargin: -5
        antialiasing: true
        backgroundColor: "transparent"
        titleColor: "red"
        titleFont.family: GlobalSystemDefine.fontBold
        titleFont.pixelSize: 20
        margins.left: 0
        margins.right: 0
        margins.top: 0
        margins.bottom: 0
        legend {
            font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 16 : 10
            font.bold: true
            labelColor: "#a3c7d0"
            font.family: GlobalSystemDefine.fontBold
        }
        Component.onCompleted:
        {
            chartUpdate()
        }

        ValueAxis {
            id: cycleCount
            min: DeviceManager.DeviceList[currentIndex].TrendObj.CountMinX
            max: DeviceManager.DeviceList[currentIndex].TrendObj.CountMaxX
            tickCount: 5
            labelsColor: "#a3c7d0"
            labelsFont.pixelSize: 12
            labelsFont.bold: true
            labelFormat: "%d"
            gridVisible:false
        }
        ValueAxis{
            id: preHeight
            min: DeviceManager.DeviceList[currentIndex].TrendObj.PreheightMinY
            max: DeviceManager.DeviceList[currentIndex].TrendObj.PreheightMaxY
            tickCount: 5
            labelsColor: "#a3c7d0"
            labelsFont.pixelSize: 12
            labelsFont.bold: true
            labelFormat: "%.2f"
            gridVisible:false
            color:"#1398fa"
            visible: (currentIndex < 0) ? false : DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption
        }
        ValueAxis{
            id: postHeight
            min: DeviceManager.DeviceList[currentIndex].TrendObj.PostHeightMinY
            max: DeviceManager.DeviceList[currentIndex].TrendObj.PostHeightMaxY
            tickCount: 5
            labelsColor: "#a3c7d0"
            labelsFont.pixelSize: 12
            labelsFont.bold: true
            labelFormat: "%.2f"
            gridVisible: false
            color:"#B388FF"
            visible: (currentIndex < 0) ? false : DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption
        }
        ValueAxis{
            id: peakPower
            min: DeviceManager.DeviceList[currentIndex].TrendObj.PeakPowerMinY
            max: DeviceManager.DeviceList[currentIndex].TrendObj.PeakPowerMaxY
            tickCount: 5
            labelsColor: "#a3c7d0"
            labelsFont.pixelSize: 12
            labelsFont.bold: true
            labelFormat: "%d"
            gridVisible:false
            color:"#FFDF65"
        }
        ValueAxis{
            id: weldTime
            min: DeviceManager.DeviceList[currentIndex].TrendObj.WeldTimeMinY
            max: DeviceManager.DeviceList[currentIndex].TrendObj.WeldTimeMaxY
            tickCount: 5
            labelsColor: "#a3c7d0"
            labelsFont.pixelSize: 12
            labelsFont.bold: true
            labelFormat: "%.2f"
            gridVisible: false
            color:"#A0CF67"
        }
        LineSeries {
            id: lineSeriesPeakPower
            // name: "功率"
            name: GlobalLanguageDefine.strPower
            axisX: cycleCount
            axisY: peakPower
            color: "#FFDF65"
            width: 2

        }
        LineSeries {
            id: lineSeriesWeldTime
            // name: "时间"
            name: GlobalLanguageDefine.strTime
            axisX: cycleCount
            axisY: weldTime
            color: "#A0CF67"
            width: 2

        }
        LineSeries {
            id: lineSeriesPreheight
            // name: "焊前高度"
            name: (is2000XDevice === false) ? GlobalLanguageDefine.strPreWeldHeight : GlobalLanguageDefine.strCollapseDistance
            axisX: cycleCount
            axisY: preHeight
            color: "#1398fa"
            width: 2
            visible: (currentIndex < 0) ? false : DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption

        }
        LineSeries {
            id: lineSeriesPostHeight
            // name: "焊后高度"
            name: (is2000XDevice === false) ? GlobalLanguageDefine.strPostWeldHeight : GlobalLanguageDefine.strAbsoluteDistance
            axisX: cycleCount
            axisY: postHeight
            color: "#B388FF"
            width: 2
            visible: (currentIndex < 0) ? false : DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption
        }

        onVisibleChanged: {
            if(visible)
            {
                chartUpdate()
            }
        }
    }
}
