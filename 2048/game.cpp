#include "game.h"
#include <QtDebug>

Game::Game(QQmlContext *context, QObject *parent) : QObject(parent)
{
    scoreCounter = new Counter(this);
    bestScoreCounter = new Counter(this);

    context->setContextProperty("vueObjectGame", this);
    context->setContextProperty("vueObjetScoreCnt", scoreCounter);
    context->setContextProperty("vueObjetBestScoreCnt", bestScoreCounter);
}

void Game::initStructure(QObject *rootObject)
{
    // Fill dynamically the board with the cases

    QQuickItem *damier = rootObject->findChild<QQuickItem*>("damier");

    // Get case qml component from qml file
    QQmlEngine *engine = new QQmlEngine(this);
    QQmlComponent component(engine, QUrl("qrc:/case.qml"), QQmlComponent::PreferSynchronous);

    // Create case object for each spot
    for(int i=0; i<4; i++) {
        QList<Case *> row;

        for (int j=0; j<4; j++) {
            QQuickItem *rect = qobject_cast<QQuickItem *>(component.create());
            rect->setParentItem(damier);

            Case *rectCase = new Case(rect);
            row.append(rectCase);
        }
        cases.append(row);
    }
}

void Game::initGame()
{
    // Initialize the game

    // Get randomly 2 first spots
    int i0 = std::rand() % 4;
    int j0 = std::rand() % 4;
    int i1 = std::rand() % 4;
    int j1;
    do {
        j1 = std::rand() % 4;
    } while (i0 == i1 && j0 == j1);

    // Set value 2 on these spots
    cases[i0][j0]->init();
    cases[i1][j1]->init();
}

void Game::restart()
{
    scoreCounter->reset();
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            cases[i][j]->reset();
        }
    }
    initGame();
}

void Game::moveTop()
{
    qWarning("Top");
    for (int j=0; j<4; j++) {
        for (int i=3; i>0; i--) {
            if (cases[i-1][j]->isNull() && !cases[i][j]->isNull()) {
                *cases[i-1][j] = *cases[i][j];
                cases[i][j]->reset();
            }
            else if (*cases[i][j] == *cases[i-1][j]) {
                cases[i-1][j]->increment();
                cases[i][j]->reset();
            }
        }
    }
}

Game::~Game()
{
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            delete cases[i][j];
        }
    }
}
