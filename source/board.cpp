#include "../header/board.h"

using std::cout;

Board::Board() {
    board[0] = '8';     // 8 4 1
    board[1] = '4';     
    board[2] = '1';
    board[3] = '2';     // 2 5 6
    board[4] = '5';
    board[5] = '6';
    board[6] = '3';     // 3 7 x
    board[7] = '7';
    board[8] = 'x';
}

Board::Board(char *nums) {
    board[0] = nums[0];
    board[1] = nums[1];
    board[2] = nums[2];
    board[3] = nums[3];
    board[4] = nums[4];
    board[5] = nums[5];
    board[6] = nums[6];
    board[7] = nums[7];
    board[8] = nums[8];
}

void Board::print() {
    for (int i = 0; i < 9; i++) {
        cout << board[i] << " ";
    }
}