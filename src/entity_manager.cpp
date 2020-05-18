#include "entity_manager.h"
#include "binutils.h"

#include "component_factory.h"

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
        {
            auto it = map.find(id);
            if (it != map.end())
                map.erase(it);
        }
        ids.erase(ids.find(id));
    }

    void EntityManager::save(std::ostream &out) const
    {
        binutils::write(out, ids.size());
        for (auto id : ids)
            binutils::write(out, id);
        binutils::write(out, comps.size());
        for (auto &[type, map] : comps)
        {
            binutils::write(out, map.size());
            binutils::write(out, type);
            for (auto [entid, comp] : map)
            {
                binutils::write(out, entid);
                comp->save(out);
            }
        }
    }
    void EntityManager::load(std::istream &in)
    {
        while (!ids.empty())
            destroyEntity(*ids.begin());
        size_t sz;
        binutils::read(in, sz);
        for (int i = 0; i < sz; ++i)
        {
            EntityId id;
            binutils::read(in, id);
            ids.insert(id);
        }
        binutils::read(in, sz);
        for (int i = 0; i < sz; ++i)
        {
            size_t pairsz;
            binutils::read(in, pairsz);
            size_t type;
            binutils::read(in, type);
            for (int i = 0; i < pairsz; ++i)
            {
                EntityId ent;
                binutils::read(in, ent);
                comps[type][ent] = ComponentFactory::make(type);
                comps[type][ent]->load(in);
            }
        }
    }
};