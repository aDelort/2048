#ifndef CASE_H
#define CASE_H

#include <QQuickItem>


class Case
{
public:
    Case(QQuickItem *rect);
    void setNull();
    void init();
    void increment();
    bool isNull();
    int getValue();

    Case& operator=(const Case& other);
    bool operator==(const Case& other);

private:
    int value;
    void setValue(int val);

    QQuickItem *rectItem;

};

#endif // CASE_H
