//#include "user.h"
#include "usermanager.h"

User::User(QObject *parent) : QObject(parent), m_userId(-1) {
    qobject_cast<UserManager *>(parent)->getAuthor();

}



void User::setUserLogin(const QString &login) {
    if (m_userLogin != login) {
        m_userLogin = login;
        emit userLoginChanged();
    }
}

void User::setUserMail(const QString &mail) {
    if (m_userMail != mail) {
        m_userMail = mail;
        emit userMailChanged();
    }
}

void User::setUserId(int id) {
    if (m_userId != id) {
        m_userId = id;
        emit userIdChanged();
    }
}



QString User::getUserLogin() const {
    return m_userLogin;
}

QString User::getUserMail() const {
    return m_userMail;
}

int User::getUserId() const {
    return m_userId;
}


