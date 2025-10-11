import QtQuick 2.6
import QtQuick.Window 2.12
import QtQuick.Window 2.3
import QtQuick.Layouts 1.12
import QtQuick.VirtualKeyboard 2.2
import QtQuick.Controls 2.5
import QtQuick.VirtualKeyboard.Settings 2.2
import "."
import Device 1.0
import DeviceInformation 1.0
import QtQml 2.15
import "TimeUtils.js" as TimeUtils


Window {
    id: window
    flags: Qt.FramelessWindowHint
    visible: true
    width: 1280
    height: 800
    x: 0
    property int showWidth: 1280
    property int showHeight: 800
    property int mode: 0
    property int equipmentCount: DeviceManager.deviceNum
    property int equipmentCurrentIndex: 0
    property int swipeCurrIndex: 0
    property int interFaceId: 0
    property var keyboardYype: 0
    property bool createModel: false
    property bool swipevis: false

    onSwipeCurrIndexChanged: {
        sigSwipeCurrIndex(swipeCurrIndex)
    }

    property bool altitudeModel1: {
        if(DeviceManager.deviceList[0]){
            DeviceManager.deviceList[0].DevInfoObject.heightOption === 0 ? false : true
        }
        else{
            return false
        }
    }
    property bool altitudeModel2: {
        if(DeviceManager.deviceList[1]){
            DeviceManager.deviceList[1].DevInfoObject.heightOption === 0 ? false : true
        }
        else{
            return false
        }
    }
    property bool altitudeModel3: {
        if(DeviceManager.deviceList[2]){
            DeviceManager.deviceList[2].DevInfoObject.heightOption === 0 ? false : true
        }
        else{
            return false
        }
    }
    property bool altitudeModel4: {
        if(DeviceManager.deviceList[3]){
            DeviceManager.deviceList[3].DevInfoObject.heightOption === 0 ? false : true
        }
        else{
            return false
        }
    }
    property bool isAdd: false
    function pRgb(r, g, b){
        var ret = (r << 16 | g << 8 | b)
        return ("#"+ret.toString(16)).toUpperCase();
    }
    function disableConsoleLog() {
        // 重定向 console.log() 到一个空函数
        console.log = function() {};
    }

    Component.onCompleted: {
        // 调用函数来禁用控制台打印
       disableConsoleLog();
    }

    //TODO Need to remove later
    Timer {
        id: startTimer
        interval: 1000  // 延时1秒
        running: true
        repeat: false
        onTriggered: {
               ModbusClient.setSysLedStatus(true)
        }
    }

    // 缓存已加载的视图
    property var cachedViews: []
    signal sigSwitch(var id)
    signal sigSysConfig()
    signal sigStatusReset()
    signal sigUpdateUI(var index)
    signal sigUndetermined(var index)
    signal sigRoot()
    signal sigNewModel()
    signal sigOneModel()
    signal sigPassError()
    signal sigDelDevice()
    signal sigRecover()
    signal sigSwipeCurrIndex(var swipeCurrIndex)
    function switchUI(id)
    {
        equipmentCurrentIndex = id
        sigSwitch(id)
        sigUpdateUI(swipeCurrIndex)
    }

    //Only one time running
    function releaseWelcomeScreen()
    {
        welcomeScreen.source = ""
    }

    // 动态加载和缓存视图
    function loadView(viewName, component)
    {
        if (cachedViews[viewName])
        {
            // 如果视图已缓存，直接显示
            stackView.push(cachedViews[viewName]);
        }
        else
        {
            // 创建视图并缓存
            var newItem = component.createObject(stackView);
            cachedViews[viewName] = newItem;
            stackView.push(newItem);
        }
    }

    Connections
    {
        target: window
        function onSigSwitch(id)
        {
            stackView.pop()
            interFaceId = id
            switch(id)
            {
            case 1:
                loadView(id, pro)
                p1.bt1Check()
                isAdd = false
                break;
            case 2:
                loadView(id, his)
                p1.bt2Check()
                isAdd = false
                break;
            case 3:
                isAdd = false
                sigSysConfig()
                Qt.callLater(sigSysConfig)//立即执行
                loadView(id, sys)
                sigStatusReset()
                p1.bt3Check()
                break;
            case 4:
                isAdd = false
                loadView(id, rootview)
                break;
            default:
                break;
            }
        }
    }

    Item{
        anchors.fill: parent
        Header{
            id: header
            anchors.top: parent.top
            anchors.left: parent.left
            width: showWidth
            height: 60
        }
        StackView{
            id: stackView
            anchors.top: header.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            width: showWidth
            Component.onCompleted:
            {
                loadView(1, pro)
                sigUpdateUI(0)
            }
        }
    }

    Loader{
        id: welcomeScreen
        visible: true
        anchors.fill: parent
        width: showWidth
        height: showHeight
        source: "qrc:/qmlSource/Welcome.qml"
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
        id:rootview
        RootConfigView{
            width: 1280
            height: 740
        }
    }

    CustomDialog{
        id:popup
        width: 567
        height: 271
        x:window.width/2 - 567/2
        y:window.height/2 - 271
    }

    Binding {
        id:bin
        target: inputPannelID.keyboard.style
        property: 'keyboardDesignWidth'
    }

    InputPanel
    {
        id: inputPannelID
        z: 99
        x: window.width/2-inputPannelID.width/2
        y: window.height      // 默认让其处于窗口最下方,貌似隐藏一样
        width: /*keyboardYype === 0 ? 400 :*/ window.width
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
            VirtualKeyboardSettings.wordCandidateList.alwaysVisible = true
            VirtualKeyboardSettings.activeLocales = ["en_US","zh_CN"/*,"ja_JP"*/]   // 英语、中文、日语 (若不设置,则语言就有很多种)
        }
    }
}



