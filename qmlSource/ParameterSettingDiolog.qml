import QtQuick 2.0
import QtQuick.Controls 2.15

Dialog {
    id: parameterSetting
    modal: true
    x:400
    y:-200
    // anchors.centerIn: parent
    width: 567
    height: 360
    font.pixelSize: 18
    font.family: "Arial"

    background: Rectangle {
        color: "#b1d5db"
        radius: 6

        Rectangle{
            width: 567
            height:30
            color: "#004b8d"
            Text {
                //anchors.horizontalCenter: parent.horizontalCenter
                anchors.centerIn: parent
                text: qsTr("设置参数")
                font.pixelSize: 18
                color: pRgb(153, 204, 255)
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: fontBold
                font.bold: true
            }
        }

        MouseArea {
            id: dragArea
            anchors.fill: parent
            cursorShape: Qt.OpenHandCursor
            property var startPosition

            onPressed: {
                // cursorShape = Qt.ClosedHandCursor
                dragArea.startPosition = Qt.point(mouse.x, mouse.y);
            }
            onReleased: {
                // cursorShape = Qt.OpenHandCursor
            }

            onPositionChanged: {
                // 更新对话框的位置
                parameterSetting.x += mouse.x - dragArea.startPosition.x;
                parameterSetting.y += mouse.y - dragArea.startPosition.y;
                console.log("parameterSetting.x:", parameterSetting.x,"parameterSetting.y:",parameterSetting.y)

                // parameterSetting.x = Math.max(0, Math.min(1353, newX))  // 1920 - 567
                // parameterSetting.y = Math.max(0, Math.min(720, newY))   // 1080 - 360
            }
        }
    }

 


    contentItem: Flickable {
        width: parent.width
        height: parent.height
        contentHeight: column.height  // 自动调整高度


        Rectangle{
            x:260
            y:45

            Column {
                id: column
                spacing: 30
                anchors.horizontalCenter: parent.horizontalCenter

                Row {
                    spacing: 15
                    anchors.horizontalCenter: parent.horizontalCenter

                    Label {
                        text: "能        量:"
                        font.pixelSize: 14
                        font.family: "Arial"
                        anchors.verticalCenter: parent.verticalCenter
                        color:"#004b8d"
                        font.bold: true
                    }

                    TextField {
                        id: energy_set
                        text: "0"
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        color: "#004b8d"
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                        font.family: "Arial"
                        font.bold: true
                        width: 70
                        height: 30
                        font.pixelSize: 14
                        background: Rectangle{
                            radius: 6
                            border.width: 2
                            border.color: "#004b8d"
                        }
                    }


                    Label {
                        text: "振        幅:"
                        font.pixelSize: 14
                        font.family: "Arial"
                        anchors.verticalCenter: parent.verticalCenter
                        color:"#004b8d"
                        font.bold: true
                    }


                    TextField {
                        id: amplitude_set
                        text: "0"
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        color: "#004b8d"
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                        font.family: "Arial"
                        font.bold: true
                        width: 70
                        height: 30
                        font.pixelSize: 14
                        background: Rectangle{
                            radius: 6
                            border.width: 2
                            border.color: "#004b8d"
                        }
                    }


                    Label {

                        text: "焊接压力:"
                        font.pixelSize: 14
                        font.family: "Arial"
                        anchors.verticalCenter: parent.verticalCenter
                        color:"#004b8d"
                        font.bold: true
                    }

                    TextField {
                        id: wp_set
                        text: "0"
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        color: "#004b8d"
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                        font.family: "Arial"
                        font.bold: true
                        width: 70
                        height: 30
                        font.pixelSize: 14

                        background: Rectangle{
                            radius: 6
                            border.width: 2
                            border.color: "#004b8d"
                        }
                    }
                }


                Row {
                    spacing: 15
                    anchors.horizontalCenter: parent.horizontalCenter

                    Label { text: "触发压力:" ; font.pixelSize: 14; font.family: "Arial" ; anchors.verticalCenter: parent.verticalCenter; color:"#004b8d"; font.bold: true }

                    TextField {
                        id: tp_set
                        text: "0"
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        color: "#004b8d"
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                        font.family: "Arial"
                        font.bold: true
                        width:70
                        height: 30
                        font.pixelSize: 14

                        background: Rectangle{
                            radius: 6
                            border.width: 2
                            border.color: "#004b8d"
                        }
                    }

                    Label { text: "时间上限:" ; font.pixelSize: 14; font.family: "Arial" ; anchors.verticalCenter: parent.verticalCenter; color:"#004b8d"; font.bold: true }

                    TextField {
                        id: time_max_set
                        text: "0"
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        color: "#004b8d"
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                        font.family: "Arial"
                        font.bold: true
                        width: 70
                        height: 30
                        font.pixelSize: 14

                        background: Rectangle{
                            radius: 6
                            border.width: 2
                            border.color: "#004b8d"
                        }
                    }

                    Label { text: "时间下限:" ;  font.pixelSize: 14; font.family: "Arial" ; anchors.verticalCenter: parent.verticalCenter; color:"#004b8d"; font.bold: true }

                    TextField {
                        id: time_min_set
                        text: "0"
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        color: "#004b8d"
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                        font.family: "Arial"
                        font.bold: true
                        width: 70
                        height: 30
                        font.pixelSize: 14

                        background: Rectangle{
                            radius: 6
                            border.width: 2
                            border.color: "#004b8d"
                        }
                    }
                }

                Row {
                    spacing: 15
                    anchors.horizontalCenter: parent.horizontalCenter
                    Label { text: "功率下限:" ; font.pixelSize: 14; font.family: "Arial" ; anchors.verticalCenter: parent.verticalCenter; color:"#004b8d"; font.bold: true }

                    TextField {
                        id: power_min_set
                        text: "0"
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        color: "#004b8d"
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                        font.family: "Arial"
                        font.bold: true
                        width: 70
                        height: 30
                        font.pixelSize: 14

                        background: Rectangle{
                            radius: 6
                            border.width: 2
                            border.color: "#004b8d"
                        }
                    }

                    Label { text: "功率上限:" ;  font.pixelSize: 14; font.family: "Arial" ; anchors.verticalCenter: parent.verticalCenter; color:"#004b8d"; font.bold: true }

                    TextField {
                        id: power_max_set
                        text: "0"
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        color: "#004b8d"
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                        font.family: "Arial"
                        font.bold: true
                        width: 70
                        height: 30
                        font.pixelSize: 14

                        background: Rectangle{
                            radius: 6
                            border.width: 2
                            border.color: "#004b8d"
                        }
                    }
                    Label { text: "预焊下限:" ; font.pixelSize: 14; font.family: "Arial" ; anchors.verticalCenter: parent.verticalCenter; color:"#004b8d"; font.bold: true }

                    TextField {
                        id: pre_hehigtmin_set
                        text: "0"
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        color: "#004b8d"
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                        font.family: "Arial"
                        font.bold: true
                        width: 70
                        height: 30
                        font.pixelSize: 14

                        background: Rectangle{
                            radius: 6
                            border.width: 2
                            border.color: "#004b8d"
                        }
                    }
                }
                Row {
                    spacing: 15
                    anchors.horizontalCenter: parent.horizontalCenter


                    Label { text: "预焊上限:" ;  font.pixelSize: 14; font.family: "Arial" ; anchors.verticalCenter: parent.verticalCenter; color:"#004b8d"; font.bold: true }

                    TextField {
                        id: pre_hehigtmax_set
                        text: "0"
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        color: "#004b8d"
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                        font.family: "Arial"
                        font.bold: true
                        width: 70
                        height: 30
                        font.pixelSize: 14

                        background: Rectangle{
                            radius: 6
                            border.width: 2
                            border.color: "#004b8d"
                        }
                    }

                    Label { text: "终焊下限:" ; font.pixelSize: 14; font.family: "Arial" ; anchors.verticalCenter: parent.verticalCenter; color:"#004b8d"; font.bold: true }

                    TextField {
                        id: post_hehigtmin_set
                        text: "0"
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        color: "#004b8d"
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                        font.family: "Arial"
                        font.bold: true
                        width: 70
                        height: 30
                        font.pixelSize: 14

                        background: Rectangle{
                            radius: 6
                            border.width: 2
                            border.color: "#004b8d"
                        }
                    }

                    Label { text: "终焊上限:" ;  font.pixelSize: 14; font.family: "Arial" ; anchors.verticalCenter: parent.verticalCenter; color:"#004b8d"; font.bold: true }

                    TextField {
                        id: post_hehigtmax_set
                        text: "0"
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        color: "#004b8d"
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                        font.family: "Arial"
                        font.bold: true
                        width: 70
                        height: 30
                        font.pixelSize: 14

                        background: Rectangle{
                            radius: 6
                            border.width: 2
                            border.color: "#004b8d"
                        }
                    }

                }
            }
        }
        Button {
            x:120
            y:290
            width: 120
            height: 36
            background: Rectangle{
                radius: 6
                color: pRgb(43, 112, 173)
            }
            contentItem: Text {
                text:qsTr("确认")
                font.pixelSize: 20
                color: pRgb(153, 204, 255)
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: fontBold
                font.bold: true
            }
            onClicked: {
                console.log("deviceIDPARMSEdIOLOG:",deviceID)

                // 从 TextField 获取用户输入的数据
                var energyValue = energy_set.text
                var amplitudeValue = amplitude_set.text
                var tpValue = tp_set.text
                var wpValue = wp_set.text
                var timeMaxValue = time_max_set.text
                var timeMinValue = time_min_set.text
                var powerMinValue = power_min_set.text
                var powerMaxValue = power_max_set.text
                var preHeightMinValue = pre_hehigtmin_set.text
                var preHeightMaxValue = pre_hehigtmax_set.text
                var postHeightMinValue = post_hehigtmin_set.text
                var postHeightMaxValue = post_hehigtmax_set.text

                // 校验函数：检查输入值是否为有效数字
                    function isValidNumber(value) {
                        return !isNaN(value) && value.trim() !== "" && value !== null;
                    }

                    // 校验所有输入值
                    if (!isValidNumber(energyValue) || !isValidNumber(amplitudeValue) || !isValidNumber(tpValue) ||
                        !isValidNumber(wpValue) || !isValidNumber(timeMaxValue) || !isValidNumber(timeMinValue) ||
                        !isValidNumber(powerMinValue) || !isValidNumber(powerMaxValue) || !isValidNumber(preHeightMinValue) ||
                        !isValidNumber(preHeightMaxValue) || !isValidNumber(postHeightMinValue) || !isValidNumber(postHeightMaxValue)) {

                        console.log("请输入有效的数字！");
                        return;  // 退出操作，不发送数据
                    }

                // 转换为整数数组传递给 C++ 层
                HBModbusClient.writeParameterSetting(
                            deviceID,
                            [
                                parseInt(energyValue),
                                parseInt(amplitudeValue),
                                parseInt(tpValue),
                                parseInt(wpValue),
                                parseInt(timeMaxValue),
                                parseInt(timeMinValue),
                                parseInt(powerMinValue),
                                parseInt(powerMaxValue),
                                parseInt(preHeightMinValue),
                                parseInt(preHeightMaxValue),
                                parseInt(postHeightMinValue),
                                parseInt(postHeightMaxValue)
                            ]
                            );

                parameterSetting.close()

            }
        }

        Button{
            x:280
            y:290
            width:  120
            height: 36
            background: Rectangle{
                radius: 6
                color: pRgb(43, 112, 173)
            }

            contentItem: Text {
                text:qsTr("取消")
                font.pixelSize: 20
                color: pRgb(153, 204, 255)
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: fontBold
                font.bold: true
            }

            onClicked: {
                parameterSetting.close();  // 点击取消时关闭对话框
            }
        }

        Connections {
               target: HBModbusClient  // 指定信号来源对象

               onParameterdata: {  // 连接到 parameterdata 信号
                   console.log("Received parameter data:", result);
                   energy_set.text = result[0].toString()
                   amplitude_set.text = result[1].toString()
                   tp_set.text = result[2].toString()
                   wp_set.text = result[3].toString()
                   time_max_set.text = result[4].toString()
                   time_min_set.text = result[5].toString()
                   power_min_set.text = result[6].toString()
                   power_max_set.text = result[7].toString()
                   pre_hehigtmin_set.text = result[8].toString()
                   pre_hehigtmax_set.text = result[9].toString()
                   post_hehigtmin_set.text = result[10].toString()
                   post_hehigtmax_set.text = result[11].toString()
               }
           }
    }

}
