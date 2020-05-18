#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <unordered_map>
#include <set>
#include <typeindex>
#include <iostream>

#include "component.h"

namespace ECS
{
    using EntityId = uint64_t;
    using ComponentId = uint64_t;
    class EntityManager
    {
    public:
        EntityManager();
        ~EntityManager();
        EntityId newEntity();
        void destroyEntity(EntityId id);
        template<typename CompT, typename ...ARGS>
        CompT *addComponent(EntityId ent, ARGS&& ...args)
        {
            return (CompT*) (comps[std::type_index(typeid(CompT))][ent] = (Component*)(new CompT(std::forward<ARGS>(args)...)));
        }
        template<typename CompT>
        CompT* getComponent(EntityId ent)
        {
            auto it = comps[std::type_index(typeid(CompT))].find(ent);
            return (CompT*)(it != comps[std::type_index(typeid(CompT))].end() ? it->second : nullptr);
        }
        template<typename CompT>
        const std::unordered_map<EntityId, Component*> &getEntitiesByComponent()
        {
            return comps[std::type_index(typeid(CompT))];
        }
        void save(std::ostream &out) const;
        void load(std::istream &in);
    private:
        std::set<EntityId> ids;
        std::unordered_map<std::type_index, std::unordered_map<EntityId, Component*>> comps;
    };
};

#endif