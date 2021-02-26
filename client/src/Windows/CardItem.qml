import QtQuick 2.9
import QtQuick.Window 2.11
import QtQuick.Controls 1.3 as Controls
import Material 0.3
import Material.ListItems 0.1 as ListItem

Item {
    id: card

    property int cardId: -1
    property int parentId: -1
    property string cardContent: "value"
    property int cardWidth: dp(100)
    property int cardHeight: dp(80)
    property QtObject modelOwner

    width: cardWidth
    height: cardHeight
    Card {
        anchors.centerIn: parent
        width: parent.width - dp(20)
        height: parent.height - dp(5)
        backgroundColor: "#fde8f5"
        Row {
            id:lay
            anchors.fill: parent
            anchors.margins: dp(20)
            spacing: dp(10)
            Text {
                id: infoText
                text: cardContent
                height: parent.height
                width: cardWidth - (menuButton.width - parent.spacing / 2)
                color: "#7a163c"
                font.pixelSize: dp(19)
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                visible: false
            }
            TextField {
                id: infoTextField
                height: parent.height
                width: lay.width - (menuButton.height + parent.spacing * 2)
                visible: !infoText.visible
                onAccepted: {
                    infoText.text = text;
                    focus = false
                    infoText.visible = true
                }

            }

            ActionBar {
                id: menuButton
                height: parent.height
                width: parent.height
//                onClicked: snackbar.open("That button is colored!")
                maxActionCount: 1
//                backgroundColor: "pink"

                actions: [
                    Action {
                        id: addPers
                        iconName: "navigation/chevron_right"
                        text: "Details.."
                        hoverAnimation: true
                        onTriggered: {
//                            var cardIndex = layout.indexAt(mouseX, mouseY + control.globalPos)
//                            var cardItem = cardModel.get(index)
                            console.log("Request to server: Id of card: " + cardId)

                            // Waiting for response

                            var component;
                            var sprite;
                            component = Qt.createComponent("CardView.qml");
                            if (component.status === Component.Ready){
                                sprite = component.createObject(card, {text: "info:" + cardId});
                            }
                            sprite.show()
                        }
                    },
                    Action {
                        id: delPers
                        iconName: "navigation/chevron_right"
                        text: "Remove"
                        hoverAnimation: true
                        onTriggered: {
                            mWorkflow.removeRequest(cardId)
                        }
                    },
                    Action {
                        id: renamePers
                        iconName: "navigation/chevron_right"
                        text: "Rename"
                        hoverAnimation: true
                        onTriggered: {
                            infoText.visible = false
                            infoTextField.forceActiveFocus();
                            infoTextField.focus = true
                        }
                    },
                    Action {
                        id: movePers
                        iconName: "navigation/chevron_right"
                        text: "Move to list.."
                        hoverAnimation: true
                        onTriggered: {
//                            var cardIndex = layout.indexAt(mouseX, mouseY + control.globalPos)
//                            var cardItem = cardModel.get(index)
                            console.log("$$$$$$$$$$$$$$$$$$$$ Request to server: Id of card: " + cardId + " LISTSSST " + parentId)
                            var componentMove;
                            var spriteMove;
                            mWorkflow.moveSetCardId(cardId);
                            mWorkflow.moveSetCurrListId(parentId);
                            componentMove = Qt.createComponent("MoveToDialog.qml");
                            if (componentMove.status === Component.Ready){
                                spriteMove = componentMove.createObject(card);
                                console.log("Request to server: Id of card: " + componentMove)
                            }

                            spriteMove.show()
                        }
                    }
                ]
            }
        }
    }
}
