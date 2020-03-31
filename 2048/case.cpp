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
    case 0:
        color = "#CDC1B4";
        break;
    case 2:
        color = "#EEE4DA";
        break;
    case 4:
        color = "#EDE0C8";
        break;
    case 8:
        color = "#F2B179";
        break;
    case 16:
        color = "#f59563";
        break;
    case 32:
        color = "#f59563";
        break;
    case 64:
        color = "#f65e3b";
        break;
    case 128:
        color = "#edcf72";
        break;
    case 256:
        color = "#edcc61";
        break;
    case 512:
        color = "#f9f6f2";
        break;
    case 1024:
        color = "#edc53f";
        break;
    case 2048:
        color = "#edc22e";
        break;
    default:
        color = "#edc22e";
    }

    rectItem->setProperty("valueColor", val > 4 ? "#f9f6f2" : "#776e65");
    rectItem->setProperty("valueText", val > 0 ? QString::number(val) : "");
    rectItem->setProperty("color", color);
}

void Case::reset()
{
    setValue(0);
}

void Case::init()
{
    setValue(2);
}

void Case::increment()
{
    setValue(value * 2);
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
