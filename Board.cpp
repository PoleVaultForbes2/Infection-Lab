/**
 * @file Board.cpp
 * @brief Board class implementation (also called 'definition') file.
 * @author Stefan Brandle
 * @author Josh Forbes
 * @date November 2023
 */

#include <iostream>
#include <cstdlib>
#include <unistd.h>

// When writing a class implementation file, you must "#include" the class
// declaration file.
#include "Board.h"

// We also use the conio namespace contents, so must "#include" the conio declarations.
#include "conio.h"

/**
 * @brief The Board class constructor, responsible for intializing a Board object.
 * The Board constructor is responsible for initializing all the Board object variables.
 *
 * @param rows The number of rows to make the board.
 * @param cols The number of columns to make the board.
 * @param numberOfHumans The number of humans to place on the board.
 */
Board::Board(int rows, int cols, int numberOfHumans, int numberofPokemon) {
    numHumans = numberOfHumans;
    numPokemon = numberofPokemon;
    numRows = rows;
    numCols = cols;
    currentTime = 0;
    uSleepTime = 250000;
    numTrainerCaught=0;
    numRangerCaught=0;
    numPokemonSafe = 0;
}

/**
 * @brief The Board class destructor.
 * The Board destructor is responsible for any last-minute cleaning 
 * up that a Board object needs to do before being destroyed. In this case,
 * it needs to return all the memory borrowed for creating the Human objects.
 */
Board::~Board() {
    for(int pos=0; pos<numHumans; ++pos) {
        delete humans[pos];
    }
    for(int pos=0; pos<numPokemon; ++pos) {
        delete pokemons[pos];
    }
}

/**
 * @brief function that runs the simulation
 * Creates human objects, infects one human, then runs simulation until all are infected.
 */
void Board::run() {
    int row, col;

    // Creates 'Human' objects and sets the array pointers to point at them.
    for(int pos=0; pos<numHumans; ++pos) {

        // Do while loop to make sure the humans are not created in the pokemon center
        do{
            //row = pos%numRows;       // row will be in range(0, numRows-1)
            row = random()%numRows;    // row will be in range(0, numRows-1)
            col = random()%numCols;    // col will be in range(0, numCols-1)
        }
        while(checkCenter(row, col));

        //** Create ID for the human being created
        int ID = -1;       // if 0=trainer if 1=ranger
        if(pos<4){
            ID = 0;
        }
        else ID = 1;
        
        // Create and initialize another Human. 
        // Parameters are  row on board, col on board, initialy infected, 
        // and a pointer to this board object ('this') and id.
        humans[pos] = new Human(row, col, true, this, ID); 
    }
    // Creates 'Pokmeon' objects and sets the array pointers to point at them.
    for (int pos=0; pos<numPokemon; ++pos) {
        
        row = pos&numRows;      // row will be in range(0, numRows-1)
        col = random()%numCols; // col will be in range(0, numCols-1)
        //** Id is assigned -1 for now but will change if infected
        int PokID = 3;

        // Create and initialize another Pokemon.
        // Parameters are row on board, col on board, intiialy infected,
        // and a pointer to the board object ('this') and id.
        pokemons[pos] = new Pokemon(row, col, false, this, PokID, true);
    }

    for(currentTime=0; allInfected() == false and currentTime <= 59; ++currentTime) {
        // Clear screen before every new time unit
        cout << conio::clrscr() << flush;

        // Tell each human to try moving
        for(int pos=0; pos<numHumans; ++pos) {
            humans[pos]->move('h');
        }
        // Tell each Pokemon to try moving
        for(int pos=0; pos<numPokemon; ++pos) {
            if(pokemons[pos]->isActive()){
                pokemons[pos]->move('p');
            }
        }

        // Deal with infection propagation.
        processInfection();
        // Check to see if a pokemon is in the center
        for( int i=0; i<numPokemon; i++) {
            int rowX=-1;
            int colY=-1;
            pokemons[i]->getLocation(rowX, colY);
            if(checkCenter(rowX, colY)){
                if(pokemons[i]->isActive() == true) {       // if pokemon is active
                    if(pokemons[i]->isInfected() == false){ // if pokemon is not infected
                        numPokemonSafe++;
                        pokemons[i]->setNotActive();
                        pokemons[i]->setInfected();
                    }
                    //else the pokemon is already caught and is active
                    else{
                        pokemons[i]->setNotActive();
                        numPokemonSafe++;
                        pokemons[i]->setID(3);
                    }
                }
            }
        }

        // Tell each human to draw itself on board with updated infection status
        for(int pos=0; pos<numHumans; ++pos) {
            humans[pos]->draw();
        }
        // Tell each pokemon to draw itself on board with updated infection status if it is active
        for(int pos=0; pos<numPokemon; ++pos) {
            if(pokemons[pos]->isActive()){
                pokemons[pos]->draw();
            }
        }

        // Print statistics.
        drawCenter();
        cout << conio::gotoRowCol(numRows+3, 1) 
             << "Time=" << currentTime << endl
             //<< "Total humans=" << numHumans << endl
             << "Total pokemon caught by Trainer=" << numTrainerCaught << endl
             << "Total pokemon caught by Ragners=" << numRangerCaught << endl
             << "Total pokemon in PokeCenter=" << numPokemonSafe << endl
             << "Total pokemon free=" << numPokemonFree << endl << flush;

        // Sleep specified microseconds
        usleep(uSleepTime);
    }
    // At the end of the simulation print the winner
    int totalSafePokemon = numPokemonSafe + numPokemonFree;     // To compare how many pokemon were not caught
    if(numTrainerCaught > numRangerCaught){
        if(numTrainerCaught > totalSafePokemon){
            cout << "The trainers caught the most Pokemon!";
        }
        else{
            cout << "The Pokemon survived the trainers and rangers!";
        }
    }
    else if(numRangerCaught > totalSafePokemon){
        if(numRangerCaught == numTrainerCaught){
            cout << "The rangers and trainers caught the same number of pokemon!";
        }
        else{
            cout << "The rangers caught the most Pokemon!";
        }
    }
    else{
        cout << "The Pokmeon survived the trainers and ragners!";
    }

    // Position the cursor so prompt shows up on its own line
    cout << endl;
}

