#ifndef POSITION_COMPONENT
#define POSITION_COMPONENT

#include "component.h"
#include <SFML/System/Vector2.hpp>

class PositionComponent : public ECS::Component
{
public:
    PositionComponent() {};
    PositionComponent(float x, float y, float a=0);
    void save(std::ostream &out) const;
    void load(std::istream &in);
    float getX() const;
    void setX(float v);
    float getY() const;
    void setY(float v);
    float getA() const;
    void setA(float v);
    sf::Vector2f getPosition() const;
    void setDirection(sf::Vector2f v);
    sf::Vector2f getDirection() const;
private:
    float x, y, a;
};

#endif