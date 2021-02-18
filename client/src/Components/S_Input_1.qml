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
    property string placeholderContent: "value"
    property alias inputText: input.text
    property int inputWidth: 200
    property int inputHeight: 40
    property alias input: input

//    signal clicked

    width: inputWidth
    height: inputHeight
    border.width: typeInput == "StandartType" ? 2 : 2
    border.color: colorInput == "MainColor" ? "#f6a2bf" : "#ffb4b0"
    radius: typeInput == "StandartType" ? height / 2 : 5

    Rectangle {
        id:content
        anchors.fill: parent
        anchors.margins: parent.border.width
        radius: parent.radius
//        color:
//        color: colorButton == "MainColor" ? (!mouseArea.containsMouse ? "#fad2e0" : "#ffdad8") : (!mouseArea.containsMouse ? "#ffdad8" : "#fad2e0")
        Item {
            id: shape
            width: parent.width - parent.radius
            height: parent.height
//            height: parent.height - parent.radius
//            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom

            TextField {
                id: input
                showBorder: false
                anchors.fill: parent
                placeholderText: placeholderContent
                anchors.horizontalCenter: parent.horizontalCenter
//                style.fieldPlaceholder.font.pixelSize: 12*dp(1)
            }
        }

//        MouseArea{
//            id: mouseArea
//            anchors.fill: parent
//            hoverEnabled: true
//        }
    //        onClick: {}
    }

}
