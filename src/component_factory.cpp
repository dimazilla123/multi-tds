#include "component_factory.h"
#include <functional>

ECS::Component *ComponentFactory::make(std::type_index ind)
{
    //static std::unordered_map<std::type_index, ComponentFactory::Factory*> szs({
    //    {std::type_index(typeid(PositionComponent)), sizeof(PositionComponent)},
    //    {std::type_index(typeid(GraphicsComponent)), sizeof(GraphicsComponent)},
    //    {std::type_index(typeid(PlayerComponent)), sizeof(PlayerComponent)},
    //    {std::type_index(typeid(VelocityComponent)), sizeof(VelocityComponent)}
    //});
    using CompPtr = ECS::Component*;
    static std::unordered_map<std::type_index, std::function<CompPtr()>> cnstrctsrs({
        {std::type_index(typeid(PositionComponent)), ComponentFactory::templ_make<PositionComponent>},
        {std::type_index(typeid(GraphicsComponent)), ComponentFactory::templ_make<GraphicsComponent>},
        {std::type_index(typeid(PlayerComponent)), ComponentFactory::templ_make<PlayerComponent>},
        {std::type_index(typeid(VelocityComponent)), ComponentFactory::templ_make<VelocityComponent>}
    }
    );
    return (ECS::Component*)(cnstrctsrs[ind]());
}