#ifndef LUAENTITYFACTORY_HPP
#define LUAENTITYFACTORY_HPP

#include <string>

namespace LuaWrapper
{
    class LuaEntity;
    class LuaTable;
    class LuaTrivialType;

    class LuaEntityFactory
    {
        private:
            LuaEntityFactory();

        public:
            static LuaEntity* makeLuaEntity(const nullptr_t value = nullptr);
            static LuaEntity* makeLuaEntity(const bool value);
            static LuaEntity* makeLuaEntity(const void* value);
            static LuaEntity* makeLuaEntity(const double value);
            static LuaEntity* makeLuaEntity(const char* const value);
            static LuaEntity* makeLuaEntity(const std::string& value);
            static LuaEntity* makeLuaEntity(std::string&& value);
            static LuaEntity* makeLuaEntity(const LuaTable& value);
            static LuaEntity* makeLuaEntity(LuaTable&& value);

            static LuaEntity* makeLuaEntity(const LuaTrivialType& value);
            static LuaEntity* makeLuaEntity(LuaTrivialType&& value);

            static LuaEntity* makeLuaEntity(LuaEntity&& value);
            static LuaEntity* makeLuaEntity(const LuaEntity& value);
    };
}

#endif // LUAENTITYFACTORY_HPP
