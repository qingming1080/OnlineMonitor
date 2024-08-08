import QtQuick 2.15
import QtQuick.Controls 1.4
import QtQml.Models 2.2
import QtQuick.Controls 2.5
import Qt.labs.qmlmodels 1.0
import QtQuick.Controls.Styles 1.4
Rectangle {
    property int itemCount: equipmentCount
    color: pRgb(153, 204, 255)
    Component.onCompleted: {
        bt1.checkable = true
    }
    onItemCountChanged: {
        if(itemCount == 1){
            bt3.visible = false
            bt4.visible = false
            bt5.visible = false
        }
        else if(itemCount == 2){
            bt3.visible = true
            bt4.visible = false
            bt5.visible = false
        }
        else if(itemCount == 3){
            bt3.visible = true
            bt4.visible = true
            bt5.visible = false
        }
        else if(itemCount == 4){
            bt3.visible = true
            bt4.visible = true
            bt5.visible = true
        }
    }

    ButtonGroup {
        id: group1
    }
    ButtonGroup {
        id: group2
    }
    Rectangle{
        id:rect
        x:27
        y:22
        width: 1222
        height: 677
        color: "#007dbc"
        radius: 3
    }

    Rectangle{
        id:top
        width: 1220
        height: 70
        color: "#007dbc"
        anchors.top: rect.top
        anchors.left: rect.left
        radius: 3
        Text {
            id: name
            text: qsTr("设备")
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.topMargin: 20
            color: pRgb(177, 213, 219)
            font.family: fontBold
            font.bold: true
            font.pixelSize: 20
        }
        RadioButton{
            id:bt1
            width: 34
            height: 34
            anchors.left: name.right
            anchors.top: name.top
            anchors.topMargin: -5
            anchors.leftMargin: 30
            ButtonGroup.group: group1
            checked: true
            indicator: Rectangle
            {
                width: 34
                height: 34
                radius: 17
                color: bt1.checked ? "#0068a7" : "#e8e8e8"
                border.color: bt1.checked ? "#afc3d8" : "#0068a8"
                border.width: 2
            }
            onPressed: {
                History.setDeviceID(0)
            }
        }
        Text {
            id: b1
            anchors.left: bt1.right
            anchors.top: bt1.top
            anchors.topMargin: 7
            anchors.leftMargin: 14
            text: qsTr("全选")
            color: pRgb(177, 213, 219)
            font.family: fontBold
            font.bold: true
            font.pixelSize: LanguageManger.language === "SimplifiedChinese" ?20:16
        }

        RadioButton{
            id:bt2
            width: 34
            height: 34
            anchors.verticalCenter: bt1.verticalCenter
            anchors.left: bt1.right
            anchors.leftMargin: 80
            ButtonGroup.group: group1
            indicator: Rectangle
            {
                width: 34
                height: 34
                radius: 17
                color: bt2.checked ? "#0068a7" : "#e8e8e8"
                border.color: bt2.checked ? "#afc3d8" : "#0068a8"
                border.width: 2
            }
            onPressed: {
                History.setDeviceID(1)
            }
        }
        Text {
            id: b2
            anchors.verticalCenter: bt2.verticalCenter
            anchors.left: bt2.right
            anchors.leftMargin: 14
            text: qsTr("设备1")
            color: pRgb(177, 213, 219)
            font.family: fontBold
            font.bold: true
            font.pixelSize: LanguageManger.language === "SimplifiedChinese" ?20:16
        }

        RadioButton{
            id:bt3
            width: 34
            height: 34
            anchors.verticalCenter: bt2.verticalCenter
            anchors.left: bt2.right
            anchors.leftMargin: 80
            ButtonGroup.group: group1
            indicator: Rectangle
            {
                width: 34
                height: 34
                radius: 17
                color: bt3.checked ? "#0068a7" : "#e8e8e8"
                border.color: bt3.checked ? "#afc3d8" : "#0068a8"
                border.width: 2
            }
            onVisibleChanged: {
                if(visible){
                    enabled = true
                }
                else{
                    enabled = false
                }
            }
            onPressed: {
                History.setDeviceID(2)
            }
        }
        Text {
            id: b3
            anchors.verticalCenter: bt3.verticalCenter
            anchors.left: bt3.right
            anchors.leftMargin: 14
            text: qsTr("设备2")
            color: pRgb(177, 213, 219)
            font.family: fontBold
            font.bold: true
            font.pixelSize: LanguageManger.language === "SimplifiedChinese" ?20:16
            visible: bt3.visible
        }

        RadioButton{
            id:bt4
            width: 34
            height: 34
            anchors.verticalCenter: bt3.verticalCenter
            anchors.left: bt3.right
            anchors.leftMargin: 80
            ButtonGroup.group: group1
            indicator: Rectangle
            {
                width: 34
                height: 34
                radius: 17
                color: bt4.checked ? "#0068a7" : "#e8e8e8"
                border.color: bt4.checked ? "#afc3d8" : "#0068a8"
                border.width: 2
            }
            onVisibleChanged: {
                if(visible){
                    enabled = true
                }
                else{
                    enabled = false
                }
            }
            onPressed: {
                History.setDeviceID(3)
            }
        }
        Text {
            id: b4
            anchors.verticalCenter: bt4.verticalCenter
            anchors.left: bt4.right
            anchors.leftMargin: 14
            text: qsTr("设备3")
            color: pRgb(177, 213, 219)
            font.family: fontBold
            font.bold: true
            font.pixelSize: LanguageManger.language === "SimplifiedChinese" ?20:16
            visible: bt4.visible
        }

        RadioButton{
            id:bt5
            width: 34
            height: 34
            anchors.verticalCenter: bt4.verticalCenter
            anchors.left: bt4.right
            anchors.leftMargin: 80
            ButtonGroup.group: group1
            indicator: Rectangle
            {
                width: 34
                height: 34
                radius: 17
                color: bt5.checked ? "#0068a7" : "#e8e8e8"
                border.color: bt5.checked ? "#afc3d8" : "#0068a8"
                border.width: 2
            }
            onVisibleChanged: {
                if(visible){
                    enabled = true
                }
                else{
                    enabled = false
                }
            }
            onPressed: {
                History.setDeviceID(4)
            }
        }
        Text {
            id: b5
            anchors.verticalCenter: bt5.verticalCenter
            anchors.left: bt5.right
            anchors.leftMargin: 14
            text: qsTr("设备4")
            color: pRgb(177, 213, 219)
            font.family: fontBold
            font.bold: true
            font.pixelSize: LanguageManger.language === "SimplifiedChinese" ?20:16
            visible: bt5.visible
        }

        Text {
            id: name1
            text: qsTr("结果")
            anchors.top: name.top
            anchors.left: parent.left
            anchors.leftMargin: 723
            color: pRgb(177, 213, 219)
            font.family: fontBold
            font.bold: true
            font.pixelSize: 20
        }
        RadioButton{
            id:bt8
            width: 34
            height: 34
            anchors.verticalCenter: name1.verticalCenter
            anchors.left: name1.right
            anchors.leftMargin: 28
            ButtonGroup.group: group2
            checked: true
            indicator: Rectangle
            {
                width: 34
                height: 34
                radius: 17
                color: bt8.checked ? "#0068a7" : "#e8e8e8"
                border.color: bt8.checked ? "#afc3d8" : "#0068a8"
                border.width: 2
            }
            onPressed: {
                History.setFinalResult(0)
            }
        }
        Text {
            id: b8
            anchors.verticalCenter: bt8.verticalCenter
            anchors.left: bt8.right
            anchors.leftMargin: 14
            text: qsTr("全选")
            color: pRgb(177, 213, 219)
            font.family: fontBold
            font.bold: true
            font.pixelSize: LanguageManger.language === "SimplifiedChinese" ?20:16
        }
        RadioButton{
            id:bt9
            width: 34
            height: 34
            anchors.verticalCenter: bt8.verticalCenter
            anchors.left: bt8.right
            anchors.leftMargin: 70
            ButtonGroup.group: group2
            indicator: Rectangle
            {
                width: 34
                height: 34
                radius: 17
                color: bt9.checked ? "#0068a7" : "#e8e8e8"
                border.color: bt9.checked ? "#afc3d8" : "#0068a8"
                border.width: 2
            }
            onPressed: {
                History.setFinalResult(1)
            }
        }
        Text {
            id: b9
            anchors.verticalCenter: bt9.verticalCenter
            anchors.left: bt9.right
            anchors.leftMargin: 6
            text: qsTr("良")
            color: pRgb(177, 213, 219)
            font.family: fontBold
            font.bold: true
            font.pixelSize: LanguageManger.language === "SimplifiedChinese" ?20:16
        }
        RadioButton{
            id:bt11
            width: 34
            height: 34
            anchors.verticalCenter: bt9.verticalCenter
            anchors.left: bt9.right
            anchors.leftMargin: 70
            ButtonGroup.group: group2
            indicator: Rectangle
            {
                width: 34
                height: 34
                radius: 17
                color: bt11.checked ? "#0068a7" : "#e8e8e8"
                border.color: bt11.checked ? "#afc3d8" : "#0068a8"
                border.width: 2
            }
            onPressed: {
                History.setFinalResult(3)
            }
        }
        Text {
            id: b11
            anchors.verticalCenter: bt11.verticalCenter
            anchors.left: bt11.right
            anchors.leftMargin: 6
            text: qsTr("可疑")
            color: pRgb(177, 213, 219)
            font.family: fontBold
            font.bold: true
            font.pixelSize: LanguageManger.language === "SimplifiedChinese" ?20:16
        }
        RadioButton{
            id:bt10
            width: 34
            height: 34
            anchors.verticalCenter: bt11.verticalCenter
            anchors.left: bt11.right
            anchors.leftMargin: 80
            ButtonGroup.group: group2
            indicator: Rectangle
            {
                width: 34
                height: 34
                radius: 17
                color: bt10.checked ? "#0068a7" : "#e8e8e8"
                border.color: bt10.checked ? "#afc3d8" : "#0068a8"
                border.width: 2
            }
            onPressed: {
                History.setFinalResult(2)
            }
        }
        Text {
            id: b10
            anchors.verticalCenter: bt10.verticalCenter
            anchors.left: bt10.right
            anchors.leftMargin: 10
            text: qsTr("次品")
            color: pRgb(177, 213, 219)
            font.family: fontBold
            font.bold: true
            font.pixelSize: LanguageManger.language === "SimplifiedChinese" ?20:16
        }
    }
    Rectangle{
        width: 1220
        height: 605
        anchors.top: top.bottom
        anchors.left: top.left
        anchors.leftMargin: 1
        color: "#004b8d"
        Text{
            id:t1
            x:1220/5/2-width/2
            y:5
            font.pixelSize: 16
            text: "设备名称"
            font.family: fontBold
            font.bold: true
            color: pRgb(153, 204, 255)
        }
        Text{
            x:1220/5*1 + 1220/5/2-width/2
            y:5
            font.pixelSize: 16
            text: "日期"
            font.family: fontBold
            font.bold: true
            color: pRgb(153, 204, 255)
        }
        Text{
            x:1220/5*2 + 1220/5/2-width/2
            y:5
            font.pixelSize: 16
            text: "能量"
            font.family: fontBold
            font.bold: true
            color: pRgb(153, 204, 255)
        }
        Text{
            x:1220/5*3 + 1220/5/2-width/2
            y:5
            font.pixelSize: 16
            text: "功率"
            font.family: fontBold
            font.bold: true
            color: pRgb(153, 204, 255)
        }
        Text{
            x:1220/5*4 + 1220/5/2-width/2
            y:5
            font.pixelSize: 16
            text: "结果"
            font.family: fontBold
            font.bold: true
            color: pRgb(153, 204, 255)
        }
        ListView{
            id: taskplanView
            width: 1220
            height: 560
            y:35
            clip: true
            model: History
            delegate: Rectangle{
                id: regionItem
                height: 36
                width: 1220
                color: index % 2 === 0 ? "#2d71ae" : "#b1d5db"
                Text{
                    x:1220/5/2-width/2
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 16
                    text: DeviceManager.getHistoryName(welder_id)
                    font.family: fontBold
                    font.bold: true
                    color: index % 2 === 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                }
                Text{
                    anchors.verticalCenter: parent.verticalCenter
                    x:1220/5*1 + 1220/5/2-width/2
                    font.pixelSize: 16
                    text: create_time
                    font.family: fontBold
                    font.bold: true
                    color: index % 2 === 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                }
                Text{
                    anchors.verticalCenter: parent.verticalCenter
                    x:1220/5*2 + 1220/5/2-width/2
                    font.pixelSize: 16
                    text: energy
                    font.family: fontBold
                    font.bold: true
                    color: index % 2 === 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                }
                Text{
                    anchors.verticalCenter: parent.verticalCenter
                    x:1220/5*3 + 1220/5/2-width/2
                    font.pixelSize: 16
                    text: power
                    font.family: fontBold
                    font.bold: true
                    color: index % 2 === 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                }
                Text{
                    anchors.verticalCenter: parent.verticalCenter
                    x:1220/5*4 + 1220/5/2-width/2
                    font.pixelSize: 16
                    text: final_result===0?"良品":final_result===1?"次品":"可疑"
                    font.family: fontBold
                    font.bold: true
                    color: index % 2 === 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                }
            }
        }

    }

    Text {
        id: version
        color: "#639ed6"
        anchors.top: timeText.top
        anchors.right: timeText.left
        anchors.rightMargin: 20
        font.family: fontBold
        font.bold: true
        font.pixelSize: 14
        text: qsTr("系统版本号: v2.0.1")
    }
    // 显示时间的文本
    Text {
        id: timeText
        y:718
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 10
        anchors.bottomMargin: 5
        font.pixelSize: 14
        font.family: fontBold
        font.bold: true
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
