#include "battle_state.h"
#include "graphics_component.h"
#include "position_component.h"
#include "player_component.h"
#include "velocity_component.h"
#include "gravity_component.h"
#include "ECS.h"

#include "graphics_system.h"
#include "velocity_system.h"
#include "gravity_system.h"

#include "binutils.h"

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
    //VelocityComponent *mc = Entities.addComponent<VelocityComponent>(unit);
    //mc->setMove(sf::Vector2f(10, 10));
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
    Entities.addComponent<GravityComponent>(unit, 1, 0);
}

void create_planet(ECS::EntityManager &Entities, float x, float y, float m, float r)
{
    ECS::EntityId unit = Entities.newEntity();
    auto pc = Entities.addComponent<PositionComponent>(unit, x, y);
    Entities.addComponent<PlayerComponent>(unit);
    Entities.addComponent<GravityComponent>(unit, m, r);
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
            else if (s[x] == 'R') create_planet(Entities, TITLE*x, TITLE*y, 100000, TITLE*4);
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
    systems.push_back(new GravitySystem());
    systems.push_back(new VelocitySystem());
}

BattleState::~BattleState()
{
    while (!systems.empty())
    {
        delete systems.back();
        systems.pop_back();
    }
}

void BattleState::draw(float dt)
{
    static GraphicsSystem gs;
    game->window.setView(view);
    if (auto pc = Entities.getComponent<PositionComponent>(player))
    {
        view.setCenter(pc->getX(), pc->getY());
    }
    gs.update(game, Entities, dt);
}

void BattleState::update(float dt)
{
    for (auto s : systems)
        s->update(game, Entities, dt);
}

void BattleState::handleInput(float dt)
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
                is_pressed[e.key.code] = true;
                break;
            case sf::Event::KeyReleased:
                is_pressed[e.key.code] = false;
                break;
        }
    }
    const sf::Keyboard::Key nums[] = {
        sf::Keyboard::Key::Num0,
        sf::Keyboard::Key::Num1,
        sf::Keyboard::Key::Num2,
        sf::Keyboard::Key::Num3,
        sf::Keyboard::Key::Num4,
        sf::Keyboard::Key::Num5,
        sf::Keyboard::Key::Num6,
        sf::Keyboard::Key::Num7,
        sf::Keyboard::Key::Num8,
        sf::Keyboard::Key::Num9
    };
    for (int i = 0; i < 10; ++i)
    {
        std::string filename = "0.dat";
        filename[0] += i;
        if (is_pressed[nums[i]])
        {
            if (is_pressed[sf::Keyboard::Key::LShift])
            {
                std::ifstream s(filename);
                Entities.load(s);
                loadTextures();
                s.close();
            } else
            {
                std::ofstream s(filename);
                Entities.save(s);
                s.close();
            }
        }
    }
    if (is_pressed[sf::Keyboard::Key::Space]) mc->setMove(mc->getMove() + 100.0f * direction / std::sqrt(direction.x * direction.x + direction.y * direction.y) * dt);
    //else mc->setMove({0, 0});
    sf::Vector2f mouse_pos = game->window.mapPixelToCoords(sf::Mouse::getPosition(game->window));
    sf::Vector2f cur = {pc->getX(), pc->getY()};
    direction = (mouse_pos - cur);
    direction /= std::sqrt(direction.x * direction.x + direction.y * direction.y);
    pc->setA(-180 / std::acos(-1) * std::atan2(direction.x, direction.y));
}