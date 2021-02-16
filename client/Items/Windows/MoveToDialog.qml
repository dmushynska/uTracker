import QtQuick 2.4
import QtQuick.Controls 1.3 as QuickControls
import QtQuick.Layouts 1.1
import Material 0.3
import Material.ListItems 0.1 as ListItem
import Material.Extras 0.1


Dialog {
    property int idCard: 0000
    property int selectedListId: -1
    id: moveDialog
    width: layout.contentWidth < dp(600) ? layout.contentWidth > dp(400) ? layout.contentWidth : dp(400) : dp(400);
    height: layout.contentHeight + dp(150) < dp(900) ? layout.contentHeight + dp(150) : dp(900)
    title: "Move to.."
    hasActions: true
    dialogContent: ListView {
        id: layout
        model: mCardListsModel
        width: parent.width
        height: contentHeight
        spacing: dp(5)
        interactive: false
        QuickControls.ExclusiveGroup { id: optionGroup }
        delegate: RadioButton {
            width: parent.width - dp(10)
            text: titleD
            checked: false
            exclusiveGroup: optionGroup
            onClicked: {
                selectedListId = index + 1              // !!!!!! change to index
            }
        }
    }

    positiveButtonText: "Move"
    negativeButtonText: "Cancel"
    onAccepted:  {
        console.log("card " + idCard + " moved to " + selectedListId)


    }
}
