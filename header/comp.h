#ifndef COMP_H
#define COMP_H

#include "boards.h"

class Comp {
public:
    bool operator() (Boards *b1, Boards *b2) {
        if (b1->getPriority() < b2->getPriority()) return false;
        return true;
    }
};


#endif