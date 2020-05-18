#ifndef COMPONENT_FACTORY
#define COMPONENT_FACTORY

#include <typeindex>
#include <unordered_map>

#include "component.h"

#include "position_component.h"
#include "graphics_component.h"
#include "player_component.h"
#include "velocity_component.h"

namespace ComponentFactory
{
    class Factoy
    {
    public:
        virtual ECS::Component *make() const = 0;
    };
    class PositionFactory : public Factoy
    {
        ECS::Component *make()
        {
            return new PositionComponent;
        }
    };
    class GraphicsFactory : public Factoy
    {
        ECS::Component *make()
        {
            return new GraphicsComponent;
        }
    };
    class PlayerFactory : public Factoy
    {
        ECS::Component *make()
        {
            return new PlayerComponent;
        }
    };
    class VelocityFactory : public Factoy
    {
        ECS::Component *make()
        {
            return new VelocityComponent;
        }
    };
    template<typename T>
    ECS::Component *templ_make()
    {
        return static_cast<ECS::Component*>(new T);
    }
    ECS::Component *make(std::type_index ind);
};

#endif