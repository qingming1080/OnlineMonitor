﻿import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15
import QtQml.Models 2.15
import "TimeUtils.js" as TimeUtils
Rectangle {
    color: pRgb(153, 204, 255)
    //    Rectangle{
    //        x:78
    //        y:29
    //        width: 1133
    //        height: 664
    //        color: pRgb(43, 112, 173)
    //        radius: 5
    SwipePage {
        id:view
        x:30
        y:29
        width: 1220
        height: 664
        color: pRgb(43, 112, 173)
        radius: 5
    }
    //    SwipeView{
    //        id:view
    //        x:58
    //        y:29
    //        width: 1173
    //        height: 664
    //        background: Rectangle{
    //            color: pRgb(43, 112, 173)
    //            radius: 5
    //        }
    //        clip: true
    //        Component.onCompleted: {
    //            //                for(var j = 0; j < equipmentCount;j++){
    //            //                    addPage(j)
    //            //                }
    //            view.setCurrentIndex(swipeIndex)
    //        }

    //        onCurrentIndexChanged: {
    //            swipeCurrIndex = view.currentIndex
    //            sigUpdateUI(view.currentIndex)
    //        }
    //        SwipePage {
    //            width: view.width
    //            height: view.height
    //            color:"transparent"
    //        }
    //        //            Loader {
    //        //                sourceComponent: view1
    //        //                asynchronous:true
    //        //                active: view.currentIndex === 0
    //        //            }
    //        //            Loader {
    //        //                sourceComponent: view2
    //        //                asynchronous:true
    //        //                active: view.currentIndex === 1
    //        //            }
    //        //            Loader {
    //        //                sourceComponent: view3
    //        //                asynchronous:true
    //        //                active: view.currentIndex === 2
    //        //            }
    //        //            Loader {
    //        //                sourceComponent: view4
    //        //                asynchronous:true
    //        //                active: view.currentIndex === 3
    //        //            }
    //        //            Component {
    //        //                id: view1
    //        //                SwipePage {
    //        //                    pbtnIndex:rect1
    //        //                    width: view.width
    //        //                    height: view.height
    //        //                    color:"transparent"
    //        //                }
    //        //            }

    //        //            Component {
    //        //                id: view2
    //        //                SwipePage {
    //        //                    pbtnIndex:rect2
    //        //                    width: view.width
    //        //                    height: view.height
    //        //                    color:"transparent"
    //        //                }
    //        //            }

    //        //            Component {
    //        //                id: view3
    //        //                SwipePage {
    //        //                    width: view.width
    //        //                    height: view.height
    //        //                    color:"transparent"
    //        //                }
    //        //            }
    //        //            Component {
    //        //                id: view4
    //        //                SwipePage {
    //        //                    width: view.width
    //        //                    height: view.height
    //        //                    color:"transparent"
    //        //                }
    //        //            }
    //        function addPage(index) {
    //            var pageComponent = Qt.createComponent("SwipePage.qml");
    //            if (pageComponent.status === Component.Ready) {
    //                if(index === 0){
    //                    var page = pageComponent.createObject(view, {"pbtnIndex":rect1,"width": view.width, "height": view.height,"color":"transparent"});
    //                }
    //                else if(index === 1){
    //                    page = pageComponent.createObject(view, {"pbtnIndex":rect2,"width": view.width, "height": view.height,"color":"transparent"});
    //                }
    //                else{
    //                    page = pageComponent.createObject(view, {"width": view.width, "height": view.height,"color":"transparent"});
    //                }
    //                view.addItem(page)
    //            }
    //        }
    //        function removePage() {
    //            if (view.count > 0) {
    //                var num = view.count
    //                for(var i = 0;i < num;i++){
    //                    var lastPage = view.contentChildren[i]
    //                    view.removeItem(lastPage);
    //                }
    //            }
    //        }
    //        //        }
    ////        PageIndicator {
    ////            id: indicator
    ////            count: equipmentCount
    ////            currentIndex: view.currentIndex
    ////            spacing: 33
    ////            anchors.bottom: view.bottom
    ////            anchors.bottomMargin: 20
    ////            anchors.horizontalCenter: parent.horizontalCenter
    ////            delegate: Rectangle {
    ////                width: 20
    ////                height: 20
    ////                radius: 10
    ////                border.width: 2
    ////                border.color: "#149bff"
    ////                color: index === indicator.currentIndex ? "#0c5696" : "#e8e8e8"
    ////            }
    ////        }
    //    }


    Button{
        x:1206
        y:34
        width: 40
        height: 40
        background: Rectangle{
            color: "transparent"
            Image {
                anchors.centerIn: parent
                source: "qrc:/image/reduce.png"
            }
        }
        onPressed: {
            if(equipmentCount === 3){
                swipeCurrIndex = 0
            }
            swipevis = false
            loadViewpro(2,multipro)
        }
        visible: !createModel
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
        text: TimeUtils.getCurrentTime()

        // 定时器每秒更新一次
        Timer {
            interval: 1  // 1秒
            repeat: true
            running: true
            onTriggered: {
                timeText.text = TimeUtils.getCurrentTime()
            }
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            drag.target: timeDialog
            onClicked: {
                timeDialog.open()  // 点击时弹出对话框
            }
        }
    }

    TimeSettingDialog {
            id: timeDialog
            onTimeSelected: {
                // 接收 timeDialog 中发出的 timeSelected 信号，并更新 timeText 显示的时间
                let date = new Date(year, month - 1, day, hour, minute, second);  // JavaScript 中月份是从 0 开始的
                timeText.text = date.toLocaleString();  // 将选中的时间转为本地时间字符串
            }
        }
}
