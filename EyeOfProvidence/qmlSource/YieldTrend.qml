import QtQuick              2.0
import QtQuick.Controls     2.5
import QtCharts             2.15
import Device               1.0
import TrendObj             1.0
import GlobalLanguageDefine 1.0
import GlobalSystemDefine   1.0
import GlobalStyle          1.0
import LanguageEnum         1.0
import YieldsTrendEnum      1.0

//良率趋势
Rectangle
{
    property int deviceIndex: 0
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
    property TrendObj objTrend: {
        if(deviceIndex < deviceCount)
            return DeviceManager.DeviceList[deviceIndex].TrendObj
        else
            return null
    }

    color: "#0c5596"
    radius: 3

    ListModel {
        id: yieldModel
        function resetYieldModel()
        {
            yieldModel.append({"modelType": YieldsTrendEnum.ONE_HOUR,
                              "modelName": "1" + GlobalLanguageDefine.strHour_Unit,
                              "checked": true})
            yieldModel.append({"modelType": YieldsTrendEnum.TWENTY_FOUR_HOURS,
                              "modelName": "24" + GlobalLanguageDefine.strHour_Unit,
                              "checked": false})
            yieldModel.append({"modelType": YieldsTrendEnum.SEVEN_DAYS,
                              "modelName": "7" + GlobalLanguageDefine.strDay_Unit,
                              "checked": false})
            yieldModel.append({"modelType": YieldsTrendEnum.THIRTY_DAYS,
                              "modelName": "30" + GlobalLanguageDefine.strDay_Unit,
                              "checked": false})
        }
    }

    // onVisibleChanged: {
    //     if(visible){
    //         enabled = true
    //     }
    //     else{
    //         enabled = false
    //     }
    // }

    // onDeviceIndexChanged:{
    //     chartUpdata()
    // }

    Connections{
        target: objTrend
        function onNotifyYieldTrendChanged()
        {
            chartUpdata()
        }
    }

    function chartUpdata()
    {
        if(objTrend !== null)
        {
            objTrend.setYieldSeries((chart.series(lineSeries.name)))
        }
    }

    Component.onCompleted: {
        yieldModel.resetYieldModel()
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
        anchors.top: parent.top
        anchors.topMargin: 12
        border.color: "#195f9f"
        border.width: 2
        radius: 4
        color:"#007dbc"
        ButtonGroup { id: buttonGroup }
        Row {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.topMargin: 2
            width: parent.width
            height: parent.height
            spacing: 2
            Repeater {
                model: yieldModel
                delegate: Button {
                    id: button
                    ButtonGroup.group: buttonGroup
                    checkable: true
                    autoExclusive: true
                    width: 79
                    height: 30
                    checked: model.checked
                    background: Rectangle{
                        id: button_Backgroud
                        color: {
                            if(button.checked === true)
                                return pRgb(177, 213, 219)
                            else
                                return "#007dbc"
                        }
                        border.color: {
                            if(button.checked === true)
                                return "#00488d"
                            else
                                return "#007dbc"
                        }

                        radius: 3
                    }
                    onPressed: {
                        objTrend.YieldType = model.modelType
                    }
                    contentItem: Text {
                        id: button_Text
                        anchors.centerIn: parent
                        text: model.modelName
                        font.pixelSize: 16
                        color: {
                            if(button.checked === true)
                                return "#00488d"
                            else
                                return "#b1d5db"
                        }
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.family: GlobalSystemDefine.fontNormal
                    }
                }
            }
        }
    }

    ChartView {
        id: chart
        anchors.top: line.bottom // 使图表的顶部与父项的顶部对齐
        anchors.left: parent.left
        anchors.leftMargin: -10
        anchors.right: parent.right
        anchors.rightMargin: -10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -5
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
    }
}

