#ifndef GAME_H
#define GAME_H

#include <stdlib.h>

#include <QObject>
#include <QtQml>
#include <QQuickItem>

#include "counter.h"
#include "case.h"
#include "range.h"

class Game : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int gridSize READ getGridSize NOTIFY gridSizeChanged)
    Q_PROPERTY(bool isBeginHistory READ isBeginHistory NOTIFY historyChanged)
    Q_PROPERTY(bool isEndHistory READ isEndHistory NOTIFY historyChanged)

public:
    explicit Game(QQmlContext *context, QObject *parent = nullptr);
    void setRootObject(QObject *object);
    void initStructure();
    void initGame();
    void popCase();
    Range getRange(int index, bool line, bool reverse);
    void move(bool line, bool reverse);
    void updateScore();
    void updateBestScore();
    void saveGame();
    void restoreGame();
    int getGridSize();
    bool isBeginHistory();
    bool isEndHistory();
    bool isAnyMovePossible();
    bool isGridFull();

    Q_INVOKABLE void restart(bool gridSizeChanged = false);
    Q_INVOKABLE void moveTop();
    Q_INVOKABLE void moveDown();
    Q_INVOKABLE void moveLeft();
    Q_INVOKABLE void moveRight();
    Q_INVOKABLE void setGridSize(const int size);
    Q_INVOKABLE void undo();
    Q_INVOKABLE void redo();

    void destroyCases();
    ~Game();

private:
    QObject *rootObject;
    Counter *scoreCounter;
    Counter *bestScoreCounter;
    vector<vector<Case *>> cases;
    vector<int **> history;
    unsigned int historyPosition;
    int emptyCases;
    int gridSize = 4;

signals:
    void gridSizeChanged();
    void historyChanged();
    void gameOver();


};

#endif // GAME_H
