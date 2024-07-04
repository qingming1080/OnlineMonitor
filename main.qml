import QtQuick 2.6
import QtQuick.Window 2.12
import QtQuick.Window 2.3
import QtQuick.Layouts 1.12
import QtQuick.VirtualKeyboard 2.2
import QtQuick.Controls 2.5
import QtQuick.VirtualKeyboard.Settings 2.2
import "./qmlSource"
import Device 1.0
import DeviceInformation 1.0

Window {
    id: window
    visible: true
    width: 1280
    height: 800
    x:0
    property int mode: 0
    property int equipmentCount: DeviceManager.deviceNum
    property int equipmentCurrentIndex: 0
    property int swipeCurrIndex: 0
    FontLoader {
        id: normal
        source: "qrc:/fonts/SourceHanSansCN-Normal.ttf"
    }
    FontLoader {
        id: bold
        source: "qrc:/fonts/SourceHanSansCN-Bold.ttf"
    }
    property string fontNormal: normal.name
    property string fontBold: bold.name
    property bool altitudeModel1: false
    property bool altitudeModel2: false
    property bool altitudeModel3: false
    property bool altitudeModel4: false
    property bool isAdd: false
    function pRgb(r, g, b){
        var ret = (r << 16 | g << 8 | b)
        return ("#"+ret.toString(16)).toUpperCase();
    }
    //    function disableConsoleLog() {
    //        // 重定向 console.log() 到一个空函数
    //        console.log = function() {};
    //    }

    //    Component.onCompleted: {
    //        // 调用函数来禁用控制台打印
    //        disableConsoleLog();
    //    }
    // 缓存已加载的视图
    property var cachedViews: []
    signal sigSwitch(var id)
    signal sigSysConfig()
    signal sigStatusReset()
    signal sigUpdateUI(var index)
    signal sigUndetermined(var index)
    function switchUI(id){
        equipmentCurrentIndex = id
        sigSwitch(id)
        sigUpdateUI(swipeCurrIndex)
    }

    // 获取当前时间的函数
    function getCurrentTime() {
        var date = new Date()
        var year = date.getFullYear()
        var month = date.getMonth() + 1 // 月份从0开始，需要加1
        var day = date.getDate()
        var hours = date.getHours()
        var minutes = date.getMinutes()
        var seconds = date.getSeconds()
        var dayOfWeek = date.getDay()

        // 星期数组
        var daysOfWeek = ["星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"]

        // 格式化时间字符串
        return year + "年" + formatTimeComponent(month) + "月" + formatTimeComponent(day) + "日 " +
                formatTimeComponent(hours) + ":" + formatTimeComponent(minutes) + ":" + formatTimeComponent(seconds) + " " +
                daysOfWeek[dayOfWeek]
    }

    // 格式化时间组件为两位数字
    function formatTimeComponent(component) {
        return component < 10 ? "0" + component : component
    }

    StackView{
        id:stackView
        initialItem: loadUI
    }
    Component{
        id: homeComponent
        Item{
            TopModule{
                id:p1
                width: 1280
                height: 60
            }
            StackView{
                id:stackView1
                anchors.top: p1.bottom
                Component.onCompleted: {
                    loadView(1,pro)
                    sigUpdateUI(0)
                }
            }
            Connections{
                target: window
                function onSigSwitch(id){
                    stackView1.pop()
                    if(id === 1){
                        loadView(id,pro)
                        p1.bt1Check()
                        isAdd = false
                    }
                    else if(id === 2){
                        loadView(id,his)
                        p1.bt2Check()
                        isAdd = false
                    }
                    else if(id === 3){
                        isAdd = false
                        sigSysConfig()
                        Qt.callLater(sigSysConfig)//立即执行
                        loadView(id,sys)
                        sigStatusReset()
                        p1.bt3Check()
                    }
                }
            }

            // 动态加载和缓存视图
            function loadView(viewName, component) {
                if (cachedViews[viewName]) {
                    // 如果视图已缓存，直接显示
                    stackView1.push(cachedViews[viewName]);
                } else {
                    // 创建视图并缓存
                    var newItem = component.createObject(stackView1);
                    cachedViews[viewName] = newItem;
                    stackView1.push(newItem);
                }
            }
        }
    }
    Timer {
        id:loadtime
        interval: 2000
        running : true
        onTriggered:{
            stackView.pop()
            stackView.push(homeComponent)
        }
    }
    Component{
        id:loadUI
        Load{
            width: 1280
            height: 800
        }
    }
    Component{
        id:pro
        ProductionModule{
            id:s1
            width: 1280
            height: 740
        }
    }
    Component{
        id:his
        HistoryModule{
            id:hisin
            width: 1280
            height: 740
        }
    }
    Component{
        id:sys
        SystemConfig{
            id: sysin
            width: 1280
            height: 740
        }
    }

    Component{
        id:swipepro
        SwipeProductionModule{
            id:swpMode
            width: 1280
            height: 740
        }
    }
    CustomDialog{
        id:popup
        width: 567
        height: 271
        anchors.centerIn: parent
    }
//    RootConfig{
//        id:swpMode
//        width: 1280
//        height: 740
//    }

    InputPanel
    {
        id: inputPannelID
        z: 99
        y: window.height      // 默认让其处于窗口最下方,貌似隐藏一样
        width: window.width
        visible: true       // 一直显示
        states: State
        {
            name: "visible"
            when: inputPannelID.active
            PropertyChanges
            {
                target: inputPannelID
                y: window.height-inputPannelID.height
            }
        }
        transitions: Transition
        {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation
            {
                NumberAnimation
                {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
        Component.onCompleted:
        {
            //            VirtualKeyboardSettings.styleName = "retro"                         // 复古样式
            VirtualKeyboardSettings.wordCandidateList.alwaysVisible = true
            VirtualKeyboardSettings.activeLocales = ["en_US","zh_CN"/*,"ja_JP"*/]   // 英语、中文、日语 (若不设置,则语言就有很多种)
        }
    }
}
