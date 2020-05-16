#ifndef PLAYER_COMPONENT
#define PLAYER_COMPONENT

#include "component.h"

class PlayerComponent : public ECS::Component
{
public:
    PlayerComponent(){};
    ~PlayerComponent(){};
};

#endif