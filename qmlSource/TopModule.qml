import QtQuick 2.0
import QtQuick.Controls 2.5
Rectangle {
    color: pRgb(43, 112, 173)

    Connections{
        target: window
        function onSigPassError(){
            if(bt1.tmp === true){
                bt1Check()
            }
            else if(bt2.tmp === true){
                bt2Check()
            }
            else if(bt3.tmp === true && bt4.tmp === true){
                if(equipmentCurrentIndex === 3){
                    bt3Check()
                }
                else if(equipmentCurrentIndex === 4){
                    bt4Check()
                }
            }
        }
    }

    function bt1Check(){
        bt2.tmp = false
        bt3.tmp = false
        bt4.tmp = false
        bt1.cbtnText.color = pRgb(177, 213, 219)
        bt1.btnCheck.visible = true
        bt2.cbtnText.color = pRgb(153, 204, 255)
        bt2.btnCheck.visible = false
        bt3.cbtnText.color = pRgb(153, 204, 255)
        bt3.btnCheck.visible = false
        bt4.visible = false
    }
    function bt2Check(){
        bt1.tmp = false
        bt3.tmp = false
        bt4.tmp = false
        bt2.cbtnText.color = pRgb(177, 213, 219)
        bt2.btnCheck.visible = true
        bt1.cbtnText.color = pRgb(153, 204, 255)
        bt1.btnCheck.visible = false
        bt3.cbtnText.color = pRgb(153, 204, 255)
        bt3.btnCheck.visible = false
        bt4.visible = false
    }
    function bt3Check(){
        bt2.tmp = false
        bt1.tmp = false
        bt4.tmp = false
        bt3.cbtnText.color = pRgb(177, 213, 219)
        bt3.btnCheck.visible = true
        bt2.cbtnText.color = pRgb(153, 204, 255)
        bt2.btnCheck.visible = false
        bt1.cbtnText.color = pRgb(153, 204, 255)
        bt1.btnCheck.visible = false
        bt4.visible = false
    }
    function bt4Check(){
        bt2.tmp = false
        bt1.tmp = false
        bt3.tmp = false
        bt4.cbtnText.color = pRgb(177, 213, 219)
        bt4.btnCheck.visible = true
        bt3.cbtnText.color = pRgb(153, 204, 255)
        bt3.btnCheck.visible = false
        bt2.cbtnText.color = pRgb(153, 204, 255)
        bt2.btnCheck.visible = false
        bt1.cbtnText.color = pRgb(153, 204, 255)
        bt1.btnCheck.visible = false
        bt4.visible = true
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
            popup.openPop(4)
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
        index:1
        Connections{
            target: bt1
            function onSigBtnSwitch(index){
                if(index === 1){
                    bt1Check()
                    switchUI(1)
                }
            }
        }
    }
    CustomBtn{
        id:bt2
        anchors.left: bt1.right
        width: 157
        height: 60
        btnText:"历史记录"
        index:2
        Connections{
            target: bt2
            function onSigBtnSwitch(index){
                if(index === 2){
                    bt2Check()
                    switchUI(2)
                }
            }
        }
    }
    CustomBtn{
        id:bt3
        anchors.left: bt2.right
        width: 157
        height: 60
        btnText:"系统配置"
        index:3
        Connections{
            target: bt3
            function onSigBtnSwitch(index){
                if(index === 3){
                    popup.openPop(1)
                }
            }
        }
    }
    CustomBtn{
        id:bt4
        anchors.right: bt1.left
        width: 157
        height: 60
        btnText:"   ROOT"
        visible: false
        index:4
        Connections{
            target: window
            function onSigRoot(){
                bt4Check()
                switchUI(4)
            }
        }
    }





}
