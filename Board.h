//----------------------------------------------------
// The "#ifndef ..." and "#define ..." lines are used to prevent the compiler from accidentally
// processing the contents of Board.h more than once, thus causing "Board redefined" errors.
// At the end of the file is a "#endif" which marks the end of the "#ifndef" section.
//----------------------------------------------------
#ifndef BOARD_H
#define BOARD_H

/**
 * @file Board.h
 * @brief the Board class declaration file
 *
 * @author Stefan Brandle
 * @author Josh Forbes and Jackson Dahlin
 * @date November 2023
 */

//----------------------------------------------------
// "forward" declaration of Board. Tell the compiler that this will be
// defined properly further "forward" in the program. This is needed because
// both classes reference each other. Otherwise, when include "Human.h" and 
// the compiler finds a reference to Board, it will complain.
//----------------------------------------------------
class Board;

// The Board class uses the Human class, so must include the Human class declaration.
#include "Human.h"
#include "Pokemon.h"

using namespace std;

/**
 * @class Board
 * @brief The Board class declaration.
 */
class Board {
  public:
    Board(int numRows, int numCols, int numHumans, int numPokemon); // Board class constructor
    ~Board();                 // Board class destructor
    void run();               // Main function that runs the simulation
    bool tryMove(int row, int col, char x); // Function that lets human know whether move is ok
    static const int MAX_HUMAN_COUNT = 100; // Maximum humans simulation can handle
    static const int MAX_POKEMON_COUNT = 100; //Maximum pokemon simulation can handle

  protected:
    //----------------------------------------------------
    // Private functions and data. These cannot be referenced other than by functions that are
    // part of the Board class.
    //----------------------------------------------------
    void processInfection();                        // Go through and process infection status
    bool allInfected();                             // Tells whether all humans are infected
    bool isNextTo(Pokemon* p, Human* h);            // Tells whether a pokemon is next to a human
    bool isNextToPoke(Pokemon* p1, Pokemon* p2);    // Tells whether a pokemon is next to a pokemon
    void drawCenter();                              // Drawls and prints pokemon center
    bool checkCenter(int row, int col);             // Checks to see if a pokemon is in the center

    Human* humans[MAX_HUMAN_COUNT];         //array holding humans
    Pokemon* pokemons[MAX_POKEMON_COUNT];   //array holding pokemons
    int numHumans;            // Num humans
    int numPokemon;           // Num pokemon
    int numTrainerCaught;     // Num pokemon the trainers caught
    int numRangerCaught;      // Num pokemon the rangers caught
    int numPokemonSafe;       // Num of pokemon not infected
    int numPokemonFree;       // Num of pokemon on board that aren't caught

    int currentTime;          // Current time in simulation
    int numRows;              // Number of rows in board
    int numCols;              // Number of cols in board
    int uSleepTime;           // Num microseconds to sleep between updates
};

#endif //#ifndef BOARD_H
