#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "game.h"

class GameState
{
public:
    Game* game;

    virtual void draw(float dt) = 0;
    virtual void update(float dt) = 0;
    virtual void handleInput(float dt) = 0;
};

#endif