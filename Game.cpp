/**
 *  Created by Tomasz Jarząbek on 17.05.2023.
 *
 * @file Game.cpp
 *
 * Implementation of methods declared in "Game.h".
 * it includes conio.h and defines arrow keys, the flag
 * and the reveal button. assigning them to their
 * corresponding keys on the keyboard.
 */


#include "Game.h"
#include <conio.h>

#define left_key 0x26
#define right_key 0x28
#define down_key 0x27
#define up_key 0x25
#define enter 0x0D
#define flag_key 0x46

#include <windows.h>


void Game::checkGameState() {
    board.CheckWin();
    if (board.getGameState() == 1)
    {
        board.revealAll();
        std::cout << std::endl << "You hit a mine! Too bad, you lost!" << std::endl << "Press any key to exit";
        return;
    } else if (board.getGameState() == 2) {
        std::cout << std::endl << "Wahoo! You won! CONGRATZ!" << std::endl << "Press any key to exit";
        getch();
        return;
    }
}

void Game::play() {
    int x = 0, y = 0;

    while (board.getGameState() == 0) {
        board.printBoard(x, y);
        std::cout << "\nCurrent coordinates:\n";
        std::cout << "X: " << y << std::endl;
        std::cout << "Y: " << x << std::endl;
        if ((GetKeyState(enter) & 0x8000)) {
            board.revealCell(x, y);
        } else if ((GetKeyState(flag_key) & 0x8000)) {
            board.toggleFlag(x, y);
        } else if ((GetKeyState(right_key) & 0x8000) && x < 9) x++;
        else if ((GetKeyState(left_key) & 0x8000) && x > 0) x--;
        else if ((GetKeyState(down_key) & 0x8000) && y < 9) y++;
        else if ((GetKeyState(up_key) & 0x8000) && y > 0) y--;

        checkGameState();
        Sleep(60);
        getch();
        system("cls");
    }
}



