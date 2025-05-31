/**
  *@file Pokemon.cpp
  *@brief The Pokemon class implementation file.
  *
  *@author Josh Forbes
  *@date November 2023
  */

#include <cstdlib>
#include <iostream>

#include "Pokemon.h"
#include "Human.h"
#include "conio.h"

using namespace std;

/**
 * @brief The Pokemon class constructor.
 * This function initializes the row, col, infected, board, id, and if its acitve.
 *
 * @param inRow the initial pokemon row location.
 * @param inCol the initial pokemon column location.
 * @param inInfected tells whether the pokemon is infected initially.
 * @param ThisBoard a pointer to the board (used to ask board whether a proposed move is ok).
 * @param ID is used to tell the differnce between rangers and trainers.
 * @param active tells whether a pokemon is on the board or in the pokemon center.
 */
Pokemon::Pokemon(int inRow, int inCol, bool inInfected, Board* ThisBoard, int ID, bool active) : Human(inRow, inCol, inInfected, ThisBoard, ID){
    row = inRow;
    col = inCol;
    infected = inInfected;
    board = ThisBoard;
    id = ID;
    is_active = active;
}

//Inherits all the functions from Human.h

// Functions exclusive to Pokemon class
/**
 * @brief sets the id of the pokemon 
 * Takes in the ID given by the parameter and sets the id equal to that
 * @param ID is given to set the actual id to.
 */
void Pokemon::setID(int ID){
    id = ID;
}

/**
 * @brief reports whether this pokemon is active.
 * @return whether a pokemon is active or not.
 */
bool Pokemon::isActive(){
    return is_active;
}

/**
 * @brief sets is_active to false.
 * This is when the pokemon enters the pokemon center.
 */
void Pokemon::setNotActive(){
    is_active = false;
}
