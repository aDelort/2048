#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QtQml>
#include <QQuickItem>

#include "counter.h"

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QQmlContext *context, QObject *parent = nullptr);
    void init(QObject *rootObject);


    Q_INVOKABLE void restart();

private:
    Counter *scoreCounter;
    Counter *bestScoreCounter;
    QQuickItem *damier;

signals:


};

#endif // GAME_H
