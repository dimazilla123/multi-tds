#include "gravity_component.h"
#include "binutils.h"

GravityComponent::GravityComponent(float mass, float range) : m(mass), r(range)
{

}

void GravityComponent::save(std::ostream &out) const
{
    binutils::write(out, m);
    binutils::write(out, r);
}

void GravityComponent::load(std::istream &in)
{
    binutils::read(in, m);
    binutils::read(in, r);
}

float GravityComponent::getMass() const
{
    return m;
}

float GravityComponent::getRadius() const
{
    return r;
}

void GravityComponent::setMass(float M)
{
    m = M;
}

void GravityComponent::setRadius(float R)
{
    r = R;
}