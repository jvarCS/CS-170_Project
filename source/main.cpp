#include <iostream>
#include "../header/boards.h"
#include "../header/problem.h"
#include <cmath>
#include <queue>
#include <unordered_set>

using namespace std;

Problem *menu(Boards **);

int main() {
    Boards *start;
    Problem *game = menu(&start);
    if (game->solve(start)) {
        cout << "-----------------------------------------------------------------------------------\n"
             << "Solving this problem required a total of " << game->getExpand() << " boards to be expanded.\n"
             << "Max nodes in queue overall was " << game->getMaxQ() << ".\n"
             << "Depth of goal board was " << game->getSolD();
    }
    else {
        cout << "Board could not be solved.\n";
    }

   // cout << "GAME DELETE\n";
    delete game;
    //cout << "GAME DELETE DONE\n";

    //cout << "YOLOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n";
    return 0;
}

Problem *menu(Boards **start) {
    char choice, algo, trace;
    cout << "Welcome to 862242193 8 puzzle solver.\n"
         << "Enter '1' to use Uniform Search Cost, '2' for Misplace Tile A*, '3' for Euclidean A*\n";
    cin  >> algo;
    cout << "Enter '1' to use default puzzle, or '2' to enter your own puzzle.\n";
    cin  >> choice;
    cout << "Enter '1' to solve showing all boards (Slower), or '2' to only show starting and goal (Much faster).\n";
    cin  >> trace;
    
    // If user enters 1, we use default board size and numbering
    if (choice == '1') {
        Problem *ex = new Problem(algo, trace);
        *start = new Boards();
        return ex;
    }
    else if (choice == '2') {   // User entered 2 so we use customized board
        int size;   // Get NxN size
        vector<string> nums;    // Get start ordering of numbers
        string temp;
        cout << "The board will be of NxN measurement. Please enter the value for N.\n";
        cin >> size;
        Problem *ex = new Problem(size,algo,trace);   // Create Problem instance
        cout << "Enter the numbers in the desired order one by one, with 'x' representing the blank space.\n"
             << "Example: 123\n"
             << "         456\n"
             << "         78x\n"
             << "for a 3x3 board would be entered as '1' 'ENTER' '2' 'ENTER' etc'.\n";
        for (int i = 0; i < size*size; i++) {
            cin >> temp;
            nums.push_back(temp);
        }
        *start = new Boards(nums,size); // Create startin board
        return ex;
    }
    return nullptr;
}
