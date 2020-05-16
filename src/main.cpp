#include <iostream>

#include "position_component.h"
#include "battle_state.h"

#include "game.h"

int main(int argc, char const *argv[])
{
    Game game;

    game.pushState(new BattleState(&game));
    game.gameLoop();


    return 0;
}