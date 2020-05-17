#include "position_component.h"

PositionComponent::PositionComponent(float x, float y, float z, float a) : x(x), y(y), z(z), a(a)
{

}
float PositionComponent::getX() const
{
    return x;
}
float PositionComponent::getY() const
{
    return y;
}
float PositionComponent::getZ() const
{
    return z;
}
float PositionComponent::getA() const
{
    return a;
}

void PositionComponent::setX(float v)
{
    x = v;
}
void PositionComponent::setY(float v)
{
    y = v;
}
void PositionComponent::setZ(float v)
{
    z = v;
}
void PositionComponent::setA(float v)
{
    a = v;
}