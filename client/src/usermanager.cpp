#include "usermanager.h"
#include <QQmlContext>
#include <QQuickItem>


UserManager::UserManager(QObject *parent) : QObject(parent), m_user(this), m_author(this)
{
//view.engine();
    QPM_INIT(engine)
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        exit(-1);
    initModules();
    //    connect(this, UserManager::doRequestToServer, reuester) // after request_class connection
}

void UserManager::initModules() const
{
    qmlRegisterType<Authorization>("Authorization", 1, 0, "Authorization");
    qmlRegisterType<Authorization>("Authorization", 1, 0, "Authorization");
//    engine.rootContext()setContextProperty("author", &m_author);
//    auto root = engine.rootContext();
//    root->setContextProperty()
//    engine.rootContext()->setContextProperty("mAuthor", QVariant::fromValue(&m_author));
    engine.rootContext()->setContextProperty("mAuthor", (QObject *)&m_author);
    engine.rootContext()->setContextProperty("mCardListsModel", (QObject *)&m_cardListModel);
}
