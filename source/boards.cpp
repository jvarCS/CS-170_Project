#include "../header/boards.h"
#include <string>

using std::cout;
using std::string;

Boards::Boards() {
    size = 3;
    board = new char*[size];
    depth = 0;
    hOn = 0;
    priority = 0;

    for (int i = 0; i < size; i++) board[i] = new char[size];    

    board[0][0] = '8';     // 8 4 1
    board[0][1] = '7';     
    board[0][2] = '1';
    board[1][0] = '6';     // 2 5 6
    board[1][1] = 'x';
    board[1][2] = '2';
    board[2][0] = '5';     // 3 7 x
    board[2][1] = '4';
    board[2][2] = '3';
}

Boards::Boards(string nums, int len) {
    size = len;
    board = new char*[size];
    depth = 0;
    hOn = 0;
    priority = 0;

    for (int i = 0; i < size; i++)  board[i] = new char[size];    

    for (int i = 0, k = 0; i < size; i++) {
        for (int j = 0; j < size; j++, ++k)
        board[i][j] = nums[k];
    } 
}

Boards::~Boards() {
    for (int i = 0; i < size; i++) {
        delete[] board[i];
    }
    delete[] board;
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
    board[m][n] = temp;
}

void Boards::setPriority(int gN, int hN) {
    hOn = hN;
    priority = gN + hN;
}

int Boards::getPriority() {
    return priority;
}

void Boards::setDepth(int d) {
    depth = d;
}

int Boards::getDepth() {
    return depth;
}

int Boards::getHN() {
    return hOn;
}
void Boards::setHN(int num) {
    hOn = num;
}