import QtQuick 2.15
import QtQuick.Window 2.11
import QtQuick.Controls 1.3 as Controls
import QtQuick.Controls 2.15
import Material 0.3
import Material.ListItems 0.1 as ListItem
import QtQuick.Layouts 1.3
import "../Components"

import UThemes 1.0

Item {
    anchors.fill: parent
    property alias createDeskButton: createDesk
    Column {
        anchors.centerIn: parent
        spacing: dp(50)
        View {
            anchors.horizontalCenter: parent.horizontalCenter
            height: lable.implicitHeight + 30
            width: lable.implicitWidth + 40
            elevation: 1
            backgroundColor: UThemes.listBack
            Label {
                anchors.centerIn: parent
                id: lable
                text: "Welcome to uTracker, " + mUser.userLogin
                font.bold: true
                color: UThemes.font_
                font.pixelSize: 80 * Units.dp
                Behavior on color {
                    ColorAnimation {
                        duration: 200
                    }
                }
            }
        }
        S_Button_1 {
            id: createDesk
            anchors.horizontalCenter: parent.horizontalCenter
            buttonContent: "Let's start"
            width: dp(300)
            onClicked: rootAccount.showNav()
        }
    }
}
