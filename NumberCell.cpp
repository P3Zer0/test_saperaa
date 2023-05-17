//
// Created by tomex on 17.05.2023.
//

#include "NumberCell.h"

void NumberCell::setAdjacentMines(int mines) { number = mines; }
bool NumberCell::isCellNumber() {return true;}
char NumberCell::getSymbol() const {
    if (isCellFlagged())
        return 'F';
    if (isCellRevealed())
        if(number == 0)
            return ' ';
        else
            return '0' + number;
    else
        return '-';
}