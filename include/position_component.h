#ifndef POSITION_COMPONENT
#define POSITION_COMPONENT

#include "component.h"

class PositionComponent : public ECS::Component
{
public:
    PositionComponent(float x, float y, float z, float a=0);
    float getX() const;
    void setX(float v);
    float getY() const;
    void setY(float v);
    float getZ() const;
    void setZ(float v);
    float getA() const;
    void setA(float v);
private:
    float x, y, z, a;
};

#endif