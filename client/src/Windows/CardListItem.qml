import QtQuick 2.15
import QtQuick.Window 2.11
import QtQuick.Controls 1.3 as Controls
import QtQuick.Controls 2.15
import Material 0.3
import Material.ListItems 0.1 as ListItem
import QtQuick.Layouts 1.3

Item {
    id: cardList

    function createNewCard() {
        layout.model.append("Task " + (layout.model.rowCount() + 1))
        control.position = 1.0
    }

    property int cardListWidth: dp(300)
    property int cardListHeight: dp(1080)
    property string cardListTitle: "Value"
    property alias cardsModel: layout.model
    readonly property alias cardListHeader: header
    property alias cardTitleEditor: name


    width: cardListWidth
    height:cardListHeight

//    function showModelItems(model, layoutItem, delegateItem) {
//        for (var item = 0; item < model.count; item++) {
//            var component;
//            var sprite;
//            component = Qt.createComponent(delegateItem);
//            console.log(model.get(item).text)
//            if (component.status === Component.Ready){
//                sprite = component.createObject(layoutItem, {cardContent: model.get(item).text});
//            }
//        }

//    }

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
        backgroundColor: "#fcd8e4"


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
                    color: "#80f6a2bf"
                    Text {
                        id:cardTitle
                        anchors.fill: parent
                        verticalAlignment: Text.AlignVCenter
                        anchors.leftMargin: dp(15)
                        color: "#7a163c"
                        font.pixelSize: dp(24)
                        text: cardListTitle
                        font.bold: true
                        visible: !name.visible
                    }
//                    Item {
//                        anchors.fill: parent
////                        focus: true
                        TextField {
                            id: name
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.margins: dp(20)
//                            Component.onCompleted: {
//                                name.forceActiveFocus()
//                            }
                            Keys.onEscapePressed: {
                                focus = false
                            }

                            anchors.fill: parent
//                            focus: true
                            color: "#7a163c"
                            onFocusChanged:  {
                                console.log(cardListTitle + ": " + focus)
                                if (text.length > 0)
                                    cardTitle.text = text
                                visible = focus
                            }
//                        }

                        visible: true
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
                                color: !(layout.height < layout.contentHeight) ? "#007a163c" :
                                                         (control.pressed || control.hovered ? "#807a163c" : "#407a163c")
                        }
                    }

                    anchors {
                        left: parent.left;
                        right: parent.right;
                    }
                    delegate: CardItem {
                        id:card
                        cardContent: model.text
                        cardWidth: layout.width
                        cardId: index
                        modelOwner: cardsModel
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
                            color: "transparent"
                            border.color: "#ffffff"
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
                    color: "#80f6a2bf"
                    Button {
                       anchors.fill: parent
                       text: "add card"
                       textColor: "#7a163c"
                       onClicked : createNewCard()
                    }
                }
                elevationInverted: true
            }
        }

    }

}

