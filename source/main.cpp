#include <iostream>
#include "../header/boards.h"
#include <cmath>
#include <queue>
#include <unordered_set>

using namespace std;

void UCS();
bool checkBoard(Boards);
float euclidean(char **);
int findPlace(char **, char, float &);
void eucStar();
bool solve(Boards);
string makeString(Boards); 
float findGPlace(char **, char, float &);

int main() {
    /*char *arr = new char(10);
    arr[0] = '8';
    arr[1] = '2';
    arr[2] = '3';
    arr[3] = '4';
    arr[4] = '5';
    arr[5] = '6';
    arr[6] = '7';
    arr[7] = '8';
    arr[8] = 'x';*/
    Boards start;

    start.print();

    //delete []arr;
    return 0;
}

bool solve(Boards start) {
    int moves = 0;  // Total moves.
    queue<Boards> boardQ;   // Queue of boards.
    unordered_set<string> uset;     // hash set to see if curr board has already been explored.

    boardQ.push(start);     // Pushes first board into queue.

    while (true) {
        if (boardQ.empty()) return false;   // Check if queue is empty. Return false if it is.
        Boards temp = boardQ.front();   // Set temp boards var to the board at front of queue.
        boardQ.pop();   // Remove board at front of queue.
        if (checkBoard(temp)) return true;  // Checks if current board is goal board.
        uset.insert(makeString(temp));     // Marks current board as explored.
        // Expand current board. Here is where the diff search algos will be called.
        // In each, their diff priority reqs will be calc as well, i.e, in eucStar, calc
        // priority as euclidean distance + total number of moves. In UCS, just total moves.
        
    }
}

void UCS() {

}


void eucStar(char **arr) {

}

bool checkBoard(Boards board) {
    char num = '1';
    for (int i = 0; i < 3; i++) {       // Hardcoded size to 3 here. Change later
        for (int j = 0; j < 3; j++) {
            if (board.getNum(i,j) != num and board.getNum(i,j) != 'x') return false;
            num++;
        }
    }
    return true;
}

// Calculates euclidean distance of current board
float euclidean(char **arr) {
    int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    float sum = 0;
    char num = '1';

    for (int i = 0; i < 3; i++) {       // Hardcoded size to 3 here. Change later
        for (int j = 0; j < 3; j++) {
            if (arr[i][j] != num and arr[i][j] != 'x') {
                x1 = i; y2 = j;     // x1,y1 = goal position for number
                x2 = findPlace(arr,num,y2);     // x2,y2 = actual position on board
                sum += sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
            }
            num++;
        }
    }

}

// Finds actual xy coordinate in board of a given number
int findPlace(char **arr, char target, int &idx) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (arr[i][j] == target) {
                idx = j;    //return y2
                return i;   //return x2
            }
        }
    }
}

// Finds goal xy coordinate in board of a given number
float findGPlace(char arr[3][3], char target, float &idx) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (arr[i][j] == target) {
                idx = j;    //return y2
                return i;   //return x2
            }
        }
    }

    return 0;
}


string makeString(Boards board) {
    string numbers;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            numbers += board.getNum(i,j);
        }
    }

    return numbers;
}
