#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#define strzalka_lewo 0x25
#define strzalka_prawo 0x27
#define strzalka_dol 0x28
#define strzalka_gora 0x26
#define enter 0x0D
#define flaga 0x46
#include <chrono>
#include <thread>
#include <windows.h>
#include <vector>

class Cell {
protected:
    bool isRevealed=0;
    bool isMine=0;
    bool isNumber=0;
    bool isFlag=0;
public:
    Cell() : isRevealed(false), isMine(false), isNumber(false), isFlag(false) {}
    bool makeFlagged() {return isFlag =true;}
    bool makeDeFlagged() {return isFlag =false;}
    virtual char getSymbol() const = 0;
    bool isCellFlagged() const {return isFlag;}
    bool reveal() { return isRevealed = true; }
    bool isCellRevealed() const { return isRevealed; }
    virtual bool isCellMine() {return isMine; }
    virtual bool isCellNumber() {return isNumber;}
};

class NumberCell : public Cell {
    int number;
public:
    NumberCell() : number() {}
    void setAdjacentMines(int mines) { number = mines; }
    bool isCellNumber() {return true;}
    char getSymbol() const override {
        if (isCellFlagged())
            return 'F';
        if (isCellRevealed())
            if(number == 0)
                return ' ';
            else
                return '0' + number;
        else
            return '-';
    }
};

class MineCell : public Cell {
public:
    bool isCellMine() {
        return true;
    }
    char getSymbol() const override {
        if (isCellFlagged())
            return 'F';
        if (isCellRevealed())
            return 'X';
        else
            return 'W';
    }
};

class Board {

private:
    std::vector<std::vector<Cell *>> cells;
    int revealed_cells = 0;
    int height = 10;
    int width = 10;
    int number_of_moves = 0;
    int GameState=0;
    int numofMines=0;
    int flags = 0;

public:
    Cell *getCell(int x, int y) {
        return cells[x][y];
    }
    int getGameState()
    {
        return GameState;
    }
    int loseGameState()
    {
        GameState = 1;
    }

    bool inBoard(int x, int y) const {
        if (x < 0) {
            return false;
        }
        if (x >= height) {
            return false;
        }
        if (y < 0) {
            return false;
        }
        if (y >= width) {
            return false;
        }
        return true;
    }

    Board() {
        cells.resize(10, std::vector<Cell *>(10));
        initializeBoard();
    }

