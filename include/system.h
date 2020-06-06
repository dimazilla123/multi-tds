#ifndef SYSTEM_H
#define SYSTEM_H

#include "entity_manager.h"
#include "game.h"

namespace ECS
{
    class System
    {
    public:
        virtual ~System() {};
        virtual void update(Game *game, ECS::EntityManager &em, float dt) = 0;
    };
};

#endif