import QtQuick 2.15
import QtQuick.Window 2.11
import QtQuick.Controls 1.3 as Controls
import QtQuick.Controls 2.15
import Material 0.3
import Material.ListItems 0.1 as ListItem
import QtQuick.Layouts 1.3

Item {
    anchors.fill: parent
    Column {
        anchors.centerIn: parent
        Label {
            width: dp(300)
            height: dp(100)
            text: "First_Name"
        }
        Label {
            width: dp(300)
            height: dp(100)
            text: "Last_Name"
        }
    }
}
