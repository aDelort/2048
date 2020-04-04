#include "game.h"
#include <iostream>
using namespace std;;

Game::Game(QQmlContext *context, QObject *parent) : QObject(parent)
{
    scoreCounter = new Counter(this);
    bestScoreCounter = new Counter(this);
    context->setContextProperty("vueObjectGame", this);
    context->setContextProperty("vueObjetScoreCnt", scoreCounter);
    context->setContextProperty("vueObjetBestScoreCnt", bestScoreCounter);

    historyPosition = 0;
}
void Game::setRootObject(QObject *object)
{
    // Sets the root qml object
    rootObject = object;
}
void Game::initStructure()
{
    // Fills dynamically the board with the cases

    QQuickItem *damier = rootObject->findChild<QQuickItem*>("damier");

    // Get case qml component from qml file
    QQmlEngine *engine = new QQmlEngine(this);
    QQmlComponent component(engine, QUrl("qrc:/Case.qml"), QQmlComponent::PreferSynchronous);

    // Create case object for each spot
    for(int i = 0; i < gridSize; i++) {
        vector<Case *> row;

        for (int j = 0; j < gridSize; j++) {
            QQuickItem *rect = qobject_cast<QQuickItem *>(component.create());
            rect->setParentItem(damier);

            Case *rectCase = new Case(rect);
            row.push_back(rectCase);
        }
        cases.push_back(row);
    }
}

void Game::initGame()
{
    // Initializes the game
    popCase();
    popCase();
    updateScore();
    saveGame();
}

void Game::setGridSize(const int size)
{
    // Sets the grid size
    if(size != gridSize) {
        destroyCases();
        gridSize = size;
        initStructure();
        restart(true);
        gridSizeChanged();
    }
}

int Game::getGridSize()
{
    return gridSize;
}
void Game::popCase()
{
    // Initializes a random case
    if (isGridFull())
        return;
    int i,j;
    do{
        i = std::rand() % gridSize;
        j = std::rand() % gridSize;
    } while (!cases[i][j]->isNull());
    cases[i][j]->init();
}

void Game::restart(bool gridSizeChanged)
{
    // Restarts the game
    scoreCounter->reset();
    history.clear();
    historyPosition = 0;
    if (!gridSizeChanged) {
        for (int i = 0; i < gridSize; i++) {
            for (int j=0; j<gridSize; j++) {
                cases[i][j]->setNull();
            }
        }
    }
    initGame();
}

void Game::move(bool line, bool reverse){
    // Makes the cases move
    bool deletedBlanks, gameMoved(false);
    int emptiedCases;

    Range r(gridSize);
    for (int i = 0; i < gridSize; i++) {
        r = getRange(i,line,reverse);
        deletedBlanks = r.deleteBlanks();
        emptiedCases = r.fusion();
        if (deletedBlanks or (emptiedCases > 0)) {gameMoved = true;}
    }
    if (gameMoved){
        popCase();
        updateScore();
        saveGame();
    }
    if (isAnyMovePossible()) {
        gameOver();
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

void Game::destroyCases()
{
    // Destroy all the cases
    for (int i = 0; i < gridSize; i++){
        for (int j = 0; j < gridSize; j++){
            delete cases[i][j];
        }
    }
    cases.clear();
}

Game::~Game()
{
    destroyCases();
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
    // Updates the game score
    int score(0);
    for (int i = 0; i < gridSize; i++){
        for (int j = 0; j < gridSize; j++){
            score += cases[i][j]->getValue();
        }
    }
    scoreCounter->setValue(score);
    updateBestScore();
}

void Game::updateBestScore()
{
    // Update the best score
    if (scoreCounter->getValue() > bestScoreCounter->getValue()){
        bestScoreCounter->setValue(scoreCounter->getValue());
    }
}

void Game::saveGame()
{
    // Save the current situation in history
    int** rows = new int*[gridSize];
    for (int i=0; i<gridSize; i++) {
        int* row = new int[gridSize];
        for (int j=0; j<gridSize; j++) {
            row[j] = cases[i][j]->getValue();
        }
        rows[i] = row;
    }
    if (!isEndHistory() && historyPosition > 0) {
        history.resize(historyPosition+1);
    }
    history.push_back(rows);
    if (history.size() > 1)
        historyPosition++;
    historyChanged();
}

void Game::restoreGame()
{
    // Restore the game from the situation with the index historyPosition
    int **rows = history[historyPosition];

    for (int i=0; i<gridSize; i++) {
        for (int j=0; j<gridSize; j++) {
            cases[i][j]->setValue(rows[i][j]);
        }
    }
    updateScore();
    historyChanged();
}

void Game::undo()
{
    // Restore from previous situation
    if (!isBeginHistory()) {
        historyPosition--;
        restoreGame();
    }
}

void Game::redo()
{
    // Restore from next situation
    if (!isEndHistory()) {
        historyPosition++;
        restoreGame();
    }
}

bool Game::isBeginHistory()
{
    // Returns true if first situation of history
    return historyPosition == 0;
}

bool Game::isEndHistory()
{
    // Returns true if last situation of history
    return historyPosition == history.size()-1;
}

bool Game::isAnyMovePossible()
{
    // Checks if a move is possible
    for (int i=0; i<gridSize; i++) {
        for (int j=0; j<gridSize; j++) {
            if(cases[i][j]->isNull() ||
                    (j<gridSize-1 && *cases[i][j] == *cases[i][j+1]) ||
                    (i<gridSize-1 && *cases[i][j] == *cases[i+1][j]))
                return false;
        }
    }
    return true;
}

bool Game::isGridFull()
{
    // Returns true if there is no empty case
    for (int i=0; i<gridSize; i++) {
        for (int j=0; j<gridSize; j++) {
            if (cases[i][j]->isNull())
                return false;
        }
    }
    return true;
}
