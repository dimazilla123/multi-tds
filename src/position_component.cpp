#include "position_component.h"

PositionComponent::PositionComponent(float x, float y, float z) : x(x), y(y), z(z)
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