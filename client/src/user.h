#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);
    void setUserId(int id);
    void setUserLogin(const QString &login);
    void setUserMail(const QString &mail);

    int getUserId() const;
    QString getUserLogin() const;
    QString getUserMail() const;

private:
    int m_userId;
    QString m_userLogin;
    QString m_userMail;
};

#endif // USER_H
