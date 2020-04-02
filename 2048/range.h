#ifndef RANGE_H
#define RANGE_H
#include "case.h"

class Range
{
public: 
    Range();
    Range(Case* L[4]);
    void shift(int k);
    int fusion();
    int collapse();

private:
    Case* L[4];
};

#endif // RANGE_H
