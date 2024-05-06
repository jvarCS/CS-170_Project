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
        char trace;
    public:
        Problem(char, char);
        Problem(int,char,char);
        bool checkBoard(Boards *);
        int findX(int&, Boards *);
        bool moveRight(Boards *);
        bool moveLeft(Boards *);
        bool moveDown(Boards *);
        bool moveUp(Boards *);
        bool solve(Boards *);
        int euclidean(Boards *);
        int findAPlace(Boards *,string,int &);
        int findGPlace(Boards *,string,int &);
        void sortQ(priority_queue<Boards *>);
        int misplaced(Boards *);
        int getExpand();
        int getMaxQ();
        int getSolD();
        void printBoard(Boards *);
        ~Problem();
};

#endif
