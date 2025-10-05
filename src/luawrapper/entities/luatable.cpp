#include "luatable.hpp"
#include "entities.hpp"

#include "../util/luaerror.hpp"

namespace LuaWrapper
{
    LuaTable::LuaTable() :
        LuaEntity(LuaTypeId::Table)
    {}

    LuaTable::~LuaTable()
    {
        for (const auto& [k, v] : table)
        {
            delete k;
            delete v;
        }
    }

    LuaTypeId LuaTable::getStaticTypeId()
    {
        return LuaTypeId::Table;
    }

    void LuaTable::pushToLua(lua_State* L) const
    {
        lua_newtable(L);

        for (const auto& [k, v] : table)
        {
            k->pushToLua(L);
            v->pushToLua(L);
            lua_settable(L, -3);
        }
    }

    void LuaTable::fetchFromLua(lua_State* L)
    {
        LuaTypeId tid;
        LuaEntity* key;
        LuaEntity* value;

        lua_pushnil(L);             // lua_next will interpret this as "begin with first key"
        while (lua_next(L, -2))     // pops key, pushes [value, next_key]; returns null if no next_key
        {
            tid = lua_type(L, -1);
            value = LuaEntityFactory::makeLuaEntityFromTypeId(tid);
            value->popFromLua(L);

            tid = lua_type(L, -1);
            key = LuaEntityFactory::makeLuaEntityFromTypeId(tid);
            key->popFromLua(L);

            table[key] = value;
        }

        // talbe is now on top of stack
    }

    bool LuaTable::isTable() const
    {
        return true;
    }

    const LuaTable::EntityMap& LuaTable::getValue() const
    {
        return table;
    }

    void LuaTable::setValue(const EntityMap& newValue)
    {
        table = newValue;
    }

    std::string LuaTable::to_string() const
    {
        throw LuaNotImplementedError("Not implemented yet: table repr");

        /* INTENDED OUTPUT:
         * { TABLE:
         *   key1 = value1
         *   key2 = { TABLE:
         *     key2.1 = value2.1
         *     ...
         *   }
         * }
         */
    }
}

namespace std
{
    size_t hash<LuaWrapper::LuaTable>::operator()(const LuaWrapper::LuaTable& luaEntity) const
    {
        throw LuaWrapper::LuaNotImplementedError("Not yet implemented: computing hash for LuaTable");

        size_t result = 0;
        for (const auto [k, v] : luaEntity.getValue())
        {
            // order of entries irrelevant => sum of components is fine (commutivity of + is no issue here)
            // correlate key and value so that [{a->A}, {b->B}] and [{a->B}, {b->A}] are distinct.
            // bitwise xor is fast and does the job.
            result += (k->getHash() ^ v->getHash());
        }

        return result;
    }
}
