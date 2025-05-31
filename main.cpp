/**
 * @file main.cpp
 * @brief Contains the main function that starts the infection simulation.
 *
 * @author Josh Forbes
 * @date November 2023
 **/

#include <iostream>
#include <cstdlib>

// Board.h needs to be included here because we create a Board
// object below.
#include "Board.h"

using namespace std;

/**
 * @fn main()
 * @brief main function that starts the simulation running
 * The main function does the following:
 * (1) seeds the random number generator
 * (2) creates a board object that is 20 rows, 80 columns, 70 humans
 * (3) starts the simulation running by calling the board's run function.
 **/
int main() {
    // Only seed the random number generator once!
    srandom( time(NULL) );

    // Promt the user what the simulation does and changed
    cout << "This program changed the human class into pokemon trainers and ragners." << endl
        << "The two are competing to catch the most pokemon which is the new class." << endl << endl
        << "The pokemon don't all get caught though, as there is a pokemon center" << endl
        << "which is a safe zone for the pokemon. " << endl
        << "The pokemon center is on the left hand side of the screen and has a " << endl
        << "special function that will heal the pokemon that have been caught." << endl << endl
        << "The red T are the trainers, the blue R are the rangers, and the green P are the pokemon." << endl
        << "Trainers and rangers will both start with 4 members and the Pokemon will start with 50 members." << endl
        << "This is a total of 58 objects!" << endl;

    char move_on;
    cout << "Run simulator?[y][n] ";
    cin >> move_on;
    if(move_on == 'y' or move_on == 'Y'){
        Board board(30, 100, 8, 50);
        board.run();
    }
    else {
        cout << "You didn't run the simulator" << endl;
    }

    return 0;
}
