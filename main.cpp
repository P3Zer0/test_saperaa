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
    /*
    void losuj_pozycje (int niex, int niey)
    {
        time_t t;
        int poz_x, poz_y;
        int ilosc = 10;

        srand((unsigned)time(&t));

        while (ilosc>0)
        {
            poz_x = rand()%10;
            poz_y = rand()%10;

            if ((dynamic_cast<MineCell *>(cells(poz_x, poz_y)) != nullptr) && poz_x!=niex && poz_y!=niey)
            {
                cells[poz_x][poz_y] = new MineCell();
                ilosc--;
            }
        }
    }*/

public:
    Cell* getCell(int x, int y) {
        return cells[x][y];
    }

    const Cell* getCellsPointer() const { //to chyba niepotrzebne
        return reinterpret_cast<const Cell *>(&cells);
    }
    Board()
    {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                if (rand() % 10 == 0)
                    cells[i][j] = new MineCell();
                else
                    cells[i][j] = new EmptyCell();//NumberCell(0);//cells[i][j] = new EmptyCell();//new NumberCell(number)//(rand() % 9 + 1);
                //calculateMines(i,j);

            }
        }
    }
    /*
    Board(int numRows, int numCols, int numMines) {
        //cells.resize(numRows, std::vector<Cell*>(numCols, new NumberCell)); !!!!!!!!!
        //setMines();
        //calculateAdjacentMines(int x,int y);
    }
    */

    void SetMines(int number){
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                if (rand() % 10 == 0)
                    cells[i][j] = new MineCell();
                else
                    cells[i][j] = new EmptyCell();//NumberCell(0);//cells[i][j] = new EmptyCell();//new NumberCell(number)//(rand() % 9 + 1);
                //calculateMines(i,j);

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
        if (x<0 || x>9) return; // poza tablicą wyjście
        if (y<0 || y>9) return; // poza tablicą wyjście
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


        cells[x][y]->reveal();// Nie może być revealCell(); ??? chciałbym tu mieć rekurencję
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
        for (int row = 0; row < 10; row++) {
            for (int col = 0; col < 10; col++) {
                //std::cout<<"2. loop";
                if (cells[row][col]->isCellMine()) {
                    std::cout<<"1. warunek";
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

        bool AreThereMines() //making sure the 1st field is not a mine, will work on this later
        {
            for (int i = 0; i<10; i++) {
                for (int j = 0; j < 10; j++) {
                    if (getCell(i, j)->isCellMine())//(dynamic_cast<MineCell *>(board.getCell(i, j)) != nullptr)
                        return true;
                }
            }
            return false;
        }
    bool calculateAdjacentMines(int x,int y) {
        int numRows = 10;//cells.size();
        int numCols = 10;// cells[0].size();
        //for (int row = 0)







    }
};

class Game : public Board {
    Board board;
    int koniec=0;
public:
    void sterowanie() {
        //int poz_x,poz_y;
        int poz_x = 0, poz_y = 0, o_poz_x = 1, o_poz_y = 1;
        while (true) {
            if ((GetKeyState(enter) & 0x8000)) {

                if (AreThereMines()) {
                    revealAll();
                    std::cout << "You hit a mine! Too bad, you lost!" << std::endl;
                    getch();
                    return;
                }

                /*
                revealCell(poz_x, poz_y); //odkrywanie pól
                board.printBoard();
                return;}*/

                if (dynamic_cast<MineCell *>(board.getCell(poz_x, poz_y)) != nullptr)//(cells[poz_x][poz_y]->isCellMine()) //trafiles na mine
                    koniec = 2;

                revealCell(poz_x, poz_y); //odkrywanie pól
                board.printBoard(); // wyswietl plansze

                /*
            if ((GetKeyState(flaga) & 0x8000))
            {
                if (board.getCell(poz_x,poz_y)){}//(plansza[poz_x][poz_y].odkryte==true) {} //odkryte, nic sie nie dzieje

                else if (plansza[poz_x][poz_y].czyFlaga==false && plansza[poz_x][poz_y].odkryte==false)
                {
                    plansza[poz_x][poz_y].czyFlaga=true;
                }
                else if (plansza[poz_x][poz_y].czyFlaga==true && plansza[poz_x][poz_y].odkryte==false)
                {
                    plansza[poz_x][poz_y].czyFlaga=false;
                }
            }
                 */

                if ((GetKeyState(strzalka_prawo) & 0x8000) && poz_x < 9) poz_x++;
                if ((GetKeyState(strzalka_lewo) & 0x8000) && poz_x > 0) poz_x--;
                if ((GetKeyState(strzalka_dol) & 0x8000) && poz_y < 9) poz_y++;
                if ((GetKeyState(strzalka_gora) & 0x8000) && poz_y > 0) poz_y--;

                //if (o_poz_y == poz_y && o_poz_x == poz_x) return; //jeżeli nie ma ruchu wyjdz

                o_poz_y = poz_y; //zmienne pomocnicza do warunku wyżej
                o_poz_x = poz_x;

                board.printBoard();// wyswietl plansze
                system("cls");
            }
        }
    }
    void play() {
        int x, y;
        while (true) {
            std::cout<< AreThereMines();
            board.printBoard();
            std::cout << "Enter the coordinates (x, y) of the cell to reveal: ";
            std::cin >> x >> y;


            board.revealCell(x, y);
            calculateMines(x,y);
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

        //Sleep(60);
        game.play();
        //if (sprawdz_czy_wygrana()==true) koniec=1;


    return 0;
}