#include "velocity_system.h"
#include "position_component.h"
#include "velocity_component.h"

VelocitySystem::VelocitySystem()
{
    
}

void VelocitySystem::update(Game *game, ECS::EntityManager &em, float dt)
{
    for (auto [ent, c] : em.getEntitiesByComponent<VelocityComponent>())
    {
        VelocityComponent *mc = (VelocityComponent*)(c);
        PositionComponent *pc = em.getComponent<PositionComponent>(ent);
        pc->setX(pc->getX() + mc->getMove().x * dt);
        pc->setY(pc->getY() + mc->getMove().y * dt);
        //if (std::abs(mc->getMove().x) + std::abs(mc->getMove().y) > 1e-3)
        //    pc->setA(-180 / std::acos(-1) * std::atan2(mc->getMove().x, mc->getMove().y));
    }
}