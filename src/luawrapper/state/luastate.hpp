#ifndef LUASTATE_HPP
#define LUASTATE_HPP

#include <filesystem>
#include <list>
#include <unordered_set>

#include "../util/luacapi.hpp"

namespace LuaWrapper
{
    class LuaFunctionDescriptor;
    class ParameterStack;

    class LuaState
    {
        private:
            lua_State* L = nullptr;
            std::unordered_set<std::string> luaFunctionNames;
            // --> luaGlobals as named tuple <name, type>

        public:
            LuaState(const std::filesystem::path& scriptFile);
            ~LuaState();

            const std::unordered_set<std::string>& getLuaFunctionNames() const;
    };
}

#endif // LUASTATE_HPP
