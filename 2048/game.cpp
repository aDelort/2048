#include "game.h"

Game::Game(QQmlContext *context, QObject *parent) : QObject(parent)
{
    scoreCounter = new Counter(this);
    bestScoreCounter = new Counter(this);

    context->setContextProperty("vueObjectGame", this);
    context->setContextProperty("vueObjetScoreCnt", scoreCounter);
    context->setContextProperty("vueObjetBestScoreCnt", bestScoreCounter);
}

void Game::init(QObject *rootObject)
{
    // Fill dynamically the board with the cases

    damier = rootObject->findChild<QQuickItem*>("damier");

    QQmlEngine *engine = new QQmlEngine();
    QQmlComponent component(engine, QUrl("qrc:/case.qml"), QQmlComponent::PreferSynchronous);

    for(int i=0; i<16; i++) {
        QQuickItem *rect = qobject_cast<QQuickItem *>(component.create());
        rect->setParentItem(damier);
    }
}

void Game::restart()
{
    scoreCounter->reset();
}
