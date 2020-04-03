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
    void setValue(const int val);

    Case& operator=(const Case& other);
    bool operator==(const Case& other);

    ~Case();

private:
    int value;

    QQuickItem *rectItem;

};

#endif // CASE_H
