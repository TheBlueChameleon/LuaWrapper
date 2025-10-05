#include <string>
using namespace std::string_literals;

#include "luastate.hpp"
#include "../util/luaerror.hpp"

namespace LuaWrapper
{

    lua_State* initLua(const std::filesystem::path& scriptFile)
    {
        lua_State* L = luaL_newstate();
        luaL_openlibs(L);

        if (luaL_loadfile(L, scriptFile.c_str()))
        {
            throw LuaError(
                "Could not load script '"s + scriptFile.c_str() + "':\n" +
                lua_tostring(L, -1)
            );
        }

        // Priming call. Without this, function names in script are unknown
        if (lua_pcall(L, 0, 0, 0))
        {
            throw LuaError(
                "Could not initialize script '"s + scriptFile.c_str() + "'.\n" +
                lua_tostring(L, -1)
            );
        }

        return L;
    }

    void scanForLuaGlobals(lua_State* const L, std::unordered_map<std::string, LuaTypeId>& globals)
    {
        const char* name;
        int         typeId;

        lua_pushglobaltable(L);                 // stack = [table]
        lua_pushnil(L);                         // stack = [nil, table]
        while (lua_next(L, -2) != 0)            // stack = [<next value>, <next key>, table]
        {
            // lua_next implies lua_pop(L, 1) to get key

            typeId = lua_type(L, -1);
            name = lua_tostring(L, -2);     // Get key(-2)

            globals.emplace(name, LuaTypeId(typeId));
            lua_pop(L, 1);                      // stack = [<next key>, table]
        }
        // lua_next has exhausted table         => stack = [table]
        lua_pop(L, 1);                          // stack = []
    }

    LuaState::LuaState(const std::filesystem::path& scriptFile)
    {
        L = initLua(scriptFile);
        scanForLuaGlobals(L, globalSymbols);
    }

    LuaState::~LuaState()
    {
        if (L)
        {
            lua_close(L);
        }
        L = nullptr;
    }

    std::unordered_map<std::string, LuaTypeId> LuaState::getGlobalSymbols() const
    {
        return globalSymbols;
    }

    lua_State* LuaState::expose() const
    {
        return L;
    }
}




