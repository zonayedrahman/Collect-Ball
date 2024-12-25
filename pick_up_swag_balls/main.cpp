#include <SFML/Graphics.hpp>
#include "Game.h"



int main()
{

    // random seed
    srand(static_cast<unsigned>(time(0)));


    // initialize game object
    Game game;


    // game loop
    while (game.running()/* && !game.getEndGame()*/) {

        game.update();
        game.render();
    }


    // end 
    return 0;
}