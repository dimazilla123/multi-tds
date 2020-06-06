#ifndef COMPONENT_FACTORY
#define COMPONENT_FACTORY

#include <typeindex>
#include <unordered_map>

#include "component.h"

namespace ComponentFactory
{
    template<typename T>
    ECS::Component *templ_make()
    {
        return static_cast<ECS::Component*>(new T);
    }
    ECS::Component *make(size_t ind);
};

#endif