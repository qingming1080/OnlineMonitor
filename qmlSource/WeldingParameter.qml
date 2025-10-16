import QtQuick 2.0
import QtQuick.Controls 2.15
import GlobalLanguageDefine 1.0
import GlobalSystemDefine 1.0
import LanguageEnum         1.0
//焊接参数

Rectangle {
    color: pRgb(43, 112, 173)
    property string eqText1: ""
    property string eqText2: ""
    property string eqText3: ""
    property string eqText4: ""
    property string eqText5: ""
    property bool altitudeMode:DeviceManager.deviceList[swipeCurrIndex].DevInfoObject.heightOption
                               === 1 ? true:false

    property int selectedTab: 0  // 0: 焊接参数, 1: 参数设置
    property int deviceID: DeviceManager.deviceList[swipeCurrIndex].DevInfoObject.id

    radius: 3
    Rectangle {
           width:  equipmentCount == 1 ? 117 : 129
           height: 35
           //border.color: selectedTab === 0 ? pRgb(43, 112, 173) :  pRgb(232, 232, 232) // 选中时边框颜色
           border.color: selectedTab === 0 ? pRgb(232, 232, 232) : pRgb(43, 112, 173) // 选中时边框颜色
           border.width: 1  // 设置边框宽度
           radius: 1
           color: selectedTab === 0 ? pRgb(232, 232, 232) : pRgb(43, 112, 173) // 选中时背景颜色
           anchors.left: parent.left
           anchors.top: parent.top

           Text {
               // text: qsTr("焊接参数")
               text: GlobalLanguageDefine.strWeldingParameter
               font.family: GlobalSystemDefine.fontBold
               font.bold: true
               font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 20 : 18
               color: selectedTab === 0 ? pRgb(43, 112, 173) : pRgb(153, 204, 255)  // 选中时文字颜色
               anchors.centerIn: parent  // 使文字居中
           }

           MouseArea {
               anchors.fill: parent
               onClicked: {
                   selectedTab = 0  // 设置选中标签为焊接参数
                   console.log("焊接参数点击了！")
                   // 在这里执行相应的操作
               }
           }
       }

       // 参数设置标签
       Rectangle {
           width: equipmentCount == 1 ? 116 : 129
           height: 35
          // border.color: selectedTab === 1 ? pRgb(43, 112, 173) :  pRgb(232, 232, 232) // 选中时边框颜色
           border.color: selectedTab === 1 ?  pRgb(232, 232, 232): pRgb(43, 112, 173) // 选中时边框颜色
           border.width: 0.5 // 设置边框宽度
           color: selectedTab === 1 ?  pRgb(232, 232, 232) : pRgb(43, 112, 173)   // 选中时背景颜色
           radius: 1
           anchors.left: parent.left
           anchors.top: parent.top
           anchors.leftMargin: 129  // 设置距离焊接参数标签的间隔

           Text {
               // text: qsTr("参数设置")
               text: GlobalLanguageDefine.strParameterSetting
               font.family: GlobalSystemDefine.fontBold
               font.bold: true
               font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 20 : 18
               color: selectedTab === 1 ? pRgb(43, 112, 173) : pRgb(153, 204, 255)   // 选中时文字颜色
               anchors.centerIn: parent  // 使文字居中
           }

           MouseArea {
               anchors.fill: parent
               onClicked: {
                   selectedTab = 1
                   parameterSetting.open()
                   console.log("deviceID: ", DeviceManager.deviceList[swipeCurrIndex].DevInfoObject.id)
                   //TODO need to double check
                   // ModbusClient.readParameterSetting(deviceID)
                   // console.log("energy_set: ",result[0].toString())
                   // console.log("amplitude_set: ",result[1].toString())
                   // console.log("tp_set: ",result[2].toString())
                   // console.log("wp_set: ",result[3].toString())
                   // console.log("time_max_set: ",result[4].toString())
                   // console.log("time_min_set: ",result[5].toString())
                   // console.log("power_min_set: ",result[6].toString())
                   // console.log("power_max_set: ",result[7].toString())
                   // console.log("pre_hehigtmin_set: ",result[8].toString())
                   // console.log("pre_hehigtmax_set: ",result[9].toString())
                   // console.log("post_hehigtmin_set: ",result[10].toString())
                   // console.log("post_hehigtmax_set: ",result[11].toString())
               }
           }
   }

    Image {
        id: imageEnergy
        source: "qrc:/images/icon_energy.png"
        x:altitudeMode ? 17:30
        y:altitudeMode ? 50:58
        width: altitudeMode ? 25:30
        height: altitudeMode ? 25:30
    }
    Image {
        id: imageAmplitude
        source: "qrc:/images/icon_amplitude.png"
        anchors.top: imageEnergy.bottom
        anchors.left: imageEnergy.left
        anchors.topMargin: altitudeMode ? 12 :22
        width: altitudeMode ? 25:30
        height: altitudeMode ? 25:30
    }
    Image {
        id: imageWeldPressure
        source: "qrc:/images/icon_wp.png"
        anchors.top: imageAmplitude.bottom
        anchors.left: imageAmplitude.left
        anchors.topMargin: altitudeMode ? 12 :22
        width: altitudeMode ? 25:30
        height: altitudeMode ? 25:30
    }
    Image {
        id: imagePreheight
        source: "qrc:/images/icon_preheight.png"
        anchors.top: imageWeldPressure.bottom
        anchors.left: imageWeldPressure.left
        anchors.topMargin: altitudeMode ? 12 :22
        visible: altitudeMode
        width: altitudeMode ? 25:30
        height: altitudeMode ? 25:30
    }
    Image {
        id: imagePostHeight
        source: "qrc:/images/icon_preheight.png"
        anchors.top: imagePreheight.bottom
        anchors.left: imagePreheight.left
        anchors.topMargin: altitudeMode ? 12 :22
        visible: altitudeMode
        width: altitudeMode ? 25:30
        height: altitudeMode ? 25:30
    }
    Text {
        id: titleEnergy
        // text: qsTr("能量")
        text: GlobalLanguageDefine.strEnergy + ": "
        height: altitudeMode ? 25:30
        width: 50
        font.family: GlobalSystemDefine.fontBold
        // font.bold: true
        font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 16 : 14
        color: pRgb(171, 206, 213)
        verticalAlignment: Text.AlignVCenter
        anchors.verticalCenter: imageEnergy.verticalCenter
        anchors.left: imageEnergy.right
        anchors.leftMargin: 10
    }
    Text {
        id: titleAmplitude
        // text: qsTr("振幅")
        text: GlobalLanguageDefine.strAmplitude + ": "
        height: altitudeMode ? 25:30
        width: 50
        font.family: GlobalSystemDefine.fontBold
        // font.bold: true
        font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 16 : 14
        color: pRgb(171, 206, 213)
        verticalAlignment: Text.AlignVCenter
        anchors.verticalCenter: imageAmplitude.verticalCenter
        anchors.left: imageAmplitude.right
        anchors.leftMargin: 10
    }
    Text {
        id: titleWeldPressure
        // text: qsTr("压力")
        text: GlobalLanguageDefine.strWeldPressure + ": "
        height: altitudeMode ? 25:30
        width: 50
        font.family: GlobalSystemDefine.fontBold
        // font.bold: true
        font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 16 : 14
        color: pRgb(171, 206, 213)
        verticalAlignment: Text.AlignVCenter
        anchors.verticalCenter: imageWeldPressure.verticalCenter
        anchors.left: imageWeldPressure.right
        anchors.leftMargin: 10
    }
    Text {
        id: titlePreheight
        // text: qsTr("焊前高度")
        text: GlobalLanguageDefine.strPreWeldHeight + ": "
        height: altitudeMode ? 25:30
        width: 50
        font.family: GlobalSystemDefine.fontBold
        // font.bold: true
        font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 16 : 14
        color: pRgb(171, 206, 213)
        verticalAlignment: Text.AlignVCenter
        anchors.verticalCenter: imageWeldPressure.verticalCenter
        anchors.left: imageWeldPressure.right
        anchors.leftMargin: 10
        visible: altitudeMode
    }
    Text {
        id: titlePostHeight
        // text: qsTr("焊后高度")
        text: GlobalLanguageDefine.strPostWeldHeight + ": "
        height: altitudeMode ? 25:30
        width: 50
        font.family: GlobalSystemDefine.fontBold
        // font.bold: true
        font.pixelSize: LanguageManager.LanguageIndex === LanguageEnum.SIMPLIFIED_CHINESE ? 16 : 14
        color: pRgb(171, 206, 213)
        verticalAlignment: Text.AlignVCenter
        anchors.verticalCenter: imagePostHeight.verticalCenter
        anchors.left: imagePostHeight.right
        anchors.leftMargin: 10
        visible: altitudeMode
    }
    TextField{
        id: fieldEnergy
        width: /*mode === 1 ? 75:*/98
        height: altitudeMode ? 28 :30
        anchors.left: titleEnergy.right
        anchors.leftMargin: altitudeMode ? 38:25
        anchors.verticalCenter: titleEnergy.verticalCenter
        horizontalAlignment: TextInput.AlignHCenter
        // verticalAlignment: TextInput.AlignBottom
        color: pRgb(43, 112, 173)
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        inputMethodHints: Qt.ImhDigitsOnly
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: "#99ccff"
        }
        text: eqText1
        MouseArea {
            anchors.fill: parent
            onPressed: {
                fieldEnergy.forceActiveFocus()
                keyboardType = 0
            }
        }
    }
    TextField{
        id: fieldAmplitude
        width: /*mode === 1 ? 75:*/98
        height: altitudeMode ? 28 :30
        anchors.left: titleAmplitude.right
        anchors.leftMargin: altitudeMode ? 38:25
        anchors.verticalCenter: titleAmplitude.verticalCenter
        horizontalAlignment: TextInput.AlignHCenter
        // verticalAlignment: TextInput.AlignVCenter
        color: pRgb(43, 112, 173)
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        inputMethodHints: Qt.ImhDigitsOnly
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: "#99ccff"
        }
        text:eqText2
        MouseArea {
            anchors.fill: parent
            onPressed: {
                fieldAmplitude.forceActiveFocus()
                keyboardType = 0
            }
        }
    }
    TextField{
        id: fieldWeldPressure
        width: /*mode === 1 ? 75:*/98
        height: altitudeMode ? 28 :30
        anchors.left: titleWeldPressure.right
        anchors.leftMargin: altitudeMode ? 38:25
        anchors.verticalCenter: titleWeldPressure.verticalCenter
        horizontalAlignment: TextInput.AlignHCenter
        // verticalAlignment: TextInput.AlignVCenter
        color: pRgb(43, 112, 173)
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        inputMethodHints: Qt.ImhDigitsOnly
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: "#99ccff"
        }
        text:eqText3
        MouseArea {
            anchors.fill: parent
            onPressed: {
                fieldWeldPressure.forceActiveFocus()
                keyboardType = 0
            }
        }
    }
    TextField{
        id: fieldPreheight
        width: /*mode === 1 ? 75:*/98
        height: altitudeMode ? 28 :30
        anchors.left: titlePreheight.right
        anchors.leftMargin: altitudeMode ? 38:25
        anchors.verticalCenter: titlePreheight.verticalCenter
        horizontalAlignment: TextInput.AlignHCenter
        // verticalAlignment: TextInput.AlignVCenter
        color: pRgb(43, 112, 173)
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        inputMethodHints: Qt.ImhDigitsOnly
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: "#99ccff"
        }
        text:eqText4
        visible: altitudeMode
        MouseArea {
            anchors.fill: parent
            onPressed: {
                fieldPreheight.forceActiveFocus()
                keyboardType = 0
            }
        }
    }
    TextField{
        id: fieldPostHeight
        width: /*mode === 1 ? 75:*/98
        height: altitudeMode ? 28 :30
        anchors.left: titlePostHeight.right
        anchors.leftMargin: altitudeMode ? 38:25
        anchors.verticalCenter: titlePostHeight.verticalCenter
        horizontalAlignment: TextInput.AlignHCenter
        // verticalAlignment: TextInput.AlignVCenter
        color: pRgb(43, 112, 173)
        font.family: GlobalSystemDefine.fontBold
        font.bold: true
        font.pixelSize: 16
        inputMethodHints: Qt.ImhDigitsOnly
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: "#99ccff"
        }
        text:eqText5
        visible: altitudeMode
        MouseArea {
            anchors.fill: parent
            onPressed: {
                fieldPostHeight.forceActiveFocus()
                keyboardType = 0
            }
        }
    }

    ParameterSettingDialog {
        id: parameterSetting
        // onTimeSelected: {
        //     // 接收 timeDialog 中发出的 timeSelected 信号，并更新 timeText 显示的时间
        //     let date = new Date(year, month - 1, day, hour, minute, second);  // JavaScript 中月份是从 0 开始的
        //     timeText.text = date.toLocaleString();  // 将选中的时间转为本地时间字符串
        // }
    }

}
