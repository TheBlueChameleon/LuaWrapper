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

            LuaNil(const LuaNil& other) = default;
            LuaNil(LuaNil&& other) = default;

            static LuaTypeId getStaticTypeId();

            void pushToLua(lua_State* L) const;
            void fetchFromLua(lua_State* L);

            bool isNil() const;

            nullptr_t getValue() const;

            std::string to_string() const;

            bool operator==(const LuaNil& other) const;
    };
}

namespace std
{
    template<>
    struct hash<LuaWrapper::LuaNil>
    {
        size_t operator()(const LuaWrapper::LuaNil& luaEntity) const;
    };
}

#endif // LUANIL_HPP
