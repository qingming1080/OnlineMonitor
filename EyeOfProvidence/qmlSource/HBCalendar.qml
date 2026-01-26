import QtQuick                  2.0
import GlobalStyle              1.0
import QtQuick.Controls         1.4
import QtQuick.Controls.Styles  1.4
import GlobalLanguageDefine     1.0
import GlobalSystemDefine       1.0
Item
{
    id: hbCalendar
    property date selectedDate: new Date()
    property date initDate: new Date(2026, 0, 1)
    width: parent.width
    height: parent.height
    readonly property int buttonWidth: 100
    readonly property int componentHeight: 30
    signal signalConfirmed(bool isConfirmed)
    SystemPalette {
        id: systemPalette
    }

    Calendar {
        id: calendar
        // Convert the timestamp to QDateTime
        property date todayDate: new Date()
        width: 450
        height: 400
        frameVisible: false
        // weekNumbersVisible: true
        selectedDate: hbCalendar.initDate
        Component.onCompleted:{
               visibleYear  =  hbCalendar.initDate.getFullYear()
               visibleMonth =  hbCalendar.initDate.getMonth()
        }
        focus: true
        onClicked:{
            hbCalendar.selectedDate = date
        }

        style: CalendarStyle {
            background: Rectangle
            {
                anchors.fill: parent
                // color: Style.hbButtonBackgroundColor
                color: "#3D7AB3"
            }
            navigationBar: Item {
                readonly property var strMonths: [GlobalLanguageDefine.strJanuary,
                                                  GlobalLanguageDefine.strFebruary,
                                                  GlobalLanguageDefine.strMarch,
                                                  GlobalLanguageDefine.strApril,
                                                  GlobalLanguageDefine.strMay,
                                                  GlobalLanguageDefine.strJune,
                                                  GlobalLanguageDefine.strJuly,
                                                  GlobalLanguageDefine.strAugust,
                                                  GlobalLanguageDefine.strSeptember,
                                                  GlobalLanguageDefine.strOctober,
                                                  GlobalLanguageDefine.strNovember,
                                                  GlobalLanguageDefine.strDecember,]

                width: parent.width
                height: Math.round(30 * GlobalStyle.scaleHint)
                Rectangle
                {
                    anchors.fill: parent
                    color: GlobalStyle.backgroundDeepColor
                }
                HBPrimaryButton {
                    text: "<"
                    width: Math.round(25 * GlobalStyle.scaleHint)
                    height: width
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {
                        calendar.showPreviousMonth()
                    }
                }

                HBPrimaryButton {
                    text: ">"
                    onClicked: calendar.showNextMonth()
                    width: Math.round(25 * GlobalStyle.scaleHint)
                    height: width
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                }

                // Current month and year label
                Label {
                    height: parent.height
                    width: Math.round(50 * GlobalStyle.scaleHint)
                    anchors.centerIn: parent
                    text: qsTr("%1  %2").arg(strMonths[calendar.visibleMonth]).arg(calendar.visibleYear)
                    font.pixelSize: Math.round(GlobalStyle.style3 * GlobalStyle.scaleHint)
                    font.family: GlobalSystemDefine.fontBold
                    color: "#E1EAEA"
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

            }

            dayOfWeekDelegate: Item {
                readonly property var strWeekDays: [GlobalLanguageDefine.strSunday,
                                                    GlobalLanguageDefine.strMonday,
                                                    GlobalLanguageDefine.strTuesday,
                                                    GlobalLanguageDefine.strWednesday,
                                                    GlobalLanguageDefine.strThursday,
                                                    GlobalLanguageDefine.strFriday,
                                                    GlobalLanguageDefine.strSaturday]
                width: parent.width
                height: Math.round(30 * GlobalStyle.scaleHint)
                Label {
                    anchors.centerIn: parent
                    text: strWeekDays[styleData.dayOfWeek]
                    color: styleData.dayOfWeek === 0 || styleData.dayOfWeek === 6 ? GlobalStyle.redFontColor : "#E1EAEA"
                    font.pixelSize: Math.round(GlobalStyle.style2 * GlobalStyle.scaleHint)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                }
            }
            dayDelegate: Item {
                readonly property color sameMonthDateTextColor: "#E1EAEA"
                readonly property color selectedDateColor: Qt.platform.os === "osx" ? GlobalStyle.hbButtonBackgroundColor : systemPalette.highlight
                readonly property color selectedDateTextColor: GlobalStyle.blackFontColor
                readonly property color differentMonthDateTextColor: "#bbb"
                readonly property color invalidDatecolor: "#dddddd"

                Rectangle {
                    anchors.fill: parent
                    border.color: "transparent"
                    // color: styleData.date !== undefined && styleData.selected ? selectedDateColor : Style.hbButtonBackgroundColor
                    color: styleData.date !== undefined && styleData.selected ? selectedDateColor : "#3D7AB3"
                    anchors.margins: styleData.selected ? -1 : 0
                }

                Label {
                    id: dayDelegateText
                    text: styleData.date.getDate()
                    font.pixelSize: Math.round(GlobalStyle.style3 * GlobalStyle.scaleHint)
                    anchors.centerIn: parent
                    color: {
                        var color = invalidDatecolor;
                        if (styleData.valid) {
                            // Date is within the valid range.
                            if(styleData.visibleMonth === true)
                            {
                                color = sameMonthDateTextColor;
                                if(styleData.date.getDay() === 0 || styleData.date.getDay() === 6)
                                    color = GlobalStyle.redFontColor
                            }
                            else
                                color = differentMonthDateTextColor;
                            if (styleData.selected) {
                                color = selectedDateTextColor;
                            }
                        }
                        return color;
                    }
                }
            }
        }
    }
}


