/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
//import QtQuick.Controls 2.2
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import GlobalStyle 1.0
import GlobalSystemDefine 1.0

//import NumpadDefine 1.0
Item {
    id: primaryNumpad
    property int minWidth: Math.round(400 * GlobalStyle.scaleHint)
    property int maxHeight: Math.round(411 * GlobalStyle.scaleHint)
    property int headermaxHeight: Math.round(30 * GlobalStyle.scaleHint)
    property string headertext: "TRIGGER FORCE"
    property string suffix:  "%"
    property int decimals: 2
    property real minimumValue: 10
    property real maximumValue: 100
    property alias value: input.text
    property var targetTextField // allow the external object to register into Component
    signal valueUpdated(string newValue)
    property var confirmCallback
    property bool showMinMax: false

    function selectAll()
    {
        input.selectAll();
        input.isSelectedAll = true
    }

    function slotDigitalKeyPressed(data)
    {
        GlobalLanguageDefine.handleWithDigitalKeyInput(data, input, suffix)
    }

    Component.onCompleted: {
        bransonprimary.signalButtonNum.connect(slotDigitalKeyPressed)
        bransonprimary.signalButtonFunc.connect(slotDigitalKeyPressed)
    }


    Rectangle {
        id: background
        anchors.fill: parent
        color: GlobalStyle.dialogBackgroundColor
        opacity: 0.75
        MouseArea {
            anchors.fill: parent
        }
    }

    Rectangle
    {
        id:root
        implicitWidth: minWidth
        implicitHeight:maxHeight
        anchors.centerIn: parent
        color: "#FFFFFF"
        /*header title*/
        Rectangle
        {
            id: numpadHeader
            width: parent.width
            implicitHeight: headermaxHeight
            color: GlobalStyle.headerBackgroundColor
            Text {
                id: headername
                anchors.left: numpadHeader.left
                anchors.top: numpadHeader.top
                anchors.leftMargin: Math.round(5 * GlobalStyle.scaleHint)
                anchors.topMargin: Math.round(5 * GlobalStyle.scaleHint)
                text: headertext
                color: GlobalStyle.whiteFontColor
                font{
                    family: GlobalSystemDefine.fontBold
                    pixelSize: Math.round(GlobalStyle.style2 * GlobalStyle.scaleHint)
                }
            }

            Rectangle
            {
                id:rectimage
                implicitWidth: Math.round(24 * GlobalStyle.scaleHint)
                implicitHeight: Math.round(24 * GlobalStyle.scaleHint)
                anchors.right: numpadHeader.right
                anchors.rightMargin: Math.round(5 * GlobalStyle.scaleHint)
                anchors.top: numpadHeader.top
                anchors.topMargin:Math.round(5 * GlobalStyle.scaleHint)
                color: "transparent"
                Image {
                    id: headerClose
                    anchors.fill: parent
                    source: "qrc:/images/crossMark.svg"
                    sourceSize.width: headerClose.width
                    sourceSize.height: headerClose.height
                    smooth: true

                }
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        primaryNumpad.visible = false
                    }
                }
            }
        }
        /*main keyboard*/
        Rectangle
        {
            anchors.top: numpadHeader.bottom
            anchors.left: numpadHeader.left
            anchors.topMargin: Math.round(0* GlobalStyle.scaleHint)
            anchors.leftMargin: Math.round(200 * GlobalStyle.scaleHint)

            BransonTextField
            {
                id: input
                anchors.top: parent.top
                anchors.topMargin: Math.round(22 * GlobalStyle.scaleHint)
                anchors.horizontalCenter: parent.horizontalCenter
                width: Math.round(260 * GlobalStyle.scaleHint)
                height: Math.round(30 * GlobalStyle.scaleHint)
                focus: true
                onlyForNumpad: true
                onTextChanged:
                {
                    GlobalLanguageDefine.decimalsNumber(decimals,input, suffix)
                }
            }
            Text {
                id: txtUnit
                text: suffix
                anchors.right: input.right
                anchors.rightMargin: Math.round(5 * GlobalStyle.scaleHint)
                anchors.top: input.top
                anchors.topMargin: Math.round(4 * GlobalStyle.scaleHint)
                color: GlobalStyle.blackFontColor
                font.pixelSize: Math.round(GlobalStyle.style4 * GlobalStyle.scaleHint)
                font.family: GlobalSystemDefine.fontBold
            }
            Label {
                id: labelMin
                text: GlobalLanguageDefine.strKeyBoardMinimun + ":" //qsTr("Min:")
                anchors.top: input.bottom
                anchors.left: input.left
                anchors.topMargin: Math.round(2 * GlobalStyle.scaleHint)
                font.pixelSize: Math.round(GlobalStyle.style3 * GlobalStyle.scaleHint)
                font.family: GlobalSystemDefine.fontBold
                color: GlobalStyle.blueFontColor
                visible: showMinMax
            }
            Text {
                id: txtMin
                text: GlobalLanguageDefine.numberToString(decimals, minimumValue)
                anchors.top: labelMin.top
                anchors.left: labelMin.right
                anchors.leftMargin:  Math.round(5 * GlobalStyle.scaleHint)
                font.pixelSize: Math.round(GlobalStyle.style3 * GlobalStyle.scaleHint)
                font.family: GlobalSystemDefine.fontBold
                color: GlobalStyle.blueFontColor
                visible: showMinMax

            }
            Label {
                id: labelMax
                text: GlobalLanguageDefine.strKeyBoardMaximum + ":" //qsTr("Max:")
                anchors.top: txtMax.top
                anchors.right: txtMax.left
                anchors.rightMargin: Math.round(5 * GlobalStyle.scaleHint)
                font.pixelSize: Math.round(GlobalStyle.style3 * GlobalStyle.scaleHint)
                font.family: GlobalSystemDefine.fontBold
                color: GlobalStyle.blueFontColor
                visible: showMinMax
            }
            Text {
                id: txtMax
                text: GlobalLanguageDefine.numberToString(decimals, maximumValue)
                anchors.top: input.bottom
                anchors.topMargin: Math.round(2 * GlobalStyle.scaleHint)
                anchors.right:  input.right
                font.pixelSize: Math.round(GlobalStyle.style3 * GlobalStyle.scaleHint)
                font.family: GlobalSystemDefine.fontBold
                color: GlobalStyle.blueFontColor
                visible: showMinMax

            }
            BransonNumKeyboard
            {
                id:bransonprimary
                anchors.top:input.bottom
                anchors.topMargin: Math.round(8 * GlobalStyle.scaleHint)
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
        /*bottom keyboard*/
        BransonPrimaryButton
        {
            id:cancel
            implicitWidth: Math.round(124 * GlobalStyle.scaleHint)
            implicitHeight: Math.round(30 * GlobalStyle.scaleHint)
            fontSize: Math.round(GlobalStyle.style2  * GlobalStyle.scaleHint)
            anchors.bottom: root.bottom
            anchors.bottomMargin: Math.round(15 * GlobalStyle.scaleHint)
            anchors.left: root.left
            anchors.leftMargin: Math.round(60 * GlobalStyle.scaleHint)
            text: GlobalLanguageDefine.strKeyBoardCancel
            font.family: GlobalSystemDefine.fontBold
            // buttonColor: GlobalStyle.backgroundColor
            // textColor: "#000000"
            onClicked:
            {
                primaryNumpad.visible = false
            }
        }

        BransonPrimaryButton
        {
            id:done
            implicitWidth: Math.round(124 * GlobalStyle.scaleHint)
            implicitHeight: Math.round(30 * GlobalStyle.scaleHint)
            fontSize: Math.round(GlobalStyle.style2  * GlobalStyle.scaleHint)
            anchors.top: cancel.top
            anchors.left: cancel.right
            anchors.leftMargin: Math.round(20 * GlobalStyle.scaleHint)
            text: GlobalLanguageDefine.strKeyBoardDone
            font.family: GlobalSystemDefine.fontBold
            onClicked:
            {
                primaryNumpad.visible = false
                targetTextField.text = value

                if (confirmCallback) {
                    confirmCallback(value)
                }

                valueUpdated(value)
            }
        }
    }

}
