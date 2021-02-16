import QtQuick 2.15
import QtQuick.Window 2.11
import QtQuick.Controls 1.3 as Controls
import QtQuick.Controls 2.15
import Material 0.3
import Material.ListItems 0.1 as ListItem
import QtQuick.Layouts 1.3


Dialog {
    id: cardView
    width: dp(600)
    height: dp(900)
    title: "ListN -> TaskN"
    text: "Task"
    hasActions: true
    dialogContent: ListView {
        id: layout
        model: 25
        width: parent.width
        height: contentHeight
        spacing: dp(5)
        interactive: false

        delegate: RowLayout {
            width: parent.width - dp(10)
            CheckBox {
//                checked:
            }
            TextField{
                Layout.fillWidth: true
            }
        }
    }

    positiveButtonText: "OK"
    negativeButtonText: "Cancel"
}
