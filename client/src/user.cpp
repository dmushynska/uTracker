//#include "user.h"
#include "usermanager.h"

User::User(QObject *parent) : QObject(parent), m_userId(-1) {
    qobject_cast<UserManager *>(parent)->getAuthor();
}

void User::setUserId(int id) {
    m_userId = id;
}

void User::setUserLogin(const QString &login) {
    m_userLogin = login;
}

void User::setUserMail(const QString &mail) {
    m_userMail = mail;
}

int User::getUserId() const {
    return m_userId;
}

QString User::getUserLogin() const {
    return m_userLogin;
}

QString User::getUserMail() const {
    return m_userMail;
}


