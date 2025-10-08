#include "entities.hpp"

namespace LuaWrapper
{
    LuaNil::LuaNil() :
        LuaNil(nullptr)
    {}

    LuaNil::LuaNil(nullptr_t nil) :
        LuaEntity(LuaTypeId::Nil)
    {}

    LuaTypeId LuaNil::getStaticTypeId()
    {
        return LuaTypeId::Nil;
    }

    bool LuaNil::isNil() const
    {
        return true;
    }

    nullptr_t LuaNil::getValue() const
    {
        return nullptr;
    }

    bool LuaNil::operator==(const LuaNil& other) const
    {
        return true;
    }

    void LuaNil::pushToLua(lua_State* L) const
    {
        lua_pushnil(L);
    }

    void LuaNil::fetchFromLua(lua_State* L)
    {
        // sic: no-op
    }

    std::string LuaNil::to_string() const
    {
        return "nil";
    }
}

namespace std
{
    size_t hash<LuaWrapper::LuaNil>::operator()(const LuaWrapper::LuaNil& luaEntity) const
    {
        return 0;
    }
}
