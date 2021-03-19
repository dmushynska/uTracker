import QtQuick 2.9
import QtQuick.Window 2.11
import QtQuick.Controls 1.3 as Controls
import Material 0.3
import Material.ListItems 0.1 as ListItem

import "Components"
import "Windows"
import UThemes 1.0

ApplicationWindow {
    id:root

    minimumWidth: 1000
    minimumHeight: 680
    title: qsTr("uTracker")
    theme {
        primaryColor: UThemes.primary
        accentColor: UThemes.accent
        tabHighlightColor: "white"

    }
    visible: true
    width: 1920
    height: 1080
    clientSideDecorations: false
    initialPage: SignIn {}

    Snackbar {
        id: snackbar
    }

    function goMainWindow() {
        pageStack.replace(Qt.resolvedUrl("Windows/MainAccountWindow.qml"))
    }

}
