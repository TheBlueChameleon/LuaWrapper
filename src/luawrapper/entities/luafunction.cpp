#include <format>

#include "luafunction.hpp"
#include "../state/parameterstack.hpp"
#include "../util/luautil.hpp"

namespace LuaWrapper
{
    LuaFunction::LuaFunction() :
        LuaFunction(nullptr)
    {}

    LuaFunction::LuaFunction(const lua_CFunction value) :
        LuaEntity(LuaTypeId::Function),
        value(value)
    {}

    LuaTypeId LuaFunction::getStaticTypeId()
    {
        return LuaTypeId::Function;
    }

    bool LuaFunction::isFunction() const
    {
        return true;
    }

    lua_CFunction LuaFunction::getValue() const
    {
        return value;
    }

    void LuaFunction::setValue(lua_CFunction newValue)
    {
        value = newValue;
    }

    ParameterStack LuaFunction::invoke(const ParameterStack& args)
    {
        throw LuaNotImplementedError("Not implemented: LuaFunction::invoke");
    }

    bool LuaFunction::operator==(const LuaFunction& other) const
    {
        return value == other.value;
    }

    void LuaFunction::pushToLua(lua_State* L) const
    {
        lua_pushcfunction(L, value);
    }

    void LuaFunction::fetchFromLua(lua_State* L)
    {
        value = reinterpret_cast<lua_CFunction>(lua_topointer(L, -1));
    }

    std::string LuaFunction::to_string() const
    {
        return std::format("Function @ {}", reinterpret_cast<void*>(value));
    }
}