/**
 * @brief Determines whether or not all humans are infected.
 * @return If even one pokemon is uninfected, returns false. Otherwise, returns true.
 */
bool Board::allInfected() {
    for(int i=0; i<numPokemon; ++i) {
        if(pokemons[i]->isInfected() == false) return false;
    }

    return true;
}

/**
 * @brief The function that handles one infection cycle to determine what new infections
 *        are present.
 * For each pair of adjacent pokmeon to infected being in the simulation, processInfection() makes sure that if 
 * one is infected, the other becomes infected as well.
 */
void Board::processInfection() {
    //Check if pokemon is next to an infected pokemon
    for(int i=0; i<numPokemon; ++i) {
       for(int j=0; j<numPokemon; ++j) {
           if(pokemons[i]->isInfected() == false ) {                   // If the pokemon is not infected
               if(isNextToPoke(pokemons[i], pokemons[j])) {           // If the pokemon are next to each other
                   if(pokemons[j]->isInfected() == true && pokemons[j]->isActive()){           // If the pokemon next to is infected
                       pokemons[i]->setID(pokemons[j]->getID());
                       pokemons[i]->setInfected();
                   }
               }
           }
       }
    }
    //Check if the pokemon is next to a human
    for( int i=0; i<numPokemon; ++i ) {
        for( int j=0; j<numHumans; ++j ) {
            if( pokemons[i]->isInfected() == false ) {
                if( isNextTo(pokemons[i], humans[j]) ){                 // If next to a human automatically becomes infected
                    pokemons[i]->setID(humans[j]->getID());
                    pokemons[i]->setInfected();
                }
            }
        }
    }
    // Reset the board 'numInfected' count and recount how many are infected.
    numTrainerCaught = 4;
    numRangerCaught = 4;
    numPokemonFree = 0;
    //set to 4 because there are only 8 humans
    
    // This is for number of pokemon that have now been infected
    for (int i=0; i<numPokemon; ++i) {
        if (pokemons[i]->isInfected() ) {
            if(pokemons[i]->getID() == 0) {
                numTrainerCaught++;
            }
            else if (pokemons[i]->getID() == 1 ) {
                numRangerCaught++;
            }
        }
        else numPokemonFree++;
    }

}

