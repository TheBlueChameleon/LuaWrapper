#ifndef LUATABLE_HPP
#define LUATABLE_HPP

#include <unordered_map>

#include "luaentity.hpp"

namespace LuaWrapper
{
    class LuaTable : public LuaEntity
    {
        public:
            using EntityMap = std::unordered_map<LuaEntity*, LuaEntity*>;

        private:
            EntityMap table;

        public:
            LuaTable();
            ~LuaTable();

            static LuaTypeId getStaticTypeId();

            void pushToLua(lua_State* L) const;
            void fetchFromLua(lua_State* L);

            bool isTable() const;

            const EntityMap& getValue() const;
            void setValue(const EntityMap& newValue);

            std::string to_string() const;

            /* TODO
             * Add Iterator
             */
    };
}

namespace std
{
    template<>
    struct hash<LuaWrapper::LuaTable>
    {
        size_t operator()(const LuaWrapper::LuaTable& luaEntity) const;
    };
}

#endif // LUATABLE_HPP
