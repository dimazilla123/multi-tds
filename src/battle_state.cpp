#include "battle_state.h"
#include "graphics_component.h"
#include "position_component.h"
#include "player_component.h"
#include "ECS.h"

#include <SFML/Window.hpp>

#include <iostream>
#include <fstream>

const int TITLE = 16;

const int VIEW_RANGE = 10;

void create_unit(ECS::EntityManager &Entities, float x, float y)
{
    ECS::EntityId unit = Entities.newEntity();
    auto gc = Entities.addComponent<GraphicsComponent>(unit);
    gc->setTextureName("unit");
    gc->setFileName("img/unit.png");
    auto pc = Entities.addComponent<PositionComponent>(unit, x, y, 0);
}

void create_wall(ECS::EntityManager &Entities, float x, float y)
{
    ECS::EntityId unit = Entities.newEntity();
    auto gc = Entities.addComponent<GraphicsComponent>(unit);
    gc->setTextureName("wall");
    gc->setFileName("img/wall.png");
    auto pc = Entities.addComponent<PositionComponent>(unit, x, y, 0);
}

void create_player(ECS::EntityManager &Entities, float x, float y)
{
    ECS::EntityId unit = Entities.newEntity();
    auto gc = Entities.addComponent<GraphicsComponent>(unit);
    gc->setTextureName("unit");
    gc->setFileName("img/unit.png");
    auto pc = Entities.addComponent<PositionComponent>(unit, x, y, 0);
    Entities.addComponent<PlayerComponent>(unit);
}

BattleState::BattleState(Game *g)
{
    game = g;
    std::ifstream f("map.txt");
    std::string s;
    int y = 0;
    int w = 0;
    while (std::getline(f, s))
    {
        std::cerr << s << "\n";
        w = s.size();
        for (int x = 0; x < s.size(); ++x)
        {
            if (s[x] == 'U') create_unit(Entities, TITLE*x, TITLE*y);
            else if (s[x] == '#') create_wall(Entities, TITLE*x, TITLE*y);
            else if (s[x] == 'P') create_player(Entities, TITLE*x, TITLE*y);
        }
        y++;
    }
    for (auto [ent, c] : Entities.getEntitiesByComponent<GraphicsComponent>())
    {
        GraphicsComponent *gc = (GraphicsComponent*)(c);
        if (!game->texman.getTexture(gc->getTextureName()))
            game->texman.loadTexture(gc->getTextureName(), gc->getFileName());
        gc->getSprite().setTexture(*game->texman.getTexture(gc->getTextureName()));
    }
    if (Entities.getEntitiesByComponent<PlayerComponent>().empty())
    {
        view.setSize(sf::Vector2f(TITLE*w, TITLE*y));
        view.setCenter(TITLE*w * 0.5f, TITLE*y*0.5f);
    } else
    {
        view.setSize(2*TITLE*VIEW_RANGE, 2*TITLE*VIEW_RANGE);
        auto [ent, c] = *Entities.getEntitiesByComponent<PlayerComponent>().begin();
        auto pc = Entities.getComponent<PositionComponent>(ent);
        view.setCenter(pc->getX(), pc->getY());
    }
}

void BattleState::draw(float dt)
{
    game->window.setView(view);
    for (auto [id, gcc] : Entities.getEntitiesByComponent<GraphicsComponent>())
    {
        auto pc = Entities.getComponent<PositionComponent>(id);
        auto gc = Entities.getComponent<GraphicsComponent>(id);
        if (pc)
        {
            gc->getSprite().setPosition(pc->getX(), pc->getY());
            game->window.draw(gc->getSprite());
        }
    }
}

void BattleState::update(float dt)
{
}

void BattleState::handleInput()
{
    sf::Event e;
    while (game->window.pollEvent(e))
    {
        switch (e.type)
        {
            case sf::Event::Closed:
            game->window.close();
            break;
            //case sf::Event::Resized:
            //view.setSize(sf::Vector2f(game->window.getSize()));
            //break;
            case sf::Event::KeyPressed:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                view.move(-TITLE, 0);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                view.move(TITLE, 0);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                view.move(0, -TITLE);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                view.move(0, TITLE);
            break;
        }
    }
}