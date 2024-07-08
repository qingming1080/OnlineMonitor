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
                return DeviceManager.deviceList[swipeCurrIndex].pDeviceInformation.connectType === 1
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
            mt1.text = "创建模型"
            mt2.text = "清除数据"
            loader.sourceComponent = mode2
            loader1.sourceComponent = weld2
        }
    }
    Button{
        id:s5
        anchors.left: s4.left
        anchors.top: s4.bottom
        anchors.topMargin:  23
        width:   210
        height:  45
        enabled: equipmentCount === 4 ? false : true
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: pRgb(43, 112, 173)
            color: equipmentCount === 4 ? pRgb(232, 232, 232) : "#0c5696"
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
                width:  812
                height:  560
                color:  "#0c5696"
                radius: 3
            }

            TableView {
                id: tableView
                width:  808
                height:  556
                x: 272
                y: 37
                horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff//隐藏水平滚动条
                verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff//隐藏竖直滚动条
                frameVisible: false
                clip: true
                itemDelegate: Rectangle {
                    height: 38
                    color: styleData.row % 2 === 0 ? "#2d71ae" : "#b1d5db"  // 奇偶行不同背景色
                    Text {
                        anchors.centerIn: parent
                        elide: styleData.elideMode
                        text: styleData.value
                        color: styleData.row % 2 === 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)  // 奇偶行不同背景色
                        font.family: fontBold
                        font.pixelSize: 16
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                }
                rowDelegate: ItemDelegate {
                    height: 40

                }

                Button{
                    id:bt1
                    width: 30
                    height: 30
                    x:14
                    y:5
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

                headerDelegate: Rectangle {
                    height: 40
                    color: pRgb(43, 112, 173)
                    Text {
                        anchors.centerIn: parent
                        text: styleData.value
                        color: "#b1d5db"
                        font.family: fontBold
                        font.pixelSize: 16
                    }
                }

                TableViewColumn {
                    id:ro
                    role: "select"
                    title: "全选"
                    width: 120
                    delegate: Rectangle{
                        color: styleData.row % 2 === 0 ? "#2d71ae" : "#b1d5db"
                        Text {
                            anchors.centerIn: parent
                            text: styleData.value
                            color: "#b1d5db"
                            font.family: fontBold
                            font.pixelSize: 16
                        }

                        Button{
                            id:bt
                            width: 30
                            height: 30
                            anchors.left: parent.left
                            anchors.leftMargin: 15
                            anchors.top: parent.top
                            anchors.topMargin: 5
                            background: Item {
                                width: parent.width
                                height: parent.height
                                Image {
                                    id:im1
                                    anchors.fill: parent
                                    source: styleData.row % 2 === 0 ? "qrc:/image/锁定.png" : "qrc:/image/锁定1.png"
                                    fillMode: Image.PreserveAspectFit // 保持图片的宽高比，适应按钮大小
                                }
                            }
                            onPressed: {
                                if(im1.source == "qrc:/image/解锁.png"){
                                    im1.source = styleData.row % 2 === 0 ? "qrc:/image/锁定.png" : "qrc:/image/锁定1.png"
                                }
                                else{
                                    im1.source = "qrc:/image/解锁.png"
                                }
                            }
                        }
                        Connections{
                            target: bt1
                            function onPressed(){
                                im1.source = im.source
                            }
                        }
                    }
                }

                TableViewColumn {
                    role: "num"
                    title: "序号"
                    width:  90
                }
                TableViewColumn {
                    role: "weldTime"
                    title: "焊接时间"
                    width:  90
                }

                TableViewColumn {
                    role: "power"
                    title: "功率"
                    width:  90
                }
                TableViewColumn {
                    role: "energy"
                    title: "能量"
                    width:  90
                }
                TableViewColumn {
                    role: "date"
                    title: "日期"
                    width:  90
                }
                TableViewColumn {
                    role: "date"
                    title: "拉力"
                    width: 122
                    delegate: Rectangle{
                        color: styleData.row % 2 === 0 ? "#2d71ae" : "#b1d5db"
                        TextField{
                            width: 100
                            height: 33
                            anchors.centerIn: parent
                            horizontalAlignment: TextInput.AlignHCenter
                            verticalAlignment: TextInput.AlignVCenter
                            color: styleData.row % 2 === 0 ? pRgb(175, 195, 216) : "#014c8d"
                            font.family: fontBold
                            font.pixelSize: 16
                            background: Rectangle{
                                radius: 2
                                border.width: 2
                                border.color: styleData.row % 2 === 0 ? pRgb(175, 195, 216) : pRgb(45, 113, 174)
                                color: styleData.row % 2 === 0 ? "#2d71ae" : "#b1d5db"
                            }
                        }
                    }
                }
                TableViewColumn {
                    role: "date"
                    title: "残留度"
                    width: 122
                    delegate: Rectangle{
                        color: styleData.row % 2 === 0 ? "#2d71ae" : "#b1d5db"
                        TextField{
                            width: 100
                            height: 33
                            anchors.centerIn: parent
                            horizontalAlignment: TextInput.AlignHCenter
                            verticalAlignment: TextInput.AlignVCenter
                            color: styleData.row % 2 === 0 ? pRgb(175, 195, 216) : "#014c8d"
                            font.family: fontBold
                            font.pixelSize: 16
                            background: Rectangle{
                                radius: 2
                                border.width: 2
                                border.color: styleData.row % 2 === 0 ? pRgb(175, 195, 216) : pRgb(45, 113, 174)
                                color: styleData.row % 2 === 0 ? "#2d71ae" : "#b1d5db"
                            }
                        }
                    }
                }
                model: ListModel {
                    ListElement {select:1;num:1;weldTime:"2002-1-2-3"; name: "Item 1"; date: "1" ;energy: "2";power: "2";result: "3";}
                    ListElement {select:1;num:1;weldTime:2; name: "Item 1"; date: "1" ;energy: "2";power: "2";result: "3";}
                }
            }
        }
    }

}
