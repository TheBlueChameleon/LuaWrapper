#ifndef LUABOOLEAN_HPP
#define LUABOOLEAN_HPP

#include "luaentity.hpp"

namespace LuaWrapper
{
    class LuaBoolean : public LuaEntity
    {
        private:
            bool value;

        public:
            LuaBoolean(bool value = true);

            static LuaTypeId getStaticTypeId();

            void pushToLua(lua_State* L) const;
            void fetchFromLua(lua_State* L);
            void popFromLua(lua_State* L);

            bool isBoolean() const;

            bool getValue() const;
            void setValue(const bool newValue);
    };

    LuaBoolean operator""_LB(unsigned long long int b);
}

#endif // LUABOOLEAN_HPP
