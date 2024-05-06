#include "../header/problem.h"
#include <string>
#include <iostream>
#include <cmath>
#include <queue>
#include <unordered_set>

using std::cout;
using std::queue;
using std::unordered_set;


Problem::Problem(char s) {
    algo = s;
    gN = 0;
    string ans = "12345678x";
    goal = new Boards(ans,3);
}

Problem::Problem(int size, char s) {
    algo = s;
    gN = 0;
    string ans = "";
    int num = 1;

    for (int i = 0; i < (size*size)-1; i++) {
        ans += std::to_string(num);
        num++;
    }
    ans += 'x';
    goal = new Boards(ans,size);
}

bool Problem::checkBoard(Boards *board) {
    if (goal->getString() != board->getString()) return false;
    return true;
}

int Problem::findX(int &idx, Boards *board) {
    for (int i = 0; i < board->getSize(); i++) {
        for (int j = 0; j < board->getSize(); j++) {
            if (board->getNum(i,j) == 'x') {
                idx = j;
                return i;
            }
        }
    }
}

// Determines if there is a number to the right of blank space that can be moved left into x.
bool Problem::moveLeft(Boards *board) {
    int x,y;
    x = findX(y,board);
    if (y == board->getSize()-1) return false;
    return true;
}

// Determines if there is a number to the left of blank space that can be moved right into blank space.
bool Problem::moveRight(Boards *board) {
    int x,y;
    x = findX(y,board);
    if (y == 0) return false;
    return true;
}

// Determines if there is a number to above blank space that can be moved down into blank space.
bool Problem::moveDown(Boards *board) {
    int x,y;
    x = findX(y,board);
    if (x == 0) return false;
    return true;
}

// Determines if there is a number below blank space that can be moved up into blank space.
bool Problem::moveUp(Boards *board) {
    int x,y;
    x = findX(y,board);
    if (x == board->getSize()-1) return false;
    return true;
}

float Problem::euclidean(Boards *board) {
    float x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    float sum = 0;
    char num = '0';

    for (int i = 0; i < 3; i++) {       // Hardcoded size to 3 here. Change later
        for (int j = 0; j < 3; j++) {
            if (board->getNum(i,j) != num and board->getNum(i,j) != 'x') {
                x1 = findGPlace(board,board->getNum(i,j),y1);     // x1,y1 = goal position for number
                x2 = findAPlace(board,board->getNum(i,j),y2);     // x2,y2 = actual position on board
                sum += sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
            }
            num++;
        }
    }
    return sum;
}

// Finds actual xy coordinate in board of a given number
int Problem::findAPlace(Boards *board, char target, float &idx) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board->getNum(i,j) == target) {
                idx = j;    //return y2
                return i;   //return x2
            }
        }
    }
    return 0;
}

// Finds goal xy coordinate in board of a given number
int Problem::findGPlace(Boards *board, char target, float &idx) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board->getNum(i,j) == target) {
                idx = j;    //return y2
                return i;   //return x2
            }
        }
    }
    return 0;
}



