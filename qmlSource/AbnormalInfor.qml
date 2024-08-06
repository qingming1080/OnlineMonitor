import QtQuick 2.0
import QmlEnum 1.0
//异常信息
Rectangle {
    color: pRgb(43, 112, 173)
    property color listColor: pRgb(153, 204, 255)
    radius: 3
    Text {
        text: qsTr("异常信息")
        font.family: fontBold
        font.pixelSize: /*mode === 1 ? 17:*/20
        color: pRgb(153, 204, 255)
        x:17
        y:9
    }
    Rectangle{
        y:42
        height: 1
        width: 97
        color: pRgb(174, 210, 216)
    }
    ListView{
        id: taskplanView
        width: 260
        height: 220
        x:24
        y:68
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
                    color:listColor
                }
            }

        }
    }
}
