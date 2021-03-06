#include "velocity_component.h"
#include "binutils.h"

void VelocityComponent::save(std::ostream &out) const
{
    binutils::write(out, move);
}

void VelocityComponent::load(std::istream &in)
{
    binutils::read(in, move);
}

sf::Vector2f VelocityComponent::getMove() const
{
    return move;
}

void VelocityComponent::setMove(sf::Vector2f v)
{
    move = v;
}