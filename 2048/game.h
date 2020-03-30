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

    Q_INVOKABLE void restart();

    ~Game();

private:
    Counter *scoreCounter;
    Counter *bestScoreCounter;
    QList<QList<Case *>> cases;

signals:


};

#endif // GAME_H
