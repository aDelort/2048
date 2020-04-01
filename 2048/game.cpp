#include "game.h"
#include <QtDebug>
#include <iostream>
using namespace std;;

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
    // Get randomly 2 first spots
    popCase();
    popCase();
}

void Game::popCase()
{
    // Get randomly a spot
    int i,j;
    do{
    i = std::rand() % 4;
    j = std::rand() % 4;
    } while (!cases[i][j]->isNull());
    cases[i][j]->init();
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
    Range r;
    for (int j=0; j<4; j++) {
        r = getRange(j,false,false);
        r.collapse();
    }
    //delete r;
    popCase();
}

void Game::moveDown()
{
    for (int j=0; j<4; j++) {
        Range r(getRange(j,false,true));
        r.collapse();
    }
    popCase();
}

void Game::moveLeft()
{
    for (int i=0; i<4; i++) {
        Range r(getRange(i,true,false));
        r.collapse();
    }
    popCase();
}

void Game::moveRight()
{
    for (int i=0; i<4; i++) {
        Range r(getRange(i,true,true));
        r.collapse();
    }
    popCase();
}

Game::~Game()
{
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            delete cases[i][j];
        }
    }
}

Range Game::getRange(int index, bool line, bool reverse)
{
    Case* L[4];
    int i2;
    for (int i = 0; i < 4; i++){
        if (reverse){
            i2 = 3-i;
        }
        else{
            i2 = i;
        }
        if (line){
            L[i] = cases[index][i2];
        }
        else
        {
            L[i] = cases[i2][index];
        }
    }
    Range r(L);
    //delete L[0];
    //delete L[1];
    //delete L[2];
    //delete L[3];
    return r;
}

