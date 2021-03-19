import QtQuick 2.15
import QtQuick.Window 2.11
import QtQuick.Controls 1.3 as Controls
import QtQuick.Controls 2.15
import Material 0.3
import Material.ListItems 0.1 as ListItem
import QtQuick.Layouts 1.3

import UThemes 1.0

Page {
    function showNav () {
        navDrawer.open()
    }

    function removeWorkflow(id) {
        mWorkflow.removeWorkflow(id)
    }

    Dialog {
        id: nameingWorkflow
        title: "Input title"
        hasActions: true

        TextField {
            id: optionText
            width: parent.width
            placeholderText: "Title"
            onAccepted: nameingWorkflow.positiveButton.clicked();
        }

        onAccepted: {
            if (optionText.text !== "") {
                createNewDesk(optionText.text)
                snackbar.open("Workflow \"%1\" created".arg(optionText.text))
                optionText.text = ""
            }
        }
    }

    function createNewDesk(title) {
        mWorkflow.createWorkflow(title)
        control.position = 1.0
    }

    Connections {
        target: mWorkflow
        onGotTaskData: {
            var component;
            var sprite;
            component = Qt.createComponent("CardView.qml");
            if (component.status === Component.Ready){
                sprite = component.createObject(parent);
            }
            sprite.show()
        }
    }

    ListModel {
        id: userSection
        ListElement {
            titleWorkflow: "Profile"
            idWorkflow: 0
        }
    }
    property var sections: [userSection, mWorkflowList]
    property var sectionsTitles: ["User information", "Desks"]
    property int selectedComponent: 0

    id: rootAccount
    visible: true
    width: dp(1920)
    height: dp(1080)

    title: "uTracker"

    backgroundColor: UThemes.backBack

    actionBar.decorationColor:"#7a163c"
    actions: [
        Action {
            id: info
            iconName: "action/account_circle"
            text: "Info"
            hoverAnimation: false
            onTriggered: {
                sidebarInfo.showing = !sidebarInfo.showing
            }
        }
    ]


    rightSidebar: InfoSidebar {
        id: sidebarInfo
        showing: false
    }
    backAction: navDrawer.action
    NavigationDrawer {
        id: navDrawer

        enabled: true
        viewer.backgroundColor: "#fbfaf6"

        tooltip: "Menu"


        overlayColor: UThemes.overlay

        onEnabledChanged: smallLoader.active = enabled

        Flickable {
            anchors.fill: parent

            contentHeight: Math.max(content.implicitHeight, height)

            Column {
                id: content
                anchors.fill: parent

                Repeater {
                    model: sections

                    delegate: Column {
                        width: parent.width

                        ListItem.Subheader {
                            text: sectionsTitles[index]
                            textColor: UThemes.isClassic ? "white" : UThemes.font
                            backgroundColor: UThemes.listBack
                            elevation: 2
                        }

                        ListView {
                            id: sectionItems

                            width: parent.width
                            clip: true
                            property bool isContentHeight: contentHeight < (rootAccount.height - (userSection.count  + 3) * dp(48) - dp(200))
                            height: isContentHeight ? contentHeight
                                    : (rootAccount.height - (userSection.count  + 3) * dp(48) - dp(200))
                            model: sections[index]
                            interactive: false
                            flickableDirection: Flickable.VerticalFlick
                            boundsBehavior: Flickable.StopAtBounds
                            ScrollBar.vertical: ScrollBar{
                                property real globalPos: control.position * sectionItems.contentHeight
                                id: control
                                hoverEnabled: true
                                active: sectionItems.height < sectionItems.contentHeight && (hovered || pressed)
                                size: 0.3
                                contentItem: Rectangle {
                                        implicitWidth: 3
                                        implicitHeight: 100
                                        radius: width / 2
                                        color: !(sectionItems.height < sectionItems.contentHeight) ? "#00000000" :
                                                                 (control.pressed || control.hovered ? UThemes.sliderMainHover : UThemes.sliderMain)
                                }
                            }
                            Behavior on height {
                                NumberAnimation {
                                    duration: 200
                                }
                            }

                            delegate: ListItem.Standard {
                                id: itemList
                                text: model.titleWorkflow
                                selected: model.idWorkflow === selectedComponent

                                secondaryItem: IconButton {
                                    id: buttonIcon
                                    visible: model.idWorkflow !== 0
                                    color: itemList.hovered || hover ? "red" : "#00000000"

                                    anchors.centerIn: parent
                                    iconName: "navigation/close"
                                    hoverAnimation: true
                                    size: dp(15)
                                    Behavior on color {
                                        ColorAnimation {
                                            duration: 200
                                        }
                                    }
                                    onClicked: {
                                        if (selectedComponent === model.idWorkflow)
                                            selectedComponent = 0
                                        removeWorkflow(model.idWorkflow)
                                    }
                                }
                                onClicked: {
                                    selectedComponent = model.idWorkflow;
                                    mWorkflow.getWorkflowsModelById(selectedComponent)
                                    navDrawer.close()
                                }
                            }
                        }
                    }
                }
                Button {
                    text: "New desk +"
                    elevation: 1
                    height: dp(40)
                    width: parent.width
                    onClicked: nameingWorkflow.show();
                    backgroundColor: UThemes.listBack
                    textColor: UThemes.isClassic ? "white" : UThemes.font
                }
            }
        }
        Rectangle {
            id: switcher
            color: UThemes.primary
            height: dp(40)
            width: parent.width
            anchors.bottom: parent.bottom
            Row {
                anchors.fill: parent
                Item {
                    height: switcher.height
                    width: parent.width / 3
                    Label {
                        anchors.centerIn: parent
                        text: "Classic"
                        style: "body2"
                        color: UThemes.font_

                    }
                }
                Item {
                    height: switcher.height
                    width: parent.width / 3
                    Switch {
                        anchors.centerIn: parent
                        checked: !UThemes.isClassic
                        darkBackground: false
                        onClicked: UThemes.changeTheme()
                        color: UThemes.font
                    }
                }
                Item {
                    height: switcher.height
                    width: parent.width / 3
                    Label {
                        anchors.centerIn: parent
                        text: "Pink"
                        style: "body2"
                        color: UThemes.font_

                    }
                }
            }
            Behavior on color {
                ColorAnimation {
                    duration: 200
                }
            }
        }
    }

    Item {
        anchors.fill: parent
        Flickable {
            id: flickable
            anchors.fill: parent
            clip: true
            contentHeight: Math.max(example.implicitHeight + 40, height)
            Loader {
                id: example
                anchors.fill: parent
                asynchronous: true
                visible: status == Loader.Ready
                source: {
                    if(selectedComponent == 0)
                        return Qt.resolvedUrl("Profile.qml")
                    else
                        return Qt.resolvedUrl("DeskItem.qml")
                }
            }

            ProgressCircle {
                anchors.centerIn: parent
                visible: example.status == Loader.Loading
            }
        }
        Scrollbar {
            flickableItem: flickable
        }
    }



    Snackbar {
        id: snackbar
    }
}
