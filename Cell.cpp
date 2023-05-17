//
// Created by tomex on 17.05.2023.
//

#include "Cell.h"

bool Cell::makeFlagged() {return isFlag =true;}
bool Cell::makeDeFlagged() {return isFlag =false;}
char Cell::getSymbol() const {return 0;}
bool Cell::isCellFlagged() const {return isFlag;}
bool Cell::reveal() { return isRevealed = true; }
bool Cell::isCellRevealed() const { return isRevealed; }
bool Cell::isCellMine() {return isMine; }
bool Cell::isCellNumber() {return isNumber;}