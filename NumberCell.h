//
// Created by tomex on 17.05.2023.
//

#ifndef TESTSAPERAAAA_NUMBERCELL_H
#define TESTSAPERAAAA_NUMBERCELL_H
#include "Cell.h"

class NumberCell : public Cell {
    int number;
public:
    NumberCell() : number() {}
    void setAdjacentMines(int mines);
    bool isCellNumber();
    char getSymbol() const override;
};


#endif //TESTSAPERAAAA_NUMBERCELL_H
