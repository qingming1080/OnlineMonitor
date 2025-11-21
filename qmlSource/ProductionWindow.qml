import QtQuick 2.15
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15
import Device 1.0

import QmlEnum 1.0
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
        // if(viewName === 3){
        //     switchingEquipment = true
        // }
        // else{
        //     switchingEquipment = false
        // }

        // prostack.pop()
        // if (proViews[viewName]) {
        //     // 如果视图已缓存，直接显示
        //     prostack.push(proViews[viewName]);
        // } else {
        //     // 创建视图并缓存
        //     var newItem = component.createObject(prostack);
        //     proViews[viewName] = newItem;
        //     prostack.push(newItem);
        // }
        prostack.clear();
        var newItem = component.createObject(prostack);
        proViews[viewName] = newItem;
        prostack.push(newItem);
        if( viewName === 2 || viewName === 3)
        {
            ModbusClient.setPilotLedStatus(true)
            ModbusClient.setLearnLedStatus(false)
        }
        else
        {
            ModbusClient.setPilotLedStatus(false)
            ModbusClient.setLearnLedStatus(true)
        }
    }
    onDeviceCountChanged: {
        var isLearning = false;
        for(var i = 0; i < deviceCount; i++)
        {
            if(DeviceManager.DeviceList[i].ProductionObj.ModelStatus === false)
            {
                DeviceManager.SelectedDeviceIndex = i;
                loadViewpro(1, autoLearning)
                isLearning = true;
            }
        }
        if(isLearning === false)
        {
            if(DeviceManager.DeviceCounter > 1)
            {
                loadViewpro(2, multiPro)
            }
            else
                loadViewpro(3, singlePro)
        }
    }

    Connections{
        target: objDevice
        function onNotifyPresetChanged(welderID)
        {
            var learningScreen = QmlEnum.AUTO_LEARNING_SCREEEN
            var objItem = prostack.find(function(item) {
                return (item.qmlscreenIndicator === learningScreen)})
            if(objItem === null)
            {
                for(var i = 0; i < deviceCount; i++)
                {
                    if(DeviceManager.DeviceList[i].WelderID === welderID)
                    {
                        DeviceManager.SelectedDeviceIndex = i;
                        loadViewpro(1, autoLearning)
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        if(DeviceManager.DeviceList[0].ProductionObj.ModelStatus === false)
            loadViewpro(1, autoLearning)
        else if(DeviceManager.DeviceCounter > 1)
        {
            loadViewpro(2, multiPro)
        }
        else
            loadViewpro(3, singlePro)
    }

    StackView{
        id: prostack
    }

    Component{
        id: multiPro
        ProductionMultiModule{
            id: mupMode
            width: 1280
            height: 740
        }
    }

    Component{
        id: singlePro
        ProductionSingleModule{
            id: mupMode
            width: 1280
            height: 740
        }
    }

    Component{
        id: autoLearning
        ProductionLearnModule{
            id: mupMode
            width: 1280
            height: 740
        }

    }

}
