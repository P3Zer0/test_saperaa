/**
 *  Created by Tomasz Jarząbek on 17.05.2023.
 *
 * @file MineCell.cpp
 *
 * Implementations of methods declared in "MineCell.h".
 *
 */

#include "MineCell.h"

bool MineCell::isCellMine() {
    return true;
}
char MineCell::getSymbol() const {
    if (isCellFlagged())
        return 'F';
    if (isCellRevealed())
        return 'X';
    if (isCellRevealed())
        return '#';
    else
        return '-';
}