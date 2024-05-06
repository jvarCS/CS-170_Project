#ifndef BOARDS_H
#define BOARDS_H

#include <vector>
#include <iostream>

using std::vector;

class Boards {
    private: 
        int size;
        float priority;
        int depth;
        char **board;
    public:
        Boards();
        Boards(string, int);
        void setSize(int);
        int getSize();
        void print();
        char getNum(int,int);
        string getString();
        void swapNums(int,int,int,int);
        void setPriority(int,int);
        void setDepth(int);
        int getDepth();
        //Board()
};


#endif
