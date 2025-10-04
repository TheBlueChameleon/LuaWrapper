#include "luanil.hpp"

namespace LuaWrapper
{
    LuaNil::LuaNil() :
        LuaEntity(LuaTypeID::Nil)
    {}

    void LuaNil::pushToLua(lua_State* L) const
    {
        lua_pushnil(L);
    }

    void LuaNil::fetchFromLua(lua_State* L)
    {
        // sic: no-op
    }

    void LuaNil::popFromLua(lua_State* L)
    {
        lua_pop(L, 1);
    }

    bool LuaNil::isNil() const
    {
        return true;
    }

    nullptr_t LuaNil::get() const
    {
        return nullptr;
    }
}
