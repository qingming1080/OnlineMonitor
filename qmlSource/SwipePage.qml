import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15
import QtQml.Models 2.15
import Device 1.0
import DeviceInformation 1.0
import QmlEnum 1.0
Rectangle {
    color: pRgb(153, 204, 255)
    radius: 5
    property int pbtnIndex: 1
    property int listSize: 0
    property int parameter1: 0
    property int parameter2: 0
    property int parameter3: 0
    property int parameter4: 0
    property int parameter5: 0
    function newModel(){
        loader.sourceComponent = mode2
        loader1.sourceComponent = weld2
    }

    Connections{
        target: window
        function onSigNewModel(){
            newModel()
            createModel = true
        }
    }
    //    Button{
    //        width: 50
    //        height: 50
    //        Image {
    //            anchors.fill: parent
    //            width: 50
    //            height: 50
    //            source: "qrc:/image/switch.png"
    //        }
    //        background: Rectangle{
    //            color: "transparent"
    //        }
    //        onPressed: {
    //            deviceStatus.visible = !deviceStatus.visible
    //        }
    //    }
    //    Rectangle {
    //        id: deviceStatus
    //        radius: 3
    //        x:42
    //        y:35
    //        width:  258
    //        height: mt1.text === "新建模型" ? 255 :225
    //        color: "#0c5696"
    //        Rectangle{
    //            width: 258
    //            height: 44
    //            radius: 3
    //            color: "#007dbc"
    //            Text {
    //                id:t2
    //                text: qsTr("设备名称")
    //                font.family: fontBold
    //                font.pixelSize:  20
    //                color: pRgb(171, 206, 213)
    //                anchors.centerIn: parent
    //            }
    //        }
    //        Button{
    //            id:b1
    //            x:5
    //            y:50
    //            width: 248
    //            height: 44
    //            background: Rectangle{
    //                radius: 5
    //                width: 248
    //                height: 44
    //                color: pRgb(177, 213, 219)
    //                border.color: "#007dbc"
    //                border.width: 2
    //                Text {
    //                    text: {
    //                        if(DeviceManager.deviceList[0]){
    //                            return DeviceManager.deviceList[0].pDeviceInformation.name
    //                        }
    //                        return ""
    //                    }
    //                    font.family: fontBold
    //                    font.pixelSize:  20
    //                    color: "#0c5696"
    //                    anchors.centerIn: parent
    //                }
    //            }
    //            visible: equipmentCount >=1 ? true : false
    //        }
    //        Button{
    //            id:b2
    //            x:5
    //            anchors.top: b1.bottom
    //            anchors.topMargin: 8
    //            width: 248
    //            height: 44
    //            background: Rectangle{
    //                radius: 5
    //                width: 248
    //                height: 44
    //                color: pRgb(177, 213, 219)
    //                border.color: "#007dbc"
    //                border.width: 2
    //                Text {
    //                    text: {
    //                        if(DeviceManager.deviceList[1]){
    //                            return DeviceManager.deviceList[1].pDeviceInformation.name
    //                        }
    //                        return ""
    //                    }
    //                    font.family: fontBold
    //                    font.pixelSize:  20
    //                    color: "#0c5696"
    //                    anchors.centerIn: parent
    //                }
    //            }
    //            visible: equipmentCount >=2 ? true : false
    //        }
    //        Button{
    //            id:b3
    //            x:5
    //            anchors.top: b2.bottom
    //            anchors.topMargin: 8
    //            width: 248
    //            height: 44
    //            background: Rectangle{
    //                radius: 5
    //                width: 248
    //                height: 44
    //                color: pRgb(177, 213, 219)
    //                border.color: "#007dbc"
    //                border.width: 2
    //                Text {
    //                    text: {
    //                        if(DeviceManager.deviceList[2]){
    //                            return DeviceManager.deviceList[2].pDeviceInformation.name
    //                        }
    //                        return ""
    //                    }
    //                    font.family: fontBold
    //                    font.pixelSize:  20
    //                    color: "#0c5696"
    //                    anchors.centerIn: parent
    //                }
    //            }
    //            visible: equipmentCount >=3 ? true : false
    //        }
    //        Button{
    //            id:b4
    //            x:5
    //            anchors.top: b3.bottom
    //            anchors.topMargin: 8
    //            width: 248
    //            height: 44
    //            background: Rectangle{
    //                radius: 5
    //                width: 248
    //                height: 44
    //                color: pRgb(177, 213, 219)
    //                border.color: "#007dbc"
    //                border.width: 2
    //                Text {
    //                    text: {
    //                        if(DeviceManager.deviceList[3]){
    //                            return DeviceManager.deviceList[3].pDeviceInformation.name
    //                        }
    //                        return ""
    //                    }
    //                    font.family: fontBold
    //                    font.pixelSize:  20
    //                    color: "#0c5696"
    //                    anchors.centerIn: parent
    //                }
    //            }
    //            visible: equipmentCount >=4 ? true : false
    //        }
    //    }
    EquipmentInfor{
        id:s1
        x:42
        y:35
        width:  258
        height: (mt1.text === "新建模型" || mt1.text === "New Model") ? 255 :225
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
        asynchronous:true
        sourceComponent: weld1
    }
    Component{
        id:weld1
        Item {
            WeldingResult{
                id:s3
                width:  258
                height:  246
                x:42
                y:314
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
                width:  258
                height:  236
                x:42
                y:274
                color:  "#0c5696"
                eqText1:parameter1
                eqText2:parameter2
                eqText3:parameter3
                eqText4:parameter4
                eqText5:parameter5
            }
        }
    }
    Button{
        id:s4
        x: 42
        y: (mt1.text === "新建模型" || mt1.text === "New Model") ? 580 :520
        width:   258
        height:  45
        background: Rectangle{
            radius: 6
            color:  "#0c5696"
        }
        contentItem: Text {
            id: mt1
            text: {
                if(LanguageManger.language === "SimplifiedChinese"){
                    if(createModel){
                        return qsTr("创建模型")
                    }
                    else{
                        return qsTr("新建模型")
                    }
                }
                else{
                    if(createModel){
                        return qsTr("Create Model")
                    }
                    else{
                        return qsTr("New Model")
                    }
                }
            }
            font.pixelSize:  17
            color: pRgb(153, 204, 255)
            anchors.centerIn: parent  // 确保文本在按钮内居中对齐
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: fontBold
            font.bold: true
        }
        onPressed: {
            if((mt1.text === "新建模型" || mt1.text === "New Model")){
                popup.openPop(2)
            }
            else if(mt1.text === "创建模型" || mt1.text === "Create Model"){
                if(DeviceManager.deviceList[swipeCurrIndex].pDeviceInformation.sample <= listSize){
                    loader.sourceComponent = mode1
                    loader1.sourceComponent = weld1
                    Manual.save()
                    sigUpdateUI(0)
                    sigRecover()
                    createModel = false
                }
                else{
                    popup.openPop(5)
                }
            }
        }
    }
    Button{
        id:s5
        anchors.left: s4.left
        anchors.top: s4.bottom
        anchors.topMargin:  10
        width:   258
        height:  45
        visible: (mt1.text === "创建模型" || mt1.text === "Create Model") ? true:false
        background: Rectangle{
            radius: 6
            border.color: pRgb(43, 112, 173)
            color: "#0c5696"
        }
        contentItem: Text {
            id:mt2
            anchors.centerIn: parent
            text: LanguageManger.language === "SimplifiedChinese" ? qsTr("清除数据") : qsTr("Clear Data")
            font.pixelSize: 17
            color: pRgb(153, 204, 255)
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: fontBold
            font.bold: true
        }
        onPressed: {
            Manual.clearData()
        }
    }
    Loader{
        id:loader
        asynchronous:true
        sourceComponent: mode1
    }

    Component{
        id:mode1
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
                height:  255
                x: 658
                y: 35
                color:  "#0c5696"
                equiInforIndex:1
                btnIndex: pbtnIndex
            }
            WeldingTrend{
                id:s7
                width:  502
                height:  311
                x: 329
                y: 314
                color:  "#0c5696"
            }
            AbnormalInfor{
                id:s8
                width:  313
                height:  311
                x: 858
                y: 314
                color:  "#0c5696"
            }
        }
    }
    Component{
        id:mode2
        Item {
            Rectangle{
                id:rect
                x: 319
                y: 36
                width:842
                height: 582
                color: "#0c5696"
                radius: 3
            }
            Rectangle{
                width:840
                height: 580
                x: 320
                y: 37
                color: pRgb(43, 112, 173)
                Text{
                    id:t1
                    x:840/7/2+5-width/2
                    y:11
                    font.pixelSize: 16
                    text: qsTr("全选")
                    font.family: fontBold
                    font.bold: true
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
                            source: "qrc:/image/unlock.png"
                            fillMode: Image.PreserveAspectFit // 保持图片的宽高比，适应按钮大小
                        }
                    }
                    onPressed: {
                        tableFlag = true
                        if(im.source == "qrc:/image/unlock.png"){
                            im.source = "qrc:/image/lock.png"
                        }
                        else{
                            im.source = "qrc:/image/unlock.png"
                        }
                    }
                }
                Text{
                    id:t2
                    x:840/8 + 840/8/2-width/2
                    y:11
                    font.pixelSize: 16
                    text: qsTr("序号")
                    font.family: fontBold
                    font.bold: true
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id:t3
                    x:840/8*2 + 840/8/2-width/2
                    y:11
                    font.pixelSize: 16
                    text: qsTr("焊接时间")
                    font.family: fontBold
                    font.bold: true
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id:t4
                    x:840/8*3 + 840/8/2-width/2
                    y:11
                    font.pixelSize: 16
                    text: qsTr("功率")
                    font.family: fontBold
                    font.bold: true
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id:t5
                    x:840/8*4 + 840/8/2-width/2
                    y:11
                    font.pixelSize: 16
                    text: qsTr("能量")
                    font.family: fontBold
                    font.bold: true
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id:t6
                    x:840/8*5 + 840/8/2-width/2
                    y:11
                    font.pixelSize: 16
                    text: qsTr("日期")
                    font.family: fontBold
                    font.bold: true
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id:t7
                    x:840/8*6 + 840/8/2-width/2
                    y:11
                    font.pixelSize: 16
                    text: qsTr("拉力")
                    font.family: fontBold
                    font.bold: true
                    color: pRgb(171, 206, 213)
                }
                Text{
                    id:t8
                    x:840/8*7 + 840/8/2-width/2
                    y:11
                    font.pixelSize: 16
                    text: qsTr("残留度")
                    font.family: fontBold
                    font.bold: true
                    color: pRgb(171, 206, 213)
                }
                ListView{
                    id: taskplanView
                    width:840
                    height: 535
                    y:40
                    clip: true
                    model: Manual
                    onCountChanged:{
                        listSize = taskplanView.count
                    }
                    delegate: Rectangle{
                        id: regionItem
                        height: 36
                        width: 840
                        color: index % 2 === 0 ? "#afc3d8" : "#2d71ae"
                        MouseArea {
                            id: mouseArea
                            anchors.fill: parent
                            onPressed: {
                                taskplanView.currentIndex = index
                                parameter1 = Manual.data(Manual.index(index,0),QmlEnum.MANUAL_energy)
                                parameter2 = Manual.data(Manual.index(index,0),QmlEnum.MANUAL_amplitude)
                                parameter3 = Manual.data(Manual.index(index,0),QmlEnum.MANUAL_pressure)
                                parameter4 = Manual.data(Manual.index(index,0),QmlEnum.MANUAL_pre_height)
                                parameter5 = Manual.data(Manual.index(index,0),QmlEnum.MANUAL_post_height)
                            }
                        }
                        Button{
                            id:bt
                            x:840/8/2-width/2
                            anchors.verticalCenter: parent.verticalCenter
                            width: 30
                            height: 30
                            background: Item {
                                width: parent.width
                                height: parent.height
                                Image {
                                    id:im1
                                    anchors.fill: parent
                                    source: index % 2 !== 0 ? "qrc:/image/lock.png" : "qrc:/image/lock1.png"
                                    fillMode: Image.PreserveAspectFit // 保持图片的宽高比，适应按钮大小
                                }
                            }

                            onPressed: {
                                if(im1.source == "qrc:/image/unlock.png"){
                                    im1.source = "qrc:/image/lock.png"
                                }
                                else if(im1.source == "qrc:/image/lock.png"){
                                    im1.source = "qrc:/image/unlock.png"
                                }
                                else if(im1.source == "qrc:/image/lock1.png"){
                                    im1.source = "qrc:/image/unlock1.png"
                                }
                                else if(im1.source == "qrc:/image/unlock1.png"){
                                    im1.source = "qrc:/image/lock1.png"
                                }
                            }
                        }
                        Connections{
                            target: bt1
                            function onPressed(){
                                if(index % 2 === 0){
                                    if(im.source == "qrc:/image/unlock.png"){
                                        im1.source = "qrc:/image/unlock1.png"
                                    }
                                    else{
                                        im1.source = "qrc:/image/lock1.png"
                                    }
                                }
                                else{
                                    if(im.source == "qrc:/image/unlock.png"){
                                        im1.source = "qrc:/image/unlock.png"
                                    }
                                    else{
                                        im1.source = "qrc:/image/lock.png"
                                    }
                                }
                            }
                        }
                        Text{
                            x:840/8*1 + 840/8/2-width/2
                            anchors.verticalCenter: parent.verticalCenter
                            font.pixelSize: 16
                            text: serial_number
                            font.family: fontBold
                            font.bold: true
                            color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                        }
                        Text{
                            anchors.verticalCenter: parent.verticalCenter
                            x:840/8*2 + 840/8/2-width/2
                            font.pixelSize: 16
                            text: time
                            font.family: fontBold
                            font.bold: true
                            color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                        }
                        Text{
                            anchors.verticalCenter: parent.verticalCenter
                            x:840/8*3 + 840/8/2-width/2
                            font.pixelSize: 16
                            text: power
                            font.family: fontBold
                            font.bold: true
                            color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                        }
                        Text{
                            anchors.verticalCenter: parent.verticalCenter
                            x:840/8*4 + 840/8/2-width/2
                            font.pixelSize: 16
                            text: energy
                            font.family: fontBold
                            font.bold: true
                            color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                        }
                        Text{
                            anchors.verticalCenter: parent.verticalCenter
                            x:840/8*5 + 840/8/2-width/2
                            font.pixelSize: 16
                            text: create_time
                            font.family: fontBold
                            font.bold: true
                            color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                        }
                        TextField{
                            id: textField
                            width: 100
                            height: 33
                            anchors.verticalCenter: parent.verticalCenter
                            x:840/8*6 + 840/8/2-width/2
                            horizontalAlignment: TextInput.AlignHCenter
                            verticalAlignment: TextInput.AlignVCenter
                            color: index % 2 === 0 ? pRgb(175, 195, 216) : "#014c8d"
                            font.family: fontBold
                            font.bold: true
                            font.pixelSize: 16
                            text:actual_force
                            inputMethodHints: Qt.ImhDigitsOnly
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
                            MouseArea {
                                anchors.fill: parent
                                onPressed: {
                                    textField.forceActiveFocus()
                                    keyboardYype = 0
                                }
                            }
                        }
                        TextField{
                            id:textField1
                            width: 100
                            height: 33
                            anchors.verticalCenter: parent.verticalCenter
                            x:840/8*7 + 840/8/2-width/2
                            horizontalAlignment: TextInput.AlignHCenter
                            verticalAlignment: TextInput.AlignVCenter
                            color: index % 2 === 0 ? pRgb(175, 195, 216) : "#014c8d"
                            font.family: fontBold
                            font.bold: true
                            font.pixelSize: 16
                            text:actual_degree
                            inputMethodHints: Qt.ImhDigitsOnly
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
                            MouseArea {
                                anchors.fill: parent
                                onPressed: {
                                    textField1.forceActiveFocus()
                                    keyboardYype = 0
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
