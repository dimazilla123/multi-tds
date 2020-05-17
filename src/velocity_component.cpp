#include "velocity_component.h"

sf::Vector2f VelocityComponent::getMove() const
{
    return move;
}

void VelocityComponent::setMove(sf::Vector2f v)
{
    move = v;
}