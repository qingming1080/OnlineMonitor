import QtQuick 2.6
import QtQuick.Window 2.12
import QtQuick.Window 2.3
import QtQuick.Layouts 1.12
import QtQuick.VirtualKeyboard 2.2
import QtQuick.Controls 2.5
import QtQuick.VirtualKeyboard.Settings 2.2
import "."
import Device 1.0
import DeviceObj    1.0
import QtQml 2.15


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
    property int interFaceId: 0
    property int keyboardType: 0
    property bool isUSBAvailable: false

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


    // 缓存已加载的视图
    property var cachedViews: []
    signal sigSwitch(var id)
    signal sigSysConfig()
    signal sigStatusReset()
    signal sigUpdateUI(var index)
    signal sigRoot()
    signal sigNewModel()
    signal sigOneModel()
    signal sigPassError()
    signal sigDelDevice()
    signal sigRecover()
    function switchUI(id)
    {
        sigSwitch(id)
        // sigUpdateUI(swipeCurrIndex)
    }

    //Only one time running
    function releaseWelcomeScreen()
    {
        inputPannelID.y = window.height
        welcomeScreen.visible = false

        if(DeviceManager.DeviceList[0].WelderID === -1)
        {
            loadView(3, sys)
        }
        else
            loadView(1, pro)

        inputPannelID.visible = true;

    }

    function showWelcomeScreen()
    {
        welcomeScreen.visible = true
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

    function showLoading(isShow)
    {
        if(isShow === false)
            loadingOverlay.progress = 0.0
        loadingOverlay.visible = isShow;
    }

    function showDialog(title, text)
    {
        mesDialog.openFor(title,text)
    }

    function showPrimaryNumpad(strTitle, strUnit, iDecimals, realMinimum, realMaximum, strCurrentValue, targetObj, onConfirmCallback)
    {
        primaryNumpad.headertext = strTitle
        primaryNumpad.suffix = strUnit
        primaryNumpad.decimals = iDecimals
        primaryNumpad.minimumValue = realMinimum
        primaryNumpad.maximumValue = realMaximum
        primaryNumpad.value = strCurrentValue
        primaryNumpad.targetTextField = targetObj
        primaryNumpad.confirmCallback = onConfirmCallback
        primaryNumpad.visible = true
        primaryNumpad.selectAll()
    }

    Connections {
        target: History
        function onSignalExportPrograss(current, total)
        {
            if(loadingOverlay.visible === true)
            {
                loadingOverlay.progress = (current + 1) / total
            }
        }
    }
    Connections
    {
        target: window
        function onSigSwitch(id)
        {
            stackView.clear()
            interFaceId = id
            switch(id)
            {
            case 1:
                loadView(id, pro)
                // p1.bt1Check()
                break;
            case 2:
                loadView(id, his)
                // p1.bt2Check()
                break;
            case 3:
                sigSysConfig()
                Qt.callLater(sigSysConfig)//立即执行
                loadView(id, sys)
                sigStatusReset()
                // p1.bt3Check()
                break;
            case 4:
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
        }
        Footer
        {
            id: footer
            anchors.left: parent.left
            anchors.bottom: parent.bottom
        }
    }

    MessageDialog
    {
        id: mesDialog
    }

    Loading{
        id:loadingOverlay
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        z: 3
        visible: false
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
        ProductionWindow{
            id:s1
            width: 1280
            height: 740
        }
    }

    Component{
        id:his
        HistoryModel{
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
        id: popup
        width: 567
        height: 271
        anchors.centerIn: parent
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
        width: /*keyboardType === 0 ? 400 :*/ window.width
        visible: false       // 一直显示
        states: State
        {
            name: "visible"
            when: inputPannelID.active
            PropertyChanges
            {
                target: inputPannelID
                y: window.height - inputPannelID.height
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

    /*KeyBoard*/
    BransonPrimaryNumpad
    {
        id:primaryNumpad
        visible: false
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        z: 2
    }
}




