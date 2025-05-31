/**
 * @file Human.cpp
 * @brief The Human class implementation file.
 *
 * @author Josh Forbes
 * @date November 2023
 */

#include <cstdlib>
#include <iostream>

#include "Human.h"
#include "Pokemon.h"
#include "conio.h"

using namespace std;

/**
 * @brief The Human class constructor.
 * This function initializes the row, col, infected, and board variables.
 *
 * @param initRow the initial human row location.
 * @param initCol the initial human column location.
 * @param initInfected whether the human is initially infected.
 * @param theBoard a pointer to the board (used to ask board whether a proposed move is ok).
 * @param ID is used to tell the difference between rangers and traienrs.
 */
Human::Human(int initRow, int initCol, bool initInfected, Board* theBoard, int ID) {
    row = initRow;
    col = initCol;
    infected = initInfected;
    board = theBoard;
    id = ID;
}

/**
 * @brief The Human class destructor.
 * The Human class destructor does nothing (so far), but is here as a placeholder to remind
 * you that it is a good idea for classes to have destructors, even if you can't think of 
 * work for destructor at this point.
 */
Human::~Human() {
    // Nothing to do
}

/**
 * @brief Have the human try to move.
 * To know whether it is ok to move to some position (r,c), ask the board
 * whether the position is ok. E.g., "if( board->tryMove(r,c) ) ..."
 * If the move is ok, then update the human's row and column to reflect the move.
 * Because the human can't move in the pokemon center but pokemon can
 * add a parameter that will allow us to see if it is a human or pokemon.
 * @param s (for species) tells us if it a human or pokemon.
 */
void Human::move(char s) {
    // Generate a +/- 2 row and column delta.
    int rowDelta=rand()%5-2, colDelta=rand()%5-2;

    // Ask the board whether you
    if(board->tryMove(row+rowDelta, col+colDelta, s)) {
        row+=rowDelta;
        col+=colDelta;
    }
}

/**
 * @brief Get the human's current row/col location.
 * Returns the human's current row/column location via the reference parameters.
 * @param[out] currentRow the human's current row. 
 * @param[out] currentCol the human's current column.
 */
void Human::getLocation(int& currentRow, int& currentCol) {
    currentRow = row;
    currentCol = col;
}

/**
 * @brief Set the human's row/col location.
 * Sets the human's current row/column location to the parameter values.
 * @param[in] newRow the human's new row location.
 * @param[in] newCol the human's new column location.
 */
void Human::setLocation(int newRow, int newCol) {
    row=newRow;
    col=newCol;
}

/**
 * @brief Sets this human to be infected.
 * Sets this human object's state to infected.
 */
void Human::setInfected() {
    infected = true;
}

/**
  * @brief Checks the id of the human.
  * @return whether a human is a trainer or ranger.
  */
int Human::getID(){
    return id;
}

/**
 * @brief reports whether this human is infected.
 * @return whether this human object is infected.
 */
bool Human::isInfected() {
    return infected;
}

/**
 * @brief Draws the human.
 * Draws the human at the current row/col location on the screen.
 * Remember that the first conio row=1, and first conio col=1.
 */
void Human::draw() {
    cout << conio::gotoRowCol(row+1,col+1);

    if( infected ) {
        if( id == 0){
            cout << conio::bgColor(conio::LIGHT_RED);
        }
        else if ( id == 1){
            cout << conio::bgColor(conio::LIGHT_BLUE);
        }
    } else {
        cout << conio::bgColor(conio::LIGHT_GREEN);
    }
    if( id == 0) {
        cout << 'T' << conio::resetAll() << flush;
    }
    else if ( id == 1 ) {
        cout << 'R' << conio::resetAll() << flush;
    }
    else if ( id == 3) {
        cout << 'P' << conio::resetAll() << flush;
    }
}
