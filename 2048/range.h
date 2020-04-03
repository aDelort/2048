#ifndef RANGE_H
#define RANGE_H

#include "case.h"
#include <iostream>

using namespace std;;

class Range
{
public: 
    Range(int rangeSize);
    Range(vector<Case* > L, int rangeSize);
    bool shift(int k);
    bool deleteBlanks();
    int fusion();
    int collapse();

private:
//    static int const size;
    vector<Case* > L;
    int rangeSize;
};

#endif // RANGE_H
