#include <iostream>
#include <string>
using namespace std::string_literals;

#include "luastate.hpp"
#include "../entities/luaentity.hpp"
#include "../entities/luaentityfactory.hpp"
#include "../entities/luafunction.hpp"
#include "../util/luaerror.hpp"

namespace LuaWrapper
{
    lua_State* initLua(const std::filesystem::path& scriptFile)
    {
        lua_State* L = luaL_newstate();
        luaL_openlibs(L);

        if (luaL_loadfile(L, scriptFile.c_str()))
        {
            throw LuaInitError(
                "Could not load script '"s + scriptFile.c_str() + "':\n" +
                lua_tostring(L, -1)
            );
        }

        // Priming call. Without this, function names in script are unknown
        if (lua_pcall(L, 0, 0, 0))
        {
            throw LuaInitError(
                "Could not initialize script '"s + scriptFile.c_str() + "'.\n" +
                lua_tostring(L, -1)
            );
        }

        return L;
    }

    LuaState::LuaState(const std::filesystem::path& scriptFile)
    {
        L = initLua(scriptFile);
        synchronizeGlobalSymbols();
    }

    LuaState::~LuaState()
    {
        if (L)
        {
            lua_close(L);
        }
        L = nullptr;
    }

    int LuaState::getStackTopIndex() const
    {
        return lua_gettop(L);
    }

    void LuaState::synchronizeGlobalSymbols()
    {
        globalSymbols.clear();
        functions.clear();

        const char* name;
        int         typeId;

        lua_pushglobaltable(L);                 // stack = [table]
        lua_pushnil(L);                         // stack = [nil, table]
        while (lua_next(L, -2) != 0)            // stack = [<next value>, <next key>, table]
        {
            // lua_next implies lua_pop(L, 1) to get key

            typeId = lua_type(L, -1);
            name = lua_tostring(L, -2);     // Get key(-2)

            globalSymbols[name] = LuaTypeId(typeId);
            if (typeId == LuaTypeId::Function)
            {
                functions[name] = lua_tocfunction(L, -1);
            }
            lua_pop(L, 1);                      // stack = [<next key>, table]
        }
        // lua_next has exhausted table         => stack = [table]
        lua_pop(L, 1);                          // stack = []
    }

    const std::unordered_map<std::string, LuaTypeId>& LuaState::getGlobalSymbols() const
    {
        return globalSymbols;
    }

    const std::unordered_map<std::string, LuaFunction>& LuaState::getFunctions() const
    {
        return functions;
    }

    bool LuaState::hasGlobalSymbol(const std::string& name) const
    {
        const LuaTypeId typeOnStack = lua_getglobal(L, name.c_str());
        lua_pop(L, 1);
        return typeOnStack != LuaTypeId::None;
    }

    LuaTypeId LuaState::getGlobalSymbolType(const std::string& name) const
    {
        const LuaTypeId typeOnStack = lua_getglobal(L, name.c_str());
        lua_pop(L, 1);
        return typeOnStack;
    }

    LuaEntity* LuaState::getGlobalEntity(const std::string& name) const
    {
        const LuaTypeId type = lua_getglobal(L, name.c_str());
        if (type == LuaTypeId::None)
        {
            return nullptr;
        }

        LuaEntity* result = LuaEntityFactory::makeLuaEntityFromTypeId(type);
        result->popFromLua(L);

        return result;
    }

    void LuaState::synchronizeWithGlobalSymbol(LuaEntity& target, const std::string& name) const
    {
        const LuaTypeId type = getGlobalSymbolType(name);
        if (type == LuaTypeId::None)
        {
            throw LuaInvalidArgumentError(
                "A global symbol with name "s + name + "does not exist"
            );
        }

        if (target.getTypeId() != type)
        {
            throw LuaInvalidArgumentError(
                "While synchronizing with global symbol: "s
                "'" + name + "' is of type " + type.getTypeName() + " "
                "while receiver is of type " + target.getTypeId().getTypeName()
            );
        }

        int typeOnStack = lua_getglobal(L, name.c_str());
        if (typeOnStack != target.getTypeId())
        {
            throw LuaInvalidArgumentError(
                "While synchronizing with global symbol: "s
                "While synchronizing with global symbol: "s
                "'" + name + "' is of type " + type.getTypeName() + " "
                "while receiver is of type " + target.getTypeId().getTypeName()
            );
        }

        target.popFromLua(L);
    }

    lua_State* LuaState::expose() const
    {
        return L;
    }
}




