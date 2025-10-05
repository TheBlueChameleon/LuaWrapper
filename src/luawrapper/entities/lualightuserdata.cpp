#include <format>

#include "lualightuserdata.hpp"

namespace LuaWrapper
{
    LuaLightUserData::LuaLightUserData(void* value) :
        LuaEntity(LuaTypeId::LightUserData),
        value(value)
    {}

    LuaTypeId LuaLightUserData::getStaticTypeId()
    {
        return LuaTypeId::Boolean;
    }

    void LuaLightUserData::pushToLua(lua_State* L) const
    {
        lua_pushlightuserdata(L, const_cast<void*>(value));
    }

    void LuaLightUserData::fetchFromLua(lua_State* L)
    {
        value = lua_topointer(L, -1);
    }

    bool LuaLightUserData::isLightUserData() const
    {
        return true;
    }

    const void* LuaLightUserData::getValue() const
    {
        return value;
    }

    void LuaLightUserData::setValue(const void* newValue)
    {
        value = newValue;
    }

    std::string LuaLightUserData::repr() const
    {
        return std::format("{}", value);
    }
}
