import QtQuick 2.0
import QtQuick.Controls 2.5
import QtCharts 2.15
import Device 1.0
import TrendObj 1.0
import GlobalLanguageDefine 1.0
import GlobalSystemDefine 1.0
import LanguageEnum 1.0
//import CustomTimeChart 1.0

//良率趋势
Rectangle
{
    property bool isSingleDevice: false
    property int deviceIndex: DeviceManager.SelectedDeviceIndex
    property int deviceCount: DeviceManager.DeviceCounter
    property var startTime: {
        if(deviceIndex < deviceCount)
            return Date.fromLocaleString(Qt.locale(), DeviceManager.DeviceList[deviceIndex].TrendObj.StartTime, "yyyy-MM-dd hh:mm:ss")
        else
            return ""
    }
    property var endTime: {
        if(deviceIndex < deviceCount)
            return Date.fromLocaleString(Qt.locale(), DeviceManager.DeviceList[deviceIndex].TrendObj.EndTime, "yyyy-MM-dd hh:mm:ss")
        else
            return ""
    }
    property TrendObj objTrend: DeviceManager.DeviceList[currentIndex].TrendObj

    color: pRgb(43, 112, 173)
    radius: 3
    onVisibleChanged: {
        if(visible){
            enabled = true
            updateBtn()
        }
        else{
            enabled = false
        }
    }

    onDeviceIndexChanged:{
        updateBtn()
        chartUpdata()
    }

    Connections{
        target: objTrend
        function onNotifyYieldTrendChanged()
        {
            chartUpdata()
        }
    }

    function updateBtn()
    {
        if(isSingleDevice)
        {
            if(DeviceManager.DeviceList[deviceIndex].TrendObj.YieldType === 0)
            {
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
            }
            else if(DeviceManager.DeviceList[deviceIndex].TrendObj.YieldType === 1)
            {
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
            }
            else if(DeviceManager.DeviceList[deviceIndex].TrendObj.YieldType === 2)
            {
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
            }
            else if(DeviceManager.DeviceList[deviceIndex].TrendObj.YieldType === 3)
            {
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
            }
        }
        else{
            if(deviceCount === 4)
            {
                return
            }
            else if(deviceCount === 1 || deviceCount === 3)
            {
                if(DeviceManager.DeviceList[0].TrendObj.YieldType === 0)
                {
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
                }
                else if(DeviceManager.DeviceList[0].TrendObj.YieldType === 1)
                {
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
                }
                else if(DeviceManager.DeviceList[0].TrendObj.YieldType === 2)
                {
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
                }
                else if(DeviceManager.DeviceList[0].TrendObj.YieldType === 3)
                {
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
                }
            }
            else if(deviceCount === 2)
            {
                if(deviceIndex === 0)
                {
                    if(DeviceManager.DeviceList[0].TrendObj.YieldType === 0)
                    {
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
                    }
                    else if(DeviceManager.DeviceList[0].TrendObj.YieldType === 1)
                    {
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
                    }
                    else if(DeviceManager.DeviceList[0].TrendObj.YieldType === 2)
                    {
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
                    }
                    else if(DeviceManager.DeviceList[0].TrendObj.YieldType === 3)
                    {
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
                    }
                }
                else if(deviceIndex === 1)
                {
                    if(DeviceManager.DeviceList[1].TrendObj.YieldType === 0)
                    {
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
                    }
                    else if(DeviceManager.DeviceList[1].TrendObj.YieldType === 1)
                    {
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
                    }
                    else if(DeviceManager.DeviceList[1].TrendObj.YieldType === 2)
                    {
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
                    }
                    else if(DeviceManager.DeviceList[1].TrendObj.YieldType === 3)
                    {
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
                    }
                }
            }
        }
    }

    function switchUpdate(index)
    {
        if(isSingleDevice)
        {
            DeviceManager.DeviceList[deviceIndex].TrendObj.YieldType = index
        }
        else
        {
            if(deviceCount === 1 || deviceCount === 3)
            {
                DeviceManager.DeviceList[0].TrendObj.YieldType = index
            }
            else if(deviceCount === 2)
            {
                if(deviceIndex === 0)
                {
                    DeviceManager.DeviceList[0].TrendObj.YieldType = index
                }
                else if(deviceIndex === 1)
                {
                    DeviceManager.DeviceList[1].TrendObj.YieldType = index
                }
            }
        }
    }

    function chartUpdata()
    {
        if(deviceCount === 1)
        {
            DeviceManager.DeviceList[0].TrendObj.setYieldSeries((chart.series(lineSeries.name)))
            return
        }

        if(isSingleDevice)
        {
            if(deviceCount === 2)
            {
                if(currentIndex === 0)
                {
                    DeviceManager.DeviceList[0].TrendObj.setYieldSeries((chart.series(lineSeries.name)))
                    DeviceManager.DeviceList[1].TrendObj.setYieldSeries(null)
                }
                else if(currentIndex === 1)
                {
                    DeviceManager.DeviceList[1].TrendObj.setYieldSeries((chart.series(lineSeries.name)))
                    DeviceManager.DeviceList[0].TrendObj.setYieldSeries(null)
                }

            }
            else if(deviceCount === 3)
            {
                if(deviceIndex === 0)
                {
                    DeviceManager.DeviceList[0].TrendObj.setYieldSeries((chart.series(lineSeries.name)))
                    DeviceManager.DeviceList[1].TrendObj.setYieldSeries(null)
                    DeviceManager.DeviceList[2].TrendObj.setYieldSeries(null)
                }
                else if(deviceIndex === 1)
                {
                    DeviceManager.DeviceList[1].TrendObj.setYieldSeries((chart.series(lineSeries.name)))
                    DeviceManager.DeviceList[0].TrendObj.setYieldSeries(null)
                    DeviceManager.DeviceList[2].TrendObj.setYieldSeries(null)
                }
                else if(deviceIndex === 2)
                {
                    DeviceManager.DeviceList[2].TrendObj.setYieldSeries((chart.series(lineSeries.name)))
                    DeviceManager.DeviceList[0].TrendObj.setYieldSeries(null)
                    DeviceManager.DeviceList[1].TrendObj.setYieldSeries(null)
                }
            }
            else if(deviceCount === 4)
            {
                if(deviceIndex === 0)
                {
                    DeviceManager.DeviceList[0].TrendObj.setYieldSeries((chart.series(lineSeries.name)))
                    DeviceManager.DeviceList[1].TrendObj.setYieldSeries(null)
                    DeviceManager.DeviceList[2].TrendObj.setYieldSeries(null)
                    DeviceManager.DeviceList[3].TrendObj.setYieldSeries(null)
                }
                else if(deviceIndex === 1)
                {
                    DeviceManager.DeviceList[1].TrendObj.setYieldSeries((chart.series(lineSeries.name)))
                    DeviceManager.DeviceList[0].TrendObj.setYieldSeries(null)
                    DeviceManager.DeviceList[2].TrendObj.setYieldSeries(null)
                    DeviceManager.DeviceList[3].TrendObj.setYieldSeries(null)
                }
                else if(deviceIndex === 2)
                {
                    DeviceManager.DeviceList[2].TrendObj.setYieldSeries((chart.series(lineSeries.name)))
                    DeviceManager.DeviceList[0].TrendObj.setYieldSeries(null)
                    DeviceManager.DeviceList[1].TrendObj.setYieldSeries(null)
                    DeviceManager.DeviceList[3].TrendObj.setYieldSeries(null)
                }
                else if(deviceIndex === 3)
                {
                    DeviceManager.DeviceList[3].TrendObj.setYieldSeries((chart.series(lineSeries.name)))
                    DeviceManager.DeviceList[0].TrendObj.setYieldSeries(null)
                    DeviceManager.DeviceList[1].TrendObj.setYieldSeries(null)
                    DeviceManager.DeviceList[2].TrendObj.setYieldSeries(null)
                }
            }
        }
        else{
            if(deviceCount === 2)
            {
                if(deviceIndex === 1)
                {
                    DeviceManager.DeviceList[0].TrendObj.setYieldSeries((chart.series(lineSeries.name)))
                }
                else if(deviceIndex === 2)
                {
                    DeviceManager.DeviceList[1].TrendObj.setYieldSeries((chart.series(lineSeries.name)))
                }
            }
            else if(deviceCount === 3)
            {
                if(deviceIndex === 1)
                {
                    DeviceManager.DeviceList[0].TrendObj.setYieldSeries((chart.series(lineSeries.name)))
                }
                DeviceManager.DeviceList[1].TrendObj.setYieldSeries(null)
                DeviceManager.DeviceList[2].TrendObj.setYieldSeries(null)
            }
            else if(deviceCount === 4)
            {
                DeviceManager.DeviceList[0].TrendObj.setYieldSeries(null)
                DeviceManager.DeviceList[1].TrendObj.setYieldSeries(null)
                DeviceManager.DeviceList[1].TrendObj.setYieldSeries(null)
                DeviceManager.DeviceList[3].TrendObj.setYieldSeries(null)
            }
        }
    }


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

    Component.onCompleted: {
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
    }

    Text {
        // text: qsTr("良率趋势")
        text: GlobalLanguageDefine.strYieldTrend
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 20 : 18
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
        anchors.right: parent.right//269
        anchors.rightMargin: 20
        y: 12
        border.color: "#195f9f"
        border.width: 2
        radius: 4
        color:"#007dbc"
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
            onPressed: {
                switchUpdate(0)
                updateBtn()
            }
            contentItem: Text {
                id:t1
                anchors.centerIn: parent
                // text: "1" + qsTr("小时")
                text: "1" + GlobalLanguageDefine.strHour_Unit
                font.pixelSize: 16
                color: pRgb(153, 204, 255)
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: GlobalSystemDefine.fontNormal
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
            onPressed: {
                switchUpdate(1)
                updateBtn()
            }
            contentItem: Text {
                id:t2
                anchors.centerIn: parent
                // text: "24" + qsTr("小时")
                text: "24" + GlobalLanguageDefine.strHour_Unit
                font.pixelSize: 16
                color: pRgb(153, 204, 255)
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: GlobalSystemDefine.fontNormal
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
            onPressed: {
                switchUpdate(2)
                updateBtn()
            }
            contentItem: Text {
                id:t3
                anchors.centerIn: parent
                // text: "7" + qsTr("天")
                text: "7" + GlobalLanguageDefine.strDay_Unit
                font.pixelSize: 16
                color: pRgb(153, 204, 255)
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: GlobalSystemDefine.fontNormal
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
            onPressed: {
                switchUpdate(3)
                updateBtn()
            }
            contentItem: Text {
                id:t4
                anchors.centerIn: parent
                // text: "30" + qsTr("天")
                text: "30" + GlobalLanguageDefine.strDay_Unit
                font.pixelSize: 16
                color: pRgb(153, 204, 255)
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: GlobalSystemDefine.fontNormal
            }
        }
    }

    property int timer: 0

    ChartView {
        id: chart
        anchors.top: line.bottom // 使图表的顶部与父项的顶部对齐
        anchors.left: parent.left
        anchors.leftMargin: -10
        width: 585
        height: 240
        antialiasing: true
        backgroundColor: "transparent"
        titleColor: "red"
        titleFont.family: GlobalSystemDefine.fontBold
        titleFont.pixelSize: 20
        margins.left: 0
        margins.right: 10
        margins.top: 0
        margins.bottom: 0
        legend.visible: false
        clip: true

        Component.onCompleted: {
            chartUpdata()
        }
        Component.onDestruction: {
            // DeviceManager.DeviceList[0].pTrend.setYieldSeries(null)
            // DeviceManager.DeviceList[1].pTrend.setYieldSeries(null)
            // DeviceManager.DeviceList[2].pTrend.setYieldSeries(null)
            // DeviceManager.DeviceList[3].pTrend.setYieldSeries(null)
        }

        DateTimeAxis {
            id: myAxisX
            format: "MM-dd hh:mm" // 时间格式
            tickCount: 3
            min: startTime
            max: endTime
            labelsColor: "#a3c7d0"
            labelsFont.pixelSize: 12
            labelsFont.bold: true
            gridVisible: false
        }
        ValueAxis{
            id: myAxisY
            min: 0
            max: 100
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
            axisY: myAxisY
            color: "#1398fa"
            width: 1
            useOpenGL: false
            pointsVisible: true
        }

        // onVisibleChanged: {
        //     if(visible){
        //         chartUpdata()
        //     }
        // }
    }
}