bool Problem::solve(Boards *start) {
    queue<Boards *> boardQ;   // Queue of boards.
    unordered_set<string> uset;     // hash set to see if curr board has already been explored.

    boardQ.push(start);     // Pushes first board into queue.

    while (true) {
        if (boardQ.empty()) return false;   // Check if queue is empty. Return false if it is.
        Boards *temp = boardQ.front();   // Set temp boards var to the board at front of queue.
        boardQ.pop();   // Remove board at front of queue.
        if (checkBoard(temp)) return true;  // Checks if current board is goal board and returns true if it is.
        uset.insert(temp->getString());     // Marks current board as explored.
        // Expand current board. Here is where the diff search algos will be called.
        bool expanding = true, up = true, down = true, left = true, right = true;
        int expdCount = 0, i,j;
        Boards *test = nullptr;   // Child board of current board.
        while (expanding) {
            if (moveUp(start) and up) {     // CHECKING IF WE CAN MOVE UP
                i = j = 0;  // Indices for the blank spot in board
                test = new Boards(temp->getString(), temp->getSize());    // Copy current board into temp.
                i = findX(j,temp);  // Find blank space in board.
                test->swapNums(i,j,i-1,j);  // Move number below blank space into blank space.
                if (uset.count(temp->getString())) {    // If we've already seen this board, dont perform euc calcs and skip.
                    up = false;
                    continue;
                }
                uset.insert(test->getString()); // This board has not been seen.
                int hN = 0;
                if (algo == '3') {
                    hN = euclidean(test); 
                }
                else if (algo == '2') {
                    // hN = ENTER MISPLACED TILE FUNCTION HERE 
                }  
                up = false;
                test->setDepth(temp->getDepth()+1);
                test->setPriority(test->getDepth(),hN);
                boardQ.push(test);
            }
            if (moveLeft(start) and left) {     // CHECKING IF WE CAN MOVE DOWN
                i = j = 0;
                test = new Boards(temp->getString(), temp->getSize());    // Copy current board into temp.
                i = findX(j,temp);  // Find blank space in board.
                test->swapNums(i,j,i-1,j);  // Move number below blank space into blank space.
                if (uset.count(temp->getString())) {    // If we've already seen this board, dont perform euc calcs and skip.
                    left = false;
                    continue;
                }
                uset.insert(test->getString()); // This board has not been seen, so set as explored and do calcs.                
                int hN = 0;
                if (algo == '3') {
                    hN = euclidean(test); 
                }
                else if (algo == '2') {
                    // hN = ENTER MISPLACED TILE FUNCTION HERE 
                }  
                left = false;
                test->setDepth(temp->getDepth()+1);
                test->setPriority(test->getDepth(),hN);
                boardQ.push(test);
            }
            if (moveRight(start) and right) {     // CHECKING IF WE CAN MOVE LEFT
                i = j = 0;
                test = new Boards(temp->getString(), temp->getSize());    // Copy current board into temp.
                i = findX(j,temp);  // Find blank space in board.
                test->swapNums(i,j,i-1,j);  // Move number below blank space into blank space.
                if (uset.count(temp->getString())) {    // If we've already seen this board, dont perform euc calcs and skip.
                    right = false;
                    continue;
                }
                uset.insert(test->getString()); // This board has not been seen, so set as explored and do calcs.
                int hN = 0;
                if (algo == '3') {
                    hN = euclidean(test); 
                }
                else if (algo == '2') {
                    // hN = ENTER MISPLACED TILE FUNCTION HERE 
                }  
                right = false;
                test->setDepth(temp->getDepth()+1);
                test->setPriority(test->getDepth(),hN);
                boardQ.push(test);
            }
            if (moveDown(start) and up) {     // CHECKING IF WE CAN MOVE RIGHT
                i = j = 0;
                test = new Boards(temp->getString(), temp->getSize());    // Copy current board into temp.
                i = findX(j,temp);  // Find blank space in board.
                test->swapNums(i,j,i-1,j);  // Move number below blank space into blank space.
                if (uset.count(temp->getString())) {    // If we've already seen this board, dont perform euc calcs and skip.
                    down = false;
                    continue;
                }
                uset.insert(test->getString()); // This board has not been seen, so set as explored and do calcs.
                int hN = 0;
                if (algo == '3') {
                    hN = euclidean(test); 
                }
                else if (algo == '2') {
                    // hN = ENTER MISPLACED TILE FUNCTION HERE 
                }  
                down = false;
                test->setDepth(temp->getDepth()+1);
                test->setPriority(test->getDepth(),hN);
                boardQ.push(test);
            }
            if (!up and !left and !right and !down) expanding = false;
        }
        // In each, their diff priority reqs will be calc as well, i.e, in eucStar, calc
        // priority as euclidean distance + total number of moves. In UCS, just total moves.
        
    }

    return true;
}