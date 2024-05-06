#include "../header/boards.h"
#include <string>

using std::cout;
using std::string;

Boards::Boards() {
    size = 3;
    board = new string*[size];
    depth = 0;
    hOn = 0;
    priority = 0;

    for (int i = 0; i < size; i++) board[i] = new string[size];    

    board[0][0] = "8";    
    board[0][1] = "7";     
    board[0][2] = "1";
    board[1][0] = "6";     
    board[1][1] = "x";
    board[1][2] = "2";
    board[2][0] = "5";     
    board[2][1] = "4";
    board[2][2] = "3";
}

Boards::Boards(vector<string> nums, int len) {
    size = len;
    board = new string*[size];
    depth = 0;
    hOn = 0;
    priority = 0;

    for (int i = 0; i < size; i++)  board[i] = new string[size];    

    // Set board tiles equal to user chosen board. 
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

// Returns tile.
string Boards::getNum(int i,int j) {
    return board[i][j];
}

void Boards::setSize(int num) {
    size = num;
}

int Boards::getSize() {
    return size;
}

// Returns boards tiles as a vector.
vector<string> Boards::getVector() {
    vector<string> temp;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            temp.push_back(board[i][j]);
        }
    }
    return temp;
}

// Returns boards tiles as a string.
string Boards::getString() {
    string brdString = "";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            brdString += board[i][j];
        }
    }
    return brdString;
}

// Swaps tile and blank space during a move.
void Boards::swapNums(int i,int j,int m,int n) {
    string temp = board[i][j];
    board[i][j] = board[m][n];
    board[m][n] = temp;
}

// Sets this boards priority.
void Boards::setPriority(int gN, int hN) {
    hOn = hN;
    priority = gN + hN;
}

// Returns this boards priority.
int Boards::getPriority() {
    return priority;
}

// Sets this boards depth.
void Boards::setDepth(int d) {
    depth = d;
}

// Returns this boards depth.
int Boards::getDepth() {
    return depth;
}

// Returns this boards h(n).
int Boards::getHN() {
    return hOn;
}

// Sets h(n) for this board.
void Boards::setHN(int num) {
    hOn = num;
}