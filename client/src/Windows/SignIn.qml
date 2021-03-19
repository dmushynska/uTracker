import QtQuick 2.9
import QtGraphicalEffects 1.15
import QtQuick.Window 2.11
import QtQuick.Controls 1.3 as Controls
import Material 0.3
import Material.ListItems 0.1 as ListItem

import UThemes 1.0

import "../Components"

Page {
    Connections {
        target: mAuthor
        onConnectionRefused: {
            connRef.visible = true
            signUp.buttonEnabled = false
            signIn.buttonEnabled = false
        }
    }

    function checkValid () {
        var ident = inputNickname.inputText
        var password = inputPassword.inputText
        mAuthor.signInHandler(ident, password);
    }
    Connections {
        target: mAuthor
        onServerResponseSignIn: {
            if (!valid) {
                snackbar.open("Wrong login or password");
            } else {
                root.goMainWindow();
            }
        }
    }

    function toSignUpPage () {
        pageStack.push(Qt.resolvedUrl("SignUp.qml"))
    }
    LinearGradient {
            anchors.fill: parent
            start: Qt.point(0, 0)
            end: Qt.point(parent.width, 0)
            gradient: Gradient {
                GradientStop { position: 0.0; color: UThemes.gradienter }
                GradientStop { position: 0.5; color: "white" }
                GradientStop { position: 1.0; color: UThemes.gradienter }
            }
    }

    anchors.fill: parent
    Column {
        spacing: dp(20)
        anchors.centerIn: parent
        Label {
            id: lable
            text: "uTracker"
            color: UThemes.font
            font.bold: true
            font.pixelSize: 100 * Units.dp
        }
        S_Input_1 {
            id: inputNickname
            placeholderContent: "Login or email"
            inputWidth: lable.width
            input.onAccepted: inputPassword.input.forceActiveFocus()
        }
        S_Input_1 {
            id: inputPassword
            placeholderContent: "Password"
            inputWidth: lable.width
            input.echoMode: TextInput.Password
            input.onAccepted: signIn.clicked()
        }
        Column {
            spacing: dp(10)
            Item {
                id: signButtons
                height: 40 * Units.dp
                width: inputPassword.width
                Row {

                    anchors.fill: parent
                    spacing: dp(20)
                    S_Button_1 {
                        id:signIn
                        buttonContent: "Sign In"
                        width: (parent.width - dp(20)) / 2
                        Component.onCompleted: {
                            signIn.clicked.connect(checkValid);
                        }
                    }
                    S_Button_1 {
                        id:signUp
                        buttonType: "Type2"
                        buttonContent: "Sign Up"
                        width: (parent.width - dp(20)) / 2
                        Component.onCompleted: {
                            signUp.clicked.connect(toSignUpPage);
                        }
                    }
                }
            }
            S_Button_1 {
                id:signInGoogle
                buttonContent: "Switch Theme"
                width: parent.width
                onClicked: {
                    UThemes.changeTheme()
                }
            }
            Label {
                id: connRef
                text: "Connection Refused"
                visible: false
                style: "body2"
                color: UThemes.font
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

    }
}
