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
    if (isCellRevealed()) {
        if (number == 0)
            return ' ';
        else if (number == 1)
            return '1';
        else if (number == 2)
            return '2';
        else if (number == 3)
            return '3';
        else if (number == 4)
            return '4';
        else if (number == 5)
            return '5';
        else if (number == 6)
            return '6';
        else if (number == 7)
            return '7';
        else if (number == 8)
            return '8';
        else if (number == 9)
            return '9';
    }
    else
        return '-';
}
