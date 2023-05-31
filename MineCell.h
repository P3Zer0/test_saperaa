/**
 *  Created by Tomasz Jarząbek on 17.05.2023.
 *
 * @file MineCell.h
 *
 * Declarations of methods implemented in "MineCell.cpp".
 *
 * This class represents a mine that is set on the board
 * Its use is to simply preserve its properties
 */
#ifndef TESTSAPERAAAA_MINECELL_H
#define TESTSAPERAAAA_MINECELL_H
#include "Cell.h"

class MineCell : public Cell {
public:
    /**
     * Method for returning true, since it tells the program this cell is a mine
     * @return true
     */
    bool isCellMine() override;
    /**
     * Method for returning the symbol of the cell, depending on whether it's
     * revealed or flagged or not, it will show different symbols
     * @return a set char value
     */
    char getSymbol() const override;
};



#endif //TESTSAPERAAAA_MINECELL_H
