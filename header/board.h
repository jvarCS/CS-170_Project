#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>

using std::vector;

class Board {
    private: 
        int size;
        char board[10];
    public:
        Board();
        Board(char *);
        void print();
        //Board()
};


#endif
