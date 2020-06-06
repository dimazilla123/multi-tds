#ifndef VELOCITY_SYSTEM_H
#define VELOCITY_SYSTEM_H

#include "system.h"

class VelocitySystem : public ECS::System
{
public:
    VelocitySystem();
    virtual void update(Game *game, ECS::EntityManager &em, float dt);
};

#endif