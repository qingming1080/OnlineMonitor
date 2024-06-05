import QtQuick 2.15
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15
Rectangle {
    color: pRgb(153, 204, 255)
    readonly property int qmlscreenIndicator:  1
    property bool tableFlag: false
    EquipmentInfor{
        id:s1
        x:29
        y:20
        width: 243
        height: 258
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
                width: 245
                height: 249
                x:29
                y:289
            }
        }
    }
    Component{
        id:weld2
        Item {
            WeldingParameter{
                id:s3_1
                width: 245
                height: 249
                x:29
                y:289
            }
        }
    }
    Button{
        id:s4
        x:31
        y:553
        width: 243
        height: 52
        background: Rectangle{
            radius: 6
            color: pRgb(43, 112, 173)
        }
        contentItem: Text {
            id: mt1
            text: "新建模型"
            font.pixelSize: 20
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
        anchors.topMargin: 31
        width: 243
        height: 52
        background: Rectangle{
            radius: 6
            color: pRgb(43, 112, 173)
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
                width: 346
                height: 283
                x:286
                y:20
            }
            YieldTrend{
                id:s6
                width: 609
                height: 283
                x:645
                y:20
            }
            WeldingTrend{
                id:s7
                width: 596
                height: 370
                x:286
                y:318
            }
            AbnormalInfor{
                id:s8
                width: 359
                height: 370
                x:895
                y:318
            }
        }
    }
    Component{
        id:mode2
        Item {
            Rectangle{
                id:rect
                x:287
                y:20
                width: 964
                height: 668
                color: pRgb(43, 112, 173)
                radius: 3
            }

            TableView {
                id: tableView
                width: 960
                height: 664
                x:289
                y:22
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
                    width: 120
                }
                TableViewColumn {
                    role: "weldTime"
                    title: "焊接时间"
                    width: 120
                }

                TableViewColumn {
                    role: "power"
                    title: "功率"
                    width: 120
                }
                TableViewColumn {
                    role: "energy"
                    title: "能量"
                    width: 120
                }
                TableViewColumn {
                    role: "date"
                    title: "日期"
                    width: 120
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
