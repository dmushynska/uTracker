import QtQuick 2.9
import QtQuick.Window 2.11
import QtQuick.Controls 1.3 as Controls
import Material 0.3
import Material.ListItems 0.1 as ListItem

import UThemes 1.0

Item {
    id: cardRoot

    property int cardId: -1
    property int parentId: -1
    property int status: 1
    property int count: 2
    property string cardContent: "value"
    property int cardWidth: dp(100)
    property int cardHeight: dp(80)
    property QtObject modelOwner

    width: cardWidth
    height: cardHeight

    function setStatus(stat, ct) {
        status = stat;
        count = ct;
    }

    function duplicateCard(name) {
        mWorkflow.appendTask(name, parentId)
        control.position = 1.0
    }

    Card {
        anchors.centerIn: parent
        width: parent.width - dp(20)
        height: parent.height - dp(5)
        backgroundColor: "#fbfaf6"

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
                color: UThemes.font
                font.pixelSize: dp(19)
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                MouseArea {
                    id: renameTaskArea
                    anchors.fill: parent
                    onDoubleClicked: {
                        infoText.visible = false
                        infoTextField.visible = true
                        infoTextField.forceActiveFocus()
                        infoTextField.text = infoText.text
                        infoTextField.selectAll()
                    }
                }
            }
            TextField {
                id: infoTextField
                height: parent.height
                width: lay.width - (menuButton.height + parent.spacing * 2)
                visible: !infoText.visible
                property bool escaped: false

                Component.onCompleted: {
                    focus = false
                    visible = false
                }
                Component.onDestruction: {
                    focus = false
                    visible = false
                }
                Keys.onEscapePressed: {
                    escaped = true
                    focus = false
                    visible = false
                }

                onAccepted: {
                    if (text.length > 0 && !escaped) {
                        snackbar.open("Task \"%1\" was renamed to \"%2\"".arg(infoText.text).arg(text))
                        infoText.text = text;
                        mWorkflow.renameTask(cardId, text);
                    }
                    text = ""
                    escaped = false
//                    focus = false
                    visible = false
                    infoText.visible = true
                }
                onFocusChanged: {
                    if (focus == false)
                        accepted()
                }

            }
            ActionBar {
                id: menuButton
                height: parent.height
                width: parent.height
                menuColor:UThemes.font
                maxActionCount: 1


                actions: [
                    Action {
                        id: details
                        iconName: "image/color_lens"
                        name: "Details.."
                        hoverAnimation: true
                        onTriggered: {
                            mWorkflow.openDescription(cardId);
                        }
                    },
                    Action {
                        id: delPers
                        iconName: "action/delete"
                        name: "Remove"
                        hoverAnimation: true
                        onTriggered: {
                            snackbar.open("Task \"%1\" was successfuly deleted.".arg(cardContent))
                            mWorkflow.removeTask(cardId)
                        }
                    },
                    Action {
                        id: renamePers
                        iconName: "image/edit"
                        name: "Rename"
                        hoverAnimation: true
                        onTriggered: {
                            infoText.visible = false
                            infoTextField.visible = true
                            infoTextField.forceActiveFocus()
                        }
                    },
                    Action {
                        id: duplicate
                        iconName: "action/copy_link"
                        name: "Duplicate"
                        hoverAnimation: true
                        onTriggered: duplicateCard(cardContent)
                    },
                    Action {
                        id: movePers
                        iconName: "content/forward"
                        name: "Move to list.."
                        hoverAnimation: true
                        onTriggered: {
                            var componentMove;
                            var spriteMove;
                            mWorkflow.moveSetCardId(cardId);
                            mWorkflow.moveSetCurrListId(parentId);
                            componentMove = Qt.createComponent("MoveToDialog.qml");
                            if (componentMove.status === Component.Ready){
                                spriteMove = componentMove.createObject(cardRoot);
                            }

                            spriteMove.show()
                        }
                    }
                ]
            }
        }
        ProgressBar {
            width: parent.width
            color: value == 1 ? UThemes.progress : UThemes.inputBorder
            value: count <= 0 ? 0 : status / count;
            Behavior on value {
                NumberAnimation {
                    duration: 500
                    easing.type: Easing.InOutQuad
                }
            }
            Behavior on color {
                ColorAnimation {
                    duration: 200
                }
            }
            
        }
    }
}
