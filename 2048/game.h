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
public:
    explicit Game(QQmlContext *context, QObject *parent = nullptr);
    void initStructure(QObject *rootObject);
    void initGame();
    void popCase();
    Range getRange(int index, bool line, bool reverse);
    void move(bool line, bool reverse);
    void updateScore();
    void updateBestScore();


    Q_INVOKABLE void restart();
    Q_INVOKABLE void moveTop();
    Q_INVOKABLE void moveDown();
    Q_INVOKABLE void moveLeft();
    Q_INVOKABLE void moveRight();
    Q_INVOKABLE int getGridSize();

    ~Game();

private:
    Counter *scoreCounter;
    Counter *bestScoreCounter;
    QList<QList<Case *>> cases;
    bool endGame;
    int emptyCases;
    int const gridSize = 9;

signals:


};

#endif // GAME_H
