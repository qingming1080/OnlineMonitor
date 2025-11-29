import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15
import QtQml.Models 2.15
import GlobalLanguageDefine 1.0
import GlobalSystemDefine 1.0
import GlobalMessageDefine 1.0
import QmlEnum 1.0

Rectangle {
    readonly property int qmlscreenIndicator: QmlEnum.SINGLE_PRODUCTION_SCREEN
    property int currentIndex: DeviceManager.SelectedDeviceIndex
    property int deviceCount: DeviceManager.DeviceCounter
    property bool heightOption: (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption : false
    color: pRgb(153, 204, 255)

    Connections{
        target: window
        function onSigNewModel(){
            loadViewpro(1, autoLearning)
        }
    }

    Rectangle {
        id: singleProduction
        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.top: parent.top
        anchors.topMargin: 29
        width: 1220
        height: 664
        color: pRgb(43, 112, 173)
        radius: 5

        EquipmentInfor{
            id: layoutDeviceInfo
            x: 42
            y: 35
            width:  258
            //TODO Need to have a double check
            height: 255
            color: "#0c5696"
            deviceName:{
                if(currentIndex < deviceCount)
                    return DeviceManager.DeviceList[currentIndex].DeviceObj.WelderName
                else
                    return ""
            }
            deviceType:{
                if(currentIndex < deviceCount)
                    return DeviceManager.DeviceList[currentIndex].DeviceObj.WelderType === 0 ? "L20-VG" : "L20-TS"
                    return ""
            }
            connectionType:{
                if(currentIndex < deviceCount)
                    return DeviceManager.DeviceList[currentIndex].DeviceObj.ConnectType === 1 ? "RS232" : "TCP/IP"
                else
                    return ""
            }
            devcieStatus:{
                if(currentIndex < deviceCount)
                {
                    var connectState = DeviceManager.DeviceList[currentIndex].DeviceObj.ConnectState
                    return GlobalMessageDefine.getConnectState(connectState)
                }
                else
                {
                    return ""
                }
            }
        }

        WeldingResult{
            id: layoutWeldResult
            width: 258
            height: 246
            x:42
            y:314
            color: "#0c5696"
            heightOption:       (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].DeviceObj.HeightEncoderOption : false
            energy:             (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ProductionObj.Energy : 0
            amplitude:          (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ProductionObj.Amplitude : 0
            weldPressure:       (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ProductionObj.WeldPressure : 0
            triggerPressure:    (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ProductionObj.TriggertPressure : 0
            peakPower:          (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ProductionObj.PeakPower : 0
            weldTime:           (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ProductionObj.WeldTime : 0
            preheight:          (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ProductionObj.Preheight : 0
            postHeight:         (currentIndex < deviceCount) ? DeviceManager.DeviceList[currentIndex].ProductionObj.PostHeight : 0
        }

        Item {
            x:0
            RealtimeYield{
                id:s2
                width:  300
                height:  255
                x: 329
                y: 35
                color:  "#0c5696"
                revealing:{
                    if(currentIndex < deviceCount)
                        return DeviceManager.DeviceList[currentIndex].DeviceObj.SuspiciousOption
                    else
                        return true
                }
                eqText1:{
                    if(currentIndex < deviceCount)
                        return DeviceManager.DeviceList[currentIndex].ProductionObj.GoodCycleCount
                    else
                        return ""
                }
                eqText2:{
                    if(currentIndex < deviceCount)
                        return DeviceManager.DeviceList[currentIndex].ProductionObj.SuspectCycleCount
                    else
                        return ""
                }
                eqText3:{
                    if(currentIndex < deviceCount)
                        return DeviceManager.DeviceList[currentIndex].ProductionObj.DefectiveCycleCount
                    else
                        return ""
                }
                eqText4:{
                    if(currentIndex < deviceCount)
                        return DeviceManager.DeviceList[currentIndex].ProductionObj.TotalCycleCount
                    else
                        return ""
                }
                eqText5:{
                    if(currentIndex < deviceCount)
                        return DeviceManager.DeviceList[currentIndex].ProductionObj.GoodRate
                    else
                        return ""
                }
            }
            YieldTrend{
                id: s6
                width:  514
                height:  255
                x: 658
                y: 35
                color:  "#0c5696"
                deviceIndex: currentIndex
                isSingleDevice: true
            }
            WeldingTrend{
                id:s7
                width:  502
                height:  311
                x: 329
                y: 314
                color:  "#0c5696"
            }
            AbnormalMessage{
                id:s8
                width:  313
                height:  311
                x: 858
                y: 314
                color:  "#0c5696"
            }
        }

        Button{
            id:s4
            x: 42
            y: 580
            width:   258
            height:  45
            background: Rectangle{
                radius: 6
                color:  "#0c5696"
            }
            contentItem: Text {
                id: mt1
                text: GlobalLanguageDefine.strNewModel // return qsTr("新建模型")
                font.pixelSize:  17
                color: pRgb(153, 204, 255)
                anchors.centerIn: parent  // 确保文本在按钮内居中对齐
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: GlobalSystemDefine.fontBold
            }
            onPressed: {
                console.debug("Welder ID: ", currentIndex)
                popup.openPop(2)
            }
        }
    }

    Button{
        x:1206
        y:34
        width: 40
        height: 40
        background: Rectangle{
            color: "transparent"
            Image {
                anchors.centerIn: parent
                source: "qrc:/images/btn_fullscreen_exit.png"
            }
        }
        onPressed: {
            if(deviceCount === 3)
                currentIndex = 0
            s6.isSingleDevice = false
            loadViewpro(2, multiPro)
        }
        visible: (DeviceManager.DeviceCounter > 1) ? true : false
    }
}
