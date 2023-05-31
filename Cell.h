/**
 *  Created by Tomasz Jarząbek on 17.05.2023.
 *
 * @file Cell.h
 *
 * Declarations of methods implemented in "Game.cpp".
 *
 * This class represents one of the cells/fields on the board.
 * Its use is to simply preserve its properties and, if needed,
 * change them using the methods included in it
 */
#ifndef TESTSAPERAAAA_CELL_H
#define TESTSAPERAAAA_CELL_H

class Cell {
protected:
    /**
     * isRevealed, isMine, isNumber and isFlag are all initially set to false
     */
     /**
      * The value that tells the program whether the cell is revealed or not
      */
    bool isRevealed=0;
    /**
     * The value that tells the program whether the cell is a mine or not
     */
    bool isMine=0;
    /**
     * The value that tells the program whether the cells is a NumberCell or not
     */
    bool isNumber=0;
    /**
     * The value that tells the program whether the cell is flagged or not
     */
    bool isFlag=0;
public:
    /**
     * Constructor for the Cell Class.
     *
     * @param isRevealed, isMine, isNumber, isFlag are all type bool and initially set to false
     */
    Cell() : isRevealed(false), isMine(false), isNumber(false), isFlag(false) {}

    /**
     * Method for setting the Cell to be flagged
     * @return isFlag to be true
     */
    bool makeFlagged();

    /**
     * Method for setting the Cell to be de-flagged
     * @return isFlag to false
     */
    bool makeDeFlagged();

    /**
     * Method for returning the symbol that will be displayed on the board
     * @return 0 by default. It is virtually changed in MineCell and NumberCell
     */
    virtual char getSymbol() const;

    /**
     * Method for returning whether the Cell is flagged or not
     * @return isFlag , depending on whether it was set to be false or true
     */
    bool isCellFlagged() const;

    /**
     * Method for revealing the Cell
     * @return isRevealed to true
     */
    bool reveal();

    /**
     * Method for returning whether the Cell is revealed or not
     * @return isRevealed , depending on whether it was set to be false or true
     */
    bool isCellRevealed() const;

    /**
     * Method for returning whether the Cell contains a mine or not
     * @return isMine , depending on whether it was set to be false or true
     */
    virtual bool isCellMine();
};

#endif //TESTSAPERAAAA_CELL_H
