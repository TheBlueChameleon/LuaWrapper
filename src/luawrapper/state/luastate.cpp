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

    void scanForLuaGlobals(
        lua_State* const L,
        std::unordered_map<std::string, LuaTypeId>& globals,
        std::unordered_map<std::string, LuaFunction>& functions
    )
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
            if (typeId == LuaTypeId::Function)
            {
                functions.emplace(std::make_pair(name, lua_tocfunction(L, -1)));
            }
            lua_pop(L, 1);                      // stack = [<next key>, table]
        }
        // lua_next has exhausted table         => stack = [table]
        lua_pop(L, 1);                          // stack = []
    }

    LuaState::LuaState(const std::filesystem::path& scriptFile)
    {
        L = initLua(scriptFile);
        scanForLuaGlobals(L, globalSymbols, functions);
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

    std::unordered_map<std::string, LuaTypeId> LuaState::getGlobalSymbols() const
    {
        return globalSymbols;
    }

    bool LuaState::hasGlobalSymbol(const std::string& name) const
    {
        return globalSymbols.find(name) != globalSymbols.end();
    }

    LuaTypeId LuaState::getGlobalSymbolType(const std::string& name) const
    {
        const auto it = globalSymbols.find(name);
        if (it == globalSymbols.end())
        {
            return LuaTypeId::None;
        }
        else
        {
            return it->second;
        }
    }

    LuaEntity* LuaState::getGlobalEntity(const std::string& name) const
    {
        const LuaTypeId type = getGlobalSymbolType(name);
        if (type == LuaTypeId::None)
        {
            return nullptr;
        }

        LuaEntity* result = LuaEntityFactory::makeLuaEntityFromTypeId(type);
        lua_getglobal(L, name.c_str());
        result->popFromLua(L);

        return result;
    }

    void LuaState::syncWithGlobalSymbol(LuaEntity& target, const std::string& name) const
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

        lua_getglobal(L, name.c_str());
        target.popFromLua(L);
    }

    lua_State* LuaState::expose() const
    {
        return L;
    }
}




