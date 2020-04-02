#include "range.h"
#include <QtDebug>
#include <iostream>

using namespace std;;

Range::Range(int m_rangeSize)
{
    rangeSize = m_rangeSize;
    for (int i = 0; i < rangeSize; i++){
        L.push_back(0);
    }
}

Range::Range(vector<Case* > m_L, int m_rangeSize)
{
    rangeSize = m_rangeSize;
    for (int i = 0; i < rangeSize; i++){
        L.push_back(m_L[i]);
    }
}

bool Range::shift(int k)
{
    bool isEmptyShift(true);
    // Deletes the case k and shifts the next cases to their left
    for(int i = k; i < rangeSize-1; i++){
        if(!L[i+1]->isNull()){isEmptyShift = false;}
        *L[i] = *L[i+1];
    }
    if (!isEmptyShift){L[rangeSize-1]->setNull();}
    return isEmptyShift;
}

bool Range::deleteBlanks()
{
    int i(0);//, iMax(0);
    bool hasDeleted(false), isEmptyShift(false);
    while (i < rangeSize && !isEmptyShift)
    {
        if(L[i]->isNull()){
            isEmptyShift = shift(i);
            if (!isEmptyShift){hasDeleted=true;}
        }
        else{
            i++;
        }
        //iMax++;
    }
    return hasDeleted;
}

int Range::fusion()
{
    bool stop = false;
    int i = 0;
    int emptied(0);
    while (i < rangeSize-1 && !stop){
        if (L[i]->isNull()){
            stop= true;
        }
        else if (*L[i] == *L[i+1]){
            L[i]->increment();
            L[i+1]->setNull();
            shift(i+1);
            i++;
            emptied++;
        }
        else{
            i++;
        }
    }
    return emptied;
}

int Range::collapse()
{
    deleteBlanks();
    return fusion();
}

