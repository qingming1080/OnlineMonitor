import QtQuick 2.12
import QtQuick.Controls 1.4
import QtQml.Models 2.2
import QtQuick.Controls 2.5
import Qt.labs.qmlmodels 1.0
Rectangle {
    property int itemCount: 0
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
            font.pixelSize: 20
        }
        RadioButton{
            id:bt1
            width: 30
            height: 30
            anchors.left: name.right
            anchors.top: name.top
            anchors.leftMargin: 30
            ButtonGroup.group: group1
            checked: true
            indicator: Rectangle
            {
                width: 30
                height: 30
                radius: 15
                color: bt1.checked ? "#0068a7" : "#e8e8e8"
                border.color: bt1.checked ? "#afc3d8" : "#0068a8"
                border.width: 2
            }
        }
        Text {
            id: b1
            anchors.left: bt1.right
            anchors.top: bt1.top
            anchors.leftMargin: 14
            text: qsTr("全选")
            color: pRgb(177, 213, 219)
            font.family: fontBold
            font.pixelSize: 20
        }

        RadioButton{
            id:bt2
            width: 30
            height: 30
            anchors.left: b1.right
            anchors.top: b1.top
            anchors.leftMargin: 40
            ButtonGroup.group: group1
            indicator: Rectangle
            {
                width: 30
                height: 30
                radius: 15
                color: bt2.checked ? "#0068a7" : "#e8e8e8"
                border.color: bt2.checked ? "#afc3d8" : "#0068a8"
                border.width: 2
            }
        }
        Text {
            id: b2
            anchors.left: bt2.right
            anchors.top: bt2.top
            anchors.leftMargin: 14
            text: qsTr("设备1")
            color: pRgb(177, 213, 219)
            font.family: fontBold
            font.pixelSize: 20
        }

        RadioButton{
            id:bt3
            width: 30
            height: 30
            anchors.left: parent.left
            anchors.top: name.top
            anchors.leftMargin: 338
            ButtonGroup.group: group1
            indicator: Rectangle
            {
                width: 30
                height: 30
                radius: 15
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
        }
        Text {
            id: b3
            anchors.left: bt3.right
            anchors.top: bt3.top
            anchors.leftMargin: 14
            text: qsTr("设备2")
            color: pRgb(177, 213, 219)
            font.family: fontBold
            font.pixelSize: 20
            visible: bt3.visible
        }

        RadioButton{
            id:bt4
            width: 30
            height: 30
            anchors.left: parent.left
            anchors.top: name.top
            anchors.leftMargin: 462
            ButtonGroup.group: group1
            indicator: Rectangle
            {
                width: 30
                height: 30
                radius: 15
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
        }
        Text {
            id: b4
            anchors.left: bt4.right
            anchors.top: bt4.top
            anchors.leftMargin: 14
            text: qsTr("设备3")
            color: pRgb(177, 213, 219)
            font.family: fontBold
            font.pixelSize: 20
            visible: bt4.visible
        }

        RadioButton{
            id:bt5
            width: 30
            height: 30
            anchors.left: parent.left
            anchors.top: name.top
            anchors.leftMargin: 586
            ButtonGroup.group: group1
            indicator: Rectangle
            {
                width: 30
                height: 30
                radius: 15
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
        }
        Text {
            id: b5
            anchors.left: bt5.right
            anchors.top: bt5.top
            anchors.leftMargin: 14
            text: qsTr("设备4")
            color: pRgb(177, 213, 219)
            font.family: fontBold
            font.pixelSize: 20
            visible: bt5.visible
        }

        Text {
            id: name1
            text: qsTr("结果")
            anchors.top: name.top
            anchors.left: parent.left
            anchors.leftMargin: 783
            color: pRgb(177, 213, 219)
            font.family: fontBold
            font.pixelSize: 20
        }
        RadioButton{
            id:bt8
            width: 30
            height: 30
            anchors.left: name1.right
            anchors.top: name.top
            anchors.leftMargin: 28
            ButtonGroup.group: group2
            checked: true
            indicator: Rectangle
            {
                width: 30
                height: 30
                radius: 15
                color: bt8.checked ? "#0068a7" : "#e8e8e8"
                border.color: bt8.checked ? "#afc3d8" : "#0068a8"
                border.width: 2
            }
        }
        Text {
            id: b8
            anchors.left: bt8.right
            anchors.top: bt8.top
            anchors.leftMargin: 14
            text: qsTr("全选")
            color: pRgb(177, 213, 219)
            font.family: fontBold
            font.pixelSize: 20
        }
        RadioButton{
            id:bt9
            width: 30
            height: 30
            anchors.left: b8.right
            anchors.top: b8.top
            anchors.leftMargin: 42
            ButtonGroup.group: group2
            indicator: Rectangle
            {
                width: 30
                height: 30
                radius: 15
                color: bt9.checked ? "#0068a7" : "#e8e8e8"
                border.color: bt9.checked ? "#afc3d8" : "#0068a8"
                border.width: 2
            }
        }
        Text {
            id: b9
            anchors.left: bt9.right
            anchors.top: bt9.top
            anchors.leftMargin: 14
            text: qsTr("良")
            color: pRgb(177, 213, 219)
            font.family: fontBold
            font.pixelSize: 20
        }
        RadioButton{
            id:bt10
            width: 30
            height: 30
            anchors.left: b9.right
            anchors.top: b9.top
            anchors.leftMargin: 55
            ButtonGroup.group: group2
            indicator: Rectangle
            {
                width: 30
                height: 30
                radius: 15
                color: bt10.checked ? "#0068a7" : "#e8e8e8"
                border.color: bt10.checked ? "#afc3d8" : "#0068a8"
                border.width: 2
            }
        }
        Text {
            id: b10
            anchors.left: bt10.right
            anchors.top: bt10.top
            anchors.leftMargin: 14
            text: qsTr("次品")
            color: pRgb(177, 213, 219)
            font.family: fontBold
            font.pixelSize: 20
        }
    }

    TableView {
        id: tableView
        width: 1220
        height: 605
        anchors.top: top.bottom
        anchors.left: top.left
        anchors.leftMargin: 1
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff//隐藏水平滚动条
        verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff//隐藏竖直滚动条
        frameVisible: false
        clip: true
        itemDelegate: Rectangle {
            height: 38
            width: 244
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
            visible:{
                console.log(tableView.model.data(listModel.index(styleData.row, listModel.name), Qt.DisplayRole))
                console.log(tableView.model.data(listModel.index(styleData.row, listModel.result), Qt.DisplayRole))
                console.log(tableView.model.data(listModel.index(styleData.row, listModel.date), Qt.DisplayRole))
                tableView.model.data(listModel.index(styleData.row, name), Qt.DisplayRole)!=="Item 1"
            }
        }
        headerDelegate: Rectangle {
            height: 40
            color: "#004b8d"
            Text {
                anchors.centerIn: parent
                text: styleData.value
                color: "#b1d5db"
                font.family: fontBold
                font.pixelSize: 14
            }
        }

        TableViewColumn {
            role: "name"
            title: "设备名称"
            width: 244
        }

        TableViewColumn {
            role: "date"
            title: "日期"
            width: 244
        }
        TableViewColumn {
            role: "energy"
            title: "能量"
            width: 244
        }

        TableViewColumn {
            role: "power"
            title: "功率"
            width: 244
        }
        TableViewColumn {
            role: "result"
            title: "结果"
            width: 244
        }
        model: ListModel {
            id: listModel
            ListElement { name: "Item 1"; date: "1" ;energy: "2";power: "2";result: "4";}
            ListElement { name: "Item 2"; date: "2" ;energy: "2";power: "2";result: "2";}
            ListElement { name: "Item 2"; date: "3" ;energy: "2";power: "2";result: "1";}
            ListElement { name: "Item 2"; date: "3" ;energy: "2";power: "2";result: "0";}
            ListElement { name: "Item 2"; date: "3" ;energy: "2";power: "2";result: "3";}
            ListElement { name: "Item 2"; date: "3" ;energy: "2";power: "2";result: "3";}
            ListElement { name: "Item 2"; date: "3" ;energy: "2";power: "2";result: "3";}
            ListElement { name: "Item 2"; date: "3" ;energy: "2";power: "2";result: "3";}
            ListElement { name: "Item 2"; date: "3" ;energy: "2";power: "2";result: "3";}
            ListElement { name: "Item 2"; date: "3" ;energy: "2";power: "2";result: "3";}
            ListElement { name: "Item 2"; date: "3" ;energy: "2";power: "2";result: "3";}
            ListElement { name: "Item 2"; date: "3" ;energy: "2";power: "2";result: "3";}
            ListElement { name: "Item 2"; date: "3" ;energy: "2";power: "2";result: "3";}
            ListElement { name: "Item 2"; date: "3" ;energy: "2";power: "2";result: "3";}
            ListElement { name: "Item 2"; date: "3" ;energy: "2";power: "2";result: "3";}
            ListElement { name: "Item 2"; date: "3" ;energy: "2";power: "2";result: "3";}
            ListElement { name: "Item 2"; date: "3" ;energy: "2";power: "2";result: "3";}
            ListElement { name: "Item 2"; date: "3" ;energy: "2";power: "2";result: "3";}
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
