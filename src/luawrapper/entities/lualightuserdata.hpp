#ifndef LUALIGHTUSERDATA_HPP
#define LUALIGHTUSERDATA_HPP

#include "luaentity.hpp"

namespace LuaWrapper
{
    class LuaLightUserData : public LuaEntity
    {
        public:
            LuaLightUserData();
            LuaLightUserData(void* value);

            LuaLightUserData(const LuaLightUserData& other) = default;
            LuaLightUserData(LuaLightUserData&& other) = default;
            LuaLightUserData& operator=(const LuaLightUserData& other) = default;
            LuaLightUserData& operator=(LuaLightUserData&& other) = default;

            static LuaTypeId getStaticTypeId();

            bool isLightUserData() const;

            const void* getValue() const;
            void        setValue(void* const newValue);

            bool operator==(const LuaLightUserData& other) const;

            void pushToLua(lua_State* L) const;
            void fetchFromLua(lua_State* L);

            std::string to_string() const;
    };
}

namespace std
{
    template<>
    struct hash<LuaWrapper::LuaLightUserData>
    {
        size_t operator()(const LuaWrapper::LuaLightUserData& luaEntity) const;
    };
}

#endif // LUALIGHTUSERDATA_HPP
