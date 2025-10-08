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
            using EntitySet = std::unordered_set<LuaEntity*>;
            using EntityMap = std::unordered_map<LuaEntity*, LuaEntity*>;
            static const std::unordered_set<LuaTypeId> allowedKeyTypes;

            // iterator types
            using container                 = EntityMap;

            using iterator                  = container::iterator;
            using const_iterator            = container::const_iterator;

            using difference_type           = container::difference_type;
            using value_type                = container::value_type;
            using pointer                   = container::pointer;
            using reference                 = container::reference;
            using iterator_category         = iterator::iterator_category;

        private:
            EntityMap table;

        public:
            LuaTable();

            LuaTable(const LuaTable& other);
            LuaTable(LuaTable&& other);
            LuaTable& operator=(const LuaTable& other) = default;
            LuaTable& operator=(LuaTable&& other);

            ~LuaTable();

            static LuaTypeId getStaticTypeId();

            bool isTable() const;

            const EntityMap& getEntityMap() const;
            EntitySet getKeySet() const;
            EntitySet getValueSet() const;

            static std::unordered_set<LuaTypeId> getAllowedKeyTypes();

            size_t size() const;
            bool  empty() const;

            LuaEntity* find(const LuaEntity& key) const;

            iterator        begin();
            const_iterator  begin() const;
            iterator        end();
            const_iterator  end() const;

            bool insert(const LuaEntity& key, const LuaEntity& value);
            bool insert(LuaEntity&& key, LuaEntity&& value);

            void update(const LuaEntity& key, const LuaEntity& value);
            void update(LuaEntity&& key, LuaEntity&& value);

            void clear();
            bool erase(const LuaEntity& key);

            void pushToLua(lua_State* L) const;
            void fetchFromLua(lua_State* L);

            std::string to_string() const;

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
