import QtQuick 2.0
import QtQuick.Controls 2.5

//系统配置
Rectangle {
    id: sysUI
    property int itemCount: 0
    property bool musysTmp1: false
    property bool musysTmp2: false
    property bool musysTmp3: false
    property bool musysTmp4: false
    color: pRgb(153, 204, 255)

    signal sigSysCheck(var id)
    function sysCheck(id){
        sigSysCheck(id)
    }
    onItemCountChanged: {
        if(itemCount == 2){
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
    Loader{
        id:loader1
        asynchronous:true
        sourceComponent: syscfg
    }

    Component{
        id:syscfg
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
                background: Rectangle{
                    radius: 6
                    border.width: 3
                    border.color: "#99ccff"
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
                background: Rectangle{
                    radius: 6
                    border.width: 3
                    border.color: "#99ccff"
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
                background: Rectangle{
                    radius: 6
                    border.width: 3
                    border.color: "#99ccff"
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
                indicator: Rectangle
                {
                    width: 30
                    height: 30
                    radius: 15
                    color: bt1.checked ? "#0d988c" : pRgb(232, 232, 232)
                    border.color: "#b1d5db"
                    border.width: 2
                }
                onPressed: {
                    altitudeModel = true
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
                checked: true
                indicator: Rectangle
                {
                    width: 30
                    height: 30
                    radius: 15
                    color: bt2.checked ? "#0d988c" : pRgb(232, 232, 232)
                    border.color: "#b1d5db"
                    border.width: 2
                }
                onPressed: {
                    altitudeModel = false
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
                onClicked: {
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
                            running: ctl.checked? true : false
                            duration: 0
                        }
                        NumberAnimation on x{
                            to:6
                            running: ctl.checked? false : true;
                            duration: 0
                        }
                    }
                    Text {
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.leftMargin: 25
                        text: qsTr("关闭")
                        color: ctl.checked? pRgb(43, 112, 173) : "#e5e6e7"
                        font.family: fontBold
                        font.pixelSize: 16
                    }
                    Text {
                        anchors.right: parent.right
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.rightMargin: 25
                        text: qsTr("启动")
                        color: ctl.checked? "#e5e6e7" : pRgb(43, 112, 173)
                        font.family: fontBold
                        font.pixelSize: 16
                    }
                }
            }
            Text {
                id: s8
                text: qsTr("PIN1")
                color: pRgb(177, 213, 219)
                font.family: fontBold
                font.pixelSize: 16
                x:103
                y:440
            }
            Text {
                id: s9
                text: qsTr("PIN2")
                color: pRgb(177, 213, 219)
                font.family: fontBold
                font.pixelSize: 16
                anchors.left: s8.left
                anchors.top: s8.bottom
                anchors.topMargin: 20
            }
            Text {
                id: s10
                text: qsTr("PIN3")
                color: pRgb(177, 213, 219)
                font.family: fontBold
                font.pixelSize: 16
                anchors.left: s9.left
                anchors.top: s9.bottom
                anchors.topMargin: 20
            }
            Image {
                id: im1
                source: "qrc:/image/报警.png"
                x:197
                y:440
            }
            Image {
                id: im2
                source: "qrc:/image/复位.png"
                anchors.left: im1.left
                anchors.top: im1.bottom
                anchors.topMargin: 13
                anchors.leftMargin: -2
            }
            Image {
                id: im3
                source: "qrc:/image/待定.png"
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
            }
            Switch{
                id:ctl1
                x:713
                y:147
                onClicked: {
                    if(ctl1.checked){
                        loader.sourceComponent = rect2
                    }
                    else{
                        loader.sourceComponent = rect1
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
                            running: ctl1.checked? true : false
                            duration: 0
                        }
                        NumberAnimation on x{
                            to:8
                            running: ctl1.checked? false : true;
                            duration: 0
                        }
                    }
                    Text {
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.topMargin: 7
                        anchors.leftMargin: 63
                        text: qsTr("网络")
                        color: ctl1.checked? pRgb(43, 112, 173) : "#e5e6e7"
                        font.family: fontBold
                        font.pixelSize: 16
                    }
                    Text {
                        anchors.right: parent.right
                        anchors.top: parent.top
                        anchors.topMargin: 7
                        anchors.rightMargin: 63
                        text: qsTr("RS232")
                        color: ctl1.checked? "#e5e6e7" : pRgb(43, 112, 173)
                        font.family: fontBold
                        font.pixelSize: 16
                    }
                }
            }
            Loader{
                id:loader
                asynchronous:true
                sourceComponent: rect1
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
                        background: Rectangle{
                            radius: 6
                            border.width: 3
                            border.color: "#99ccff"
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
                        background: Rectangle{
                            radius: 6
                            border.width: 3
                            border.color: "#99ccff"
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
                        background: Rectangle{
                            radius: 6
                            border.width: 3
                            border.color: "#99ccff"
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
                    }
                    CustomComboBox{
                        id:com4
                        width: 243
                        height: 40
                        x:233
                        y:97
                        model: ["2400", "9600", "19200","115200"]
                    }
                    CustomComboBox{
                        id:com5
                        width: 243
                        height: 40
                        x:233
                        y:151
                        model: ["7bits", "8bits"]
                    }
                    CustomComboBox{
                        id:com6
                        width: 243
                        height: 40
                        x:233
                        y:206
                        model: ["None", "Odd", "Even"]
                    }
                    CustomComboBox{
                        id:com7
                        width: 243
                        height: 40
                        x:233
                        y:265
                        model: ["1bit", "1.5bits", "2bits"]
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
                visible: musysTmp1
            }
            MultideviceSystemConfig{
                id:s2
                x:347
                y:68
                sysCurrIndex:2
                visible: musysTmp2
            }
            MultideviceSystemConfig{
                id:s3
                x:654
                y:68
                sysCurrIndex:3
                visible: musysTmp3
            }
            MultideviceSystemConfig{
                id:s4
                x:961
                y:68
                sysCurrIndex:4
                visible: musysTmp4
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
