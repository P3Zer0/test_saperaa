/**
 * Created by Tomasz Jarząbek on 17.5.2023
 *
 * @file Game.h
 *
 * Declaration of methods implemented in "Game.cpp".
 *
 * This class is responsible for creating the board the player will play on
 * Allows the player to communicate with the program through the play function.
 * Allows to print, edit and go through the menu_element array.
 */
#ifndef TESTSAPERAAAA_GAME_H
#define TESTSAPERAAAA_GAME_H
#include "Board.h"


class Game {
    /**
     * @param board an object of Board type
     */
    Board board;
public:
    /**
 * Checks the state of the game.
 * If the player has either won or lost, ends the game.
 * If not, continues the game.
 */
    void checkGameState();
    /**
* Allows the player to communicate with the game by using the arrow keys.
* To reveal a field, press ENTER.
* To place a flag, press F.
* Uses the checkGameState method each time the player makes a move.
*/
    void play();
};



#endif //TESTSAPERAAAA_GAME_H
