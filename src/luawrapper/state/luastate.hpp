#ifndef LUASTATE_HPP
#define LUASTATE_HPP

#include <filesystem>
#include <list>
#include <unordered_map>

#include "../entities/luaentityforwarddeclarations.hpp"
#include "../util/luautil.hpp"

namespace LuaWrapper
{
    class ParameterStack;

    class LuaState
    {
        private:
            lua_State* L = nullptr;
            std::unordered_map<std::string, LuaTypeId>   globalSymbols;
            std::unordered_map<std::string, LuaFunction> functions;

        public:
            LuaState(const std::filesystem::path& scriptFile);
            ~LuaState();

            int getStackTopIndex() const;

            void synchronizeGlobalSymbols();

            const std::unordered_map<std::string, LuaTypeId>& getGlobalSymbols() const;
            const std::unordered_map<std::string, LuaFunction>& getFunctions() const;

            bool            hasGlobalSymbol(const std::string& name) const;
            LuaTypeId       getGlobalSymbolType(const std::string& name) const;
            LuaEntity*      getGlobalEntity(const std::string& name) const;
            void            synchronizeWithGlobalSymbol(LuaEntity& target, const std::string& name) const;
            void            setGlobalEntity(const std::string& name, const LuaEntity& value);

            bool            hasFunction(const std::string& name) const;
            LuaFunction     getFunction(const std::string& name) const;
            ParameterStack  invoke(const std::string& name, const ParameterStack& args) const;
            void            registerFunction(const std::string& name, const lua_CFunction funcPtr); // todo

            lua_State* expose() const;
    };
}

#endif // LUASTATE_HPP
