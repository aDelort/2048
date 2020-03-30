#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>

class Counter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString cntQML READ readCounter NOTIFY cntChanged)

public:
    explicit Counter(QObject *parent = nullptr);
    QString readCounter();
    void increment(int value);
    void reset();

signals:
    void cntChanged();

private:
    int count;

};

#endif // COUNTER_H
