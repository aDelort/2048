#ifndef RANGE_H
#define RANGE_H
#include "case.h"


class Range
{
public: 
    Range(int rangeSize);
    Range(std::vector<Case* > L, int rangeSize);
    bool shift(int k);
    bool deleteBlanks();
    int fusion();
    int collapse();

private:
//    static int const size;
    std::vector<Case* > L;
    int rangeSize;
};

#endif // RANGE_H
