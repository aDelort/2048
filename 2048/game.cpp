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

    emptyCases = 16;
    endGame = false;
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
    updateScore();
}

void Game::popCase()
{
    // Get randomly a spot
    if (emptyCases == 0){
        endGame = true;
    }
    else{
        int i,j;
        do{
        i = std::rand() % 4;
        j = std::rand() % 4;
        } while (!cases[i][j]->isNull());
        cases[i][j]->init();
        emptyCases--;
    }
}

void Game::restart()
{
    scoreCounter->reset();
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            cases[i][j]->setNull();
        }
    }
    emptyCases = 16;
    endGame = false;
    initGame();
}

void Game::move(bool line, bool reverse){
    if (!endGame){
        Range r;
        for (int i=0; i<4; i++) {
            r = getRange(i,line,reverse);
            emptyCases += r.collapse();
        }
        popCase();
        updateScore();
    }
}

void Game::moveTop()
{
    move(false,false);
}

void Game::moveDown()
{
    move(false,true);
}

void Game::moveLeft()
{
    move(true,false);
}

void Game::moveRight()
{
    move(true,true);
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
    return r;
}

void Game::updateScore()
{
    int score(0);
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (cases[i][j]->getValue() > score){score = cases[i][j]->getValue();}
        }
    }
    scoreCounter->setValue(score);
    updateBestScore();
}

void Game::updateBestScore()
{
    if (scoreCounter->getValue() > bestScoreCounter->getValue()){bestScoreCounter->setValue(scoreCounter->getValue());}
}
