#include "authorization.h"
#include <iostream>

Authorization::Authorization(QObject *parent) : QObject(parent) {}

void Authorization::setRequest(AbstractRequest *request) {
    m_request = request;
}

void Authorization::signUpHandler(QString login, QString mail, QString password)
{
    m_request->signUp(login, password, login + mail, mail + login, mail);
}

void Authorization::signInHandler(QString ident, QString password) {
    m_request->signIn(ident, ident, password);
}

void Authorization::printStr(QString str) {
    qDebug() << str;
}