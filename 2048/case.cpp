#include "case.h"

using namespace std;;

Case::Case(QQuickItem *rect)
{
    rectItem = rect;
    setValue(0);
}

int Case::getValue()
{
    return value;
}

void Case::setValue(const int val)
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
        color = "#edc94f";
        break;
    case 1024:
        color = "#edc53f";
        break;
    case 2048:
        color = "#edc22e";
        break;
    default:
        color = "#000000";
    }

    rectItem->setProperty("valueColor", val > 4 ? "#f9f6f2" : "#776e65");
    rectItem->setProperty("valueText", val > 0 ? QString::number(val) : "");
    rectItem->setProperty("color", color);
}

void Case::setNull()
{
    setValue(0);
}

void Case::init()
{
    // Initializes the case with a 2 or 4
    int p = rand() % 6;
    if (p > 0){
    setValue(2);
    }
    else{
        setValue(4);
    }
}

void Case::increment()
{
    // Doubles the displayed value of the case
    setValue(value * 2);
}

bool Case::isNull()
{
    return value == 0;
}

Case& Case::operator=(const Case& other)
{
    // Compares the cases value
    if (this != &other) {
        this->setValue(other.value);
    }
    return *this;
}

bool Case::operator==(const Case &other)
{
    // Copy the case value
    return this->value == other.value;
}

Case::~Case()
{
    rectItem->deleteLater();
}
