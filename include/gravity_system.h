#ifndef GRAVITY_SYSTEM
#define GRAVITY_SYSTEM

#include "system.h"

class GravitySystem : public ECS::System
{
public:
    GravitySystem();
    virtual void update(Game *game, ECS::EntityManager &em, float dt);
};

#endif