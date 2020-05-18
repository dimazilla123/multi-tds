#include "battle_state.h"
#include "graphics_component.h"
#include "position_component.h"
#include "player_component.h"
#include "velocity_component.h"
#include "ECS.h"

#include <SFML/Window.hpp>

#include <iostream>
#include <fstream>
#include <cmath>

const int TITLE = 16;

const int VIEW_RANGE = 10;

void create_unit(ECS::EntityManager &Entities, float x, float y)
{
    ECS::EntityId unit = Entities.newEntity();
    auto gc = Entities.addComponent<GraphicsComponent>(unit);
    gc->setTextureName("unit");
    gc->setFileName("img/unit.png");
    auto pc = Entities.addComponent<PositionComponent>(unit, x, y);
    VelocityComponent *mc = Entities.addComponent<VelocityComponent>(unit);
    mc->setMove(sf::Vector2f(0, 0));
}

void create_wall(ECS::EntityManager &Entities, float x, float y)
{
    ECS::EntityId unit = Entities.newEntity();
    auto gc = Entities.addComponent<GraphicsComponent>(unit);
    gc->setTextureName("wall");
    gc->setFileName("img/wall.png");
    auto pc = Entities.addComponent<PositionComponent>(unit, x, y);
}

void create_player(ECS::EntityManager &Entities, float x, float y)
{
    ECS::EntityId unit = Entities.newEntity();
    auto gc = Entities.addComponent<GraphicsComponent>(unit);
    gc->setTextureName("unit");
    gc->setFileName("img/unit.png");
    gc->getSprite().setColor(sf::Color(0, 255, 0));
    auto pc = Entities.addComponent<PositionComponent>(unit, x, y);
    Entities.addComponent<PlayerComponent>(unit);
    Entities.addComponent<VelocityComponent>(unit);
}

void BattleState::loadTextures()
{
    for (auto [ent, c] : Entities.getEntitiesByComponent<GraphicsComponent>())
    {
        GraphicsComponent *gc = (GraphicsComponent*)(c);
        if (!game->texman.getTexture(gc->getTextureName()))
            game->texman.loadTexture(gc->getTextureName(), gc->getFileName());
        gc->getSprite().setTexture(*game->texman.getTexture(gc->getTextureName()));
        gc->getSprite().setOrigin(TITLE * 0.5f, TITLE * 0.5f);
    }
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
    loadTextures();
    if (Entities.getEntitiesByComponent<PlayerComponent>().empty())
    {
        //view.setSize(sf::Vector2f(TITLE*w, TITLE*y));
        view.setCenter(TITLE*w * 0.5f, TITLE*y*0.5f);
    } else
    {
        auto [ent, c] = *Entities.getEntitiesByComponent<PlayerComponent>().begin();
        auto pc = Entities.getComponent<PositionComponent>(ent);
        view.setCenter(pc->getX(), pc->getY());
        player = ent;
    }
    f.close();
}

void BattleState::draw(float dt)
{
    if (auto pc = Entities.getComponent<PositionComponent>(player))
    {
        view.setCenter(pc->getX(), pc->getY());
    }
    game->window.setView(view);
    for (auto [id, gcc] : Entities.getEntitiesByComponent<GraphicsComponent>())
    {
        auto pc = Entities.getComponent<PositionComponent>(id);
        auto gc = Entities.getComponent<GraphicsComponent>(id);
        if (pc)
        {
            gc->getSprite().setPosition(pc->getX(), pc->getY());
            gc->getSprite().setRotation(pc->getA());
            game->window.draw(gc->getSprite());
        }
    }
}

void BattleState::update(float dt)
{
    for (auto [ent, c] : Entities.getEntitiesByComponent<VelocityComponent>())
    {
        VelocityComponent *mc = (VelocityComponent*)(c);
        PositionComponent *pc = Entities.getComponent<PositionComponent>(ent);
        pc->setX(pc->getX() + mc->getMove().x * dt);
        pc->setY(pc->getY() + mc->getMove().y * dt);
        if (std::abs(mc->getMove().x) + std::abs(mc->getMove().y) > 1e-3)
            pc->setA(-180 / std::acos(-1) * std::atan2(mc->getMove().x, mc->getMove().y));
    }
}

void BattleState::handleInput()
{
    sf::Event e;
    PositionComponent *pc = Entities.getComponent<PositionComponent>(player);
    VelocityComponent *mc = Entities.getComponent<VelocityComponent>(player);
    while (game->window.pollEvent(e))
    {
        switch (e.type)
        {
            case sf::Event::Closed:
            game->window.close();
            break;
            case sf::Event::Resized:
            view.setSize(sf::Vector2f(game->window.getSize()));
            break;
            case sf::Event::KeyPressed:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                mc->setMove(100.0f * direction / std::sqrt(direction.x * direction.x + direction.y * direction.y));
                std::cerr << "Key pressed" << "\n";
            }
            case sf::Event::KeyReleased:
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                mc->setMove(sf::Vector2f(0, 0));
                std::cerr << "Key released" << "\n";
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T))
            {
                std::ofstream s("save.dat");
                Entities.save(s);
                s.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y))
            {
                std::ifstream s("save.dat");
                Entities.load(s);
                loadTextures();
                s.close();
            }
            break;
            case sf::Event::MouseMoved:
            sf::Vector2f mouse_pos = game->window.mapPixelToCoords(sf::Mouse::getPosition(game->window));
            sf::Vector2f cur = {pc->getX(), pc->getY()};
            direction = (mouse_pos - cur);
            direction /= std::sqrt(direction.x * direction.x + direction.y * direction.y);
            //pc->setA(-180 / std::acos(-1) * std::atan2(direction.x, direction.y));
            break;
        }
    }
}