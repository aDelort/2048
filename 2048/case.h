#ifndef CASE_H
#define CASE_H

#include <QQuickItem>


class Case
{
public:
    Case(QQuickItem *rect);
    void reset();
    void init();
    void increment();

    bool isNull();

    Case& operator=(const Case& other);
    bool operator==(const Case& other);

private:
    void setValue(int val);

    QQuickItem *rectItem;
    int value;

};

#endif // CASE_H
