import QtQuick 2.0
import QtQuick.Controls 2.5
Rectangle {
    color: pRgb(43, 112, 173)

    function bt1Check(){
        bt1.cbtnText.color = pRgb(177, 213, 219)
        bt1.btnCheck.visible = true
        bt2.cbtnText.color = pRgb(153, 204, 255)
        bt2.btnCheck.visible = false
        bt3.cbtnText.color = pRgb(153, 204, 255)
        bt3.btnCheck.visible = false
        bt2.tmp = false
        bt3.tmp = false
    }
    function bt2Check(){
        bt2.cbtnText.color = pRgb(177, 213, 219)
        bt2.btnCheck.visible = true
        bt1.cbtnText.color = pRgb(153, 204, 255)
        bt1.btnCheck.visible = false
        bt3.cbtnText.color = pRgb(153, 204, 255)
        bt3.btnCheck.visible = false
        bt1.tmp = false
        bt3.tmp = false
    }
    function bt3Check(){
        bt3.cbtnText.color = pRgb(177, 213, 219)
        bt3.btnCheck.visible = true
        bt2.cbtnText.color = pRgb(153, 204, 255)
        bt2.btnCheck.visible = false
        bt1.cbtnText.color = pRgb(153, 204, 255)
        bt1.btnCheck.visible = false
        bt2.tmp = false
        bt1.tmp = false
    }
    Button{
        x:20
        y:12
        width: 64
        height: 36
        background: Image {
            source: "qrc:/image/title.png"  // 替换为你的图像路径
            fillMode: Image.PreserveAspectCrop  // 调整图片填充模式
        }
        onClicked: {

        }
    }
    Text {
        x:94
        y:6
        width: 180
        height: 44
        text: "在线监测系统"
        color: pRgb(153, 204, 255)
        font.family: fontBold
        font.pixelSize: 30
    }
    CustomBtn{
        id:bt1
        x:810
        tmp:true
        width: 157
        height: 60
        btnText:"生产界面"
    }
    CustomBtn{
        id:bt2
        anchors.left: bt1.right
        width: 157
        height: 60
        btnText:"历史记录"
    }
    CustomBtn{
        id:bt3
        anchors.left: bt2.right
        width: 157
        height: 60
        btnText:"系统配置"
    }
    Connections{
        target: bt1
        function onSigBtnSwitch(){
            bt1Check()
            switchUI(1)
        }
    }
    Connections{
        target: bt2
        function onSigBtnSwitch(){
            bt2Check()
            switchUI(2)
        }
    }
    Connections{
        target: bt3
        function onSigBtnSwitch(){
            bt3Check()
            switchUI(3)
        }
    }
}
