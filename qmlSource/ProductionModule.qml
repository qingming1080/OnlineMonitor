import QtQuick 2.15
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15
import Device 1.0
import DeviceInformation 1.0
import QmlEnum 1.0
Rectangle {
    id:mpro
    color: pRgb(153, 204, 255)
    property bool tableFlag: false
    property var proViews: []
    property int rect1: 1
    property int rect2: 1
    property int swipeIndex: 0
    property int parameter1: 0
    property int parameter2: 0
    property int parameter3: 0
    property int parameter4: 0
    property int parameter5: 0
    property int listSize: 0
    signal sigBtnSynchronization(var index,var time)
    signal sigSwipeCurrIndex(var index)
    onRect1Changed: {
        sigBtnSynchronization(1,rect1)
    }
    onRect2Changed: {
        sigBtnSynchronization(2,rect2)
    }

    onSwipeIndexChanged: {
        sigSwipeCurrIndex(swipeIndex)
    }

    Component.onCompleted: {
        if(equipmentCount > 1){
            mode = 1
            loadViewpro(2,multipro)
        }
        else{
            mode = 0
            loadViewpro(1,autopro)
        }
    }
    function loadViewpro(viewName, component) {
        prostack.pop()
        if (proViews[viewName]) {
            // 如果视图已缓存，直接显示
            prostack.push(proViews[viewName]);
        } else {
            // 创建视图并缓存
            var newItem = component.createObject(prostack);
            proViews[viewName] = newItem;
            prostack.push(newItem);
        }
    }
    function buttonSynchronization(index,time){
        if(index === 1){
            rect1 = time
        }
        else if(index === 2){
            rect2 = time
        }
    }


    Connections{
        target: window
        function onEquipmentCountChanged(){
            if(equipmentCount > 1){
                mode = 1
                loadViewpro(2,multipro)
            }
            else{
                mode = 0
                loadViewpro(1,autopro)
            }
        }
    }

    StackView{
        id:prostack
    }
    Component{
        id:autopro
        Item{
            Connections{
                target: window
                function onSigOneModel(){
                    mt1.text = "创建模型"
                    mt2.text = "清除数据"
                    loader.sourceComponent = mode2
                    loader1.sourceComponent = weld2
                }
            }

            EquipmentInfor{
                id:s1
                x:mode == 1 ? 52 : 29
                y:mode == 1 ? 35 : 20
                width: mode == 1 ? 208 : 243
                height: mode == 1 ? 203 : 258
                color: mode == 1 ? "#0c5696" : pRgb(43, 112, 173)
                eqText1:DeviceManager.deviceList[0].pDeviceInformation.name
                eqText2:DeviceManager.deviceList[0].pDeviceInformation.model
                eqText3:DeviceManager.deviceList[0].pDeviceInformation.connectType === 2
                        ? "RS232" : "网络连接"
                eqText4:DeviceManager.deviceList[0].pDeviceInformation.state
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
                        width: mode == 1 ? 212 : 245
                        height: mode == 1 ? 215 : 249
                        x: mode == 1 ? 50 : 29
                        y: mode == 1 ? 248 : 289
                        color: mode == 1 ? "#0c5696" : pRgb(43, 112, 173)
                        eqText1:{
                            if(DeviceManager.deviceList[0]){
                                return DeviceManager.deviceList[0].pDeviceInformation.power
                            }
                            else{
                                return ""
                            }
                        }
                        eqText2:{
                            if(DeviceManager.deviceList[0]){
                                return DeviceManager.deviceList[0].pDeviceInformation.time
                            }
                            else{
                                return ""
                            }
                        }

                        eqText3:{
                            if(DeviceManager.deviceList[0]){
                                return DeviceManager.deviceList[0].pDeviceInformation.energy
                            }
                            else{
                                return ""
                            }
                        }
                        eqText4:{
                            if(DeviceManager.deviceList[0]){
                                return DeviceManager.deviceList[0].pDeviceInformation.heightPre
                            }
                            else{
                                return ""
                            }
                        }
                        eqText5:{
                            if(DeviceManager.deviceList[0]){
                                return DeviceManager.deviceList[0].pDeviceInformation.heightPost
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
                        width: mode == 1 ? 212 : 245
                        height: mode == 1 ? 215 : 249
                        x: mode == 1 ? 50 : 29
                        y: mode == 1 ? 248 : 289
                        color: mode == 1 ? "#0c5696" : pRgb(43, 112, 173)
                        altitudeMode:{
                            if(equipmentCount === 1){
                                return DeviceManager.deviceList[0].pDeviceInformation.heightOption
                                        === 1 ? true:false
                            }
                        }
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
                x:mode == 1 ? 50 : 31
                y:mode == 1 ? 482 : 553
                width: mode == 1 ?  210 :243
                height: mode == 1 ? 45 : 52
                background: Rectangle{
                    radius: 6
                    color: mode == 1 ? "#0c5696" : pRgb(43, 112, 173)
                }
                contentItem: Text {
                    id: mt1
                    text: "新建模型"
                    font.pixelSize: mode == 1 ? 17:20
                    color: pRgb(153, 204, 255)
                    anchors.centerIn: parent  // 确保文本在按钮内居中对齐
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.family: fontBold
                }
                onClicked: {
                    if(mt1.text === "新建模型"){
                        popup.openPop(3)
                    }
                    else if(mt1.text === "创建模型"){
                        if(DeviceManager.deviceList[0].pDeviceInformation.sample <= listSize){
                            loader.sourceComponent = mode1
                            loader1.sourceComponent = weld1
                            Manual.save()
                            mt1.text = "新建模型"
                            mt2.text = "新增设备"
                            sigUpdateUI(0)
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
                anchors.topMargin: mode == 1 ? 23 : 31
                width: mode == 1 ?  210 :243
                height: mode == 1 ? 45 : 52
                background: Rectangle{
                    radius: 6
                    color: mode == 1 ? "#0c5696" : pRgb(43, 112, 173)
                }
                contentItem: Text {
                    id:mt2
                    anchors.centerIn: parent
                    text:"新增设备"
                    font.pixelSize:mode == 1 ? 17: 20
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
                        width: mode === 1 ? 288:346
                        height: mode === 1 ? 235:283
                        x:mode === 1 ? 269:286
                        y:mode === 1 ? 35:20
                        color: mode === 1 ? "#0c5696" : pRgb(43, 112, 173)
                        revealing:{
                            if(DeviceManager.deviceList[0]){
                                return DeviceManager.deviceList[0].pIO.availabel
                            }
                            else{
                                return true
                            }
                        }
                        eqText1:{
                            if(DeviceManager.deviceList[0]){
                                return DeviceManager.deviceList[0].pDeviceInformation.goodCycles
                            }
                            else{
                                return ""
                            }
                        }
                        eqText2:{
                            if(DeviceManager.deviceList[0]){
                                return DeviceManager.deviceList[0].pDeviceInformation.suspectCycles
                            }
                            else{
                                return ""
                            }
                        }
                        eqText3:{
                            if(DeviceManager.deviceList[0]){
                                return DeviceManager.deviceList[0].pDeviceInformation.notDefinite
                            }
                            else{
                                return ""
                            }
                        }
                        eqText4:{
                            if(DeviceManager.deviceList[0]){
                                return DeviceManager.deviceList[0].pDeviceInformation.goodCycles
                                        + DeviceManager.deviceList[0].pDeviceInformation.notDefinite
                                        +DeviceManager.deviceList[0].pDeviceInformation.suspectCycles
                            }
                            else{
                                return ""
                            }
                        }
                        eqText5:{
                            if(DeviceManager.deviceList[0]){
                                return DeviceManager.deviceList[0].pDeviceInformation.goodRate
                            }
                            else{
                                return ""
                            }
                        }
                    }
                    YieldTrend{
                        id:s6
                        width: mode === 1 ? 514:609
                        height: mode === 1 ? 235:283
                        x:mode === 1 ? 568:645
                        y:mode === 1 ? 35:20
                        color: mode === 1 ? "#0c5696" : pRgb(43, 112, 173)
                        equiInforIndex:1
                    }
                    WeldingTrend{
                        id:s7
                        width: mode === 1 ? 502:596
                        height: mode === 1 ? 311:370
                        x:mode === 1 ? 269:286
                        y:mode === 1 ? 284:318
                        color: mode === 1 ? "#0c5696" : pRgb(43, 112, 173)
                    }
                    AbnormalInfor{
                        id:s8
                        width: mode === 1 ? 303:359
                        height: mode === 1 ? 311:370
                        x:mode === 1 ? 778:895
                        y:mode === 1 ? 284:318
                        color: mode === 1 ? "#0c5696" : pRgb(43, 112, 173)
                    }
                }
            }
            Component{
                id:mode2
                Item {
                    Rectangle{
                        id:rect
                        x:mode === 1 ? 269:287
                        y:mode === 1 ? 36:20
                        width: mode === 1 ? 812 : 964
                        height: mode === 1 ? 560:668
                        color: mode === 1 ? "#0c5696" : pRgb(43, 112, 173)
                        radius: 3
                    }
                    Rectangle{
                        width: mode === 1 ? 808:960
                        height: mode === 1 ? 556:664
                        x:mode === 1 ? 272:289
                        y:mode === 1 ? 37:22
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
                            x:960/8 + 960/8/2-width/2
                            y:11
                            font.pixelSize: 16
                            text: "序号"
                            font.family: fontBold
                            color: pRgb(171, 206, 213)
                        }
                        Text{
                            id:t3
                            x:960/8*2 + 960/8/2-width/2
                            y:11
                            font.pixelSize: 16
                            text: "焊接时间"
                            font.family: fontBold
                            color: pRgb(171, 206, 213)
                        }
                        Text{
                            id:t4
                            x:960/8*3 + 960/8/2-width/2
                            y:11
                            font.pixelSize: 16
                            text: "功率"
                            font.family: fontBold
                            color: pRgb(171, 206, 213)
                        }
                        Text{
                            id:t5
                            x:960/8*4 + 960/8/2-width/2
                            y:11
                            font.pixelSize: 16
                            text: "能量"
                            font.family: fontBold
                            color: pRgb(171, 206, 213)
                        }
                        Text{
                            id:t6
                            x:960/8*5 + 960/8/2-width/2
                            y:11
                            font.pixelSize: 16
                            text: "日期"
                            font.family: fontBold
                            color: pRgb(171, 206, 213)
                        }
                        Text{
                            id:t7
                            x:960/8*6 + 960/8/2-width/2
                            y:11
                            font.pixelSize: 16
                            text: "拉力"
                            font.family: fontBold
                            color: pRgb(171, 206, 213)
                        }
                        Text{
                            id:t8
                            x:960/8*7 + 960/8/2-width/2
                            y:11
                            font.pixelSize: 16
                            text: "残留度"
                            font.family: fontBold
                            color: pRgb(171, 206, 213)
                        }
                        ListView{
                            id: taskplanView
                            width: 960
                            height: 615
                            y:40
                            clip: true
                            model: Manual
                            onCountChanged:{
                                listSize = taskplanView.count
                            }
                            delegate: Rectangle{
                                id: regionItem
                                height: 36
                                width: 960
                                color: index % 2 === 0 ? "#afc3d8" : "#2d71ae"
                                MouseArea {
                                    id: mouseArea
                                    anchors.fill: parent
                                    onClicked: {
                                        taskplanView.currentIndex = index
                                        parameter1 = Manual.data(Manual.index(index,0),QmlEnum._MANUAL_energy)
                                        parameter2 = Manual.data(Manual.index(index,0),QmlEnum._MANUAL_amplitude)
                                        parameter3 = Manual.data(Manual.index(index,0),QmlEnum._MANUAL_pressure)
                                        parameter4 = Manual.data(Manual.index(index,0),QmlEnum._MANUAL_pre_height)
                                        parameter5 = Manual.data(Manual.index(index,0),QmlEnum._MANUAL_post_height)
                                    }
                                }
                                Button{
                                    id:bt
                                    x:960/8/2-width/2
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
                                    x:960/8*1 + 960/8/2-width/2
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.pixelSize: 16
                                    text: serial_number
                                    font.family: fontBold
                                    color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                                }
                                Text{
                                    anchors.verticalCenter: parent.verticalCenter
                                    x:960/8*2 + 960/8/2-width/2
                                    font.pixelSize: 16
                                    text: time
                                    font.family: fontBold
                                    color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                                }
                                Text{
                                    anchors.verticalCenter: parent.verticalCenter
                                    x:960/8*3 + 960/8/2-width/2
                                    font.pixelSize: 16
                                    text: power
                                    font.family: fontBold
                                    color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                                }
                                Text{
                                    anchors.verticalCenter: parent.verticalCenter
                                    x:960/8*4 + 960/8/2-width/2
                                    font.pixelSize: 16
                                    text: energy
                                    font.family: fontBold
                                    color: index % 2 !== 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                                }
                                Text{
                                    anchors.verticalCenter: parent.verticalCenter
                                    x:960/8*5 + 960/8/2-width/2
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
                                    x:960/8*6 + 960/8/2-width/2
                                    horizontalAlignment: TextInput.AlignHCenter
                                    verticalAlignment: TextInput.AlignVCenter
                                    color: index % 2 === 0 ? pRgb(175, 195, 216) : "#014c8d"
                                    font.family: fontBold
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
                                }
                                TextField{
                                    width: 100
                                    height: 33
                                    anchors.verticalCenter: parent.verticalCenter
                                    x:960/8*7 + 960/8/2-width/2
                                    horizontalAlignment: TextInput.AlignHCenter
                                    verticalAlignment: TextInput.AlignVCenter
                                    color: index % 2 === 0 ? pRgb(175, 195, 216) : "#014c8d"
                                    font.family: fontBold
                                    font.pixelSize: 16
                                    text:actual_degree
                                    inputMethodHints: Qt.ImhDigitsOnly
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
    }

    Component{
        id:multipro
        MultideviceProductionModule{
            id:mupMode
            width: 1280
            height: 740
            itemCount:equipmentCount
        }
    }

    Component{
        id:swipe
        SwipeProductionModule{
            id:mupMode
            width: 1280
            height: 740
        }
    }

    Text {
        id: version
        color: "#639ed6"
        x:895
        y:718
        font.family: fontBold
        font.pixelSize: 14
        text: qsTr("系统版本号: v2.0.1")
    }
    // 显示时间的文本
    Text {
        id: timeText
        anchors.left: version.right
        anchors.top: version.top
        anchors.leftMargin: 27
        font.pixelSize: 14
        font.family: fontBold
        color: "#639ed6"
        text: getCurrentTime()

        // 定时器每秒更新一次
        Timer {
            interval: 1  // 1秒
            repeat: true
            running: true
            onTriggered: {
                timeText.text = getCurrentTime()
            }
        }
    }
}
