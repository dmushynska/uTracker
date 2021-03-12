import QtQuick 2.9
//import QtQuick.Controls 1.4
import Material 0.2

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

    property string typeInput: "StandartType"
    property string colorInput: "MainColor"
    property string inputMainColor: "#5a585c"  //"#fad2e0"
    property string inputBorderColor: inputMainColor   //"#f6a2bf"
    property string inputHoverColor: "#8b8da0" //"#ffdad8"
    property string inputFontColor: "white"   //"#7a163c"
    property string placeholderContent: "value"
    property alias inputText: input.text
    property int inputWidth: 200
    property int inputHeight: 40
    property alias input: input

//    signal clicked

    width: inputWidth
    height: inputHeight
    border.width: typeInput == "StandartType" ? 2 : 2
    border.color: inputBorderColor
    radius: typeInput == "StandartType" ? height / 2 : 5

    Rectangle {
        id:content
        anchors.fill: parent
        anchors.margins: parent.border.width
        radius: parent.radius
        Item {
            id: shape
            width: parent.width - parent.radius
            height: parent.height
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom

            TextField {
                id: input
                showBorder: false
                anchors.fill: parent
                placeholderText: placeholderContent
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }

}
