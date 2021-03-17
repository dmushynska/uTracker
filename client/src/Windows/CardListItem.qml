import QtQuick 2.15
import QtQuick.Window 2.11
import QtQuick.Controls 1.3 as Controls
import QtQuick.Controls 2.15
import Material 0.3
import Material.ListItems 0.1 as ListItem
import QtQuick.Layouts 1.3

import UThemes 1.0

Item {
    id: cardList

    function createNewCard() {
        console.debug("{{{DEBUGGGG}}} ListId -> " + (layout.model.parentId()))
        if (layout.model.parentId() > -1)
            mWorkflow.appendTask("Task " + (layout.model.rowCount() + 1), layout.model.parentId())
        control.position = 1.0
    }

    property int cardListWidth: dp(300)
    property int cardListHeight: dp(1080)
    property string cardListTitle: "Value"
    property alias cardsModel: layout.model
    readonly property alias cardListHeader: header
    property alias cardTitleEditor: name
    property int listId: -1



    width: cardListWidth
    height:cardListHeight


    ListModel {
        id: cardModel
        ListElement {
            text: "Task1"
        }
//        ListElement {
//            text: "Task2"
//        }
//        ListElement {
//            text: "Task3"
//        }
//        ListElement {
//            text: "Task4"
//        }
//        ListElement {
//            text: "Task5"
//        }
//        ListElement {
//            text: "Task6"
//        }
//        ListElement {
//            text: "Task7"
//        }
//        ListElement {
//            text: "Task8"
//        }
//        ListElement {
//            text: "Task9"
//        }
//        ListElement {
//            text: "Task10"
//        }
//        ListElement {
//            text: "Task11"
//        }
//        ListElement {
//            text: "Task12"
//        }
//        ListElement {
//            text: "Task13"
//        }
//        ListElement {
//            text: "Task14"
//        }
//        ListElement {
//            text: "Task15"
//        }

    }

    Card {
        id: cardBack
        width: parent.width
        height: (layout.contentHeight + dp(104)) < parent.height ? (layout.contentHeight + dp(104)) : parent.height
//        anchors.fill: pa  rent
//        backgroundColor: Palette.colors["pink"]["50"]
        backgroundColor: UThemes.listBack


        Column {
            spacing: dp(7)
            id: listGroup
            anchors.fill: parent
            View {
                id: header
                width: parent.width
                height: dp(70)
                elevation: 2
                z:1
//                            radius: 5
                Rectangle {
                    anchors.fill: parent
                    color: UThemes.headerBack
                    Row {
                        anchors.fill: parent

                        anchors.leftMargin: dp(15)
                        anchors.topMargin: dp(15)
                        anchors.bottomMargin: dp(15)
                        Text {
                            id:cardTitle
                            height: parent.height
                            width: parent.width - parent.height
                            verticalAlignment: Text.AlignVCenter
                            anchors.leftMargin: dp(15)
                            color: UThemes.isClassic ? "white" : UThemes.font
                            font.pixelSize: dp(24)
                            text: cardListTitle
                            font.bold: true
        //                        visible: !name.visible
                            MouseArea {
                                id: renameList
                                anchors.fill: parent
                                onDoubleClicked: {
                                    console.log("Renaming List")
                                    cardTitle.visible = false
                                    name.visible = true
                                    name.forceActiveFocus()
                                }
                            }
                        }
                        Item {
                            height: parent.height
                            width: parent.width - parent.height - dp(20)
//                            width: parent.implicitWidth
                            TextField {
                                id: name
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.horizontalCenter: parent.horizontalCenter
                                Component.onCompleted: {
                                    focus = false
                                    visible = false
                                }
                                Component.onDestruction: {
                                    focus = false
                                    visible = false
                                }

                                Keys.onEscapePressed: {
                                    focus = false
                                    visible = false
                                }

                                anchors.fill: parent
                                color: "#7a163c"
                                onAccepted: {
                                    if (text.length > 0) {
                                        cardTitle.text = text
                                        mWorkflow.renameList(listId, text);
                                    }
                                    focus = false
                                    visible = false
                                    cardTitle.visible = true
                                }

                                onFocusChanged:  {
                                    if(focus == false)
                                        accepted();
                                }
                            }
                        }
                        ActionBar {
                            id: menuListButton
                            height: parent.height
                            width: parent.height
                            anchors.verticalCenter: parent.verticalCenter
            //                onClicked: snackbar.open("That button is colored!")
                            maxActionCount: 1
            //                backgroundColor: "pink"
                            actions: [
                                Action {
                                    id: delPers
                                    iconName: "action/delete"
                                    text: "Remove list"
                                    hoverAnimation: true
                                    onTriggered: {
                                        mWorkflow.removeList(listId)
                                    }
                                },
                                Action {
                                    id: renamePers
                                    iconName: "image/edit"
                                    text: "Rename list"
                                    hoverAnimation: true
                                    onTriggered: {
                                        cardTitle.visible = false
                                        name.visible = true
                                        name.forceActiveFocus()
                                    }
                                }
                            ]
                        }
                    }
                }
            }
            Item {
                height: cardBack.height - dp(104)
                width: parent.width

                ListView {
                    id:layout
                    width: parent.width
                    height: parent.height
                    model:mCardModel
                    flickableDirection: Flickable.VerticalFlick
                    boundsBehavior: Flickable.StopAtBounds
                    ScrollBar.vertical: ScrollBar{
                        property real globalPos: control.position * layout.contentHeight
                        id: control
                        hoverEnabled: true
                        active: layout.height < layout.contentHeight && (hovered || pressed)
                        size: 0.3
                        contentItem: Rectangle {
                                implicitWidth: 3
                                implicitHeight: 100
                                radius: width / 2
                                color: !(layout.height < layout.contentHeight) ? "#005a585c" :
                                                         (control.pressed || control.hovered ? "#5a585c" : "#805a585c")
                        }
                    }

                    anchors {
                        left: parent.left;
                        right: parent.right;
                    }
                    delegate: CardItem {
                        id:card
                        cardContent: textCard
                        cardWidth: layout.width
                        cardId: idCard
                        parentId: idParent
                        modelOwner: cardsModel
                        Connections {                               // !
                            target: cardsModel                      // !
                            onTaskAppended: {                       // !
                                control.position = 1.0;             // !
                                console.log("{}{}{}{}{} Peremoga {}{}{}{}")
                            }                                       // !
                        }                                           // !

                        states: [
                            State {
                                name: "inDrag"
                                when: index == layout.draggedItemIndex
                                PropertyChanges { target: border; opacity: 1 }
                                PropertyChanges { target: card; parent: dndContainer }
                                PropertyChanges { target: card; anchors.centerIn: undefined }
//                                PropertyChanges { target: card; x: coords.mouseX - card.width / 2 }
                                PropertyChanges { target: card; y: coords.mouseY - card.height / 2 }
                            }
                        ]
                        Rectangle {
                            id: border
                            anchors.fill: parent
                            radius: 5
//                            color: "transparent"
                            color: "#fbfaf6"
//                            border.color: "#ffffff"
                            border.width: 6
                            opacity: 0
                        }
                    }
                    property int draggedItemIndex: -1
                    interactive: false
                    Item {
                        id: dndContainer
                        anchors.fill: parent
                    }



//                    MouseArea {
//                        id: coords
//                        height: parent.height
//                        width: layout.width - dp(80)
////                        pressAndHoldInterval: 200
//                        property int pressedX: 0
//                        property int pressedY: 0
//                        property bool isHeld: false

//                        onReleased: {
//                            if (layout.draggedItemIndex !== -1) {
//                                var draggedIndex = layout.draggedItemIndex
//                                layout.draggedItemIndex = -1
//                                cardModel.move(draggedIndex,layout.indexAt(mouseX, mouseY + control.globalPos), 1)
//                                isHeld = false
//                            }
//                        }
////                        onClicked: {
////                            if (!isHeld) {
////                                var cardIndex = layout.indexAt(mouseX, mouseY + control.globalPos)
////                                var cardItem = cardModel.get(index)
////                                console.log("Request to server: Id of card: " + cardItem.cardId)

////                                // Waiting for response

////                                var component;
////                                var sprite;
////                                component = Qt.createComponent("CardView.qml");
////                                if (component.status === Component.Ready){
////                                    sprite = component.createObject(cardItem, {text: "info:" + cardId});
////                                }
////                            }
////                        }

//                        onPressed: {
//                            pressedX = mouseX
//                            pressedY = mouseY
//                        }
//                        onPositionChanged: {
//                            if (pressed && Math.abs(mouseY - pressedY) > dp(20) && !isHeld) {
//                                isHeld = true
//                                layout.draggedItemIndex = layout.indexAt(mouseX, mouseY + control.globalPos)
//                            }
//                            console.log("dragged: " + layout.draggedItemIndex)
//                            console.log("layout: " + layout.indexAt(mouseX, mouseY + control.globalPos))
////                            if (pressed && isHeld && layout.draggedItemIndex !== -1 && layout.draggedItemIndex !== layout.indexAt(mouseX, mouseY + control.globalPos)) {
////                                var draggedIndex = layout.draggedItemIndex
////                                layout.draggedItemIndex = layout.indexAt(mouseX, mouseY + control.globalPos)
////                                cardModel.move(draggedIndex, layout.indexAt(mouseX, mouseY + control.globalPos), 1)
////                            }
//                        }

//                    }
                }

            }


            View {

                width: parent.width
                height: dp(20)
                elevation: 2
                z:1
//                            radius: 5
                Rectangle {
                    anchors.fill: parent
                    color: UThemes.addTask
                    Button {
                       anchors.fill: parent
                       text: "add card"
                       textColor: UThemes.addTaskFont
                       onClicked : createNewCard()
                    }
                }
                elevationInverted: true
            }
        }

    }

}

