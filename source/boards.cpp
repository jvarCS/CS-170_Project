#include "../header/boards.h"
#include <string>

using std::cout;
using std::string;

Boards::Boards() {
    size = 3;
    board = new char*[size];
    depth = 0;

    for (int i = 0; i < size; i++) board[i] = new char[size];    

    board[0][0] = '8';     // 8 4 1
    board[0][1] = '4';     
    board[0][2] = '1';
    board[1][0] = '2';     // 2 5 6
    board[1][1] = '5';
    board[1][2] = '6';
    board[2][0] = '3';     // 3 7 x
    board[2][1] = '7';
    board[2][2] = 'x';
}

Boards::Boards(string nums, int len) {
    size = len;
    board = new char*[size];
    depth = 0;

    for (int i = 0; i < size; i++)  board[i] = new char[size];    

    for (int i = 0, k = 0; i < size; i++) {
        for (int j = 0; j < size; j++, ++k)
        board[i][j] = nums[k];
    } 
}

void Boards::print() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
        cout << board[i][j] << " ";
    }
}

char Boards::getNum(int i,int j) {
    return board[i][j];
}

void Boards::setSize(int num) {
    size = num;
}

int Boards::getSize() {
    return size;
}

string Boards::getString() {
    string brdString = "";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            brdString += board[i][j];
        }
    }
    return brdString;
}

void Boards::swapNums(int i,int j,int m,int n) {
    char temp = board[i][j];
    board[i][j] = board[m][n];
    board[m][n] = board[i][j];
}

void Boards::setPriority(int gN, int hN) {
    priority = gN + hN;
}

void Boards::setDepth(int d) {
    depth = d;
}

int Boards::getDepth() {
    return depth;
}