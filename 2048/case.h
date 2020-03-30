#ifndef CASE_H
#define CASE_H

#include <QQuickItem>


class Case
{
public:
    Case(QQuickItem *rect);
    void setValue(int val);

private:
    QQuickItem *rectItem;
    int value;

};

#endif // CASE_H
