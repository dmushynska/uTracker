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


    Card {
        id: cardBack
        width: parent.width
        height: (layout.contentHeight + dp(104)) < parent.height ? (layout.contentHeight + dp(104)) : parent.height
        backgroundColor: UThemes.listBack
        Behavior on height {
            NumberAnimation {
                duration: 100
            }
        }


        Column {
            spacing: dp(7)
            id: listGroup
            anchors.fill: parent
            View {
                id: header
                width: parent.width
                height: dp(70)
                elevation: 2
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
                            MouseArea {
                                id: renameList
                                anchors.fill: parent
                                onDoubleClicked: {
                                    cardTitle.visible = false
                                    name.visible = true
                                    name.forceActiveFocus()
                                }
                            }
                        }
                        Item {
                            height: parent.height
                            width: parent.width - parent.height - dp(20)
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
                            maxActionCount: 1
                            actions: [
                                Action {
                                    id: delPers
                                    iconName: "action/delete"
                                    name: "Remove list"
                                    hoverAnimation: true
                                    onTriggered: {
                                        mWorkflow.removeList(listId)
                                    }
                                },
                                Action {
                                    id: renamePers
                                    iconName: "image/edit"
                                    name: "Rename list"
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
                    clip: true
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
                                                         (control.pressed || control.hovered ? UThemes.sliderHover : UThemes.slider)
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
                        status: statusD
                        count: countD
                        Connections {                               // !
                            target: cardsModel                      // !
                            onTaskAppended: {                       // !
                                control.position = 1.0;             // !
                            }                                       // !
                        }                                           // !

                        states: [
                            State {
                                name: "inDrag"
                                when: index == layout.draggedItemIndex
                                PropertyChanges { target: border; opacity: 1 }
                                PropertyChanges { target: card; parent: dndContainer }
                                PropertyChanges { target: card; anchors.centerIn: undefined }
                                PropertyChanges { target: card; y: coords.mouseY - card.height / 2 }
                            }
                        ]
                        Rectangle {
                            id: border
                            anchors.fill: parent
                            radius: 5
                            color: "#fbfaf6"
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
                }

            }


            View {

                width: parent.width
                height: dp(20)
                elevation: 2
                z:1
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

