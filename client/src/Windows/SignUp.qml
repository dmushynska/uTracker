import QtQuick 2.4
import QtGraphicalEffects 1.15
import QtQuick.Controls.Material 2.3
import Material 0.3
import Material.ListItems 0.1 as ListItem
import Authorization 1.0

import "../Components"



Page {
    id: signUpPage
    function signUpRequest () {
        console.log("requested " + mAuthor.LOGIN_EX)
        var login = inputLogin.inputText
        var mail = inputEmail.inputText
        var password = inputPassword.inputText
        mAuthor.signUpHandler(login, mail, password)
    }
    Connections {
        target: mAuthor
        onServerResponseSignUp: {
            if(err == 0) {
                snackbar.open("Account created successfuly");
                signUpPage.pop();
            }
            else if(err == 1) {
                snackbar.open(strErr);
            }
        }
    }

    LinearGradient {
            anchors.fill: parent
            start: Qt.point(0, 0)
            end: Qt.point(parent.width, 0)
            gradient: Gradient {

                GradientStop { position: 0.4; color: "white" }
                GradientStop { position: 1.0; color: "#80808F" }
            }
    }

    Column {
        spacing: dp(10)
        anchors.centerIn: parent
        Label {
            id: lable
            text: "uTracker"
            font.bold: true
            color: "#5a585c"
            font.pixelSize: 100 * Units.dp
        }
        S_Input_1 {
            id: inputLogin
            property bool error: true
            placeholderContent: "Entry Your Login"
            inputWidth: lable.width
            KeyNavigation.tab: inputEmail
            KeyNavigation.backtab: inputEmail
            input {
                focus: true
                onTextChanged: {
                    inputLogin.error = (input.text.length < 4)
                    logLableLogin.toLogLable()
                }
                validator: RegExpValidator { regExp:/\w+([-+.']\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*/ }
            }
            input.onAccepted:inputEmail.input.forceActiveFocus()
        }
        Label {
            id: logLableLogin

            function toLogLable() {
                var message = "";
                if (inputLogin.error && inputLogin.input.text.length !== 0) {
                    message += "Login must be great then 4 symbols"
                }
                logLableLogin.text = message
            }
            width: text !== "" ? inputLogin.width : 0
            horizontalAlignment: Text.Center
            visible: !(!inputLogin.error && !inputEmail.error && !inputPassword.error && !inputPasswordConfirm.error)
            text: ""
            color: "red"
        }
        S_Input_1 {
            id: inputEmail
            property bool error: true
            placeholderContent: "Entry Your Email"
            inputWidth: lable.width
            input {
                onTextChanged: {
                    if (!input.acceptableInput)
                        inputEmail.error = true
                    else {
                        inputEmail.error = false
                    }
                    logLableMail.toLogLable()
                }
                validator: RegExpValidator { regExp:/\w+([-+.']\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*/ }
            }
            KeyNavigation.tab: inputPassword
            input.onAccepted:inputPassword.input.forceActiveFocus()
        }
        Label {
            id: logLableMail

            function toLogLable() {
                var message = "";
                if (inputEmail.error && inputEmail.input.text.length !== 0) {
                    message += "Wrong email"
                }
                logLableMail.text = message
            }
            width: text !== "" ? inputEmail.width : 0
            horizontalAlignment: Text.Center
            visible: !(!inputLogin.error && !inputEmail.error && !inputPassword.error && !inputPasswordConfirm.error)
            color: "red"
        }
        S_Input_1 {
            id: inputPassword
            property bool error: true
            placeholderContent: "Password"
            inputWidth: lable.width
            input.echoMode: TextInput.Password
            KeyNavigation.tab: inputPasswordConfirm
            input {
                onTextChanged: {
                    inputPassword.error = (input.text.length < 7)
                    logLablePassword.toLogLable()
                    inputPasswordConfirm.error = (inputPassword.input.text != inputPasswordConfirm.input.text) ||
                            (inputPasswordConfirm.input.text.length <= 0)
                }
            }
            input.onAccepted:inputPasswordConfirm.input.forceActiveFocus()
        }
        Label {
            id: logLablePassword

            function toLogLable() {
                var message = "";
                if (inputPassword.error && inputPassword.input.text.length !== 0) {
                    message += "Password must contain more then 7 symbols"
                }
                logLablePassword.text = message
            }
            width: text !== "" ? inputPassword.width : 0
            horizontalAlignment: Text.Center
            visible: !(!inputLogin.error && !inputEmail.error && !inputPassword.error && !inputPasswordConfirm.error)
            text: ""
            color: "red"
        }
        S_Input_1 {
            id: inputPasswordConfirm

            property bool error: true
            placeholderContent: "Password Confirm"
            inputWidth: lable.width
            input.echoMode: TextInput.Password
            input {
                onTextChanged: {
                    inputPasswordConfirm.error = (inputPassword.input.text != inputPasswordConfirm.input.text) ||
                            (inputPasswordConfirm.input.text.length <= 0)
                    logLableConfirm.toLogLable()
                }
            }
            input.onAccepted:signUp.clicked()
        }

        Label {
            id: logLableConfirm

            function toLogLable() {
                var message = ""
                if (!inputPassword.error && inputPassword.input.text.length !== 0
                         && inputPasswordConfirm.error && inputPasswordConfirm.input.text.length !== 0) {
                    message += "Passwords do not match"
                }
                logLableConfirm.text = message
            }
            width: text !== "" ? inputPasswordConfirm.width : 0
            horizontalAlignment: Text.Center
            visible: !(!inputLogin.error && !inputEmail.error && !inputPassword.error && !inputPasswordConfirm.error)
            text: ""
            color: "red"
        }

        S_Button_1 {
            id:signUp
            buttonEnabled: !inputLogin.error && !inputEmail.error && !inputPassword.error && !inputPasswordConfirm.error
            buttonContent: "Sign Up"
            width: parent.width
            Component.onCompleted: {
                signUp.clicked.connect(signUpRequest);
            }
        }
    }

}
