//
// Created by tomex on 17.05.2023.
//

#ifndef TESTSAPERAAAA_BOARD_H
#define TESTSAPERAAAA_BOARD_H
#include "Cell.h"
#include "MineCell.h"
#include "NumberCell.h"
#include <vector>
#include <iostream>

class Board {

private:
    std::vector<std::vector<Cell *>> cells;
    int revealed_cells = 0;
    int height = 10;
    int width = 10;
    int number_of_moves = 0;
    int GameState=0;
    //int numofMines=0;
    int flags = 0;

public:
    //Cell *getCell(int x, int y);

    bool inBoard(int x, int y) const;
    Board() {
        cells.resize(10, std::vector<Cell *>(10));
        initializeBoard();
    }
    int getGameState() const;

    int loseGameState();

    void initializeBoard();

    void updateAdjacentMines();

    //~Board();

    void reveal_empty_fields_around(int row, int col);

    int getMinesOnField() const;

    int countMines(int row, int col) const;

    void toggleFlag(int x,int y);

    void revealCell(int row, int col);

    void revealAll();

    void printBoard() const;

    void CheckWin();

};


#endif //TESTSAPERAAAA_BOARD_H
