#ifndef LUANIL_HPP
#define LUANIL_HPP

#include "luaentity.hpp"

namespace LuaWrapper
{
    class LuaNil : public LuaEntity
    {
        public:
            LuaNil();
            LuaNil(nullptr_t nil);

            static LuaTypeId getStaticTypeId();

            void pushToLua(lua_State* L) const;
            void fetchFromLua(lua_State* L);
            void popFromLua(lua_State* L);

            bool isNil() const;

            nullptr_t getValue() const;
    };
}

#endif // LUANIL_HPP
