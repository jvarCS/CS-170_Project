#include "../header/problem.h"
#include <string>
#include <iostream>
#include <cmath>
#include <queue>
#include <unordered_set>
#include <algorithm>

using std::cout;
using std::priority_queue;
using std::unordered_set;
using std::endl;


Problem::Problem(char s) {
    algo = s;
    string ans = "12345678x";
    goal = new Boards(ans,3);
    solDepth = 0;
    expand = 0;
    maxQ = 0;
}

Problem::Problem(int size, char s) {
    algo = s;
    string ans = "";
    int num = 1;
    solDepth = 0;
    expand = 0;
    maxQ = 0;

    for (int i = 0; i < (size*size)-1; i++) {
        ans += std::to_string(num);
        num++;
    }
    ans += 'x';
    goal = new Boards(ans,size);
}

Problem::~Problem() {
    delete goal;
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
    return 0;
}

void Problem::printBoard(Boards *board) {
    for (int i = 0; i < board->getSize(); i++) {
        for (int j = 0; j < board->getSize(); j++)
            cout << board->getNum(i,j) << " ";
        cout << "\n";
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

// Determines if there is a number above blank space that can be moved down into blank space.
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

int Problem::getExpand() {
    return expand;
}

int Problem::getMaxQ() {
    return maxQ;
}

int Problem::getSolD() {
    return solDepth;
}

int Problem::euclidean(Boards *board) {
    int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    int sum = 0;
    char num = '1';

    for (int i = 0; i < board->getSize(); i++) {      
        for (int j = 0; j < board->getSize(); j++) {
            if (board->getNum(i,j) != num and board->getNum(i,j) != 'x') {
                //cout << i << " " << j << "\n";
                x1 = findGPlace(board,board->getNum(i,j),y1);     // x1,y1 = actual position for number
                x2 = findAPlace(goal,board->getNum(i,j),y2);     // x2,y2 = goal position on board
                //cout << "x1 : " << x1 << " y1: " << y2 << " \n";
                //cout << "x2 : " << x2 << " y2: " << y2 << " \n";
                sum += sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
            }
            num++;
        }
    }
   // cout << sum << " ";
    return sum;
}

int Problem::misplaced(Boards *board) {
    int count = 0;
    for (int i = 0; i < board->getSize(); i++) {
        for (int j = 0; j < board->getSize(); j++) {
            if (board->getNum(i,j) != goal->getNum(i,j) and board->getNum(i,j) != 'x')
            count++;
        }
    }
    return count;
}

// Finds actual xy coordinate in board of a given number
int Problem::findAPlace(Boards *board, char target, int &idx) {
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
int Problem::findGPlace(Boards *board, char target, int &idx) {
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
    priority_queue<Boards *, vector<Boards *>, Comp> boardQ;   // Queue of boards.
    unordered_set<string> uset;     // hash set to see if curr board has already been explored.

    boardQ.push(start);     // Pushes first board into queue.
    cout << "Starting board: \n";
    printBoard(start);

    while (true) {
        if (boardQ.empty()) return false;   // Check if queue is empty. Return false if it is.
        maxQ = (boardQ.size() > maxQ)? boardQ.size() : maxQ;
        Boards *temp = boardQ.top();   // Set temp boards var to the board at front of queue.
        boardQ.pop();   // Remove board at front of queue.
        if (checkBoard(temp)) {            
            cout << "Solved!\n";
            printBoard(temp);
            solDepth = temp->getDepth();
            int roa = boardQ.size();
            delete temp;
            for (int i = 0; i < roa; i++) {
                Boards *delBrd = boardQ.top();
                boardQ.pop();
                delete delBrd;
            }
            return true;  // Checks if current board is goal board and returns true if it is.
        }
        uset.insert(temp->getString());     // Marks current board as explored.
        // Expand current board. Here is where the diff search algos will be called.
        expand++;
        //cout << "Expanding board from frontier with g(n) = " << temp->getDepth() << " and h(n) = " << temp->getHN() << "\n";
        //printBoard(temp);
        int expdCount = 0, i,j;
        Boards *test = nullptr;   // Child board of current board.
        ////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////
        // BEGIN MOVING BOARD/////////////////
        if (moveUp(temp)) {     // CHECKING IF WE CAN MOVE UP ////////////////////////////////////////////////////
        //cout << "up\n";
            i = j = 0;  // Indices for the blank spot in board
            test = new Boards(temp->getString(), temp->getSize());    // Copy current board into temp.
            i = findX(j,temp);  // Find blank space in board.
            test->swapNums(i,j,i+1,j);  // Move number below blank space into blank space.
            if (!(uset.count(test->getString()))) {    // If we've already seen this board, dont perform euc calcs and skip.            
                uset.insert(test->getString()); // This board has not been seen.
                int hN = 0;
                if (algo == '3') {
                    hN = euclidean(test); 
                }
                else if (algo == '2') {
                    hN = misplaced(test);
                }  
                test->setDepth(temp->getDepth()+1);
               // cout << "hn " << hN << ":" << test->getDepth()+hN << "\n";
                test->setPriority(test->getDepth(),hN);
                test->setHN(hN);
                boardQ.push(test);
            }
            else {
              //  cout << "UP DELETE\n";
                delete test;
             //   cout << "UP DELETE DONE\n";
            }
        }   // CHECKING IF WE CAN MOVE LEFT ////////////////////////////////////////////////////
        if (moveLeft(temp)) {     // CHECKING IF WE CAN MOVE DOWN
        //cout << "left\n";
            i = j = 0;
            test = new Boards(temp->getString(), temp->getSize());    // Copy current board into temp.
            i = findX(j,temp);  // Find blank space in board.
            test->swapNums(i,j,i,j+1);  // Move number below blank space into blank space.
            if (!(uset.count(test->getString()))) {    // If we've already seen this board, dont perform euc calcs and skip.          
                uset.insert(test->getString()); // This board has not been seen, so set as explored and do calcs.                
                int hN = 0;
                if (algo == '3') {
                    hN = euclidean(test); 
                }
                else if (algo == '2') {
                    hN = misplaced(test);
                }  
                test->setDepth(temp->getDepth()+1);
                //cout << "hn " << hN << ":" << test->getDepth()+hN << "\n";
                test->setPriority(test->getDepth(),hN);
                test->setHN(hN);
                boardQ.push(test);
            }
            else {
               // cout << "LEFT DELETE\n";
                delete test;
               // cout << "LEFT DELETE DONEE\n";
            }
        }   // CHECKING IF WE CAN MOVE RIGHT ////////////////////////////////////////////////////
        if (moveRight(temp)) {     
       // cout << "right\n";
            i = j = 0;
            test = new Boards(temp->getString(), temp->getSize());    // Copy current board into temp.
            i = findX(j,temp);  // Find blank space in board.
            test->swapNums(i,j,i,j-1);  // Move number below blank space into blank space.
            if (!(uset.count(test->getString()))) {    // If we've already seen this board, dont perform euc calcs and skip.      
                uset.insert(test->getString()); // This board has not been seen, so set as explored and do calcs.
                int hN = 0;
                //cout << "ALGO IS " << algo << endl;
                if (algo == '3') {
                    hN = euclidean(test); 
                }
                else if (algo == '2') {
                    hN = misplaced(test);
                }  
                //cout << "THISRIGHT HERE " << hN;
                test->setDepth(temp->getDepth()+1);
                //cout << "hn " << hN << ":" << test->getDepth()+hN << "\n";
                test->setPriority(test->getDepth(),hN);
                test->setHN(hN);
                boardQ.push(test);
            }
            else {
              //  cout << "RIGHT DELETE\n";
                delete test;
              //  cout << "RIGHT DELETE DONEE\n";
            }
        }   // CHECKING IF WE CAN MOVE DOWN ////////////////////////////////////////////////////
        if (moveDown(temp)) {    
        //cout << "down\n";
            i = j = 0;
            test = new Boards(temp->getString(), temp->getSize());    // Copy current board into temp.
            i = findX(j,temp);  // Find blank space in board.
            //cout << "TEEHEE";
            test->swapNums(i,j,i-1,j);  // Move number below blank space into blank space.
            //cout << "TEEHEE";
            if (!(uset.count(test->getString()))) {    // If we've already seen this board, dont perform euc calcs and skip.
                uset.insert(test->getString()); // This board has not been seen, so set as explored and do calcs.
                int hN = 0;
                if (algo == '3') {
                    hN = euclidean(test); 
                }
                else if (algo == '2') {
                    hN = misplaced(test);
                }  
                test->setDepth(temp->getDepth()+1);
                //cout << "hn " << hN << ":" << test->getDepth()+hN << "\n";
                test->setPriority(test->getDepth(),hN);
                test->setHN(hN);
                boardQ.push(test);
            }
            else {
              //  cout << "DOWN DELETE\n";
                delete test;
              //  cout << "DOWN DELETE DONEE\n";
            }
        }
        //cout << "THIS MF DELETE\n";
        delete temp;
        //cout << "THIS MF DELETE DONEENE\n";
    }
    return true;
}