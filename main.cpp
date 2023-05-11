#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>

class Cell {
protected:
    bool isRevealed;
    bool isMine;
    bool isNumber;
public:
    Cell() : isRevealed(false) {}
    virtual char getSymbol() const = 0;
    bool reveal() { return isRevealed = true; }
    bool isCellRevealed() const { return isRevealed; }
    bool isCellMine() {return isMine; }
    bool isCellNumber() {return isNumber;}
};

class EmptyCell : public Cell {
public:
    //EmptyCell() {}
    char getSymbol() const override {
        if (isCellRevealed())
            return ' ';
        else
            return '-';
    }
};

class NumberCell : public Cell {
    int number;
public:
    NumberCell(int num) : number(num) {}
    char getSymbol() const override {
        if (isCellRevealed())
            return '0' + number;
        else
            return '-';
    }
};

class MineCell : public Cell {
private:
    bool isMine;
public:
     bool getMine() {
         return this->isMine;
     }
    char getSymbol() const override {
        if (isCellRevealed())
            return 'X';
        else
            return '-';
    }
};

class Board  {
    Cell* cells[10][10];
public:
    Cell* getCell(int x, int y) {
        return cells[x][y];
    }

    const Cell* getCellsPointer() const {
        return reinterpret_cast<const Cell *>(&cells);
    }
    Board() {
    //void SetMines(int number){
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                if (rand() % 10 == 0)
                    cells[i][j] = new MineCell();
                else                                //To na dole działa tylko jak jest random numbers????
                    cells[i][j] = new EmptyCell();//NumberCell(0);//cells[i][j] = new EmptyCell();//new NumberCell(number)//(rand() % 9 + 1);
                //calculateMines(i,j);
                    /*
                    {
                    cells[i-1][j-1] = new NumberCell(rand() % 9 + 1);
                    cells[i-1][j] = new NumberCell(rand() % 9 + 1);
                    cells[i-1][j+1] = new NumberCell(rand() % 9 + 1);
                    cells[i+1][j-1] = new NumberCell(rand() % 9 + 1);
                    cells[i+1][j] = new NumberCell(rand() % 9 + 1);
                    cells[i][j-1] = new NumberCell(rand() % 9 + 1);
                    cells[i][j+1] = new NumberCell(rand() % 9 + 1);
                    cells[i+1][j+1] = new NumberCell(rand() % 9 + 1);
                }//
                 */
            }
        }
    }
/*
    ~Board() {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                delete cells[i][j];
            }
        }
    }
*/
    void revealCell(int x, int y) {
        if (x < 0 || x >= 10 || y < 0 || y >= 10) {
            std::cout << "Invalid cell coordinates!" << std::endl;
            return;
        }

        if (cells[x][y]->isCellRevealed()) {
            std::cout << "Cell already revealed!" << std::endl;
            return;
        }

        if (cells[x][y]->isCellMine()) {
            return;
        }


        cells[x][y]->reveal();// Nie może być revealCell(); ???
        /*
            if (cells[x][y]->isCellRevealed()) {
                 std::cout << "Cell already revealed!" << std::endl;
                 return;
        }*/
        cells[x-1][y-1]->reveal();
        cells[x-1][y]->reveal();
        cells[x-1][y+1]->reveal();
        cells[x+1][y-1]->reveal();
        cells[x+1][y]->reveal();
        cells[x][y-1]->reveal();
        cells[x][y+1]->reveal();
        cells[x+1][y+1]->reveal();

    }

    void revealAll()
    {
        for (int i=0;i<10;i++)
        {
            for (int j=0;i<10;i++)
            {
                cells[i][j]->reveal();
            }
        }
    }

    void calculateMines(int x, int y)
    {
        int numRows = 10;//cells.size();
        int numCols = 10;// cells[0].size();

        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < numCols; col++) {
                if (!cells[row][col]->isCellMine()) {
                    int count = 0;
                    for (int i = -1; i <= 1; i++) {
                        for (int j = -1; j <= 1; j++) {
                            int r = row + i;
                            int c = col + j;
                            if (cells[r][c]->isCellMine()) {
                                count++;
                                std::cout<<"COUNT W LOOP: "<<count;
                            }
                        }
                    }
                    std::cout<<"Count poza:" <<count;
                    cells[row][col] = new NumberCell(8);//NumberCell::getSymbol(count);// = count;//static_cast<NumberCell*>(cells[row][col])->setAdjacentMines(count);
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
    }

        bool AreThereMines(int x, int y) //making sure the 1st field is not a mine, will work on later
        {
            for (int i = 0; i<10; i++)
                for (int j = 0; j<10; j++)
                {
                   // if (dynamic_cast<MineCell *>(board.getCell(i, j)) != nullptr)
                        return 1;
                }
            return 0;
        }
    bool calculateAdjacentMines(int x,int y) {
        int numRows = 10;//cells.size();
        int numCols = 10;// cells[0].size();
        //for (int row = 0)







    }
};

class Game : public Board {
    Board board;
public:
    void play() {
        int x, y;
        while (true) {
            board.printBoard();
            std::cout << "Enter the coordinates (x, y) of the cell to reveal: ";
            std::cin >> x >> y;
            board.revealCell(x, y);
            Cell* cell = board.getCell(x, y);
            if (!(dynamic_cast<MineCell*>(board.getCell(x,y)) == nullptr))
                {
                    revealAll();
                std::cout<<"You hit a mine! Too bad, you lost!"<<std::endl;
                    getch();
                    return;
                }
            system("cls");//(cell->MineCell()) {
            }//if (board.getCellsPointer[x][y]->MineCell()) //dynamic_cast<MineCell *>(board.getCells()[x][y]) == nullptr)//
        }
    };
//};

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Game game;
    game.play();

    return 0;
}