#include "entities.hpp"

namespace LuaWrapper
{
    LuaNil::LuaNil(nullptr_t nil) :
        LuaEntity(LuaTypeId::Nil)
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

    std::string LuaNil::to_string() const
    {
        return "nil";
    }

    bool LuaNil::operator==(const LuaNil& other) const
    {
        return true;
    }
}

namespace std
{
    size_t hash<LuaWrapper::LuaNil>::operator()(const LuaWrapper::LuaNil& luaEntity) const
    {
        return 0;
    }
}
