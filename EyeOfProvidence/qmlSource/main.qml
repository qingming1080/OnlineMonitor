import QtQuick          2.6
import QtQuick.Window   2.12
import QtQuick.Window   2.3
import QtQuick.Layouts  1.12
import QtQuick.Controls 2.5
import "."
import Device           1.0
import DeviceObj        1.0
import QtQml            2.15


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
    property bool isUSBAvailable: false
    property var currentField: null

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
    signal sigRoot()
    signal sigNewModel()
    signal sigOneModel()
    signal sigPassError()
    signal sigDelDevice()
    signal signalOneSecondEvent()
    function switchUI(id)
    {
        sigSwitch(id)
    }

    //Only one time running
    function releaseWelcomeScreen()
    {
        welcomeScreen.visible = false

        if(DeviceManager.DeviceList[0].WelderID === -1)
        {
            // loadView(3, sys)
            loadView(3, null)
        }
        else
            // loadView(1, pro)
            loadView(1, null)
    }

    function showWelcomeScreen()
    {
        welcomeScreen.visible = true
    }

    // 动态加载和缓存视图
    function loadView(viewName, component)
    {
        // stackView.clear()

        // if (cachedViews[viewName])
        // {
        //     // 如果视图已缓存，直接显示
        //     stackView.push(cachedViews[viewName]);
        // }
        // else
        // {
            // 创建视图并缓存
            // var newItem = component.createObject(stackView);
            // cachedViews[viewName] = newItem;
            // stackView.push(newItem);
        // }
        stackView.source = ""
        switch(viewName)
        {
        case 1:
            stackView.source = "qrc:/qmlSource/ProductionWindow.qml"
            break;
        case 2:
            stackView.source = "qrc:/qmlSource/HistoryModel.qml"
            break;
        case 3:
            stackView.source = "qrc:/qmlSource/SystemConfig.qml"
            break;
        case 4:
            stackView.source = "qrc:/qmlSource/AdminConfigView.qml"
            break;
        default:
            stackView.source = ""
            break;
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
    function showFullKeyboard(textField)
    {
        if (textField) {
            currentField = textField
            textField.focus = true
            textField.selectAll()
            inputPannelID.active = true
            inputPannelID.pinyinBuffer = ""
        }
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
            interFaceId = id
            switch(id)
            {
            case 1:
                loadView(id, null)
                // p1.bt1Check()
                break;
            case 2:
                loadView(id, null)
                // p1.bt2Check()
                break;
            case 3:
                sigSysConfig()
                Qt.callLater(sigSysConfig)//立即执行
                loadView(id, null)
                sigStatusReset()
                // p1.bt3Check()
                break;
            case 4:
                loadView(id, null)
                break;
            default:
                break;
            }
        }
    }


    Header{
        id: header
        anchors.top: parent.top
        anchors.left: parent.left
        width: showWidth
        height: 60
    }

    Footer
    {
        id: footer
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        width: showWidth
        height: 40
    }

    Loader{
        id: stackView
        anchors.top: header.bottom
        anchors.bottom: footer.top
        anchors.left: parent.left
        width: showWidth
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

    CustomDialog{
        id: popup
        width: 567
        height: 271
        y: window.width / 7
        x: window.height / 2 - 50
        onSigInputFieldFocusChanged: {
            if (focused)
            {
                window.currentField = textField
                Qt.callLater(function()
                {
                    inputPannelID.active = true
                    inputPannelID.pinyinBuffer = ""
                })
            }
            else
            {
                inputPannelID.active = false
            }
        }
    }

    HBKeyboard
    {
        id: inputPannelID
        z: 999  // 确保虚拟键盘在所有元素之上，包括弹窗
        width: window.width
        visible: false
        y: window.height  // 初始位置在屏幕底部下方
        states: State
        {
            name: "visible"
            when: inputPannelID.active
            PropertyChanges
            {
                target: inputPannelID
                y: window.height - inputPannelID.height
                visible: true
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
                    easing.type: Easing.OutQuart
                }
            }
        }
        onKeyPressed:
        {
            if(currentField)
            {
                currentField.text = currentField.text + key
                currentField.cursorPosition = currentField.text.length
            }
        }
        onBackspace:
        {
            if (currentField)
            {
                if (currentField.text.length > 0)
                {
                    currentField.text = currentField.text.slice(0, -1)
                    currentField.cursorPosition = currentField.text.length
                }
            }
        }
        onEnter:
        {
            inputPannelID.active = false
            if (currentField)
            {
                currentField.focus = false
            }
        }
        onSpace:
        {
            if (currentField)
            {
                currentField.text = currentField.text + " "
                currentField.cursorPosition = currentField.text.length
            }
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
    HBDateTimeSetting
    {
        id: dateTimeSetting
        anchors.centerIn: parent
        visible:false
        z:100
    }


    Timer
    {
        id: timer
        interval: 1000
        repeat: true
        running: true
        onTriggered:
        {
            signalOneSecondEvent()
        }
    }
}




