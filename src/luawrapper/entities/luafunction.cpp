#include <iostream>
#include <format>

#include "luafunction.hpp"
#include "../state/parameterstack.hpp"
#include "../util/luautil.hpp"

namespace LuaWrapper
{
    LuaFunction::LuaFunction() :
        LuaFunction("", nullptr)
    {}

    LuaFunction::LuaFunction(const std::string& name, const lua_CFunction value) :
        LuaEntity(LuaTypeId::Function),
        name(name),
        pseudoFuncPtr(value)
    {}

    LuaTypeId LuaFunction::getStaticTypeId()
    {
        return LuaTypeId::Function;
    }

    bool LuaFunction::isFunction() const
    {
        return true;
    }

    const std::string& LuaFunction::getName() const
    {
        return name;
    }

    lua_CFunction LuaFunction::getPseudoFuncPtr() const
    {
        return pseudoFuncPtr;
    }

    ParameterStack LuaFunction::invoke(lua_State* const L, const ParameterStack& args)
    {
        if (pseudoFuncPtr == nullptr || name.empty())
        {
            throw LuaInvalidStateError("Function has not been configured");
        }

        lua_getglobal(L, name.c_str());
        if (lua_type(L, -1) != LuaTypeId::Function)
        {
            if (lua_type(L, -1) != LuaTypeId::None)
            {
                lua_pop(L, 1);
            }

            throw LuaInvalidArgumentError(
                "The function '" + name + "' is not known to Lua"
            );
        }

        args.pushToLua(L);
        lua_pcall(L, args.size(), LUA_MULTRET, 0);
        ParameterStack result;
        result.popFromLua(L);

        return result;
    }

    bool LuaFunction::operator==(const LuaFunction& other) const
    {
        return pseudoFuncPtr == other.pseudoFuncPtr;
    }

    void LuaFunction::pushToLua(lua_State* L) const
    {
        lua_pushcfunction(L, pseudoFuncPtr);
    }

    void LuaFunction::fetchFromLua(lua_State* L)
    {
        pseudoFuncPtr = reinterpret_cast<lua_CFunction>(lua_topointer(L, -1));
    }

    std::string LuaFunction::to_string() const
    {
        return std::format("Function @ {}", reinterpret_cast<void*>(pseudoFuncPtr));
    }
}

namespace std
{
    std::size_t std::hash<LuaWrapper::LuaFunction>::operator()(const LuaWrapper::LuaFunction& luaEntity) const
    {
        return std::hash<const void*>()(
                   reinterpret_cast<const void*>(luaEntity.getPseudoFuncPtr())
               );
    }
}
