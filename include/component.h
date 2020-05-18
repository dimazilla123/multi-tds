#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>

namespace ECS
{
    class Component
    {
    public:
        virtual void save(std::ostream &out) const;
        virtual void load(std::istream &in);
    private:
    };
};

#endif