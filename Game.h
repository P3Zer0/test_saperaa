//
// Created by tomex on 17.05.2023.
//

#ifndef TESTSAPERAAAA_GAME_H
#define TESTSAPERAAAA_GAME_H
#include "Board.h"


class Game {
    Board board;
    char letter;
public:
    void checkGameState();
    void play();
};



#endif //TESTSAPERAAAA_GAME_H
