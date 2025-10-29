import QtQuick 2.15
import QtQuick.Controls 2.15
import GlobalLanguageDefine 1.0
Dialog {
    id: timeDialog
    modal: true
    width: 700
    height: 300
    anchors.centerIn: Overlay.overlay
    font.pixelSize: 18
    font.family: "Arial"
    background: Rectangle {
        color: "#b1d5db"
        radius: 6

        Rectangle{
            id: setTimeRectangle
            width: parent.width
            height: 30
            color: "#004b8d"
            Text {
                //anchors.horizontalCenter: parent.horizontalCenter
                anchors.centerIn: parent
                // text: qsTr("设置时间")
                text: GlobalLanguageDefine.strTimeSettings
                font.pixelSize: 18
                color: "#99CCFF"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: GlobalSystemDefine.fontBold
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
        // text: qsTr("请输入当前时间")
        text: GlobalLanguageDefine.strEnterCurrentTime
        //color: pRgb(153, 204, 255)
        color: "#004b8d"
        font.pixelSize: 16
        font.family: "Arial" ;
        font.bold: true
        visible: errorText.text.length > 0
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.horizontalCenter: parent.horizontalCenter
        // x:200
        y:40

    }

    Column {
        spacing: 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 80

        Grid {
            columns: 6
            rowSpacing: 15
            columnSpacing: 15

            Label {
                id: yearLable
                text: GlobalLanguageDefine.strYear + ":"
                font.pixelSize: 20
                font.family: GlobalSystemDefine.fontBold
                color:"#004b8d"
                font.bold: true
            }

            TextField {
                id: yearField
                text: "2025"
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                color: "#004b8d"
                horizontalAlignment: TextInput.AlignHCenter
                verticalAlignment: TextInput.AlignVCenter
                font.family:GlobalSystemDefine.fontBold
                font.bold: true
                width: 100
                height: 35
                font.pixelSize: 17
                maximumLength: 4
                background: Rectangle{
                    radius: 6
                    border.width: 2
                    border.color: "#004b8d"
                }

                onEditingFinished: {
                      var minuteRegex = /^(19|20)\d{2}$/
                     if (!minuteRegex.test(yearField.text))
                         footer.showError(yearLable.text + "请输入有效年份！")
                     else
                         footer.hideError()
                 }
            }


            Label {
                // text: qsTr("月") + ":"
                id: monthLabel
                text: GlobalLanguageDefine.strMonth + ":"
                font.pixelSize: 20
                font.family: GlobalSystemDefine.fontBold
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
                font.family: GlobalSystemDefine.fontBold
                font.bold: true
                width: 100
                height: 35
                font.pixelSize: 17
                maximumLength: 2
                background: Rectangle{
                    radius: 6
                    border.width: 2
                    border.color: "#004b8d"
                }
                onEditingFinished: {
                      var monthRegex = /^(0[1-9]|1[0-2])$/
                     if (!monthRegex.test(monthField.text))
                         footer.showError(monthLabel.text + "月份必须是 1~12！")
                     else
                         footer.hideError()
                 }
            }

            Label {
                // text: qsTr("日") + ":"
                id: dayLabel
                text: GlobalLanguageDefine.strDay + ":"
                font.pixelSize: 20
                font.family: GlobalSystemDefine.fontBold
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
                font.family: GlobalSystemDefine.fontBold
                font.bold: true
                width: 100
                height: 35
                font.pixelSize: 17
                maximumLength: 2
                background: Rectangle{
                    radius: 6
                    border.width: 2
                    border.color: "#004b8d"
                }
                onEditingFinished: {
                      var daoyRegex = /^([1-9]|[12][0-9]|3[01])$/
                     if (!daoyRegex.test(dayField.text))
                         footer.showError(dayLabel.text + "请输入正确的日期（1~31）！")
                     else
                         footer.hideError()
                 }
            }

            Label {
                // text: qsTr("时") + ":" ;
                id: hourLabel
                text: GlobalLanguageDefine.strHour + ":"
                font.pixelSize: 20;
                font.family: GlobalSystemDefine.fontBold
                color:"#004b8d";
                font.bold: true
            }

            TextField {
                id: hourField
                text: "0"
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                color: "#004b8d"
                horizontalAlignment: TextInput.AlignHCenter
                verticalAlignment: TextInput.AlignVCenter
                font.family: GlobalSystemDefine.fontBold
                font.bold: true
                width: 100
                height: 35
                font.pixelSize: 17
                maximumLength: 2
                background: Rectangle{
                    radius: 6
                    border.width: 2
                    border.color: "#004b8d"
                }
                onEditingFinished: {
                      var hourRegex = /^(0\d|1\d|2[0-3])$/
                     if (!hourRegex.test(hourField.text))
                         footer.showError(hourLabel.text + "请输入正确的小时（0~23）！")
                     else
                         footer.hideError()
                 }
            }

            Label {
                // text: qsTr("分") + ":" ;
                id: minuteLabel
                text: GlobalLanguageDefine.strMinute + ":"
                font.pixelSize: 20;
                font.family: GlobalSystemDefine.fontBold
                color:"#004b8d";
                font.bold: true
            }

            TextField {
                id: minuteField
                text: "0"
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                color: "#004b8d"
                horizontalAlignment: TextInput.AlignHCenter
                verticalAlignment: TextInput.AlignVCenter
                font.family: GlobalSystemDefine.fontBold
                font.bold: true
                width: 100
                height: 35
                font.pixelSize: 17
                maximumLength: 2
                background: Rectangle{
                    radius: 6
                    border.width: 2
                    border.color: "#004b8d"
                }
                onEditingFinished: {
                     var minuteRegex = /^[0-5]\d$/
                     if (!minuteRegex.test(minuteField.text))
                         footer.showError(minuteLabel.text + "请输入正确的分钟（0~59）！")
                     else
                         footer.hideError()
                 }
            }

            Label {
                // text: qsTr("秒") + ":" ;
                id: secondLabel
                text: GlobalLanguageDefine.strSecond + ":"
                font.pixelSize: 20;
                font.family: GlobalSystemDefine.fontBold
                color:"#004b8d";
                font.bold: true
            }
            TextField {
                id: secondField
                text: "0"
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                color: "#004b8d"
                horizontalAlignment: TextInput.AlignHCenter
                verticalAlignment: TextInput.AlignVCenter
                font.family: GlobalSystemDefine.fontBold
                font.bold: true
                width: 100
                height: 35
                maximumLength: 2
                font.pixelSize: 17
                background: Rectangle{
                    radius: 6
                    border.width: 2
                    border.color: "#004b8d"
                }
                onEditingFinished: {
                     var secondRegex = /^[0-5]\d$/
                     if (!secondRegex.test(secondField.text))
                        footer.showError(secondLabel.text + "请输入正确的秒数（0~59）！")
                     else
                        footer.hideError()
                 }
            }

        }
    }
    Row{
        spacing: 60
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.bottom
        anchors.topMargin: -50
        Button {

            width: 120
            height: 36
            background: Rectangle{
                radius: 6
                color: pRgb(43, 112, 173)
            }
            contentItem: Text {
                // text: qsTr("确认")
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
                    // errorText.text = qsTr("所有字段必须是数字!");
                    errorText.text = GlobalLanguageDefine.strInvalidNumeric
                }

                // 检查年份范围
                if (year < 1900 || year > 2100) {
                    isValidDate = false;
                    // errorText.text = qsTr("无效的年份!");
                    errorText.text = GlobalLanguageDefine.strInvalidYear
                }

                // 检查月份范围
                if (month < 1 || month > 12) {
                    isValidDate = false;
                    // errorText.text = qsTr("无效的月份!");
                    errorText.text = GlobalLanguageDefine.strInvalidMonth
                }

                // 检查日期范围
                let daysInMonth = new Date(year, month, 0).getDate();  // 获取该月总天数
                if (day < 1 || day > daysInMonth) {
                    isValidDate = false;
                    // errorText.text = qsTr("无效的日期!");
                    errorText.text = GlobalLanguageDefine.strInvalidDay
                }

                // 闰年检查
                if (month === 2 && day === 29) {
                    let isLeapYear = (year % 4 === 0 && year % 100 !== 0) || (year % 400 === 0);
                    if (!isLeapYear) {
                        isValidDate = false;
                        // errorText.text = qsTr("无效的日期：该年份不是闰年!");
                        errorText.text = GlobalLanguageDefine.strInvalidLeapYear
                    }
                }

                // 检查时间范围
                if (hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59) {
                    isValidDate = false;
                    // errorText.text = qsTr("无效的时间!");
                    errorText.text = GlobalLanguageDefine.strInvalidDate
                }

                // 如果日期和时间有效，发出信号并关闭对话框
                if (isValidDate) {
                    timeSelected(year, month, day, hour, minute, second);  // 发出时间信号
                    timeDialog.close();  // 关闭对话框
                    //这里将年月日时间写入到

                }
                // ModbusClient.testAllFunctions()
                // ModbusClient.setSysLedStatus(true)
                // ModbusClient.setLearnLedStatus(true);
                // ModbusClient.setPilotLedStatus(true);
                // ModbusClient.setReadyLedStatus(true);
                // ModbusClient.setAlarmLedStatus(true);

                // ModbusClient.setSystemClock(qDateTime.datetime)
            }
        }

        Button{
            width:  120
            height: 36
            background: Rectangle{
                radius: 6
                color: pRgb(43, 112, 173)
            }

            contentItem: Text {
                // text:qsTr("取消")
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
                timeDialog.close();  // 点击取消时关闭对话框
            }
        }

    }

}

