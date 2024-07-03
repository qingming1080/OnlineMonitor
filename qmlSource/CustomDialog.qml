import QtQuick 2.0
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
Popup {
    id:customPopup
    width: 567
    height: 271
    modal: true
    padding:0
    closePolicy:Popup.CloseOnEscape
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
                    source: "qrc:/image/关闭.png"
                }
            }
            onClicked: {
                customPopup.close()
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
            y:34
            width: 567
            height: 236
            color: "#b1d5db"
            Text {
                x:203
                y:49
                text: qsTr("请输入操作员密码")
                font.pixelSize: 20
                color: "#004b8d"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: fontBold
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
                font.pixelSize: 20
                background: Rectangle{
                    radius: 6
                }
            }
        }
    }
    Component{
        id:passerror
        Rectangle{
            y:34
            width: 567
            height: 236
            color: "#b1d5db"
            Text {
                x:203
                y:49
                text: qsTr("密码错误请重新输入!")
                font.pixelSize: 20
                color: "#004b8d"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: fontBold
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
                    text: "确认"
                    font.pixelSize: mode == 1 ? 17:20
                    color: pRgb(153, 204, 255)
                    anchors.centerIn: parent  // 确保文本在按钮内居中对齐
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.family: fontBold
                }
                onClicked: {

                }
            }
        }
    }
    Component{
        id:newpass
        Rectangle{
            y:34
            width: 567
            height: 236
            color: "#b1d5db"
            Text {
                x:203
                y:49
                text: qsTr("请输入新密码")
                font.pixelSize: 20
                color: "#004b8d"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: fontBold
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
                font.pixelSize: 20
                background: Rectangle{
                    radius: 6
                }
            }
        }
    }
    Component{
        id:dataeficiency
        Rectangle{
            y:34
            width: 567
            height: 236
            color: "#b1d5db"
            Text {
                x:203
                y:49
                text: qsTr("样本数不足请继续采样!")
                font.pixelSize: 20
                color: "#004b8d"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: fontBold
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
                    text: "确认"
                    font.pixelSize: mode == 1 ? 17:20
                    color: pRgb(153, 204, 255)
                    anchors.centerIn: parent  // 确保文本在按钮内居中对齐
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.family: fontBold
                }
                onClicked: {

                }
            }
        }
    }
    Component{
        id:language
        Rectangle{
            y:34
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
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            RadioButton{
                id:bt1
                width: 30
                height: 30
                x:208
                y:34
                indicator: Rectangle
                {
                    width: 30
                    height: 30
                    radius: 15
                    color: bt1.checked ? "#0d988c" : pRgb(232, 232, 232)
                    border.color: "#004b8d"
                    border.width: 2
                }
                onPressed: {

                }
            }
            Text {
                id: s2
                x:262
                y:100
                text: qsTr("English")
                color: "#004b8d"
                font.family: fontBold
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
                    color: bt2.checked ? "#0d988c" : pRgb(232, 232, 232)
                    border.color: "#004b8d"
                    border.width: 2
                }
                onPressed: {

                }
            }
            Text {
                id: s3
                x:262
                y:165
                text: qsTr("其他语言")
                color: "#004b8d"
                font.family: fontBold
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
            y:34
            width: 567
            height: 236
            color: "#b1d5db"
        }
    }
}
