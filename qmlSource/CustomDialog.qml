﻿import QtQuick 2.0
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import QmlEnum 1.0
Popup {
    id:customPopup
    width: 567
    height: 271
    modal: true
    padding:0
    closePolicy:Popup.CloseOnEscape
    property int id: 0
    signal sigDataClear()
    function openPop(index){//1输入密码(配置) 2输入密码(新建模型) 3输入密码(新建模型单设备)
        //4语言 5采样 6系统消息 7修改密码 8新增设备 9删除设备 10系统保存 11输入范围
        id = index
        if(index === 1 || index === 2 || index === 3 || index === 8 || index === 9){
            sigDataClear()
            popload.sourceComponent = inputpass
            open()
        }
        else if(index === 4){
            popload.sourceComponent = language
            open()
        }
        else if(index === 5){
            popload.sourceComponent = dataeficiency
            open()
        }
        else if(index === 6){
            popload.sourceComponent = sysInfor
            open()
        }
        else if(index === 7){
            popload.sourceComponent = newpass
            open()
        }
        else if(index === 10){
            popload.sourceComponent = sysConfig
            open()
        }
        else if(index === 11){
            popload.sourceComponent = scope
            open()
        }
    }
    onClosed:{
        id = 0
    }

    background: Rectangle{
        color: "transparent"
        radius: 5
    }
    MouseArea {
        anchors.fill: parent
        drag.target: parent
    }
    Rectangle{
        id:top
        anchors.top: parent.top
        anchors.left: parent.left
        width: 567
        height: 33
        radius: 3
        color: "#004b8d"
        Button{
            x:536
            y:4
            width: 26
            height: 26
            background: Rectangle{
                color: "transparent"
                Image {
                    source: "qrc:/image/close.png"
                }
            }
            onPressed: {
                customPopup.close()
                sigPassError()
            }
        }
    }
    Loader{
        id:popload
        Component.onCompleted: {
            popload.sourceComponent = language
        }
    }

    Component{
        id:inputpass
        Rectangle{
            y:33
            width: 567
            height: 236
            color: "#b1d5db"
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                y:49
                text: qsTr("请输入操作员密码")
                font.pixelSize: 20
                color: "#004b8d"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: fontBold
                font.bold: true
            }
            TextField{
                id:t1
                width: 243
                height: 52
                x:162
                y:103
                horizontalAlignment: TextInput.AlignHCenter
                verticalAlignment: TextInput.AlignVCenter
                color: "#004b8d"
                font.family: fontBold
                font.bold: true
                font.pixelSize: 20

                //设置密码输入的字符为星号（*）
                echoMode: TextInput.Password //密码模式，输入的字符变成星号

                background: Rectangle{
                    radius: 6
                }
                onFocusChanged: {
                    if(focus){
                        keyboardYype = 1
                    }
                }
            }
            Connections{
                target: customPopup
                function onSigDataClear(){
                    t1.text = ""
                }
            }

            Button{
                id:s1
                x:170
                y:165
                width: 230
                height: 52
                background: Rectangle{
                    radius: 6
                    color: pRgb(43, 112, 173)
                }
                contentItem: Text {
                    id: mt1
                    text: qsTr("确认")
                    font.pixelSize: mode == 1 ? 17:20
                    color: pRgb(153, 204, 255)
                    anchors.centerIn: parent  // 确保文本在按钮内居中对齐
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.family: fontBold
                    font.bold: true
                }
                onPressed: {
                    if(DeviceManager.getPasswordLevel(t1.text) === 1){
                        close()
                        sigRoot()
                    }
                    else if(DeviceManager.getPasswordLevel(t1.text) === 2){
                        if(id === 2){
                            sigNewModel()
                        }
                        else if(id === 1){
                            sigSwitch(3)
                        }
                        else if(id === 3){
                            sigOneModel()
                        }
                        else if(id === 8){
                            switchUI(3)
                            isAdd = true
                            sigSysConfig()
                        }
                        else if(id === 9){
                            sigDelDevice()
                        }
                        close()
                    }
                    else{
                        popload.sourceComponent = passerror
                    }
                }
            }
        }
    }
    Component{
        id:passerror
        Rectangle{
            y:33
            width: 567
            height: 236
            color: "#b1d5db"
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                y:49
                text: qsTr("密码错误请重新输入!")
                font.pixelSize: 20
                color: "#004b8d"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: fontBold
                font.bold: true
            }
            Button{
                id:s4
                x:170
                y:165
                width: 243
                height: 52
                background: Rectangle{
                    radius: 6
                    color: pRgb(43, 112, 173)
                }
                contentItem: Text {
                    id: mt1
                    text:qsTr("确认")
                    font.pixelSize: mode == 1 ? 17:20
                    color: pRgb(153, 204, 255)
                    anchors.centerIn: parent  // 确保文本在按钮内居中对齐
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.family: fontBold
                    font.bold: true
                }
                onPressed: {
                    close()
                    sigPassError()
                }
            }
        }
    }
    Component{
        id:newpass
        Rectangle{
            y:33
            width: 567
            height: 236
            color: "#b1d5db"
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                y:49
                text: qsTr("请输入新密码")
                font.pixelSize: 20
                color: "#004b8d"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: fontBold
                font.bold: true
            }
            TextField{
                id:t1
                width: 243
                height: 52
                x:162
                y:103
                horizontalAlignment: TextInput.AlignHCenter
                verticalAlignment: TextInput.AlignVCenter
                color: "#004b8d"
                font.family: fontBold
                font.bold: true
                font.pixelSize: 20
                background: Rectangle{
                    radius: 6
                }
                onFocusChanged: {
                    if(focus){
                        keyboardYype = 1
                    }
                }
            }
            Button{
                id:s4
                x:170
                y:165
                width: 225
                height: 52
                background: Rectangle{
                    radius: 6
                    color: pRgb(43, 112, 173)
                }
                contentItem: Text {
                    id: mt1
                    text: qsTr("确认")
                    font.pixelSize: mode == 1 ? 17:20
                    color: pRgb(153, 204, 255)
                    anchors.centerIn: parent  // 确保文本在按钮内居中对齐
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.family: fontBold
                    font.bold: true
                }
                onPressed: {
                    DeviceManager.setUserPassword(t1.text)
                    close()
                }
            }
        }
    }
    Component{
        id:dataeficiency
        Rectangle{
            y:33
            width: 567
            height: 236
            color: "#b1d5db"
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                y:49
                text: qsTr("样本数不足请继续采样!")
                font.pixelSize: 20
                color: "#004b8d"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: fontBold
                font.bold: true
            }
            Button{
                id:s4
                x:170
                y:165
                width: 243
                height: 52
                background: Rectangle{
                    radius: 6
                    color: pRgb(43, 112, 173)
                }
                contentItem: Text {
                    id: mt1
                    text: qsTr("确认")
                    font.pixelSize: mode == 1 ? 17:20
                    color: pRgb(153, 204, 255)
                    anchors.centerIn: parent  // 确保文本在按钮内居中对齐
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.family: fontBold
                    font.bold: true
                }
                onPressed: {
                    close()
                }
            }
        }
    }
    Component{
        id:scope
        Rectangle{
            y:33
            width: 567
            height: 236
            color: "#b1d5db"
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                y:49
                text: qsTr("输入范围错误请重新输入!")
                font.pixelSize: 20
                color: "#004b8d"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: fontBold
                font.bold: true
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                y:69
                text: qsTr("最大生产批量上下限（2w-100w）")
                font.pixelSize: 20
                color: "#004b8d"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: fontBold
                font.bold: true
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                y:89
                text: qsTr("学习样本数上下限（10~20个）")
                font.pixelSize: 20
                color: "#004b8d"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: fontBold
                font.bold: true
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                y:109
                text: qsTr("良率下限区间（90-99）")
                font.pixelSize: 20
                color: "#004b8d"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: fontBold
                font.bold: true
            }
            Button{
                id:s4
                x:170
                y:165
                width: 243
                height: 52
                background: Rectangle{
                    radius: 6
                    color: pRgb(43, 112, 173)
                }
                contentItem: Text {
                    id: mt1
                    text: qsTr("确认")
                    font.pixelSize: mode == 1 ? 17:20
                    color: pRgb(153, 204, 255)
                    anchors.centerIn: parent  // 确保文本在按钮内居中对齐
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.family: fontBold
                    font.bold: true
                }
                onPressed: {
                    close()
                }
            }
        }
    }

    Component{
        id:language
        Rectangle{
            y:33
            width: 567
            height: 236
            color: "#b1d5db"
            Text {
                id: s1
                x:262
                y:35
                text: qsTr("简体中文")
                color: "#004b8d"
                font.family: fontBold
                font.bold: true
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            RadioButton{
                id:bt1
                width: 30
                height: 30
                x:208
                y:33
                checked:true
                indicator: Rectangle
                {
                    width: 30
                    height: 30
                    radius: 15
                    color: LanguageManger.language === "SimplifiedChinese" ? "#0d988c" : pRgb(232, 232, 232)
                    border.color: "#004b8d"
                    border.width: 2
                }
                onPressed: LanguageManger.loadLanguage("SimplifiedChinese")

            }
            Text {
                id: s2
                x:262
                y:100
                text: qsTr("English")
                color: "#004b8d"
                font.family: fontBold
                font.bold: true
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            RadioButton{
                id:bt2
                width: 30
                height: 30
                x:208
                y:99
                indicator: Rectangle
                {
                    width: 30
                    height: 30
                    radius: 15
                    color: LanguageManger.language === "English" ? "#0d988c" : pRgb(232, 232, 232)
                    border.color: "#004b8d"
                    border.width: 2
                }
                onPressed: LanguageManger.loadLanguage("English")
            }
            Text {
                id: s3
                x:262
                y:165
                text: qsTr("其他语言")
                color: "#004b8d"
                font.family: fontBold
                font.bold: true
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            RadioButton{
                id:bt3
                width: 30
                height: 30
                x:208
                y:164
                indicator: Rectangle
                {
                    width: 30
                    height: 30
                    radius: 15
                    color: bt3.checked ? "#0d988c" : pRgb(232, 232, 232)
                    border.color: "#004b8d"
                    border.width: 2
                }
                onPressed: {

                }
            }
        }
    }

    Component{
        id:sysInfor
        Rectangle{
            y:33
            width: 567
            height: 236
            color: "#b1d5db"
            ListView{
                id: taskplanView
                width: 260
                height: 220
                anchors.centerIn: parent
                model: Message
                delegate: Rectangle{
                    id: regionItem
                    height: 20
                    Row{
                        anchors.fill: parent
                        Text{
                            font.pixelSize: 16
                            text: {
                                var str = time + "设备" + welderID
                                if(messageType === QmlEnum.MESSAGE_suspicious){
                                    str += "出现可疑品"
                                }
                                else if(messageType === QmlEnum.MESSAGE_defective){
                                    str += "出现次品"
                                }
                                else if(messageType === QmlEnum.MESSAGE_noConnect){
                                    str += "未连接"
                                }
                                else if(messageType === QmlEnum.MESSAGE_lowerValue){
                                    str += "良率下降至下限值"
                                }
                                else if(messageType === QmlEnum.MESSAGE_defectiveOften){
                                    str += "频繁出现次品"
                                }
                                else if(messageType === QmlEnum.MESSAGE_suspiciousOften){
                                    str += "频繁出现可疑品"
                                }
                                else if(messageType === QmlEnum.MESSAGE_upperValue){
                                    str += "自动学习次数超过上限值"
                                }
                                else if(messageType === QmlEnum.MESSAGE_studyOver){
                                    str += "自动学习已完成"
                                }
                                else if(messageType === QmlEnum.MESSAGE_touchSuccess){
                                    str += "创建模型已完成"
                                }
                                return str
                            }
                            font.family: fontBold
                            font.bold: true
                            color:"#004b8d"
                        }
                    }
                }
            }
        }
    }
    Component{
        id:sysConfig
        Rectangle{
            y:33
            width: 567
            height: 236
            color: "#b1d5db"
            Text {
                x:223
                y:49
                text: qsTr("系统配置成功!")
                font.pixelSize: 20
                color: "#004b8d"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: fontBold
                font.bold: true
            }
            Button{
                id:s4
                x:170
                y:165
                width: 243
                height: 52
                background: Rectangle{
                    radius: 6
                    color: pRgb(43, 112, 173)
                }
                contentItem: Text {
                    id: mt1
                    text: qsTr("确认")
                    font.pixelSize: mode == 1 ? 17:20
                    color: pRgb(153, 204, 255)
                    anchors.centerIn: parent  // 确保文本在按钮内居中对齐
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.family: fontBold
                    font.bold: true
                }
                onPressed: {
                    close()
                }
            }
        }
    }

}
