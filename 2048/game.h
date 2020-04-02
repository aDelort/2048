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
    Q_PROPERTY(bool isBeginHistory READ isBeginHistory NOTIFY historyChanged)
    Q_PROPERTY(bool isEndHistory READ isEndHistory NOTIFY historyChanged)

public:
    explicit Game(QQmlContext *context, QObject *parent = nullptr);
    void initStructure(QObject *rootObject);
    void initGame();
    void popCase();
    Range getRange(int index, bool line, bool reverse);
    void move(bool line, bool reverse);
    void updateScore();
    void updateBestScore();
    void saveGame();
    void restoreGame();
    bool isBeginHistory();
    bool isEndHistory();

    Q_INVOKABLE void restart();
    Q_INVOKABLE void moveTop();
    Q_INVOKABLE void moveDown();
    Q_INVOKABLE void moveLeft();
    Q_INVOKABLE void moveRight();
    Q_INVOKABLE int getGridSize();
    Q_INVOKABLE void undo();
    Q_INVOKABLE void redo();

    ~Game();

private:
    Counter *scoreCounter;
    Counter *bestScoreCounter;
    QList<QList<Case *>> cases;
    vector<int **> history;
    unsigned int historyPosition;
    bool endGame;
    int emptyCases;
    int const gridSize = 4;

signals:
    void historyChanged();


};

#endif // GAME_H
