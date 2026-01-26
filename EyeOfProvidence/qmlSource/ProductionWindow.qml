import QtQuick              2.15
import QtQuick.Controls     1.4
import QtQuick.Controls     2.15
import Device               1.0

import QmlEnum              1.0
import GlobalLanguageDefine 1.0
import GlobalSystemDefine   1.0
import GlobalMessageDefine  1.0
import DeviceInfoEnum       1.0
import DeviceObj            1.0
import ProductionObj        1.0

Rectangle {
    id:mpro
    color: pRgb(153, 204, 255)
    property bool tableFlag: false
    property var proViews: []
    property int rect1: 1
    property int rect2: 1

    property int currentIndex: DeviceManager.SelectedDeviceIndex
    property int deviceCount: DeviceManager.DeviceCounter
    property Device objDevice: DeviceManager.DeviceList[currentIndex]
    signal sigBtnSynchronization(var index,var time)

    onRect1Changed: {
        sigBtnSynchronization(1,rect1)
    }
    onRect2Changed: {
        sigBtnSynchronization(2,rect2)
    }

    function loadViewpro(viewName, component)
    {
        componentLoader.source = ""
        switch(viewName)
        {
        case 1:
            componentLoader.source = "qrc:/qmlSource/ProductionLearnModule.qml";
            break;
        case 2:
            componentLoader.source = "qrc:/qmlSource/ProductionMultiModule.qml"
            break;
        case 3:
            componentLoader.source = "qrc:/qmlSource/ProductionSingleModule.qml"
            break;
        default:
            componentLoader.source = "qrc:/qmlSource/ProductionLearnModule.qml";
            break;
        }

        if( viewName === 2 || viewName === 3)
        {
            ModbusClient.setPilotLedStatus(true)
            ModbusClient.setLearnLedStatus(false)
        }
        else
        {
            DeviceManager.DeviceList[currentIndex].ProductionObj.ModelStatus = false
            ModbusClient.setPilotLedStatus(false)
            ModbusClient.setLearnLedStatus(true)
        }
    }

    function stillNeedToLearning()
    {
        var isLearning = false;
        for(var i = 0; i < deviceCount; i++)
        {
            if(DeviceManager.DeviceList[i].ProductionObj.ModelStatus === false)
            {
                DeviceManager.SelectedDeviceIndex = i;
                isLearning = true;
                break;
            }
        }
        return isLearning;
    }

    onDeviceCountChanged:
    {
        if(stillNeedToLearning() === false)
        {
            if(DeviceManager.DeviceCounter > 1)
            {
                // loadViewpro(2, multiPro)
                loadViewpro(2, null)
            }
            else
                // loadViewpro(3, singlePro)
                loadViewpro(3, null)

        }
        else
        {
            // loadViewpro(1, autoLearning)
            loadViewpro(1, null)
        }
    }

    Connections{
        target: objDevice
        function onNotifyPresetChanged(welderID)
        {
            var learningScreen = QmlEnum.AUTO_LEARNING_SCREEEN
            // var objItem = prostack.find(function(item) {
            //     return (item.qmlscreenIndicator === learningScreen)})
            var isCurrentLearningPage = componentLoader.item && componentLoader.item.qmlscreenIndicator === learningScreen
            if(!isCurrentLearningPage)
            {
                for(var i = 0; i < deviceCount; i++)
                {
                    if(DeviceManager.DeviceList[i].WelderID === welderID)
                    {
                        DeviceManager.SelectedDeviceIndex = i;
                        loadViewpro(1, null)
                    }
                }
            }
        }
    }

    Loader{
        id: componentLoader
        anchors.left: parent.left
        anchors.top: parent.top
        width: 1280
        height: 700
    }

}
