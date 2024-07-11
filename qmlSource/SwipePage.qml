import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15
import QtQml.Models 2.15
import Device 1.0
import DeviceInformation 1.0
Rectangle {
    color: pRgb(153, 204, 255)
    radius: 5
    property int pbtnIndex: 1
    function newModel(){
        mt1.text = "创建模型"
        mt2.text = "清除数据"
        loader.sourceComponent = mode2
        loader1.sourceComponent = weld2
    }

    EquipmentInfor{
        id:s1
        x: 52
        y:35
        width:  208
        height: 203
        color: "#0c5696"
        eqText1:{
            if(DeviceManager.deviceList[swipeCurrIndex]){
                return DeviceManager.deviceList[swipeCurrIndex].pDeviceInformation.name
            }
            else{
                return ""
            }
        }
        eqText2:{
            if(DeviceManager.deviceList[swipeCurrIndex]){
                return DeviceManager.deviceList[swipeCurrIndex].pDeviceInformation.model
            }
            else{
                return ""
            }
        }
        eqText3:{
            if(DeviceManager.deviceList[swipeCurrIndex]){
                return DeviceManager.deviceList[swipeCurrIndex].pDeviceInformation.connectType === 2
                        ? "RS232" : "网络连接"
            }
            else{
                return ""
            }
        }
        eqText4:{
            if(DeviceManager.deviceList[swipeCurrIndex]){
                return DeviceManager.deviceList[swipeCurrIndex].pDeviceInformation.state
            }
            else{
                return ""
            }
        }
    }

    Loader{
        id:loader1
        sourceComponent: weld1
    }
    Component{
        id:weld1
        Item {
            WeldingResult{
                id:s3
                width:  212
                height:  215
                x:50
                y:248
                color: "#0c5696"
                eqText1:{
                    if(DeviceManager.deviceList[swipeCurrIndex]){
                        return DeviceManager.deviceList[swipeCurrIndex].pDeviceInformation.power
                    }
                    else{
                        return ""
                    }
                }
                eqText2:{
                    if(DeviceManager.deviceList[swipeCurrIndex]){
                        return DeviceManager.deviceList[swipeCurrIndex].pDeviceInformation.time
                    }
                    else{
                        return ""
                    }
                }

                eqText3:{
                    if(DeviceManager.deviceList[swipeCurrIndex]){
                        return DeviceManager.deviceList[swipeCurrIndex].pDeviceInformation.energy
                    }
                    else{
                        return ""
                    }
                }
                eqText4:{
                    if(DeviceManager.deviceList[swipeCurrIndex]){
                        return DeviceManager.deviceList[swipeCurrIndex].pDeviceInformation.heightPre
                    }
                    else{
                        return ""
                    }
                }
                eqText5:{
                    if(DeviceManager.deviceList[swipeCurrIndex]){
                        return DeviceManager.deviceList[swipeCurrIndex].pDeviceInformation.heightPost
                    }
                    else{
                        return ""
                    }
                }
            }
        }
    }
    Component{
        id:weld2
        Item {
            WeldingParameter{
                id:s3_1
                width:  212
                height:  215
                x:  50
                y:  248
                color:  "#0c5696"
                altitudeMode:DeviceManager.deviceList[swipeCurrIndex].pDeviceInformation.heightOption
                             === 1 ? true:false
            }
        }
    }
    Button{
        id:s4
        x: 50
        y: 482
        width:   210
        height:  45
        background: Rectangle{
            radius: 6
            color:  "#0c5696"
        }
        contentItem: Text {
            id: mt1
            text: "新建模型"
            font.pixelSize:  17
            color: pRgb(153, 204, 255)
            anchors.centerIn: parent  // 确保文本在按钮内居中对齐
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: fontBold
        }
        onClicked: {
            if(mt1.text === "新建模型"){
                popup.openPop(2)
            }
            else{
                mt1.text = "创建模型"
                mt2.text = "清除数据"
                loader.sourceComponent = mode2
                loader1.sourceComponent = weld2
            }
        }
    }
    Button{
        id:s5
        anchors.left: s4.left
        anchors.top: s4.bottom
        anchors.topMargin:  23
        width:   210
        height:  45
        enabled: {
            if(mt2.text === "新增设备"){
                return equipmentCount === 4 ? false : true
            }
            else{
                return true
            }
        }
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: pRgb(43, 112, 173)
            color: {
                if(mt2.text === "新增设备"){
                    return equipmentCount === 4 ? pRgb(232, 232, 232) : "#0c5696"
                }
                else{
                    return "#0c5696"
                }
            }
        }
        contentItem: Text {
            id:mt2
            anchors.centerIn: parent
            text: "新增设备"
            font.pixelSize: 17
            color: pRgb(153, 204, 255)
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: fontBold
        }
        onPressed: {
            if(mt2.text == "新增设备"){
                switchUI(3)
                isAdd = true
                sigSysConfig()
            }
        }
    }
    Loader{
        id:loader
        sourceComponent: mode1
    }

    Component{
        id:mode1
        Item {
            x:0
            RealtimeYield{
                id:s2
                width:  288
                height:  235
                x: 269
                y: 35
                color:  "#0c5696"
                revealing:{
                    if(DeviceManager.deviceList[swipeCurrIndex]){
                        return DeviceManager.deviceList[swipeCurrIndex].pIO.availabel
                    }
                    else{
                        return true
                    }
                }
                eqText1:{
                    if(DeviceManager.deviceList[swipeCurrIndex]){
                        return DeviceManager.deviceList[swipeCurrIndex].pDeviceInformation.goodCycles
                    }
                    else{
                        return ""
                    }
                }
                eqText2:{
                    if(DeviceManager.deviceList[swipeCurrIndex]){
                        return DeviceManager.deviceList[swipeCurrIndex].pDeviceInformation.suspectCycles
                    }
                    else{
                        return ""
                    }
                }
                eqText3:{
                    if(DeviceManager.deviceList[swipeCurrIndex]){
                        return DeviceManager.deviceList[swipeCurrIndex].pDeviceInformation.notDefinite
                    }
                    else{
                        return ""
                    }
                }
                eqText4:{
                    if(DeviceManager.deviceList[swipeCurrIndex]){
                        return DeviceManager.deviceList[swipeCurrIndex].pDeviceInformation.goodCycles
                                + DeviceManager.deviceList[swipeCurrIndex].pDeviceInformation.notDefinite
                                +DeviceManager.deviceList[swipeCurrIndex].pDeviceInformation.suspectCycles
                    }
                    else{
                        return ""
                    }
                }
                eqText5:{
                    if(DeviceManager.deviceList[swipeCurrIndex]){
                        return DeviceManager.deviceList[swipeCurrIndex].pDeviceInformation.goodRate
                    }
                    else{
                        return ""
                    }
                }
            }
            YieldTrend{
                id:s6
                width:  514
                height:  235
                x: 568
                y: 35
                color:  "#0c5696"
                equiInforIndex:1
                btnIndex: pbtnIndex
            }
            WeldingTrend{
                id:s7
                width:  502
                height:  311
                x: 269
                y: 284
                color:  "#0c5696"
            }
            AbnormalInfor{
                id:s8
                width:  303
                height:  311
                x: 778
                y: 284
                color:  "#0c5696"
            }
        }
    }
    Component{
        id:mode2
        Item {
            Rectangle{
                id:rect
                x: 269
                y: 36
                width:812
                height: 560
                color: "#0c5696"
                radius: 3
            }
            Rectangle{
                width:810
                height: 558
                x: 270
                y: 37
                color: pRgb(43, 112, 173)
                Text{
                    id:t1
                    x:808/7/2+5-width/2
                    y:11
                    font.pixelSize: 16
                    text: "全选"
                    font.family: fontBold
                    color: pRgb(153, 204, 255)
                }
                Button{
                    id:bt1
                    width: 30
                    height: 30
                    x:15
                    y:8
                    background: Item {
                        width: parent.width
                        height: parent.height
                        Image {
                            id:im
                            anchors.fill: parent
                            source: "qrc:/image/解锁.png"
                            fillMode: Image.PreserveAspectFit // 保持图片的宽高比，适应按钮大小
                        }
                    }
                    onPressed: {
                        tableFlag = true
                        if(im.source == "qrc:/image/解锁.png"){
                            im.source = "qrc:/image/锁定.png"
                        }
                        else{
                            im.source = "qrc:/image/解锁.png"
                        }
                    }
                }
                Text{
                    id:t2
                    x:808/8 + 808/8/2-width/2
                    y:11
                    font.pixelSize: 16
                    text: "序号"
                    font.family: fontBold
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id:t3
                    x:808/8*2 + 808/8/2-width/2
                    y:11
                    font.pixelSize: 16
                    text: "焊接时间"
                    font.family: fontBold
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id:t4
                    x:808/8*3 + 808/8/2-width/2
                    y:11
                    font.pixelSize: 16
                    text: "功率"
                    font.family: fontBold
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id:t5
                    x:808/8*4 + 808/8/2-width/2
                    y:11
                    font.pixelSize: 16
                    text: "能量"
                    font.family: fontBold
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id:t6
                    x:808/8*5 + 808/8/2-width/2
                    y:11
                    font.pixelSize: 16
                    text: "日期"
                    font.family: fontBold
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id:t7
                    x:808/8*6 + 808/8/2-width/2
                    y:11
                    font.pixelSize: 16
                    text: "拉力"
                    font.family: fontBold
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id:t8
                    x:808/8*7 + 808/8/2-width/2
                    y:11
                    font.pixelSize: 16
                    text: "残留度"
                    font.family: fontBold
                    color: pRgb(171, 206, 213)
                }
                ListView{
                    id: taskplanView
                    width:810
                    height: 510
                    y:40
                    clip: true
                    model: Manual
                    delegate: Rectangle{
                        id: regionItem
                        height: 36
                        width: 810
                        color: index % 2 === 0 ? "#afc3d8" : "#2d71ae"
                        Button{
                            id:bt
                            x:808/8/2-width/2
                            anchors.verticalCenter: parent.verticalCenter
                            width: 30
                            height: 30
                            background: Item {
                                width: parent.width
                                height: parent.height
                                Image {
                                    id:im1
                                    anchors.fill: parent
                                    source: index % 2 !== 0 ? "qrc:/image/锁定.png" : "qrc:/image/锁定1.png"
                                    fillMode: Image.PreserveAspectFit // 保持图片的宽高比，适应按钮大小
                                }
                            }
                            onPressed: {
                                if(im1.source == "qrc:/image/解锁.png"){
                                    im1.source = "qrc:/image/锁定.png"
                                }
                                else if(im1.source == "qrc:/image/锁定.png"){
                                    im1.source = "qrc:/image/解锁.png"
                                }
                                else if(im1.source == "qrc:/image/锁定1.png"){
                                    im1.source = "qrc:/image/解锁1.png"
                                }
                                else if(im1.source == "qrc:/image/解锁1.png"){
                                    im1.source = "qrc:/image/锁定1.png"
                                }
                            }
                        }
                        Connections{
                            target: bt1
                            function onPressed(){
                                if(index % 2 === 0){
                                    if(im.source == "qrc:/image/解锁.png"){
                                        im1.source = "qrc:/image/解锁1.png"
                                    }
                                    else{
                                        im1.source = "qrc:/image/锁定1.png"
                                    }
                                }
                                else{
                                    if(im.source == "qrc:/image/解锁.png"){
                                        im1.source = "qrc:/image/解锁.png"
                                    }
                                    else{
                                        im1.source = "qrc:/image/锁定.png"
                                    }
                                }
                            }
                        }
                        Text{
                            x:808/8*1 + 808/8/2-width/2
                            anchors.verticalCenter: parent.verticalCenter
                            font.pixelSize: 16
                            text: serial_number
                            font.family: fontBold
                            color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                        }
                        Text{
                            anchors.verticalCenter: parent.verticalCenter
                            x:808/8*2 + 808/8/2-width/2
                            font.pixelSize: 16
                            text: time
                            font.family: fontBold
                            color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                        }
                        Text{
                            anchors.verticalCenter: parent.verticalCenter
                            x:808/8*3 + 808/8/2-width/2
                            font.pixelSize: 16
                            text: power
                            font.family: fontBold
                            color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                        }
                        Text{
                            anchors.verticalCenter: parent.verticalCenter
                            x:808/8*4 + 808/8/2-width/2
                            font.pixelSize: 16
                            text: energy
                            font.family: fontBold
                            color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                        }
                        Text{
                            anchors.verticalCenter: parent.verticalCenter
                            x:808/8*5 + 808/8/2-width/2
                            font.pixelSize: 16
                            text: create_time
                            font.family: fontBold
                            color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                        }
                        TextField{
                            id: textField
                            width: 100
                            height: 33
                            anchors.verticalCenter: parent.verticalCenter
                            x:808/8*6 + 808/8/2-width/2
                            horizontalAlignment: TextInput.AlignHCenter
                            verticalAlignment: TextInput.AlignVCenter
                            color: index % 2 === 0 ? pRgb(175, 195, 216) : "#014c8d"
                            font.family: fontBold
                            font.pixelSize: 16
                            text:actual_force
                            background: Rectangle{
                                radius: 3
                                border.width: 2
                                border.color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                                color: index % 2 !== 0 ? "#2d71ae" : "#afc3d8"
                            }
                            cursorDelegate: Rectangle {
                                width: textField.cursorWidth
                                height: textField.font.pixelSize * 1.1
                                color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                                visible: textField.activeFocus
                                anchors.verticalCenter: parent.verticalCenter
                                Text {
                                    text: "|"
                                    color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                                    font.pixelSize: textField.font.pixelSize
                                    anchors.centerIn: parent
                                }
                            }
                        }
                        TextField{
                            width: 100
                            height: 33
                            anchors.verticalCenter: parent.verticalCenter
                            x:808/8*7 + 808/8/2-width/2
                            horizontalAlignment: TextInput.AlignHCenter
                            verticalAlignment: TextInput.AlignVCenter
                            color: index % 2 === 0 ? pRgb(175, 195, 216) : "#014c8d"
                            font.family: fontBold
                            font.pixelSize: 16
                            text:actual_degree
                            background: Rectangle{
                                radius: 6
                                border.width: 3
                                border.color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                                color: index % 2 !== 0 ? "#2d71ae" : "#afc3d8"
                            }
                            cursorDelegate: Rectangle {
                                width: textField.cursorWidth
                                height: textField.font.pixelSize * 1.1
                                color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                                visible: textField.activeFocus
                                anchors.verticalCenter: parent.verticalCenter
                                Text {
                                    text: "|"
                                    color: index % 2 === 0 ? "#2d71ae" : "#afc3d8"
                                    font.pixelSize: textField.font.pixelSize
                                    anchors.centerIn: parent
                                }
                            }
                        }
                    }
                }
            }
        }
    }

}
