import QtQuick 2.15
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15
Rectangle {
    color: pRgb(153, 204, 255)
    property bool tableFlag: false
    property var proViews: []
    Component.onCompleted: {
        if(equipmentCount > 1){
            mode = 1
            loadView(2,multipro)
        }
        else{
            mode = 0
            loadView(1,autopro)
        }
    }
    function loadView(viewName, component) {
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
    Connections{
        target: window
        function onEquipmentCountChanged(){
            if(equipmentCount > 1){
                mode = 1
                loadView(2,multipro)
            }
        }
    }

    StackView{
        id:prostack
    }
    Component{
        id:autopro
        Item{
            EquipmentInfor{
                id:s1
                x:mode == 1 ? 52 : 29
                y:mode == 1 ? 35 : 20
                width: mode == 1 ? 208 : 243
                height: mode == 1 ? 203 : 258
                color: mode == 1 ? "#0c5696" : pRgb(43, 112, 173)
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
                        width: mode == 1 ? 212 : 245
                        height: mode == 1 ? 215 : 249
                        x: mode == 1 ? 50 : 29
                        y: mode == 1 ? 248 : 289
                        color: mode == 1 ? "#0c5696" : pRgb(43, 112, 173)
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
                    text: "新增设备"
                    font.pixelSize:mode == 1 ? 17: 20
                    color: pRgb(153, 204, 255)
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.family: fontBold
                }
                onPressed: {
                    switchUI(3)
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
                        width: mode === 1 ? 288:346
                        height: mode === 1 ? 235:283
                        x:mode === 1 ? 269:286
                        y:mode === 1 ? 35:20
                        color: mode === 1 ? "#0c5696" : pRgb(43, 112, 173)
                    }
                    YieldTrend{
                        id:s6
                        width: mode === 1 ? 514:609
                        height: mode === 1 ? 235:283
                        x:mode === 1 ? 568:645
                        y:mode === 1 ? 35:20
                        color: mode === 1 ? "#0c5696" : pRgb(43, 112, 173)
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

                    TableView {
                        id: tableView
                        width: mode === 1 ? 808:960
                        height: mode === 1 ? 556:664
                        x:mode === 1 ? 272:289
                        y:mode === 1 ? 37:22
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
                            width: mode === 1 ? 90 :120
                        }
                        TableViewColumn {
                            role: "weldTime"
                            title: "焊接时间"
                            width: mode === 1 ? 90 :120
                        }

                        TableViewColumn {
                            role: "power"
                            title: "功率"
                            width: mode === 1 ? 90 :120
                        }
                        TableViewColumn {
                            role: "energy"
                            title: "能量"
                            width: mode === 1 ? 90 :120
                        }
                        TableViewColumn {
                            role: "date"
                            title: "日期"
                            width: mode === 1 ? 90 :120
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
    }
    Component{
        id:multipro
        MultideviceProductionModule{
            id:mupMode
            width: 1280
            height: 740
            Connections{
                target: window
                function onSigEquipmentCountChanged(id){
                    mupMode.itemCount = id
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
