#include "usermanager.h"
#include <QQmlContext>
#include <QQuickItem>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "material/src/plugin.h"



UserManager::UserManager(QObject *parent) : QObject(parent), m_user(this),
    m_author(new Authorization(this)),
    m_workflow(new Workflow(this))
{
//view.engine();
    QPM_INIT(engine)
    MaterialPlugin qmlMaterial;
    qmlMaterial.registerTypes("Material");
    engine.addImportPath("qrc:/");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        exit(-1);
    initModules();
    //    connect(this, UserManager::doRequestToServer, requester) // after request_class connection
}

void UserManager::initModules() const
{
    qmlRegisterType<Authorization>("Authorization", 1, 0, "Authorization");
//    qmlRegisterType<Authorization>("Authorization", 1, 0, "Authorization");
//    engine.rootContext()setContextProperty("author", &m_author);
//    auto root = engine.rootContext();
//    root->setContextProperty()
//    engine.rootContext()->setContextProperty("mAuthor", QVariant::fromValue(&m_author));
    engine.rootContext()->setContextProperty("mAuthor", (QObject *)m_author);
    engine.rootContext()->setContextProperty("mWorkflow", (QObject *)m_workflow);
    engine.rootContext()->setContextProperty("mCardListsModel", (QObject *)(m_workflow->getCardListModel()));
    engine.rootContext()->setContextProperty("mWorkflowList", (QObject *)(m_workflow->getWorkflowsModel()));
    engine.rootContext()->setContextProperty("mDescriptor", (QObject *)(m_workflow->getDescriptionModel()));
}

Authorization *UserManager::getAuthor() {
    return m_author;
}

User *UserManager::getUser() {
    return &m_user;
}

Workflow *UserManager::getWorkflow() {
    return m_workflow;
}
