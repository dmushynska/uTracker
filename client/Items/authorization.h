#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QObject>

class Authorization : public QObject
{
    Q_OBJECT

public:
    enum SignUpError {
        NO_ERR = 0,
        LOGIN_EX,
        MAIL_EX
    };
    Q_ENUMS(SignUpError)
    explicit Authorization(QObject *parent = nullptr);
    ~Authorization() = default;

    Q_INVOKABLE void signUpHandler(QString login, QString mail, QString password);
    Q_INVOKABLE void signInHandler(QString ident, QString password);

signals:
    void serverResponseSignIn(bool valid);
    void serverResponseSignUp(SignUpError err);

private:
    void doServerRequest();
private:
    // Request m_request;
    QString m_mail;
    QString m_login;
    QString m_password;
};

#endif // AUTHORIZATION_H
