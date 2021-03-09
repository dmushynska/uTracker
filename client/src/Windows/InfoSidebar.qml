import QtQuick 2.15
//import QtQuick.Layouts 1.1
import QtQuick.Controls 2.15
import QtQuick.Controls 1.3 as Controls
import Material 0.3
import Material.ListItems 0.1 as ListItem

import "../Components"

PageSidebar {
        id: sidebarInfo
        title: "Table Info"

        width: dp(320)

        actionBar.maxActionCount: 1

        actions: [
            Action {
                id: addPers
                iconName: "content/add"
                text: "Add colab"
                hoverAnimation: true
                onTriggered: {
                }
            },
            Action {
                id: delPers
                iconName: "action/delete"
                text: "Remove colab"
                hoverAnimation: true
                onTriggered: {
                }
            }
        ]
        data:
            Rectangle {
                anchors.fill: parent
//                color: "#80fad2e0"
                color: "#ebc7d3"

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
//                            radius: 5
                            Rectangle {
                                anchors.fill: parent
                                color: "#80f6a2bf"
//                                border.width: 2
//                                border.color: "#f6a2bf"
//                                radius: parent.radius
                                Text {
                                    anchors.fill: parent
                                    verticalAlignment: Text.AlignVCenter
    //                                horizontalAlignment: Text.AlignHCenter
                                    anchors.leftMargin: dp(15)
                                    color: "#7a163c"
                                    font.pixelSize: dp(24)
                                    text: "Colaborators"
                                    font.bold: true
//                                    font.capitalization: Font.AllUppercase
                                }
                            }
                        }

                        ListView {
                            id: listColab
                            anchors.horizontalCenter: parent.horizontalCenter
    //                        anchors.fill: parent
                            width: parent.width
                            height: parent.height * 0.875

                            spacing: dp(5)
                            flickableDirection: Flickable.VerticalFlick
                            boundsBehavior: Flickable.StopAtBounds
                            model: 15
                            clip: true
                            delegate: UserForms {
//                                anchors.horizontalCenter: listColab.horizontalCenter
                                formContent: "intelek2al"
                                formType: ""
//                                formColor: ""
                                formWidth: listColab.width
                                formHeight: 40
                            }

                        }
                    }
    //                Rectangle {
    //                    height: 2
    //                    color: "#f6a2bf"
    //                    width: parent.width
    //                } //separator
                }
            }
    }
