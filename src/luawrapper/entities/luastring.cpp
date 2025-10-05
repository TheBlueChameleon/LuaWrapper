#include "luastring.hpp"

namespace LuaWrapper
{
    LuaString::LuaString(const char* value) :
        LuaEntity(LuaTypeId::String),
        value(value)
    {}

    LuaString::LuaString(const std::string& value) :
        LuaEntity(LuaTypeId::String),
        value(value)
    {}

    LuaString::LuaString(std::string&& value) :
        LuaEntity(LuaTypeId::String),
        value(std::move(value))
    {}

    LuaTypeId LuaString::getStaticTypeId()
    {
        return LuaTypeId::String;
    }

    void LuaString::pushToLua(lua_State* L) const
    {
        lua_pushstring(L, value.c_str());
    }

    void LuaString::fetchFromLua(lua_State* L)
    {
        value = lua_tostring(L, -1);
    }

    bool LuaString::isString() const
    {
        return true;
    }

    std::string LuaString::getValue() const
    {
        return value;
    }

    void LuaString::setValue(const std::string& newValue)
    {
        value = newValue;
    }

    std::string LuaString::to_string() const
    {
        return value;
    }
}
