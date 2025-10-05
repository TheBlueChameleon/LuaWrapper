#ifndef LUASTATE_HPP
#define LUASTATE_HPP

#include <filesystem>
#include <list>
#include <unordered_map>

#include "../util/luautil.hpp"

namespace LuaWrapper
{
    class LuaFunctionDescriptor;
    class ParameterStack;

    class LuaState
    {
        private:
            lua_State* L = nullptr;
            std::unordered_map<std::string, LuaTypeId> globalSymbols;

        public:
            LuaState(const std::filesystem::path& scriptFile);
            ~LuaState();

            std::unordered_map<std::string, LuaTypeId> getGlobalSymbols() const;

            lua_State* expose() const;
    };
}

#endif // LUASTATE_HPP
