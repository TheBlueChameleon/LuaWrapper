#include <algorithm>
#include <string>
using namespace std::string_literals;

#include "luatable.hpp"
#include "entities.hpp"

#include "../util/luaerror.hpp"

namespace LuaWrapper
{
    const std::unordered_set<LuaTypeId> LuaTable::allowedKeyTypes =
    {
        LuaTypeId::LightUserData, LuaTypeId::Number, LuaTypeId::String
    };

    LuaTable::LuaTable() :
        LuaEntity(LuaTypeId::Table)
    {}

    LuaTable::LuaTable(const LuaTable& other) :
        LuaEntity(LuaTypeId::Table)
    {
        throw LuaNotImplementedError("Not yet implemented: Copy CTOR for LuaTable");
    }

    LuaTable::LuaTable(LuaTable&& other) :
        LuaEntity(LuaTypeId::Table),
        table(std::move(other.table))
    {}

    LuaTable& LuaTable::operator=(LuaTable&& other)
    {
        table = std::move(other.table);
        return *this;
    }

    LuaTable::~LuaTable()
    {
        for (const auto& [k, v] : table)
        {
            delete k;
            delete v;
        }
    }

    std::unordered_set<LuaTypeId> LuaTable::getAllowedKeyTypes()
    {
        return allowedKeyTypes;
    }

    bool LuaTable::operator==(const LuaTable& other) const
    {
        throw LuaNotImplementedError("Not implemented yet: compare equal tables");
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
    size_t LuaTable::size() const
    {
        return table.size();
    }

    bool LuaTable::empty() const
    {
        return table.empty();
    }

    std::pair<LuaEntity*, LuaEntity*> findInternal(const LuaEntity& key, const LuaTable::EntityMap& table)
    {
        const auto matchesKey = [&key](const std::pair<LuaEntity*, LuaEntity*>& keyValuePair)
        {
            return *(keyValuePair.first) == key;
        };

        const auto it = std::find_if(table.begin(), table.end(), matchesKey);

        if (it == table.end())
        {
            return std::make_pair(nullptr, nullptr);
        }
        else
        {
            return *it;
        }
    }

    LuaEntity* LuaTable::find(const LuaEntity& key) const
    {
        return findInternal(key, table).second;
    }

    void assertValidKey(const LuaEntity& key)
    {
        if (!LuaTable::getAllowedKeyTypes().contains(key.getTypeId()))
        {
            throw LuaInvalidArgumentError(
                "A key of type "s + key.getTypeId().getTypeName() + " may not be used."
            );
        }
    }

    bool LuaTable::insert(const LuaEntity& key, const LuaEntity& value)
    {
        assertValidKey(key);
        if (find(key))
        {
            return false;
        }

        LuaEntity* copiedKey   = LuaEntityFactory::makeLuaEntity(key);
        LuaEntity* copiedValue = LuaEntityFactory::makeLuaEntity(value);
        table[copiedKey] = copiedValue;

        return true;
    }

    bool LuaTable::insert(LuaEntity&& key, LuaEntity&& value)
    {
        assertValidKey(key);
        if (find(key))
        {
            return false;
        }

        LuaEntity* movedKey   = LuaEntityFactory::makeLuaEntity(std::move(key));
        LuaEntity* movedValue = LuaEntityFactory::makeLuaEntity(std::move(value));
        table[movedKey] = movedValue;

        return true;
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
