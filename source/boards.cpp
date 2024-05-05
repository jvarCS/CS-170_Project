#include "../header/boards.h"

using std::cout;

Boards::Boards() {
    board[0][0] = '8';     // 8 4 1
    board[0][1] = '4';     
    board[0][2] = '1';
    board[1][3] = '2';     // 2 5 6
    board[1][4] = '5';
    board[1][5] = '6';
    board[2][6] = '3';     // 3 7 x
    board[2][7] = '7';
    board[2][8] = 'x';
}

Boards::Boards(char **nums) {
    board[0][0] = nums[0][0];
    board[0][1] = nums[0][1];
    board[0][2] = nums[0][2];
    board[1][3] = nums[1][3];
    board[1][4] = nums[1][4];
    board[1][5] = nums[1][5];
    board[2][6] = nums[2][6];
    board[2][7] = nums[2][7];
    board[2][8] = nums[2][8];
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

void Boards::moveNumber() {
    
}