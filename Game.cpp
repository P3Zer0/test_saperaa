//
// Created by tomex on 17.05.2023.
//

#include "Game.h"
#include <conio.h>

Board board;
char letter;

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
void Game::play() {
    int x, y;
    while (board.getGameState() == 0) {
        board.printBoard();
        std::cout << "Enter the coordinates (x, y) of the cell to reveal and then either F or R to command: ";
        std::cin >> y >> x >> letter;
        switch (letter) {
            case 'f' :
                board.toggleFlag(x,y);
                break;
            case 'r' :
                board.revealCell(x, y);
                break;
            default:
                std::cout << "Unknown command." << std::endl;
        }
        checkGameState();

        system("cls");
    }
}