/**
 * @brief The function that determines whether a particular move can happen.
 *        If the move would go off the board, or land on the same position as another
 *        human, the function returns false (do not move). Otherwise, it returns true (ok to proceed).
 * @param[in] row the row the human wishes to move to.
 * @param[in] col the col the human wishes to move to.
 * @param s (for species) to make sure that humans don't go in the pokemon center
 * @return Whether the human calling this function may move to the specified row and column.
 */
bool Board::tryMove(int row, int col, char s) {
    //row and col is where we are trying to go, x is if its human or pokemon
    int tryRow=-1, tryCol=-1;

    // If off board, the move is not permitted
    if( row<0 || row>=numRows || col<0 || col>=numCols ) return false;

    // Else if the move is inside the Pokemon Center return false for humans.
    if(s == 'h'){
        if( row>=9 and row<=14 and col>=9 and col<=17 ) return false;
    }

    // Else if where 'its' going is the same location as a human, move is invalid.
    for(int i=0; i<numHumans; ++i) {
        humans[i]->getLocation(tryRow, tryCol);
        if( row==tryRow && col==tryCol ) return false;
    }
    // Else if where 'its' going is the same location as a pokemon, move is also invalid.
    for (int i=0; i<numPokemon; ++i) {
        pokemons[i]->getLocation(tryRow, tryCol);
        if ( row==tryRow && col==tryCol ) return false;
    }

    // No problems, so the move is permitted
    return true;
}

/**
 * @brief The function that determines whether a pokemon and human are on adjacent squares.
 * @param p pointer to first human object.
 * @param h pointer to second human object.
 * @return Whether or not p and h are on adjacent squares.
 */
bool Board::isNextTo(Pokemon *p, Human* h) {
    // Get pokemon and human location information
    int pRow, pCol;
    p->getLocation(pRow, pCol);
    int hRow, hCol;
    h->getLocation(hRow, hCol);

    // Return whether h1 and h2 are on adjacent squares in any direction 
    // (horizontally, vertically, diagonally).
    return abs(pRow-hRow)<=1 && abs(pCol-hCol)<=1;
}

/**
 * @brief The function that determines whether two pokemon are on adjacent squares.
 * @param p1 pointer to first pokemon object.
 * @param p2 pointer to second pokemon object.
 * @return Whether or not p1 and p2 are on adjacent squares.
 */
bool Board::isNextToPoke(Pokemon *p1, Pokemon *p2) {
    // Get pokemon location information
    int p1Row, p1Col;
    p1->getLocation(p1Row, p1Col);
    int p2Row, p2Col;
    p2->getLocation(p2Row, p2Col);

    // Return whether p1 and p2 are on adjacent squares in any direction
    // (horizontally, vertically, diagonally).
    return abs(p1Row-p2Row)<=1 && abs(p1Col-p2Col)<=1;
    
}

/**
 * @brief The function that will draw the pokemon center at a location.
 * Is used to determine the safe zone for pokemon.
 */
void Board::drawCenter() {
    char col[6];
    char row[6];
    // Add the bondaries
    for (int i=0; i<6; i++) {
        col[i] = '|';
        row[i] = '_';
    }

    // Now print the PokeCenter
    for (int i=0; i<5; i++) {
        cout << conio::gotoRowCol(10+i, 10) << col[i];
    }
    for (int i=0; i<5; i++) {
        cout << conio::gotoRowCol(10+i, 17) << col[i];
    }
    for (int i=0; i<6; i++) {
        cout << conio::gotoRowCol(9, 11+i) << row[i];
    }
    for (int i=0; i<6; i++) {
        cout << conio::gotoRowCol(14, 11+i) << row[i];
    }
    // Print "Poke Cent" inside the pokemon center
    cout << conio::gotoRowCol(11, 12) << "Poke";
    cout << conio::gotoRowCol(12, 11) << "Center";
}

/**
 * @brief The function that checks to see if a pokemon went into the pokemon center.
 * This function will return true if the pokemon is in the center.
 * and will return false if it is not in the center.
 * @param row which is the y value of where the pokemon is moving.
 * @param col which is the x value of where the pokmeon is moving.
 * @return whether the object is in the pokemon center or not.
 */
bool Board::checkCenter(int row, int col){
    if( row>=8 and row<=14 and col>=9 and col<=17 ) {
        return true;
    }
    else return false;
}
