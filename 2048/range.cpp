#include "range.h"
#include <QtDebug>
#include <iostream>

using namespace std;;

Range::Range()
{
    for (int i=0; i<4; i++){
        L[i] = 0;
    }
}

Range::Range(Case* m_L[4])
{
    for (int i=0; i<4; i++){
        L[i] = m_L[i];
    }
}

void Range::shift(int k)
{
    // Deletes the case k and shifts the next cases to their left
    for(int i = k; i < 3; i++){
        *L[i] = *L[i+1];
    }
    L[3]->setNull();
}

int Range::fusion()
{
    bool stop = false;
    int i=0;
    int emptied(0);
    while (i<3 && !stop){
        if (L[i]->isNull()){
            stop= true;
        }
        else if (*L[i] == *L[i+1]){
            L[i]->increment();
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
    int i(0), iMax(0);
    while (i < 4 && iMax < 4)
    {
        if(L[i]->isNull()){
            shift(i);
        }
        else{
            i++;
        }
        iMax++;
    }
    return fusion();
}

