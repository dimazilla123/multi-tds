#include "graphics_system.h"
#include "graphics_component.h"
#include "position_component.h"
#include "gravity_component.h"

GraphicsSystem::GraphicsSystem()
{

}

void GraphicsSystem::update(Game *game, ECS::EntityManager &Entities, float dt)
{
    sf::CircleShape circ(0.0f);
    for (auto [id, grav_c] : Entities.getEntitiesByComponent<GravityComponent>())
    {
        auto pc = Entities.getComponent<PositionComponent>(id);
        auto grc = Entities.getComponent<GravityComponent>(id);
        if (pc && grc->getRadius() > 0)
        {
            circ.setRadius(grc->getRadius());
            circ.setPosition(pc->getPosition());
            circ.setOrigin(grc->getRadius(), grc->getRadius());
            circ.setFillColor(sf::Color(100, 250, 50));
            game->window.draw(circ);
        }
    }
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