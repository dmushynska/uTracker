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
    title: mDescriptor.getTaskTitle()
    text: mDescriptor.getTaskDescription()
    hasActions: true

    dialogContent:
    Column {

        width: parent.width
        height: contentHeight + addButton.height
        spacing: 10
        ListView {
            id: layout
            model: mDescriptor
            width: parent.width
            height: contentHeight
            spacing: dp(5)
            interactive: false

            delegate: RowLayout {
                width: parent.width - dp(10)
                CheckBox {
                    checked: pointCheck
                    onClicked: {
                        model.pointCheck = !model.pointCheck
                    }
                }
                TextField{
                    Layout.fillWidth: true
                    text: model.pointDescription
                    onTextChanged: {
                        model.pointDescription = text;
                    }
                }
            }
        }
        Button {
            id: addButton
//            anchor.right: parent.right
//            anchor.margin: 32
            height: dp(30)
            width: parent.width
            text: "+ Add +"
            elevation: 1
            onClicked: {
                mDescriptor.append();
            }
        }
    }
    positiveButtonText: "OK"
    negativeButtonText: "Cancel"
    onAccepted: {
//        cardRoot.setStatus(8, 10)
        mWorkflow.saveDescription();
        mDescriptor.clearAllData();
        snackbar.open("Data saved");
    }
    onRejected: {
        mDescriptor.clearAllData();
    }
}

