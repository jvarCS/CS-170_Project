#ifndef BOARDS_H
#define BOARDS_H

#include <vector>
#include <iostream>

using std::vector;
using std::string;

class Boards {
    private: 
        int size;
        int priority;
        int depth;
        int hOn;
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
        int getPriority();
        void setDepth(int);
        int getDepth();
        int getHN();
        void setHN(int);
        ~Boards();
};


#endif
