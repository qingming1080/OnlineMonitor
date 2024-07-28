import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.5
import Device 1.0
import DeviceInformation 1.0
import IO 1.0
import QmlEnum 1.0
//系统配置
Rectangle {
    id: sysUI
    property int itemCount: equipmentCount
    property int currIndex: 0
    property int currentConfigId: 0 // 多设备时放大界面数据判断
    property bool musysTmp1: false
    property bool musysTmp2: false
    property bool musysTmp3: false
    property bool musysTmp4: false

    property bool undetermined1: false
    property bool undetermined2: false
    property bool undetermined3: false
    property bool undetermined4: false
    property bool undeterMined: {
        if(equipmentCount === 1){
            if(DeviceManager.deviceList[0]){
                return DeviceManager.deviceList[0].pIO.availabel
            }
            else{
                return false
            }
        }
        else{
            if(DeviceManager.deviceList[currentConfigId-1]){
                return DeviceManager.deviceList[currentConfigId-1].pIO.availabel
            }
            else{
                return false
            }
        }
    }
    property bool altitudMode:{
        if(DeviceManager.deviceList[0]){
            return DeviceManager.deviceList[0].pDeviceInformation.heightOption
                    === 1 ? true:false
        }
        else{
            return false
        }
    }
    property bool oneself: false
    property bool btnDefault: false
    property var sysViews: []
    Component.onCompleted: {
        loadViewsys(1,syscfg)
    }

    color: pRgb(153, 204, 255)

    signal sigSysCheck(var id)
    function sysCheck(id){
        sigSysCheck(id)
    }
    function loadViewsys(viewName, component) {
        loader1.pop()
        if (sysViews[viewName]) {
            // 如果视图已缓存，直接显示
            loader1.push(sysViews[viewName]);
        } else {
            // 创建视图并缓存
            var newItem = component.createObject(loader1);
            sysViews[viewName] = newItem;
            loader1.push(newItem);
        }
    }
    Connections{
        target: window
        function onSigSysConfig(){
            Qt.callLater(configCheck)
        }
    }

    function configCheck(){
        if(isAdd){
            loadViewsys(1,syscfg)
        }
        else{
            if(itemCount == 1){
                loadViewsys(1,syscfg)
            }
            else{
                loadViewsys(2,musys)
                currIndex = 0
            }
        }
    }

    onItemCountChanged: {
        if(itemCount == 1){
            loadViewsys(1,syscfg)
        }
        else if(itemCount == 2){
            musysTmp1 = true
            musysTmp2 = true
            musysTmp3 = false
            musysTmp4 = false
        }
        else if(itemCount == 3){
            musysTmp1 = true
            musysTmp2 = true
            musysTmp3 = true
            musysTmp4 = false
        }
        else if(itemCount == 4){
            musysTmp1 = true
            musysTmp2 = true
            musysTmp3 = true
            musysTmp4 = true
        }
    }

    StackView{
        id:loader1
        //禁用动画
        pushEnter: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 0
                to:1
                duration: 0
            }
        }

        // 退出项的动画过渡
        pushExit: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 1
                to:0
                duration: 0
            }
        }

        // 退出进入项的动画过渡
        popEnter: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 0
                to:1
                duration: 0
            }
        }

        // 退出进入项的动画过渡
        popExit: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 1
                to:0
                duration: 0
            }
        }
    }

    Component{
        id:syscfg
        Item {
            Rectangle{
                x:30
                y:25
                width: 1221
                height: 613
                color: pRgb(43, 112, 173)
                radius: 3
                Text {
                    id: name
                    text: qsTr("设备配置")
                    color: pRgb(153, 204, 255)
                    font.family: fontBold
                    font.pixelSize: 20
                    x:33
                    y:16
                }
                Rectangle{
                    y:46
                    width: 126
                    height: 1
                    color: pRgb(174, 210, 216)
                }
                Text {
                    id: s1
                    x:35
                    y:74
                    text: qsTr("最大生产批量")
                    color: pRgb(177, 213, 219)
                    font.family: fontBold
                    font.pixelSize: 16
                }
                TextField{
                    id:t1
                    width: 243
                    height: 40
                    anchors.top: parent.top
                    anchors.topMargin: 66
                    anchors.left: s1.right
                    anchors.leftMargin: 37
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    color: pRgb(43, 112, 173)
                    font.family: fontBold
                    font.pixelSize: 16
                    inputMethodHints: Qt.ImhDigitsOnly

                    background: Rectangle{
                        radius: 6
                        border.width: 3
                        border.color: "#99ccff"
                    }
                    text:{
                        if(equipmentCount === 1){
                            if(DeviceManager.deviceList[0]){
                                DeviceManager.deviceList[0].pDeviceInformation.maxBacth
                            }
                            else{
                                return ""
                            }
                        }
                        else{
                            if(DeviceManager.deviceList[currentConfigId-1]){
                                DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.maxBacth
                            }
                            else{
                                return ""
                            }
                        }
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            t1.focus = true
                            keyboardYype = 0
                        }
                    }
                }

                Text {
                    id: s2
                    text: qsTr("学习样本数")
                    color: pRgb(177, 213, 219)
                    font.family: fontBold
                    font.pixelSize: 16
                    anchors.left: s1.left
                    anchors.top: s1.bottom
                    anchors.topMargin: 46
                }
                TextField{
                    id:t2
                    width: 243
                    height: 40
                    anchors.top: t1.bottom
                    anchors.topMargin: 30
                    anchors.left: t1.left
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    color: pRgb(43, 112, 173)
                    font.family: fontBold
                    font.pixelSize: 16
                    inputMethodHints: Qt.ImhDigitsOnly
                    background: Rectangle{
                        radius: 6
                        border.width: 3
                        border.color: "#99ccff"
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            t2.focus = true
                            keyboardYype = 0
                        }
                    }
                    text:{
                        if(equipmentCount === 1){
                            if(DeviceManager.deviceList[0]){
                                DeviceManager.deviceList[0].pDeviceInformation.sample
                            }
                            else{
                                return ""
                            }
                        }
                        else{
                            if(DeviceManager.deviceList[currentConfigId-1]){
                                DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.sample
                            }
                            else{
                                return ""
                            }
                        }
                    }
                }
                Text {
                    id: s3
                    text: qsTr("良率下限")
                    color: pRgb(177, 213, 219)
                    font.family: fontBold
                    font.pixelSize: 16
                    anchors.left: s2.left
                    anchors.top: s2.bottom
                    anchors.topMargin: 46
                }
                TextField{
                    id:t3
                    width: 243
                    height: 40
                    anchors.top: t2.bottom
                    anchors.topMargin: 30
                    anchors.left: t2.left
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    color: pRgb(43, 112, 173)
                    font.family: fontBold
                    font.pixelSize: 16
                    inputMethodHints: Qt.ImhDigitsOnly
                    background: Rectangle{
                        radius: 6
                        border.width: 3
                        border.color: "#99ccff"
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            t3.focus = true
                            keyboardYype = 0
                        }
                    }
                    text:{
                        if(equipmentCount === 1){
                            if(DeviceManager.deviceList[0]){
                                DeviceManager.deviceList[0].pDeviceInformation.lowerLimit
                            }
                            else{
                                return ""
                            }
                        }
                        else{
                            if(DeviceManager.deviceList[currentConfigId-1]){
                                DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.lowerLimit
                            }
                            else{
                                return ""
                            }
                        }
                    }
                }
                Text {
                    id: s4
                    text: qsTr("高度模式")
                    color: pRgb(177, 213, 219)
                    font.family: fontBold
                    font.pixelSize: 16
                    anchors.left: s3.left
                    anchors.top: s3.bottom
                    anchors.topMargin: 51
                }
                Text {
                    id: s5
                    text: qsTr("启动")
                    color: pRgb(177, 213, 219)
                    font.family: fontBold
                    font.pixelSize: 16
                    anchors.top: s4.top
                    anchors.left: s4.right
                    anchors.leftMargin: 69
                }
                RadioButton{
                    id:bt1
                    width: 30
                    height: 30
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.leftMargin: 214
                    anchors.topMargin: 283
                    checked: altitudMode
                    indicator: Rectangle
                    {
                        width: 30
                        height: 30
                        radius: 15
                        color: altitudMode ? "#0d988c" : pRgb(232, 232, 232)
                        border.color: "#b1d5db"
                        border.width: 2
                    }
                    onPressed: {
                        if(equipmentCount > 1){
                            sigUndetermined(currentConfigId)
                        }
                        if(equipmentCount === 1){
                            DeviceManager.deviceList[0].pDeviceInformation.setHeightOption(1)
                        }
                        else{
                            DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.setHeightOption(1)
                        }
                    }
                }
                Text {
                    id: s6
                    text: qsTr("关闭")
                    color: pRgb(177, 213, 219)
                    font.family: fontBold
                    font.pixelSize: 16
                    anchors.top: s5.top
                    anchors.left: s5.right
                    anchors.leftMargin: 88
                }
                RadioButton{
                    id:bt2
                    width: 30
                    height: 30
                    anchors.left: bt1.right
                    anchors.top: bt1.top
                    anchors.leftMargin: 90
                    checked: !altitudMode
                    indicator: Rectangle
                    {
                        width: 30
                        height: 30
                        radius: 15
                        color: !altitudMode ? "#0d988c" : pRgb(232, 232, 232)
                        border.color: "#b1d5db"
                        border.width: 2
                    }
                    onPressed: {
                        if(equipmentCount === 1){
                            DeviceManager.deviceList[0].pDeviceInformation.setHeightOption(0)
                        }
                        else{
                            DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.setHeightOption(0)
                        }
                    }
                }
                Text {
                    id: s7
                    text: qsTr("是否开启待定")
                    color: "#99ccff"
                    font.family: fontBold
                    font.pixelSize: 20
                    x:110
                    y:362
                }
                Switch{
                    id:ctl
                    x:269
                    y:356
                    onPressed: {
                        if(equipmentCount === 1){
                            DeviceManager.deviceList[0].pIO.setAvailabel(!ctl.checked)
                        }
                        else{
                            DeviceManager.deviceList[currentConfigId-1].pIO.setAvailabel(!ctl.checked)
                        }

                    }

                    indicator: Rectangle{
                        id:indicator
                        implicitWidth: 150
                        implicitHeight:35
                        x:ctl.leftPadding
                        y:parent.height / 2 - height / 2
                        border.width: 3
                        radius: 20
                        color: pRgb(232, 232, 232)
                        border.color: "#99ccff"
                        //小圆点
                        Rectangle{
                            id:smallRect
                            width: 72
                            height: 28
                            radius: 20
                            border.width: 3
                            color: "#2b70ad"
                            border.color: "#99ccff"
                            anchors.verticalCenter: parent.verticalCenter
                            //改变小圆点位置
                            NumberAnimation on x{
                                to:smallRect.width
                                running: undeterMined? true : false
                                duration: 0
                            }
                            NumberAnimation on x{
                                to:6
                                running: undeterMined? false : true;
                                duration: 0
                            }
                        }
                        Text {
                            anchors.left: parent.left
                            anchors.top: parent.top
                            anchors.topMargin: 5
                            anchors.leftMargin: 25
                            text: qsTr("关闭")
                            color: undeterMined? pRgb(43, 112, 173) : "#e5e6e7"
                            font.family: fontBold
                            font.pixelSize: 16
                        }
                        Text {
                            anchors.right: parent.right
                            anchors.top: parent.top
                            anchors.topMargin: 5
                            anchors.rightMargin: 25
                            text: qsTr("启动")
                            color: undeterMined? "#e5e6e7" : pRgb(43, 112, 173)
                            font.family: fontBold
                            font.pixelSize: 16
                        }
                    }
                }
                Text {
                    id: s8
                    text: currentConfigId === 1 ? "PIN1" : currentConfigId === 2 ? "PIN4" :
                                                                                   currentConfigId === 3 ? "PIN7" : currentConfigId === 4 ? "PIN10" : "PIN1"
                    color: pRgb(177, 213, 219)
                    font.family: fontBold
                    font.pixelSize: 16
                    x:103
                    y:440
                }
                Text {
                    id: s9
                    text: currentConfigId === 1 ? "PIN2" : currentConfigId === 2 ? "PIN5" :
                                                                                   currentConfigId === 3 ? "PIN8" : currentConfigId === 4 ? "PIN11" : "PIN2"
                    color: pRgb(177, 213, 219)
                    font.family: fontBold
                    font.pixelSize: 16
                    anchors.left: s8.left
                    anchors.top: s8.bottom
                    anchors.topMargin: 20
                }
                Text {
                    id: s10
                    text: currentConfigId === 1 ? "PIN3" : currentConfigId === 2 ? "PIN6" :
                                                                                   currentConfigId === 3 ? "PIN9" : currentConfigId === 4 ? "PIN12" : "PIN3"
                    color: pRgb(177, 213, 219)
                    font.family: fontBold
                    font.pixelSize: 16
                    anchors.left: s9.left
                    anchors.top: s9.bottom
                    anchors.topMargin: 20
                }
                Image {
                    id: im1
                    source: "qrc:/image/alarm.png"
                    x:197
                    y:440
                }
                Image {
                    id: im2
                    source: "qrc:/image/restoration.png"
                    anchors.left: im1.left
                    anchors.top: im1.bottom
                    anchors.topMargin: 13
                    anchors.leftMargin: -2
                }
                Image {
                    id: im3
                    width: 30
                    height: 30
                    source: !undeterMined ? "qrc:/image/undetermined1.png" : "qrc:/image/undetermined.png"
                    anchors.left: im2.left
                    anchors.top: im2.bottom
                    anchors.topMargin: 13
                }
                Text {
                    id: s11
                    text: qsTr("报警")
                    color: pRgb(177, 213, 219)
                    font.family: fontBold
                    font.pixelSize: 16
                    anchors.top: s8.top
                    anchors.left: s8.right
                    anchors.leftMargin: 139
                }
                Text {
                    id: s12
                    text: qsTr("复位")
                    color: pRgb(177, 213, 219)
                    font.family: fontBold
                    font.pixelSize: 16
                    anchors.top: s9.top
                    anchors.left: s9.right
                    anchors.leftMargin: 139
                }
                Text {
                    id: s13
                    text: qsTr("待定")
                    color: pRgb(177, 213, 219)
                    font.family: fontBold
                    font.pixelSize: 16
                    anchors.top: s10.top
                    anchors.left: s10.right
                    anchors.leftMargin: 139
                }
                Text {
                    id: s14
                    x:508
                    y:74
                    text: qsTr("设备名称")
                    color: pRgb(177, 213, 219)
                    font.family: fontBold
                    font.pixelSize: 16
                }
                TextField{
                    id:t4
                    width: 243
                    height: 40
                    anchors.top: parent.top
                    anchors.topMargin: 66
                    anchors.left: s14.right
                    anchors.leftMargin: 23
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    color: pRgb(43, 112, 173)
                    font.family: fontBold
                    font.pixelSize: 16
                    background: Rectangle{
                        radius: 6
                        border.width: 3
                        border.color: "#99ccff"
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            t4.focus = true
                            keyboardYype = 1
                        }
                    }
                    text:{
                        if(equipmentCount === 1){
                            if(DeviceManager.deviceList[0]){
                                return DeviceManager.deviceList[0].pDeviceInformation.name
                            }
                            else{
                                return ""
                            }
                        }
                        else{
                            if(DeviceManager.deviceList[currentConfigId-1]){
                                return DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.name
                            }
                            else{
                                return ""
                            }
                        }
                    }
                }
                Text {
                    id: s15
                    text: qsTr("设备型号")
                    color: pRgb(177, 213, 219)
                    font.family: fontBold
                    font.pixelSize: 16
                    anchors.top: s14.top
                    anchors.left: s14.right
                    anchors.leftMargin: 293
                }
                CustomComboBox{
                    id:com1
                    width: 243
                    height: 40
                    anchors.top: parent.top
                    anchors.topMargin: 66
                    anchors.left: s15.right
                    anchors.leftMargin: 23
                    model: ["L20-VG", "L20-TS", "20DP", "20MA", "自定义"]
                    displayText:{
                        if(equipmentCount === 1){
                            if(DeviceManager.deviceList[0]){
                                return DeviceManager.deviceList[0].pDeviceInformation.model
                            }
                            else{
                                return ""
                            }
                        }
                        else{
                            if(DeviceManager.deviceList[currentConfigId-1]){
                                return DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.model
                            }
                            else{
                                return ""
                            }
                        }
                    }
                    onDataAlter: {
                        if(equipmentCount === 1){
                            DeviceManager.deviceList[0].pDeviceInformation.setModel(com1.currentText)
                        }
                        else{
                            DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.setModel(com1.currentText)
                        }
                    }
                }
                Switch{
                    id:ctl1
                    x:713
                    y:147
                    onClicked: {
                        if(isAdd){

                        }
                        if(equipmentCount === 1){
                            if(ctl1.checked){
                                DeviceManager.deviceList[0].pDeviceInformation.setConnectType(2)
                            }
                            else{
                                DeviceManager.deviceList[0].pDeviceInformation.setConnectType(1)
                            }
                        }
                        else{
                            if(ctl1.checked){
                                DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.setConnectType(2)
                            }
                            else{
                                DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.setConnectType(1)
                            }
                        }
                    }
                    indicator: Rectangle{
                        id:indicator1
                        implicitWidth: 339
                        implicitHeight:40
                        x:ctl1.leftPadding
                        y:parent.height / 2 - height / 2
                        border.width: 3
                        radius: 20
                        color: pRgb(232, 232, 232)
                        border.color: "#99ccff"
                        //小圆点
                        Rectangle{
                            id:smallRect1
                            width: 163
                            height: 35
                            radius: 20
                            border.width: 3
                            color: "#2b70ad"
                            border.color: "#99ccff"
                            anchors.verticalCenter: parent.verticalCenter
                            //改变小圆点位置
                            NumberAnimation on x{
                                to:smallRect1.width
                                running: {
                                    if(isAdd){
                                        return ctl1.checked
                                    }
                                    else if(equipmentCount === 1){
                                        return DeviceManager.deviceList[0].pDeviceInformation.connectType !== 1? true : false
                                    }
                                    else{
                                        return DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.connectType !== 1? true : false
                                    }
                                }
                                duration: 0
                            }
                            NumberAnimation on x{
                                to:8
                                running: {
                                    if(isAdd){
                                        return !ctl1.checked
                                    }
                                    else if(equipmentCount === 1){
                                        return DeviceManager.deviceList[0].pDeviceInformation.connectType !== 1? false : true
                                    }
                                    else{
                                        return DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.connectType !== 1? false : true
                                    }
                                }
                                duration: 0
                            }
                        }
                        Text {
                            anchors.left: parent.left
                            anchors.top: parent.top
                            anchors.topMargin: 7
                            anchors.leftMargin: 63
                            text: qsTr("网络")
                            color: {
                                if(isAdd){
                                    return ctl1.checked ? pRgb(43, 112, 173) : "#e5e6e7"
                                }
                                else if(equipmentCount === 1){
                                    return DeviceManager.deviceList[0].pDeviceInformation.connectType !== 1 ? pRgb(43, 112, 173) : "#e5e6e7"
                                }
                                else{
                                    return DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.connectType !== 1 ? pRgb(43, 112, 173) : "#e5e6e7"
                                }
                            }
                            font.family: fontBold
                            font.pixelSize: 16
                        }
                        Text {
                            anchors.right: parent.right
                            anchors.top: parent.top
                            anchors.topMargin: 7
                            anchors.rightMargin: 63
                            text: qsTr("RS232")
                            color: {
                                if(isAdd){
                                    return !ctl1.checked ? pRgb(43, 112, 173) : "#e5e6e7"
                                }
                                else if(equipmentCount === 1){
                                    return DeviceManager.deviceList[0].pDeviceInformation.connectType !== 1? "#e5e6e7" : pRgb(43, 112, 173)
                                }
                                else{
                                    return DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.connectType !== 1? "#e5e6e7" : pRgb(43, 112, 173)
                                }
                            }
                            font.family: fontBold
                            font.pixelSize: 16
                        }
                    }
                }
                Loader{
                    id:loader
                    sourceComponent: {
                        if(isAdd){
                            return ctl1.checked ? rect1 : rect2
                        }
                        else if(equipmentCount === 1){
                            return DeviceManager.deviceList[0].pDeviceInformation.connectType === 1 ? rect1 : rect2
                        }
                        else{
                            return DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.connectType === 1 ? rect1 : rect2
                        }
                    }
                }
                Component{
                    id:rect1
                    Rectangle{
                        x:595
                        y:226
                        width: 600
                        height: 343
                        radius: 6
                        color: "#78b0e7"
                        Text {
                            id: s16
                            text: qsTr("网络端口")
                            color: pRgb(43, 112, 173)
                            font.family: fontBold
                            font.pixelSize: 16
                            x:101
                            y:63
                        }
                        Text {
                            id: s17
                            text: qsTr("服务器端口")
                            color: pRgb(43, 112, 173)
                            font.family: fontBold
                            font.pixelSize: 16
                            anchors.left: s16.left
                            anchors.top: s16.bottom
                            anchors.topMargin: 33
                        }
                        Text {
                            id: s18
                            text: qsTr("设备IP地址")
                            color: pRgb(43, 112, 173)
                            font.family: fontBold
                            font.pixelSize: 16
                            anchors.left: s17.left
                            anchors.top: s17.bottom
                            anchors.topMargin: 33
                        }
                        Text {
                            id: s19
                            text: qsTr("本地IP地址")
                            color: pRgb(43, 112, 173)
                            font.family: fontBold
                            font.pixelSize: 16
                            anchors.left: s18.left
                            anchors.top: s18.bottom
                            anchors.topMargin: 33
                        }
                        CustomComboBox{
                            id:com2
                            width: 243
                            height: 40
                            x:233
                            y:55
                            model: ["ETH0", "ETH1", "ETH2", "ETH3"]
                            displayText: {
                                if(isAdd){
                                    return "ETH0"
                                }
                                else if(equipmentCount === 1){
                                    if(DeviceManager.deviceList[0].pDeviceInformation.connectID === 1){
                                        return "ETH0"
                                    }
                                    else if(DeviceManager.deviceList[0].pDeviceInformation.connectID === 2){
                                        return "ETH1"
                                    }
                                    else if(DeviceManager.deviceList[0].pDeviceInformation.connectID === 3){
                                        return "ETH2"
                                    }
                                    else if(DeviceManager.deviceList[0].pDeviceInformation.connectID === 4){
                                        return "ETH3"
                                    }
                                }
                                else{
                                    if(DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.connectID === 1){
                                        return "ETH0"
                                    }
                                    else if(DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.connectID === 2){
                                        return "ETH1"
                                    }
                                    else if(DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.connectID === 3){
                                        return "ETH2"
                                    }
                                    else if(DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.connectID === 4){
                                        return "ETH3"
                                    }
                                }
                            }
                            onDataAlter: {
                                if(equipmentCount === 1){
                                    DeviceManager.deviceList[0].pDeviceInformation.setConnectID(com2.currentIndex+1)
                                }
                                else{
                                    DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.setConnectID(com2.currentIndex+1)
                                }


                            }
                        }
                        TextField{
                            id:t5
                            width: 243
                            height: 40
                            anchors.top: com2.bottom
                            anchors.topMargin: 17
                            anchors.left: com2.left
                            horizontalAlignment: TextInput.AlignHCenter
                            verticalAlignment: TextInput.AlignVCenter
                            color: pRgb(43, 112, 173)
                            font.family: fontBold
                            font.pixelSize: 16
                            inputMethodHints: Qt.ImhDigitsOnly
                            background: Rectangle{
                                radius: 6
                                border.width: 3
                                border.color: "#99ccff"
                            }
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    t5.focus = true
                                    keyboardYype = 0
                                }
                            }
                            text: {
                                if(com2.displayText === "ETH0"){
                                    return NetworkModel.getDataByWelderID(1,QmlEnum.NETWORK_server_port)
                                }
                                else if(com2.displayText === "ETH1"){
                                    return NetworkModel.getDataByWelderID(2,QmlEnum.NETWORK_server_port)
                                }
                                else if(com2.displayText === "ETH2"){
                                    return NetworkModel.getDataByWelderID(3,QmlEnum.NETWORK_server_port)
                                }
                                else if(com2.displayText === "ETH3"){
                                    return NetworkModel.getDataByWelderID(4,QmlEnum.NETWORK_server_port)
                                }
                            }
                        }
                        TextField{
                            id:t6
                            width: 243
                            height: 40
                            anchors.top: t5.bottom
                            anchors.topMargin: 17
                            anchors.left: t5.left
                            horizontalAlignment: TextInput.AlignHCenter
                            verticalAlignment: TextInput.AlignVCenter
                            color: pRgb(43, 112, 173)
                            font.family: fontBold
                            font.pixelSize: 16
                            inputMethodHints: Qt.ImhDigitsOnly
                            background: Rectangle{
                                radius: 6
                                border.width: 3
                                border.color: "#99ccff"
                            }
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    t6.focus = true
                                    keyboardYype = 0
                                }
                            }
                            text:{
                                if(com2.displayText === "ETH0"){
                                    return NetworkModel.getDataByWelderID(1,QmlEnum.NETWORK_remote_ip)
                                }
                                else if(com2.displayText === "ETH1"){
                                    return NetworkModel.getDataByWelderID(2,QmlEnum.NETWORK_remote_ip)
                                }
                                else if(com2.displayText === "ETH2"){
                                    return NetworkModel.getDataByWelderID(3,QmlEnum.NETWORK_remote_ip)
                                }
                                else if(com2.displayText === "ETH3"){
                                    return NetworkModel.getDataByWelderID(4,QmlEnum.NETWORK_remote_ip)
                                }
                            }
                        }
                        TextField{
                            id:t7
                            width: 243
                            height: 40
                            anchors.top: t6.bottom
                            anchors.topMargin: 17
                            anchors.left: t6.left
                            horizontalAlignment: TextInput.AlignHCenter
                            verticalAlignment: TextInput.AlignVCenter
                            color: pRgb(43, 112, 173)
                            font.family: fontBold
                            font.pixelSize: 16
                            inputMethodHints: Qt.ImhDigitsOnly
                            background: Rectangle{
                                radius: 6
                                border.width: 3
                                border.color: "#99ccff"
                            }
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    t7.focus = true
                                    keyboardYype = 0
                                }
                            }
                            text:{
                                if(com2.displayText === "ETH0"){
                                    return NetworkModel.getDataByWelderID(1,QmlEnum.NETWORK_local_ip)
                                }
                                else if(com2.displayText === "ETH1"){
                                    return NetworkModel.getDataByWelderID(2,QmlEnum.NETWORK_local_ip)
                                }
                                else if(com2.displayText === "ETH2"){
                                    return NetworkModel.getDataByWelderID(3,QmlEnum.NETWORK_local_ip)
                                }
                                else if(com2.displayText === "ETH3"){
                                    return NetworkModel.getDataByWelderID(4,QmlEnum.NETWORK_local_ip)
                                }
                            }
                        }
                    }
                }
                Component{
                    id:rect2
                    Rectangle{
                        x:595
                        y:226
                        width: 600
                        height: 343
                        radius: 6
                        color: "#78b0e7"
                        Text {
                            id: s20
                            text: qsTr("端口")
                            color: pRgb(43, 112, 173)
                            font.family: fontBold
                            font.pixelSize: 16
                            x:101
                            y:48
                        }
                        Text {
                            id: s21
                            text: qsTr("波特率")
                            color: pRgb(43, 112, 173)
                            font.family: fontBold
                            font.pixelSize: 16
                            x:101
                            y:105
                        }
                        Text {
                            id: s22
                            text: qsTr("数据位")
                            color: pRgb(43, 112, 173)
                            font.family: fontBold
                            font.pixelSize: 16
                            x:101
                            y:159
                        }
                        Text {
                            id: s23
                            text: qsTr("奇偶校验位")
                            color: pRgb(43, 112, 173)
                            font.family: fontBold
                            font.pixelSize: 16
                            x:101
                            y:214
                        }
                        Text {
                            id: s24
                            text: qsTr("停止位")
                            color: pRgb(43, 112, 173)
                            font.family: fontBold
                            font.pixelSize: 16
                            x:101
                            y:273
                        }
                        CustomComboBox{
                            id:com3
                            width: 243
                            height: 40
                            x:233
                            y:40
                            model: ["COM1", "COM2"]
                            displayText: {
                                if(isAdd){
                                    return "ETH0"
                                }
                                else if(equipmentCount === 1){
                                    if(DeviceManager.deviceList[0].pDeviceInformation.connectID === 1){
                                        return "COM1"
                                    }
                                    else if(DeviceManager.deviceList[0].pDeviceInformation.connectID === 2){
                                        return "COM2"
                                    }
                                }
                                else{
                                    if(DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.connectID === 1){
                                        return "COM1"
                                    }
                                    else if(DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.connectID === 2){
                                        return "COM2"
                                    }
                                }
                            }
                            onDataAlter: {
                                if(equipmentCount === 1){
                                    DeviceManager.deviceList[0].pDeviceInformation.setConnectID(com3.currentIndex+1)
                                }
                                else{
                                    DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.setConnectID(com3.currentIndex+1)
                                }
                            }
                        }
                        CustomComboBox{
                            id:com4
                            width: 243
                            height: 40
                            x:233
                            y:97
                            model: ["2400", "9600", "19200","115200"]
                            displayText:{
                                if(com3.displayText === "COM1"){
                                    return RS232Model.getDataByWelderID(1,QmlEnum.RS232_baud_rate)
                                }
                                else if(com3.displayText === "COM2"){
                                    return RS232Model.getDataByWelderID(2,QmlEnum.RS232_baud_rate)
                                }
                            }
                            onDataAlter: {
                                if(com3.displayText === "COM1"){
                                    RS232Model.setRS232Data(1,QmlEnum.RS232_baud_rate,currentText)
                                }
                                else if(com3.displayText === "COM2"){
                                    RS232Model.setRS232Data(2,QmlEnum.RS232_baud_rate,currentText)
                                }
                                com4.displayText = currentText
                            }
                        }
                        CustomComboBox{
                            id:com5
                            width: 243
                            height: 40
                            x:233
                            y:151
                            model: ["7bit", "8bit"]
                            displayText:{
                                if(com3.displayText === "COM1"){
                                    return RS232Model.getDataByWelderID(1,QmlEnum.RS232_data_bit)
                                }
                                else if(com3.displayText === "COM2"){
                                    return RS232Model.getDataByWelderID(2,QmlEnum.RS232_data_bit)
                                }
                            }
                            onDataAlter: {
                                if(com3.displayText === "COM1"){
                                    if(com7.currentIndex === 0){
                                        RS232Model.setRS232Data(1,QmlEnum.RS232_data_bit,7)
                                    }
                                    else if(com7.currentIndex === 1){
                                        RS232Model.setRS232Data(1,QmlEnum.RS232_data_bit,8)
                                    }
                                }
                                else if(com3.displayText === "COM2"){
                                    if(com7.currentIndex === 0){
                                        RS232Model.setRS232Data(2,QmlEnum.RS232_data_bit,7)
                                    }
                                    else if(com7.currentIndex === 1){
                                        RS232Model.setRS232Data(2,QmlEnum.RS232_data_bit,8)
                                    }
                                }
                                com5.displayText = currentText
                            }
                        }
                        CustomComboBox{
                            id:com6
                            width: 243
                            height: 40
                            x:233
                            y:206
                            model: ["None", "Odd", "Even"]
                            displayText: {
                                if(com3.displayText === "COM1"){
                                    return RS232Model.getDataByWelderID(1,QmlEnum.RS232_parity_bit)
                                }
                                else if(com3.displayText === "COM2"){
                                    return RS232Model.getDataByWelderID(2,QmlEnum.RS232_parity_bit)
                                }
                            }
                            onDataAlter: {
                                if(com3.displayText === "COM1"){
                                    RS232Model.setRS232Data(1,QmlEnum.RS232_parity_bit,currentText)
                                }
                                else if(com3.displayText === "COM2"){
                                    RS232Model.setRS232Data(2,QmlEnum.RS232_parity_bit,currentText)
                                }
                                com6.displayText = currentText
                            }
                        }
                        CustomComboBox{
                            id:com7
                            width: 243
                            height: 40
                            x:233
                            y:265
                            model: ["1bit", "1.5bit", "2bit"]
                            displayText:{
                                if(com3.displayText === "COM1"){
                                    return RS232Model.getDataByWelderID(1,QmlEnum.RS232_stop_bit)
                                }
                                else if(com3.displayText === "COM2"){
                                    return RS232Model.getDataByWelderID(2,QmlEnum.RS232_stop_bit)
                                }
                            }
                            onDataAlter: {
                                if(com3.displayText === "COM1"){
                                    if(com7.currentIndex === 0){
                                        RS232Model.setRS232Data(1,QmlEnum.RS232_stop_bit,1)
                                    }
                                    else if(com7.currentIndex === 1){
                                        RS232Model.setRS232Data(1,QmlEnum.RS232_stop_bit,1.5)
                                    }
                                    else if(com7.currentIndex === 2){
                                        RS232Model.setRS232Data(1,QmlEnum.RS232_stop_bit,2)
                                    }
                                }
                                else if(com3.displayText === "COM2"){
                                    if(com7.currentIndex === 0){
                                        RS232Model.setRS232Data(2,QmlEnum.RS232_stop_bit,1)
                                    }
                                    else if(com7.currentIndex === 1){
                                        RS232Model.setRS232Data(2,QmlEnum.RS232_stop_bit,1.5)
                                    }
                                    else if(com7.currentIndex === 2){
                                        RS232Model.setRS232Data(2,QmlEnum.RS232_stop_bit,2)
                                    }
                                }
                                com7.displayText = currentText
                            }
                        }
                    }
                }
                Button{
                    id:full
                    width: 30
                    height: 30
                    x:1170
                    y:10
                    visible: equipmentCount > 1 ? true : false
                    background: Rectangle{
                        color: "transparent"
                        Image {
                            anchors.fill: parent
                            source: "qrc:/image/reduce.png"
                        }
                    }
                    onPressed: {
                        loadViewsys(2,musys)
                    }
                }
            }
            Button{
                id:bt3
                x:516
                y:677
                width: 243
                height: 52
                background: Rectangle{
                    radius: 6
                    color: pRgb(43, 112, 173)
                }
                contentItem: Text {
                    text: "保存"
                    font.pixelSize: 20
                    color: pRgb(153, 204, 255)
                    anchors.centerIn: parent  // 确保文本在按钮内居中对齐
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.family: fontBold
                }
                onPressed: {
                    if(isAdd){
                        if(!oneself){
                            switchUI(1)
                        }
                        else{
                            loadViewsys(2,musys)
                        }
                        DeviceManager.addDevice()
                        oneself = false
                        sigUndetermined(1)
                    }
                    if(full.visible){//设置多设备时配置存储
                        DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.setMaxBacth(t1.text)
                        DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.setSample(t2.text)
                        DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.setLowerLimit(t3.text)
                        DeviceManager.deviceList[currentConfigId-1].pDeviceInformation.setName(t4.text)
                    }
                    else{
                        DeviceManager.deviceList[0].pDeviceInformation.setMaxBacth(t1.text)
                        DeviceManager.deviceList[0].pDeviceInformation.setSample(t2.text)
                        DeviceManager.deviceList[0].pDeviceInformation.setLowerLimit(t3.text)
                        DeviceManager.deviceList[0].pDeviceInformation.setName(t4.text)
                    }
                }
            }
        }
    }
    Component{
        id:musys
        Item{
            MultideviceSystemConfig{
                id:s1
                x:41
                y:68
                sysCurrIndex:1
                heightOpation:{
                    if(DeviceManager.deviceList[0]){
                        return DeviceManager.deviceList[0].pDeviceInformation.heightOption
                                === 1 ? true:false
                    }
                    else{
                        return false
                    }
                }
                visible: musysTmp1
                eqText1:{
                    if(DeviceManager.deviceList[0]){
                        DeviceManager.deviceList[0].pDeviceInformation.name
                    }
                    else{
                        return ""
                    }
                }
                eqText2:{
                    if(DeviceManager.deviceList[0]){
                        DeviceManager.deviceList[0].pDeviceInformation.model
                    }
                    else{
                        return ""
                    }
                }
                eqText3:{
                    if(DeviceManager.deviceList[0]){
                        DeviceManager.deviceList[0].pDeviceInformation.connectType === 1  ? "网络连接" : "RS232"
                    }
                    else{
                        return ""
                    }
                }
                eqText4:{
                    if(DeviceManager.deviceList[0]){
                        DeviceManager.deviceList[0].pDeviceInformation.state
                    }
                    else{
                        return ""
                    }
                }
                onSigAltitudeModel: {
                    if(visible){
                        altitudeModel1 = tmp
                    }
                }
            }
            MultideviceSystemConfig{
                id:s2
                x:347
                y:68
                heightOpation:{
                    if(DeviceManager.deviceList[1]){
                        return DeviceManager.deviceList[1].pDeviceInformation.heightOption
                                === 1 ? true:false
                    }
                    else{
                        return false
                    }
                }
                sysCurrIndex:2
                visible: musysTmp2
                eqText1:{
                    if(DeviceManager.deviceList[1]){
                        DeviceManager.deviceList[1].pDeviceInformation.name
                    }
                    else{
                        return ""
                    }
                }
                eqText2:{
                    if(DeviceManager.deviceList[1]){
                        DeviceManager.deviceList[1].pDeviceInformation.model
                    }
                    else{
                        return ""
                    }
                }
                eqText3:{
                    if(DeviceManager.deviceList[1]){
                        DeviceManager.deviceList[1].pDeviceInformation.connectType === 1  ? "网络连接" : "RS232"
                    }
                    else{
                        return ""
                    }
                }
                eqText4:{
                    if(DeviceManager.deviceList[1]){
                        DeviceManager.deviceList[1].pDeviceInformation.state
                    }
                    else{
                        return ""
                    }
                }
                onSigAltitudeModel: {
                    if(visible){
                        altitudeModel2 = tmp
                    }
                }
            }
            MultideviceSystemConfig{
                id:s3
                x:654
                y:68
                sysCurrIndex:3
                heightOpation:{
                    if(DeviceManager.deviceList[2]){
                        return DeviceManager.deviceList[2].pDeviceInformation.heightOption
                                === 1 ? true:false
                    }
                    else if(DeviceManager.deviceList[3]){
                        return DeviceManager.deviceList[3].pDeviceInformation.heightOption
                                === 1 ? true:false
                    }
                    else{
                        return false
                    }
                }
                visible: musysTmp3
                eqText1:{
                    if(DeviceManager.deviceList[2]){
                        DeviceManager.deviceList[2].pDeviceInformation.name
                    }
                    else if(DeviceManager.deviceList[3]){
                        DeviceManager.deviceList[3].pDeviceInformation.name
                    }
                    else{
                        return ""
                    }
                }
                eqText2:{
                    if(DeviceManager.deviceList[2]){
                        DeviceManager.deviceList[2].pDeviceInformation.model
                    }
                    else if(DeviceManager.deviceList[3]){
                        DeviceManager.deviceList[3].pDeviceInformation.model
                    }
                    else{
                        return ""
                    }
                }
                eqText3:{
                    if(DeviceManager.deviceList[2]){
                        DeviceManager.deviceList[2].pDeviceInformation.connectType === 1  ? "网络连接" : "RS232"
                    }
                    else if(DeviceManager.deviceList[3]){
                        DeviceManager.deviceList[3].pDeviceInformation.connectType === 1  ? "网络连接" : "RS232"
                    }
                    else{
                        return ""
                    }
                }
                eqText4:{
                    if(DeviceManager.deviceList[2]){
                        DeviceManager.deviceList[2].pDeviceInformation.state
                    }
                    else if(DeviceManager.deviceList[3]){
                        DeviceManager.deviceList[3].pDeviceInformation.state
                    }
                    else{
                        return ""
                    }
                }
                onSigAltitudeModel: {
                    if(visible){
                        altitudeModel2 = tmp
                    }
                }
            }
            MultideviceSystemConfig{
                id:s4
                x:961
                y:68
                sysCurrIndex:4
                visible: musysTmp4
                heightOpation:{
                    if(DeviceManager.deviceList[3]){
                        return DeviceManager.deviceList[3].pDeviceInformation.heightOption
                                === 1 ? true:false
                    }
                    else if(DeviceManager.deviceList[2]){
                        return DeviceManager.deviceList[2].pDeviceInformation.heightOption
                                === 1 ? true:false
                    }
                    else{
                        return false
                    }
                }
                eqText1:{
                    if(DeviceManager.deviceList[3]){
                        DeviceManager.deviceList[3].pDeviceInformation.name
                    }
                    else if(DeviceManager.deviceList[2]){
                        DeviceManager.deviceList[2].pDeviceInformation.name
                    }
                    else{
                        return ""
                    }
                }
                eqText2:{
                    if(DeviceManager.deviceList[3]){
                        DeviceManager.deviceList[3].pDeviceInformation.model
                    }
                    else if(DeviceManager.deviceList[2]){
                        DeviceManager.deviceList[2].pDeviceInformation.model
                    }
                    else{
                        return ""
                    }
                }
                eqText3:{
                    if(DeviceManager.deviceList[3]){
                        DeviceManager.deviceList[3].pDeviceInformation.connectType === 1  ? "网络连接" : "RS232"
                    }
                    else if(DeviceManager.deviceList[2]){
                        DeviceManager.deviceList[2].pDeviceInformation.connectType === 1  ? "网络连接" : "RS232"
                    }
                    else{
                        return ""
                    }
                }
                eqText4:{
                    if(DeviceManager.deviceList[3]){
                        DeviceManager.deviceList[3].pDeviceInformation.state
                    }
                    else if(DeviceManager.deviceList[2]){
                        DeviceManager.deviceList[2].pDeviceInformation.state
                    }
                    else{
                        return ""
                    }
                }
                onSigAltitudeModel: {
                    if(visible){
                        altitudeModel4 = tmp
                    }
                }
            }
            Connections{
                target: sysUI
                function onSigSysCheck(id){
                    s1.color = pRgb(43, 112, 173)
                    s2.color = pRgb(43, 112, 173)
                    s3.color = pRgb(43, 112, 173)
                    s4.color = pRgb(43, 112, 173)
                    if(id === 1){
                        s1.color = "#4a8ac4"
                    }
                    else if(id === 2){
                        s2.color = "#4a8ac4"
                    }
                    else if(id === 3){
                        s3.color = "#4a8ac4"
                    }
                    else if(id === 4){
                        s4.color = "#4a8ac4"
                    }
                }
            }
            Connections{
                target: window
                function onSigStatusReset(){
                    s1.color = pRgb(43, 112, 173)
                    s2.color = pRgb(43, 112, 173)
                    s3.color = pRgb(43, 112, 173)
                    s4.color = pRgb(43, 112, 173)
                }
            }
            Button{
                id:btn1
                x:210
                y:654
                width: 243
                height: 52
                enabled: itemCount === 4 ? false : true
                background: Rectangle{
                    radius: 6
                    border.width: 2
                    border.color: pRgb(43, 112, 173)
                    color: itemCount === 4 ? pRgb(232, 232, 232) : pRgb(43, 112, 173)
                }
                contentItem: Text {
                    text: "新增设备"
                    font.pixelSize: 20
                    color: pRgb(153, 204, 255)
                    anchors.centerIn: parent  // 确保文本在按钮内居中对齐
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.family: fontBold
                }
                onPressed: {
                    oneself = true
                    popup.openPop(8)
                }
            }
            Button{
                id:btn2
                x:542
                y:654
                width: 243
                height: 52
                enabled: currIndex === 0 ? false : true
                background: Rectangle{
                    radius: 6
                    border.width: 2
                    border.color: pRgb(43, 112, 173)
                    color: currIndex === 0 ? pRgb(232, 232, 232) : pRgb(43, 112, 173)
                }
                contentItem: Text {
                    text: "删除设备"
                    font.pixelSize: 20
                    color: pRgb(153, 204, 255)
                    anchors.centerIn: parent  // 确保文本在按钮内居中对齐
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.family: fontBold
                }
                onPressed: {
                    DeviceManager.removeDevice(currIndex)
                    var a = altitudeModel1
                    var b = altitudeModel2
                    var c = altitudeModel3
                    var d = altitudeModel4
                    var p1 = undetermined1
                    var p2 = undetermined2
                    var p3 = undetermined3
                    var p4 = undetermined4
                    altitudeModel1 = false
                    altitudeModel2 = false
                    altitudeModel3 = false
                    altitudeModel4 = false
                    undetermined1 = false
                    undetermined2 = false
                    undetermined3 = false
                    undetermined4 = false
                    if(currIndex == 1){
                        s1.color = pRgb(43, 112, 173)
                        if(equipmentCount == 3){
                            altitudeModel1 = b
                            altitudeModel2 = c
                            altitudeModel3 = d
                            undetermined1 = p2
                            undetermined2 = p3
                            undetermined3 = p4
                        }
                        else if(equipmentCount == 2){
                            altitudeModel1 = b
                            altitudeModel2 = c
                            undetermined1 = p2
                            undetermined2 = p3
                        }
                        else if(equipmentCount == 1){
                            altitudeModel1 = b
                            btnDefault = b
                            undetermined1 = p2
                        }
                    }
                    else if(currIndex == 2){
                        s2.color = pRgb(43, 112, 173)
                        if(equipmentCount == 3){
                            altitudeModel1 = a
                            altitudeModel2 = c
                            altitudeModel3 = d
                            undetermined1 = p1
                            undetermined2 = p3
                            undetermined3 = p4
                        }
                        else if(equipmentCount == 2){
                            altitudeModel1 = a
                            altitudeModel2 = c
                            undetermined1 = p1
                            undetermined2 = p3
                        }
                        else if(equipmentCount == 1){
                            altitudeModel1 = a
                            btnDefault = a
                            undetermined1 = p1
                        }
                    }
                    else if(currIndex == 3){
                        s3.color = pRgb(43, 112, 173)
                        if(equipmentCount == 3){
                            altitudeModel1 = a
                            altitudeModel2 = b
                            altitudeModel3 = d
                            undetermined1 = p1
                            undetermined2 = p2
                            undetermined3 = p4
                        }
                        else if(equipmentCount == 2){
                            altitudeModel1 = a
                            altitudeModel2 = b
                            undetermined1 = p1
                            undetermined2 = p2
                        }
                        else if(equipmentCount == 1){
                            altitudeModel1 = a
                            btnDefault = a
                            undetermined1 = p1
                        }
                    }
                    else if(currIndex == 4){
                        s4.color = pRgb(43, 112, 173)
                        if(equipmentCount == 3){
                            altitudeModel1 = a
                            altitudeModel2 = b
                            altitudeModel3 = c
                            undetermined1 = p1
                            undetermined2 = p2
                            undetermined3 = p3
                        }
                        else if(equipmentCount == 2){
                            altitudeModel1 = a
                            altitudeModel2 = b
                            undetermined1 = p1
                            undetermined2 = p2
                        }
                        else if(equipmentCount == 1){
                            altitudeModel1 = a
                            btnDefault = a
                            undetermined1 = p1
                        }
                    }
                    currIndex = 0
                }
            }
            Button{
                id:btn3
                x:867
                y:654
                width: 243
                height: 52
                background: Rectangle{
                    radius: 6
                    color: pRgb(43, 112, 173)
                }
                contentItem: Text {
                    text: "修改密码"
                    font.pixelSize: 20
                    color: pRgb(153, 204, 255)
                    anchors.centerIn: parent  // 确保文本在按钮内居中对齐
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.family: fontBold
                }
                onPressed: {
                    popup.openPop(7)
                }
            }
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
