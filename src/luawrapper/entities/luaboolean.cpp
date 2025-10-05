#include "luaboolean.hpp"

namespace LuaWrapper
{
    LuaBoolean::LuaBoolean(bool value) :
        LuaEntity(LuaTypeId::Boolean),
        value(value)
    {}

    LuaTypeId LuaBoolean::getStaticTypeId()
    {
        return LuaTypeId::Boolean;
    }

    void LuaBoolean::pushToLua(lua_State* L) const
    {
        lua_pushboolean(L, value);
    }

    void LuaBoolean::fetchFromLua(lua_State* L)
    {
        value = lua_toboolean(L, -1);
    }

    void LuaBoolean::popFromLua(lua_State* L)
    {
        fetchFromLua(L);
        lua_pop(L, 1);
    }

    bool LuaBoolean::isBoolean() const
    {
        return true;
    }

    bool LuaBoolean::getValue() const
    {
        return value;
    }

    void LuaBoolean::setValue(const bool newValue)
    {
        value = newValue;
    }

    LuaBoolean operator ""_LB(unsigned long long int b)
    {
        return LuaBoolean(b);
    }

}
