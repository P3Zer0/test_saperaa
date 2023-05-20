//
// Created by tomex on 17.05.2023.
//

#include "Game.h"
#include <conio.h>
#define strzalka_lewo 0x26
#define strzalka_prawo 0x28
#define strzalka_dol 0x27
#define strzalka_gora 0x25
#define enter 0x0D
#define flaga 0x46
#include <windows.h>


void Game::checkGameState()
{
    board.CheckWin();
    if(board.getGameState() == 1)
    {
        board.revealAll();
        std::cout<<"You hit a mine! Too bad, you lost!"<<std::endl<<"Press any key to exit";
        getch();
        return;
    }
    else if(board.getGameState() == 2)
    {
        std::cout<<"Wahoo! You won! CONGRATZ!"<<std::endl<<"Press any key to exit";
        getch();
        return;
    }
}

void Game::play()
{
    int x=0, y=0;

    while (board.getGameState() == 0) {
        board.printBoard(x,y);
        std::cout << "\nCurrent coordinates:\n";  //aktualkna pozycja kursora
        std::cout << "X: " << x << std::endl;  //aktualkna pozycja kursora
        std::cout << "Y: " << y << std::endl;  //aktualkna pozycja kursora
        if ((GetKeyState(enter) & 0x8000))
        {
            board.revealCell(x, y);
        }
        else if ((GetKeyState(flaga) & 0x8000))
        {
            board.toggleFlag(x,y);
        }

        else if ((GetKeyState(strzalka_prawo) & 0x8000) && x<9) x++;
        else if ((GetKeyState(strzalka_lewo) & 0x8000) && x>0) x--;
        else if ((GetKeyState(strzalka_dol) & 0x8000) && y<9) y++;
        else if ((GetKeyState(strzalka_gora) & 0x8000) && y>0) y--;

        checkGameState();
        Sleep(60);
        getch();
        system("cls");
    }
}



