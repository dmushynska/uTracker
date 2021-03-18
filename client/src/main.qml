import QtQuick 2.9
import QtQuick.Window 2.11
import QtQuick.Controls 1.3 as Controls
import Material 0.3
import Material.ListItems 0.1 as ListItem

//import Themes.qml

import "Components"
import "Windows"
import UThemes 1.0

ApplicationWindow {
    id:root

    minimumWidth: 1000
    minimumHeight: 680
    title: qsTr("uTracker")



    theme {
//        primaryColor: Qt.rgba(0.5,0.5,0.56, 1)
        primaryColor: UThemes.primary
        accentColor: UThemes.accent
        tabHighlightColor: "white"

    }

    visible: true
    width: 1920
    height: 1080
    clientSideDecorations: false
    initialPage: SignIn {}
   // initialPage: MainAccountWindow {}

    Snackbar {
        id: snackbar
    }

    function goMainWindow() {
//        showError("Titile", "Text", "Hide", "2000")
        console.log("MainAccountWindow")
        pageStack.replace(Qt.resolvedUrl("Windows/MainAccountWindow.qml"))
//        mWorkflow.getAllListWorkflow()
    }

}

//Loader {
//        anchors.fill: parent
//        asynchronous: true
//        visible: status == Loader.Ready
//    }
//    ProgressCircle {
//        anchors.centerIn: parent
//        visible: example.status === Loader.Loading
//    }



//        borderColor: "#f6a2bf"
