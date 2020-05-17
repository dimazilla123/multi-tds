#include "position_component.h"
#include <cmath>

PositionComponent::PositionComponent(float x, float y, float a) : x(x), y(y), a(a)
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
void PositionComponent::setA(float v)
{
    a = v;
}

sf::Vector2f PositionComponent::getPosition() const
{
    return sf::Vector2f(x, y);
}

sf::Vector2f PositionComponent::getDirection() const
{
    return sf::Vector2f(sin(a / 360 * std::acos(-1)), cos(a / 360 * std::acos(-1)));
}