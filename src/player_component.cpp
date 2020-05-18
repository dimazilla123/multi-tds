#include "player_component.h"
#include "binutils.h"

void PlayerComponent::save(std::ostream &out) const
{
    binutils::write(out, *this);
}

void PlayerComponent::load(std::istream &in)
{
    binutils::read(in, *this);
}