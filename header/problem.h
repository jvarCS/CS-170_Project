#ifndef PROBLEM_H
#define PROBLEM_H

#include <vector>
#include <iostream>
#include "boards.h"
#include "comp.h"
#include <queue>

using std::vector;
using std::string;
using std::priority_queue;

class Problem {
    private: 
        Boards *goal;
        char algo;
        int solDepth;
        int expand;
        int maxQ;
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
        int euclidean(Boards *);
        int findAPlace(Boards *,char,int &);
        int findGPlace(Boards *,char,int &);
        void sortQ(priority_queue<Boards *>);
        int misplaced(Boards *);
        int getExpand();
        int getMaxQ();
        int getSolD();
        void printBoard(Boards *);
        ~Problem();
};

#endif
