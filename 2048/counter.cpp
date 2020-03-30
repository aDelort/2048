#include "counter.h"

Counter::Counter(QObject *parent) : QObject(parent)
{
    count = 0;
}

QString Counter::readCounter()
{
    return QString::number(count);
}

void Counter::increment(int value)
{
    count += value;
    cntChanged();
}

void Counter::reset()
{
    count = 0;
    cntChanged();
}
