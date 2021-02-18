#include "authorization.h"
#include <iostream>

Authorization::Authorization(QObject *parent) : QObject(parent) {}

void Authorization::signUpHandler(QString login, QString mail, QString password)
{
    auto err = NO_ERR;
    // request to server
    if (login == "hello") {
        err = LOGIN_EX;
    }
    else if (mail == "hello@a.a") {
        err = MAIL_EX;
    }

    emit serverResponseSignUp(err);
}

void Authorization::signInHandler(QString ident, QString password) {
    if (ident == "hello" && password == "123456789")
        std::cout << "Hello" << std::endl;

    emit serverResponseSignIn(ident == "hello" && password == "123456789");

}
