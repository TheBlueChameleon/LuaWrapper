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
            LuaBoolean();
            LuaBoolean(bool value);

            LuaBoolean(const LuaBoolean& other) = default;
            LuaBoolean(LuaBoolean&& other) = default;

            static LuaTypeId getStaticTypeId();

            void pushToLua(lua_State* L) const;
            void fetchFromLua(lua_State* L);

            bool isBoolean() const;

            bool getValue() const;
            void setValue(const bool newValue);

            std::string to_string() const;

            bool operator==(const LuaBoolean& other) const;
    };
}

namespace std
{
    template<>
    struct hash<LuaWrapper::LuaBoolean>
    {
        size_t operator()(const LuaWrapper::LuaBoolean& luaEntity) const;
    };
}

#endif // LUABOOLEAN_HPP
