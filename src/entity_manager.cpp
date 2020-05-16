#include "entity_manager.h"

#include <cassert>

namespace ECS
{
    EntityManager::EntityManager()
    {
        ids.insert(0);
    }
    EntityManager::~EntityManager()
    {
        for (auto &[type, map] : comps)
        {
            for (auto [ent, c] : map)
            {
                delete c;
            }
        }
    }
    EntityId EntityManager::newEntity()
    {
        EntityId ans = *(ids.end()--) + 1;
        ids.insert(ans);
        return ans;
    }
    void EntityManager::destroyEntity(EntityId id)
    {
        assert(ids.find(id) != ids.end());
        for (auto &[type, map] : comps)
            map.erase(map.find(id));
        ids.erase(ids.find(id));
    }
};