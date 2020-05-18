#include "component.h"
#include "binutils.h"
#include <typeindex>

void ECS::Component::save(std::ostream &out) const
{
    binutils::write(out, *this);
}

void ECS::Component::load(std::istream &in)
{
    binutils::read(in, *this);
}