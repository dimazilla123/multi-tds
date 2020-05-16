#ifndef GAME_H
#define GAME_H

#include "texture_manager.h"
#include <vector>
#include <SFML/Graphics.hpp>

class GameState;

class Game
{
public:
    Game();
    ~Game();

    void pushState(GameState *st);
    void popState();
    GameState *peekState();

    void loadTextures();

    void gameLoop();
    sf::RenderWindow window;
    TextureManager texman;
private:
    std::vector<GameState*> states;

};

#endif