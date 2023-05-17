//
// Created by tomex on 17.05.2023.
//

#ifndef TESTSAPERAAAA_CELL_H
#define TESTSAPERAAAA_CELL_H

class Cell {
protected:
    bool isRevealed=0;
    bool isMine=0;
    bool isNumber=0;
    bool isFlag=0;
public:
    Cell() : isRevealed(false), isMine(false), isNumber(false), isFlag(false) {}
    bool makeFlagged();
    bool makeDeFlagged();
    virtual char getSymbol() const;
    bool isCellFlagged() const;
    bool reveal();
    bool isCellRevealed() const;
    virtual bool isCellMine();
    virtual bool isCellNumber();
};

#endif //TESTSAPERAAAA_CELL_H
