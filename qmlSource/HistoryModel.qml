import QtQuick 2.15
import QtQuick.Controls 1.4
import QtQml.Models 2.2
import QtQuick.Controls 2.5
import Qt.labs.qmlmodels 1.0
import QtQuick.Controls.Styles 1.4
import GlobalLanguageDefine 1.0
import GlobalSystemDefine 1.0
import GlobalMessageDefine 1.0
import LanguageEnum 1.0
Rectangle {
    property int itemCount: DeviceManager.DeviceCounter
    property string buttonColor: "#0d988c"

    Connections {
        target: History
        function onSignalExportCompleted(success, message)
        {
            console.debug("message", message)
            window.showLoading(false)
            if(success === true)
                window.showDialog(qsTr("提示"),qsTr("导出数据已完成"))
            else
                window.showDialog(qsTr("提示"),qsTr("没有找到可以使用的U盘或尝试再次导出"))
        }
    }

    color: pRgb(153, 204, 255)
    Component.onCompleted: {
        bt1.checkable = true
    }
    onItemCountChanged: {
        if(itemCount == 1){
            bt3.visible = false
            bt4.visible = false
            bt5.visible = false
        }
        else if(itemCount == 2){
            bt3.visible = true
            bt4.visible = false
            bt5.visible = false
        }
        else if(itemCount == 3){
            bt3.visible = true
            bt4.visible = true
            bt5.visible = false
        }
        else if(itemCount == 4){
            bt3.visible = true
            bt4.visible = true
            bt5.visible = true
        }
    }

    ButtonGroup {
        id: group1
    }
    ButtonGroup {
        id: group2
    }
    Rectangle{
        id:rect
        x:27
        y:22
        width: 1222
        // height: 677
        height: 616
        color: "#007dbc"
        radius: 3
    }

    Rectangle{
        id:top
        width: 1220
        height: 70
        color: "#007dbc"
        anchors.top: rect.top
        anchors.left: rect.left
        radius: 3
        Text {
            id: name
            // text: qsTr("设备")
            text: GlobalLanguageDefine.strDevice
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.topMargin: 25
            color: pRgb(177, 213, 219)
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
            font.pixelSize: 20
        }
        RadioButton{
            id:bt1
            width: 40
            height: 40
            anchors.left: name.right
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.leftMargin: 20
            ButtonGroup.group: group1
            checked: true
            indicator: Rectangle
            {
                width: 40
                height: 40
                radius: 20
                color: bt1.checked ? buttonColor : "#e8e8e8"
                border.color: bt1.checked ? "#afc3d8" : "#0068a8"
                border.width: 2
            }
            onPressed: {
                History.setDeviceID(0)
                //History.setWelderID(0)
            }
        }
        Text {
            id: b1
            anchors.left: bt1.right
            anchors.top: parent.top
            anchors.topMargin: 25
            anchors.leftMargin: 6
            // text: qsTr("全选")
            text: GlobalLanguageDefine.strSelectAll
            color: pRgb(177, 213, 219)
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
            font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 20 : 16
        }

        RadioButton{
            id:bt2
            width: 40
            height: 40
            anchors.verticalCenter: bt1.verticalCenter
            anchors.left: bt1.right
            anchors.leftMargin: 80
            ButtonGroup.group: group1
            indicator: Rectangle
            {
                width: 40
                height: 40
                radius: 20
                color: bt2.checked ? buttonColor : "#e8e8e8"
                border.color: bt2.checked ? "#afc3d8" : "#0068a8"
                border.width: 2
            }
            onPressed: {
                History.setDeviceID(1)
            }
        }
        Text {
            id: b2
            anchors.verticalCenter: bt2.verticalCenter
            anchors.left: bt2.right
            anchors.leftMargin: 6
            anchors.top: parent.top
            anchors.topMargin: 25
            // text: qsTr("设备") + "1"
            text: GlobalLanguageDefine.strDevice + "1"
            color: pRgb(177, 213, 219)
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
            font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 20 : 16
        }

        RadioButton{
            id:bt3
            width: 40
            height: 40
            anchors.verticalCenter: bt2.verticalCenter
            anchors.left: bt2.right
            anchors.leftMargin: 80
            ButtonGroup.group: group1
            indicator: Rectangle
            {
                width: 40
                height: 40
                radius: 20
                color: bt3.checked ? buttonColor : "#e8e8e8"
                border.color: bt3.checked ? "#afc3d8" : "#0068a8"
                border.width: 2
            }
            onVisibleChanged: {
                if(visible){
                    enabled = true
                }
                else{
                    enabled = false
                }
            }
            onPressed: {
                History.setDeviceID(2)
            }
        }
        Text {
            id: b3
            anchors.verticalCenter: bt3.verticalCenter
            anchors.left: bt3.right
            anchors.leftMargin: 6
            // text: qsTr("设备") + "2"
            anchors.top: parent.top
            anchors.topMargin: 25
            text: GlobalLanguageDefine.strDevice + "2"
            color: pRgb(177, 213, 219)
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
            font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 20 : 16
            visible: bt3.visible
        }

        RadioButton{
            id:bt4
            width: 40
            height: 40
            anchors.verticalCenter: bt3.verticalCenter
            anchors.left: bt3.right
            anchors.leftMargin: 80
            ButtonGroup.group: group1
            indicator: Rectangle
            {
                width: 40
                height: 40
                radius: 20
                color: bt4.checked ? buttonColor : "#e8e8e8"
                border.color: bt4.checked ? "#afc3d8" : "#0068a8"
                border.width: 2
            }
            onVisibleChanged: {
                if(visible){
                    enabled = true
                }
                else{
                    enabled = false
                }
            }
            onPressed: {
                History.setDeviceID(3)
            }
        }
        Text {
            id: b4
            anchors.verticalCenter: bt4.verticalCenter
            anchors.left: bt4.right
            anchors.leftMargin: 6
            anchors.top: parent.top
            anchors.topMargin: 25
            // text: qsTr("设备") + "3"
            text: GlobalLanguageDefine.strDevice + "3"
            color: pRgb(177, 213, 219)
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
            font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 20 : 16
            visible: bt4.visible
        }

        RadioButton{
            id:bt5
            width: 40
            height: 40
            anchors.verticalCenter: bt4.verticalCenter
            anchors.left: bt4.right
            anchors.leftMargin: 80
            ButtonGroup.group: group1
            indicator: Rectangle
            {
                width: 40
                height: 40
                radius: 20
                color: bt5.checked ? buttonColor : "#e8e8e8"
                border.color: bt5.checked ? "#afc3d8" : "#0068a8"
                border.width: 2
            }
            onVisibleChanged: {
                if(visible){
                    enabled = true
                }
                else{
                    enabled = false
                }
            }
            onPressed: {
                History.setDeviceID(4)
            }
        }
        Text {
            id: b5
            anchors.verticalCenter: bt5.verticalCenter
            anchors.left: bt5.right
            anchors.leftMargin: 6
            // text: qsTr("设备") + "4"
            anchors.top: parent.top
            anchors.topMargin: 25
            text: GlobalLanguageDefine.strDevice + "4"
            color: pRgb(177, 213, 219)
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
            font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 20 : 16
            visible: bt5.visible
        }

        Text {
            id: name1
            // text: qsTr("结果")
            text: GlobalLanguageDefine.strResult
            anchors.top: name.top
            anchors.left: parent.left
            anchors.leftMargin: 723
            color: pRgb(177, 213, 219)
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
            font.pixelSize: 20
        }
        RadioButton{
            id:bt8
            width: 40
            height: 40
            anchors.verticalCenter: name1.verticalCenter
            anchors.left: name1.right
            anchors.leftMargin: 18
            ButtonGroup.group: group2
            checked: true
            indicator: Rectangle
            {
                width: 40
                height: 40
                radius: 20
                color: bt8.checked ? buttonColor : "#e8e8e8"
                border.color: bt8.checked ? "#afc3d8" : "#0068a8"
                border.width: 2
            }
            onPressed: {
                History.setFinalResult(0)
            }    
        }
        Text {
            id: b8
            anchors.verticalCenter: bt8.verticalCenter
            anchors.left: bt8.right
            anchors.leftMargin: 6
            // text: qsTr("全选")
            text: GlobalLanguageDefine.strSelectAll
            color: pRgb(177, 213, 219)
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
            font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 20 : 16
        }
        RadioButton{
            id:bt9
            width: 40
            height: 40
            anchors.verticalCenter: bt8.verticalCenter
            anchors.left: bt8.right
            anchors.leftMargin: 60
            ButtonGroup.group: group2
            indicator: Rectangle
            {
                width: 40
                height: 40
                radius: 20
                color: bt9.checked ? buttonColor : "#e8e8e8"
                border.color: bt9.checked ? "#afc3d8" : "#0068a8"
                border.width: 2
            }
            onPressed: {
                History.setFinalResult(1)
            }
        }
        Text {
            id: b9
            anchors.verticalCenter: bt9.verticalCenter
            anchors.left: bt9.right
            anchors.leftMargin: 6
            // text: qsTr("良")
            text: GlobalLanguageDefine.strGood
            color: pRgb(177, 213, 219)
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
            font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 20 : 16
        }
        RadioButton{
            id:bt11
            width: 40
            height: 40
            anchors.verticalCenter: bt9.verticalCenter
            anchors.left: bt9.right
            anchors.leftMargin: 70
            ButtonGroup.group: group2
            indicator: Rectangle
            {
                width: 40
                height: 40
                radius: 20
                color: bt11.checked ? buttonColor : "#e8e8e8"
                border.color: bt11.checked ? "#afc3d8" : "#0068a8"
                border.width: 2
            }
            onPressed: {
                History.setFinalResult(3)
            }

        }
        Text {
            id: b11
            anchors.verticalCenter: bt11.verticalCenter
            anchors.left: bt11.right
            anchors.leftMargin: 6
            // text: qsTr("可疑")
            text: GlobalLanguageDefine.strSuspicious
            color: pRgb(177, 213, 219)
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
            font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 20 : 16
        }
        RadioButton{
            id:bt10
            width: 40
            height: 40
            anchors.verticalCenter: bt11.verticalCenter
            anchors.left: bt11.right
            anchors.leftMargin: 70
            ButtonGroup.group: group2
            indicator: Rectangle
            {
                width: 40
                height: 40
                radius: 20
                color: bt10.checked ? buttonColor : "#e8e8e8"
                border.color: bt10.checked ? "#afc3d8" : "#0068a8"
                border.width: 2
            }
            onPressed: {
                History.setFinalResult(2)
            }
        }
        Text {
            id: b10
            anchors.verticalCenter: bt10.verticalCenter
            anchors.left: bt10.right
            anchors.leftMargin: 6
            // text: qsTr("次品")
            text: GlobalLanguageDefine.strDefective
            color: pRgb(177, 213, 219)
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
            font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 20 : 16
        }
    }
    Rectangle{
        width: 1220
        // height: 605
        height: 510
        anchors.top: top.bottom
        anchors.left: top.left
        anchors.leftMargin: 1
        color: "#004b8d"
        Text{
            id:t1
            anchors.left: parent.left
            anchors.leftMargin: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 20 : 10
            anchors.top: parent.top
            anchors.topMargin: 7
            font.pixelSize: 16
            text: GlobalLanguageDefine.strDeviceName
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
            color: pRgb(153, 204, 255)
        }
        Text{
            id: serialNumberText
            anchors.left: parent.left
            anchors.leftMargin: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 120 : 130
            anchors.top: parent.top
            anchors.topMargin: 7
            font.pixelSize: 16
            text: GlobalLanguageDefine.strCycleCount
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
            color: pRgb(153, 204, 255)
        }
        Text{
            id: historyDateText
            anchors.top: t1.top
            anchors.left: t1.right
            anchors.leftMargin: 200
            font.pixelSize: 16
            text: GlobalLanguageDefine.strDate
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
            color: pRgb(153, 204, 255)
        }
        Text{
            id: historyEnergyeText
            anchors.top: historyDateText.top
            anchors.left: historyDateText.right
            anchors.leftMargin: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 120 : 80
            font.pixelSize: 16
            text: GlobalLanguageDefine.strEnergy + "(J)"
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
            color: pRgb(153, 204, 255)
        }
        Text{
            id: historyAmplitudeText
            anchors.top: historyEnergyeText.top
            anchors.left: historyEnergyeText.right
            anchors.leftMargin: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 70 : 40
            font.pixelSize: 16
            text: GlobalLanguageDefine.strAmplitude + "(μm)"
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
            color: pRgb(153, 204, 255)
        }
        Text{
            id: historyPowerText
            anchors.top: historyAmplitudeText.top
            anchors.left: historyAmplitudeText.right
            anchors.leftMargin: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 70 : 40
            font.pixelSize: 16
            text: GlobalLanguageDefine.strPower + "(W)"
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
            color: pRgb(153, 204, 255)
        }
        Text{
            id: historyWeldTimeText
            anchors.top: historyPowerText.top
            anchors.left: historyPowerText.right
            anchors.leftMargin: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 70 : 50
            font.pixelSize: 16
            text: GlobalLanguageDefine.strTime + "(S)"
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
            color: pRgb(153, 204, 255)
        }
        Text{
            id: historyWeldPressureText
            anchors.top: historyWeldTimeText.top
            anchors.left: historyWeldTimeText.right
            anchors.leftMargin: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 70 : 40
            font.pixelSize: 16
            text: GlobalLanguageDefine.strWeldPressure + "(Psi)"
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
            color: pRgb(153, 204, 255)
        }
        Text{
            id: historyWeldResultText
            anchors.top: historyWeldPressureText.top
            anchors.left: historyWeldPressureText.right
            anchors.leftMargin: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 85 : 50
            font.pixelSize: 16
            text: GlobalLanguageDefine.strResult
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
            color: pRgb(153, 204, 255)
        }
        ListView{
            id: taskplanView
            width: 1220
            // height: 560
            height: 510
            y:35
            clip: true
            model: History
            delegate: Rectangle{
                id: regionItem
                height: 36
                width: 1220
                color: index % 2 === 0 ? "#2d71ae" : "#b1d5db"
                Text{
                    id:historyDeviceNameValueText
                    anchors.left: parent.left
                    anchors.leftMargin: 30
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 16
                    text: DeviceManager.getHistoryName(welder_id)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    color: index % 2 === 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                }
                Text{
                     id: rowNumberText
                     anchors.verticalCenter: parent.verticalCenter
                     anchors.left: parent.left
                     anchors.leftMargin: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 120 : 150
                     font.pixelSize: 16
                     text: cycle_count
                     font.family: GlobalSystemDefine.fontBold
                     font.bold: true
                     color: index % 2 === 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                 }
               Text{
                    id: historyDateValueText
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 220 : 250
                    font.pixelSize: 16
                    text: UtilityFunction.timestampToString(create_time)
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    color: index % 2 === 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                }
                Text{
                    id: historyEnergyValueText
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 447
                    font.pixelSize: 16
                    text: energy
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    color: index % 2 === 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                }
                Text{
                    id: historyAmplitudeValueText
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 580
                    font.pixelSize: 16
                    text: amplitude
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    color: index % 2 === 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                }
                Text{
                    id: historyPowerValueText
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 709
                    font.pixelSize: 16
                    text: power
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    color: index % 2 === 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                }
                Text{
                    id: historyTimeValueText
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 840
                    font.pixelSize: 16
                    text: time
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    color: index % 2 === 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                }
                Text{
                    id: historyPressureValueText
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 975
                    font.pixelSize: 16
                    text: weld_pressure
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    color: index % 2 === 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                }


                Text{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 1136
                    font.pixelSize: 16
                    text: {
                        // var strResult = qsTr("可疑")
                        var strResult = GlobalLanguageDefine.strSuspicious
                        switch(final_result)
                        {
                        case 0:
                            // strResult = qsTr("良品")
                            strResult = GlobalLanguageDefine.strGood
                            break;
                        case 1:
                            // strResult = qsTr("次品")
                            strResult = GlobalLanguageDefine.strDefective
                            break;
                        default:
                            // strResult = qsTr("可疑")
                            strResult = GlobalLanguageDefine.strSuspicious
                            break;
                        }
                        return strResult;
                    }
                    font.family: GlobalSystemDefine.fontBold
                    font.bold: true
                    color: index % 2 === 0 ? pRgb(177, 213, 219) : pRgb(45, 113, 174)
                }
            }
        }

    }

    Text {
        id: usbVisableText
        anchors.left: parent.left
        anchors.leftMargin: 25
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        text: window.isUSBAvailable ? GlobalLanguageDefine.strUSBConnected : GlobalLanguageDefine.strNoUSB
        color: "#E8E8E8"
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 20
    }

    Button{
        width: 120
        height: 36
        anchors.top: usbVisableText.top
        anchors.right: parent.right
        anchors.rightMargin: 35
        visible: window.isUSBAvailable
        background: Rectangle{
            radius: 6
            color: pRgb(43, 112, 173)
        }

        contentItem: Text {
            text: GlobalLanguageDefine.strExportButton
            font.pixelSize: 20
            color: pRgb(153, 204, 255)
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
        }
        onClicked:
        {
             window.showLoading(true)
            if(History.exportData() === false)
            {
                window.showLoading(false)
            }
            else
            {
                // window.showDialog(qsTr("提示"), qsTr("无法开始导出，未找到可用的U盘"))
            }
        }
    }

}
