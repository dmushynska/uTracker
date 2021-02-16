#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);

private:
    int m_userId;
    QString m_userLogin;
    QString m_userTocken;
    QString m_userMail;
};

#endif // USER_H
