#ifndef LUATABLE_HPP
#define LUATABLE_HPP

#include <unordered_map>
#include <unordered_set>

#include "luaentity.hpp"

namespace LuaWrapper
{
    class LuaTable : public LuaEntity
    {
        public:
            using EntityMap = std::unordered_map<LuaEntity*, LuaEntity*>;
            static const std::unordered_set<LuaTypeId> allowedKeyTypes;

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

            size_t size() const;
            bool  empty() const;

            LuaEntity* find(const LuaEntity& key) const;

            bool insert(const LuaEntity& key, const LuaEntity& value);
            bool insert(LuaEntity&& key, LuaEntity&& value);

            void update(const LuaEntity& key, const LuaEntity& value);
            void update(LuaEntity&& key, LuaEntity&& value);

            /* TODO
             * Add update, delete, ...
             * Expose Iterator like in parameterstack
             * remove _etValue?
             */
            static std::unordered_set<LuaTypeId> getAllowedKeyTypes();

            bool operator==(const LuaTable& other) const;
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
