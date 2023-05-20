//
// Created by tomex on 17.05.2023.
//

#include "Board.h"
#include <cstdlib>


//std::vector<std::vector<Cell *>> cells;

/*
    Cell Board::*getCell(int x, int y) {
        return cells[x][y];
    }
    */
int Board::getGameState() const
{
    return GameState;
}
int Board::loseGameState()
{
    return GameState = 1;
}

bool Board::inBoard(int x, int y) const {
    if (x < 0) {
        return false;
    }
    if (x >= height) {
        return false;
    }
    if (y < 0) {
        return false;
    }
    if (y >= width) {
        return false;
    }
    return true;
}


void Board::initializeBoard() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cells[i][j] = new NumberCell();
        }
    }
    int minesToPlace = 10;
    while (minesToPlace > 0) {
        int row = rand() % 10;
        int col = rand() % 10;
        if (!cells[row][col]->isCellMine()) {
            delete cells[row][col];
            cells[row][col] = new MineCell();
            minesToPlace--;
        }
    }
    updateAdjacentMines();
}

void Board::updateAdjacentMines() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (dynamic_cast<MineCell *>(cells[i][j]) == nullptr) {
                int count = 0;
                for (int row = -1; row <= 1; row++) {
                    for (int col = -1; col <= 1; col++) {
                        if (i + row >= 0 && i + row < 10 && j + col >= 0 && j + col < 10) {
                            if (dynamic_cast<MineCell *>(cells[i + row][j + col]) != nullptr)
                                count++;
                        }
                    }
                }
                dynamic_cast<NumberCell *>(cells[i][j])->setAdjacentMines(count);
            }
        }
    }
}

/*
~Board() {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            delete cells[i][j];
        }
    }
}
 */

void Board::reveal_empty_fields_around(int row, int col) {
    for (int help_row = (row - 1); help_row <= (row + 1); help_row++) {
        for (int help_col = (col - 1); help_col <= (col + 1); help_col++) {
            if (inBoard(help_row, help_col)) {
                if (!cells[help_row][help_col]->isCellRevealed()) {//(help_row, help_col)) {
                    if(cells[help_row][help_col]->isCellFlagged()) {
                        cells[help_row][help_col]->makeDeFlagged();
                        flags -= 1;
                    }
                    if (!cells[help_row][help_col]->isCellMine())
                    {
                        cells[help_row][help_col]->reveal();
                        revealed_cells += 1;
                    }
                    if (countMines(help_row, help_col) == 0) {
                        reveal_empty_fields_around(help_row, help_col);

                    }
                }

            }

        }
    }

}
int Board::getMinesOnField() const {
    int allMines = 0;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (cells[i][j]->isCellMine())
                allMines += 1;
        }
    }
    return allMines;
}
int Board::countMines(int row, int col) const {
    if (!inBoard(row, col)) {
        return -1;
    }
    if (!cells[row][col]->isCellRevealed()) {
        return -1;
    }

    int mines_around = 0;
    for (int help_row = row - 1; help_row <= (row + 1); help_row++) {
        for (int help_col = (col - 1); help_col <= (col + 1); help_col++) {
            if (inBoard(help_row, help_col)) {
                if (cells[help_row][help_col]->isCellMine()) {
                    mines_around += 1;
                    std::cout << mines_around;
                }
            }
        }
    }
    //odejmujemy jesli zadane pole ma bombe
    if (cells[row][col]->isCellMine()) {
        mines_around -= 1;
    }
    //std::cout<<mines_around;
    return mines_around;
}
void Board::toggleFlag(int x,int y){
    if (!inBoard(x,y)) {
        return;
    }
    if (!cells[x][y]->isCellRevealed()) {
        if (!cells[x][y]->isCellFlagged()) {
            cells[x][y]->makeFlagged();
            flags += 1;
        }
        else{
            cells[x][y]->makeDeFlagged();
            flags -=1;
        }
    }
}

void Board::revealCell(int row, int col) {
    if (!inBoard(row, col)) {
        return;
    }
    if (cells[row][col]->isCellFlagged()) {
        return;
    }
    if (cells[row][col]->isCellRevealed()) {
        return;
    }
    if (!cells[row][col]->isCellMine()) {
        cells[row][col]->reveal();
        revealed_cells += 1;
        number_of_moves += 1;
        if (countMines(row, col) == 0) {
            reveal_empty_fields_around(row, col);
        }
    } else {
        if (number_of_moves == 0) {
            delete cells[row][col];
            cells[row][col] = new NumberCell;
            updateAdjacentMines();
            cells[row][col]->reveal();
            revealed_cells += 1;
            number_of_moves += 1;
            if (countMines(row, col) == 0) {
                reveal_empty_fields_around(row, col);
            }
            return;
        }
        if (number_of_moves != 0) {
            loseGameState();
            return;
        }
    }

}

void Board::revealAll()
{
    for(int row=0; row<height; row++)
    {
        for(int col=0; col<width; col++)
        {
            cells[row][col]->reveal();
            if(cells[row][col]->isCellMine())
            {
                cells[row][col]->reveal();
            }
        }
    }
}

void Board::printBoard(int x, int y) const {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (i==x&&j==y)
            {
                std::cout << "# ";
                std::cout << cells[i][j]->getSymbol() << '\b';
            }
            else
            std::cout << cells[i][j]->getSymbol() << ' ';
        }
        std::cout << std::endl;
    }

    std::cout<<"To move around the board, use arrow keys.\nTo reveal a cell, press ENTER.\nTo place a flag, press F.";
    std::cout<<revealed_cells<<std::endl;
    std::cout<< getMinesOnField()<<std::endl;
}

void Board::CheckWin()
{
    if(revealed_cells == (height*width)-getMinesOnField()){
        GameState = 2;
    }
}