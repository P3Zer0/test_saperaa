//
// Created by tomex on 17.05.2023.
//

#include "MineCell.h"

bool MineCell::isCellMine() {
    return true;
}
char MineCell::getSymbol() const {
    if (isCellFlagged())
        return 'F';
    if (isCellRevealed())
        return 'X';
    else
        return '-';
}