import QtQuick 2.9
import QtQuick.Window 2.11
import QtQuick.Controls 1.3 as Controls
import QtQuick.Controls 2.15
import Material 0.3
import Material.ListItems 0.1 as ListItem
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

//    height:
//    ListModel {
//        id: model
//        ListElement {
//            text: "Plan"
////            tasks: ["Task1", "Task2"]
//        }
//        ListElement {
//            text: "Prccess"
////            tasks: ["Task3", "Task4"]
//        }
//        ListElement {
//            text: "Done"
////            tasks: ["Task5"]
//        }
//    }



//                                                                      add variable isEdit



Item {
    property alias listModel: deskListView.model
    function createNewList () {
        mWorkflow.appendLists("List " + (listModel.rowCount() + 1))
//        listModel.append({titleD: "List " + (listModel.rowCount() + 1)})

        control.position = 1.0
    }

//    Connections {
//        target: mWorkflow
//        onServerSingleWorkflowResponse: {
//            if (!valid) {
//                snackbar.open("Wrong login or password");
//            } else {
//                root.goMainWindow();
//            }
//        }
//    }

    ListModel {
        id: deskModel
        ListElement {
            titleD: "List 1"
        }
    }

    id: deskItem
    property int listWidgth: dp(300)


    width: listWidgth
    Card {
        id: mainForm
        anchors.centerIn: parent
        width: parent.width - dp(20)
        height: parent.height - dp(20)
//        backgroundColor: Palette.colors["purple"]["50"]
        backgroundColor: "#f5f2f1"
        Row{
            id: layout
            width: parent.width - dp(20)
            height: parent.height - dp(20)
            anchors.centerIn: parent
            spacing: deskListView.spacing
            ListView {
                id: deskListView
                width: contentWidth < parent.width - (barier.width + deskListView.spacing)
                       ? contentWidth : parent.width - (barier.width + deskListView.spacing)
                height: parent.height - dp(20)
                spacing: dp(20)
                clip: true
                orientation: Qt.Horizontal
                flickableDirection: Flickable.HorizontalFlick
                boundsBehavior: Flickable.StopAtBounds
//                anchors {
//                    top: parent.top
//                    left: parent.left
//                    margins: dp(10)
//                }
                interactive: false
                model: mCardListsModel

                ScrollBar.horizontal: ScrollBar{
                    property real globalPos: control.position * deskListView.contentWidth
                    id: control
                    hoverEnabled: true
                    active: deskListView.contentWidth < layout.width - (barier.width + deskListView.spacing) && (hovered || pressed)
                    size: 0.3
                    contentItem: Rectangle {
                        implicitWidth: 3
                        implicitHeight: 50
                        radius: width / 2
                        color: !(deskListView.width < deskListView.contentWidth) ? "#007a163c" :
                                                 (control.pressed || control.hovered ? "#805a585c" : "#405a585c")
                    }
                }

                delegate: CardListItem {
                    id: cardList
                    cardsModel: modelD
                    cardListHeight: deskListView.height - dp(70)
                    cardListTitle: titleD
                    listId: idD
//                    cardTitleEditor.onAccepted:  {
//                        if(index == (mCardListsModel.rowCount() - 1)) {
//                            buttonAddList.clicked()
//                        }
//                    }
                    states: [
                    State {
                            name: "inDrag"
                            when: index === deskListView.draggedItemIndex
                            PropertyChanges { target: cardList; parent: dndContainer }
                            PropertyChanges { target: cardList; anchors.centerIn: undefined }
//                            PropertyChanges { target: cardList; x: coords.mouseX - dp(150)}
//                            PropertyChanges { target: cardList; y: coords.mouseY - dp(35)}
                        }
                    ]
                }
                property int draggedItemIndex: -1
                property int draggedMousePos: {x: 0; y: 0}

                Item {
                    id: dndContainer
                    anchors.fill: parent
                }

            }
            View {
                id:barier
                height: parent.height
                width: dp(300)
                backgroundColor: mainForm.backgroundColor

                Button {
                    id: buttonAddList
                    height: dp(70)
                    text: "Add"
                    width: parent.width - dp(20)
                    anchors.horizontalCenter: parent.horizontalCenter
                    elevation: 1
                    onClicked: {snackbar.open("Added new List"); createNewList()}
                    backgroundColor: "#5a585c"
                    textColor: "white"
                }

                Rectangle {
                    anchors.left: parent.left
                    height: parent.height
                    width: deskListView.contentWidth < barier.parent.width - (barier.width + deskListView.spacing)
                           ? 0 : 1
                    color: "grey"
                }
            }
        }
//        MouseArea {
//            id: coords
//            anchors {
//                top:parent.top
//                left: parent.left
//            }
//            width: deskListView.width
//            height: dp(70)
//            acceptedButtons: Qt.LeftButton | Qt.RightButton

//            onReleased: {
//                if (mouse.button === Qt.RightButton)
//                    return
//                if (deskListView.draggedItemIndex !== -1) {
//                    var draggedIndex = deskListView.draggedItemIndex
//                    deskListView.draggedItemIndex = -1
//                    mCardListsModel.move(draggedIndex,deskListView.indexAt(mouseX + control.globalPos, mouseY),1)
//                }
//            }

//            onPressed: {
//                if (mouse.button === Qt.RightButton)
//                    return
//                deskListView.draggedItemIndex = deskListView.indexAt(mouseX + control.globalPos, mouseY)
//                console.log("Pressed " + deskListView.draggedItemIndex)
//            }
//        }

    }
}



