#include "entities.hpp"

namespace LuaWrapper
{
    LuaNil::LuaNil() :
        LuaEntity(LuaTypeId::Nil)
    {}

    LuaNil::LuaNil(nullptr_t nil) :
        LuaNil()
    {}

    LuaTypeId LuaNil::getStaticTypeId()
    {
        return LuaTypeId::Nil;
    }

    void LuaNil::pushToLua(lua_State* L) const
    {
        lua_pushnil(L);
    }

    void LuaNil::fetchFromLua(lua_State* L)
    {
        // sic: no-op
    }

    bool LuaNil::isNil() const
    {
        return true;
    }

    nullptr_t LuaNil::getValue() const
    {
        return nullptr;
    }

    std::string LuaNil::repr() const
    {
        return "nil";
    }
}
