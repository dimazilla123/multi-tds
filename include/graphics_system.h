#ifndef GRAPHICS_SYSTEM
#define GRAPHICS_SYSTEM

#include "system.h"


class GraphicsSystem : public ECS::System
{
public:
    GraphicsSystem();
    virtual void update(Game *game, ECS::EntityManager &em, float dt);
};

#endif