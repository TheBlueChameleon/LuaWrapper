#ifndef LUAFUNCTION_HPP
#define LUAFUNCTION_HPP

#include <string>

#include "luaentity.hpp"

namespace LuaWrapper
{
    class ParameterStack;

    class LuaFunction : public LuaEntity
    {
        private:
            std::string     name;
            lua_CFunction   pseudoFuncPtr;

        public:
            LuaFunction();
            LuaFunction(const std::string& name, const lua_CFunction value);

            LuaFunction(const LuaFunction& other) = default;
            LuaFunction(LuaFunction&& other) = default;
            LuaFunction& operator=(const LuaFunction& other) = default;
            LuaFunction& operator=(LuaFunction&& other) = default;

            static LuaTypeId getStaticTypeId();

            bool isFunction() const;

            const std::string& getName() const;
            lua_CFunction getPseudoFuncPtr() const;

            ParameterStack invoke(lua_State* const L, const ParameterStack& args);

            bool operator==(const LuaFunction& other) const;

            void pushToLua(lua_State* L) const;
            void fetchFromLua(lua_State* L);
            std::string to_string() const;
    };
}

namespace std
{
    template<>
    struct hash<LuaWrapper::LuaFunction>
    {
        size_t operator()(const LuaWrapper::LuaFunction& luaEntity) const;
    };
}

#endif // LUAFUNCTION_HPP
