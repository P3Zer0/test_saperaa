#include <cstdlib>
#include <ctime>
#include "Game.h"


int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Game game;
    game.play();

    return 0;
}