#ifndef LUAINVOKE_HPP
#define LUAINVOKE_HPP

#include "luacapi.hpp"

namespace LuaWrapper
{
    class ParameterStack;

ParameterStack invokeLuaFunction(lua_State* const L, const char * const name, const ParameterStack& args);
}

#endif // LUAINVOKE_HPP
