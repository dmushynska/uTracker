#include "authorization.h"
#include "usermanager.h"
#include <iostream>

Authorization::Authorization(QObject *parent) : QObject(parent) {}

void Authorization::setRequest(AbstractRequest *request) {
    m_request = request;
    m_request->signUp("1", "11111111", "Pavel", "Durov", "1@1.1");
}

void Authorization::signUpHandler(QString login, QString mail, QString password)
{
    m_request->signUp(login, password, login + mail, mail + login, mail);
}

void Authorization::signInHandler(QString ident, QString password) {
    m_request->signIn(ident, password);
}

void Authorization::printStr(QString str) {
    qDebug() << str;
}

void Authorization::setUserId(int id) {
    PARENT_CAST(UserManager, parent())->getUser()->setUserId(id);
}
