import QtQuick 2.4
import QtQuick.Layouts 1.1
import Material 0.3
import Material.ListItems 0.1 as ListItem
import Material.Extras 0.1

//Rectangle {

//}

Item {
    id: root
    property string formType: "StandartType"
    property string formMainColor: "#E7E6E2" // "#fad2e0"
    property string formFontColor: "#5a585c" // "#7a163c"
    property string formContent: "value"
    property int formWidth: 300
    property int formHeight: 40
    property bool formEnabled: true

    signal clicked

    width: formWidth
    height: formHeight

    View {
        anchors.horizontalCenter: parent.horizontalCenter
        width: formWidth - dp(20)
        height: formHeight
        radius: formType == "StandartType" ? height/2 : 10
        elevation: 1

        data: Rectangle {
            width: parent.width
            height: formHeight
            radius: formType == "StandartType" ? height/2 : 2

            Rectangle {
                z:1
                width: formHeight
                height: formHeight
                radius: formType == "StandartType" ? formHeight : parent.radius
                color: formFontColor
                Text {
                    id: letterName
                    text: formContent[0]
                    anchors.fill: parent
                    font.pixelSize: 20 * Units.dp
                    color: formMainColor
                    font.capitalization: Font.AllUppercase
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Rectangle {
                anchors.fill: parent
//                anchors.margins: parent.border.width
                id: form
                radius: parent.radius
                color: formMainColor
                Text {
                    id: text
                    elide: Text.ElideRight
                    anchors.fill: parent
                    text: root.formContent
                    font.pixelSize: 20 * Units.dp
                    color: formFontColor
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
        //            MouseArea {
        //                id: mouseArea
        //                anchors.fill: parent
        //                onClicked: {
        //                    root.clicked();
        //                }

        //                enabled: formEnabled
        //                hoverEnabled: formEnabled
        //            }
                }
                Rectangle {
                    visible: !formEnabled
                    anchors.fill: parent
                    radius: parent.radius
                    z: 1
                    color: "#20000000"
                }

            //        onClick: {}
            }

        }

    }
}


