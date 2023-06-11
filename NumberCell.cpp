/**
 *  Created by Tomasz Jarząbek on 17.05.2023.
 *
 * @file NumberCell.cpp
 *
 * Implementations of methods declared in "NumberCell.h".
 *
 */

#include "NumberCell.h"

void NumberCell::setAdjacentMines(int mines) { number = mines; }

char NumberCell::getSymbol() const {
    if (isCellFlagged())
        return 'F';
    if (isCellRevealed())
        if (number == 0)
            return ' ';
        else
            return '0' + number;
    else
        return '-';
}
