import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15
import QtQml.Models 2.15
Rectangle {
    color: pRgb(153, 204, 255)
    Connections{
        target: window
        function onEquipmentCountChanged(){
            updateUI()
        }
        function onSigNewModel(){
            var lastPage = view.contentChildren[view.currentIndex]
            lastPage.newModel()
            view.interactive = false
        }
        function onSigRecover(){
            view.interactive = true
        }
    }
    Connections{
        target: mpro
        function onSigSwipeCurrIndex(index){
            view.setCurrentIndex(index)
        }
    }
    function updateUI(){
//        view.removePage()
//        for(var j = 0; j < equipmentCount;j++){
//            view.addPage(j)
//        }
        sigUpdateUI(view.currentIndex)
    }
    Rectangle{
        x:78
        y:29
        width: 1133
        height: 664
        color: pRgb(43, 112, 173)
        radius: 5
        SwipeView{
            id:view
            anchors.fill: parent
            clip: true
            Component.onCompleted: {
//                for(var j = 0; j < equipmentCount;j++){
//                    addPage(j)
//                }
                view.setCurrentIndex(swipeIndex)
            }

            onCurrentIndexChanged: {
                swipeCurrIndex = view.currentIndex
                sigUpdateUI(view.currentIndex)
            }
            Loader {
                sourceComponent: view1
                asynchronous:true
                active: swipeView.currentIndex === 0
            }
            Loader {
                sourceComponent: view2
                asynchronous:true
                active: swipeView.currentIndex === 1
            }
            Loader {
                sourceComponent: view3
                asynchronous:true
                active: swipeView.currentIndex === 2
            }
            Loader {
                sourceComponent: view4
                asynchronous:true
                active: swipeView.currentIndex === 3
            }
            Component {
                id: view1
                SwipePage {
                    pbtnIndex:rect1
                    width: view.width
                    height: view.height
                    color:"transparent"
                }
            }

            Component {
                id: view2
                SwipePage {
                    pbtnIndex:rect2
                    width: view.width
                    height: view.height
                    color:"transparent"
                }
            }

            Component {
                id: view3
                SwipePage {
                    width: view.width
                    height: view.height
                    color:"transparent"
                }
            }
            Component {
                id: view4
                SwipePage {
                    width: view.width
                    height: view.height
                    color:"transparent"
                }
            }
            function addPage(index) {
                var pageComponent = Qt.createComponent("SwipePage.qml");
                if (pageComponent.status === Component.Ready) {
                    if(index === 0){
                        var page = pageComponent.createObject(view, {"pbtnIndex":rect1,"width": view.width, "height": view.height,"color":"transparent"});
                    }
                    else if(index === 1){
                        page = pageComponent.createObject(view, {"pbtnIndex":rect2,"width": view.width, "height": view.height,"color":"transparent"});
                    }
                    else{
                        page = pageComponent.createObject(view, {"width": view.width, "height": view.height,"color":"transparent"});
                    }
                    view.addItem(page)
                }
            }
            function removePage() {
                if (view.count > 0) {
                    var num = view.count
                    for(var i = 0;i < num;i++){
                        var lastPage = view.contentChildren[i]
                        view.removeItem(lastPage);
                    }
                }
            }
        }
        PageIndicator {
            id: indicator
            count: equipmentCount
            currentIndex: view.currentIndex
            spacing: 33
            anchors.bottom: view.bottom
            anchors.bottomMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            delegate: Rectangle {
                width: 20
                height: 20
                radius: 10
                border.width: 2
                border.color: "#149bff"
                color: index === indicator.currentIndex ? "#0c5696" : "#e8e8e8"
            }
        }
    }


    Button{
        x:1176
        y:34
        width: 30
        height: 30
        background: Rectangle{
            color: "transparent"
            Image {
                anchors.fill: parent
                source: "qrc:/image/reduce.png"
            }
        }
        onPressed: {
            loadViewpro(2,multipro)
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
