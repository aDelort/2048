#include "case.h"
#include <QtDebug>

Case::Case(QQuickItem *rect)
{
    rectItem = rect;
    setValue(0);
}

void Case::setValue(int val)
{
    value = val;

    QString color;
    switch (val) {
    case 0: color = "#CDC1B4"; break;
    case 1: color = "#EEE4DA"; break;
    case 2: color = "#EDE0C8"; break;
    case 3: color = "#F2B179"; break;
    case 4: color = "#f59563"; break;
    case 5: color = "#f59563"; break;
    case 6: color = "#f65e3b"; break;
    case 7: color = "#edcf72"; break;
    case 8: color = "#edcc61"; break;
    case 9: color = "#f9f6f2"; break;
    case 10:color = "#edc53f"; break;
    case 11:color = "#edc22e"; break;
    default:color = "#edc22e";
    }

    rectItem->setProperty("valueColor", val > 2 ? "#f9f6f2" : "#776e65");
    rectItem->setProperty("valueText", val > 0 ? QString::number(pow(2,val)) : "");
    rectItem->setProperty("color", color);
}

void Case::reset()
{
    setValue(0);
}

void Case::init()
{
    setValue(1);
}

void Case::increment()
{
    setValue(value+1);
}

bool Case::isNull()
{
    return value == 0;
}

Case& Case::operator=(const Case& other)
{
    if (this != &other) {
        this->setValue(other.value);
    }
    return *this;
}

bool Case::operator==(const Case &other)
{
    return this->value == other.value;
}
