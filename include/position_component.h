#ifndef POSITION_COMPONENT
#define POSITION_COMPONENT

#include "component.h"

class PositionComponent : public ECS::Component
{
public:
    PositionComponent(float x, float y, float a=0);
    float getX() const;
    void setX(float v);
    float getY() const;
    void setY(float v);
    float getA() const;
    void setA(float v);
private:
    float x, y, a;
};

#endif