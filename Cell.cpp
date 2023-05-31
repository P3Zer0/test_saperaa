/**
 *  Created by Tomasz Jarząbek on 17.05.2023.
 *
 * @file Cell.cpp
 *
 * Implementation of methods declared in "Cell.h".
 */

#include "Cell.h"

bool Cell::makeFlagged() {return isFlag =true;}
bool Cell::makeDeFlagged() {return isFlag =false;}
char Cell::getSymbol() const {return 0;}
bool Cell::isCellFlagged() const {return isFlag;}
bool Cell::reveal() { return isRevealed = true; }
bool Cell::isCellRevealed() const { return isRevealed; }
bool Cell::isCellMine() {return isMine; }