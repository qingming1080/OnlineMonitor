import QtQuick              2.0
import QtQuick.Controls     2.15
import Device               1.0
import GlobalLanguageDefine 1.0
import GlobalSystemDefine   1.0
import GlobalMessageDefine  1.0

Rectangle {
    radius: 5
    color: pRgb(153, 204, 255)

    Component.onCompleted:
    {
        advanceModel.resetAdvanceModel()
    }

    ListModel {
        id: advanceModel
        function resetAdvanceModel()
        {
            for(var i = 0; i < DeviceManager.DeviceCounter; i++)
            {
                advanceModel.append({"SingleFactor":    DeviceManager.DeviceList[i].DeviceObj.SingleFactor,
                                     "GeneralFactor":   DeviceManager.DeviceList[i].DeviceObj.GeneralFactor,
                                     "OtherFactor":     DeviceManager.DeviceList[i].DeviceObj.OtherFactor,
                                     "ForceThreshold":  DeviceManager.DeviceList[i].DeviceObj.ForceThreshold,
                                     "ResidualThreshold": DeviceManager.DeviceList[i].DeviceObj.ResidualThreshold,
                                     "AutoLearningCount": DeviceManager.DeviceList[i].DeviceObj.AutoLearningCount
                                     })
            }
        }
    }


    Item {
        id: advanceSetting
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 40;
        width: 1200
        height: 350
        Row {
            anchors.fill: parent
            spacing: 20
            Repeater {
                model: advanceModel
                delegate: Item {
                    width: 290
                    height: parent.height
                    AdminConfig {
                        id: advanceConfigure
                        width: 290
                        height: parent.height
                        eqText1: model.SingleFactor
                        eqText2: model.GeneralFactor
                        eqText3: model.OtherFactor
                        eqText4: model.AutoLearningCount
                    }

                    HBPrimaryButton {
                        id: btnAdvanceSave
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 10
                        text: GlobalLanguageDefine.strSave
                        onPressed: {
                            DeviceManager.SelectedDeviceIndex = index;
                            advanceModel.set(index, {"SingleFactor":    advanceConfigure.t1Edit.text,
                                                     "GeneralFactor":   advanceConfigure.t2Edit.text,
                                                     "OtherFactor":     advanceConfigure.t3Edit.text,
                                                     "AutoLearningCount": advanceConfigure.t4Edit.text})
                            DeviceManager.DeviceList[index].DeviceObj.SingleFactor = advanceConfigure.t1Edit.text
                            DeviceManager.DeviceList[index].DeviceObj.GeneralFactor = advanceConfigure.t2Edit.text
                            DeviceManager.DeviceList[index].DeviceObj.OtherFactor = advanceConfigure.t3Edit.text
                            DeviceManager.DeviceList[index].DeviceObj.AutoLearningCount = advanceConfigure.t4Edit.text
                            DeviceManager.updateDevice();
                        }
                    }
                }

            }
        }
    }

    Row {
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.top: advanceSetting.bottom
        anchors.topMargin: 20
        anchors.bottom: btn1.top
        anchors.bottomMargin: 20
        width: 1200
        spacing: 20
        AdminUpgrade {
            height: parent.height
            width: 290
        }

        AdminLicense {
            height: parent.height
            width: 290
        }
    }

    Button{
        id: btn1
        x:165
        y:654
        width: 243
        height: 52
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: pRgb(43, 112, 173)
            color: pRgb(43, 112, 173)
        }
        contentItem: Text {
            // text: qsTr("客户密码重置")
            text: GlobalLanguageDefine.strCustomerPasswordReset
            font.pixelSize: 20
            color: pRgb(153, 204, 255)
            anchors.centerIn: parent  // 确保文本在按钮内居中对齐
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
        }
        onPressed: {

        }
    }

    Button{
        id:btn3
        x:867
        y:654
        width: 243
        height: 52
        background: Rectangle{
            radius: 6
            border.width: 2
            border.color: pRgb(43, 112, 173)
            color: pRgb(43, 112, 173)
        }
        contentItem: Text {
            // text: qsTr("初始化")
            text: GlobalLanguageDefine.strInitialize
            font.pixelSize: 20
            color: pRgb(153, 204, 255)
            anchors.centerIn: parent  // 确保文本在按钮内居中对齐
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: GlobalSystemDefine.fontBold
            font.bold: true
        }
        onPressed: {

        }
    }
}
