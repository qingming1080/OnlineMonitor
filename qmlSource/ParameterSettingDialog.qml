import QtQuick 2.0
import QtQuick.Controls 2.15
import GlobalLanguageDefine 1.0
import GlobalSystemDefine 1.0

Dialog {
    id: parameterSetting
    modal: true
    x:400
    y:-200
    width: 567
    height: 360
    readonly property int labelWidth: 65
    readonly property int textFieldWidth: 80
    readonly property int rowHeight: 30
    readonly property int rowWidth: 10
    readonly property int columnWidth: 40
    readonly property int elementWidth: 25

    background: Rectangle {
        color: "#b1d5db"
        radius: 6
        anchors.fill: parent
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

    header:Rectangle{
        width: 567
        height: 30
        color: "#004b8d"
        Text {
            anchors.centerIn: parent
            // text: qsTr("设置参数")
            text: GlobalLanguageDefine.strSetParameters
            font.pixelSize: 18
            color: pRgb(153, 204, 255)
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
        }
    }
    contentHeight: 360 - 30
    contentWidth: 567

    contentItem: Rectangle {
        height: 360 - 30
        width: 567
        color: "transparent"

        Grid {
            id: grid
            rowSpacing: elementWidth
            // anchors.centerIn: parent
            anchors.top:  parent.top
            anchors.topMargin: 30
            columnSpacing: columnWidth
            columns: 3
            rows: 4
            width: parent.width
            height: rowHeight * 4 + elementWidth * 3

            Row{
                id: energeSetting
                spacing: rowWidth
                height: rowHeight
                Text{
                    id: titleEnergy
                    // text: "能        量:"
                    text: GlobalLanguageDefine.strEnergy + ": "
                    font.pixelSize: 14
                    font.family: GlobalSystemDefine.fontNormal
                    verticalAlignment: TextInput.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                    color: "#004b8d"
                    width: labelWidth
                    height: parent.height
                }
                TextField {
                    id: energy_set
                    text: "0"
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    color: "#004b8d"
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    font.family: GlobalSystemDefine.fontNormal
                    width: textFieldWidth
                    height: parent.height
                    font.pixelSize: 14
                    anchors.verticalCenter: parent.verticalCenter
                    background: Rectangle{
                        radius: 6
                        border.width: 2
                        border.color: "#004b8d"
                    }
                }
            }

            Row{
                id: amplitudeSetting
                spacing: rowWidth
                height: rowHeight
                Label {
                    // text: "振        幅:"
                    text: GlobalLanguageDefine.strAmplitude + ": "
                    font.pixelSize: 14
                    font.family: GlobalSystemDefine.fontNormal
                    verticalAlignment: TextInput.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                    color:"#004b8d"
                    width: labelWidth
                    height: parent.height
                }
                TextField {
                    id: amplitude_set
                    text: "0"
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    color: "#004b8d"
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    font.family: GlobalSystemDefine.fontNormal
                    width: textFieldWidth
                    height: parent.height
                    font.pixelSize: 14
                    anchors.verticalCenter: parent.verticalCenter
                    background: Rectangle{
                        radius: 6
                        border.width: 2
                        border.color: "#004b8d"
                    }
                }
            }

            Row{
                id: weldPressureSetting
                spacing: rowWidth
                height: rowHeight
                Label {
                    // text: "焊接压力:"
                    text: GlobalLanguageDefine.strWeldPressure + ": "
                    font.pixelSize: 14
                    font.family: GlobalSystemDefine.fontNormal
                    verticalAlignment: TextInput.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                    color:"#004b8d"
                    width: labelWidth
                    height: parent.height
                }
                TextField {
                    id: wp_set
                    text: "0"
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    color: "#004b8d"
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    font.family: GlobalSystemDefine.fontNormal
                    width: textFieldWidth
                    height: parent.height
                    font.pixelSize: 14
                    anchors.verticalCenter: parent.verticalCenter
                    background: Rectangle{
                        radius: 6
                        border.width: 2
                        border.color: "#004b8d"
                    }
                }
            }

            Row{
                id: triggerPressureSetting
                spacing: rowWidth
                height: rowHeight
                Label {
                    // text: "触发压力:" ;
                    text: GlobalLanguageDefine.strTriggerPressure + ": "
                    font.pixelSize: 14;
                    font.family: GlobalSystemDefine.fontNormal
                    verticalAlignment: TextInput.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter;
                    color:"#004b8d";
                    width: labelWidth
                    height: parent.height
                }
                TextField {
                    id: tp_set
                    text: "0"
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    color: "#004b8d"
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    font.family: GlobalSystemDefine.fontNormal
                    width: textFieldWidth
                    height: parent.height
                    font.pixelSize: 14
                    anchors.verticalCenter: parent.verticalCenter
                    background: Rectangle{
                        radius: 6
                        border.width: 2
                        border.color: "#004b8d"
                    }
                }
            }

            Row{
                id: timeUpperSetting
                spacing: rowWidth
                height: rowHeight
                Label {
                    // text: "时间上限:" ;
                    text: GlobalLanguageDefine.strTimeUpper + ": "
                    font.pixelSize: 14;
                    font.family: GlobalSystemDefine.fontNormal
                    verticalAlignment: TextInput.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter;
                    color: "#004b8d";
                    width: labelWidth
                    height: parent.height
                }
                TextField {
                    id: time_max_set
                    text: "0"
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    color: "#004b8d"
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    font.family: GlobalSystemDefine.fontNormal
                    width: textFieldWidth
                    height: parent.height
                    font.pixelSize: 14
                    anchors.verticalCenter: parent.verticalCenter
                    background: Rectangle{
                        radius: 6
                        border.width: 2
                        border.color: "#004b8d"
                    }
                }
            }

            Row{
                id: timeLowerSetting
                spacing: rowWidth
                height: rowHeight
                Label {
                    // text: "时间下限:" ;
                    text: GlobalLanguageDefine.strTimeLower + ": "
                    font.pixelSize: 14;
                    font.family: GlobalSystemDefine.fontNormal
                    verticalAlignment: TextInput.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter;
                    color:"#004b8d";
                    width: labelWidth
                    height: parent.height
                }
                TextField {
                    id: time_min_set
                    text: "0"
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    color: "#004b8d"
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    font.family: GlobalSystemDefine.fontNormal
                    // font.bold: true
                    width: textFieldWidth
                    height: parent.height
                    font.pixelSize: 14
                    anchors.verticalCenter: parent.verticalCenter
                    background: Rectangle{
                        radius: 6
                        border.width: 2
                        border.color: "#004b8d"
                    }
                }
            }

            Row{
                id: powerLowerSetting
                spacing: rowWidth
                height: rowHeight
                Label {
                    // text: "功率下限:" ;
                    text: GlobalLanguageDefine.strPowerLower + ": "
                    font.pixelSize: 14;
                    font.family: GlobalSystemDefine.fontNormal
                    verticalAlignment: TextInput.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter;
                    color:"#004b8d";
                    width: labelWidth
                    height: parent.height
                }
                TextField {
                    id: power_min_set
                    text: "0"
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    color: "#004b8d"
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    font.family: GlobalSystemDefine.fontNormal
                    width: textFieldWidth
                    height: parent.height
                    font.pixelSize: 14
                    anchors.verticalCenter: parent.verticalCenter
                    background: Rectangle{
                        radius: 6
                        border.width: 2
                        border.color: "#004b8d"
                    }
                }
            }

            Row{
                id: powerUpperSetting
                spacing: rowWidth
                height: rowHeight
                Label {
                    // text: "功率上限:" ;
                    text: GlobalLanguageDefine.strPowerUpper + ": "
                    font.pixelSize: 14;
                    font.family: GlobalSystemDefine.fontNormal
                    verticalAlignment: TextInput.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter;
                    color:"#004b8d";
                    width: labelWidth
                    height: parent.height
                }
                TextField {
                    id: power_max_set
                    text: "0"
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    color: "#004b8d"
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    font.family: GlobalSystemDefine.fontNormal
                    width: textFieldWidth
                    height: parent.height
                    font.pixelSize: 14
                    anchors.verticalCenter: parent.verticalCenter
                    background: Rectangle{
                        radius: 6
                        border.width: 2
                        border.color: "#004b8d"
                    }
                }
            }

            Row{
                id: preheightLower
                spacing: rowWidth
                height: rowHeight
                Label {
                    // text: "预焊下限:" ;
                    text: GlobalLanguageDefine.strPreheightLower + ": "
                    font.pixelSize: 14;
                    font.family: GlobalSystemDefine.fontNormal
                    verticalAlignment: TextInput.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter;
                    color:"#004b8d";
                    width: labelWidth
                    height: parent.height
                }
                TextField {
                    id: pre_heightmin_set
                    text: "0"
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    color: "#004b8d"
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    font.family: GlobalSystemDefine.fontNormal
                    width: textFieldWidth
                    height: parent.height
                    font.pixelSize: 14
                    anchors.verticalCenter: parent.verticalCenter
                    background: Rectangle{
                        radius: 6
                        border.width: 2
                        border.color: "#004b8d"
                    }
                }
            }

            Row{
                id: preheightUpperSetting
                spacing: rowWidth
                height: rowHeight
                Label {
                    // text: "预焊上限:" ;
                    text: GlobalLanguageDefine.strPreheightUpper + ": "
                    font.pixelSize: 14;
                    font.family: GlobalSystemDefine.fontNormal
                    verticalAlignment: TextInput.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter;
                    color:"#004b8d";
                    width: labelWidth
                    height: parent.height
                }
                TextField {
                    id: pre_heightmax_set
                    text: "0"
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    color: "#004b8d"
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    font.family: GlobalSystemDefine.fontNormal
                    width: textFieldWidth
                    height: parent.height
                    font.pixelSize: 14
                    anchors.verticalCenter: parent.verticalCenter
                    background: Rectangle{
                        radius: 6
                        border.width: 2
                        border.color: "#004b8d"
                    }
                }
            }

            Row{
                id: postHeightLowerSetting
                spacing: rowWidth
                height: rowHeight
                Label {
                    // text: "终焊下限:" ;
                    text: GlobalLanguageDefine.strPostHeightLower + ": "
                    font.pixelSize: 14;
                    font.family: GlobalSystemDefine.fontNormal
                    verticalAlignment: TextInput.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter;
                    color:"#004b8d";
                    width: labelWidth
                    height: parent.height
                }
                TextField {
                    id: post_hehigtmin_set
                    text: "0"
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    color: "#004b8d"
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    font.family: GlobalSystemDefine.fontNormal
                    width: textFieldWidth
                    height: parent.height
                    font.pixelSize: 14
                    anchors.verticalCenter: parent.verticalCenter
                    background: Rectangle{
                        radius: 6
                        border.width: 2
                        border.color: "#004b8d"
                    }
                }
            }

            Row{
                id: postHeightUpperSetting
                spacing: rowWidth
                height: rowHeight
                Label {
                    // text: "终焊上限:" ;
                    text: GlobalLanguageDefine.strPostHeightUpper + ": "
                    font.pixelSize: 14;
                    font.family: GlobalSystemDefine.fontNormal
                    verticalAlignment: TextInput.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter;
                    color:"#004b8d";
                    width: labelWidth
                    height: parent.height
                }
                TextField {
                    id: post_hehigtmax_set
                    text: "0"
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    color: "#004b8d"
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    font.family: GlobalSystemDefine.fontNormal
                    width: textFieldWidth
                    height: parent.height
                    font.pixelSize: 14
                    anchors.verticalCenter: parent.verticalCenter
                    background: Rectangle{
                        radius: 6
                        border.width: 2
                        border.color: "#004b8d"
                    }
                }
            }
        }

        Button {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.leftMargin: 130
            width: 120
            height: 36
            background: Rectangle{
                radius: 6
                color: pRgb(43, 112, 173)
            }
            contentItem: Text {
                // text:qsTr("确认")
                text: GlobalLanguageDefine.strOK
                font.pixelSize: 20
                color: pRgb(153, 204, 255)
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: GlobalSystemDefine.fontBold
                font.bold: true
            }
            onClicked: {
                console.log("deviceIDPARMSEdIOLOG:",deviceID)

                // 从 TextField 获取用户输入的数据
                // var energyValue = energy_set.text
                // var amplitudeValue = amplitude_set.text
                // var tpValue = tp_set.text
                // var wpValue = wp_set.text
                // var timeMaxValue = time_max_set.text
                // var timeMinValue = time_min_set.text
                // var powerMinValue = power_min_set.text
                // var powerMaxValue = power_max_set.text
                // var preHeightMinValue = pre_hehigtmin_set.text
                // var preHeightMaxValue = pre_hehigtmax_set.text
                // var postHeightMinValue = post_hehigtmin_set.text
                // var postHeightMaxValue = post_hehigtmax_set.text

                // 校验函数：检查输入值是否为有效数字
                    // function isValidNumber(value) {
                    //     return !isNaN(value) && value.trim() !== "" && value !== null;
                    // }

                    // // 校验所有输入值
                    // if (!isValidNumber(energyValue) || !isValidNumber(amplitudeValue) || !isValidNumber(tpValue) ||
                    //     !isValidNumber(wpValue) || !isValidNumber(timeMaxValue) || !isValidNumber(timeMinValue) ||
                    //     !isValidNumber(powerMinValue) || !isValidNumber(powerMaxValue) || !isValidNumber(preHeightMinValue) ||
                    //     !isValidNumber(preHeightMaxValue) || !isValidNumber(postHeightMinValue) || !isValidNumber(postHeightMaxValue)) {

                    //     console.log("请输入有效的数字！");
                    //     return;  // 退出操作，不发送数据
                    // }

                // 转换为整数数组传递给 C++ 层
                // HBModbusClient.writeParameterSetting(
                //             deviceID,
                //             [
                //                 parseInt(energyValue),
                //                 parseInt(amplitudeValue),
                //                 parseInt(tpValue),
                //                 parseInt(wpValue),
                //                 parseInt(timeMaxValue),
                //                 parseInt(timeMinValue),
                //                 parseInt(powerMinValue),
                //                 parseInt(powerMaxValue),
                //                 parseInt(preHeightMinValue),
                //                 parseInt(preHeightMaxValue),
                //                 parseInt(postHeightMinValue),
                //                 parseInt(postHeightMaxValue)
                //             ]
                //             );

                parameterSetting.close()

            }
        }

        Button{
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.rightMargin: 130
            width:  120
            height: 36
            background: Rectangle{
                radius: 6
                color: pRgb(43, 112, 173)
            }

            contentItem: Text {
                // text: qsTr("取消")
                text: GlobalLanguageDefine.strCancel
                font.pixelSize: 20
                color: pRgb(153, 204, 255)
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: GlobalSystemDefine.fontBold
                font.bold: true
            }

            onClicked: {
                parameterSetting.close();  // 点击取消时关闭对话框
            }
        }

        Connections {
            //TODO Need to do something
           //     target: ModbusClient  // 指定信号来源对象

           //     onParameterdata: {  // 连接到 parameterdata 信号
           //         console.log("Received parameter data:", result);
           //         energy_set.text = result[0].toString()
           //         amplitude_set.text = result[1].toString()
           //         tp_set.text = result[2].toString()
           //         wp_set.text = result[3].toString()
           //         time_max_set.text = result[4].toString()
           //         time_min_set.text = result[5].toString()
           //         power_min_set.text = result[6].toString()
           //         power_max_set.text = result[7].toString()
           //         pre_hehigtmin_set.text = result[8].toString()
           //         pre_hehigtmax_set.text = result[9].toString()
           //         post_hehigtmin_set.text = result[10].toString()
           //         post_hehigtmax_set.text = result[11].toString()
           //     }
           }
    }

}
