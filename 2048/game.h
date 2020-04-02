#ifndef GAME_H
#define GAME_H

#include <stdlib.h>

#include <QObject>
#include <QtQml>
#include <QQuickItem>

#include "counter.h"
#include "case.h"

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QQmlContext *context, QObject *parent = nullptr);
    void initStructure(QObject *rootObject);
    void initGame();

    bool isFull();

    void initRandomCase();
    void moveCaseIfEmptyNeighbour(int i0, int j0, int i1, int j1);
    void mergeCasesIfEqual(int i0, int j0, int i1, int j1);

    Q_INVOKABLE void restart();
    Q_INVOKABLE void moveTop();
    Q_INVOKABLE void moveBottom();
    Q_INVOKABLE void moveLeft();
    Q_INVOKABLE void moveRight();

    ~Game();

private:
    Counter *scoreCounter;
    Counter *bestScoreCounter;
    QList<QList<Case *>> cases;

signals:


};

#endif // GAME_H
