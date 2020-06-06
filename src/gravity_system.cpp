#include "gravity_system.h"
#include "gravity_component.h"
#include "velocity_component.h"
#include "position_component.h"

#include <cmath>

GravitySystem::GravitySystem()
{

}

void GravitySystem::update(Game *game, ECS::EntityManager &em, float dt)
{
    for (auto [u1, c1] : em.getEntitiesByComponent<GravityComponent>())
    {
        for (auto [u2, c2] : em.getEntitiesByComponent<GravityComponent>())
        {
            auto vc = em.getComponent<VelocityComponent>(u2);
            const float G = 1;
            auto gc1 = em.getComponent<GravityComponent>(u1);
            auto gc2 = em.getComponent<GravityComponent>(u2);
            auto pc1 = em.getComponent<PositionComponent>(u1);
            auto pc2 = em.getComponent<PositionComponent>(u2);
            sf::Vector2f r = pc2->getPosition() - pc1->getPosition();
            float rl = std::sqrt(r.x * r.x + r.y * r.y);
            if (u1 != u2 && vc && rl <= gc1->getRadius())
                vc->setMove(vc->getMove() - G * gc1->getMass() * r / (rl*rl*rl) * dt);
        }
    }
}