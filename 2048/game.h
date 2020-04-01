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


    Q_INVOKABLE void restart();
    Q_INVOKABLE void moveTop();
    Q_INVOKABLE void moveDown();
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
