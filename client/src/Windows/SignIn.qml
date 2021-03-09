import QtQuick 2.9
import QtGraphicalEffects 1.15
import QtQuick.Window 2.11
import QtQuick.Controls 1.3 as Controls
import Material 0.3
import Material.ListItems 0.1 as ListItem
//import Authorization 1.0

import "../Components"

Page {
//    Authorization {
//        id:author
//    }

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
        console.log("SignUp")
        pageStack.push(Qt.resolvedUrl("SignUp.qml"))
    }
//    Rectangle {
//        z: -1
//        anchors.fill: parent


//    }
    LinearGradient {
            anchors.fill: parent
            start: Qt.point(0, 0)
            end: Qt.point(parent.width, 0)
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#dab6c2" }
                GradientStop { position: 0.5; color: "white" }
                GradientStop { position: 1.0; color: "#dab6c2" }
            }
    }

    anchors.fill: parent
    Column {
        spacing: dp(20)
        anchors.centerIn: parent
        Label {
            id: lable
            text: "uTracker"
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
                buttonContent: "Continue with Google"
                width: parent.width
                Component.onCompleted: {
//                    signIn.clicked.connect(signUpRequest);
                }
            }
        }

    }
}
