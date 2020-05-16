#include "game.h"
#include "game_state.h"

Game::Game()
{
    loadTextures();
    window.create(sf::VideoMode(300, 300), "TDS");
    window.setFramerateLimit(60);
}

void Game::loadTextures()
{
}

Game::~Game()
{
    while (peekState())
    {
        popState();
    }
}

void Game::pushState(GameState *st)
{
    states.push_back(st);
}

void Game::popState()
{
    states.pop_back();
}

GameState *Game::peekState()
{
    if (states.empty())
        return nullptr;
    return states.back();
}

void Game::gameLoop()
{
    sf::Clock cl;
    while (window.isOpen())
    {
        sf::Time passed = cl.restart();
        float dt = passed.asSeconds();
        if (!peekState())
            continue;
        peekState()->handleInput();
        peekState()->update(dt);
        window.clear();
        peekState()->draw(dt);
        window.display();
    }
}