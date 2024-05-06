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


Problem::Problem(char s, char t) {
    algo = s;
    trace = t;
    vector<string> ans = {"1","2","3","4","5","6","7","8","x"};
    goal = new Boards(ans,3);
    solDepth = 0;
    expand = 0;
    maxQ = 0;
}

Problem::Problem(int size, char s, char t) {
    algo = s;
    trace = t;
    vector<string> ans;
    int num = 1;
    solDepth = 0;
    expand = 0;
    maxQ = 0;

    for (int i = 0; i < (size*size)-1; i++) {
        string temp = std::to_string(num);
        ans.push_back(temp);
        num++;
    }
    ans.push_back("x");
    goal = new Boards(ans,size);
}

Problem::~Problem() {
    delete goal;
}

// Checks if passed in board is goal board.
bool Problem::checkBoard(Boards *board) {
    if (goal->getString() != board->getString()) return false;
    return true;
}

// Finds blank space in board.
int Problem::findX(int &idx, Boards *board) {
    for (int i = 0; i < board->getSize(); i++) {
        for (int j = 0; j < board->getSize(); j++) {
            if (board->getNum(i,j) == "x") {    // If current tile is the blank space.
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

// Returns total boards expanded.
int Problem::getExpand() {
    return expand;
}

// Returns highest queue size recorded.
int Problem::getMaxQ() {
    return maxQ;
}

// Returns solution depth.
int Problem::getSolD() {
    return solDepth;
}

// Calculate euclidean heuristic.
int Problem::euclidean(Boards *board) {
    int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    int sum = 0;
    int temp = 1;
    string num = std::to_string(temp);

    for (int i = 0; i < board->getSize(); i++) {      
        for (int j = 0; j < board->getSize(); j++) {
            if (board->getNum(i,j) != num and board->getNum(i,j) != "x") {
                x1 = findGPlace(board,board->getNum(i,j),y1);     // x1,y1 = actual position for number.
                x2 = findAPlace(goal,board->getNum(i,j),y2);     // x2,y2 = goal position on board.
                sum += sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
            }
            temp++;
            num = std::to_string(temp);
        }
    }
    return sum;
}

// Calculate misplaced tile heuristic.
int Problem::misplaced(Boards *board) {
    int count = 0;
    for (int i = 0; i < board->getSize(); i++) {
        for (int j = 0; j < board->getSize(); j++) {
            if (board->getNum(i,j) != goal->getNum(i,j) and board->getNum(i,j) != "x")  // If actual tile doesnt match goal tile, increment count.
            count++;
        }
    }
    return count;
}

// Finds actual xy coordinate in board of a given number.
int Problem::findAPlace(Boards *board, string target, int &idx) {
    for (int i = 0; i < board->getSize(); i++) {
        for (int j = 0; j < board->getSize(); j++) {
            if (board->getNum(i,j) == target) {
                idx = j;    //return y2.
                return i;   //return x2.
            }
        }
    }
    return 0;
}

// Finds goal xy coordinate in board of a given number.
int Problem::findGPlace(Boards *board, string target, int &idx) {
    for (int i = 0; i < board->getSize(); i++) {
        for (int j = 0; j < board->getSize(); j++) {
            if (board->getNum(i,j) == target) {
                idx = j;    //return y2.
                return i;   //return x2.
            }
        }
    }
    return 0;
}

// Solves Problem.
bool Problem::solve(Boards *start) {
    priority_queue<Boards *, vector<Boards *>, Comp> boardQ;   // Queue of boards.
    unordered_set<string> uset;     // hash set to see if curr board has already been explored.

    boardQ.push(start);     // Pushes first board into queue.
    cout << "Starting board: \n";
    printBoard(start);

    while (true) {
        if (boardQ.empty()) return false;   // Check if queue is empty. Return false if it is.
        maxQ = (boardQ.size() > maxQ)? boardQ.size() : maxQ;    // Keep track of max queue size.
        Boards *temp = boardQ.top();   // Set temp boards var to the board at front of queue.
        boardQ.pop();   // Remove board at front of queue.
        if (checkBoard(temp)) {            
            cout << "Solved!\n";
            printBoard(temp);
            solDepth = temp->getDepth();    // Get solution depth.
            int qSize = boardQ.size();      // Get size of current queue.
            delete temp;    // Delete most recently popped board.
            for (int i = 0; i < qSize; i++) {   // Delete all remaining boards in queue.
                Boards *delBrd = boardQ.top();
                boardQ.pop();
                delete delBrd;
            }
            return true;  // Checks if current board is goal board and returns true if it is.
        }
        uset.insert(temp->getString());     // Marks current board as explored.
        expand++;   // Keep track of total expanded boards.
        if (trace == '1') {
            cout << "Expanding board from frontier with g(n) = " << temp->getDepth() << " and h(n) = " << temp->getHN() << "\n";
            printBoard(temp);
        }
        int i,j;    // Indices to keep track of where blank space is.
        Boards *test = nullptr;   // Child board of current board.
    
        // Begin moving numbers
        if (moveUp(temp)) {     // Checking if we can move up. 
            i = j = 0;  // Indices for the blank spot in board
            test = new Boards(temp->getVector(), temp->getSize());    // Copy parent board into child board.
            i = findX(j,temp);  // Find blank space in board.
            test->swapNums(i,j,i+1,j);  // Move number below blank space into blank space.
            if (!(uset.count(test->getString()))) {    // If we've already seen this board, skip.            
                uset.insert(test->getString()); // This board has not been seen.
                int hN = 0; // h(n) value
                if (algo == '3') {
                    hN = euclidean(test); // Calc euclidean heuristic if user chose to.
                }
                else if (algo == '2') {
                    hN = misplaced(test);   // Calc misplaced tile heuristic if user chose to.
                }  
                test->setDepth(temp->getDepth()+1);     // Set depth of new board as parent depth + 1.
                test->setPriority(test->getDepth(),hN); // Set priority of new board as g(n) + h(n).
                test->setHN(hN);    // Set h(n) value.
                boardQ.push(test);  // Push new board onto queue.
            }
            else {
                delete test;    // If we've seen this board already, delete.
            }
        }   // Checking if we can move left.
        if (moveLeft(temp)) {     // Checking if we can move left.
            i = j = 0;
            test = new Boards(temp->getVector(), temp->getSize());    // Copy current board into temp.
            i = findX(j,temp);  // Find blank space in board.
            test->swapNums(i,j,i,j+1);  // Move number to right of blank space into blank space.
            if (!(uset.count(test->getString()))) {    // If we've already seen this board, skip.          
                uset.insert(test->getString()); // This board has not been seen, so set as explored and do calcs.                
                int hN = 0; // h(n) value.
                if (algo == '3') {
                    hN = euclidean(test);   // Calc euclidean heuristic if user chose to.
                }
                else if (algo == '2') {
                    hN = misplaced(test);   // Calc misplaced tile heuristic if user chose to.
                }  
                test->setDepth(temp->getDepth()+1);     // Set depth of new board as parent depth + 1.
                test->setPriority(test->getDepth(),hN); // Set priority of new board as g(n) + h(n).
                test->setHN(hN);    // Set h(n) value.
                boardQ.push(test);  // Push new board onto queue.
            }
            else {
                delete test;    // If we've seen this board already, delete.
            }
        }
        if (moveRight(temp)) {    // Checking if we can move right. 
            i = j = 0;
            test = new Boards(temp->getVector(), temp->getSize());    // Copy current board into temp.
            i = findX(j,temp);  // Find blank space in board.
            test->swapNums(i,j,i,j-1);  // Move number to left of blank space into blank space.
            if (!(uset.count(test->getString()))) {    // If we've already seen this board, skip.      
                uset.insert(test->getString()); // This board has not been seen, so set as explored and do calcs.
                int hN = 0; // h(n) value.
                if (algo == '3') {
                    hN = euclidean(test);   // Calc euclidean heuristic if user chose to.
                }
                else if (algo == '2') {
                    hN = misplaced(test);   // Calc misplaced tile heuristic if user chose to.
                }  
                test->setDepth(temp->getDepth()+1);     // Set depth of new board as parent depth + 1.
                test->setPriority(test->getDepth(),hN); // Set priority of new board as g(n) + h(n).
                test->setHN(hN);    // Set h(n) value.
                boardQ.push(test);  // Push new board onto queue.
            }
            else {
                delete test;    // If we've seen this board already, delete.
            }
        }  
        if (moveDown(temp)) {    // Checking if we can move down.
            i = j = 0;
            test = new Boards(temp->getVector(), temp->getSize());    // Copy current board into temp.
            i = findX(j,temp);  // Find blank space in board.
            test->swapNums(i,j,i-1,j);  // Move number above blank space into blank space.
            if (!(uset.count(test->getString()))) {    // If we've already seen this board, skip.
                uset.insert(test->getString()); // This board has not been seen, so set as explored and do calcs.
                int hN = 0; // h(n) value.
                if (algo == '3') {
                    hN = euclidean(test);   // Calc euclidean heuristic if user chose to.
                }
                else if (algo == '2') {
                    hN = misplaced(test);   // Calc misplaced tile heuristic if user chose to.
                }  
                test->setDepth(temp->getDepth()+1);     // Set depth of new board as parent depth + 1.
                test->setPriority(test->getDepth(),hN); // Set priority of new board as g(n) + h(n).
                test->setHN(hN);    // Set h(n) value.
                boardQ.push(test);  // Push new board onto queue.
            }
            else {
                delete test;    // If we've seen this board already, delete.
            }
        }
        delete temp;
    }
    return true;
}