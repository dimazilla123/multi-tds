#include "component_factory.h"
#include "position_component.h"
#include "graphics_component.h"
#include "player_component.h"
#include "velocity_component.h"
#include "gravity_component.h"
#include <functional>

ECS::Component *ComponentFactory::make(size_t ind)
{
    //static std::unordered_map<std::type_index, ComponentFactory::Factory*> szs({
    //    {std::type_index(typeid(PositionComponent)), sizeof(PositionComponent)},
    //    {std::type_index(typeid(GraphicsComponent)), sizeof(GraphicsComponent)},
    //    {std::type_index(typeid(PlayerComponent)), sizeof(PlayerComponent)},
    //    {std::type_index(typeid(VelocityComponent)), sizeof(VelocityComponent)}
    //});
    using CompPtr = ECS::Component*;
    static std::unordered_map<size_t, std::function<CompPtr()>> cnstrctsrs({
        {typeid(PositionComponent).hash_code(), ComponentFactory::templ_make<PositionComponent>},
        {typeid(GraphicsComponent).hash_code(), ComponentFactory::templ_make<GraphicsComponent>},
        {typeid(PlayerComponent).hash_code(), ComponentFactory::templ_make<PlayerComponent>},
        {typeid(VelocityComponent).hash_code(), ComponentFactory::templ_make<VelocityComponent>},
        {typeid(GravityComponent).hash_code(), ComponentFactory::templ_make<GravityComponent>},
    }
    );
    return (ECS::Component*)(cnstrctsrs[ind]());
}