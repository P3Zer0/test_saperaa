/**
 *  Created by Tomasz Jarząbek on 17.05.2023.
 *
 * @file NumberCell.h
 *
 * Declarations of methods implemented in "NumberCell.cpp".
 *
 * This class represents a cell with a set number of mines
 * around it that is set on the board
 * Its use is to simply preserve its properties
 */

#ifndef TESTSAPERAAAA_NUMBERCELL_H
#define TESTSAPERAAAA_NUMBERCELL_H
#include "Cell.h"

class NumberCell : public Cell {
    /**
     * is used in the getSymbol method for showing the number of mines
     * around this cell
     */
    int number;
public:
    /**
     * Constructor for the NumberCell Class with a set number value
     */
    NumberCell() : number() {}
    /**
    * Method for setting the number value in the constructor to the value given
     * in the parameter from outside of the method
    * @param mines
    */
    void setAdjacentMines(int mines);

    /**
     * Method for returning the number of mines around a cell on the board
     * @return a set char value (dependent on number)
     */
    char getSymbol() const override;
};


#endif //TESTSAPERAAAA_NUMBERCELL_H
