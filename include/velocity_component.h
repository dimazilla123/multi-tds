#ifndef MOVE_COMPONENT_H
#define MOVE_COMPONENT_H

#include <SFML/System/Vector2.hpp>
#include "component.h"

class VelocityComponent : public ECS::Component
{
public:
    //VelocityComponent();
    //~VelocityComponent();
    sf::Vector2f getMove() const;
    void setMove(sf::Vector2f v);
private:
    sf::Vector2f move = sf::Vector2f(0, 0);
};

#endif