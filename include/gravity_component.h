#ifndef GRAVITY_COMPONENT
#define GRAVITY_COMPONENT

#include "component.h"

class GravityComponent : public ECS::Component
{
public:
    GravityComponent(float mass=1, float range=0);

    void save(std::ostream &out) const;
    void load(std::istream &in);

    float getMass() const;
    float getRadius() const;
    void setMass(float m);
    void setRadius(float r);

private:
    float m, r;
};

#endif