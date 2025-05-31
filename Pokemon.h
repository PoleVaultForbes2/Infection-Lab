/**
  * Decleration of the Pokemon class.
  *
  * @author Josh Forbes
  * @date November 2023
  */

#include "Board.h"

#ifndef POKEMON_H
#define POKEMON_H

using namespace std;

/**
  *@class Pokemon
  *@brief the Pokemon class decleration
  *inherits the Human class
  */
class Pokemon: public Human
{
    public:
        //Constructor
        Pokemon(int inRow, int inCol, bool inInfected, Board* ThisBoard, int ID, bool active);

        //Function exclusive to Pokemon class
        void setID(int ID);
        bool isActive();
        void setNotActive();

    protected:
        bool is_active;     // track if the pokemon is in the pokemon center or not

    // **What is inherited**
        /*
        void move();
        void draw();
        void getLocation();
        void setLocation();
        void setInfected();
        bool isInfected();
        int getId();

        protected:
        int id;
        bool infected;
        int row, col;

        Board *board;
        */


};
#endif //POKEMON_H
