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

    initRandomCase();
    initRandomCase();
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

bool Game::isFull()
{
    // Renvoie true si toutes les cases sont non nulles

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            if(cases[i][j]->isNull())
                return false;
        }
    }
    return true;
}

void Game::initRandomCase()
{
    // Generate a 2 on an null case
    // rajouter erreur si impossible et try catch dans l'appel

    if (isFull())
        return;
    int i,j;
    do {
        i = std::rand() % 4;
        j = std::rand() % 4;
    } while (!cases[i][j]->isNull());

    cases[i][j]->init();
}

void Game::moveTop()
{
    for (int j=0; j<4; j++) {

        // Déplacement
        for (int i=3; i>0; i--) {
            moveCaseIfEmptyNeighbour(i,j,i-1,j);
        }

        // Fusion + Déplacement
        for (int i=0; i<3; i++) {
            mergeCasesIfEqual(i,j,i+1,j);
            moveCaseIfEmptyNeighbour(i+1,j,i,j);
        };
    }
    initRandomCase();
}

void Game::moveBottom()
{
    for (int j=0; j<4; j++) {

        for (int i=0; i<3; i++)
            moveCaseIfEmptyNeighbour(i,j,i+1,j);

        for (int i=3; i>0; i--) {
            mergeCasesIfEqual(i,j,i-1,j);
            moveCaseIfEmptyNeighbour(i-1,j,i,j);
        };
    }
    initRandomCase();
}

void Game::moveLeft()
{
    for(int i=0; i<4; i++)
    {
        for (int j=3; j>0; j--)
            moveCaseIfEmptyNeighbour(i,j,i,j-1);

        for (int j=0; j<3; j++) {
            mergeCasesIfEqual(i,j,i,j+1);
            moveCaseIfEmptyNeighbour(i,j+1,i,j);
        }
    }
    initRandomCase();
}

void Game::moveRight()
{
    for(int i=0; i<4; i++)
    {
        for (int j=0; j<3; j++)
            moveCaseIfEmptyNeighbour(i,j,i,j+1);

        for (int j=3; j>0; j--) {
            mergeCasesIfEqual(i,j,i,j-1);
            moveCaseIfEmptyNeighbour(i,j-1,i,j);
        }
    }
    initRandomCase();
}

void Game::moveCaseIfEmptyNeighbour(int i0, int j0, int i1, int j1)
{
    if (cases[i1][j1]->isNull() && !cases[i0][j0]->isNull()) {
        *cases[i1][j1] = *cases[i0][j0];
        cases[i0][j0]->reset();
    }
}

void Game::mergeCasesIfEqual(int i0, int j0, int i1, int j1)
{
    if (!cases[i0][j0]->isNull() && *cases[i0][j0] == *cases[i1][j1]) {
        cases[i0][j0]->increment();
        cases[i1][j1]->reset();
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
