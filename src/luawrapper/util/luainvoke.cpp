#include <string>
using namespace std::string_literals;

#include "luainvoke.hpp"

#include "state/parameterstack.hpp"
#include "luaerror.hpp"

namespace LuaWrapper
{
    ParameterStack invokeLuaFunction(
        lua_State* const L,
        const char* const name,
        const ParameterStack& args
    )
    {
        lua_getglobal(L, name);
        if (lua_type(L, -1) != LuaTypeId::Function)
        {
            if (lua_type(L, -1) != LuaTypeId::None)
            {
                lua_pop(L, 1);
            }

            throw LuaInvalidStateError(
                "The function '"s + name + "' is not known to Lua"
            );
        }

        args.pushToLua(L);
        int resultCode = lua_pcall(L, args.size(), LUA_MULTRET, 0);

        ParameterStack result;
        const char* errMsg;
        switch (resultCode)
        {
            case LUA_OK:
                result.popFromLua(L);
                return result;

            case LUA_ERRRUN:
                errMsg = lua_tostring(L, -1);
                throw LuaCallError("LuaCall Runtime Error: "s + errMsg);
            case LUA_ERRERR:
                errMsg = lua_tostring(L, -1);
                throw LuaCallError("LuaCall Error Handling Error: "s + errMsg);
            case LUA_ERRMEM:
                errMsg = lua_tostring(L, -1);
                throw LuaCallError("LuaCall Memory Error: "s + errMsg);

            default:
                throw LuaInvalidStateError("Unkown LuaCall result code: "s +  std::to_string(resultCode));
        }
    }
}
