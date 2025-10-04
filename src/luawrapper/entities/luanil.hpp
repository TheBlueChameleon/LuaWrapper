#ifndef LUANIL_HPP
#define LUANIL_HPP

#include "luaentity.hpp"

namespace LuaWrapper
{
    class LuaNil : public LuaEntity
    {
        protected:
            void pushToLua(lua_State* L) const;
            void fetchFromLua(lua_State* L);
            void popFromLua(lua_State* L);

        public:
            LuaNil();

            bool isNil() const;

            nullptr_t get() const;
    };
}

#endif // LUANIL_HPP
