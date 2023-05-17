//
// Created by tomex on 17.05.2023.
//

#ifndef TESTSAPERAAAA_MINECELL_H
#define TESTSAPERAAAA_MINECELL_H
#include "Cell.h"

class MineCell : public Cell {
public:
    bool isCellMine();
    char getSymbol() const;
};



#endif //TESTSAPERAAAA_MINECELL_H
