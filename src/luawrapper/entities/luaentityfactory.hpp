#ifndef LUAENTITYFACTORY_HPP
#define LUAENTITYFACTORY_HPP

#include <string>

#include "../util/luacapi.hpp"

#include "luaentityforwarddeclarations.hpp"

namespace LuaWrapper
{
    class LuaEntityFactory
    {
        private:
            LuaEntityFactory() = default;

        public:
            static LuaEntity* makeLuaEntityFromTypeId(const LuaTypeId typeId);

            static LuaEntity* makeLuaEntity(const nullptr_t value = nullptr);
            static LuaEntity* makeLuaEntity(const bool value);
            static LuaEntity* makeLuaEntity(const void* value);
            static LuaEntity* makeLuaEntity(const int value);
            static LuaEntity* makeLuaEntity(const double value);
            static LuaEntity* makeLuaEntity(const char* const value);
            static LuaEntity* makeLuaEntity(const std::string& value);
            static LuaEntity* makeLuaEntity(std::string&& value);
            static LuaEntity* makeLuaEntity(const std::string& name, const lua_CFunction value);

            static LuaEntity* makeLuaEntity(const LuaTrivialType& value);
            static LuaEntity* makeLuaEntity(LuaTrivialType&& value);

            static LuaEntity* makeLuaEntity(const LuaNil& value);
            static LuaEntity* makeLuaEntity(LuaNil&& value);
            static LuaEntity* makeLuaEntity(const LuaBoolean& value);
            static LuaEntity* makeLuaEntity(LuaBoolean&& value);
            static LuaEntity* makeLuaEntity(const LuaLightUserData& value);
            static LuaEntity* makeLuaEntity(LuaLightUserData&& value);
            static LuaEntity* makeLuaEntity(const LuaNumber& value);
            static LuaEntity* makeLuaEntity(LuaNumber&& value);
            static LuaEntity* makeLuaEntity(const LuaString& value);
            static LuaEntity* makeLuaEntity(LuaString&& value);
            static LuaEntity* makeLuaEntity(const LuaTable& value);
            static LuaEntity* makeLuaEntity(LuaTable&& value);
            static LuaEntity* makeLuaEntity(const LuaFunction& value);
            static LuaEntity* makeLuaEntity(LuaFunction&& value);

            static LuaEntity* makeLuaEntity(LuaEntity&& value);
            static LuaEntity* makeLuaEntity(const LuaEntity& value);
    };
}

#endif // LUAENTITYFACTORY_HPP
