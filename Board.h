/**
 *  Created by Tomasz Jarząbek on 17.05.2023.
 *
 * @file Board.h
 *
 * Declarations of methods implemented in "Board.cpp".
 *
 * This class represents the board, which stores the cells.
 * It contains methods essential to the proper functioning
 * of the Minesweeper game.
 *
 */

#ifndef TESTSAPERAAAA_BOARD_H
#define TESTSAPERAAAA_BOARD_H
#include "Cell.h"
#include "MineCell.h"
#include "NumberCell.h"
#include <vector>
#include <iostream>

class Board {

private:
    /**
     * cells , a vector of vectors of Cell* type
     * it is used to storage the multiple Cells classes.
     */
    std::vector<std::vector<Cell *>> cells;
    /**
     * the number of cells that are revealed currently.
     * it is used to determine if the game's been won
     * is set to 0 by default
     */
    int revealed_cells = 0;
    /**
     * the height of the board
     * is set to 10 by default
     */
    int height = 10;
    /**
     * the width of the board
     * is set to 10 by default
     */
    int width = 10;
    /**
     * the number of moves (as in, whether the player
     * has revealed any cells yet).
     * it is used in making sure the first cell the
     * player reveals is not a mine, so as to be fair towards them
     * is set to 0 by default
     */
    int number_of_moves = 0;

    /**
     * the number of flags that the player has placed on
     * the board. it is used in determining the current
     * state of the game.
     * it is set to 0 by default
     */
    int flags = 0;
    /**
    * Method for checking whether the coordinates the player
    * has inserted are within the boarders of the board.
    * @param x the abscissa axis position of the cursor
    * @param y the ordinate axis position of the cursor
    * @return false if is outside the board, else true
    */
    bool inBoard(int x, int y) const;
    /**
     * Method for making the current state of the game a loss
     * @return GameState = 1
     */
    int loseGameState();

    /**
     * Method for initialising the board. i.e. setting the
     * mines on the board, making the cells NumberCells and
     * updating the numbers on the cells around mines
     */
    void initializeBoard();

    /**
     * Method for updating the number shown on the cells around
     * the mines on the board.
     */
    void updateAdjacentMines();

    /**
     * Method for revealing the empty fields (i.e. the number
     * of mines around them is 0) around any other empty fields
     * @param row the current row that is being revealed
     * @param col the current column that is being revealed
     */
    void revealEmptyFieldsAround(int row, int col);

    /**
 * Method for counting up the mines around a field
 * @param row the row coordinates of the cell
 * @param col the column coordinates of the cell
 * @return mines_around the number of mines around the cell
 */
    int countMines(int row, int col) const;

    /**
     * The number of mines that is set to be placed on the board.
     * Set to zero by default.
     */
    int minesToPlace = 0;

    /**
 * the variable used to determine the state of the game.
 */
    enum GameStates
    {
        RUNNING,
        LOSS,
        WIN
    };

    GameStates GameState;


public:

    /**
     * Constructor for the Board, initializing the object to
     * be resized to 10x10 in width and height. Then, initializes
     * the board using the initializeBoard method.
     */
    Board() : minesToPlace(20), height(10), width(10), GameState(RUNNING) {
        cells.resize(height, std::vector<Cell *>(width));
        initializeBoard();
    }

    /**
     * Method for checking the current state of the game
     * @return GameState
     */
    int getGameState() const;

    /**
     * Method for toggling a flag on the cell. If it doesn't have one,
     * it sets up one. If it already has one, it removes the flag
     * @param x the abscissa axis position of the cell
     * @param y the ordinate axis position of the cell
     */
    void toggleFlag(int x,int y);

    /**
     * Method for revealing a cell. it disallows to reveal an already
     * revealed cell or a flagged cell.
     * If the cell contains a mine and the number of moves is not
     * equal to 0, it ends the game. Else, the cell is made into a
     * NumberCell instead, making sure the player doesn't lose on
     * their first move.
     * @param row the abscissa axis position of the cell
     * @param col the ordinate axis position of the cell
     */
    void revealCell(int row, int col);

    /**
     * Method for revealing the entire board to showcase where the mines
     * were after the player hits one.
     */
    void revealAll();

    /**
     * Method for printing out the entire board.
     * It is made in mind with showing the current position of the
     * cursor on the board. Instead of the symbol the cell contains,
     * it shows a "#" sign.
     * @param x the abscissa axis position of the cursor
     * @param y the ordinate axis position of the cursor
     */
    void printBoard(int x, int y) const;

    /**
     * Method for checking if the game has been won by the player.
     * It calculates if teh overall number of the cells minus the mines
     * equals the number of the revealed cells. Flagged cells do not count
     * as revealed ones and, if put on a NumberCell, must be de-flagged.
     */
    void CheckWin();

};


#endif //TESTSAPERAAAA_BOARD_H
