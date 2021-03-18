import QtQuick 2.9
import Material 0.3
import Material.ListItems 0.1 as ListItem

import UThemes 1.0

Rectangle {
    id: root
    enum ButtonType {
        StandartType,
        SquareType
    }
    enum ButtonColor {
        MainColor,
        ExtraColor
    }

    property string buttonType: "StandartType"
    property string buttonMainColor: UThemes.buttonBack
    property string buttonBorderColor: UThemes.buttonBorder
    property string buttonHoverColor: UThemes.buttonBackHover
    property string buttonFontColor: UThemes.buttonFont
    property string buttonContent: "value"
    property int buttonWidth: 125
    property int buttonHeight: 40
    property bool buttonEnabled: true

    signal clicked

    width: buttonWidth
    height: buttonHeight
    border.width: buttonType == "StandartType" ? 2 : 2
    border.color: buttonBorderColor
    radius: buttonType == "StandartType" ? height/2 : 5

    Rectangle {
        anchors.fill: parent
        anchors.margins: parent.border.width
        id: button
        radius: parent.radius
        color: (!mouseArea.containsMouse ? buttonMainColor : buttonHoverColor)
        Text {
            id: text
//            clip: true
            elide: Text.ElideRight
            anchors.fill: parent
            text: qsTr(root.buttonContent)
            font.pixelSize: 16 * Units.dp
            color: buttonFontColor
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked: {
                    root.clicked();
                }

                enabled: buttonEnabled
                hoverEnabled: buttonEnabled
            }
        }
        Rectangle {
            visible: !buttonEnabled
            anchors.fill: parent
            radius: parent.radius
            z: 1
            color: "#20000000"
        }
        Behavior on color {
            ColorAnimation {
                duration: 200
            }
        }
        Behavior on border.color {
            ColorAnimation {
                duration: 200
            }
        }
    }

}
