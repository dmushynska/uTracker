#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QObject>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include "user.h"
#include "authorization.h"
#include "model/cardlistsmodel.h"

namespace Request { // this have to be moved to request class/file
    enum TypeRequest {
        SIGN_IN,
        SIGN_UP
    };
}

class UserManager : public QObject
{
    Q_OBJECT
public:
    explicit UserManager(QObject *parent = nullptr);
    ~UserManager() = default;

    void initModules() const;
    // Sing* page

    //


signals:
    void doRequestToServer(Request::TypeRequest type, QHash<QString, QString> content);

private:
//    Request m_requester;
    QQmlApplicationEngine engine;
//    QQuickView view;
    User m_user;
    Authorization m_author;

    // Models
    CardListsModel m_cardListModel;
};

#endif // USERMANAGER_H
