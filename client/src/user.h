#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userLogin READ getUserLogin WRITE setUserLogin NOTIFY userLoginChanged)
    Q_PROPERTY(QString userMail READ getUserMail WRITE setUserMail NOTIFY userMailChanged)
    Q_PROPERTY(int userId READ getUserId WRITE setUserId NOTIFY userIdChanged)

public:

    explicit User(QObject *parent = nullptr);

    void setUserLogin(const QString &login);
    void setUserMail(const QString &mail);
    void setUserId(int id);

    QString getUserLogin() const;
    QString getUserMail() const;
    int getUserId() const;

signals:
    void userLoginChanged();
    void userMailChanged();
    void userIdChanged();

private:
    int m_userId;
    QString m_userLogin;
    QString m_userMail;
};

#endif // USER_H
