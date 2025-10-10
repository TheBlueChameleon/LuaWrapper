#include <string>
#include <format>
using namespace std::string_literals;

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
        if (name.empty())
        {
            throw LuaInvalidArgumentError("Function has not been configured");
        }
        if (pseudoFuncPtr == nullptr)
        {
            throw LuaInvalidArgumentError("Function '"s + name + "' has not been configured");
        }

        return invokeLuaFunction(L, name.c_str(), args);
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
