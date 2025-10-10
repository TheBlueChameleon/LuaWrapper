#include <format>

#include "lualightuserdata.hpp"

namespace LuaWrapper
{
    LuaLightUserData::LuaLightUserData() :
        LuaLightUserData(nullptr)
    {}

    LuaLightUserData::LuaLightUserData(void* value) :
        LuaEntity(LuaTypeId::LightUserData, value)
    {}

    LuaTypeId LuaLightUserData::getStaticTypeId()
    {
        return LuaTypeId::LightUserData;
    }

    bool LuaLightUserData::isLightUserData() const
    {
        return true;
    }

    const void* LuaLightUserData::getValue() const
    {
        return value.getAsLightUserData();
    }

    void LuaLightUserData::setValue(void* const newValue)
    {
        value = newValue;
    }

    bool LuaLightUserData::operator==(const LuaLightUserData& other) const
    {
        return value == other.value;
    }

    void LuaLightUserData::pushToLua(lua_State* L) const
    {
        lua_pushlightuserdata(L, value.getAsLightUserData());
    }

    void LuaLightUserData::fetchFromLua(lua_State* L)
    {
        value = const_cast<void*>(lua_topointer(L, -1));
    }

    std::string LuaLightUserData::to_string() const
    {
        return std::format("LightUserData @ {}", value.getAsLightUserData());
    }
}

namespace std
{
    size_t hash<LuaWrapper::LuaLightUserData>::operator()(const LuaWrapper::LuaLightUserData& luaEntity) const
    {
        return std::hash<const void*>()(luaEntity.getValue());
    }
}
