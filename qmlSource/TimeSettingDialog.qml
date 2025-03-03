import QtQuick 2.15
import QtQuick.Controls 2.15

Dialog {
    id: timeDialog
    modal: true
    x:400
    y:65
    width: 567
    height: 236
    font.pixelSize: 18
    font.family: "Arial"

    background: Rectangle {
        color: "#b1d5db"
        radius: 6

        Rectangle{
            width: 567
            height:29
            color: "#004b8d"
            Text {
                //anchors.horizontalCenter: parent.horizontalCenter
                anchors.centerIn: parent
                text: qsTr("设置时间")
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
                dragArea.startPosition = Qt.point(mouse.x, mouse.y);
            }

            onPositionChanged: {
                // 更新对话框的位置
                timeDialog.x += mouse.x - dragArea.startPosition.x;
                timeDialog.y += mouse.y - dragArea.startPosition.y;
            }
        }
    }

    signal timeSelected(int year, int month, int day, int hour, int minute, int second)

    Text {
        id: errorText
        text: "请输入当前时间"
        //color: pRgb(153, 204, 255)
        color:"#004b8d"
        font.pixelSize: 16
        font.family: "Arial" ;
        font.bold: true
        visible: errorText.text.length > 0
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.horizontalCenter: parent.horizontalCenter
        // x:200
        y:30
    }


    contentItem: Flickable {
        width: parent.width
        height: parent.height
        contentHeight: column.height  // 自动调整高度


        Rectangle{
              x:260
              y:60
            Column {
                id: column
                spacing: 30
                anchors.horizontalCenter: parent.horizontalCenter

                Row {
                    spacing: 15
                    anchors.horizontalCenter: parent.horizontalCenter

                    Label {
                        text: "年:"
                        font.pixelSize: 20
                        font.family: "Arial"
                        anchors.verticalCenter: parent.verticalCenter
                        color:"#004b8d"
                        font.bold: true
                    }

                    TextField {
                        id: yearField
                        text: "2024"
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        color: "#004b8d"
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                        font.family: "Arial"
                        font.bold: true
                        width: 100
                        height: 35
                        font.pixelSize: 17
                        background: Rectangle{
                            radius: 6
                            border.width: 2
                            border.color: "#004b8d"
                        }
                    }


                    Label {
                        text: "月:"
                        font.pixelSize: 20
                        font.family: "Arial"
                        anchors.verticalCenter: parent.verticalCenter
                        color:"#004b8d"
                        font.bold: true
                    }


                    TextField {
                        id: monthField
                        text: "1"
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        color: "#004b8d"
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                        font.family: "Arial"
                        font.bold: true
                        width: 100
                        height: 35
                        font.pixelSize: 17
                        background: Rectangle{
                            radius: 6
                            border.width: 2
                            border.color: "#004b8d"
                        }
                    }

                    Label {

                        text: "日:"
                        font.pixelSize: 20
                        font.family: "Arial"
                        anchors.verticalCenter: parent.verticalCenter
                        color:"#004b8d"
                        font.bold: true
                    }

                    TextField {
                        id: dayField
                        text: "1"
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        color: "#004b8d"
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                        font.family: "Arial"
                        font.bold: true
                        width: 100
                        height: 35
                        font.pixelSize: 17

                        background: Rectangle{
                            radius: 6
                            border.width: 2
                            border.color: "#004b8d"
                        }
                    }
                }

                // 时间选择
                Row {
                    spacing: 15
                    anchors.horizontalCenter: parent.horizontalCenter
                    Label { text: "时:" ; font.pixelSize: 20; font.family: "Arial" ; anchors.verticalCenter: parent.verticalCenter; color:"#004b8d"; font.bold: true }

                    TextField {
                        id: hourField
                        text: "0"
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        color: "#004b8d"
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                        font.family: "Arial"
                        font.bold: true
                        width: 100
                        height: 35
                        font.pixelSize: 17

                        background: Rectangle{
                            radius: 6
                            border.width: 2
                            border.color: "#004b8d"
                        }
                    }

                    Label { text: "分:" ;  font.pixelSize: 20; font.family: "Arial" ; anchors.verticalCenter: parent.verticalCenter; color:"#004b8d"; font.bold: true }

                    TextField {
                        id: minuteField
                        text: "0"
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        color: "#004b8d"
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                        font.family: "Arial"
                        font.bold: true
                        width: 100
                        height: 35
                        font.pixelSize: 17

                        background: Rectangle{
                            radius: 6
                            border.width: 2
                            border.color: "#004b8d"
                        }
                    }

                    Label { text: "秒:" ;  font.pixelSize: 20; font.family: "Arial" ; anchors.verticalCenter: parent.verticalCenter; color:"#004b8d"; font.bold: true }
                    TextField {
                        id: secondField
                        text: "0"
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        color: "#004b8d"
                        horizontalAlignment: TextInput.AlignHCenter
                        verticalAlignment: TextInput.AlignVCenter
                        font.family: "Arial"
                        font.bold: true
                        width: 100
                        height: 35
                        font.pixelSize: 17
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
            y:180
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
                errorText.text = "";  // 清除错误信息

                let year = parseInt(yearField.text);
                let month = parseInt(monthField.text);
                let day = parseInt(dayField.text);
                let hour = parseInt(hourField.text);
                let minute = parseInt(minuteField.text);
                let second = parseInt(secondField.text);

                let isValidDate = true;

                // 检查是否为数字
                if (isNaN(year) || isNaN(month) || isNaN(day) || isNaN(hour) || isNaN(minute) || isNaN(second)) {
                    isValidDate = false;
                    errorText.text = "所有字段必须是数字！";
                }

                // 检查年份范围
                if (year < 1900 || year > 2100) {
                    isValidDate = false;
                    errorText.text = "无效的年份！";
                }

                // 检查月份范围
                if (month < 1 || month > 12) {
                    isValidDate = false;
                    errorText.text = "无效的月份！";
                }

                // 检查日期范围
                let daysInMonth = new Date(year, month, 0).getDate();  // 获取该月总天数
                if (day < 1 || day > daysInMonth) {
                    isValidDate = false;
                    errorText.text = "无效的日期！";
                }

                // 闰年检查
                if (month === 2 && day === 29) {
                    let isLeapYear = (year % 4 === 0 && year % 100 !== 0) || (year % 400 === 0);
                    if (!isLeapYear) {
                        isValidDate = false;
                        errorText.text = "无效的日期：该年份不是闰年！";
                    }
                }

                // 检查时间范围
                if (hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59) {
                    isValidDate = false;
                    errorText.text = "无效的时间！";
                }

                // 如果日期和时间有效，发出信号并关闭对话框
                if (isValidDate) {
                    timeSelected(year, month, day, hour, minute, second);  // 发出时间信号
                    timeDialog.close();  // 关闭对话框
                }

                 HBModbusClient.setIO(1,1);
                HBModbusClient.setIO(2,1);
                HBModbusClient.setIO(3,1);
                HBModbusClient.setIO(4,1);
                // HBModbusClient.setLED(false);
                HBModbusClient.writeSetTime(year, month, day, hour, minute, second);

            }
        }

        Button{
            x:280
            y:180
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
                timeDialog.close();  // 点击取消时关闭对话框
            }
        }

    }

}

