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
    char choice, algo;
    cout << "Welcome to 862242193 8 puzzle solver.\n"
         << "Enter '1' to use Uniform Search Cost, '2' for Misplace Tile A*, '3' for Euclidean A*\n";
    cin  >> algo;
    cout << "Enter '1' to use default puzzle, or '2' to enter your own puzzle.\n";
    cin  >> choice;
    
    // If user enters 1, we use default board size and numbering
    if (choice == '1') {
        Problem *ex = new Problem(algo);
        *start = new Boards();
        return ex;
    }
    else if (choice == '2') {   // User entered 2 so we use customized board
        int size;   // Get NxN size
        string nums;    // Get start ordering of numbers
        cout << "The board will be of NxN measurement. Please enter the value for N.\n";
        cin >> size;
        Problem *ex = new Problem(size,algo);   // Create Problem instance
        cout << "Enter the numbers in the desired order, with 'x' representing the blank space.\n"
             << "Example: 123\n"
             << "         456\n"
             << "         78x\n"
             << "for a 3x3 board would be entered as '12345678x'.\n";
        cin >> nums;
        *start = new Boards(nums,size); // Create startin board
        return ex;
    }
    return nullptr;
}
