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

    emptyCases = gridSize*gridSize;
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
    for(int i = 0; i < gridSize; i++) {
        QList<Case *> row;

        for (int j = 0; j < gridSize; j++) {
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

int Game::getGridSize()
{
    return gridSize;
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
        i = std::rand() % gridSize;
        j = std::rand() % gridSize;
        } while (!cases[i][j]->isNull());
        cases[i][j]->init();
        emptyCases--;
    }
}

void Game::restart()
{
    scoreCounter->reset();
    for (int i = 0; i < gridSize; i++) {
        for (int j=0; j<gridSize; j++) {
            cases[i][j]->setNull();
        }
    }
    emptyCases = gridSize*gridSize;
    endGame = false;
    initGame();
}

void Game::move(bool line, bool reverse){
    bool deletedBlanks, gameMoved(false);
    int emptiedCases;
    if (!endGame){
        Range r(gridSize);
        for (int i = 0; i < gridSize; i++) {
            r = getRange(i,line,reverse);
            deletedBlanks = r.deleteBlanks();
            emptiedCases = r.fusion();
            emptyCases += emptiedCases;
            if (deletedBlanks or (emptiedCases > 0)) {gameMoved = true;}
        }
        if (gameMoved){
            popCase();
            updateScore();
        }
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
    for (int i = 0; i < gridSize; i++){
        for (int j = 0; j < gridSize; j++){
            delete cases[i][j];
        }
    }
}

Range Game::getRange(int index, bool line, bool reverse)
{
    vector<Case* > L;
    int i2;
    for (int i = 0; i < gridSize; i++){
        if (reverse){
            i2 = gridSize - 1 - i;
        }
        else{
            i2 = i;
        }
        if (line){
            L.push_back(cases[index][i2]);
        }
        else
        {
            L.push_back(cases[i2][index]);
        }
    }
    Range r(L, gridSize);
    return r;
}

void Game::updateScore()
{
    int score(0);
    for (int i = 0; i < gridSize; i++){
        for (int j = 0; j < gridSize; j++){
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
