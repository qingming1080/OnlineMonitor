import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15
import Device 1.0

import GlobalLanguageDefine 1.0
import GlobalMessageDefine  1.0
import DeviceInfoEnum       1.0
import DeviceObj            1.0
import ProductionObj        1.0

//多设备生产界面
Rectangle {
    color: pRgb(153, 204, 255)
    property int currentIndex: DeviceManager.SelectedDeviceIndex
    property int deviceCount: DeviceManager.DeviceCounter

    Connections{
        target: mpro
        function onSigBtnSynchronization(index,time){
            if(index === 1){
                s5.btnIndex = time
            }
            else if(index === 2){
                s6.btnIndex = time
            }
        }
    }
    function swichCount(){
        if(deviceCount == 2)
        {
            r1.height = 581
            r2.height = 581
            r3.visible = false
            r4.visible = false
            s1.x = 28
            s1.y = 42
            s2.x = 284
            s2.y = 42
            s3.x = 28
            s3.y = 42
            s4.x = 284
            s4.y = 42

            s1.width = 243
            s1.height = 237
            s2.width = 289
            s2.height = 238
            s3.width = 243
            s3.height = 237
            s4.width = 289
            s4.height = 238
        }
        else if(deviceCount == 3)
        {
            r1.height = 581
            r2.height = 287
            r3.visible = false
            r4.visible = true
            s1.x = 28
            s1.y = 42
            s2.x = 284
            s2.y = 42
            s3.x = 35
            s3.y = 36
            s4.x = 280
            s4.y = 36

            s1.width = 243
            s1.height = 237
            s2.width = 289
            s2.height = 238
            s3.width = 233
            s3.height = 227
            s4.width = 277
            s4.height = 228
        }
        else if(deviceCount == 4)
        {
            r1.height = 287
            r2.height = 287
            r3.visible = true
            r4.visible = true

            s1.x = 35
            s1.y = 36
            s2.x = 280
            s2.y = 36
            s3.x = 35
            s3.y = 36
            s4.x = 280
            s4.y = 36

            s1.width = 233
            s1.height = 227
            s2.width = 277
            s2.height = 228
            s3.width = 233
            s3.height = 227
            s4.width = 277
            s4.height = 228
        }
    }

    onDeviceCountChanged: {
        swichCount()
    }

    Rectangle{
        id:r1
        x:28
        y:44
        width: 600
        height: 581
        radius: 5
        color: pRgb(43, 112, 173)
        onHeightChanged: {
            if(height>290){
                s5.visible = true
            }
            else{
                s5.visible = false
            }
        }

        EquipmentInfor{
            id:s1
            x:28
            y:42
            width: 243
            height: 237
            radius: 3
            color: "#0c5596"
            deviceName:{
                if(DeviceManager.DeviceList[0]){
                    return DeviceManager.DeviceList[0].DeviceObj.WelderName
                }
                else{
                    return ""
                }
            }
            deviceType:{
                if(DeviceManager.DeviceList[0]){
                    return DeviceManager.DeviceList[0].DeviceObj.WelderType === 0 ? "L20-VG" : "L20-TS"
                }
                else{
                    return ""
                }
            }
            connectionType:{
                if(DeviceManager.DeviceList[0]){
                    return DeviceManager.DeviceList[0].DeviceObj.ConnectType === 1 ? "RS232" : "TCP/IP"
                }
                else{
                    return ""
                }
            }
            devcieStatus:{
                if(DeviceManager.DeviceList[0])
                {
                    var connectState = DeviceManager.DeviceList[0].DeviceObj.ConnectState
                    return GlobalMessageDefine.getConnectState(connectState)
                }
                else
                    return ""

            }
        }
        RealtimeYield{
            id:s2
            width: 289
            height: 238
            x:284
            y:42
            radius: 3
            color: "#0c5596"
            revealing:{
                if(DeviceManager.DeviceList[0]){
                    return DeviceManager.DeviceList[0].DeviceObj.SuspiciousOption
                }
                else{
                    return true
                }
            }
            eqText1:{
                if(DeviceManager.DeviceList[0]){
                    return DeviceManager.DeviceList[0].ProductionObj.GoodCycleCount
                }
                else{
                    return ""
                }
            }
            eqText2:{
                if(DeviceManager.DeviceList[0]){
                    return DeviceManager.DeviceList[0].ProductionObj.SuspectCycleCount
                }
                else{
                    return ""
                }
            }
            eqText3:{
                if(DeviceManager.DeviceList[0]){
                    return DeviceManager.DeviceList[0].ProductionObj.DefectiveCycleCount
                }
                else{
                    return ""
                }
            }
            eqText4:{
                if(DeviceManager.DeviceList[0]){
                    return DeviceManager.DeviceList[0].ProductionObj.GoodCycleCount
                            + DeviceManager.DeviceList[0].ProductionObj.SuspectCycleCount
                            +DeviceManager.DeviceList[0].ProductionObj.DefectiveCycleCount
                }
                else{
                    return ""
                }
            }
            eqText5:{
                if(DeviceManager.DeviceList[0]){
                    return DeviceManager.DeviceList[0].ProductionObj.GoodRate
                }
                else{
                    return ""
                }
            }
        }
        YieldTrend{
            id:s5
            width: 545
            height: 254
            x:28
            y:298
            radius: 3
            color: "#0c5596"
            equiInforIndex:1
        }
        Button{
            width: 30
            height: 30
            x:566
            y:6
            background: Rectangle{
                color: "transparent"
                Image {
                    anchors.fill: parent
                    source: "qrc:/images/btn_fullscreen_enter.png"
                }
            }
            onPressed: {
                swipevis = true
                DeviceManager.SelectedDeviceIndex = 0;
                loadViewpro(3, singlePro)
                sigUpdateUI(0)
            }
        }
    }
    Rectangle{
        id:r2
        x:654
        y:44
        width: 600
        height: 581
        radius: 5
        color: pRgb(43, 112, 173)
        onHeightChanged: {
            if(height > 290){
                s6.visible = true
            }
            else{
                s6.visible = false
            }
        }
        EquipmentInfor{
            id:s3
            x:28
            y:42
            width: 243
            height: 237
            radius: 3
            color: "#0c5596"
            deviceName:{
                if(DeviceManager.DeviceList[1])
                {
                    return DeviceManager.DeviceList[1].DeviceObj.WelderName
                }
                else
                {
                    return ""
                }
            }
            deviceType:{
                if(DeviceManager.DeviceList[1])
                {
                    return DeviceManager.DeviceList[1].DeviceObj.WelderType === 0 ? "L20-VG" : "L20-TS"
                }
                else
                {
                    return ""
                }
            }
            connectionType:{
                if(DeviceManager.DeviceList[1]){
                    return DeviceManager.DeviceList[1].DeviceObj.ConnectType === 1 ? "RS232" : "TCP/IP"

                }
                else{
                    return ""
                }
            }
            devcieStatus:{
                if(DeviceManager.DeviceList[1])
                {
                    var connectState = DeviceManager.DeviceList[1].DeviceObj.ConnectState
                    return GlobalMessageDefine.getConnectState(connectState)
                }
                else
                    return ""
            }
        }
        RealtimeYield{
            id:s4
            width: 289
            height: 238
            x:284
            y:42
            radius: 3
            color: "#0c5596"
            revealing:{
                if(DeviceManager.DeviceList[1]){
                    return DeviceManager.DeviceList[1].DeviceObj.SuspiciousOption
                }
                else{
                    return true
                }
            }
            eqText1:{
                if(DeviceManager.DeviceList[1]){
                    return DeviceManager.DeviceList[1].ProductionObj.GoodCycleCount
                }
                else{
                    return ""
                }
            }
            eqText2:{
                if(DeviceManager.DeviceList[1]){
                    return DeviceManager.DeviceList[1].ProductionObj.SuspectCycleCount
                }
                else{
                    return ""
                }
            }
            eqText3:{
                if(DeviceManager.DeviceList[1]){
                    return DeviceManager.DeviceList[1].ProductionObj.DefectiveCycleCount
                }
                else{
                    return ""
                }
            }
            eqText4:{
                if(DeviceManager.DeviceList[1]){
                    return DeviceManager.DeviceList[1].ProductionObj.GoodCycleCount
                            + DeviceManager.DeviceList[1].ProductionObj.SuspectCycleCount
                            +DeviceManager.DeviceList[1].ProductionObj.DefectiveCycleCount
                }
                else{
                    return ""
                }
            }
            eqText5:{
                if(DeviceManager.DeviceList[1]){
                    return DeviceManager.DeviceList[1].ProductionObj.GoodRate
                }
                else{
                    return ""
                }
            }
        }
        YieldTrend{
            id:s6
            width: 545
            height: 254
            x:28
            y:298
            radius: 3
            color: "#0c5596"
            equiInforIndex:2
        }
        Button{
            width: 30
            height: 30
            x:566
            y:6
            background: Rectangle{
                color: "transparent"
                Image {
                    anchors.fill: parent
                    source: "qrc:/images/btn_fullscreen_enter.png"
                }
            }
            onPressed: {
                swipevis = true
                DeviceManager.SelectedDeviceIndex = 1
                loadViewpro(3, singlePro)
                sigUpdateUI(1)
            }
        }
    }
    Rectangle{
        id:r3
        x:28
        y:338
        width: 600
        height: 287
        radius: 5
        color: pRgb(43, 112, 173)
        onVisibleChanged: {
            if(visible){
                enabled = true
            }
            else{
                enabled = false
            }
        }

        EquipmentInfor{
            id:s7
            x:35
            y:36
            width: 233
            height: 227
            radius: 3
            color: "#0c5596"
            deviceName:{
                if(DeviceManager.DeviceList[2]){
                    return DeviceManager.DeviceList[2].DeviceObj.WelderName
                }
                else if(DeviceManager.DeviceList[3]){
                    return DeviceManager.DeviceList[3].DeviceObj.WelderName
                }
                else{
                    return ""
                }
            }
            deviceType:{
                if(DeviceManager.DeviceList[2]){
                    return DeviceManager.DeviceList[2].DeviceObj.WelderType === 0 ? "L20-VG" : "L20-TS"
                }
                else if(DeviceManager.DeviceList[3]){
                    return DeviceManager.DeviceList[3].DeviceObj.WelderType === 0 ? "L20-VG" : "L20-TS"
                }
                else{
                    return ""
                }
            }
            connectionType:{
                if(DeviceManager.DeviceList[2]){
                    return DeviceManager.DeviceList[2].DeviceObj.ConnectType === 1 ? "RS232" : "TCP/IP"

                }
                else if(DeviceManager.DeviceList[3]){
                    return DeviceManager.DeviceList[3].DeviceObj.ConnectType === 1 ? "RS232" : "TCP/IP"

                }
                else{
                    return ""
                }
            }
            devcieStatus:{
                var connectState = 0
                if(DeviceManager.DeviceList[2])
                {
                    connectState = DeviceManager.DeviceList[2].DeviceObj.ConnectState
                    return GlobalMessageDefine.getConnectState(connectState)
                }
                else if(DeviceManager.DeviceList[3])
                {
                    connectState = DeviceManager.DeviceList[3].DeviceObj.ConnectState
                    return GlobalMessageDefine.getConnectState(connectState)
                }
                else
                {
                    return ""
                }
            }
        }
        RealtimeYield{
            id:s8
            width: 277
            height: 228
            x:280
            y:35
            radius: 3
            color: "#0c5596"
            revealing:{
                if(DeviceManager.DeviceList[2]){
                    return DeviceManager.DeviceList[2].DeviceObj.SuspiciousOption
                }
                else if(DeviceManager.DeviceList[3]){
                    return DeviceManager.DeviceList[3].DeviceObj.SuspiciousOption
                }
                else{
                    return true
                }
            }
            eqText1:{
                if(DeviceManager.DeviceList[2]){
                    return DeviceManager.DeviceList[2].ProductionObj.GoodCycleCount
                }
                else if(DeviceManager.DeviceList[3]){
                    return DeviceManager.DeviceList[3].ProductionObj.GoodCycleCount
                }
                else{
                    return ""
                }
            }
            eqText2:{
                if(DeviceManager.DeviceList[2]){
                    return DeviceManager.DeviceList[2].ProductionObj.SuspectCycleCount
                }
                else if(DeviceManager.DeviceList[3]){
                    return DeviceManager.DeviceList[3].ProductionObj.SuspectCycleCount
                }
                else{
                    return ""
                }
            }
            eqText3:{
                if(DeviceManager.DeviceList[2]){
                    return DeviceManager.DeviceList[2].ProductionObj.DefectiveCycleCount
                }
                else if(DeviceManager.DeviceList[3]){
                    return DeviceManager.DeviceList[3].ProductionObj.DefectiveCycleCount
                }
                else{
                    return ""
                }
            }
            eqText4:{
                if(DeviceManager.DeviceList[2]){
                    return DeviceManager.DeviceList[2].ProductionObj.GoodCycleCount
                            + DeviceManager.DeviceList[2].ProductionObj.SuspectCycleCount
                            +DeviceManager.DeviceList[2].ProductionObj.DefectiveCycleCount
                }
                else if(DeviceManager.DeviceList[3]){
                    return DeviceManager.DeviceList[3].ProductionObj.GoodCycleCount
                            + DeviceManager.DeviceList[3].ProductionObj.SuspectCycleCount
                            +DeviceManager.DeviceList[3].ProductionObj.DefectiveCycleCount
                }
                else{
                    return ""
                }
            }
            eqText5:{
                if(DeviceManager.DeviceList[2]){
                    return DeviceManager.DeviceList[2].ProductionObj.GoodRate
                }
                else if(DeviceManager.DeviceList[3]){
                    return DeviceManager.DeviceList[3].ProductionObj.GoodRate
                }
                else{
                    return ""
                }
            }
        }
        Button{
            width: 30
            height: 30
            x:566
            y:6
            background: Rectangle{
                color: "transparent"
                Image {
                    anchors.fill: parent
                    source: "qrc:/images/btn_fullscreen_enter.png"
                }
            }
            onPressed: {
                swipevis = true
                DeviceManager.SelectedDeviceIndex = 2
                loadViewpro(3,swipe)
                sigUpdateUI(2)
            }
        }
    }
    Rectangle{
        id:r4
        x:654
        y:338
        width: 600
        height: 287
        radius: 5
        color: pRgb(43, 112, 173)
        onVisibleChanged: {
            if(visible){
                enabled = true
            }
            else{
                enabled = false
            }
        }
        EquipmentInfor{
            id:s10
            x:35
            y:36
            width: 233
            height: 227
            radius: 3
            color: "#0c5596"
            deviceName:{
                if(DeviceManager.DeviceList[3]){
                    return DeviceManager.DeviceList[3].DeviceObj.WelderName
                }
                else if(DeviceManager.DeviceList[2]){
                    return DeviceManager.DeviceList[2].DeviceObj.WelderName
                }
                else{
                    return ""
                }
            }
            deviceType:{
                if(DeviceManager.DeviceList[3]){
                    return DeviceManager.DeviceList[3].DeviceObj.WelderType === 0 ? "L20-VG" : "L20-TS"
                }
                else if(DeviceManager.DeviceList[2]){
                    return DeviceManager.DeviceList[2].DeviceObj.WelderType === 0 ? "L20-VG" : "L20-TS"
                }
                else{
                    return ""
                }
            }
            connectionType:{
                if(DeviceManager.DeviceList[3]){
                    return DeviceManager.DeviceList[3].DeviceObj.ConnectType === 1 ? "RS232" : "TCP/IP"

                }
                else if(DeviceManager.DeviceList[2]){
                    return DeviceManager.DeviceList[2].DeviceObj.ConnectType === 1 ? "RS232" : "TCP/IP"

                }
                else{
                    return ""
                }
            }
            devcieStatus:{
                var connectState = 0
                if(DeviceManager.DeviceList[3])
                {
                    connectState = DeviceManager.DeviceList[3].DeviceObj.ConnectState
                    return GlobalMessageDefine.getConnectState(connectState)
                }
                else if(DeviceManager.DeviceList[2])
                {
                    connectState = DeviceManager.DeviceList[2].DeviceObj.ConnectState
                    return GlobalMessageDefine.getConnectState(connectState)
                }
                else
                {
                    return ""
                }
            }
        }
        RealtimeYield{
            id:s11
            width: 277
            height: 228
            x:280
            y:35
            radius: 3
            color: "#0c5596"
            revealing:{
                if(DeviceManager.DeviceList[3]){
                    return DeviceManager.DeviceList[3].DeviceObj.SuspiciousOption
                }
                else if(DeviceManager.DeviceList[2]){
                    return DeviceManager.DeviceList[2].DeviceObj.SuspiciousOption
                }
                else{
                    return true
                }
            }
            eqText1:{
                if(DeviceManager.DeviceList[3]){
                    return DeviceManager.DeviceList[3].ProductionObj.GoodCycleCount
                }
                else if(DeviceManager.DeviceList[2]){
                    return DeviceManager.DeviceList[2].ProductionObj.GoodCycleCount
                }
                else{
                    return ""
                }
            }
            eqText2:{
                if(DeviceManager.DeviceList[3]){
                    return DeviceManager.DeviceList[3].ProductionObj.SuspectCycleCount
                }
                else if(DeviceManager.DeviceList[2]){
                    return DeviceManager.DeviceList[2].ProductionObj.SuspectCycleCount
                }
                else{
                    return ""
                }
            }
            eqText3:{
                if(DeviceManager.DeviceList[3]){
                    return DeviceManager.DeviceList[3].ProductionObj.DefectiveCycleCount
                }
                else if(DeviceManager.DeviceList[2]){
                    return DeviceManager.DeviceList[2].ProductionObj.DefectiveCycleCount
                }
                else{
                    return ""
                }
            }
            eqText4:{
                if(DeviceManager.DeviceList[3]){
                    return DeviceManager.DeviceList[3].ProductionObj.GoodCycleCount
                            + DeviceManager.DeviceList[3].ProductionObj.SuspectCycleCount
                            +DeviceManager.DeviceList[3].ProductionObj.DefectiveCycleCount
                }
                else if(DeviceManager.DeviceList[2]){
                    return DeviceManager.DeviceList[2].ProductionObj.GoodCycleCount
                            + DeviceManager.DeviceList[2].ProductionObj.SuspectCycleCount
                            +DeviceManager.DeviceList[2].ProductionObj.DefectiveCycleCount
                }
                else{
                    return ""
                }
            }
            eqText5:{
                if(DeviceManager.DeviceList[3]){
                    return DeviceManager.DeviceList[3].ProductionObj.GoodRate
                }
                else if(DeviceManager.DeviceList[2]){
                    return DeviceManager.DeviceList[2].ProductionObj.GoodRate
                }
                else{
                    return ""
                }
            }
        }
        Button{
            width: 30
            height: 30
            x:566
            y:6
            background: Rectangle{
                color: "transparent"
                Image {
                    anchors.fill: parent
                    source: "qrc:/images/btn_fullscreen_enter.png"
                }
            }
            onPressed: {
                swipevis = true
                if(DeviceManager.DeviceCounter === 4)
                {
                    DeviceManager.SelectedDeviceIndex = 3
                }
                else
                {
                    DeviceManager.SelectedDeviceIndex = 2
                }
                loadViewpro(3, swipe)
                sigUpdateUI(3)
            }
        }
    }

       // Button{
       //     id:b1
       //     x:195
       //     y:654
       //     width: 243
       //     height: 52
       //     background: Rectangle{
       //         radius: 6
       //         color: pRgb(43, 112, 173)
       //     }
       //     contentItem: Text {
       //         id:mt1
       //         anchors.centerIn: parent
       //         text: "新建模型"
       //         font.pixelSize: 20
       //         color: pRgb(153, 204, 255)
       //         horizontalAlignment: Text.AlignHCenter
       //         verticalAlignment: Text.AlignVCenter
       //         font.family: fontBold
       //     }
       //     onPressed: {
       //         mt1.text = "创建模型"
       //         mt2.text = "清除数据"
       //     }
       // }
    // Button{
    //     id:b2
    //     width: 243
    //     height: 52
    //     x:228
    //     y:654
    //     background: Rectangle{
    //         radius: 6
    //         border.width: 2
    //         border.color: pRgb(43, 112, 173)
    //         color: itemCount === 4 ? pRgb(232, 232, 232) : pRgb(43, 112, 173)
    //     }
    //     contentItem: Text {
    //         id:mt2
    //         anchors.centerIn: parent
    //         // text: qsTr("新增设备")
    //         text: GlobalLanguageDefine.strAddDevice
    //         font.pixelSize: 20
    //         color: pRgb(153, 204, 255)
    //         horizontalAlignment: Text.AlignHCenter
    //         verticalAlignment: Text.AlignVCenter
    //         font.family: GlobalSystemDefine.fontBold
    //         font.bold: true
    //     }
    //     onPressed: {
    //         // if(mt2.text === qsTr("新增设备"))
    //         if(mt2.text === GlobalLanguageDefine.strAddDevice)
    //         {
    //             popup.openPop(8)
    //         }
    //     }
    // }
    // Button{
    //     id:b3
    //     width: 243
    //     height: 52
    //     x:813
    //     y:654
    //     background: Rectangle{
    //         radius: 6
    //         color: pRgb(43, 112, 173)
    //     }
    //     contentItem: Text {
    //         id:mt3
    //         anchors.centerIn: parent
    //         // text: qsTr( "系统消息")
    //         text: GlobalLanguageDefine.strSystemMessage
    //         font.pixelSize: 20
    //         color: pRgb(153, 204, 255)
    //         horizontalAlignment: Text.AlignHCenter
    //         verticalAlignment: Text.AlignVCenter
    //         font.family: GlobalSystemDefine.fontBold
    //         font.bold: true
    //     }
    //     onPressed: {
    //         popup.openPop(6)
    //     }
    // }
}
