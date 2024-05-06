#ifndef PROBLEM_H
#define PROBLEM_H

#include <vector>
#include <iostream>
#include "boards.h"

using std::vector;
using std::string;

class Problem {
    private: 
        Boards *goal;
        int gN;
        char algo;
    public:
        Problem(char);
        Problem(int,char);
        bool checkBoard(Boards *);
        int findX(int&, Boards *);
        bool moveRight(Boards *);
        bool moveLeft(Boards *);
        bool moveDown(Boards *);
        bool moveUp(Boards *);
        bool solve(Boards *);
        float Problem::euclidean(Boards *);
        int findAPlace(Boards *,char,float &);
        int findGPlace(Boards *,char,float &);
};


#endif