    void initializeBoard() {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                cells[i][j] = new NumberCell();
            }
        }
        int minesToPlace = 10;
        while (minesToPlace > 0) {
            int row = rand() % 10;
            int col = rand() % 10;
            if (!cells[row][col]->isCellMine()) {
                delete cells[row][col];
                cells[row][col] = new MineCell();
                minesToPlace--;
            }
        }
        updateAdjacentMines();
    }

    void updateAdjacentMines() {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (dynamic_cast<MineCell *>(cells[i][j]) == nullptr) {
                    int count = 0;
                    for (int row = -1; row <= 1; row++) {
                        for (int col = -1; col <= 1; col++) {
                            if (i + row >= 0 && i + row < 10 && j + col >= 0 && j + col < 10) {
                                if (dynamic_cast<MineCell *>(cells[i + row][j + col]) != nullptr)
                                    count++;
                            }
                        }
                    }
                    dynamic_cast<NumberCell *>(cells[i][j])->setAdjacentMines(count);
                }
            }
        }
    }
    ~Board() {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                delete cells[i][j];
            }
        }
    }

    void reveal_empty_fields_around(int row, int col) {
        for (int help_row = (row - 1); help_row <= (row + 1); help_row++) {
            for (int help_col = (col - 1); help_col <= (col + 1); help_col++) {
                if (inBoard(help_row, help_col)) {
                    if (!cells[help_row][help_col]->isCellRevealed()) {//(help_row, help_col)) {
                        if(cells[help_row][help_col]->isCellFlagged()) {
                            cells[help_row][help_col]->makeDeFlagged();
                            flags -= 1;
                        }
                        if (!cells[help_row][help_col]->isCellMine())
                        {
                            cells[help_row][help_col]->reveal();
                            revealed_cells += 1;
                        }
                        // if (cells[help_row][help_col]->isCellNumber())
                        //  return;
                        if (countMines(help_row, help_col) == 0) {
                            reveal_empty_fields_around(help_row, help_col);

                        }
                    }

                }

            }
        }

    }
    int getMinesOnField() const {
        int allMines = 0;
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                if (cells[i][j]->isCellMine())
                    allMines += 1;
            }
        }
        return allMines;
    }
    int countMines(int row, int col) const {
        if (!inBoard(row, col)) {
            return -1;
        }
        if (!cells[row][col]->isCellRevealed()) {
            return -1;
        }

        int mines_around = 0;
        for (int help_row = row - 1; help_row <= (row + 1); help_row++) {
            for (int help_col = (col - 1); help_col <= (col + 1); help_col++) {
                if (inBoard(help_row, help_col)) {
                    if (cells[help_row][help_col]->isCellMine()) {
                        mines_around += 1;
                        std::cout << mines_around;
                    }
                }
            }
        }
        //odejmujemy jesli zadane pole ma bombe
        if (cells[row][col]->isCellMine()) {
            mines_around -= 1;
        }
        //std::cout<<mines_around;
        return mines_around;
    }
    void toggleFlag(int x,int y){
        std::cout<<"HAGBAGA!!!! ";
        if (!inBoard(x,y)) {
            return;
        }

        if (!cells[x][y]->isCellRevealed()) {
            std::cout<<"niburhigur!!!! ";
            if (!cells[x][y]->isCellFlagged()) {
                if (flags==getMinesOnField()){
                    return;}

                std::cout<<"ulumbulum!!!! ";
                cells[x][y]->makeFlagged();
                flags += 1;
            }
            else{
                std::cout<<"maronfaron!!!! ";
                cells[x][y]->makeDeFlagged();
                flags -=1;
            }
            //number_of_moves += 1; //ZOBACZYMY CZY WYRZUCIC CZY NIE
        }
    }

    void revealCell(int row, int col) {
        if (!inBoard(row, col)) {
            return;
        }
        if ((cells[row][col]->isCellFlagged())&&(cells[row][col]->isCellMine())) {
            return;
        }
        if (cells[row][col]->isCellRevealed()) {
            return;
        }
        if (!cells[row][col]->isCellMine()) {
            cells[row][col]->reveal();
            revealed_cells += 1;
            number_of_moves += 1;
            if (countMines(row, col) == 0) {
                reveal_empty_fields_around(row, col);
            }
        } else {
            if (number_of_moves == 0) {
                delete cells[row][col];
                cells[row][col] = new NumberCell;
                updateAdjacentMines();
                cells[row][col]->reveal();
                revealed_cells += 1;
                number_of_moves += 1;
                if (countMines(row, col) == 0) {
                    reveal_empty_fields_around(row, col);
                }
                return;
            }
            if (number_of_moves != 0) {
                loseGameState();
                std::cout << "LOSSS!" << std::endl;
                return;
            }
        }

    }

    void revealAll()
    {
        for(int row=0; row<height; row++)
        {
            for(int col=0; col<width; col++)
            {
                cells[row][col]->reveal();
                if(cells[row][col]->isCellMine())
                {
                    cells[row][col]->reveal();
                }
            }
        }
    }

    void printBoard() const {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {

                std::cout << cells[i][j]->getSymbol() << ' ';
            }
            std::cout << std::endl;
        }
        std::cout<<revealed_cells<<std::endl;
        std::cout<< getMinesOnField();
    }

    void CheckWin()
    {
        if (revealed_cells == ((height*width)-getMinesOnField())){
            GameState = 2;
            std::cout<<"WIN";
        }
    }

};

class Game {
    Board board;
    char letter;
public:
    void checkGameState()
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
    void play() {
        int x, y;
        while (board.getGameState() == 0) {
            board.printBoard();
            std::cout << "Enter the coordinates (x, y) of the cell to reveal and then either F or R to command: ";
            std::cin >> x >> y >> letter;
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
};

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Game game;
    game.play();

    return 0;
}