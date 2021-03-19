import QtQuick 2.15
//import QtQuick.Layouts 1.1
import QtQuick.Controls 2.15
import QtQuick.Controls 1.3 as Controls
import Material 0.3
import Material.ListItems 0.1 as ListItem

import UThemes 1.0

import "../Components"

PageSidebar {
        id: sidebarInfo
        title: "Table Info"

        width: dp(320)

        actionBar.maxActionCount: 1

        Dialog {
            id: inviteDialog
            title: "Invite collaborator"
            hasActions: true

            TextField {
                id: optionText
                width: parent.width
                placeholderText: "Login"
            }

            onAccepted: {
                if (optionText.text !== "") {
                    snackbar.open("Invite was sent to %1".arg(optionText.text))
                    optionText.text = ""
                }
            }
        }

        actions: [
            Action {
                id: addPers
                iconName: "content/add"
                name: "Invite"
                hoverAnimation: true
                onTriggered: {
                    inviteDialog.show()
                }
            },
            Action {
                id: delPers
                iconName: "action/delete"
                name: "Remove collaborator"
                hoverAnimation: true
                onTriggered: {
                }
            }
        ]
        data:
            Rectangle {
                anchors.fill: parent
                color: UThemes.infoBack

                Column {
                    anchors.fill: parent
                    spacing: 0
                    Column {
                        spacing: 7
                        id: colabComp
                        width: parent.width
                        height: (parent.height) / 2
                        View {
                            width: parent.width
                            height: parent.height / 8
                            elevation: 1
                            Rectangle {
                                anchors.fill: parent
                                color: UThemes.infoHeader
                                Text {
                                    anchors.fill: parent
                                    verticalAlignment: Text.AlignVCenter
                                    anchors.leftMargin: dp(15)
                                    color: UThemes.infoHeaderFont
                                    font.pixelSize: dp(24)
                                    text: "Collaborators"
                                    font.bold: true
                                }
                            }
                        }

                        ListView {
                            id: listColab
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: parent.width
                            height: parent.height * 0.875

                            spacing: dp(5)
                            flickableDirection: Flickable.VerticalFlick
                            boundsBehavior: Flickable.StopAtBounds
                            model: 1
                            clip: true

                            delegate: UserForms {
                                formContent: mUser.userLogin
                                formType: ""
                                formWidth: listColab.width
                                formHeight: 40
                            }

                        }
                    }
                }
            }
    }
