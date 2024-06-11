import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15
//多设备生产界面
Rectangle {
    color: pRgb(153, 204, 255)
    property int itemCount: 0
    function swichCount(){
        if(itemCount == 2){
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
        else if(itemCount == 3){
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
        else if(itemCount == 4){
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

    onItemCountChanged: {
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
        }
        RealtimeYield{
            id:s2
            width: 289
            height: 238
            x:284
            y:42
            radius: 3
            color: "#0c5596"
        }
        YieldTrend{
            id:s5
            width: 545
            height: 254
            x:28
            y:298
            radius: 3
            color: "#0c5596"
        }
        Button{
            width: 24
            height: 24
            x:570
            y:6
            background: Rectangle{
                color: "transparent"
                Image {
                    anchors.fill: parent
                    source: "qrc:/image/expand-全屏化.png"
                }
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
            if(height>290){
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
        }
        RealtimeYield{
            id:s4
            width: 289
            height: 238
            x:284
            y:42
            radius: 3
            color: "#0c5596"
        }
        YieldTrend{
            id:s6
            width: 545
            height: 254
            x:28
            y:298
            radius: 3
            color: "#0c5596"
        }
        Button{
            width: 24
            height: 24
            x:570
            y:6
            background: Rectangle{
                color: "transparent"
                Image {
                    anchors.fill: parent
                    source: "qrc:/image/expand-全屏化.png"
                }
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
        }
        RealtimeYield{
            id:s8
            width: 277
            height: 228
            x:280
            y:35
            radius: 3
            color: "#0c5596"
        }
        Button{
            width: 24
            height: 24
            x:570
            y:6
            background: Rectangle{
                color: "transparent"
                Image {
                    anchors.fill: parent
                    source: "qrc:/image/expand-全屏化.png"
                }
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
        }
        RealtimeYield{
            id:s11
            width: 277
            height: 228
            x:280
            y:35
            radius: 3
            color: "#0c5596"
        }
        Button{
            width: 24
            height: 24
            x:570
            y:6
            background: Rectangle{
                color: "transparent"
                Image {
                    anchors.fill: parent
                    source: "qrc:/image/expand-全屏化.png"
                }
            }
        }
    }

    Button{
        id:b1
        x:195
        y:654
        width: 243
        height: 52
        background: Rectangle{
            radius: 6
            color: pRgb(43, 112, 173)
        }
        contentItem: Text {
            id:mt1
            anchors.centerIn: parent
            text: "新建模型"
            font.pixelSize: 20
            color: pRgb(153, 204, 255)
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: fontBold
        }
    }
    Button{
        id:b2
        width: 243
        height: 52
        anchors.left: b1.right
        anchors.top: b1.top
        anchors.leftMargin: 63
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: pRgb(43, 112, 173)
            color: itemCount === 4 ? pRgb(232, 232, 232) : pRgb(43, 112, 173)
        }
        contentItem: Text {
            id:mt2
            anchors.centerIn: parent
            text: "新增设备"
            font.pixelSize: 20
            color: pRgb(153, 204, 255)
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: fontBold
        }
        onPressed: {
            switchUI(3)
            isAdd = true
            sigSysConfig()
        }
    }
    Button{
        id:b3
        width: 243
        height: 52
        anchors.left: b2.right
        anchors.top: b2.top
        anchors.leftMargin: 63
        background: Rectangle{
            radius: 6
            color: pRgb(43, 112, 173)
        }
        contentItem: Text {
            id:mt3
            anchors.centerIn: parent
            text: "系统消息"
            font.pixelSize: 20
            color: pRgb(153, 204, 255)
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
